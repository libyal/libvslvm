# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir3)"
pyexecdir = $(pyexecdir3)

if HAVE_PYTHON3
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBVSLVM_DLL_IMPORT@

am_pyvslvm_la_rpath = -rpath $(pyexecdir3)

BUILT_SOURCES = \
	pyvslvm.c pyvslvm.h \
	pyvslvm_error.c pyvslvm_error.h \
	pyvslvm_file_object_io_handle.c pyvslvm_file_object_io_handle.h \
	pyvslvm_file_objects_io_pool.c pyvslvm_file_objects_io_pool.h \
	pyvslvm_handle.c pyvslvm_handle.h \
	pyvslvm_integer.c pyvslvm_integer.h \
	pyvslvm_libbfio.h \
	pyvslvm_libcerror.h \
	pyvslvm_libclocale.h \
	pyvslvm_libvslvm.h \
	pyvslvm_logical_volume.c pyvslvm_logical_volume.h \
	pyvslvm_logical_volumes.c pyvslvm_logical_volumes.h \
	pyvslvm_physical_volume.c pyvslvm_physical_volume.h \
	pyvslvm_physical_volumes.c pyvslvm_physical_volumes.h \
	pyvslvm_python.h \
	pyvslvm_segment.c pyvslvm_segment.h \
	pyvslvm_segments.c pyvslvm_segments.h \
	pyvslvm_stripe.c pyvslvm_stripe.h \
	pyvslvm_stripes.c pyvslvm_stripes.h \
	pyvslvm_unused.h \
	pyvslvm_volume_group.c pyvslvm_volume_group.h

pyexec_LTLIBRARIES = pyvslvm.la

nodist_pyvslvm_la_SOURCES = $(BUILT_SOURCES)

pyvslvm_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libvslvm/libvslvm.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pyvslvm_la_CPPFLAGS = $(PYTHON3_CPPFLAGS)
pyvslvm_la_LDFLAGS  = -module -avoid-version $(PYTHON3_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyvslvm/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyvslvm*.[ch]

distclean: clean
	/bin/rm -f Makefile

