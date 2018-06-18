# --------------------------------------------------------------------------
#
#   Makefile for the 'dbgraphe' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x64_.net2013_12.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ILVHOME)
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

DATACCESSDIR = $(ROOTDIR)\..\..\..
DATACCESSINCDIR= $(DATACCESSDIR)\include
DATACCESSLIBDIR= $(DATACCESSDIR)\lib\$(SYSTEM)\$(FORMAT)

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




DBOBJ  = app.obj grapher.obj

PROGRAMS     = dbgraphe

all: $(PROGRAMS)

# --------------------------------------------------------------------------
dbgraphe: dbgraphe.exe
dbgraphe.exe: $(DBOBJ) main.obj viewsico.res
	-@IF EXIST dbgraphe.exe DEL dbgraphe.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(DATACCESSLIBDIR)" dbgraphe.lib ilvpng.lib ilvppm.lib ilvgadgraph.lib dbgadget.lib dataccess.lib ilvgadmgr.lib ilvbmp.lib ilvadvgdt.lib ilvgrapher.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(DATACCESSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ main.obj $(DBOBJ) ilvmain.obj viewsico.res

main.obj: "$(DATACCESSDIR)\samples\dataccess\dbgraphe\src\main.cpp"
	-@IF EXIST main.obj DEL main.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\dbgraphe\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\dbgraphe\src\main.cpp

app.obj: "$(DATACCESSDIR)\samples\dataccess\dbgraphe\src\app.cpp"
	-@IF EXIST app.obj DEL app.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\dbgraphe\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\dbgraphe\src\app.cpp

grapher.obj: "$(DATACCESSDIR)\samples\dataccess\dbgraphe\src\grapher.cpp"
	-@IF EXIST grapher.obj DEL grapher.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\dbgraphe\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\dbgraphe\src\grapher.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST main.obj DEL main.obj
	-@IF EXIST app.obj DEL app.obj
	-@IF EXIST grapher.obj DEL grapher.obj
	-@IF EXIST dbgraphe.exe DEL dbgraphe.exe

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

