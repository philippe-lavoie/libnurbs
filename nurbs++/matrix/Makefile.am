#CXXFLAGS = @CXXFLAGS@ -DMATRIX_TEMPLATE_INSTANTIATION

EXTRA_DIST = barray.cc   barray2d.cc  matrix.cc  vector.cc  

pkginclude_HEADERS = barray.hh galloc2d.hh barray2d.hh hpoint_nd.hh matrixTool.hh coordinate.hh point_nd.hh cvector.hh specialType.hh error.hh list.hh specialVcc.hh galloc.hh matrix.hh vector.hh matrix_global.hh

#pkginclude_SOURCES = barray.cc   barray2d.cc  error.cc   cvector.cc  matrix.cc  vector.cc  list.cc point_nd.cc hpoint_nd.cc coordinate.cc matrixTool.cc

INCLUDES = -I../include

lib_LTLIBRARIES = libmatrix.la
libmatrix_la_SOURCES = error.cc   cvector.cc list.cc point_nd.cc hpoint_nd.cc coordinate.cc matrixTool.cc
libmatrix_la_SOURCES +=   barray_int.cc   barray2d_int.cc  matrix_int.cc  vector_int.cc 
libmatrix_la_SOURCES +=   barray_float.cc   barray2d_float.cc  matrix_float.cc  vector_float.cc 
libmatrix_la_SOURCES +=   barray_double.cc   barray2d_double.cc  matrix_double.cc  vector_double.cc 
libmatrix_la_SOURCES +=  barray_uchar.cc   barray2d_uchar.cc  matrix_uchar.cc  vector_uchar.cc 
libmatrix_la_SOURCES +=  barray_char.cc   barray2d_char.cc  matrix_char.cc  vector_char.cc 
libmatrix_la_SOURCES +=  barray_point.cc   barray2d_point.cc  matrix_point.cc  vector_point.cc 
libmatrix_la_SOURCES +=  barray_hpoint.cc   barray2d_hpoint.cc  matrix_hpoint.cc  vector_hpoint.cc 
libmatrix_la_SOURCES +=  barray_complex.cc   barray2d_complex.cc  matrix_complex.cc  vector_complex.cc 
libmatrix_la_SOURCES +=  barray_coordinate.cc   barray2d_coordinate.cc 
libmatrix_la_SOURCES +=  barray_void.cc


libmatrix_la_LDFLAGS = -version-info 1:0:0
