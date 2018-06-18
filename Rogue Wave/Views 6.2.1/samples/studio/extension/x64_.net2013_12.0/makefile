# --------------------------------------------------------------------------
#
#   Makefile for the 'studio' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x64_.net2013_12.0
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



PROGRAMS	= mystudio

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# mystudio
# --------------------------------------------------------------------------
mystudio: mystudio.exe
mystudio.exe: myclass.obj myinter.obj myclinsp.obj mybuf.obj myman.obj mycont.obj myutil.obj mypan.obj myext.obj mymain.obj ivfstudio.res
	-@IF EXIST mystudio.exe DEL mystudio.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(STUDIOLIBDIR)" ilvstgenex.lib ilvstappli.lib ilvstgadget.lib ivstudio.lib ilvprtdlg.lib ilvmgrprint.lib ilvbmpflt.lib ilvpng.lib ilvppm.lib ilvprint.lib ilvadvgadmgr.lib ilvstates.lib ilvedit.lib ilvgadmgr.lib ilvbmp.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(STUDIOSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ mymain.obj myclass.obj myinter.obj myclinsp.obj mybuf.obj myman.obj mycont.obj myutil.obj mypan.obj myext.obj ilvmain.obj ivfstudio.res

mymain.obj: "$(ROOTDIR)\src\mymain.cpp"
	-@IF EXIST mymain.obj DEL mymain.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\mymain.cpp

# --------------------------------------------------------------------------
ivfstudio.res: $(VIEWSDIR)\studio\data\res\ivfstudio.rc
	$(RC) $(RCFLAGS) -r -foivfstudio.res /I$(VIEWSDIR)\data /I$(VIEWSDIR)\data\icon /I$(VIEWSDIR)\data\res /I$(STUDIODIR)\data\res $(VIEWSDIR)\studio\data\res\ivfstudio.rc

myclass.obj: "$(ROOTDIR)\src\myclass.cpp"
	-@IF EXIST myclass.obj DEL myclass.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\myclass.cpp

myinter.obj: "$(ROOTDIR)\src\myinter.cpp"
	-@IF EXIST myinter.obj DEL myinter.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\myinter.cpp

myclinsp.obj: "$(ROOTDIR)\src\myclinsp.cpp"
	-@IF EXIST myclinsp.obj DEL myclinsp.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\myclinsp.cpp

mybuf.obj: "$(ROOTDIR)\src\mybuf.cpp"
	-@IF EXIST mybuf.obj DEL mybuf.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\mybuf.cpp

myman.obj: "$(ROOTDIR)\src\myman.cpp"
	-@IF EXIST myman.obj DEL myman.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\myman.cpp

mycont.obj: "$(ROOTDIR)\src\mycont.cpp"
	-@IF EXIST mycont.obj DEL mycont.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\mycont.cpp

myutil.obj: "$(ROOTDIR)\src\myutil.cpp"
	-@IF EXIST myutil.obj DEL myutil.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\myutil.cpp

mypan.obj: "$(ROOTDIR)\src\mypan.cpp"
	-@IF EXIST mypan.obj DEL mypan.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\mypan.cpp

myext.obj: "$(ROOTDIR)\src\myext.cpp"
	-@IF EXIST myext.obj DEL myext.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\myext.cpp


# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST mymain.obj DEL mymain.obj
	-@IF EXIST myclass.obj DEL myclass.obj
	-@IF EXIST myinter.obj DEL myinter.obj
	-@IF EXIST myclinsp.obj DEL myclinsp.obj
	-@IF EXIST mybuf.obj DEL mybuf.obj
	-@IF EXIST myman.obj DEL myman.obj
	-@IF EXIST mycont.obj DEL mycont.obj
	-@IF EXIST myutil.obj DEL myutil.obj
	-@IF EXIST mypan.obj DEL mypan.obj
	-@IF EXIST myext.obj DEL myext.obj
	-@IF EXIST mystudio.exe DEL mystudio.exe
	-@IF EXIST ivfstudio.res DEL ivfstudio.res

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

