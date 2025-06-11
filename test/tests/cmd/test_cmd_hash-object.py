"""Test the hash-object command"""

# from standard library
import os
import shutil
import subprocess

# from local modules
from util import _global

def _case_hash_object_no_flag() -> None:
    """Test the hash-object command with no flag"""
    _global.compare_output(["hash-object"])

def _case_hash_object_flag_file() -> None:
    """Test the hash-object command with a file"""

    _global.compare_output(["hash-object", __file__])
    _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "util", "test_util_files.py")])
    _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "util", "test_util_str.py")])
    _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "util", "__init__.py")])
    _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "cmd", "test_cmd_hash-object.py")])
    _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "cmd", "test_cmd_cat-file.py")])
    _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "cmd", "test_cmd_init.py")])
    _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "tests", "cmd", "__init__.py")])
    _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "util", "__init__.py")])
    _global.compare_output(["hash-object", os.path.join(_global.ROOT_DIR, "util", "_global.py")])

def _case_hash_object_flag_w() -> None:
    """Test the hash-object command with the -w flag"""
    _global.compare_output(["hash-object", "-w", __file__])
    

def test_cmd_hash_object():
    """Test the hash-object command"""
    _global.global_setup(True)

    _case_hash_object_no_flag()
    _case_hash_object_flag_file()
    _case_hash_object_flag_w()

    _global.global_teardown()