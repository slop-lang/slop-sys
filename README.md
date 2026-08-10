# slop-sys

Rust `-sys` crates for building and linking the vendored SLOP C runtime and RDF
libraries with Cargo.

This workspace contains two crates:

| Crate | Contents |
| --- | --- |
| `slop-std-sys` | The SLOP runtime header and the string, file, and thread support libraries |
| `slop-rdf-sys` | RDF data structures, indexing and vocabulary helpers, and Turtle parsing and serialization |

`slop-rdf-sys` depends on `slop-std-sys`. Both crates compile their bundled C
sources from `build.rs`, so consumers do not need to install the SLOP libraries
separately. The crates provide native libraries and header paths for downstream
build scripts; they do not currently expose Rust FFI declarations.

## Requirements

- A Rust toolchain with Cargo
- A C compiler supported by the [`cc`](https://crates.io/crates/cc) crate
- POSIX threads (`pthread`), required by `slop-std-sys`

## Building

Build the complete workspace:

```sh
cargo build --workspace
```

Run the workspace checks and tests:

```sh
cargo test --workspace
```

To use the crates from another workspace before they are published, add path
dependencies:

```toml
[dependencies]
slop-std-sys = { path = "path/to/slop-sys/slop-std-sys" }
slop-rdf-sys = { path = "path/to/slop-sys/slop-rdf-sys" }
```

Depending on `slop-rdf-sys` also builds and links `slop-std-sys`. Cargo exposes
the crates' public C header directories to downstream build scripts through
`DEP_SLOP_STD_INCLUDE` and `DEP_SLOP_RDF_INCLUDE`, respectively.

## Repository layout

```text
slop-std-sys/
  csrc/runtime/   SLOP runtime header
  csrc/src/       Standard support C sources and headers
slop-rdf-sys/
  csrc/runtime/   Runtime header used to compile the RDF library
  csrc/src/       RDF and Turtle C sources and headers
```

## License

Licensed under the [Apache License, Version 2.0](LICENSE).
