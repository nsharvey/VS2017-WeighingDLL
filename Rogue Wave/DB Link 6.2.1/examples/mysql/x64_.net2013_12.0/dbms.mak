## ----------------------------------------------------------- -*- Makefile -*-
##
## This makefile contains the specific flags required to build an application
## for Oracle.
##
## ----------------------------------------------------------------------------

DBMSCCFLAGS=-DILDMYSQL

# MySQL 5.6
MYSQL_DBDIR=$(MYSQL_HOME)\lib
MYSQL_LIBS=mysqlclient.lib
MYSQL_DBLIB=dbmysql.lib

DBDIR=$(MYSQL_DBDIR)
MYSQLLIB=$(MYSQL_LIBS)
DBLIB=$(MYSQL_DBLIB)

DBMSLDFLAGS=-NODEFAULTLIB:LIBCMT -LIBPATH:$(DBDIR) $(MYSQLLIB)

ILDLIBS=-LIBPATH:"$(ILDLIBDIR)" $(DBLIB) dbkernel.lib dblnkst.lib ilddb.lib ilog.lib
ICULIBS=-LIBPATH:"$(ILDHOME)\lib\$(SYSTEM)\dll_mda" \
	icuio.lib icuin.lib icuuc.lib icutu.lib icudt.lib
