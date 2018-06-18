## ----------------------------------------------------------- -*- Makefile -*-
##
## This makefile contains the specific flags required to build an application
## for MySQL.
##
## ----------------------------------------------------------------------------

# -----------------------
# RDBMS specific flags
# -----------------------

DBMSCCFLAGS=-DILDMYSQL

# MySQL 5.6
MYSQL_DBDIR="$(MYSQL_HOME)"\lib
MYSQL_DBLIB=dbmysql.lib

MYSQL_LIBS=-NODEFAULTLIB:LIBCMT -LIBPATH:$(MYSQL_DBDIR) mysqlclient.lib

# 
DBDIR=$(MYSQL_DBDIR)
DBLIB=$(MYSQL_DBLIB)

DBMSLDFLAGS=$(MYSQL_LIBS)

ILDLIBS=-LIBPATH:$(ILDLIBDIR) $(DBLIB) dbkernel.lib dblnkst.lib ilddb.lib ilog.lib
ICULIBS=-LIBPATH:"$(ILDHOME)\lib\$(SYSTEM)\dll_mda" \
	icuio.lib icuin.lib icuuc.lib icutu.lib icudt.lib

