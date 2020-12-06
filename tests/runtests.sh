#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libvslvm/.libs/libvslvm.1.dylib && test -f ./pyvslvm/.libs/pyvslvm.so;
then
	install_name_tool -change /usr/local/lib/libvslvm.1.dylib ${PWD}/libvslvm/.libs/libvslvm.1.dylib ./pyvslvm/.libs/pyvslvm.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

