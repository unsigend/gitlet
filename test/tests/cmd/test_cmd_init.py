"""
Test the init command
"""

# from standard library
import os
import shutil
import subprocess

# from local modules
from util import _global

def _case_init_no_flag() -> None:
    """Test the init command with no flag"""

    result = subprocess.run(["gitlet", "init"], capture_output=True, text=True, cwd=_global.TEST_DIR)
    assert result.returncode == 0

    assert os.path.exists(_global.GITLET_DIR) and os.path.isdir(_global.GITLET_DIR)

    assert os.path.isdir(os.path.join(_global.GITLET_DIR, "objects"))

    assert os.path.isdir(os.path.join(_global.GITLET_DIR, "refs"))
    assert os.path.isdir(os.path.join(_global.GITLET_DIR, "refs", "heads"))
    assert os.path.isdir(os.path.join(_global.GITLET_DIR, "refs", "tags"))

    assert os.path.isfile(os.path.join(_global.GITLET_DIR, "HEAD"))
    with open(os.path.join(_global.GITLET_DIR, "HEAD"), "r") as f:
        assert f.read() == "ref: refs/heads/master\n"

    assert os.path.isfile(os.path.join(_global.GITLET_DIR, "config"))

    assert os.path.isfile(os.path.join(_global.GITLET_DIR, "description"))
    with open(os.path.join(_global.GITLET_DIR, "description"), "r") as f:
        assert f.read() == "Unnamed repository; edit this file 'description' to name the repository.\n"

    shutil.rmtree(_global.GITLET_DIR)

def _case_init_flag_dir() -> None:
    """Test the init command with the dir flag"""

    result = subprocess.run(["gitlet", "init", "test_dir"], capture_output=True, text=True, cwd=_global.TEST_DIR)
    assert result.returncode == 0

    assert os.path.exists(os.path.join(_global.TEST_DIR, "test_dir")) 
    assert os.path.isdir(os.path.join(_global.TEST_DIR, "test_dir"))
    assert os.path.exists(os.path.join(_global.TEST_DIR, "test_dir", ".gitlet")) 
    assert os.path.isdir(os.path.join(_global.TEST_DIR, "test_dir", ".gitlet"))

    shutil.rmtree(os.path.join(_global.TEST_DIR, "test_dir"))


def test_cmd_init():
    """
    Test the init command
    """
    _global.global_setup(False)

    _case_init_no_flag()
    _case_init_flag_dir()

    _global.global_teardown()
    