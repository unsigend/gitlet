"""
Test case name: test_cmd_path
Test case description:
    Test the path of the command "gitlet init"
    Test the path of the command "gitlet init" with the option "--help"
    Test the path of the command "gitlet init" with the option "-h"
    Test the path of the command "gitlet init" with the option "--help" and the path
    Test the path of the command "gitlet init" with the option "-h" and the path
"""

import os
import subprocess
import pytest

PROGRAM_NAME = "gitlet"
TEST_DIR = "temp_dir"

def test_cmd_path() -> None:
    """
    Test the path of the command "gitlet init"
    """

    # before run the command "gitlet init"
    assert not os.path.exists(TEST_DIR)
    assert not os.path.exists(f"{TEST_DIR}/.gitlet")

    # run the command "gitlet init" with subprocess
    result = subprocess.run([PROGRAM_NAME, "init", TEST_DIR],
                            capture_output=True, text=True, check=False)
    assert result.returncode == 0

    # check the path of the command "gitlet init"
    assert os.path.exists(TEST_DIR)
    assert os.path.exists(f"{TEST_DIR}/.gitlet")

    # Make sure all directory and file are created
    assert os.path.exists(f"{TEST_DIR}/.gitlet/objects")
    assert os.path.exists(f"{TEST_DIR}/.gitlet/refs")
    assert os.path.exists(f"{TEST_DIR}/.gitlet/refs/heads")
    assert os.path.exists(f"{TEST_DIR}/.gitlet/refs/tags")
    assert os.path.exists(f"{TEST_DIR}/.gitlet/HEAD")
    assert os.path.exists(f"{TEST_DIR}/.gitlet/config")

    # remove the test directory
    os.system(f"rm -rf {TEST_DIR}")
    assert not os.path.exists(TEST_DIR)
    assert not os.path.exists(f"{TEST_DIR}/.gitlet")

    # run the command "gitlet init" with subprocess
    # if using the option "--help" or "-h", the init command will not be executed
    result = subprocess.run([PROGRAM_NAME, "init", "--help", TEST_DIR],
                            capture_output=True, text=True, check=False)
    assert result.returncode == 0

    assert not os.path.exists(TEST_DIR)
    assert not os.path.exists(f"{TEST_DIR}/.gitlet")

    result = subprocess.run([PROGRAM_NAME, "init", "-h", TEST_DIR],
                            capture_output=True, text=True, check=False)
    assert result.returncode == 0

    assert not os.path.exists(TEST_DIR)
    assert not os.path.exists(f"{TEST_DIR}/.gitlet")

    # Test non-exist option will terminate the init process
    result = subprocess.run([PROGRAM_NAME, "init", "--non-exist-option", TEST_DIR],
                            capture_output=True, text=True, check=False)
    assert result.returncode != 0

    assert not os.path.exists(TEST_DIR)
    assert not os.path.exists(f"{TEST_DIR}/.gitlet")

if __name__ == "__main__":
    pytest.main()