ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

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



PROGRAMS     = manager

all: $(PROGRAMS)
# ##########################################################################
# Manager sample
# ##########################################################################

MANAGEROBJS  = ManagerView.obj ManagerDocument.obj mgercmd.obj selinter.obj

# --------------------------------------------------------------------------
manager: manager.exe
manager.exe: $(MANAGEROBJS) manager.obj viewsico.res
	-@IF EXIST manager.exe DEL manager.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvappmgr.lib ilvappframe.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ manager.obj $(MANAGEROBJS) ilvmain.obj viewsico.res

manager.obj: "$(ROOTDIR)\src\manager.cpp"
	-@IF EXIST manager.obj DEL manager.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" -DILVDVMGR  $(CCFLAGS) $(ROOTDIR)\src\manager.cpp

ManagerView.obj: "$(ROOTDIR)\src\ManagerView.cpp"
	-@IF EXIST ManagerView.obj DEL ManagerView.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" -DILVDVMGR  $(CCFLAGS) $(ROOTDIR)\src\ManagerView.cpp

ManagerDocument.obj: "$(ROOTDIR)\src\ManagerDocument.cpp"
	-@IF EXIST ManagerDocument.obj DEL ManagerDocument.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" -DILVDVMGR  $(CCFLAGS) $(ROOTDIR)\src\ManagerDocument.cpp

mgercmd.obj: "$(ROOTDIR)\src\mgercmd.cpp"
	-@IF EXIST mgercmd.obj DEL mgercmd.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" -DILVDVMGR  $(CCFLAGS) $(ROOTDIR)\src\mgercmd.cpp

selinter.obj: "$(ROOTDIR)\src\selinter.cpp"
	-@IF EXIST selinter.obj DEL selinter.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" -DILVDVMGR  $(CCFLAGS) $(ROOTDIR)\src\selinter.cpp

# ##########################################################################
# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST manager.obj DEL manager.obj
	-@IF EXIST ManagerView.obj DEL ManagerView.obj
	-@IF EXIST ManagerDocument.obj DEL ManagerDocument.obj
	-@IF EXIST mgercmd.obj DEL mgercmd.obj
	-@IF EXIST selinter.obj DEL selinter.obj
	-@IF EXIST manager.exe DEL manager.exe

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

