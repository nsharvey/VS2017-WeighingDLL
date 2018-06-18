## ----------------------------------------------------------- -*- Makefile -*-
##
## This makefile compiles all the examples supplied with Rogue Wave DB Link.
##
## Note:
##       + Programs are compiled with the -DILDMYSQL option.
##
##       + To use this makefile, do the following:
##
##            % make clean all
##
##       + The variable ILDMODE sets the compiling mode of the DB Link library
##         the examples will be linking with.
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
DEBUG=-Od -ZI -D _DEBUG
LDDBG=-debug -assemblydebug
!else
DEBUG=-O2 -Ob2 -D NDEBUG
LDDBG=
!endif

SYSCCFLAGS=-nologo -W3 -GR -EHsc -D _CONSOLE -D _CRT_SECURE_NO_DEPRECATE

SYSLDFLAGS=kernel32.lib user32.lib wsock32.lib advapi32.lib \
  -nologo -subsystem:console -machine:x86 $(LDDBG)

include dbms.mak

#############################################################################
# Targets
#############################################################################

TARGETS=blob$(EEXT) clob$(EEXT) datasmpl$(EEXT) fscroll$(EEXT) \
	ildbin$(EEXT) ildsql$(EEXT) ildtext$(EEXT) multidb$(EEXT) \
	readrel$(EEXT) rebindcl$(EEXT) relnames$(EEXT) \
	sample$(EEXT) sbinding$(EEXT) smplbnd$(EEXT) testerr$(EEXT) \
	trans$(EEXT)

ildsamples: $(TARGETS)

# ----------------------
# Dependencies
# ----------------------

include ../../makefile.dbl

include ../makefile.mysql
