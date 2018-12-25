AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFUSE_CPPFLAGS@ \
	@LIBVSLVM_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	vslvminfo \
	vslvmmount

vslvminfo_SOURCES = \
	byte_size_string.c byte_size_string.h \
	info_handle.c info_handle.h \
	vslvminfo.c \
	vslvmtools_getopt.c vslvmtools_getopt.h \
	vslvmtools_i18n.h \
	vslvmtools_libbfio.h \
	vslvmtools_libcerror.h \
	vslvmtools_libclocale.h \
	vslvmtools_libcnotify.h \
	vslvmtools_libvslvm.h \
	vslvmtools_libuna.h \
	vslvmtools_output.c vslvmtools_output.h \
	vslvmtools_signal.c vslvmtools_signal.h \
	vslvmtools_unused.h

vslvminfo_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

vslvmmount_SOURCES = \
	mount_dokan.c mount_dokan.h \
	mount_file_entry.c mount_file_entry.h \
	mount_file_system.c mount_file_system.h \
	mount_fuse.c mount_fuse.h \
	mount_handle.c mount_handle.h \
	vslvmmount.c \
	vslvmtools_getopt.c vslvmtools_getopt.h \
	vslvmtools_i18n.h \
	vslvmtools_libbfio.h \
	vslvmtools_libcdata.h \
	vslvmtools_libcerror.h \
	vslvmtools_libclocale.h \
	vslvmtools_libcnotify.h \
	vslvmtools_libcpath.h \
	vslvmtools_libvslvm.h \
	vslvmtools_libuna.h \
	vslvmtools_output.c vslvmtools_output.h \
	vslvmtools_signal.c vslvmtools_signal.h \
	vslvmtools_unused.h

vslvmmount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on vslvminfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(vslvminfo_SOURCES)

