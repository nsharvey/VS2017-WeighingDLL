# --------------------------------------------------------------------------
#
#   Makefile for the 'withdb' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x64_.net2010_10.0
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

DATACCESSDIR = $(ROOTDIR)\..\..\..
DATACCESSINCDIR= $(DATACCESSDIR)\include
DATACCESSLIBDIR= $(DATACCESSDIR)\lib\$(SYSTEM)\$(FORMAT)

SYSTEM       = x64_.net2010_10.0
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

PROGRAMS     = withdb

all: $(PROGRAMS)


DBOBJ  = app.obj dynsel.obj gauge.obj getstart.obj query.obj session.obj

# --------------------------------------------------------------------------
withdb: withdb.exe
withdb.exe: $(DBOBJ) main.obj viewsico.res
	-@IF EXIST withdb.exe DEL withdb.exe
	$(LD) $(LDFLAGS) $(EXCLUDELIBS) /LIBPATH:"$(VIEWSLIBDIR)" /LIBPATH:"$(DATACCESSLIBDIR)" dbsqlgad.lib iljsgide.lib dbaccess.lib ilvjs.lib dbgadget.lib dataccess.lib ilvadvgdt.lib ilvgadgt.lib views.lib winviews.lib ilog.lib iljs.lib "$(DBLINKLIBDIR)\dblnkdyn.lib" "$(DBLINKLIBDIR)\dbkernel.lib" $(VIEWSSYSLIBS) $(DATACCESSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ main.obj $(DBOBJ) ilvmain.obj viewsico.res

main.obj: "$(DATACCESSDIR)\samples\dataccess\withdb\src\main.cpp"
	-@IF EXIST main.obj DEL main.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\withdb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" $(DBFLAGS) $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\withdb\src\main.cpp

app.obj: "$(DATACCESSDIR)\samples\dataccess\withdb\src\app.cpp"
	-@IF EXIST app.obj DEL app.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\withdb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\withdb\src\app.cpp

dynsel.obj: "$(DATACCESSDIR)\samples\dataccess\withdb\src\dynsel.cpp"
	-@IF EXIST dynsel.obj DEL dynsel.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\withdb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\withdb\src\dynsel.cpp

gauge.obj: "$(DATACCESSDIR)\samples\dataccess\withdb\src\gauge.cpp"
	-@IF EXIST gauge.obj DEL gauge.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\withdb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\withdb\src\gauge.cpp

getstart.obj: "$(DATACCESSDIR)\samples\dataccess\withdb\src\getstart.cpp"
	-@IF EXIST getstart.obj DEL getstart.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\withdb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\withdb\src\getstart.cpp

query.obj: "$(DATACCESSDIR)\samples\dataccess\withdb\src\query.cpp"
	-@IF EXIST query.obj DEL query.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\withdb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\withdb\src\query.cpp

session.obj: "$(DATACCESSDIR)\samples\dataccess\withdb\src\session.cpp"
	-@IF EXIST session.obj DEL session.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(DATACCESSDIR)\samples\dataccess\withdb\include" /I"$(DATACCESSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" $(CCFLAGS) $(DATACCESSDIR)\samples\dataccess\withdb\src\session.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST main.obj DEL main.obj
	-@IF EXIST app.obj DEL app.obj
	-@IF EXIST dynsel.obj DEL dynsel.obj
	-@IF EXIST gauge.obj DEL gauge.obj
	-@IF EXIST getstart.obj DEL getstart.obj
	-@IF EXIST query.obj DEL query.obj
	-@IF EXIST session.obj DEL session.obj
	-@IF EXIST withdb.exe DEL withdb.exe

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

