# --------------------------------------------------------------------------
#
#   Makefile for the 'table' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x86_.net2015_14.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SYSTEM       = x86_.net2015_14.0
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



PROGRAMS     = table

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# table
DDOBJS       = edit.obj hugetabl.obj matrix.obj random.obj app.obj

# --------------------------------------------------------------------------
table: table.exe
table.exe: $(DDOBJS) table.obj viewsico.res
	-@IF EXIST table.exe DEL table.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvpng.lib ilvadvgdt.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ table.obj $(DDOBJS) ilvmain.obj viewsico.res

table.obj: "$(ROOTDIR)\src\table.cpp"
	-@IF EXIST table.obj DEL table.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"..\include" $(CCFLAGS) $(ROOTDIR)\src\table.cpp

matrix.obj: "$(ROOTDIR)\src\matrix.cpp"
	-@IF EXIST matrix.obj DEL matrix.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"..\include" $(CCFLAGS) $(ROOTDIR)\src\matrix.cpp

random.obj: "$(ROOTDIR)\src\random.cpp"
	-@IF EXIST random.obj DEL random.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"..\include" $(CCFLAGS) $(ROOTDIR)\src\random.cpp

hugetabl.obj: "$(ROOTDIR)\src\hugetabl.cpp"
	-@IF EXIST hugetabl.obj DEL hugetabl.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"..\include" $(CCFLAGS) $(ROOTDIR)\src\hugetabl.cpp

edit.obj: "$(ROOTDIR)\src\edit.cpp"
	-@IF EXIST edit.obj DEL edit.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"..\include" $(CCFLAGS) $(ROOTDIR)\src\edit.cpp

app.obj: "$(ROOTDIR)\src\app.cpp"
	-@IF EXIST app.obj DEL app.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"..\include" $(CCFLAGS) $(ROOTDIR)\src\app.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST table.obj DEL table.obj
	-@IF EXIST matrix.obj DEL matrix.obj
	-@IF EXIST random.obj DEL random.obj
	-@IF EXIST hugetabl.obj DEL hugetabl.obj
	-@IF EXIST edit.obj DEL edit.obj
	-@IF EXIST app.obj DEL app.obj
	-@IF EXIST table.exe DEL table.exe

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

