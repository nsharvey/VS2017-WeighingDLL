# --------------------------------------------------------------------------
#
#   Makefile for the 'charts/scales' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x86_.net2010_10.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SYSTEM       = x86_.net2010_10.0
FORMAT       = dll_mda

CCC          = cl
COMPILERFLAGS= /c /DWIN32 /DIL_DLL /MD /nologo /W3 /EHsc /GR /D_CRT_SECURE_NO_DEPRECATE
LD           = link
LDFLAGS      = $(LDDBGFLAGS) /NOLOGO /SUBSYSTEM:WINDOWS /MACHINE:I386 /INCREMENTAL:NO	
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


PROGRAMS     = scales

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# scales
DDOBJS       = loga.obj ex2y.obj app.obj samputil.obj

# --------------------------------------------------------------------------
scales: scales.exe
scales.exe: $(DDOBJS) scales.obj viewsico.res
	-@IF EXIST scales.exe DEL scales.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvcharts.lib ilvadvgdt.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ scales.obj $(DDOBJS) ilvmain.obj viewsico.res

scales.obj: "$(ROOTDIR)\src\scales.cpp"
	-@IF EXIST scales.obj DEL scales.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\scales.cpp

loga.obj: "$(ROOTDIR)\src\loga.cpp"
	-@IF EXIST loga.obj DEL loga.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\loga.cpp

ex2y.obj: "$(ROOTDIR)\src\ex2y.cpp"
	-@IF EXIST ex2y.obj DEL ex2y.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\ex2y.cpp

app.obj: "$(ROOTDIR)\src\app.cpp"
	-@IF EXIST app.obj DEL app.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\app.cpp

# --------------------------------------------------------------------------
samputil.obj: "$(ROOTDIR)\..\src\samputil.cpp"
	-@IF EXIST samputil.obj DEL samputil.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\..\src\samputil.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST scales.obj DEL scales.obj
	-@IF EXIST loga.obj DEL loga.obj
	-@IF EXIST ex2y.obj DEL ex2y.obj
	-@IF EXIST app.obj DEL app.obj
	-@IF EXIST samputil.obj DEL samputil.obj
	-@IF EXIST scales.exe DEL scales.exe

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

