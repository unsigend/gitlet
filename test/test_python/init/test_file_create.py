"""
Test case name: test_file_create
Test case description:
    Test the file creation after execute the command "gitlet init"
"""

import os
import pytest

PROGRAM_NAME = "gitlet"


def test_file_create() -> None:
    """
    Test the file creation after execute the command "gitlet init"
    """
    result = os.system(f"{PROGRAM_NAME} --help")
    if (result != 0):
        raise RuntimeError("Missing gitlet program, try to run 'make export-env' to export the program to the PATH variable")


if __name__ == "__main__":
    pytest.main()
