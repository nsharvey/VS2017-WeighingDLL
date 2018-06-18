## ----------------------------------------------------------- -*- Makefile -*-
##
## This makefile compiles all the examples supplied with Rogue Wave DB Link.
##
## Note:
##       + Programs are compiled with the -DILDORACLE option.
##       + To use this makefile, do the following:
##            % make clean ildsamples
##       + The variable ILDMODE sets the compiling mode of the DB Link library
##         the examples will be linking with.
##       + The variable DBDIR sets the pathname to Oracle Libraries if needed
##       + Make sure the PATH variable contains the path to the ICU 
##         libraries. Otherwise the link will fail.
##
## ----------------------------------------------------------------------------

SYSTEM=x64_.net2017_15.0
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
LDDBG=-debug -assemblydebug
!else
DEBUG=-O2 -Ob2 -D NDEBUG
LDDBG=
!endif

SYSCCFLAGS=-nologo -W3 -GR -EHsc -D_CONSOLE -D_CRT_SECURE_NO_DEPRECATE
SYSLDFLAGS=kernel32.lib user32.lib wsock32.lib advapi32.lib -nologo \
-subsystem:console -machine:x64

# -----------------------
# RDBMS specific flags
# -----------------------

include dbms.mak

# -----------------------
# Targets
# -----------------------

TARGETS=datasmpl$(EEXT) blob$(EEXT) clob$(EEXT) fscroll$(EEXT) ildbin$(EEXT) \
	ildsql$(EEXT) ildtext$(EEXT) readrel$(EEXT) rebindcl$(EEXT) \
	relnames$(EEXT) sample$(EEXT) sbinding$(EEXT) smplbnd$(EEXT) \
	testerr$(EEXT) trans$(EEXT) 

ildsamples: $(TARGETS)

# ----------------------
# Dependencies
# ----------------------

include ../../makefile.dbl
include ../makefile.ora
