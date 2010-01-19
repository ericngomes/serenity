bin_PROGRAMS = serenity
noinst_LTLIBRARIES = libserenity.la

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)s/locale"\"	\
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\"				\
	-DPACKAGE_DATA_DIR=\""$(datadir)"\"				\
	-DPACKAGE_LIB_DIR=\""$(libdir)"\"				\
	-DGETTEXT_PACKAGE=\""serenity"\"				\
	-DHAVE_CONFIG_H							\
	-DG_LOG_DOMAIN=\"Serenity\"					\
	-DSERENE_COMPILATION						\
	$(SERENITY_CFLAGS)						\
	$(NULL)

AM_LDFLAGS = $(SERENITY_LIBS)

INST_H_FILES =								\
	serenity.h							\
	serenity-document.h						\
	serenity-panels.h						\
	serenity-paths.h						\
	serenity-prefs.h						\
	serenity-runtime.h						\
	serenity-window.h						\
	serenity-version.h						\
	$(NULL)

libserenity_la_SOURCES =						\
	$(INST_H_FILES)							\
	serenity-document.c						\
	serenity-panels.c						\
	serenity-paths.c						\
	serenity-prefs.c						\
	serenity-runtime.c						\
	serenity-window.c						\
	$(NULL)

headerdir = $(prefix)/include/serenity-1.0/serenity
header_DATA = $(INST_H_FILES)

serenity_SOURCES = serenity.c
serenity_LDADD = libserenity.la
serenity_LDFLAGS =							\
	-export-dynamic							\
	-no-undefined							\
	-export-symbols-regex "^serenity_.*"				\
	$(NULL)

test:
	SERENITY_DATA_PATH=$(top_srcdir)/data $(builddir)/serenity
