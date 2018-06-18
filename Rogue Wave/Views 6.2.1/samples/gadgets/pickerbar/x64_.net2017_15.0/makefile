# --------------------------------------------------------------------------
#
#   Makefile for the 'guitarchords' Rogue Wave Views Sample
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



PROGRAMS     = guitarchords

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# guitarchords
OBJS       = main.obj pickerbar.obj tonepicker.obj fretboard.obj

# --------------------------------------------------------------------------
guitarchords: guitarchords.exe
guitarchords.exe: $(OBJS) guitarchords.obj viewsico.res
	-@IF EXIST guitarchords.exe DEL guitarchords.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvjpg.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ guitarchords.obj $(OBJS) ilvmain.obj viewsico.res

guitarchords.obj: "$(ROOTDIR)\src\guitarchords.cpp"
	-@IF EXIST guitarchords.obj DEL guitarchords.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"..\include" $(CCFLAGS) $(ROOTDIR)\src\guitarchords.cpp

main.obj: "$(ROOTDIR)\src\main.cpp"
	-@IF EXIST main.obj DEL main.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"..\include" $(CCFLAGS) $(ROOTDIR)\src\main.cpp

pickerbar.obj: "$(ROOTDIR)\src\pickerbar.cpp"
	-@IF EXIST pickerbar.obj DEL pickerbar.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"..\include" $(CCFLAGS) $(ROOTDIR)\src\pickerbar.cpp

tonepicker.obj: "$(ROOTDIR)\src\tonepicker.cpp"
	-@IF EXIST tonepicker.obj DEL tonepicker.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"..\include" $(CCFLAGS) $(ROOTDIR)\src\tonepicker.cpp

fretboard.obj: "$(ROOTDIR)\src\fretboard.cpp"
	-@IF EXIST fretboard.obj DEL fretboard.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"..\include" $(CCFLAGS) $(ROOTDIR)\src\fretboard.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST guitarchords.obj DEL guitarchords.obj
	-@IF EXIST main.obj DEL main.obj
	-@IF EXIST pickerbar.obj DEL pickerbar.obj
	-@IF EXIST tonepicker.obj DEL tonepicker.obj
	-@IF EXIST fretboard.obj DEL fretboard.obj
	-@IF EXIST guitarchords.exe DEL guitarchords.exe

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

