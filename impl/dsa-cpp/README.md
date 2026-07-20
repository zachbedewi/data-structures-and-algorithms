# dsa-cpp

C++ implementations of data structures and algorithms from scratch.

C++23, CMake, Catch2 for testing, clangd for LSP.

## Prerequisites

- [Nix](https://nixos.org/) with flakes enabled
- [direnv](https://direnv.net/) (optional but recommended)

The flake at the repo root provides: clang, cmake, ninja, clangd, clang-tidy, cppcheck, ccache.

## Quick Start

```bash
# Enter the dev shell (automatic with direnv, or manually):
cd /path/to/data-structures-and-algorithms
nix develop  # or just `cd` here if direnv is set up

# Navigate to the C++ project:
cd impl/dsa-cpp

# Configure (generates build/compile_commands.json for clangd):
cmake --preset dev

# Build:
cmake --build --preset dev

# Test:
ctest --preset dev
```

## Day-to-Day Workflow

```bash
# Build and test after editing existing files:
cmake --build --preset dev && ctest --preset dev

# After adding/removing source files or editing CMakeLists.txt:
cmake --preset dev            # regenerates compile_commands.json
cmake --build --preset dev    # build
ctest --preset dev            # test

# Run with full static analysis and sanitizers:
cmake --preset check
cmake --build --preset check
ctest --preset check
```

Note: if you only run `cmake --build`, Ninja will auto-reconfigure when it detects
CMakeLists.txt changes — so the compile database stays in sync as long as you build.

## Presets

| Preset  | Purpose                                    |
|---------|--------------------------------------------|
| `dev`   | Fast iteration — no sanitizers, no linting |
| `check` | Full checks — ASan, UBSan, clang-tidy, cppcheck |

## Project Layout

```
impl/dsa-cpp/
├── CMakeLists.txt          # Top-level CMake
├── CMakePresets.json       # Build presets
├── Dependencies.cmake      # CPM dependencies (Catch2)
├── ProjectOptions.cmake    # Compiler options, sanitizers, static analysis
├── .clangd                 # LSP config (points to build/)
├── .clang-format           # Formatting rules
├── .clang-tidy             # Linting rules
├── cmake/                  # CMake modules
├── include/
│   └── <ds_name>/
│       └── <ds_name>.hpp   # Public header
├── src/
│   └── <ds_name>/
│       ├── CMakeLists.txt  # Library target
│       └── <ds_name>.cpp   # Implementation
└── test/
    ├── CMakeLists.txt      # Test targets
    └── <ds_name>_test.cpp  # Tests
```

## Adding a New Data Structure

Example: adding a `hash_map` implementation.

### 1. Create the header

```bash
mkdir -p include/hash_map
```

Create `include/hash_map/hash_map.hpp`:
```cpp
#ifndef DSA_HASH_MAP_HPP
#define DSA_HASH_MAP_HPP

namespace dsa {

template<typename K, typename V>
class HashMap
{
  // ...
};

} // namespace dsa

#endif
```

### 2. Create the source

```bash
mkdir -p src/hash_map
```

Create `src/hash_map/hash_map.cpp`:
```cpp
#include <hash_map/hash_map.hpp>

// Implementation (or leave empty for header-only)
```

Create `src/hash_map/CMakeLists.txt`:
```cmake
add_library(hash_map hash_map.cpp)
target_link_libraries(hash_map PRIVATE myproject::myproject_options myproject::myproject_warnings)
target_include_directories(hash_map PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
```

### 3. Register in src/CMakeLists.txt

```cmake
add_subdirectory(variant)
add_subdirectory(hash_map)   # <-- add this
```

### 4. Create the test

Create `test/hash_map_test.cpp`:
```cpp
#include <catch2/catch_test_macros.hpp>
#include <hash_map/hash_map.hpp>

TEST_CASE("HashMap basic operations", "[hash_map]")
{
  dsa::HashMap<std::string, int> map;
  // ...
}
```

Add to `test/CMakeLists.txt`:
```cmake
# --- hash_map ---
add_executable(hash_map_test hash_map_test.cpp)
target_link_libraries(hash_map_test PRIVATE
  myproject::myproject_warnings
  myproject::myproject_options
  hash_map
  Catch2::Catch2WithMain)
catch_discover_tests(hash_map_test TEST_PREFIX "hash_map.")
```

### 5. Build and test

```bash
cmake --build --preset dev
ctest --preset dev
```

## Editor Setup (Emacs)

This project uses `clangd` for LSP. After running `cmake --preset dev` once (to generate
`build/compile_commands.json`), clangd will provide completions, diagnostics, and navigation.

### eglot (built-in, Emacs 29+)

Add to your Emacs config:
```elisp
(use-package eglot
  :hook (c++-mode . eglot-ensure)
  :config
  (add-to-list 'eglot-server-programs '(c++-mode . ("clangd"))))
```

### lsp-mode (alternative)

```elisp
(use-package lsp-mode
  :hook (c++-mode . lsp-deferred)
  :config
  (setq lsp-clients-clangd-args '("--header-insertion=never")))
```

The `.clangd` file in this directory tells clangd where to find the compilation database.
No additional configuration needed.
