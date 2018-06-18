## ----------------------------------------------------------- -*- Makefile -*-
## Purpose:
## 
## This makefile contains the specific flags required to buld an application
## for DB2 on a Win64 platform.
##
## ----------------------------------------------------------------------------

DBDIR="$(DB2PATH)\lib"

DBMSCCFLAGS=-DILDDB2

DB2_DBLIB=dbdb2.lib
DB2_LIBS=-LIBPATH:$(DBDIR) db2cli64.lib

DB29X_DBLIB=dbdb29x.lib
DB29X_LIBS=-LIBPATH:$(DBDIR) db2cli64.lib

DBLIB=$(DB29X_DBLIB)
DBMSLDFLAGS=$(DB29X_LIBS)

ILDLIBS=-LIBPATH:"$(ILDLIBDIR)" dbkernel.lib dblnkst.lib ilddb.lib ilog.lib $(DBLIB)
## ICU libraries are only in dll mode
ICULIBS=-LIBPATH:"$(ILDHOME)\lib\$(SYSTEM)\dll_mda" \
	icuio.lib icuin.lib icuuc.lib icutu.lib
