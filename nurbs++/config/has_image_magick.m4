dnl WITH_IMAGE_MAGICK
dnl
dnl Wheter Image Magick is defined in this system.
AC_DEFUN(HAS_IMAGE_MAGICK,
[
AC_REQUIRE([AC_PROG_CXX])

AC_CACHE_VAL(has_image_magick,
[
 AC_CHECK_PROG([has_image_magick],[Magick++-config],[yes],[no])

 if test x"$has_image_magick" = xyes; then
   AC_MSG_CHECKING([Whether you can use the Image Magick Magick++ library])
   AC_LANG_SAVE
   AC_LANG_CPLUSPLUS
   MAGICK_CPPFLAGS=`Magick++-config --cppflags`
   MAGICK_LDFLAGS=`Magick++-config --ldflags`
   MAGICK_LIBS=`Magick++-config --libs`
   SAVE_CPPFLAGS="$CPPFLAGS"
  CPPFLAGS="$CPPFLAGS $MAGICK_CPPFLAGS"
  SAVE_LDFLAGS="$LDFLAGS"
  LDFLAGS="$LDFLAGS $MAGICK_LDFLAGS"
  SAVE_LIBS="$LIBS"
  LIBS="$LIBS $MAGICK_LDFLAGS $MAGICK_LIBS"

  AC_TRY_COMPILE([
    #include <Magick++.h>
    ],[return 1;],
    [has_image_magick=yes],
    [has_image_magick=no])

  CPPFLAGS="$SAVE_CPPFLAGS"
  LDFLAGS="$SAVE_LDFLAGS"
  LIBS="$SAVE_LIBS"
  AC_LANG_RESTORE
  AC_MSG_RESULT($has_image_magick)
 fi
])

if test x"$has_image_magick" = xyes; then
  AC_DEFINE(WITH_IMAGE_MAGICK)
  AC_SUBST(MAGICK_CPPFLAGS)
  AC_SUBST(MAGICK_LDFLAGS)
  AC_SUBST(MAGICK_LIBS)
fi

])dnl HAS_IMAGE MAGICK

