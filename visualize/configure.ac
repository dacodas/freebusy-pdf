AC_INIT([freebusy], [0.0.1], [dacoda.strack@gmail.com], [https://dacodastrack.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_USE_SYSTEM_EXTENSIONS([_GNU_SOURCE])
AH_VERBATIM([_POSIX_C_SOURCE], [
#ifndef __USE_POSIX
# define __USE_POSIX
#endif

#ifndef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE 200809L
#endif])

AC_CONFIG_FILES([gnulib/Makefile])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC
AC_PROG_CXX

gl_EARLY

gl_INIT

AC_OUTPUT([Makefile])
