"""Test the init command in gitlet"""
import os

from util import _global

def test_command_init() -> None:
    _global.global_setup()

    _global.global_teardown()