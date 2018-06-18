# --------------------------------------------------------------------------
#
#   Makefile for the 'layout' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x64_.net2015_14.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

STUDIODIR    = $(VIEWSDIR)\studio
STUDIOINCDIR = $(VIEWSDIR)\include
STUDIOLIBDIR = $(STUDIODIR)\$(SYSTEM)\$(FORMAT)

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



PROGRAMS	= inspector

all: $(PROGRAMS)

OTHEROBJS	= panel.obj
# --------------------------------------------------------------------------
# inspector
# --------------------------------------------------------------------------
inspector: inspector.exe
inspector.exe: $(OTHEROBJS) inspector.obj
	-@IF EXIST inspector.exe DEL inspector.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(STUDIOLIBDIR)" ilvstbus.lib ilvsttree.lib ilvsthierarchical.lib ilvbus.lib ilvhierarchical.lib ilvstrandom.lib ilvstorthlink.lib ilvorthlink.lib ilvstlayout.lib ilvstgrapher.lib ilvstappli.lib ilvstgadget.lib ivstudio.lib ilvprtdlg.lib ilvtree.lib ilvmgrprint.lib ilvbmpflt.lib ilvpng.lib ilvppm.lib ilvrandom.lib ilvgadgraph.lib ilvprint.lib ilvadvgadmgr.lib ilvstates.lib ilvedit.lib ilvgadmgr.lib ilvbmp.lib ilvlayout.lib ilvadvgdt.lib ilvgrapher.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(STUDIOSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ inspector.obj $(OTHEROBJS) ilvmain.obj

inspector.obj: "$(ROOTDIR)\src\inspector.cpp"
	-@IF EXIST inspector.obj DEL inspector.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ROOTDIR)\include" /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\inspector.cpp

panel.obj: "$(ROOTDIR)\src\panel.cpp"
	-@IF EXIST panel.obj DEL panel.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ROOTDIR)\include" /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\panel.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST inspector.obj DEL inspector.obj
	-@IF EXIST panel.obj DEL panel.obj
	-@IF EXIST inspector.exe DEL inspector.exe

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

