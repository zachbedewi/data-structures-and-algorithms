#!/usr/bin/env bash
# Copy the template into a new problem directory.
#
#   ./new.sh 1234a                 -> codeforces/1234a/
#   ./new.sh round-999 a b c d     -> codeforces/round-999/{a,b,c,d}/
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
template="$root/template"

if [ $# -eq 0 ]; then
  echo "usage: $0 <dir> [problem...]" >&2
  exit 1
fi

# Make sure clangd has flags to work with (covers all dirs under codeforces/).
[ -f "$root/compile_flags.txt" ] || "$root/setup-clangd.sh"

dest="$root/$1"
shift

if [ $# -eq 0 ]; then
  targets=("$dest")
else
  targets=()
  for p in "$@"; do targets+=("$dest/$p"); done
fi

for t in "${targets[@]}"; do
  if [ -e "$t" ]; then
    echo "skip (exists): $t"
    continue
  fi
  mkdir -p "$t"
  cp "$template/sol.cpp" "$template/Makefile" "$template/in.txt" "$t/"
  echo "created: $t"
done
