#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libvslvm/.libs/libvslvm.1.dylib && test -f ./pyvslvm/.libs/pyvslvm.so
then
	install_name_tool -change /usr/local/lib/libvslvm.1.dylib ${PWD}/libvslvm/.libs/libvslvm.1.dylib ./pyvslvm/.libs/pyvslvm.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

