from util import _global
import ctypes
import hashlib

"""Test the str_hash_sha1 function from the util/str.h"""
def test_str_hash_sha1() -> None:
    c_lib = _global.get_c_lib()

    buffer = ctypes.create_string_buffer(40)
    c_lib.str_hash_sha1(buffer, b"hello")
    assert buffer.value.decode() == hashlib.sha1(b"hello").hexdigest()

    c_lib.str_hash_sha1(buffer, b"world")
    assert buffer.value.decode() == hashlib.sha1(b"world").hexdigest()

    c_lib.str_hash_sha1(buffer, b"hello world")
    assert buffer.value.decode() == hashlib.sha1(b"hello world").hexdigest()

    c_lib.str_hash_sha1(buffer, b"")
    
    assert buffer.value.decode() == hashlib.sha1(b"").hexdigest()

    c_lib.str_hash_sha1(buffer, b" ")
    assert buffer.value.decode() == hashlib.sha1(b" ").hexdigest()

    c_lib.str_hash_sha1(buffer, b"1234567890")
    assert buffer.value.decode() == hashlib.sha1(b"1234567890").hexdigest()

    c_lib.str_hash_sha1(buffer, b"./test/test_python/tests/util/test_util_str.py")
    assert buffer.value.decode() == hashlib.sha1(b"./test/test_python/tests/util/test_util_str.py").hexdigest()

    c_lib.str_hash_sha1(buffer, b"../test/test_python/tests/util/test_util_str.py")
    assert buffer.value.decode() == hashlib.sha1(b"../test/test_python/tests/util/test_util_str.py").hexdigest()

    c_lib.str_hash_sha1(buffer, b"../test/test_python/tests/util/test_util_str.py")
    assert buffer.value.decode() == hashlib.sha1(b"../test/test_python/tests/util/test_util_str.py").hexdigest()
    
    