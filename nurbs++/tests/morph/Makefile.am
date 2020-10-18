EXTRA_DIST = Morph.dsp

AM_CPPFLAGS = @CPPUNIT_CPPFLAGS@ @matrix_include@ @option_cflags@
LDADD = @CPPUNIT_LIBS@ \
	@top_srcdir@/morph/libmorph.la \
	@top_srcdir@/image/libmatrixI.la \
	@top_srcdir@/matrix/libmatrix.la \
	@option_libs@ \
	-ldl -lm -lc

if BUILD_CPPUNIT_TESTS
test_program = test_morph
else
test_program = 
endif

noinst_PROGRAMS = $(test_program)

test_morph_SOURCES = test_main.cpp \
			test_basicTransform.cpp \
			test_kernels.cpp \
			test_watershed.cpp





