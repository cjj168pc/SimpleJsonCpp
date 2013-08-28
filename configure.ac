#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.69)
AC_INIT(libsimplejsoncpp, 1.0, chenjiajun90@gmail.com)
AM_INIT_AUTOMAKE

# LT library
LT_INIT

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for header files.
AC_CHECK_HEADERS([wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE

AC_OUTPUT([Makefile
		src/Makefile
		src/util/Makefile
		src/json/entity/Makefile
		src/json/parser/Makefile])
