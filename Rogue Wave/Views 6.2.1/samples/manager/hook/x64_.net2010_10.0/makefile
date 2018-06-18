# --------------------------------------------------------------------------
#
#   Makefile for the 'hook' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x64_.net2010_10.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SYSTEM       = x64_.net2010_10.0
FORMAT       = dll_mda

CCC          = cl
COMPILERFLAGS= /c /DWIN64 /DIL_DLL /MD /nologo /W3 /EHsc /GR /D_CRT_SECURE_NO_DEPRECATE
LD           = link
LDFLAGS      = $(LDDBGFLAGS) /NOLOGO /SUBSYSTEM:WINDOWS /MACHINE:X64 /INCREMENTAL:NO	
OUTPUTFILE   = -Fo
RC           = rc
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



PROGRAMS     = magnify scalemgr

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# magnify
# --------------------------------------------------------------------------
magnify: magnify.exe
magnify.exe: magnify.obj viewsico.res
	-@IF EXIST magnify.exe DEL magnify.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvpng.lib ilvgadmgr.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ magnify.obj ilvmain.obj viewsico.res

magnify.obj: "$(ROOTDIR)\src\magnify.cpp"
	-@IF EXIST magnify.obj DEL magnify.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\magnify.cpp

# --------------------------------------------------------------------------
# scalemgr
# --------------------------------------------------------------------------
scalemgr: scalemgr.exe
scalemgr.exe: scalehk.obj scalemgr.obj viewsico.res
	-@IF EXIST scalemgr.exe DEL scalemgr.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ scalemgr.obj scalehk.obj ilvmain.obj viewsico.res

scalemgr.obj: "$(ROOTDIR)\src\scalemgr.cpp"
	-@IF EXIST scalemgr.obj DEL scalemgr.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\scalemgr.cpp

scalehk.obj: "$(ROOTDIR)\src\scalehk.cpp"
	-@IF EXIST scalehk.obj DEL scalehk.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\scalehk.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST magnify.obj DEL magnify.obj
	-@IF EXIST scalemgr.obj DEL scalemgr.obj
	-@IF EXIST scalehk.obj DEL scalehk.obj
	-@IF EXIST magnify.exe DEL magnify.exe
	-@IF EXIST scalemgr.exe DEL scalemgr.exe

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

