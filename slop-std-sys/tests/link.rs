use slop_std_sys as _;
use std::os::raw::{c_char, c_void};

/// `slop_string` from slop_runtime.h
#[repr(C)]
struct SlopString {
    len: usize,
    data: *const c_char,
}

/// A generated `{ bool is_ok; union { int64_t ok; <error enum> err; } data; }`
#[repr(C)]
struct ResultInt {
    is_ok: bool,
    data: i64,
}

/// A generated `{ bool is_ok; union { uint8_t ok; <error enum> err; } data; }`
#[repr(C)]
struct ResultVoid {
    is_ok: bool,
    data: u32,
}

/// `slop_closure_t` from slop_runtime.h
#[repr(C)]
struct SlopClosure {
    func: extern "C" fn() -> i64,
    env: *mut c_void,
}

extern "C" {
    fn std_strlib_min(a: i64, b: i64) -> i64;

    fn std_file_file_exists(path: SlopString) -> u8;
    fn std_file_file_size(path: SlopString) -> ResultInt;

    fn slopsys_arena_new(capacity: usize) -> *mut c_void;
    fn slopsys_arena_free(arena: *mut c_void);
    fn std_thread_chan_buffered(arena: *mut c_void, capacity: i64) -> *mut c_void;
    fn std_thread_send(ch: *mut c_void, value: i64) -> ResultVoid;
    fn std_thread_recv(ch: *mut c_void) -> ResultInt;
    fn std_thread_chan_close(ch: *mut c_void);
    fn std_thread_spawn(arena: *mut c_void, func: SlopClosure) -> *mut c_void;
    fn std_thread_join(thread: *mut c_void) -> i64;
}

/// The runtime passes the path's data to the C library as a C string
fn slop_str(nul_terminated: &'static [u8]) -> SlopString {
    SlopString {
        len: nul_terminated.len() - 1,
        data: nul_terminated.as_ptr().cast(),
    }
}

#[test]
fn links_and_calls_slop_std() {
    assert_eq!(unsafe { std_strlib_min(-7, 4) }, -7);
}

#[test]
fn file_exists_and_size_use_the_platform_crt() {
    let expected = std::fs::metadata("Cargo.toml").unwrap().len() as i64;
    unsafe {
        assert_ne!(std_file_file_exists(slop_str(b"Cargo.toml\0")), 0);
        assert_eq!(std_file_file_exists(slop_str(b"no-such-file.toml\0")), 0);
        let size = std_file_file_size(slop_str(b"Cargo.toml\0"));
        assert!(size.is_ok);
        assert_eq!(size.data, expected);
    }
}

extern "C" fn forty_two() -> i64 {
    42
}

#[test]
fn threads_and_channels_use_the_portable_runtime_api() {
    unsafe {
        let arena = slopsys_arena_new(4096);
        assert!(!arena.is_null());

        let ch = std_thread_chan_buffered(arena, 2);
        assert!(std_thread_send(ch, 7).is_ok);
        let got = std_thread_recv(ch);
        assert!(got.is_ok);
        assert_eq!(got.data, 7);
        std_thread_chan_close(ch);

        let closure = SlopClosure {
            func: forty_two,
            env: std::ptr::null_mut(),
        };
        let thread = std_thread_spawn(arena, closure);
        assert_eq!(std_thread_join(thread), 42);

        slopsys_arena_free(arena);
    }
}
