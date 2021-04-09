AUTOMAKE_OPTIONS = subdir-objects

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
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBVSLVM_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYVSLVM = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_tools.sh \
	test_vslvminfo.sh \
	$(TESTS_PYVSLVM)

check_SCRIPTS = \
	pyvslvm_test_support.py \
	test_library.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh \
	test_tools.sh \
	test_vslvminfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vslvm_test_chunk_data \
	vslvm_test_data_area_descriptor \
	vslvm_test_error \
	vslvm_test_handle \
	vslvm_test_io_handle \
	vslvm_test_logical_volume \
	vslvm_test_logical_volume_values \
	vslvm_test_metadata \
	vslvm_test_metadata_area \
	vslvm_test_notify \
	vslvm_test_physical_volume \
	vslvm_test_raw_location_descriptor \
	vslvm_test_segment \
	vslvm_test_stripe \
	vslvm_test_support \
	vslvm_test_tools_info_handle \
	vslvm_test_tools_output \
	vslvm_test_tools_signal \
	vslvm_test_volume_group

vslvm_test_chunk_data_SOURCES = \
	vslvm_test_chunk_data.c \
	vslvm_test_libbfio.h \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_unused.h

vslvm_test_chunk_data_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_data_area_descriptor_SOURCES = \
	vslvm_test_data_area_descriptor.c \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_unused.h

vslvm_test_data_area_descriptor_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_error_SOURCES = \
	vslvm_test_error.c \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_unused.h

vslvm_test_error_LDADD = \
	../libvslvm/libvslvm.la

vslvm_test_handle_SOURCES = \
	vslvm_test_getopt.c vslvm_test_getopt.h \
	vslvm_test_handle.c \
	vslvm_test_libcerror.h \
	vslvm_test_libclocale.h \
	vslvm_test_libcnotify.h \
	vslvm_test_libuna.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h

vslvm_test_handle_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvslvm/libvslvm.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

vslvm_test_io_handle_SOURCES = \
	vslvm_test_io_handle.c \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_unused.h

vslvm_test_io_handle_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_logical_volume_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_logical_volume.c \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_unused.h

vslvm_test_logical_volume_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_logical_volume_values_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_logical_volume_values.c \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_unused.h

vslvm_test_logical_volume_values_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_metadata_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_metadata.c \
	vslvm_test_unused.h

vslvm_test_metadata_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_metadata_area_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_metadata_area.c \
	vslvm_test_unused.h

vslvm_test_metadata_area_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_notify_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_notify.c \
	vslvm_test_unused.h

vslvm_test_notify_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_physical_volume_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_physical_volume.c \
	vslvm_test_unused.h

vslvm_test_physical_volume_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_raw_location_descriptor_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_raw_location_descriptor.c \
	vslvm_test_unused.h

vslvm_test_raw_location_descriptor_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_segment_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_segment.c \
	vslvm_test_unused.h

vslvm_test_segment_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_stripe_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_stripe.c \
	vslvm_test_unused.h

vslvm_test_stripe_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_support_SOURCES = \
	vslvm_test_functions.c vslvm_test_functions.h \
	vslvm_test_getopt.c vslvm_test_getopt.h \
	vslvm_test_libbfio.h \
	vslvm_test_libcerror.h \
	vslvm_test_libclocale.h \
	vslvm_test_libcnotify.h \
	vslvm_test_libuna.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_support.c

vslvm_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_tools_info_handle_SOURCES = \
	../vslvmtools/byte_size_string.c ../vslvmtools/byte_size_string.h \
	../vslvmtools/info_handle.c ../vslvmtools/info_handle.h \
	vslvm_test_libcerror.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_tools_info_handle.c \
	vslvm_test_unused.h

vslvm_test_tools_info_handle_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_tools_output_SOURCES = \
	../vslvmtools/vslvmtools_output.c ../vslvmtools/vslvmtools_output.h \
	vslvm_test_libcerror.h \
	vslvm_test_macros.h \
	vslvm_test_tools_output.c \
	vslvm_test_unused.h

vslvm_test_tools_output_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_tools_signal_SOURCES = \
	../vslvmtools/vslvmtools_signal.c ../vslvmtools/vslvmtools_signal.h \
	vslvm_test_libcerror.h \
	vslvm_test_macros.h \
	vslvm_test_tools_signal.c \
	vslvm_test_unused.h

vslvm_test_tools_signal_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

vslvm_test_volume_group_SOURCES = \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_macros.h \
	vslvm_test_memory.c vslvm_test_memory.h \
	vslvm_test_unused.h \
	vslvm_test_volume_group.c

vslvm_test_volume_group_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

