# --------------------------------------------------------------------------
#
#   Makerules for the prototype Rogue Wave Views Samples
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



PROGRAMS     = gppanel gpstudio 

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# gppanel
# --------------------------------------------------------------------------
gppanel: gppanel.exe
gppanel.exe: gpacc.obj gppanel.obj viewsico.res
	-@IF EXIST gppanel.exe DEL gppanel.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvgdpro.lib ilvgadgraph.lib ilvgadmgr.lib ilvproto.lib ilvgrapher.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ gppanel.obj gpacc.obj ilvmain.obj viewsico.res

gppanel.obj: "$(ROOTDIR)\src\gppanel.cpp"
	-@IF EXIST gppanel.obj DEL gppanel.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\gppanel.cpp

gpacc.obj: "$(ROOTDIR)\src\gpacc.cpp"
	-@IF EXIST gpacc.obj DEL gpacc.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\gpacc.cpp

# --------------------------------------------------------------------------
# gpstudio
# --------------------------------------------------------------------------
gpstudio: gpstudio.exe
gpstudio.exe: gpacc.obj libini.obj defaultx.obj gpstmain.obj ivfstudio.res
	-@IF EXIST gpstudio.exe DEL gpstudio.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(STUDIOLIBDIR)" prstudio.lib jsstudio.lib iljsgide.lib ilvstgrapher.lib ilvstappli.lib ilvstgadget.lib ivstudio.lib ilvprtdlg.lib ilvmgrprint.lib ilvgdpro.lib ilvbmpflt.lib ilvpng.lib ilvjs.lib ilvppm.lib ilvgadgraph.lib ilvprint.lib ilvatext.lib ilvadvgadmgr.lib ilvstates.lib ilvedit.lib ilvgadmgr.lib ilvbmp.lib ilvadvgdt.lib ilvproto.lib ilvgrapher.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib iljs.lib $(VIEWSSYSLIBS) $(STUDIOSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ gpstmain.obj gpacc.obj libini.obj defaultx.obj ilvmain.obj ivfstudio.res

gpstmain.obj: "$(ROOTDIR)\src\gpstmain.cpp"
	-@IF EXIST gpstmain.obj DEL gpstmain.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(STUDIOINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\gpstmain.cpp

# --------------------------------------------------------------------------
ivfstudio.res: $(VIEWSDIR)\studio\data\res\ivfstudio.rc
	$(RC) $(RCFLAGS) -r -foivfstudio.res /I$(VIEWSDIR)\data\res /I$(VIEWSDIR)\data /I$(VIEWSDIR)\data\icon $(VIEWSDIR)\studio\data\res\ivfstudio.rc

libini.obj: "$(ROOTDIR)\src\libini.cpp"
	-@IF EXIST libini.obj DEL libini.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(STUDIOINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\libini.cpp

defaultx.obj: "$(ROOTDIR)\src\defaultx.cpp"
	-@IF EXIST defaultx.obj DEL defaultx.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(STUDIOINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\defaultx.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST gppanel.obj DEL gppanel.obj
	-@IF EXIST gpacc.obj DEL gpacc.obj
	-@IF EXIST gpstmain.obj DEL gpstmain.obj
	-@IF EXIST libini.obj DEL libini.obj
	-@IF EXIST defaultx.obj DEL defaultx.obj
	-@IF EXIST gppanel.exe DEL gppanel.exe
	-@IF EXIST gpstudio.exe DEL gpstudio.exe
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

