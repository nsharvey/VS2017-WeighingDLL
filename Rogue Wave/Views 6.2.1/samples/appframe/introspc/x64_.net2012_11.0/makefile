ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SYSTEM       = x64_.net2012_11.0
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



PROGRAMS     = introspc

all: $(PROGRAMS)
# ##########################################################################
# DocView Introspection mechanism
# ##########################################################################

INTROSPCOBJS  = execdlg.obj IntroView.obj IntroDocument.obj introcmd.obj

# --------------------------------------------------------------------------
introspc: introspc.exe
introspc.exe: $(INTROSPCOBJS) introspc.obj viewsico.res
	-@IF EXIST introspc.exe DEL introspc.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvappframe.lib ilvadvgdt.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ introspc.obj $(INTROSPCOBJS) ilvmain.obj viewsico.res

introspc.obj: "$(ROOTDIR)\src\introspc.cpp"
	-@IF EXIST introspc.obj DEL introspc.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\introspc.cpp

execdlg.obj: "$(ROOTDIR)\src\execdlg.cpp"
	-@IF EXIST execdlg.obj DEL execdlg.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\execdlg.cpp

IntroView.obj: "$(ROOTDIR)\src\IntroView.cpp"
	-@IF EXIST IntroView.obj DEL IntroView.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\IntroView.cpp

IntroDocument.obj: "$(ROOTDIR)\src\IntroDocument.cpp"
	-@IF EXIST IntroDocument.obj DEL IntroDocument.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\IntroDocument.cpp

introcmd.obj: "$(ROOTDIR)\src\introcmd.cpp"
	-@IF EXIST introcmd.obj DEL introcmd.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include"  $(CCFLAGS) $(ROOTDIR)\src\introcmd.cpp

# ##########################################################################
# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST introspc.obj DEL introspc.obj
	-@IF EXIST execdlg.obj DEL execdlg.obj
	-@IF EXIST IntroView.obj DEL IntroView.obj
	-@IF EXIST IntroDocument.obj DEL IntroDocument.obj
	-@IF EXIST introcmd.obj DEL introcmd.obj
	-@IF EXIST introspc.exe DEL introspc.exe

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

