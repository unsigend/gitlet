"""Test the init command in gitlet"""
import os

from util import _global

def test_command_init() -> None:
    _global.global_setup()

    # check if the objects directory exists
    assert os.path.exists(_global.GITLET_DIR + "/objects")

    # check if the refs directory exists
    assert os.path.exists(_global.GITLET_DIR + "/refs")
    assert os.path.exists(_global.GITLET_DIR + "/refs/heads")
    assert os.path.exists(_global.GITLET_DIR + "/refs/tags")

    # check if the HEAD file exists
    assert os.path.exists(_global.GITLET_DIR + "/HEAD")
    with open(_global.GITLET_DIR + "/HEAD", "r") as f:
        assert f.read() == "ref: refs/heads/master\n"

    # check if the config file exists
    assert os.path.exists(_global.GITLET_DIR + "/config")

    # check if the description file exists
    assert os.path.exists(_global.GITLET_DIR + "/description")
    with open(_global.GITLET_DIR + "/description", "r") as f:
        assert f.read() == "Unnamed repository; edit this file 'description' to name the repository.\n"

    _global.global_teardown()