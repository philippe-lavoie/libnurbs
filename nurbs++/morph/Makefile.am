EXTRA_DIST = kernel.cpp transform.cpp

INCLUDES = -I@top_srcdir@/include -I@top_srcdir@

CXXFLAGS = @NURBS_DEP_CPPFLAGS@ @CXXFLAGS@

pkginclude_HEADERS = kernel.h transform.h

lib_LTLIBRARIES = libmorph.la
libmorph_la_SOURCES = kernel.cpp transform.cpp
libmorph_la_LDFLAGS = -version-info 1:0:0
