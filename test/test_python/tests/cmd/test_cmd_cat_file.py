"""Test the cat-file command in gitlet"""

import os
import subprocess
from util import _global

"""
    Generate the SHA1 object of the file to both git and gitlet repository
"""
def _generate_object(file_path: str) -> str:
    # generate the SHA1 object of the file
    result_git = subprocess.run([_global.GIT, "hash-object", "-w", _global.WORKING_DIR + file_path],
                                 cwd=_global.TEMP_DIR, capture_output=True)
    assert result_git.returncode == 0
    assert len(result_git.stdout) == 41

    # copy the objects directory to the gitlet directory
    os.system(f"cp -rf {_global.GIT_DIR}/objects/* {_global.GITLET_DIR}/objects/")

    return result_git.stdout.decode("utf-8")[:40]

"""
    Test the -p flag
    Test the output and difference between git and gitlet
"""
def _flag_p_case(file_path: str) -> None:
    SHA1 = _generate_object(file_path)

    # check if the file is the same as the original file
    result_git = subprocess.run([_global.GIT, "cat-file", "-p", SHA1],
                                 cwd=_global.TEMP_DIR, capture_output=True)
    result_gitlet = subprocess.run([_global.GITLET, "cat-file", "-p", SHA1],
                                 cwd=_global.TEMP_DIR, capture_output=True)

    assert result_git.returncode == result_gitlet.returncode
    assert result_git.stdout.decode("utf-8") == result_gitlet.stdout.decode("utf-8")

"""
    Test the -s flag
    Test the output and difference between git and gitlet
"""
def _flag_s_case(file_path: str) -> None:
    SHA1 = _generate_object(file_path)

    result_git = subprocess.run([_global.GIT, "cat-file", "-s", SHA1],
                                 cwd=_global.TEMP_DIR, capture_output=True)
    result_gitlet = subprocess.run([_global.GITLET, "cat-file", "-s", SHA1],
                                 cwd=_global.TEMP_DIR, capture_output=True)

    assert result_git.returncode == result_gitlet.returncode
    assert result_git.stdout.decode("utf-8") == result_gitlet.stdout.decode("utf-8")

"""
    Test the -t flag
    Test the output and difference between git and gitlet
"""
def _flag_t_case(file_path: str) -> None:
    SHA1 = _generate_object(file_path)

    result_git = subprocess.run([_global.GIT, "cat-file", "-t", SHA1],
                                 cwd=_global.TEMP_DIR, capture_output=True)
    result_gitlet = subprocess.run([_global.GITLET, "cat-file", "-t", SHA1],
                                 cwd=_global.TEMP_DIR, capture_output=True)

    assert result_git.returncode == result_gitlet.returncode
    assert result_git.stdout.decode("utf-8") == result_gitlet.stdout.decode("utf-8")

"""
    Test the -e flag
    Test the output and difference between git and gitlet
"""
def _flag_e_case(file_path: str) -> None:
    result_git = subprocess.run([_global.GIT, "hash-object", _global.WORKING_DIR + file_path],
                                 cwd=_global.TEMP_DIR, capture_output=True)
    assert result_git.returncode == 0
    sha1 = result_git.stdout.decode("utf-8")[:40]

    result_git = subprocess.run([_global.GIT, "cat-file", "-e", sha1],
                                 cwd=_global.TEMP_DIR, capture_output=True)
    result_gitlet = subprocess.run([_global.GITLET, "cat-file", "-e", sha1],
                                 cwd=_global.TEMP_DIR, capture_output=True)

    assert result_git.returncode == result_gitlet.returncode


def test_command_cat_file() -> None:
    _global.global_setup()

    result_gitlet = subprocess.run([_global.GITLET, "cat-file", "-h"],
                                 cwd=_global.TEMP_DIR, capture_output=True)
    assert result_gitlet.returncode == 0

    # Check the -t flag
    _flag_t_case("/cmd/test_cmd_init.py")
    _flag_t_case("/cmd/test_cmd_cat_file.py")
    _flag_t_case("/cmd/__init__.py")
    _flag_t_case("/cmd/test_cmd_hash_object.py")
    _flag_t_case("/__init__.py")

    # Check the -p flag
    _flag_p_case("/cmd/test_cmd_init.py")
    _flag_p_case("/cmd/test_cmd_cat_file.py")
    _flag_p_case("/cmd/__init__.py")
    _flag_p_case("/cmd/test_cmd_hash_object.py")
    _flag_p_case("/__init__.py")

    # Check the -s flag
    _flag_s_case("/cmd/test_cmd_init.py")
    _flag_s_case("/cmd/test_cmd_cat_file.py")
    _flag_s_case("/cmd/__init__.py")
    _flag_s_case("/cmd/test_cmd_hash_object.py")
    _flag_s_case("/__init__.py")

    # Check the -e flag
    _flag_e_case("/cmd/test_cmd_init.py")
    _flag_e_case("/cmd/test_cmd_cat_file.py")
    _flag_e_case("/cmd/__init__.py")
    _flag_e_case("/cmd/test_cmd_hash_object.py")
    _flag_e_case("/__init__.py")
                                

    _global.global_teardown()