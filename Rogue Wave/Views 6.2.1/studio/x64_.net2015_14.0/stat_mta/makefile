# --------------------------------------------------------------------------
#
#   Makefile for Rogue Wave Views Studio
#
# --------------------------------------------------------------------------
#   platform: x64_.net2015_14.0
#   format:   stat_mta
# --------------------------------------------------------------------------

ROOTDIR      = ..\..

VIEWSDIR     = $(ROOTDIR)\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

STUDIODIR    = $(VIEWSDIR)\studio
STUDIOINCDIR = $(VIEWSDIR)\include
STUDIOLIBDIR = $(STUDIODIR)\$(SYSTEM)\$(FORMAT)

SYSTEM       = x64_.net2015_14.0
FORMAT       = stat_mta

CCC          = CL
COMPILERFLAGS= /c /MT /W3 /EHsc /GR /D_CRT_SECURE_NO_WARNINGS
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
CCFLAGS      = $(OPTIMFLAGS) $(COMPILERFLAGS)
ALLSYSLIBS   = $(ADDLIBS) $(BIDILIBS) $(SYSLIBS)



STUDIOSRCDIR = $(STUDIODIR)\src
PROTOSSRCDIR = $(STUDIODIR)\src\protos

PROGRAMS=ivfstudio ivstudio jsstudio prstudio chstudio

all: $(LIBS) ivfstudio

progs: $(PROGRAMS)

# ##########################################################################
# --------------------------------------------------------------------------
ivfstudio: ivfstudio.exe
ivfstudio.exe: $(IVSTUDIOLIB) $(JSSTUDIOLIB) libini.obj ivfstudio.obj ivfstudio.res
	-@IF EXIST ivfstudio.exe DEL ivfstudio.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(STUDIOLIBDIR)" ilvawxplook.lib ilvwxplook.lib ilvamlook.lib ilvavxlook.lib jsstudio.lib iljsgide.lib ilvmlook.lib ivstudio.lib ilvprtdlg.lib ilvaw95look.lib ilvmgrprint.lib ilvawlook.lib ilvvxlook.lib ilvw95look.lib ilvbmpflt.lib ilvpng.lib ilvjs.lib ilvppm.lib ilvwlook.lib ilvprint.lib ilvadvgadmgr.lib ilvstates.lib ilvedit.lib ilvgadmgr.lib ilvbmp.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib iljs.lib $(VIEWSSYSLIBS) $(STUDIOSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ ivfstudio.obj libini.obj ilvmain.obj ivfstudio.res

ivfstudio.obj: "$(STUDIOSRCDIR)\ivfstudio.cpp"
	-@IF EXIST ivfstudio.obj DEL ivfstudio.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" $(CCFLAGS) $(STUDIOSRCDIR)\ivfstudio.cpp

# --------------------------------------------------------------------------
ivfstudio.res: $(STUDIODIR)\data\res\ivfstudio.rc
	$(RC) $(RCFLAGS) -r -foivfstudio.res /I$(VIEWSDIR)\data\res /I$(VIEWSDIR)\data /I$(VIEWSDIR)\data\icon /I$(STUDIODIR)\data\res $(STUDIODIR)\data\res\ivfstudio.rc

# ##########################################################################
# --------------------------------------------------------------------------
ivstudio: ivstudio.exe
ivstudio.exe: $(IVSTUDIOLIB) $(STGADGETLIB) $(STAPPLILIB) $(STGENEXLIB) $(STGRAPHERLIB) libini.obj defaultx.obj main.obj
	-@IF EXIST ivstudio.exe DEL ivstudio.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(STUDIOLIBDIR)" ilvawxplook.lib ilvwxplook.lib ilvamlook.lib ilvavxlook.lib ilvstgenex.lib ilvstgrapher.lib ilvmlook.lib ilvstappli.lib ilvstgadget.lib ivstudio.lib ilvprtdlg.lib ilvaw95look.lib ilvmgrprint.lib ilvawlook.lib ilvvxlook.lib ilvw95look.lib ilvbmpflt.lib ilvpng.lib ilvppm.lib ilvwlook.lib ilvgadgraph.lib ilvprint.lib ilvadvgadmgr.lib ilvstates.lib ilvedit.lib ilvgadmgr.lib ilvbmp.lib ilvadvgdt.lib ilvgrapher.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(STUDIOSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ main.obj libini.obj defaultx.obj ilvmain.obj

main.obj: "$(STUDIOSRCDIR)\main.cpp"
	-@IF EXIST main.obj DEL main.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" $(CCFLAGS) $(STUDIOSRCDIR)\main.cpp

# ##########################################################################
# --------------------------------------------------------------------------
jsstudio: jsstudio.exe
jsstudio.exe: $(IVSTUDIOLIB) $(JSSTUDIOLIB) $(STGADGETLIB) $(STAPPLILIB) $(STGENEXLIB) $(STGRAPHERLIB) libini.obj defaultx.obj jsmain.obj
	-@IF EXIST jsstudio.exe DEL jsstudio.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(STUDIOLIBDIR)" ilvawxplook.lib ilvwxplook.lib ilvamlook.lib ilvavxlook.lib ilvstgenex.lib jsstudio.lib iljsgide.lib ilvstgrapher.lib ilvmlook.lib ilvstappli.lib ilvstgadget.lib ivstudio.lib ilvprtdlg.lib ilvaw95look.lib ilvmgrprint.lib ilvawlook.lib ilvvxlook.lib ilvw95look.lib ilvbmpflt.lib ilvpng.lib ilvjs.lib ilvppm.lib ilvwlook.lib ilvgadgraph.lib ilvprint.lib ilvadvgadmgr.lib ilvstates.lib ilvedit.lib ilvgadmgr.lib ilvbmp.lib ilvadvgdt.lib ilvgrapher.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib iljs.lib $(VIEWSSYSLIBS) $(STUDIOSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ jsmain.obj libini.obj defaultx.obj ilvmain.obj

