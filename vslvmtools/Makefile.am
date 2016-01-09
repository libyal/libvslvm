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
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBFUSE_CPPFLAGS@ \
	@LIBVSLVM_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	vslvminfo \
	vslvmmount

vslvminfo_SOURCES = \
	byte_size_string.c byte_size_string.h \
	vslvminfo.c \
	vslvmoutput.c vslvmoutput.h \
	vslvmtools_libbfio.h \
	vslvmtools_libcerror.h \
	vslvmtools_libclocale.h \
	vslvmtools_libcnotify.h \
	vslvmtools_libcstring.h \
	vslvmtools_libcsystem.h \
	vslvmtools_libvslvm.h \
	vslvmtools_libuna.h \
	info_handle.c info_handle.h

vslvminfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvslvm/libvslvm.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

vslvmmount_SOURCES = \
	mount_handle.c mount_handle.h \
	vslvmmount.c \
	vslvmoutput.c vslvmoutput.h \
	vslvmtools_libbfio.h \
	vslvmtools_libcdata.h \
	vslvmtools_libcerror.h \
	vslvmtools_libclocale.h \
	vslvmtools_libcnotify.h \
	vslvmtools_libcstring.h \
	vslvmtools_libcsystem.h \
	vslvmtools_libvslvm.h \
	vslvmtools_libuna.h

vslvmmount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBCSYSTEM_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvslvm/libvslvm.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on vslvminfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(vslvminfo_SOURCES)

