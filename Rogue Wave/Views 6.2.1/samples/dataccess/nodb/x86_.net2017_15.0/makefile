# --------------------------------------------------------------------------
#
#   Makefile for the 'nodb' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x86_.net2017_15.0
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




DBOBJ  = app.obj folio.obj foliotbl.obj form.obj html.obj sintoggl.obj usercall.obj

PROGRAMS     = nodb

all: $(PROGRAMS)

# --------------------------------------------------------------------------
nodb: nodb.exe
nodb.exe: $(DBOBJ) main.obj
	-@IF EXIST nodb.exe DEL nodb.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(DATACCESSLIBDIR)" dbgadget.lib dataccess.lib ilvadvgdt.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(DATACCESSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ main.obj $(DBOBJ) ilvmain.obj

main.obj: "$(DATACCESSDIR)\samples\dataccess\nodb\src\main.cpp"
	-@IF EXIST main.obj DEL main.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\nodb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\nodb\src\main.cpp

app.obj: "$(DATACCESSDIR)\samples\dataccess\nodb\src\app.cpp"
	-@IF EXIST app.obj DEL app.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\nodb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\nodb\src\app.cpp

folio.obj: "$(DATACCESSDIR)\samples\dataccess\nodb\src\folio.cpp"
	-@IF EXIST folio.obj DEL folio.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\nodb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\nodb\src\folio.cpp

foliotbl.obj: "$(DATACCESSDIR)\samples\dataccess\nodb\src\foliotbl.cpp"
	-@IF EXIST foliotbl.obj DEL foliotbl.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\nodb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\nodb\src\foliotbl.cpp

form.obj: "$(DATACCESSDIR)\samples\dataccess\nodb\src\form.cpp"
	-@IF EXIST form.obj DEL form.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\nodb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\nodb\src\form.cpp

html.obj: "$(DATACCESSDIR)\samples\dataccess\nodb\src\html.cpp"
	-@IF EXIST html.obj DEL html.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\nodb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\nodb\src\html.cpp

sintoggl.obj: "$(DATACCESSDIR)\samples\dataccess\nodb\src\sintoggl.cpp"
	-@IF EXIST sintoggl.obj DEL sintoggl.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\nodb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\nodb\src\sintoggl.cpp

usercall.obj: "$(DATACCESSDIR)\samples\dataccess\nodb\src\usercall.cpp"
	-@IF EXIST usercall.obj DEL usercall.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\nodb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\nodb\src\usercall.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST main.obj DEL main.obj
	-@IF EXIST app.obj DEL app.obj
	-@IF EXIST folio.obj DEL folio.obj
	-@IF EXIST foliotbl.obj DEL foliotbl.obj
	-@IF EXIST form.obj DEL form.obj
	-@IF EXIST html.obj DEL html.obj
	-@IF EXIST sintoggl.obj DEL sintoggl.obj
	-@IF EXIST usercall.obj DEL usercall.obj
	-@IF EXIST nodb.exe DEL nodb.exe

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

