//! Builds/links the SLOP std C library (strlib/file/thread), owns the canonical
//! `slop_runtime.h`, and exports its header dir via `DEP_SLOP_STD_INCLUDE`.
//! No Rust API is required for the link.
#![allow(non_camel_case_types)]
