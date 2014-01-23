dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------

AC_PREREQ([2.69])


dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

GENERIC_LIBRARY_NAME=fnx

#release versioning
GENERIC_MAJOR_VERSION=0
GENERIC_MINOR_VERSION=8
GENERIC_MICRO_VERSION=0
GENERIC_PATCH_LEVEL=0
AC_SUBST(GENERIC_MAJOR_VERSION)
AC_SUBST(GENERIC_MINOR_VERSION)
AC_SUBST(GENERIC_MICRO_VERSION)
AC_SUBST(GENERIC_PATCH_LEVEL)


#shared library versioning
GENERIC_LIBRARY_VERSION=$GENERIC_MINOR_VERSION:$GENERIC_MICRO_VERSION:$GENERIC_PATCH_LEVEL
GENERIC_LIBRARY_VERSION_DOTTED=$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION.$GENERIC_PATCH_LEVEL



dnl --------------------------------
dnl Package name and version number
dnl --------------------------------

AC_SUBST(GENERIC_LIBRARY_VERSION)
AC_SUBST(GENERIC_LIBRARY_VERSION_DOTTED)

PACKAGE=$GENERIC_LIBRARY_NAME
AC_SUBST(GENERIC_LIBRARY_NAME)

#GENERIC_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION.$GENERIC_PATCH_LEVEL
GENERIC_VERSION=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION
GENERIC_RELEASE=$GENERIC_MAJOR_VERSION.$GENERIC_MINOR_VERSION.$GENERIC_MICRO_VERSION
AC_SUBST(GENERIC_RELEASE)
AC_SUBST(GENERIC_VERSION)

VERSION=$GENERIC_VERSION

#AC_INIT(fnx/APNSConstants.h)
AC_INIT([PACKAGE], [VERSION], [http://github.com/coredumped/libfnx])
AC_CONFIG_MACRO_DIR([m4])
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE

dnl -----------------------------------------------
dnl Checks for programs.
dnl -----------------------------------------------

AC_PROG_CC
AC_PROG_CXX
dnl -----------------------------------------------
dnl If it is GCC verify its version is >= 3.0.0
dnl -----------------------------------------------
if test "$GXX" = "yes" ; then
        AC_MSG_RESULT([GCC Detected, checking version... ])
        AC_TRY_RUN([ 

                        int main()
                        {
                                if(__GNUC__ < 3) return 1;
                                return 0;
                        }
        ], [ echo "GCC version is >= 3" ], 
        [
                echo "libfnx must be compiled with GCC versions 3.0.0 and above, please upgrade your compiler"
                exit 1
        ]
        )
fi
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL
AC_PROG_INSTALL

AC_LANG_CPLUSPLUS
AC_C_BIGENDIAN([
                        SYSTEM_IS_BIGENDIAN=1
                        SYSTEM_IS_LITTLEENDIAN=0
                        AC_SUBST(SYSTEM_IS_BIGENDIAN)
                        echo "System architecture is big-endian"
                ],[
                        SYSTEM_IS_LITTLEENDIAN=1
                        SYSTEM_IS_BIGENDIAN=0
                        AC_SUBST(SYSTEM_IS_LITTLEENDIAN)
                        echo "System architecture is little-endian"
                ],[
                        echo "Unknown architecture byte ordering"
                        exit 1
                ]
              )


CXXFLAGS="$CXXFLAGS -Wall "

dnl -----------------------------------------------
dnl Verify manual features
dnl -----------------------------------------------
dnl LIBS="$LIBS -ldl"

AC_ARG_ENABLE(debug, AC_HELP_STRING([--enable-debug                Build library in debug mode]), [
                AC_DEFINE(DEBUG, 1, [Activates debug mode])
                debug_mode_activated=on
                AC_MSG_RESULT([ *** This library will be compiled with debug support activated *** ])
                CPPFLAGS="$CPPFLAGS -DDEBUG"
        ], [
                debug_mode_activated=off
        ]
)

AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h stdint.h string.h strings.h sys/socket.h unistd.h])
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

dnl -----------------------------------------------
dnl Miscellaneous function checking
dnl -----------------------------------------------
AC_CHECK_FUNCS(strtol strcpy memcpy pow strtoul strtoll strtoull strtof strtod strtold strerror_r, [
        threads_library="POSIX Threads (pthreads)"
        ENABLE_XVR2_POSIX_THREADS_SUPPORT=1
        AC_SUBST(ENABLE_XVR2_POSIX_THREADS_SUPPORT)
],[
        exit 1;
])

dnl -----------------------------------------------
dnl Miscellaneous function checking
dnl -----------------------------------------------
AC_CHECK_FUNCS(getgrgid_r, [

],[
        AC_DEFINE(DONT_HAVE_REENTRANT_GETGRGID, 1, [Reentrant getgrgid_r function is not defined])
])


dnl -----------------------------------------------
dnl POSIX Threads testing
dnl -----------------------------------------------
AC_CHECK_LIB(pthread, pthread_create, [
        AC_CHECK_LIB(pthread, pthread_attr_init, [
                AC_CHECK_FUNCS(pthread_self, [
                        threads_library="POSIX Threads (pthreads)"
                        ENABLE_XVR2_POSIX_THREADS_SUPPORT=1
                        AC_SUBST(ENABLE_XVR2_POSIX_THREADS_SUPPORT)
                ],[
                        AC_MSG_RESULT([ !!! Posix Threads are not supported in this platform !!! ])
                        exit 1;
                ])
        ],[
                AC_MSG_RESULT([ !!! Posix Threads are not supported in this platform !!! ])
                exit 1;
        ])
        
],[
        AC_MSG_RESULT([ !!! Posix Threads are not supported in this platform !!! ])
        exit 1;
])

if test "$ENABLE_XVR2_POSIX_THREADS_SUPPORT" = "1"; then
        LIBS="$LIBS -lpthread"
        CPPFLAGS="$CPPFLAGS -DUSE_POSIX_THREADS -D_REENTRANT -D_THREAD_SAFE"
fi

dnl --------------------------------------------------------------
dnl Verify that SQLite development files are already installed
dnl --------------------------------------------------------------
SQLITE_INCLUDES=""
SQLITE_CFLAGS=""
SQLITE_LIBDIR=""
SQLITE_LIBS=""
SQLITE_DRIVER_ENABLED=no
SQLITE_DRIVER_DIR=""

AC_CHECK_HEADERS(sqlite3.h, [
        SQLITE_DRIVER_ENABLED=yes
        SQLITE_DRIVER_DIR=sqlite
        SQLITE_LIBS=-lsqlite3
])

AC_SUBST(SQLITE_DRIVER_DIR)
AC_SUBST(SQLITE_LIBS)

dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_OUTPUT(Makefile \
        fnx/Makefile
)

