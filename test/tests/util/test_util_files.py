"""Test Suite for util/files.c module"""

# from standard library
import os
import shutil

# from local modules
from util import _global
from util._global import gitlet_lib


def _case_exists() -> None:
    """Test the exists function"""
    with open(os.path.join(_global.TEST_DIR, "test.txt"), "w") as f:
        f.write("test")
    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test.txt").encode())
    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test2.txt").encode())
    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test3.txt").encode())
    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test4.txt").encode())
    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test5.txt").encode())
    
    if not os.path.exists(os.path.join(_global.TEST_DIR, "test_dir")):
        os.mkdir(os.path.join(_global.TEST_DIR, "test_dir"))
    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test_dir").encode())
    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test_dir2").encode())
    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test_dir3").encode())
    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test_dir4").encode())
    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test_dir5").encode())
    

    assert gitlet_lib.exists(b".")
    assert gitlet_lib.exists(b"..")
    assert not gitlet_lib.exists(b"")
    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, _global.GITLET_DIR).encode())
    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, _global.GIT_DIR).encode())

    shutil.rmtree(os.path.join(_global.TEST_DIR, "test_dir"))

def _case_create_directory() -> None:
    """Test the create_directory function"""
    assert gitlet_lib.create_directory(os.path.join(_global.TEST_DIR, "test_dir").encode())
    assert gitlet_lib.create_directory(os.path.join(_global.TEST_DIR, "another_dir").encode())

    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test_dir").encode())
    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, "another_dir").encode())

    assert gitlet_lib.exists(b".")
    assert gitlet_lib.exists(b"..")
    assert not gitlet_lib.exists(b"")
    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, _global.GITLET_DIR).encode())
    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, _global.GIT_DIR).encode())

    shutil.rmtree(os.path.join(_global.TEST_DIR, "test_dir"))
    shutil.rmtree(os.path.join(_global.TEST_DIR, "another_dir"))


def _case_create_file() -> None:
    """Test the create_file function"""

    assert gitlet_lib.create_file(os.path.join(_global.TEST_DIR, "test.txt").encode())
    assert gitlet_lib.create_file(os.path.join(_global.TEST_DIR, "another.txt").encode())

    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test.txt").encode())
    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, "another.txt").encode())

    os.remove(os.path.join(_global.TEST_DIR, "test.txt"))
    os.remove(os.path.join(_global.TEST_DIR, "another.txt"))


def _case_remove_directory() -> None:
    """Test the remove_directory function"""

    assert gitlet_lib.create_directory(os.path.join(_global.TEST_DIR, "test_dir").encode())
    assert gitlet_lib.create_directory(os.path.join(_global.TEST_DIR, "another_dir").encode())

    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test_dir").encode())
    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, "another_dir").encode())

    assert gitlet_lib.remove_directory(os.path.join(_global.TEST_DIR, "test_dir").encode())
    assert gitlet_lib.remove_directory(os.path.join(_global.TEST_DIR, "another_dir").encode())

    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test_dir").encode())
    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "another_dir").encode())


def _case_remove_file() -> None:
    """Test the remove_file function"""

    assert gitlet_lib.create_file(os.path.join(_global.TEST_DIR, "test.txt").encode())
    assert gitlet_lib.create_file(os.path.join(_global.TEST_DIR, "another.txt").encode())

    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test.txt").encode())
    assert gitlet_lib.exists(os.path.join(_global.TEST_DIR, "another.txt").encode())

    assert gitlet_lib.remove_file(os.path.join(_global.TEST_DIR, "test.txt").encode())
    assert gitlet_lib.remove_file(os.path.join(_global.TEST_DIR, "another.txt").encode())

    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test.txt").encode())
    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "another.txt").encode())


def _case_is_directory() -> None:
    """Test the is_directory function"""

    assert gitlet_lib.create_directory(os.path.join(_global.TEST_DIR, "test_dir").encode())
    assert gitlet_lib.create_directory(os.path.join(_global.TEST_DIR, "another_dir").encode())

    assert gitlet_lib.is_directory(os.path.join(_global.TEST_DIR, "test_dir").encode())
    assert gitlet_lib.is_directory(os.path.join(_global.TEST_DIR, "another_dir").encode())

    assert gitlet_lib.is_directory(os.path.join(_global.TEST_DIR, _global.GITLET_DIR).encode())
    assert gitlet_lib.is_directory(os.path.join(_global.TEST_DIR, _global.GIT_DIR).encode())

    assert not gitlet_lib.is_directory(os.path.join(_global.TEST_DIR, "test.txt").encode())
    assert not gitlet_lib.is_directory(os.path.join(_global.TEST_DIR, "another.txt").encode())

    assert gitlet_lib.remove_directory(os.path.join(_global.TEST_DIR, "test_dir").encode())
    assert gitlet_lib.remove_directory(os.path.join(_global.TEST_DIR, "another_dir").encode())

    assert not gitlet_lib.is_directory(os.path.join(_global.TEST_DIR, "test_dir").encode())
    assert not gitlet_lib.is_directory(os.path.join(_global.TEST_DIR, "another_dir").encode())

    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "test_dir").encode())
    assert not gitlet_lib.exists(os.path.join(_global.TEST_DIR, "another_dir").encode())


def test_util_files():
    """Run all file utility tests"""
    _global.global_setup(True)

    _case_exists()
    _case_create_directory()
    _case_create_file()
    _case_remove_directory()
    _case_remove_file()
    _case_is_directory()

    _global.global_teardown()