# slop-sys

Rust `-sys` crates for building and linking the vendored SLOP C runtime and RDF
libraries with Cargo.

This workspace contains two crates:

| Crate | Contents |
| --- | --- |
| [`slop-std-sys`](slop-std-sys/README.md) | The SLOP runtime header and the string, file, and thread support libraries |
| [`slop-rdf-sys`](slop-rdf-sys/README.md) | RDF data structures, indexing and vocabulary helpers, and Turtle and Notation3 parsing and serialization |

`slop-rdf-sys` depends on `slop-std-sys`. Both crates compile their bundled C
sources from `build.rs`, so consumers do not need to install the SLOP libraries
separately. The crates provide native libraries and header paths for downstream
build scripts; they do not currently expose Rust FFI declarations.

The current standard-library snapshot comes from SLOP v0.4.3. The RDF snapshot
was generated from `slop-rdf` v0.5.2 with SLOP v0.4.3. These versions are also
recorded in each crate's package metadata.

## Requirements

- A Rust toolchain with Cargo
- A C compiler supported by the [`cc`](https://crates.io/crates/cc) crate that accepts GNU C extensions:
  GCC or Clang, MinGW-w64 GCC for `*-windows-gnu`, or clang-cl for
  `*-windows-msvc` (Visual Studio's C++ Clang tools or LLVM). MSVC's
  `cl.exe` can't compile the generated C, so the build uses clang-cl on
  MSVC targets unless `CC` names another compiler.
- POSIX threads (`pthread`) on Unix targets, required by `slop-std-sys`;
  Windows targets use the Win32 thread API

## Building

Build the complete workspace:

```sh
cargo build --workspace
```

Run the workspace checks and tests:

```sh
cargo test --workspace
```

Use the published crates from another Cargo project:

```toml
[dependencies]
slop-std-sys = "0.4.3"
slop-rdf-sys = "0.5.2"
```

For local development, use path dependencies instead:

```toml
[dependencies]
slop-std-sys = { path = "path/to/slop-sys/slop-std-sys" }
slop-rdf-sys = { path = "path/to/slop-sys/slop-rdf-sys" }
```

Depending on `slop-rdf-sys` also builds and links `slop-std-sys`. Cargo exposes
the crates' public C header directories to downstream build scripts through
`DEP_SLOP_STD_INCLUDE` and `DEP_SLOP_RDF_INCLUDE`, respectively.

Consumers compiling C sources against the RDF, Turtle, or Notation3 headers
should depend directly on both crates so both include-directory variables are
available to their build script.

## Repository layout

```text
slop-std-sys/
  csrc/runtime/   SLOP runtime header
  csrc/src/       Standard support C sources and headers
slop-rdf-sys/
  csrc/runtime/   Runtime header used to compile the RDF library
  csrc/src/       RDF, Turtle, and Notation3 C sources and headers
```

## Releasing

See [RELEASING.md](RELEASING.md) for the release checks, publication order, and
tagging procedure.

## License

Licensed under the [Apache License, Version 2.0](LICENSE).
