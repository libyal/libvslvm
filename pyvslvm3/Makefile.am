# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir3)"
pyexecdir = $(pyexecdir3)

if HAVE_PYTHON3
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@

am_pyvslvm_la_rpath = -rpath $(pyexecdir3)

BUILT_SOURCES = \
	pyvslvm.c pyvslvm.h

pyexec_LTLIBRARIES = pyvslvm.la

nodist_pyvslvm_la_SOURCES = $(BUILT_SOURCES)

pyvslvm_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	../libvslvm/libvslvm.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFGUID_LIBADD@

pyvslvm_la_CPPFLAGS = $(PYTHON3_CPPFLAGS)
pyvslvm_la_LDFLAGS  = -module -avoid-version $(PYTHON3_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyvslvm/pyvslvm*.[ch] .

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyvslvm*.[ch]

distclean: clean
	/bin/rm -f Makefile

