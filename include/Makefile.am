include_HEADERS = \
	libvslvm.h

pkginclude_HEADERS = \
	libvslvm/codepage.h \
	libvslvm/definitions.h \
	libvslvm/error.h \
	libvslvm/extern.h \
	libvslvm/features.h \
	libvslvm/types.h

EXTRA_DIST = \
	libvslvm.h.in \
	libvslvm/definitions.h.in \
	libvslvm/features.h.in \
	libvslvm/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libvslvm.h
	/bin/rm -f libvslvm/definitions.h
	/bin/rm -f libvslvm/features.h
	/bin/rm -f libvslvm/types.h
	/bin/rm -f Makefile

