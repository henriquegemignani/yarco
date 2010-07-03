#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(Yarco, 1.0)
AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_YACC
AC_PROG_CC
AC_PROG_LEX

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lfl':
AC_CHECK_LIB([fl], [main])
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h sys/time.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_TIME

# Checks for library functions.
AC_CHECK_FUNCS([gettimeofday sqrt strcasecmp])

AC_CONFIG_FILES([Makefile
                 config/Makefile])
AC_OUTPUT
