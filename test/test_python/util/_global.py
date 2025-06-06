"""Global Utility for Test gitlet"""

import os
import subprocess
import shutil

GIT    = "git"
GITLET = "gitlet"

WORKING_DIR = os.getcwd() + "/test_python/tests"
TEMP_DIR    = WORKING_DIR + "/temp"
GIT_DIR     = TEMP_DIR + "/" + ".git"
GITLET_DIR  = TEMP_DIR + "/" + ".gitlet"

def global_setup():
    if not os.path.exists(TEMP_DIR):
        os.mkdir(TEMP_DIR)
    assert os.path.exists(TEMP_DIR)

    if not os.path.exists(GIT_DIR):
        result_git = subprocess.run([GIT, "init", TEMP_DIR], cwd=WORKING_DIR)
        assert result_git.returncode == 0
    assert os.path.exists(GIT_DIR)

    if not os.path.exists(GITLET_DIR):
        result_gitlet = subprocess.run([GITLET, "init", TEMP_DIR], cwd=WORKING_DIR)
        assert result_gitlet.returncode == 0
    assert os.path.exists(GITLET_DIR)


def global_teardown():
    if os.path.exists(TEMP_DIR):
        shutil.rmtree(TEMP_DIR)
    assert not os.path.exists(TEMP_DIR)
  