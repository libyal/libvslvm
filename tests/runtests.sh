#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libvslvm/.libs/libvslvm.1.dylib" ] && [ -f ./pyvslvm/.libs/pyvslvm.so ]
then
    install_name_tool -change /usr/local/lib/libvslvm.1.dylib "${PWD}/libvslvm/.libs/libvslvm.1.dylib" ./pyvslvm/.libs/pyvslvm.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

