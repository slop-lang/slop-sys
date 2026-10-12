use std::env;
use std::path::{Path, PathBuf};

fn main() {
    let manifest = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    let csrc = Path::new("csrc/src");
    let runtime = Path::new("csrc/runtime");

    let sources = [
        "slop_strlib.c",
        "slop_file.c",
        "slop_thread.c",
        "slop_std_shim.c",
    ];

    let mut build = cc::Build::new();
    // The generated C uses GNU statement expressions and __auto_type, which
    // MSVC's cl.exe rejects; clang-cl accepts them. CC still overrides this.
    build
        .prefer_clang_cl_over_msvc(true)
        .include(runtime)
        .include(csrc)
        .define("SLOP_ARENA_NO_CAP", None)
        .define("SLOP_INTERN_THREADSAFE", None)
        .opt_level(2)
        .warnings(false);
    for s in &sources {
        build.file(csrc.join(s));
    }
    build.compile("slop_std");

    println!("cargo:include={}", manifest.join("csrc/src").display());
    // slop_runtime.h threads through pthreads on POSIX and Win32 on Windows.
    if env::var("CARGO_CFG_TARGET_OS").as_deref() != Ok("windows") {
        println!("cargo:rustc-link-lib=pthread");
    }
    println!("cargo:rerun-if-changed=csrc");
    println!("cargo:rerun-if-changed=build.rs");
}
