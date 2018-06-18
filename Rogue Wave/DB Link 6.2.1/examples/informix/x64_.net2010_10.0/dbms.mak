## ----------------------------------------------------------- -*- Makefile -*-
##
## This makefile contains the specific flags required to build an application
## for Informix.
##
## ---------------------------------------------------------------------------

DBDIR="$(INFORMIXDIR)\lib"

DBMSCCFLAGS=-DILDINFORMIX

INF9_DBLIB=dbinf9.lib
INF9_LIBS=isqlt09a.lib

DBLIB=$(INF9_DBLIB)
DBMSLDFLAGS=-LIBPATH:$(DBDIR) $(INF9_LIBS)

ILDLIBS=-LIBPATH:"$(ILDLIBDIR)" $(DBLIB) dbkernel.lib dblnkst.lib ilddb.lib ilog.lib
ICULIBS=-LIBPATH:"$(ILDHOME)\lib\$(SYSTEM)\dll_mda" \
	icuio.lib icuin.lib icuuc.lib icutu.lib icudt.lib