jsmain.obj: "$(STUDIOSRCDIR)\iscript\jsmain.cpp"
	-@IF EXIST jsmain.obj DEL jsmain.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" $(CCFLAGS) $(STUDIOSRCDIR)\iscript\jsmain.cpp

# ##########################################################################
# --------------------------------------------------------------------------
prstudio: prstudio.exe
prstudio.exe: $(IVSTUDIOLIB) $(PRSTUDIOLIB) $(STOLDPROLIB) $(JSSTUDIOLIB) $(STGADGETLIB) $(STAPPLILIB) $(STGENEXLIB) $(STGRAPHERLIB) libini.obj defaultx.obj promain.obj
	-@IF EXIST prstudio.exe DEL prstudio.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(STUDIOLIBDIR)" ilvawxplook.lib stoldpro.lib ilvwxplook.lib ilvamlook.lib ilvavxlook.lib ilvstgenex.lib prstudio.lib jsstudio.lib iljsgide.lib ilvstgrapher.lib ilvmlook.lib ilvstappli.lib ilvstgadget.lib ivstudio.lib ilvprtdlg.lib ilvaw95look.lib ilvmgrprint.lib ilvawlook.lib ilvvxlook.lib ilvw95look.lib ilvgdpro.lib ilvbmpflt.lib ilvpng.lib ilvjs.lib ilvppm.lib ilvwlook.lib ilvgadgraph.lib ilvprint.lib ilvatext.lib ilvadvgadmgr.lib ilvstates.lib ilvedit.lib ilvgadmgr.lib ilvbmp.lib ilvadvgdt.lib ilvproto.lib ilvgrapher.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib iljs.lib $(VIEWSSYSLIBS) $(STUDIOSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ promain.obj libini.obj defaultx.obj ilvmain.obj

promain.obj: "$(PROTOSSRCDIR)\promain.cpp"
	-@IF EXIST promain.obj DEL promain.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" $(CCFLAGS) $(PROTOSSRCDIR)\promain.cpp

# ##########################################################################
# --------------------------------------------------------------------------
chstudio: chstudio.exe
chstudio.exe: $(IVSTUDIOLIB) $(STCHARTSLIB) $(PRSTUDIOLIB) $(JSSTUDIOLIB) $(STGADGETLIB) $(STAPPLILIB) $(STGENEXLIB) $(STGRAPHERLIB) libini.obj defaultx.obj chmain.obj
	-@IF EXIST chstudio.exe DEL chstudio.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(STUDIOLIBDIR)" ilvawxplook.lib ilvwxplook.lib ilvstcharts.lib ilvamlook.lib ilvavxlook.lib ilvstgenex.lib prstudio.lib jsstudio.lib iljsgide.lib ilvstgrapher.lib ilvmlook.lib ilvstappli.lib ilvstgadget.lib ivstudio.lib ilvprtdlg.lib ilvaw95look.lib ilvmgrprint.lib ilvawlook.lib ilvvxlook.lib ilvw95look.lib ilvgdpro.lib ilvbmpflt.lib ilvpng.lib ilvjs.lib ilvppm.lib ilvwlook.lib ilvgadgraph.lib ilvcharts.lib ilvprint.lib ilvatext.lib ilvadvgadmgr.lib ilvstates.lib ilvedit.lib ilvgadmgr.lib ilvbmp.lib ilvadvgdt.lib ilvproto.lib ilvgrapher.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib iljs.lib $(VIEWSSYSLIBS) $(STUDIOSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ chmain.obj libini.obj defaultx.obj ilvmain.obj

chmain.obj: "$(STUDIOSRCDIR)\charts\chmain.cpp"
	-@IF EXIST chmain.obj DEL chmain.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" $(CCFLAGS) $(STUDIOSRCDIR)\charts\chmain.cpp

libini.obj: "$(STUDIOSRCDIR)\libini.cpp"
	-@IF EXIST libini.obj DEL libini.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" $(CCFLAGS) $(STUDIOSRCDIR)\libini.cpp

defaultx.obj: "$(STUDIOSRCDIR)\defaultx.cpp"
	-@IF EXIST defaultx.obj DEL defaultx.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" $(CCFLAGS) $(STUDIOSRCDIR)\defaultx.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST ivfstudio.obj DEL ivfstudio.obj
	-@IF EXIST main.obj DEL main.obj
	-@IF EXIST jsmain.obj DEL jsmain.obj
	-@IF EXIST promain.obj DEL promain.obj
	-@IF EXIST chmain.obj DEL chmain.obj
	-@IF EXIST libini.obj DEL libini.obj
	-@IF EXIST defaultx.obj DEL defaultx.obj
	-@IF EXIST ivfstudio.exe DEL ivfstudio.exe
	-@IF EXIST ivstudio.exe DEL ivstudio.exe
	-@IF EXIST jsstudio.exe DEL jsstudio.exe
	-@IF EXIST prstudio.exe DEL prstudio.exe
	-@IF EXIST chstudio.exe DEL chstudio.exe
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

