use slop_std_sys as _;

extern "C" {
    fn strlib_min(a: i64, b: i64) -> i64;
}

#[test]
fn links_and_calls_slop_std() {
    assert_eq!(unsafe { strlib_min(-7, 4) }, -7);
}
