# slop-std-sys

Rust `-sys` crate for building and linking the vendored SLOP standard C
library. It includes the canonical `slop_runtime.h` plus the string, file, and
thread support libraries.

The crate compiles its bundled C sources from `build.rs`; consumers do not need
to install SLOP separately. It provides native linkage and headers, but does not
currently expose Rust FFI declarations.

The vendored standard library and runtime snapshot comes from SLOP 0.3.0.

## Usage

Add the crate as a direct dependency:

```toml
[dependencies]
slop-std-sys = "0.3.0"
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
- A C compiler supported by the `cc` crate
- POSIX threads (`pthread`)

## License

Licensed under the Apache License, Version 2.0. See [LICENSE](LICENSE).
