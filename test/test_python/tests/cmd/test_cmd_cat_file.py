"""Test the cat-file command in gitlet"""

import os
import subprocess
from util import _global

def test_command_cat_file() -> None:
    _global.global_setup()

    # generate the SHA1 of the file
    result_git = subprocess.run([_global.GIT, "hash-object", "-w", __file__],
                                 cwd=_global.TEMP_DIR, capture_output=True)
    assert result_git.returncode == 0
    assert len(result_git.stdout) == 41

    SHA1 = result_git.stdout.decode("utf-8")[:40]

    # check if the file is the same as the original file
    result_git = subprocess.run([_global.GIT, "cat-file", "-p", SHA1],
                                 cwd=_global.TEMP_DIR, capture_output=True)
    assert result_git.returncode == 0
    assert result_git.stdout.decode("utf-8") == open(__file__).read()

    # copy the objects directory to the gitlet directory
    os.system(f"cp -r {_global.GIT_DIR}/objects/ {_global.GITLET_DIR}/objects/")

    result_gitlet = subprocess.run([_global.GITLET, "cat-file", SHA1],
                                 cwd=_global.TEMP_DIR, capture_output=True)
    assert result_gitlet.returncode == 0


    _global.global_teardown()