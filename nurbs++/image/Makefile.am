EXTRA_DIST = rec_filter.cc filter.cc image.cc

MAGICK_INCLUDE =  @MAGICK_CPPFLAGS@
INCLUDES = $(MAGICK_INCLUDE) -I@top_srcdir@/include -I@top_srcdir@/matrix

CXXFLAGS = @CXXFLAGS@

pkginclude_HEADERS = image.hh rec_filter.hh color.hh filter.hh

lib_LTLIBRARIES = libmatrixI.la
libmatrixI_la_SOURCES = color.cc image_.cc  rec_filter_.cc filter_.cc
libmatrixI_la_LDFLAGS = -version-info 1:0:0
