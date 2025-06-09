"""Global Utility for Test gitlet"""

import os
import subprocess
import shutil
import ctypes
import sys

GIT    = "git"
GITLET = "gitlet"

WORKING_DIR = os.getcwd() + "/test_python/tests"
TEMP_DIR    = WORKING_DIR + "/temp"
GIT_DIR     = TEMP_DIR + "/" + ".git"
GITLET_DIR  = TEMP_DIR + "/" + ".gitlet"

"""Setup the global gitlet test environment"""
def global_setup():
    if not os.path.exists(TEMP_DIR):
        os.mkdir(TEMP_DIR)
    assert os.path.exists(TEMP_DIR)

    if not os.path.exists(GIT_DIR):
        result_git = subprocess.run([GIT, "init", TEMP_DIR], cwd=WORKING_DIR, capture_output=True)
        assert result_git.returncode == 0
    assert os.path.exists(GIT_DIR)

    if not os.path.exists(GITLET_DIR):
        result_gitlet = subprocess.run([GITLET, "init", TEMP_DIR], cwd=WORKING_DIR, capture_output=True)
        assert result_gitlet.returncode == 0
    assert os.path.exists(GITLET_DIR)


"""Tear Down the global gitlet test environment"""
def global_teardown():
    if os.path.exists(TEMP_DIR):
        shutil.rmtree(TEMP_DIR)
    assert not os.path.exists(TEMP_DIR)

"""Get the c library for the gitlet test"""
def get_c_lib() -> ctypes.CDLL:
    lib_path = "../lib/"
    assert os.path.exists(lib_path)

    # check if the os is macos
    if sys.platform == "darwin":
        lib_path += "libgitlet.dylib"
    else:
        lib_path += "libgitlet.so"

    return ctypes.CDLL(lib_path)