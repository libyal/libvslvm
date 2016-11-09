AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBVSLVM_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYVSLVM =
endif

TESTS = \
	test_api_functions.sh \
	test_vslvminfo.sh \
	$(TESTS_PYVSLVM)

check_SCRIPTS = \
	test_vslvminfo.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vslvm_test_error \
	vslvm_test_open_close \
	vslvm_test_read \
	vslvm_test_seek \
	vslvm_test_support

vslvm_test_error_SOURCES = \
	vslvm_test_error.c \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_unused.h

vslvm_test_error_LDADD = \
	../libvslvm/libvslvm.la

vslvm_test_open_close_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_open_close.c \
	vslvm_test_unused.h

vslvm_test_open_close_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_read_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_read.c \
	vslvm_test_unused.h

vslvm_test_read_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_seek_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_seek.c \
	vslvm_test_unused.h

vslvm_test_seek_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_support_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_support.c \
	vslvm_test_unused.h

vslvm_test_support_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

