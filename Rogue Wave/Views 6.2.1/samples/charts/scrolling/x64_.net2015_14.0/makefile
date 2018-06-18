# --------------------------------------------------------------------------
#
#   Makefile for the 'charts/scrolling' Rogue Wave Views Sample
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


PROGRAMS     = scrolling

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# scrolling
DDOBJS       = shiftcar.obj shiftpol.obj cyclic.obj listener.obj app.obj samputil.obj

# --------------------------------------------------------------------------
scrolling: scrolling.exe
scrolling.exe: $(DDOBJS) scrolling.obj viewsico.res
	-@IF EXIST scrolling.exe DEL scrolling.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvcharts.lib ilvadvgdt.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ scrolling.obj $(DDOBJS) ilvmain.obj viewsico.res

scrolling.obj: "$(ROOTDIR)\src\scrolling.cpp"
	-@IF EXIST scrolling.obj DEL scrolling.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\scrolling.cpp

shiftcar.obj: "$(ROOTDIR)\src\shiftcar.cpp"
	-@IF EXIST shiftcar.obj DEL shiftcar.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\shiftcar.cpp

shiftpol.obj: "$(ROOTDIR)\src\shiftpol.cpp"
	-@IF EXIST shiftpol.obj DEL shiftpol.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\shiftpol.cpp

cyclic.obj: "$(ROOTDIR)\src\cyclic.cpp"
	-@IF EXIST cyclic.obj DEL cyclic.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\cyclic.cpp

listener.obj: "$(ROOTDIR)\src\listener.cpp"
	-@IF EXIST listener.obj DEL listener.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\listener.cpp

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
	-@IF EXIST scrolling.obj DEL scrolling.obj
	-@IF EXIST shiftcar.obj DEL shiftcar.obj
	-@IF EXIST shiftpol.obj DEL shiftpol.obj
	-@IF EXIST cyclic.obj DEL cyclic.obj
	-@IF EXIST listener.obj DEL listener.obj
	-@IF EXIST app.obj DEL app.obj
	-@IF EXIST samputil.obj DEL samputil.obj
	-@IF EXIST scrolling.exe DEL scrolling.exe

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

