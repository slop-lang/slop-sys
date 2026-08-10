//! Builds and links the complete slop-rdf C library, including Turtle and N3.
//! Depends on slop-std-sys for the runtime header and strlib/file symbols, and
//! exports its header directory via `DEP_SLOP_RDF_INCLUDE`.
#![allow(non_camel_case_types)]

// Retain the native-link metadata from slop-std-sys even though this crate does
// not expose Rust FFI declarations of its own.
use slop_std_sys as _;
