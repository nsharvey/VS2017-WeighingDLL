# --------------------------------------------------------------------------
#                                                                          
# Makefile for the image projection demo
#                                                                          
# --------------------------------------------------------------------------
#   platform: x64_.net2015_14.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ILVHOME)
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

ILVMAPSDIR   = $(ILVMAPSHOME)
ILVMAPSINCDIR= $(ILVMAPSDIR)\include
ILVMAPSLIBDIR= $(ILVMAPSDIR)\lib\$(SYSTEM)\$(FORMAT)

DBLINKDIR    = $(ILDHOME)
DBLINKINCDIR = $(DBLINKDIR)\include
DBLINKLIBDIR = $(DBLINKDIR)\lib\$(SYSTEM)\$(FORMAT)

SYSTEM       = x64_.net2015_14.0
FORMAT       = dll_mda

CCC          = CL
COMPILERFLAGS= /c /DIL_DLL /MD /W3 /EHsc /GR /D_CRT_SECURE_NO_WARNINGS
LD           = LINK
LDFLAGS      = $(LDDBGFLAGS) /NOLOGO /SUBSYSTEM:WINDOWS /MACHINE:X64 /INCREMENTAL:NO	
OUTPUTFILE   = -Fo
RC           = RC
RCFLAGS      = /c1252 /I"$(VIEWSDIR)\data\res" $(RCDEFINES)
SYSLIBS      = winspool.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib shell32.lib advapi32.lib wsock32.lib imm32.lib

# Debug options:
DEBUG        = 0
LDDEBUG      = 0
!if $(DEBUG)
DEBUGFLAGS   = /Zi /Od 
OPTIMFLAGS   = $(DEBUGFLAGS) 
LDDEBUG      = 1
RCDEFINES    = /d_DEBUG
!else
DEBUGFLAGS   =  
RCDEFINES    = /dNDEBUG
OPTIMFLAGS   = /Gs /O1
!endif
!if $(LDDEBUG)
LDDBGFLAGS   = /debug /DEBUGTYPE:CV /PDB:$*.pdb
!else
LDDBGFLAGS   = 
!endif

CCFLAGSSYS   = $(DEBUGFLAGS) $(COMPILERFLAGS)
CCVIEWSFLAGS = -DILVNODEFAULTLOOK
CCFLAGS      = $(OPTIMFLAGS) $(COMPILERFLAGS) $(CCVIEWSFLAGS)
ALLSYSLIBS   = $(ADDLIBS) $(BIDILIBS) $(SYSLIBS)


ILVMAPSDIR = $(ROOTDIR)\..\..\..

# CCFLAGSPROJ = -DILDORACLE

DBLINKLIBDIR=$(ILDHOME)\lib\$(SYSTEM)\$(FORMAT)

PROGRAMS     = sdosample

all: $(PROGRAMS)

#
# sdosample
#


# --------------------------------------------------------------------------
sdosample: sdosample.exe
sdosample.exe: mysdopan.obj sdopan.obj defdbmsfact.obj sdosample.obj viewsico.res
	-@IF EXIST sdosample.exe DEL sdosample.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(DBLINKLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvpng.lib ilvdbmaps.lib ilvmaps.lib ilvgadmgr.lib ilvtiff.lib dblnkdyn.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib dbkernel.lib views.lib winviews.lib ilog.lib ilddb.lib $(VIEWSMAPSSYSLIBS) $(DBLINKSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ sdosample.obj mysdopan.obj sdopan.obj defdbmsfact.obj ilvmain.obj viewsico.res

sdosample.obj: "$(ROOTDIR)\src\sdosample.cpp"
	-@IF EXIST sdosample.obj DEL sdosample.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ILDHOME)\include" /I"..\include" /I"$(DBLINKINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\sdosample.cpp

defdbmsfact.obj: "$(ROOTDIR)\src\defdbmsfact.cpp"
	-@IF EXIST defdbmsfact.obj DEL defdbmsfact.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ILDHOME)\include" /I"..\include" /I"$(DBLINKINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\defdbmsfact.cpp

mysdopan.obj: "$(ROOTDIR)\src\mysdopan.cpp"
	-@IF EXIST mysdopan.obj DEL mysdopan.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ILDHOME)\include" /I"..\include" /I"$(DBLINKINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\mysdopan.cpp

sdopan.obj: "$(ROOTDIR)\src\sdopan.cpp"
	-@IF EXIST sdopan.obj DEL sdopan.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ILDHOME)\include" /I"..\include" /I"$(DBLINKINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\sdopan.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST sdosample.obj DEL sdosample.obj
	-@IF EXIST defdbmsfact.obj DEL defdbmsfact.obj
	-@IF EXIST mysdopan.obj DEL mysdopan.obj
	-@IF EXIST sdopan.obj DEL sdopan.obj
	-@IF EXIST sdosample.exe DEL sdosample.exe

# --------------------------------------------------------------------------
viewsico.res: "$(VIEWSRESDIR)\viewsico.rc"
	$(RC) $(RCFLAGS) /I"$(VIEWSRESDIR)" -r -foviewsico.res "$(VIEWSRESDIR)\viewsico.rc"


# --------------------------------------------------------------------------
clean: clean1
	-@IF EXIST *.ncb DEL *.ncb
	-@IF EXIST *.pdb DEL *.pdb
	-@IF EXIST *.ilk DEL *.ilk
	-@IF EXIST *.idb DEL *.idb
	-@IF EXIST *.plg DEL *.plg
	-@IF EXIST *.map DEL *.map
	-@IF EXIST *.res DEL *.res
	-@IF EXIST *.bak DEL *.bak
	-@IF EXIST *.lnk DEL *.lnk

