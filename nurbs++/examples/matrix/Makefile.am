
COMPLEXLIB = @complex_lib@

INCLUDES = -I@top_srcdir@/matrix
#LIBSINC = $(MAGICK_LIB) 

EXTRALIBS = -lm -lc
ALLLIBS = $(EXTRALIBS)

TESTS = tvqSort tmatrix 
noinst_PROGRAMS = tvqSort tmatrix terr
LDADD = ../../matrix/libmatrix.la $(ALLLIBS)
#LDFLAGS = $(LIBSINC)

tvqSort_SOURCES = tvqSort.C
tmatrix_SOURCES = tmatrix.C
terr_SOURCES = terr.C 
