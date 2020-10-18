#!/bin/bash
set -eu

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd ${DIR}/..
rm -f ./build/*.o
wine cmd /c ${DIR}/compile.bat
