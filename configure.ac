dnl ************************************************************************
dnl Versioning
dnl ************************************************************************
m4_define([serenity_major_version], [0])
m4_define([serenity_minor_version], [1])
m4_define([serenity_micro_version], [1])
m4_define([serenity_version],
          [serenity_major_version.serenity_minor_version.serenity_micro_version])
m4_define([serenity_binary_age], [m4_eval(100 * serenity_minor_version +
           serenity_micro_version)])
m4_define([lt_current], [m4_eval(100 * serenity_minor_version +
           serenity_micro_version - serenity_interface_age)])
m4_define([lt_revision], [serenity_interface_age])
m4_define([lt_age], [m4_eval(serenity_binary_age - serenity_interface_age)])
SERENITY_MAJOR_VERSION=serenity_major_version
SERENITY_MINOR_VERSION=serenity_minor_version
SERENITY_MICRO_VERSION=serenity_micro_version


dnl ************************************************************************
dnl Initialize Automake
dnl ************************************************************************
AC_INIT(serenity, serenity_version)
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([build/m4])
AM_MAINTAINER_MODE
AC_ISC_POSIX
AC_PROG_CC
AC_PROG_CC_STDC
AC_HEADER_STDC
AM_PATH_GLIB_2_0
AC_SUBST(SERENITY_MAJOR_VERSION)
AC_SUBST(SERENITY_MAJOR_VERSION)
AC_SUBST(SERENITY_MAJOR_VERSION)


dnl ************************************************************************
dnl Check for Required Modules
dnl ************************************************************************
PKG_CHECK_MODULES(SERENITY, [gobject-2.0 >= 2.20
                             gthread-2.0 >= 2.20
                             gio-2.0 >= 2.20
                             clutter-1.0 >= 1.0
                             clutter-gtk-0.10 >= 0.10.2])


dnl ************************************************************************
dnl Unit Tests
dnl ************************************************************************
AC_PATH_PROG([GTESTER], [gtester])
AC_PATH_PROG([GTESTER_REPORT], [gtester-report])
AM_CONDITIONAL(ENABLE_GLIB_TEST, test "x$enable_glibtest" = "xyes")


dnl ************************************************************************
dnl Miscellaneous
dnl ************************************************************************
AM_PROG_LIBTOOL
GTK_DOC_CHECK([1.11])
SHAVE_INIT([build], [enable])
SHAMROCK_EXPAND_LIBDIR
SHAMROCK_EXPAND_BINDIR
SHAMROCK_EXPAND_DATADIR


dnl ************************************************************************
dnl Output
dnl ************************************************************************
AC_OUTPUT([
	Makefile
	build/shave
	build/shave-libtool
	data/Makefile
	data/dbus/Makefile
	doc/Makefile
	doc/reference/Makefile
	tests/Makefile

	doc/reference/serenity/Makefile
	doc/reference/serenity/version.xml
	serenity/Makefile
	serenity/serenity-version.h
])

echo ""
echo "Serenity $VERSION"
echo ""
echo "  Prefix.....................: ${prefix}"
echo "  Enable API Reference.......: ${enable_gtk_doc}"
echo "  Enable Test Suite..........: ${enable_glibtest}"
echo ""
