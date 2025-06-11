"""
Test the cat-file command
"""

# from standard library
import os
import shutil
import subprocess

# from local modules
from util import _global

SHA1_LIST = []

def __generate_obj_hash(file_path: str) -> str:
    """Generate the hash object use git hash-object -w <file_path>"""

    result = subprocess.run(["git", "hash-object", "-w", os.path.join(_global.ROOT_DIR, file_path)], 
                            capture_output=True, text=True, cwd=_global.TEST_DIR)
    
    return result.stdout.strip()

def __copy_objs() -> None:
    """Remove .gitlet/objs then copy the objs from .git/objects to .gitlet/objects"""

    # remove the .gitlet/objects
    if os.path.exists(os.path.join(_global.GITLET_DIR, "objects")):
        shutil.rmtree(os.path.join(_global.GITLET_DIR, "objects"))

    shutil.copytree(os.path.join(_global.GIT_DIR, "objects"), os.path.join(_global.GITLET_DIR, "objects"))
    assert os.listdir(os.path.join(_global.GITLET_DIR, "objects")) == os.listdir(os.path.join(_global.GIT_DIR, "objects"))

def _case_cat_file_no_flag() -> None:
    """Test the cat-file command with no flag"""

    result = subprocess.run([_global.PROGRAM_GITLET, "cat-file"], capture_output=True, text=True, cwd=_global.TEST_DIR)
    assert result.returncode == 0
    assert result.stdout != ""

def _case_cat_file_flag_t() -> None:
    """Test the cat-file command with the -t flag"""

    for sha1 in SHA1_LIST:
        result_map = _global.compare_output(["cat-file", "-t", sha1])
        assert result_map["gitlet_result"].returncode == result_map["git_result"].returncode
        assert result_map["gitlet_result"].stdout == result_map["git_result"].stdout


def _case_cat_file_flag_p() -> None:
    """Test the cat-file command with the -p flag"""

    for sha1 in SHA1_LIST:
        result_map = _global.compare_output(["cat-file", "-p", sha1])
        assert result_map["gitlet_result"].returncode == result_map["git_result"].returncode
        assert result_map["gitlet_result"].stdout == result_map["git_result"].stdout


def _case_cat_file_flag_s() -> None:
    """Test the cat-file command with the -s flag"""

    for sha1 in SHA1_LIST:
        result_map = _global.compare_output(["cat-file", "-s", sha1])
        assert result_map["gitlet_result"].returncode == result_map["git_result"].returncode
        assert result_map["gitlet_result"].stdout == result_map["git_result"].stdout

def _case_cat_file_flag_e() -> None:
    """Test the cat-file command with the -e flag"""

    for sha1 in SHA1_LIST:
        result_map = _global.compare_output(["cat-file", "-e", sha1])
        assert result_map["gitlet_result"].returncode == result_map["git_result"].returncode
        assert result_map["gitlet_result"].stdout == result_map["git_result"].stdout


def test_cmd_cat_file():
    """
    Test the cat-file command
    """

    _global.global_setup(True)

    _case_cat_file_no_flag()

    # generate the sha1 list of the test files
    SHA1_LIST.append(__generate_obj_hash("tests/cmd/test_cmd_cat-file.py"))
    SHA1_LIST.append(__generate_obj_hash("tests/cmd/test_cmd_init.py"))
    SHA1_LIST.append(__generate_obj_hash("tests/cmd/__init__.py"))
    SHA1_LIST.append(__generate_obj_hash("tests/util/test_util_files.py"))
    SHA1_LIST.append(__generate_obj_hash("tests/util/test_util_str.py"))
    SHA1_LIST.append(__generate_obj_hash("tests/util/__init__.py"))

    # move the objs to .gitlet/objects
    __copy_objs()

    # test the cat-file command with the -t flag
    _case_cat_file_flag_t()

    # test the cat-file command with the -p flag
    _case_cat_file_flag_p()

    # test the cat-file command with the -s flag
    _case_cat_file_flag_s()

    # test the cat-file command with the -e flag
    _case_cat_file_flag_e()

    _global.global_teardown()