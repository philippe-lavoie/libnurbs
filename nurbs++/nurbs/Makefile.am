EXTRA_DIST = nurbs.cc curve.cc hnurbs.cc hnurbsS.cc hnurbsS_sp.cc matrixRT.cc nurbs.cc nurbsArray.cc nurbsGL.cc nurbsS.cc nurbsS_sp.cc nurbsSub.cc nurbs_sp.cc surface.cc tri_spline.cc

MAGICK_INCLUDE =  $(X_CFLAGS) @MAGICK_CPPFLAGS@

INCLUDES = $(MAGICK_INCLUDE) -I@top_srcdir@/include @matrix_include@ $(GL_CFLAGS)

pkginclude_HEADERS = curve.hh matrixRT.hh nurbsSub.hh hnurbs.hh nurbs.hh nurbs_sp.hh hnurbsS.hh nurbsGL.hh surface.hh hnurbsS_sp.hh nurbsS.hh nurbsS_sp.hh tri_spline.hh nurbs_global.hh

float_sources = f_nurbs.cc f_nurbsS.cc f_curve.cc f_surface.cc f_hnurbsS.cc matrixRT.cc f_nurbs_sp.cc f_nurbsS_sp.cc f_hnurbsS_sp.cc nurbsGL.cc f_nurbsArray.cc f_nurbsSub.cc f_tri_spline.cc

double_sources = d_nurbs.cc d_nurbsS.cc d_curve.cc d_surface.cc d_hnurbsS.cc matrixRT.cc d_nurbs_sp.cc d_nurbsS_sp.cc d_hnurbsS_sp.cc d_nurbsArray.cc  d_nurbsSub.cc d_tri_spline.cc

ldflags = -version-info 1:0:1

#EXTRA_LTLIBRARIES = libnurbsf.la libnurbsd.la
#lib_LTLIBRARIES = @build_lib@


#libnurbsf_la_SOURCES = f_nurbs.cc f_nurbsS.cc f_curve.cc f_surface.cc f_hnurbsS.cc matrixRT.cc f_nurbs_sp.cc f_nurbsS_sp.cc f_hnurbsS_sp.cc nurbsGL.cc f_nurbsArray.cc f_nurbsSub.cc

#libnurbsd_la_SOURCES = d_nurbs.cc d_nurbsS.cc d_curve.cc d_surface.cc d_hnurbsS.cc matrixRT.cc d_nurbs_sp.cc d_nurbsS_sp.cc d_hnurbsS_sp.cc d_nurbsArray.cc  d_nurbsSub.cc

#libnurbsf_la_LDFLAGS = -version-info 0:0:0
#libnurbsd_la_LDFLAGS = -version-info 0:0:0

#if BUILD_FLOAT_DOUBLE
#lib_LTLIBRARIES = libnurbsf.la libnurbsd.la
#libnurbsf_la_SOURCES = $(float_sources)
#libnurbsf_la_LDFLAGS = $(ldflags)
#libnurbsd_la_SOURCES = $(double_sources)
#libnurbsd_la_LDFLAGS = $(ldflags)
#else
#if BUILD_FLOAT
#lib_LTLIBRARIES = libnurbsf.la
#libnurbsf_la_SOURCES = $(float_sources)
#libnurbsf_la_LDFLAGS = $(ldflags)
#endif
#if BUILD_DOUBLE
#lib_LTLIBRARIES = libnurbsd.la
#libnurbsd_la_SOURCES = $(double_sources)
#libnurbsd_la_LDFLAGS = $(ldflags)
#endif
#endif

lib_LTLIBRARIES = libnurbsf.la libnurbsd.la
libnurbsf_la_SOURCES = $(float_sources)
libnurbsf_la_LDFLAGS = $(ldflags)
libnurbsd_la_SOURCES = $(double_sources)
libnurbsd_la_LDFLAGS = $(ldflags)

