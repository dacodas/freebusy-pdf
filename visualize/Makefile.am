bin_PROGRAMS = freebusy

ACLOCAL_AMFLAGS = -I gl/m4

SUBDIRS = gl

freebusy_SOURCES = src/busy.c src/text.c src/measurements.h src/strokeHelper.c.in src/measurements.c src/drawDays.h src/drawDays.c src/text.h src/specification.h src/settings.c src/main.c src/settings.h src/specification.c src/busy.h

freebusy_CPPFLAGS = -I${HOME}/projects/mailbox/freebusy/visualize/src

freebusy_CFLAGS = -I${HOME}/projects/mailbox/freebusy/visualize/src

freebusy_LDFLAGS = -lcairo -lical

dist_doc_DATA = README.md
