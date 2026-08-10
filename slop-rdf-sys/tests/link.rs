use slop_rdf_sys as _;

extern "C" {
    fn ttl_is_pn_chars_base(c: u8) -> u8;
}

#[test]
fn links_and_calls_slop_rdf_and_std() {
    assert_ne!(unsafe { ttl_is_pn_chars_base(b'A') }, 0);
    assert_eq!(unsafe { ttl_is_pn_chars_base(b'-') }, 0);
}
