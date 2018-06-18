# --------------------------------------------------------------------------
#                                                                          
# Makefile for the s57 demo
#                                                                          
# --------------------------------------------------------------------------
#   platform: x86_.net2013_12.0
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

SYSTEM       = x86_.net2013_12.0
FORMAT       = dll_mda

CCC          = CL
COMPILERFLAGS= /c /DIL_DLL /MD /W3 /EHsc /GR /D_CRT_SECURE_NO_WARNINGS
LD           = LINK
LDFLAGS      = $(LDDBGFLAGS) /NOLOGO /SUBSYSTEM:WINDOWS /MACHINE:I386 /INCREMENTAL:NO
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


PROGRAMS     = s57viewer

all: $(PROGRAMS)


# --------------------------------------------------------------------------
s57viewer: s57viewer.exe
s57viewer.exe: gui.obj s57viewer.obj viewsico.res
	-@IF EXIST s57viewer.exe DEL s57viewer.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvpng.lib ilvmaps.lib ilvgadmgr.lib ilvtiff.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ s57viewer.obj gui.obj ilvmain.obj viewsico.res

s57viewer.obj: "$(ROOTDIR)\src\s57viewer.cpp"
	-@IF EXIST s57viewer.obj DEL s57viewer.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\s57viewer.cpp

gui.obj: "$(ROOTDIR)\src\gui.cpp"
	-@IF EXIST gui.obj DEL gui.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\gui.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST s57viewer.obj DEL s57viewer.obj
	-@IF EXIST gui.obj DEL gui.obj
	-@IF EXIST s57viewer.exe DEL s57viewer.exe

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

