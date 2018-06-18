# --------------------------------------------------------------------------
#
#   Makefile for the 'charts/simple' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x64_.net2017_15.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SYSTEM       = x64_.net2017_15.0
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


PROGRAMS     = simple

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# simple
DDOBJS       = cartesian.obj polar.obj xml.obj xml_date.obj app.obj samputil.obj

# --------------------------------------------------------------------------
simple: simple.exe
simple.exe: $(DDOBJS) simple.obj viewsico.res
	-@IF EXIST simple.exe DEL simple.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvcharts.lib ilvadvgdt.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ simple.obj $(DDOBJS) ilvmain.obj viewsico.res

simple.obj: "$(ROOTDIR)\src\simple.cpp"
	-@IF EXIST simple.obj DEL simple.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\simple.cpp

cartesian.obj: "$(ROOTDIR)\src\cartesian.cpp"
	-@IF EXIST cartesian.obj DEL cartesian.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\cartesian.cpp

polar.obj: "$(ROOTDIR)\src\polar.cpp"
	-@IF EXIST polar.obj DEL polar.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\polar.cpp

xml.obj: "$(ROOTDIR)\src\xml.cpp"
	-@IF EXIST xml.obj DEL xml.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\xml.cpp

xml_date.obj: "$(ROOTDIR)\src\xml_date.cpp"
	-@IF EXIST xml_date.obj DEL xml_date.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\xml_date.cpp

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
	-@IF EXIST simple.obj DEL simple.obj
	-@IF EXIST cartesian.obj DEL cartesian.obj
	-@IF EXIST polar.obj DEL polar.obj
	-@IF EXIST xml.obj DEL xml.obj
	-@IF EXIST xml_date.obj DEL xml_date.obj
	-@IF EXIST app.obj DEL app.obj
	-@IF EXIST samputil.obj DEL samputil.obj
	-@IF EXIST simple.exe DEL simple.exe

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

