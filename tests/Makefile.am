AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_SCRIPTS = \
	pyvslvm_test_handle.py \
	pyvslvm_test_support.py

check_PROGRAMS = \
	vslvm_test_checksum \
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

vslvm_test_checksum_SOURCES = \
	vslvm_test_checksum.c \
	vslvm_test_libcerror.h \
	vslvm_test_libvslvm.h \
	vslvm_test_unused.h

vslvm_test_checksum_LDADD = \
	../libvslvm/libvslvm.la \
	@LIBCERROR_LIBADD@

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
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libvslvm.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libvslvm

test_inputs_pyvslvm.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) pyvslvm

test_inputs_vslvminfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) vslvminfo

test_library: \
	package.m4 \
	test_inputs_libvslvm.at \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_python_module: \
	package.m4 \
	test_inputs_pyvslvm.at \
	test_python_module.at

test_tools: \
	package.m4 \
	test_inputs_vslvminfo.at \
	test_macros.at \
	test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(check_SCRIPTS) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

