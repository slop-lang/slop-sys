# Releasing slop-sys

The workspace publishes two independent crates. `slop-rdf-sys` depends on
`slop-std-sys`, so the standard crate must be available in the crates.io index
before the RDF crate is published. Publishing is permanent and the two uploads
are not atomic.

## Preflight

Start from the commit that will be published and require a clean working tree:

```sh
git status --short
cargo fmt --all --check
cargo clippy --workspace --all-targets -- -D warnings
RUSTDOCFLAGS="-D warnings" cargo doc --workspace --no-deps
cargo test --workspace --all-targets
cargo publish --workspace --dry-run
```

Inspect the exact files in both archives. Each list must contain `README.md`
and `LICENSE`:

```sh
cargo package -p slop-std-sys --list
cargo package -p slop-rdf-sys --list
```

Confirm that the `slop-std-sys` and `slop-rdf-sys` names are still unclaimed on
crates.io and that Cargo is authenticated as the intended owner. Do not use
`--allow-dirty` or `--no-verify` for a release.

## Publish

Publish the dependency first:

```sh
cargo publish -p slop-std-sys
```

Wait until Cargo can retrieve the exact published version from the crates.io
index:

```sh
cargo info slop-std-sys@0.1.2
```

Then publish the dependent crate:

```sh
cargo publish -p slop-rdf-sys
```

Using `cargo publish --workspace` is supported, but the explicit sequence above
makes a partial release visible and easier to recover from. A failure while
publishing the RDF crate cannot roll back the standard crate.

## Tag

After both crates are confirmed on crates.io, create annotated, crate-specific
tags on the exact published commit. Do not move the existing workspace tags.

```sh
git tag -a slop-std-sys-v0.1.2 -m "Release slop-std-sys 0.1.2"
git tag -a slop-rdf-sys-v0.3.0 -m "Release slop-rdf-sys 0.3.0"
git push origin slop-std-sys-v0.1.2 slop-rdf-sys-v0.3.0
```
