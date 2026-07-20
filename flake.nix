{
  description = "C++ DSA development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };

  outputs = { nixpkgs, ... }:
    let
      systems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
    in
    {
      devShells = forAllSystems (pkgs:
        let
          llvm = pkgs.llvmPackages_19;
        in
        {
          default = pkgs.mkShell {
            packages = with pkgs; [
              # Build system
              cmake
              ninja
              pkg-config

              # Compiler toolchain
              llvm.clang
              llvm.llvm

              # Static analysis & formatting
              llvm.clang-tools  # includes clangd, clang-tidy, clang-format
              cppcheck
              include-what-you-use

              # Build acceleration
              ccache

              # Testing & coverage
              lcov
            ] ++ lib.optionals stdenv.isLinux [
              gdb
              valgrind
            ];

            shellHook = ''
              export CC=clang
              export CXX=clang++
            '' + pkgs.lib.optionalString pkgs.stdenv.isDarwin ''
              # clang-tidy doesn't use the nix clang wrapper, so it can't find libc++ headers.
              libcxx_include=$(sed -n 's/.*-cxx-isystem \([^ ]*\).*/\1/p' $(dirname $(dirname $(which clang)))/nix-support/libcxx-cxxflags)
              export CPLUS_INCLUDE_PATH="''${libcxx_include}''${CPLUS_INCLUDE_PATH:+:$CPLUS_INCLUDE_PATH}"
            '';
          };
        });
    };
}
