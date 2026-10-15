# slop-std-sys

Rust `-sys` crate for building and linking the vendored SLOP standard C
library. It includes the canonical `slop_runtime.h` plus the string, file, and
thread support libraries.

The crate compiles its bundled C sources from `build.rs`; consumers do not need
to install SLOP separately. It provides native linkage and headers, but does not
currently expose Rust FFI declarations.

The vendored standard library and runtime snapshot comes from SLOP 0.5.0.

## Usage

Add the crate as a direct dependency:

```toml
[dependencies]
slop-std-sys = "0.5.0"
```

Cargo makes the public C header directory available to your build script as
`DEP_SLOP_STD_INCLUDE`:

```rust
let include = std::env::var_os("DEP_SLOP_STD_INCLUDE")
    .expect("slop-std-sys must be a direct dependency");

cc::Build::new()
    .include(include)
    .file("src/consumer.c")
    .compile("consumer");
```

## Requirements

- Rust 1.63 or newer
- A C compiler supported by the `cc` crate that accepts GNU C extensions:
  GCC or Clang, MinGW-w64 GCC for `*-windows-gnu`, or clang-cl for
  `*-windows-msvc` (Visual Studio's C++ Clang tools or LLVM). MSVC's
  `cl.exe` can't compile the generated C, so the build uses clang-cl on
  MSVC targets unless `CC` names another compiler.
- POSIX threads (`pthread`) on Unix targets; Windows targets use the Win32
  thread API

## License

Licensed under the Apache License, Version 2.0. See [LICENSE](LICENSE).
