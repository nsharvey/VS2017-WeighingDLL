## ----------------------------------------------------------- -*- Makefile -*-
##
## This makefile contains the specific flags required to buld an application
## for Sybase.
##
## ----------------------------------------------------------------------------

DBDIR=$(SYBASE)\lib

DBMSCCFLAGS=-DILDSYBASE

SYB_DBLIB=ctsyb.lib
SYB_LIBS=libsybct.lib libsybcs.lib

DBLIB=$(SYB_DBLIB)
DBMSLDFLAGS=-LIBPATH:$(DBDIR) $(SYB_LIBS)

ILDLIBS=-LIBPATH:$(ILDLIBDIR) $(DBLIB) dbkernel.lib dblnkst.lib ilddb.lib ilog.lib
ICULIBS=-LIBPATH:$(ILDHOME)\lib\$(SYSTEM)\dll_mda \
	icuio.lib icuin.lib icutu.lib icuuc.lib icudt.lib
