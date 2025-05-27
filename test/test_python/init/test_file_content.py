"""
Test case name: test_file_content
Test case description:
    Test the content of the file after execute the command "gitlet init"

    Expected result: After execute the command "gitlet init" 
        - the file ".gitlet/HEAD" will be created. 
            And the content of the file is "ref: refs/heads/master"
        - the file ".gitlet/description" will be created.
            And the content of the file is "Unnamed repository; edit this file 'description' to name the repository."
"""

import os
import subprocess
import pytest

PROGRAM_NAME = "gitlet"

def test_head_file_content() -> None:
    """
    Test the content of the file ".gitlet/HEAD"
    """

    # before run the command "gitlet init"
    # check the .gitlet directory is not exist
    if os.path.exists(".gitlet"):
        os.system("rm -rf .gitlet")
        assert not os.path.exists(".gitlet")

    # run the command "gitlet init" with subprocess
    result = subprocess.run([PROGRAM_NAME, "init"], capture_output=True, text=True, check=False)
    assert result.returncode == 0

    # check the content of the file ".gitlet/HEAD"
    with open(".gitlet/HEAD", "r", encoding="utf-8") as file:
        content = file.read()
        assert content == "ref: refs/heads/master\n"
        
def test_description_file_content() -> None:
    """
    Test the content of the file ".gitlet/description"
    """

    # before run the command "gitlet init"
    # check the .gitlet directory is not exist
    if os.path.exists(".gitlet"):
        os.system("rm -rf .gitlet")
        assert not os.path.exists(".gitlet")

    # run the command "gitlet init" with subprocess
    result = subprocess.run([PROGRAM_NAME, "init"], capture_output=True, text=True, check=False)
    assert result.returncode == 0

    # check the content of the file ".gitlet/description"
    with open(".gitlet/description", "r", encoding="utf-8") as file:
        content = file.read()
        assert content == "Unnamed repository; edit this file 'description' to name the repository.\n"


if __name__ == "__main__":
    pytest.main()