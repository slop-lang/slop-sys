# slop-rdf-sys

Rust `-sys` crate for building and linking the vendored `slop-rdf` C library,
including RDF data structures, indexing and vocabulary helpers, and Turtle and
Notation3 parsing and serialization.

The crate compiles its bundled C sources from `build.rs` and depends on
`slop-std-sys` for runtime, string, and file symbols. It provides native linkage
and headers, but does not currently expose Rust FFI declarations.

The vendored snapshot contains `slop-rdf` 0.4.0 generated with SLOP 0.3.0.

## Usage

Add both crates as direct dependencies when compiling C code against the RDF,
Turtle, or Notation3 headers. A direct dependency on each crate makes both
header directories available to your build script:

```toml
[dependencies]
slop-rdf-sys = "0.4.0"
slop-std-sys = "0.3.0"
```

```rust
let rdf_include = std::env::var_os("DEP_SLOP_RDF_INCLUDE")
    .expect("slop-rdf-sys must be a direct dependency");
let std_include = std::env::var_os("DEP_SLOP_STD_INCLUDE")
    .expect("slop-std-sys must be a direct dependency");

cc::Build::new()
    .include(rdf_include)
    .include(std_include)
    .file("src/consumer.c")
    .compile("consumer");
```

Depending only on `slop-rdf-sys` still builds and links `slop-std-sys`
transitively. The second direct dependency is needed when the consumer's own C
sources include standard-library headers such as `slop_strlib.h` or
`slop_file.h`.

## Requirements

- Rust 1.63 or newer
- A C compiler supported by the `cc` crate
- POSIX threads (`pthread`), through `slop-std-sys`

## License

Licensed under the Apache License, Version 2.0. See [LICENSE](LICENSE).
