AUTOMAKE_OPTIONS = 1.4
ACLOCAL_AMFLAGS = -I config

SUBDIRS= include matrix numerical image nurbs tests
EXTRA_SUBDIRS = examples
DIST_SUBDIRS = include matrix numerical image nurbs examples

bin_SCRIPTS = nurbs++-config
man_MANS = nurbs++-config.1

EXTRA_DIST = config_mvc.bat \
	nurbs++-config.1

dist-hook:
	cp -pr $(top_srcdir)/examples/vc6 $(distdir)/examples
	find $(distdir)/examples/vc6 -name CVS -exec rm -rf {} \; 

m4sources = \
	config/has_image_magick.m4 \
	config/has_cppunit.m4

m4datadir = $(datadir)/aclocal
#m4data_DATA = nurbs++.m4

