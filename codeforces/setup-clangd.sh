#!/usr/bin/env bash
# Generate codeforces/compile_flags.txt so clangd can resolve <bits/stdc++.h>.
#
# clangd is clang-based and, unwrapped from nix, finds neither libstdc++ nor its
# own builtin headers. This asks g++ where its headers live and hands clangd the
# same list. GCC's internal include dirs are dropped because clang chokes on
# GCC's stddef.h; clang's own resource-dir covers those.
#
# Re-run after changing the flake / updating the toolchain.
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
out="$root/compile_flags.txt"

command -v g++ >/dev/null || { echo "g++ not found - are you in the nix devShell?" >&2; exit 1; }
command -v clang++ >/dev/null || { echo "clang++ not found - are you in the nix devShell?" >&2; exit 1; }

# clang's builtin headers (stdarg.h, stddef.h, ...), via the nix wrapper.
wrapper="$(dirname "$(dirname "$(command -v clang++)")")"
resource_dir="$(sed -n 's/.*-resource-dir=\([^ ]*\).*/\1/p' "$wrapper/nix-support/cc-cflags")"

includes="$(env -u CPLUS_INCLUDE_PATH g++ -E -x c++ - -v </dev/null 2>&1 \
  | sed -n '/#include <...> search starts here:/,/End of search list./p' \
  | sed '1d;$d' | sed 's/^ *//' \
  | grep -v '(framework directory)' \
  | grep -v '/lib/gcc/')"

{
  echo "-std=c++23"
  echo "-DLOCAL"
  echo "-nostdinc++"
  [ -n "$resource_dir" ] && echo "-resource-dir=$resource_dir"
  while IFS= read -r p; do
    [ -n "$p" ] || continue
    echo "-isystem"
    echo "$p"
  done <<<"$includes"
} >"$out"

echo "wrote $out"
