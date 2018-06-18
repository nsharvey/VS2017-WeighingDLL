## ----------------------------------------------------------- -*- Makefile -*-
## Purpose:
##
## This makefile compiles all the examples supplied with Rogue Wave DB Link.
##
## Note:
##       + Programs are compiled with the -DILDINFORMIX option.
##       + To use this makefile, do the following:
##            % nmake clean ildsamples
##       + The variable ILDMODE sets the compiling mode of the DB Link library
##         the examples will be linking with.
##       + The variable DBDIR sets the pathname to Informix Libraries
##       + Make sure the LD_LIBRARY_PATH variable contains the path to the ICU 
##         libraries. Otherwise the link will fail.
##
## ----------------------------------------------------------------------------

SYSTEM=x86_.net2013_12.0
CCC=cl
LD=link
RM=-@erase

ILDMODDIR=stat_mda
ILDMODE=-MD

OEXT=obj
EEXT=.exe
OUT=-out:$@

ILDLIBDIR=..\..\..\lib\$(SYSTEM)\$(ILDMODDIR)

DBG=0
!if $(DBG)
DEBUG=-Od -ZI
LDDBG=-debug
!else
DEBUG=-O2 -Ob2 -D NDEBUG
LDDBG=
!endif

SYSCCFLAGS=-nologo -W3 -GR -EHsc -D_CONSOLE -D_CRT_SECURE_NO_DEPRECATE
SYSLDFLAGS=kernel32.lib user32.lib wsock32.lib advapi32.lib -nologo \
 -subsystem:console -machine:x86

# -----------------------
# RDBMS specific flags
# -----------------------

include dbms.mak

# -----------------------
# Targets
# -----------------------
TARGETS=blob$(EEXT) clob$(EEXT) fscroll$(EEXT) ildbin$(EEXT) \
	ildsql$(EEXT) ildtext$(EEXT) multidb$(EEXT) readrel$(EEXT) \
	rebindcl$(EEXT) relnames$(EEXT) sample$(EEXT) sbinding$(EEXT) \
	smplbnd$(EEXT) testerr$(EEXT) trans$(EEXT) datasmpl$(EEXT) \
	blob$(EEXT) clob$(EEXT) inf9obj$(EEXT) infproc$(EEXT)

ildsamples: $(TARGETS)

# ----------------------
# Dependencies
# ----------------------

include ../../makefile.dbl
include ../makefile.inf
