EXTRA_DIST = tleastS.png

XINCLUDE = @X_CFLAGS@
XLIBS = @X_PRE_LIBS@ @X_LIBS@ -lXt -lX11
MAGICK_INCLUDE =  $(XINCLUDE) @magick_include@
MAGICK_LIB = @magick_lib@
MAGICK_LIBS = @magick_libs@ 

COMPLEXLIB = @complex_lib@

MATRIX_INCLUDE = @matrix_include@
MATRIX_LIB_FLAG = @matrix_lib_flag@
MATRIXLIB = @matrix_lib@ @complex_lib@

OPENGL_LIBS = $(GL_LFLAGS) $(GL_LIBS) $(X_EXTRA_LIBS)

#INCLUDES = $(MAGICK_INCLUDE) $(GL_CFLAGS) @matrix_include@ @nurbs_include@
INCLUDES = @matrix_include@ @nurbs_include@ @option_include@
#EXTRALIBS = -lm -lc
#ALLLIBS = @nurbs_libf@ $(MATRIXLIB) @option_libs@ $(EXTRALIBS)
ALLLIBS = @nurbs_libf@ $(MATRIXLIB) @option_libs@

TESTS = tnurbs tnlength tnurbsS thnurbsS tnsSweep tmatrixRT tdrawAa  tnInterp tnApprox tnMovePoint tnsMovePoint tngl tleastS tnurbs_sp  tnurbsS_sp tclose tnurbsSub tmeasures trispline
noinst_PROGRAMS = tnurbs tnlength tnurbsS thnurbsS tnsSweep tmatrixRT tdrawAa  tnInterp tnApprox tnMovePoint tnsMovePoint tngl tleastS tnurbs_sp  tnurbsS_sp tclose tnurbsSub tmeasures  trispline 

LDADD = $(ALLLIBS)
#LDFLAGS = $(LIBSINC)

tnurbs_SOURCES = tnurbs.C
tnlength_SOURCES = tnlength.C
tnurbsS_SOURCES = tnurbsS.C
thnurbsS_SOURCES = thnurbsS.C
tnsSweep_SOURCES = tnsSweep.C
tmatrixRT_SOURCES = tmatrixRT.C
tdrawAa_SOURCES = tdrawAa.C
tnInterp_SOURCES = tnInterp.C
tnApprox_SOURCES = tnApprox.C
tnMovePoint_SOURCES = tnMovePoint.C
tnsMovePoint_SOURCES = tnsMovePoint.C
tngl_SOURCES = tngl.C
tleastS_SOURCES = tleastS.C
tnurbs_sp_SOURCES = tnurbs_sp.C
tnurbsS_sp_SOURCES = tnurbsS_sp.C
tclose_SOURCES = tclose.C
tnurbsSub_SOURCES = tnurbsSub.C
tmeasures_SOURCES = tmeasures.C
trispline_SOURCES = trispline.C


