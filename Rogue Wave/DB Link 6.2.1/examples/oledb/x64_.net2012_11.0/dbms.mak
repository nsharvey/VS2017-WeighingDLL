## ----------------------------------------------------------- -*- Makefile -*-
##
## This makefile contains the specific flags required to build an application
## for Oledb.
##
## ----------------------------------------------------------------------------

DBDIR=

DBMSCCFLAGS=-DILDOLEDB

OLEDB_DBLIB=dboledb.lib
OLEDB_LIBS=-LIBPATH:"$(SQLS_HOME)\100\SDK\Lib\x64" sqlncli10.lib oledb.lib comsuppw.lib

DBLIB=$(OLEDB_DBLIB)
DBMSLDFLAGS=$(OLEDB_LIBS)

ILDLIBS=-LIBPATH:"$(ILDLIBDIR)" $(DBLIB) dbkernel.lib dblnkst.lib ilddb.lib ilog.lib
ICULIBS=-LIBPATH:"$(ILDHOME)\lib\$(SYSTEM)\dll_mda" \
	icuio.lib icuin.lib icuuc.lib icutu.lib icudt.lib
