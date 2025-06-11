"""Test the hash-object command"""

# from standard library
import os
import shutil
import subprocess

# from local modules
from util import _global

def __compare_using_cat_file(SHA1: str) -> None:
    """Compare the output of the commands using cat-file"""
    assert len(SHA1) == 40
    
    result = _global.compare_output(["cat-file", "-p", SHA1])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

    result = _global.compare_output(["cat-file", "-t", SHA1])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

    result = _global.compare_output(["cat-file", "-s", SHA1])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

    result = _global.compare_output(["cat-file", "-e", SHA1])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

def _case_hash_object_no_flag() -> None:
    """Test the hash-object command with no flag"""

    result = _global.compare_output(["hash-object"])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

def _case_hash_object_flag_file() -> None:
    """Test the hash-object command with a file"""

    result = _global.compare_output(["hash-object", __file__])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

    result = _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "util", "test_util_files.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

    result = _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "util", "test_util_str.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

    result = _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "util", "__init__.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

    result = _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "cmd", "test_cmd_hash-object.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

    result = _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "cmd", "test_cmd_cat-file.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

    result = _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "cmd", "test_cmd_init.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

    result = _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "util", "__init__.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout
    
    result = _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "util", "_global.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout

def _case_hash_object_flag_w() -> None:
    """Test the hash-object command with the -w flag"""
    result = _global.compare_output(["hash-object", "-w", __file__])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout
    __compare_using_cat_file(result["gitlet_result"].stdout[:40])

    result = _global.compare_output(["hash-object", "-w", os.path.join(_global.ROOT_DIR, "tests", "util", "test_util_files.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout
    __compare_using_cat_file(result["gitlet_result"].stdout[:40])

    result = _global.compare_output(["hash-object", "-w", os.path.join(_global.ROOT_DIR, "tests", "util", "test_util_str.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout
    __compare_using_cat_file(result["gitlet_result"].stdout[:40])

    result = _global.compare_output(["hash-object", "-w", os.path.join(_global.ROOT_DIR, "tests", "util", "__init__.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout
    __compare_using_cat_file(result["gitlet_result"].stdout[:40])

    result = _global.compare_output(["hash-object", "-w", os.path.join(_global.ROOT_DIR, "tests", "cmd", "test_cmd_cat-file.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout
    __compare_using_cat_file(result["gitlet_result"].stdout[:40])

    result = _global.compare_output(["hash-object", "-w", os.path.join(_global.ROOT_DIR, "tests", "cmd", "test_cmd_init.py")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout
    __compare_using_cat_file(result["gitlet_result"].stdout[:40])

    # Test for small file
    with open(os.path.join(_global.TEST_DIR, "small_file.txt"), "w") as f:
        f.write("Hello, world!")

    result = _global.compare_output(["hash-object", "-w", os.path.join(_global.TEST_DIR, "small_file.txt")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout
    __compare_using_cat_file(result["gitlet_result"].stdout[:40])

    # Test for large file
    with open(os.path.join(_global.TEST_DIR, "large_file.txt"), "w") as f:
        f.write("Hello, world!" * 1000000)

    result = _global.compare_output(["hash-object", "-w", os.path.join(_global.TEST_DIR, "large_file.txt")])
    assert result["gitlet_result"].returncode == result["git_result"].returncode
    assert result["gitlet_result"].stdout == result["git_result"].stdout
    __compare_using_cat_file(result["gitlet_result"].stdout[:40])



def test_cmd_hash_object():
    """Test the hash-object command"""
    _global.global_setup(True)

    _case_hash_object_no_flag()
    _case_hash_object_flag_file()
    _case_hash_object_flag_w()

    _global.global_teardown()