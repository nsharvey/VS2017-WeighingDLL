# --------------------------------------------------------------------------
#
#   Makefile for the 'runner' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x64_.net2012_11.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ILVHOME)
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

DBLINKDIR    = $(ILDHOME)
DBLINKINCDIR = $(DBLINKDIR)\include
DBLINKLIBDIR = $(DBLINKDIR)\lib\$(SYSTEM)\$(FORMAT)

DBSTUDDIR    = $(DATACCESSDIR)\studio
DBSTUDINCDIR = $(DBSTUDDIR)
DBSTUDLIBDIR = $(DBSTUDDIR)\$(SYSTEM)\$(FORMAT)

STUDIODIR    = $(VIEWSDIR)\studio
STUDIOINCDIR = $(VIEWSDIR)\include
STUDIOLIBDIR = $(STUDIODIR)\$(SYSTEM)\$(FORMAT)

DATACCESSDIR = $(ROOTDIR)\..\..\..
DATACCESSINCDIR= $(DATACCESSDIR)\include
DATACCESSLIBDIR= $(DATACCESSDIR)\lib\$(SYSTEM)\$(FORMAT)

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



DBFLAGS=-DILDALL

PROGRAMS     = runner

all: $(PROGRAMS)

# --------------------------------------------------------------------------
runner: runner.exe
runner.exe: main.obj
	-@IF EXIST runner.exe DEL runner.exe
	$(LD) $(LDFLAGS) $(EXCLUDELIBS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(DBSTUDLIBDIR)" /LIBPATH:"$(STUDIOLIBDIR)" /LIBPATH:"$(DATACCESSLIBDIR)" dbstgant.lib dbgantt.lib dbstsql.lib dbstchart.lib dbstgrap.lib dbstudio.lib ilvstcharts.lib ilvstgenex.lib dbsqlgad.lib dbchart.lib jsstudio.lib iljsgide.lib dbgraphe.lib ilvgantt.lib ilvstgrapher.lib ilvstappli.lib ilvstgadget.lib ivstudio.lib ilvprtdlg.lib ilvmgrprint.lib dbaccess.lib ilvbmpflt.lib ilvpng.lib ilvjs.lib ilvppm.lib ilvgadgraph.lib ilvcharts.lib dbgadget.lib ilvprint.lib ilvadvgadmgr.lib dataccess.lib ilvstates.lib ilvedit.lib ilvgadmgr.lib ilvbmp.lib ilvadvgdt.lib ilvgrapher.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib iljs.lib "$(DBLINKLIBDIR)\dblnkdyn.lib" "$(DBLINKLIBDIR)\dbkernel.lib" $(VIEWSSYSLIBS) $(DBSTUDSYSLIBS) $(STUDIOSYSLIBS) $(DATACCESSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ main.obj ilvmain.obj

main.obj: "$(DATACCESSDIR)\samples\dataccess\runner\src\main.cpp"
	-@IF EXIST main.obj DEL main.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\runner\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(STUDIOINCDIR)" /I"$(DBLINKINCDIR)" $(DBFLAGS) $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\runner\src\main.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST main.obj DEL main.obj
	-@IF EXIST runner.exe DEL runner.exe

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

