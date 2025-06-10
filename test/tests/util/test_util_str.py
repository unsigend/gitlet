"""Test Suite for util/str.c module"""

# from standard library
import os
import hashlib
import ctypes

# from local modules
from util import _global
from util._global import gitlet_lib


def _case_str_start_with() -> None:
    """Test the str_start_with function"""

    assert gitlet_lib.str_start_with(b"hello", b"he") == str("hello").startswith("he")
    assert gitlet_lib.str_start_with(b"hello", b"") == str("hello").startswith("")
    assert gitlet_lib.str_start_with(b"hello", b"world") == str("hello").startswith("world")
    assert gitlet_lib.str_start_with(b"hello", b"") == str("hello").startswith("")
    assert gitlet_lib.str_start_with(b"", b"") == str("").startswith("")
    assert gitlet_lib.str_start_with(b"", b"hello") == str("").startswith("hello")
    assert gitlet_lib.str_start_with(b"hello", b"hello") == str("hello").startswith("hello")
    assert gitlet_lib.str_start_with(b"hello", b"hello world") == str("hello").startswith("hello world")
    assert gitlet_lib.str_start_with(b"hello", b"hello world") == str("hello").startswith("hello world")
    
def _case_str_end_with() -> None:
    """Test the str_end_with function"""

    assert gitlet_lib.str_end_with(b"hello", b"lo") == str("hello").endswith("lo")
    assert gitlet_lib.str_end_with(b"hello", b"") == str("hello").endswith("")
    assert gitlet_lib.str_end_with(b"hello", b"world") == str("hello").endswith("world")
    assert gitlet_lib.str_end_with(b"hello", b"") == str("hello").endswith("")
    assert gitlet_lib.str_end_with(b"", b"") == str("").endswith("")
    assert gitlet_lib.str_end_with(b"", b"hello") == str("").endswith("hello")
    assert gitlet_lib.str_end_with(b"hello", b"hello") == str("hello").endswith("hello")
    assert gitlet_lib.str_end_with(b"hello", b"hello world") == str("hello").endswith("hello world")
    assert gitlet_lib.str_end_with(b"hello", b"hello world") == str("hello").endswith("hello world")


def _case_str_contains() -> None:
    """Test the str_contains function"""

    assert gitlet_lib.str_contains(b"hello", b"he") == ("he" in "hello")
    assert gitlet_lib.str_contains(b"hello", b"") == ("" in "hello")
    assert gitlet_lib.str_contains(b"hello", b"world") == ("world" in "hello")
    assert gitlet_lib.str_contains(b"hello", b"") == ("" in "hello")
    assert gitlet_lib.str_contains(b"", b"") == ("" in "")
    assert gitlet_lib.str_contains(b"", b"hello") == ("hello" in "")
    assert gitlet_lib.str_contains(b"hello", b"hello") == ("hello" in "hello")
    assert gitlet_lib.str_contains(b"hello", b"hello world") == ("hello world" in "hello")


def _case_str_equals() -> None:
    """Test the str_equals function"""

    assert gitlet_lib.str_equals(b"hello", b"hello") == (str("hello") == str("hello"))
    assert gitlet_lib.str_equals(b"hello", b"world") == (str("hello") == str("world"))
    assert gitlet_lib.str_equals(b"hello", b"") == (str("hello") == str(""))
    assert gitlet_lib.str_equals(b"", b"") == (str("") == str(""))
    assert gitlet_lib.str_equals(b"", b"hello") == (str("") == str("hello"))
    assert gitlet_lib.str_equals(b"hello", b"hello") == (str("hello") == str("hello"))
    assert gitlet_lib.str_equals(b"hello", b"hello world") == (str("hello") == str("hello world"))
    assert gitlet_lib.str_equals(b"hello", b"hello world") == (str("hello") == str("hello world"))

def _case_str_hash_sha1() -> None:
    """Test the str_hash_sha1 function"""
    buffer = ctypes.create_string_buffer(40)

    gitlet_lib.str_hash_sha1(buffer, b"hello")
    assert buffer.value == hashlib.sha1(b"hello").hexdigest().encode()

    gitlet_lib.str_hash_sha1(buffer, b"world")
    assert buffer.value == hashlib.sha1(b"world").hexdigest().encode()

    gitlet_lib.str_hash_sha1(buffer, b"")
    assert buffer.value == hashlib.sha1(b"").hexdigest().encode()

    gitlet_lib.str_hash_sha1(buffer, b"hello world")
    assert buffer.value == hashlib.sha1(b"hello world").hexdigest().encode()

    with open(__file__, "rb") as f:
        content = f.read()
        gitlet_lib.str_hash_sha1(buffer, content)
        assert buffer.value == hashlib.sha1(content).hexdigest().encode()

    with open(os.path.join(_global.ROOT_DIR, "tests", "util", "test_util_files.py"), "rb") as f:
        content = f.read()
        gitlet_lib.str_hash_sha1(buffer, content)
        assert buffer.value == hashlib.sha1(content).hexdigest().encode()

    with open(os.path.join(_global.ROOT_DIR, "tests", "util", "__init__.py"), "rb") as f:
        content = f.read()
        gitlet_lib.str_hash_sha1(buffer, content)
        assert buffer.value == hashlib.sha1(content).hexdigest().encode()

def _case_str_hash_sha1_n() -> None:
    """Test the str_hash_sha1_n function"""

    buffer = ctypes.create_string_buffer(40)

    gitlet_lib.str_hash_sha1_n(buffer, b"hello", 5)
    assert buffer.value == hashlib.sha1(b"hello").hexdigest().encode()

    gitlet_lib.str_hash_sha1_n(buffer, b"world", 5)
    assert buffer.value == hashlib.sha1(b"world").hexdigest().encode()

    gitlet_lib.str_hash_sha1_n(buffer, b"", 0)
    assert buffer.value == hashlib.sha1(b"").hexdigest().encode()


def test_util_str():
    """Run all string utility tests"""
    _case_str_start_with()
    _case_str_end_with()
    _case_str_contains()
    _case_str_equals()
    _case_str_hash_sha1()
    _case_str_hash_sha1_n()
