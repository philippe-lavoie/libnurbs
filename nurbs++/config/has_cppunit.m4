dnl WITH_CPPUNIT
dnl
dnl Whether CppUnit is defined in this system.
AC_DEFUN(WITH_CPPUNIT,
[
AC_REQUIRE([AC_PROG_CXX])
AC_MSG_CHECKING(whether cppunit library is present)

AC_CACHE_VAL(has_cppunit,
[
 AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 CPPUNIT_CPPFLAGS=`cppunit-config --cflags`
 CPPUNIT_LIBS=`cppunit-config --libs`
 SAVE_CPPFLAGS="$CPPFLAGS"
 CPPFLAGS="$CPPFLAGS $CPPUNIT_CPPFLAGS"
 SAVE_LIBS="$LIBS"
 LIBS="$LIBS $CPPUNIT_LIBS"

 AC_TRY_COMPILE([
 #include <cppunit/TestCase.h>
 ],[return 1;],
 has_cppunit=yes,
 has_cppunit=no)
 
 CPPFLAGS="$SAVE_CPPFLAGS"
 LDFLAGS="$SAVE_LDFLAGS"
 LIBS="$SAVE_LIBS"
 AC_LANG_RESTORE
])

AC_MSG_RESULT($has_cppunit)
if test "$has_cppunit" = yes; then
   AC_DEFINE(HAS_CPPUNIT)
   AC_SUBST(CPPUNIT_CPPFLAGS)
   AC_SUBST(CPPUNIT_LIBS)
fi
])

