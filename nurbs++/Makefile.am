EXTRA_DIST = config_mvc.bat
SUBDIRS= include matrix numerical image nurbs
EXTRA_SUBDIRS = examples
DIST_SUBDIRS = include matrix numerical image nurbs examples

dist-hook:
	cp -pr $(top_srcdir)/examples/vc6 $(distdir)/examples
	find $(distdir)/examples/vc6 -name CVS -exec rm -rf {} \; 
