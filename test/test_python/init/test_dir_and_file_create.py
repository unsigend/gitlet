"""
Test case name: test_dir_and_file_create
Test case description:
    Test the directory and file creation after execute the command "gitlet init"

    Expected result: After execute the command "gitlet init" 
        - the directory ".gitlet" will be created.
        - the subdirectory ".gitlet/objects" will be created.
        - the subdirectory ".gitlet/refs" will be created.
        - the subdirectory ".gitlet/refs/heads" will be created.
        - the subdirectory ".gitlet/refs/tags" will be created.
        - the file ".gitlet/HEAD" will be created.
        - the file ".gitlet/config" will be created.
        - the file ".gitlet/description" will be created.
"""

import os
import subprocess
import pytest

PROGRAM_NAME = "gitlet"


def test_dir_and_file_create() -> None:
    """
    Test the directory and file creation after execute the command "gitlet init"
    """

    # before run the command "gitlet init"
    # check the .gitlet directory is not exist
    if os.path.exists(".gitlet"):
        os.system("rm -rf .gitlet")
        assert not os.path.exists(".gitlet")

    # run the command "gitlet init" with subprocess
    result = subprocess.run([PROGRAM_NAME, "init"], capture_output=True, text=True, check=False)
    assert result.returncode == 0
    assert result.stdout == f"Initialized empty Gitlet repository in {os.getcwd()}/.gitlet/\n"
    # Make sure the .gitlet directory is created after the command "gitlet init"
    assert os.path.exists(".gitlet")
    # check the .gitlet directory is a directory
    assert os.path.isdir(".gitlet")

    assert os.path.exists(".gitlet/objects") and os.path.isdir(".gitlet/objects")
    assert os.path.exists(".gitlet/refs") and os.path.isdir(".gitlet/refs")
    assert os.path.exists(".gitlet/refs/heads") and os.path.isdir(".gitlet/refs/heads")
    assert os.path.exists(".gitlet/refs/tags") and os.path.isdir(".gitlet/refs/tags")

    assert os.path.exists(".gitlet/HEAD") and os.path.isfile(".gitlet/HEAD")
    assert os.path.exists(".gitlet/config") and os.path.isfile(".gitlet/config")
    assert os.path.exists(".gitlet/description") and os.path.isfile(".gitlet/description")

    # Make sure the .gitlet directory will be deleted before finish the test case
    # delete the .gitlet directory
    os.system("rm -rf .gitlet")
    assert not os.path.exists(".gitlet")

if __name__ == "__main__":
    pytest.main()
