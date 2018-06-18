## ----------------------------------------------------------- -*- Makefile -*-
##
## This makefile contains the specific flags required to build an application
## for Odbc.
##
## ----------------------------------------------------------------------------

DBDIR=

DBMSCCFLAGS=-DILDODBC

ODBC_DBLIB=dbodbc.lib
ODBC_LIBS=odbc32.lib

DBLIB=$(ODBC_DBLIB)
DBMSLDFLAGS=$(ODBC_LIBS)

ILDLIBS=-LIBPATH:"$(ILDLIBDIR)" $(DBLIB) dbkernel.lib dblnkst.lib ilddb.lib ilog.lib
ICULIBS=-LIBPATH:"$(ILDHOME)\lib\$(SYSTEM)\dll_mda" \
	icuio.lib icuin.lib icuuc.lib icutu.lib icudt.lib
