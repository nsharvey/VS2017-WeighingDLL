## ----------------------------------------------------------- -*- Makefile -*-
##
## This makefile compiles all the examples supplied with Rogue Wave DB Link.
##
## Note:
##       + Programs are compiled with the -DILDSYBASE option.
##       + To use this makefile, do the following:
##            % nmake clean ildsamples
##       + The variable ILDMODE sets the compiling mode of the DB Link library
##         the examples will be linking with.
##       + The variable DBDIR sets the pathname to Sybase Libraries
##       + Make sure the PATH variable contains the path to the ICU 
##         libraries. Otherwise the link will fail.
##
## ----------------------------------------------------------------------------

SYSTEM=x86_.net2017_15.0
CCC=cl
LD=link
RM=-@erase

OEXT=obj
EEXT=.exe
OUT=-out:$@

ILDMODDIR=stat_mda
ILDMODE=-MD

ILDLIBDIR=..\..\..\lib\$(SYSTEM)\$(ILDMODDIR)

DBG=0
!if $(DBG)
DEBUG=-Od -Z7
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

TARGETS=datasmpl$(EEXT) ildbin$(EEXT) ildsql$(EEXT) ildtext$(EEXT) \
	multidb$(EEXT) readrel$(EEXT) rebindcl$(EEXT) \
	relnames$(EEXT) sample$(EEXT) sbinding$(EEXT) smplbnd$(EEXT) \
	testerr$(EEXT) trans$(EEXT) \
	blob$(EEXT) clob$(EEXT) sybtrig$(EEXT) sybproc$(EEXT) sybcomp$(EEXT)

ildsamples: $(TARGETS)

# ----------------------
# Dependencies
# ----------------------

include ../../makefile.dbl
include ../makefile.syb
