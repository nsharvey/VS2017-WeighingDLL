## ----------------------------------------------------------- -*- Makefile -*-
##
## This makefile contains the specific flags required to build an application
## for Oracle.
##
## ----------------------------------------------------------------------------

DBMSCCFLAGS=-DILDORACLE

# Default :
DBLIB=dbora.lib

DBMSLDFLAGS=-LIBPATH:$(ORACLE_HOME)\oci\lib\msvc oci.lib

ILDLIBS=-LIBPATH:"$(ILDLIBDIR)" $(DBLIB) dbkernel.lib dblnkst.lib ilddb.lib ilog.lib
ICULIBS=-LIBPATH:"$(ILDHOME)\lib\$(SYSTEM)\dll_mda" \
	icuio.lib icuin.lib icuuc.lib icutu.lib icudt.lib
