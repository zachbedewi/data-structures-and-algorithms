# Codeforces

## New problem

```sh
./new.sh 1234a              # -> 1234a/
./new.sh round-999 a b c d  # -> round-999/{a,b,c,d}/
```

Each directory gets `sol.cpp`, `Makefile`, and `in.txt`.

## Solving

```sh
cd 1234a
$EDITOR in.txt              # paste the sample input
make run                    # build (debug) + run against in.txt
make fast                   # -O2, no debug flags — what the judge sees
```

Debug builds define `LOCAL`, so `dbg(a, b, c)` prints to stderr; `make fast`
compiles it away. They also enable `_GLIBCXX_DEBUG` (bounds-checked vectors,
iterator validation) and `-ftrapv` (signed overflow aborts). Check anything
suspicious with `make fast` before submitting, since those flags change
behaviour and cost runtime.

## Emacs + clangd

`setup-clangd.sh` writes `compile_flags.txt` here, which clangd picks up for
every problem directory underneath. `new.sh` runs it automatically the first
time. Re-run it by hand after changing `flake.nix` or updating the toolchain:

```sh
./setup-clangd.sh
```

It exists because clangd is clang-based and, unwrapped from nix, resolves
neither libstdc++ (so no `<bits/stdc++.h>`) nor its own builtin headers. The
script asks `g++` where its headers live and hands clangd the same list.

Emacs needs the nix devShell on its `exec-path` to find `clangd` at all — use
[envrc](https://github.com/purcell/envrc), which applies direnv per buffer:

```elisp
(use-package envrc
  :hook (after-init . envrc-global-mode))

(use-package eglot
  :hook (c++-mode . eglot-ensure))
```

Load order matters: `envrc-global-mode` must be active before eglot starts, or
eglot will look for `clangd` on the system `PATH` and fail.
