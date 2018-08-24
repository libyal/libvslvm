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
	@LIBVSLVM_DLL_EXPORT@

lib_LTLIBRARIES = libvslvm.la

libvslvm_la_SOURCES = \
	libvslvm.c \
	libvslvm_checksum.c libvslvm_checksum.h \
	libvslvm_chunk_data.c libvslvm_chunk_data.h \
	libvslvm_data_area_descriptor.c libvslvm_data_area_descriptor.h \
	libvslvm_debug.c libvslvm_debug.h \
	libvslvm_definitions.h \
	libvslvm_error.c libvslvm_error.h \
	libvslvm_extern.h \
	libvslvm_handle.c libvslvm_handle.h \
	libvslvm_io_handle.c libvslvm_io_handle.h \
	libvslvm_libbfio.h \
	libvslvm_libcdata.h \
	libvslvm_libcerror.h \
	libvslvm_libclocale.h \
	libvslvm_libcnotify.h \
	libvslvm_libcsplit.h \
	libvslvm_libcthreads.h \
	libvslvm_libfcache.h \
	libvslvm_libfdata.h \
	libvslvm_libfvalue.h \
	libvslvm_logical_volume.c libvslvm_logical_volume.h \
	libvslvm_logical_volume_values.c libvslvm_logical_volume_values.h \
	libvslvm_metadata.c libvslvm_metadata.h \
	libvslvm_metadata_area.c libvslvm_metadata_area.h \
	libvslvm_notify.c libvslvm_notify.h \
	libvslvm_physical_volume.c libvslvm_physical_volume.h \
	libvslvm_raw_location_descriptor.c libvslvm_raw_location_descriptor.h \
	libvslvm_segment.c libvslvm_segment.h \
	libvslvm_stripe.c libvslvm_stripe.h \
	libvslvm_support.c libvslvm_support.h \
	libvslvm_types.h \
	libvslvm_unused.h \
	libvslvm_volume_group.c libvslvm_volume_group.h \
	vslvm_metadata_area.h \
	vslvm_physical_volume_label.h

libvslvm_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@LIBFVALUE_LIBADD@ \
	@PTHREAD_LIBADD@

libvslvm_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libvslvm_definitions.h.in \
	libvslvm.rc \
	libvslvm.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libvslvm_definitions.h
	/bin/rm -f libvslvm.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libvslvm ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libvslvm_la_SOURCES)

