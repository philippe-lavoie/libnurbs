EXTRA_DIST = nurbs.dsp

INCLUDES = 	@matrix_include@ \
		@nurbs_include@ \
		@option_cflags@ \
		@CPPUNIT_CPPFLAGS@

LDADD = @CPPUNIT_LIBS@ \
	@top_srcdir@/nurbs/libnurbsf.la \
	@top_srcdir@/numerical/libmatrixN.la \
	@top_srcdir@/image/libmatrixI.la \
	@top_srcdir@/matrix/libmatrix.la \
	@option_libs@ \
	-ldl -lm -lc


if BUILD_CPPUNIT_TESTS
test_program = test_nurbs
else
test_program = 
endif

noinst_PROGRAMS = $(test_program)
test_nurbs_SOURCES = test_main.cpp test_nurbs.cpp


