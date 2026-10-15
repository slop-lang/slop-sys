use slop_rdf_sys as _;

extern "C" {
    fn slop_rdf_ttl_is_pn_chars_base(c: u8) -> u8;
    fn slop_rdf_n3_is_formula_start(c: u8) -> u8;
}

#[test]
fn links_and_calls_slop_rdf_turtle_n3_and_std() {
    assert_ne!(unsafe { slop_rdf_ttl_is_pn_chars_base(b'A') }, 0);
    assert_eq!(unsafe { slop_rdf_ttl_is_pn_chars_base(b'-') }, 0);
    assert_ne!(unsafe { slop_rdf_n3_is_formula_start(b'{') }, 0);
    assert_eq!(unsafe { slop_rdf_n3_is_formula_start(b'<') }, 0);
}
