use std::env;
use std::path::{Path, PathBuf};

fn main() {
    let manifest = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    let csrc = Path::new("csrc/src");
    let runtime = Path::new("csrc/runtime");

    let sources = ["slop_strlib.c", "slop_file.c", "slop_thread.c", "slop_std_shim.c"];

    let mut build = cc::Build::new();
    build
        .include(runtime)
        .include(csrc)
        .define("SLOP_ARENA_NO_CAP", None)
        .define("SLOP_INTERN_THREADSAFE", None)
        .opt_level(2)
        .warnings(false);
    for s in &sources { build.file(csrc.join(s)); }
    build.compile("slop_std");

    println!("cargo:include={}", manifest.join("csrc/src").display());
    println!("cargo:rustc-link-lib=pthread");
    println!("cargo:rerun-if-changed=csrc");
    println!("cargo:rerun-if-changed=build.rs");
}
