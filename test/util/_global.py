"""Global utility functions for testing gitlet"""

import os
import subprocess
import shutil
import sys
import ctypes

ROOT_DIR = os.getcwd()
TEST_DIR = os.path.join(ROOT_DIR, "temp")

PROGRAM_GITLET   = "gitlet"
PROGRAM_GIT      = "git"

GITLET_DIR = os.path.join(TEST_DIR, ".gitlet")
GIT_DIR    = os.path.join(TEST_DIR, ".git")


def global_setup(init_repo: bool = False) -> None:
    """Initialize the test environment and init git and gitlet repository"""
    if not os.path.exists(TEST_DIR):
        os.makedirs(TEST_DIR)

    if init_repo:
        if not os.path.exists(GITLET_DIR):
            assert subprocess.run([PROGRAM_GITLET, "init"], cwd=TEST_DIR).returncode == 0
        if not os.path.exists(GIT_DIR):
            assert subprocess.run([PROGRAM_GIT, "init"], cwd=TEST_DIR).returncode == 0

def global_teardown() -> None:
    """Teardown the test environment"""
    if os.path.exists(TEST_DIR):
        shutil.rmtree(TEST_DIR)

def get_shared_lib() -> ctypes.CDLL:
    """Get the shared library of gitlet"""
    lib_name = ""
    if sys.platform == "darwin":
        lib_name = "libgitlet.dylib"
    elif sys.platform == "linux":
        lib_name = "libgitlet.so"
    else:
        raise ValueError(f"Unsupported platform: {sys.platform}")
    return ctypes.CDLL(f"../lib/{lib_name}")


def compare_output(commands: list[str], _capture_output: bool = True) -> dict[str, subprocess.CompletedProcess[str]]:
    """Compare the output of the commands based on the test directory"""
    _gitlet_commands = [PROGRAM_GITLET] + commands
    _git_commands = [PROGRAM_GIT] + commands

    _gitlet_output = subprocess.run(_gitlet_commands, cwd=TEST_DIR, capture_output=_capture_output, text=True)
    _git_output = subprocess.run(_git_commands, cwd=TEST_DIR, capture_output=_capture_output, text=True)

    return {
        "gitlet_result": _gitlet_output,
        "git_result": _git_output,
    }

gitlet_lib = get_shared_lib()