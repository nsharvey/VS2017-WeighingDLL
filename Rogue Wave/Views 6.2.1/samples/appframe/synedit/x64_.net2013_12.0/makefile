ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SYSTEM       = x64_.net2013_12.0
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



PROGRAMS     = synedit

all: $(PROGRAMS)
# ##########################################################################
# Synedit sample
# ##########################################################################

SYNEDITOBJS  = ProjectDocument.obj ProjectView.obj TextView.obj TreeView.obj docsynt.obj synode.obj synparse.obj

# --------------------------------------------------------------------------
synedit: synedit.exe
synedit.exe: $(SYNEDITOBJS) synedit.obj viewsico.res
	-@IF EXIST synedit.exe DEL synedit.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvappframe.lib ilvadvgdt.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ synedit.obj $(SYNEDITOBJS) ilvmain.obj viewsico.res

synedit.obj: "$(ROOTDIR)\src\synedit.cpp"
	-@IF EXIST synedit.obj DEL synedit.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\synedit.cpp

ProjectDocument.obj: "$(ROOTDIR)\src\ProjectDocument.cpp"
	-@IF EXIST ProjectDocument.obj DEL ProjectDocument.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\ProjectDocument.cpp

ProjectView.obj: "$(ROOTDIR)\src\ProjectView.cpp"
	-@IF EXIST ProjectView.obj DEL ProjectView.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\ProjectView.cpp

TextView.obj: "$(ROOTDIR)\src\TextView.cpp"
	-@IF EXIST TextView.obj DEL TextView.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\TextView.cpp

TreeView.obj: "$(ROOTDIR)\src\TreeView.cpp"
	-@IF EXIST TreeView.obj DEL TreeView.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\TreeView.cpp

docsynt.obj: "$(ROOTDIR)\src\docsynt.cpp"
	-@IF EXIST docsynt.obj DEL docsynt.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\docsynt.cpp

synode.obj: "$(ROOTDIR)\src\synode.cpp"
	-@IF EXIST synode.obj DEL synode.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\synode.cpp

synparse.obj: "$(ROOTDIR)\src\synparse.cpp"
	-@IF EXIST synparse.obj DEL synparse.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\synparse.cpp

# ##########################################################################
# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST synedit.obj DEL synedit.obj
	-@IF EXIST ProjectDocument.obj DEL ProjectDocument.obj
	-@IF EXIST ProjectView.obj DEL ProjectView.obj
	-@IF EXIST TextView.obj DEL TextView.obj
	-@IF EXIST TreeView.obj DEL TreeView.obj
	-@IF EXIST docsynt.obj DEL docsynt.obj
	-@IF EXIST synode.obj DEL synode.obj
	-@IF EXIST synparse.obj DEL synparse.obj
	-@IF EXIST synedit.exe DEL synedit.exe

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

