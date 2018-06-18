# --------------------------------------------------------------------------
#
#   Makefile for the 'colorbox' Rogue Wave Views Studio Sample
#
# --------------------------------------------------------------------------
#   platform: x86_.net2015_14.0
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

SYSTEM       = x86_.net2015_14.0
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



PROGRAMS	= colorbox

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# colorbox
# --------------------------------------------------------------------------
colorbox: colorbox.exe
colorbox.exe: colorext.obj colorpnl.obj colorbox.obj maincbox.obj viewsico.res
	-@IF EXIST colorbox.exe DEL colorbox.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(STUDIOLIBDIR)" ilvstgenex.lib ilvstappli.lib ilvstgadget.lib ivstudio.lib ilvprtdlg.lib ilvmgrprint.lib ilvbmpflt.lib ilvpng.lib ilvppm.lib ilvprint.lib ilvadvgadmgr.lib ilvstates.lib ilvedit.lib ilvgadmgr.lib ilvbmp.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(STUDIOSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ maincbox.obj colorext.obj colorpnl.obj colorbox.obj ilvmain.obj viewsico.res

maincbox.obj: "$(ROOTDIR)\src\maincbox.cpp"
	-@IF EXIST maincbox.obj DEL maincbox.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\maincbox.cpp

colorext.obj: "$(ROOTDIR)\src\colorext.cpp"
	-@IF EXIST colorext.obj DEL colorext.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\colorext.cpp

colorpnl.obj: "$(ROOTDIR)\src\colorpnl.cpp"
	-@IF EXIST colorpnl.obj DEL colorpnl.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\colorpnl.cpp

colorbox.obj: "$(ROOTDIR)\src\colorbox.cpp"
	-@IF EXIST colorbox.obj DEL colorbox.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\colorbox.cpp


# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST maincbox.obj DEL maincbox.obj
	-@IF EXIST colorext.obj DEL colorext.obj
	-@IF EXIST colorpnl.obj DEL colorpnl.obj
	-@IF EXIST colorbox.obj DEL colorbox.obj
	-@IF EXIST colorbox.exe DEL colorbox.exe

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

