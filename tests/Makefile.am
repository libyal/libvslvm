AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBVSLVM_DLL_IMPORT@

if HAVE_PYTHON
TESTS_PYVSLVM =
endif

TESTS = \
	test_open_close.sh \
	test_seek.sh \
	test_read.sh \
	test_vslvminfo.sh \
	$(TESTS_PYVSLVM)

check_SCRIPTS = \
	test_open_close.sh \
	test_vslvminfo.sh \
	test_read.sh \
	test_runner.sh \
	test_seek.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vslvm_test_open_close \
	vslvm_test_read \
	vslvm_test_seek

vslvm_test_open_close_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libcstring.h \
	vslvm_test_libvslvm.h \
	vslvm_test_open_close.c \
	vslvm_test_unused.h

vslvm_test_open_close_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

vslvm_test_read_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libcstring.h \
	vslvm_test_libvslvm.h \
	vslvm_test_read.c \
	vslvm_test_unused.h

vslvm_test_read_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

vslvm_test_seek_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libcstring.h \
	vslvm_test_libvslvm.h \
	vslvm_test_seek.c \
	vslvm_test_unused.h

vslvm_test_seek_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

