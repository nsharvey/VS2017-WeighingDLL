# --------------------------------------------------------------------------
#
#   Makefile for Rogue Wave Views Gantt Chart Samples
#
# --------------------------------------------------------------------------
#   platform: x86_.net2017_15.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SYSTEM       = x86_.net2017_15.0
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



# --------------------------------------------------------------------------
PROGRAMS     = calendar

all: $(PROGRAMS)

COMMONOBJS    = toolbar.obj tooltip.obj utils.obj
# --------------------------------------------------------------------------
calendar: calendar.exe
calendar.exe: $(COMMONOBJS) calendar.obj viewsico.res
	-@IF EXIST calendar.exe DEL calendar.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvgantt.lib ilvpng.lib ilvgadgraph.lib ilvgadmgr.lib ilvadvgdt.lib ilvgrapher.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ calendar.obj $(COMMONOBJS) ilvmain.obj viewsico.res

calendar.obj: "$(ROOTDIR)\src\calendar.cpp"
	-@IF EXIST calendar.obj DEL calendar.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\common\include" $(CCFLAGS) $(ROOTDIR)\src\calendar.cpp

toolbar.obj: "$(ROOTDIR)\..\common\src\toolbar.cpp"
	-@IF EXIST toolbar.obj DEL toolbar.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\common\include" $(CCFLAGS) $(ROOTDIR)\..\common\src\toolbar.cpp

tooltip.obj: "$(ROOTDIR)\..\common\src\tooltip.cpp"
	-@IF EXIST tooltip.obj DEL tooltip.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\common\include" $(CCFLAGS) $(ROOTDIR)\..\common\src\tooltip.cpp

utils.obj: "$(ROOTDIR)\..\common\src\utils.cpp"
	-@IF EXIST utils.obj DEL utils.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\common\include" $(CCFLAGS) $(ROOTDIR)\..\common\src\utils.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST calendar.obj DEL calendar.obj
	-@IF EXIST toolbar.obj DEL toolbar.obj
	-@IF EXIST tooltip.obj DEL tooltip.obj
	-@IF EXIST utils.obj DEL utils.obj
	-@IF EXIST calendar.exe DEL calendar.exe

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

