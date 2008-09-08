AC_INIT([libft], [0.1], [erik@vontaene.de])

AH_TOP(
#undef DARWIN_API
)

AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_LIBTOOL
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
Makefile
lib/Makefile
examples/Makefile
README.OSX
])

if test -d "/usr/local/include" -a -d "/usr/local/lib"; then
	CPPFLAGS="$CPPFLAGS -I/usr/local/include"
	LDFLAGS="$LDFLAGS -L/usr/local/lib"
fi

pthread_libs=""
AC_CHECK_LIB(pthread, pthread_create, pthread_libs="-lpthread")
if test ! "$pthread_libs"; then
        AC_MSG_ERROR([pthreads not found])
fi
LIBS="$pthread_libs $LIBS"

have_libusb=no
AC_CHECK_LIB(usb, usb_find_devices, have_libusb=yes)
if test "$have_libusb" != yes; then
        AC_MSG_ERROR([libusb not found])
fi
LIBS="-lusb $LIBS"
AC_DEFINE(HAVE_LIBUSB, ,[Define if we have libusb.])
AM_CONDITIONAL(HAVE_LIBUSB, test "$have_libusb" = "yes")

DARWIN_API=0
AC_MSG_CHECKING([if the host operating system is Darwin])
case $host in
 	*-darwin*)
  		DARWIN_API=1
		AC_MSG_RESULT([yes - Not building examples.])
		AC_DEFINE(DARWIN_API, 1)
		os_support=darwin
		;;
	*)
		AC_MSG_RESULT([no])
		;;
esac
AC_SUBST(DARWIN_API)
AM_CONDITIONAL(DARWIN_API, test "$os_support" = "darwin")

AC_OUTPUT

