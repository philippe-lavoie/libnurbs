EXTRA_DIST = Matrix.dsp

INCLUDES = @CPPUNIT_CPPFLAGS@ @matrix_include@ @option_cflags@
LDADD = @CPPUNIT_LIBS@ \
	@top_srcdir@/image/libmatrixI.la \
	@top_srcdir@/matrix/libmatrix.la \
	@option_libs@ \
	-ldl -lm -lc

if BUILD_CPPUNIT_TESTS
test_program = test_image xsection general
else
test_program = 
endif

noinst_PROGRAMS = $(test_program)

test_image_SOURCES = test_main.cpp test_magick.cpp
xsection_SOURCES = xsection.cpp
general_SOURCES = general.cpp




