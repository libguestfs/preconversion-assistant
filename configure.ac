# Preconversion assistant
# Copyright (C) 2026 Red Hat Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

AC_INIT([pca],0.0.1)

# Headings within the configure script output.
term_bold=""
term_red=""
term_green=""
term_restore=""
AS_IF([test -t 1], [
    AS_CASE(["$TERM"],
            [xterm*|vt220*], [
              term_bold="$(printf "\e@<:@1m")"
              term_red="$(printf "\e@<:@22;31m")"
              term_green="$(printf "\e@<:@22;32m")"
              term_restore="$(printf "\e@<:@0m")"
    ])
])
m4_define([HEADING],
          [AS_ECHO
           AS_ECHO(["${term_bold}$1${term_restore}"])])

HEADING([Checking for C compiler and basic build environment])

AC_CONFIG_AUX_DIR([build-aux])

AC_USE_SYSTEM_EXTENSIONS

dnl Initialize automake.
dnl NB: Do not [quote] this parameter.
AM_INIT_AUTOMAKE(foreign tar-pax)

m4_ifndef([AM_SILENT_RULES], [m4_define([AM_SILENT_RULES],[])])
AM_SILENT_RULES([yes]) # make --enable-silent-rules the default.

AC_CONFIG_MACRO_DIR([m4])

dnl Extra string, a freeform string defined by packagers.
AC_ARG_WITH([extra],
    [AS_HELP_STRING([--with-extra],
                    [extra version string (for use by packagers)])],
    [extra="$withval"],
    [extra=]
)
AC_MSG_NOTICE([Virt-v2v / QEMU Preconversion Assistant version $PACKAGE_VERSION$extra])

AC_DEFINE_UNQUOTED([PACKAGE_VERSION_EXTRA],["$extra"],[Extra version string.])
PACKAGE_VERSION_FULL="$PACKAGE_VERSION$extra"
AC_DEFINE_UNQUOTED([PACKAGE_VERSION_FULL],["$PACKAGE_VERSION_FULL"],[Full version string.])
AC_SUBST([PACKAGE_VERSION_FULL])

HEADING([Checking for the C compiler environment])
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_CPP
AC_SYS_LARGEFILE

AC_C_PROTOTYPES
test "x$U" != "x" && AC_MSG_ERROR([Compiler not ANSI compliant])

AM_PROG_CC_C_O

dnl The C++ compiler test is pretty useless because even if it fails
dnl it sets CXX=g++.  So test the compiler actually works.
AC_MSG_CHECKING([if the C++ compiler really really works])
AS_IF([$CXX --version >&AS_MESSAGE_LOG_FD 2>&1],[have_cxx=yes],[have_cxx=no])
AC_MSG_RESULT([$have_cxx])
AM_CONDITIONAL([HAVE_CXX], [test "$have_cxx" = "yes"])

dnl If --enable-compiler-warnings is used, then compiler warnings are
dnl turned on.
AC_ARG_ENABLE([compiler-warnings],
    [AS_HELP_STRING([--enable-compiler-warnings],
                    [turn on compiler warnings (for developers)])],
     [case $enableval in
      yes|no) ;;
      *)      AC_MSG_ERROR([bad value $enableval for compiler-warnings option]) ;;
      esac
      compiler_warnings=$enableval],
      [compiler_warnings=no]
)
if test "x$compiler_warnings" = "xyes"; then
    WARNINGS_CFLAGS="-Wall -Wshadow -Wvla -Werror"
    AC_SUBST([WARNINGS_CFLAGS])
fi
AM_CONDITIONAL([COMPILER_WARNINGS], [test "$compiler_warnings" = "yes"])

dnl Define the host CPU architecture (defines 'host_cpu').
AC_CANONICAL_HOST
AC_DEFINE_UNQUOTED([host_cpu],["$host_cpu"],[Host architecture.])

dnl Define 'host_os'.
AC_DEFINE_UNQUOTED([host_os],["$host_os"],[Host operating system.])

AC_MSG_CHECKING([if this is Linux or Windows])
AS_CASE([$host_os],
    [linux-gnu],    [
        what_is=linux
        SOEXT=so
    ],
    [mingw*|msys*], [
        what_is=windows
        SOEXT=dll
    ],
    [ AC_MSG_ERROR([Unknown host operating system ($host_os)]) ]
)
AC_MSG_RESULT([$what_is])
AM_CONDITIONAL([LINUX],[test "x$what_is" = "xlinux"])
AM_CONDITIONAL([WINDOWS],[test "x$what_is" = "xwindows"])

AC_DEFINE_UNQUOTED([EXEEXT],["$EXEEXT"],[Extension used for executables.])
AC_DEFINE_UNQUOTED([SOEXT],["$SOEXT"],[Extension used for shared objects/DLLs.])

HEADING([Checking for external programs])

HEADING([Checking for Perl and podwrapper dependencies])
AC_CHECK_PROG([PERL],[perl],[perl],[no])
test "x$PERL" = "xno" &&
    AC_MSG_ERROR([perl must be installed])

dnl Check for Pod::Man, Pod::Simple (for man pages).
AC_MSG_CHECKING([for Pod::Man])
if ! $PERL -MPod::Man -e1 >&AS_MESSAGE_LOG_FD 2>&1; then
    AC_MSG_ERROR([perl Pod::Man must be installed])
else
    AC_MSG_RESULT([yes])
fi
AC_MSG_CHECKING([for Pod::Simple])
if ! $PERL -MPod::Simple -e1 >&AS_MESSAGE_LOG_FD 2>&1; then
    AC_MSG_ERROR([perl Pod::Simple must be installed])
else
    AC_MSG_RESULT([yes])
fi
PODWRAPPER="$(pwd)/podwrapper.pl"
AC_SUBST([PODWRAPPER])

HEADING([Checking for libraries])

dnl Produce output files.
HEADING([Generating output files])

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([podwrapper.pl],
                [chmod +x,-w podwrapper.pl])
AC_CONFIG_FILES([run],
                [chmod +x,-w run])

AC_CONFIG_FILES([Makefile
                 linux/Makefile
                 windows/Makefile])

AC_OUTPUT

dnl Produce summary.
echo
echo
echo "------------------------------------------------------------"
HEADING([Thank you for downloading $PACKAGE_STRING])
echo
echo "This is how we have configured the optional components for you today:"
echo

print ()
{
    printf '    %.40s %s\n' \
        "$1 ........................................" "$2"
}

feature ()
{
    feat="$1"
    shift
    if "$@"; then
        printf "$term_green"
        print "$feat" "yes"
    else
        printf "$term_red"
        print "$feat" "no"
    fi
    printf "$term_restore"
}

#...

echo
echo "If any optional component is configured 'no' when you expected 'yes'"
echo "then you should check the preceding messages."
echo
echo "Please report bugs back to the mailing list:"
echo "https://lists.libguestfs.org"
echo
echo "Next you should type 'make' to build the package."
echo "------------------------------------------------------------"
