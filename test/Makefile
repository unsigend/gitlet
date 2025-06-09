# MIT License
#
# Copyright (c) 2025 Qiu Yixiang
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

ROOT_PATH       :=      .
TEST_PATH   	:=		./tests

PIP             :=      $(ROOT_PATH)/.venv/bin/pip
PYTEST          :=      $(ROOT_PATH)/.venv/bin/pytest

.DEFAULT_GOAL := test
.PHONY: test clean-all py-init py-install py-dependencies

test: py-install
	@$(PYTEST) $(TEST_PATH)
    
clean-all:
	@rm -rf $(ROOT_PATH)/.venv
	@rm -rf $(ROOT_PATH)/.pytest_cache

# Init the python environment
py-init:
	@if [ ! -d $(ROOT_PATH)/.venv ]; then \
		$(PYTHON) -m venv $(ROOT_PATH)/.venv; \
	fi
	@. $(ROOT_PATH)/.venv/bin/activate

# Install the dependencies
py-dependencies     	:=	pytest
py-install: py-init
	@if ! $(PIP) list | grep -q $(py-dependencies); then \
		$(PIP) install $(py-dependencies); \
	fi
	