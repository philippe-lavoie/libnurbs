EXTRA_DIST = matrixMat.cc fft.cc chebexp.cc intccq.cc statistic.cc

pkginclude_HEADERS = matrixMat.hh integrate.hh statistic.hh

INCLUDES = -I@top_srcdir@/include -I@top_srcdir@/matrix

lib_LTLIBRARIES = libmatrixN.la
libmatrixN_la_SOURCES = matrixMat_.cc fft_.cc chebexp_.cc intccq_.cc statistic_.cc
libmatrixN_la_LDFLAGS = -version-info 1:0:0

