# --------------------------------------------------------------------------
#
#   Makefile for the 'bmpfilters' Rogue Wave Views Samples
#
# --------------------------------------------------------------------------
#   platform: x64_.net2010_10.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

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



PROGRAMS     = displace bmpfilters

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# displace
# --------------------------------------------------------------------------
displace: displace.exe
displace.exe: displace.obj viewsico.res
	-@IF EXIST displace.exe DEL displace.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvbmpflt.lib ilvpng.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ displace.obj ilvmain.obj viewsico.res

displace.obj: "..\src\displace.cpp"
	-@IF EXIST displace.obj DEL displace.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" $(CCFLAGS) ..\src\displace.cpp

# --------------------------------------------------------------------------
# bmpfilters
DDOBJS       = app.obj emboss.obj gold.obj relief.obj filtgraph.obj

# --------------------------------------------------------------------------
bmpfilters: bmpfilters.exe
bmpfilters.exe: $(DDOBJS) bmpfilters.obj viewsico.res
	-@IF EXIST bmpfilters.exe DEL bmpfilters.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvbmpflt.lib ilvpng.lib ilvadvgdt.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ bmpfilters.obj $(DDOBJS) ilvmain.obj viewsico.res

bmpfilters.obj: "..\src\bmpfilters.cpp"
	-@IF EXIST bmpfilters.obj DEL bmpfilters.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(CCFLAGS) ..\src\bmpfilters.cpp

app.obj: "..\src\app.cpp"
	-@IF EXIST app.obj DEL app.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\app.cpp

emboss.obj: "..\src\emboss.cpp"
	-@IF EXIST emboss.obj DEL emboss.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\emboss.cpp

gold.obj: "..\src\gold.cpp"
	-@IF EXIST gold.obj DEL gold.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\gold.cpp

relief.obj: "..\src\relief.cpp"
	-@IF EXIST relief.obj DEL relief.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\relief.cpp

filtgraph.obj: "..\src\filtgraph.cpp"
	-@IF EXIST filtgraph.obj DEL filtgraph.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\filtgraph.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST displace.obj DEL displace.obj
	-@IF EXIST bmpfilters.obj DEL bmpfilters.obj
	-@IF EXIST app.obj DEL app.obj
	-@IF EXIST emboss.obj DEL emboss.obj
	-@IF EXIST gold.obj DEL gold.obj
	-@IF EXIST relief.obj DEL relief.obj
	-@IF EXIST filtgraph.obj DEL filtgraph.obj
	-@IF EXIST displace.exe DEL displace.exe
	-@IF EXIST bmpfilters.exe DEL bmpfilters.exe

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

