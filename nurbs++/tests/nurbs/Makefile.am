EXTRA_DIST = nurbs.dsp

INCLUDES = 	@matrix_include@ \
		@nurbs_include@ \
		@option_cflags@ \
		@CPPUNIT_CPPFLAGS@

LDADD = @CPPUNIT_LIBS@ @option_libs@ -ldl @matrix_lib_flag@ @matrix_lib@ @top_srcdir@/nurbs/libnurbsf.la -lm -lc

if BUILD_CPPUNIT_TESTS
test_program = test_nurbs
else
test_program = 
endif

noinst_PROGRAMS = $(test_program)
test_nurbs_SOURCES = test_main.cpp test_nurbs.cpp


