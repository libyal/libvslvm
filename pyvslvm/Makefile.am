if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@

pyexec_LTLIBRARIES = pyvslvm.la

pyvslvm_la_SOURCES = \
	pyvslvm.c pyvslvm.h \
	pyvslvm_error.c pyvslvm_error.h \
	pyvslvm_file_object_io_handle.c pyvslvm_file_object_io_handle.h \
	pyvslvm_file_objects_io_pool.c pyvslvm_file_objects_io_pool.h \
	pyvslvm_handle.c pyvslvm_handle.h \
	pyvslvm_integer.c pyvslvm_integer.h \
	pyvslvm_libbfio.h \
	pyvslvm_libcerror.h \
	pyvslvm_libclocale.h \
	pyvslvm_libcstring.h \
	pyvslvm_libvslvm.h \
	pyvslvm_python.h \
	pyvslvm_unused.h

pyvslvm_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	../libvslvm/libvslvm.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pyvslvm_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pyvslvm_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

