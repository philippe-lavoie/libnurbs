dnl WITH_IMAGE_MAGICK
dnl
dnl Wheter Image Magick is defined in this system.
AC_DEFUN(HAS_IMAGE_MAGICK,
[
AC_REQUIRE([AC_PROG_CXX])

AC_CACHE_VAL(has_image_magick,
[
 AC_CHECK_PROG([has_image_magick],[Magick-config],[yes],[no])

 if test x"$has_image_magick" = xyes; then
dnl   AC_MSG_CHECKING([Whether you can use the Image Magick library])
   AC_LANG_SAVE
   MAGICK_CPPFLAGS=`Magick-config --cppflags`
   MAGICK_LDFLAGS=`Magick-config --ldflags`
   MAGICK_LIBS=`Magick-config --libs`
   SAVE_CPPFLAGS="$CPPFLAGS"
  CPPFLAGS="$CPPFLAGS $MAGICK_CPPFLAGS"
  SAVE_LDFLAGS="$LDFLAGS"
  LDFLAGS="$LDFLAGS $MAGICK_LDFLAGS"
  SAVE_LIBS="$LIBS"
  LIBS="$LIBS $MAGICK_LDFLAGS $MAGICK_LIBS"

  has_image_magick=no
  AC_CHECK_HEADER(magick/magick_config.h,
	[has_image_magick=yes])

dnl  AC_TRY_COMPILE([
dnl    #include <magick/magick_config.h>
dnl #include <magick/api.h>
dnl ],[return 1;],
dnl    [has_image_magick=yes],
dnl    [has_image_magick=no])

  CPPFLAGS="$SAVE_CPPFLAGS"
  LDFLAGS="$SAVE_LDFLAGS"
  LIBS="$SAVE_LIBS"
dnl  AC_MSG_RESULT($has_image_magick)
 fi
])

if test x"$has_image_magick" = xyes; then
  AC_DEFINE(WITH_IMAGE_MAGICK)
  AC_SUBST(MAGICK_CPPFLAGS)
  AC_SUBST(MAGICK_LDFLAGS)
  AC_SUBST(MAGICK_LIBS)
fi

])dnl HAS_IMAGE MAGICK

