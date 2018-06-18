## ----------------------------------------------------------- -*- Makefile -*-
## Purpose:
##
## This makefile compiles all the examples supplied with Rogue Wave DB Link.
##
## Note:
##       + To use this makefile, do the following:
##            % make clean ildsamples
##	 + Make sure the PATH variable contains the path to ICU
##	   libraries. Otherwise the link will fail.
##       + The variable ILDMODE sets the compiling mode of the DB Link library
##         the examples will be linking with.
## ----------------------------------------------------------------------------

SYSTEM=x86_.net2010_10.0
CCC=cl
LD=link
RM=-@erase

ILDMODDIR=dll_mda
ILDMODE=-MD

OEXT=obj
EEXT=.exe
OUT=-out:$@
ILDLIBDIR=..\..\..\lib\$(SYSTEM)\$(ILDMODDIR)

DBG=0
!if $(DBG)
DEBUG=-Od -Z7
LDDBG=-debug -fixed:no
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
DBMSLDFLAGS=
DBMSCCFLAGS=

ILDLIBS=-LIBPATH:"$(ILDLIBDIR)" dblinkdm.lib ilddb.lib ilog.lib
ICULIBS=-LIBPATH:"$(ILDLIBDIR)" \
	icuio.lib icuin.lib icutu.lib icuuc.lib icudt.lib

## --------------
## Targets
## --------------

TARGETS=blob$(EEXT) clob$(EEXT) datasmpl$(EEXT) fscroll$(EEXT) \
	ildbin$(EEXT) ildsql$(EEXT) ildtext$(EEXT) multidb$(EEXT) \
	readrel$(EEXT) rebindcl$(EEXT) relnames$(EEXT) \
	sample$(EEXT) sbinding$(EEXT) \
	smplbnd$(EEXT) testerr$(EEXT) trans$(EEXT) \
	oraproc$(EEXT) oracurs$(EEXT) ora8obj$(EEXT) \
	inf9obj$(EEXT) sybcomp$(EEXT) sybproc$(EEXT) sybtrig$(EEXT)

ildsamples : $(TARGETS)

# ----------------------
# Dependencies
# ----------------------

include ../../makefile.dbl
include ../makefile.spe

