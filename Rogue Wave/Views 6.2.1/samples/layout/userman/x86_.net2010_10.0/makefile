# --------------------------------------------------------------------------
#
#   Makefile for the 'layout/userman' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x86_.net2010_10.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SYSTEM       = x86_.net2010_10.0
FORMAT       = dll_mda

CCC          = cl
COMPILERFLAGS= /c /DWIN32 /DIL_DLL /MD /nologo /W3 /EHsc /GR /D_CRT_SECURE_NO_DEPRECATE
LD           = link
LDFLAGS      = $(LDDBGFLAGS) /NOLOGO /SUBSYSTEM:WINDOWS /MACHINE:I386 /INCREMENTAL:NO	
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



PROGRAMS	= layoutsample1

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# layoutsample1
# --------------------------------------------------------------------------
layoutsample1: layoutsample1.exe
layoutsample1.exe: layoutsample1.obj viewsico.res
	-@IF EXIST layoutsample1.exe DEL layoutsample1.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvorthlink.lib ilvlayout.lib ilvgrapher.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ layoutsample1.obj ilvmain.obj viewsico.res

layoutsample1.obj: "$(ROOTDIR)\src\layoutsample1.cpp"
	-@IF EXIST layoutsample1.obj DEL layoutsample1.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ROOTDIR)\include" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\layoutsample1.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST layoutsample1.obj DEL layoutsample1.obj
	-@IF EXIST layoutsample1.exe DEL layoutsample1.exe

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

