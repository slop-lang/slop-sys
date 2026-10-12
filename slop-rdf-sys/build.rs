use std::env;
use std::path::{Path, PathBuf};

fn main() {
    let manifest = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    let csrc = Path::new("csrc/src");
    let runtime = Path::new("csrc/runtime");

    let std_inc = env::var("DEP_SLOP_STD_INCLUDE")
        .expect("DEP_SLOP_STD_INCLUDE unset — is slop-std-sys a [dependencies] entry?");

    let sources = [
        "slop_rdf.c",
        "slop_index.c",
        "slop_list.c",
        "slop_vocab.c",
        "slop_xsd.c",
        "slop_common.c",
        "slop_ttl.c",
        "slop_n3.c",
        "slop_serialize_ttl.c",
        "slop_serialize_n3.c",
    ];

    let mut build = cc::Build::new();
    // The generated C uses GNU statement expressions and __auto_type, which
    // MSVC's cl.exe rejects; clang-cl accepts them. CC still overrides this.
    build
        .prefer_clang_cl_over_msvc(true)
        .include(runtime)
        .include(csrc)
        .include(&std_inc)
        .define("SLOP_ARENA_NO_CAP", None)
        .define("SLOP_INTERN_THREADSAFE", None)
        .opt_level(2)
        .warnings(false);
    for s in &sources {
        build.file(csrc.join(s));
    }
    build.compile("slop_rdf");

    println!("cargo:include={}", manifest.join("csrc/src").display());
    println!("cargo:rerun-if-changed=csrc");
    println!("cargo:rerun-if-changed=build.rs");
}
