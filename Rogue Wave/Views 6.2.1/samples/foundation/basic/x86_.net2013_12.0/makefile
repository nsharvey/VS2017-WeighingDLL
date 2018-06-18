# --------------------------------------------------------------------------
#
#   Package 'foundation'
#   Makefile for the 'basic' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x86_.net2013_12.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SYSTEM       = x86_.net2013_12.0
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



PROGRAMS     = ilvread inter hull

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# ilvread
# --------------------------------------------------------------------------
ilvread: ilvread.exe
ilvread.exe: ilvread.obj viewsico.res
	-@IF EXIST ilvread.exe DEL ilvread.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ ilvread.obj ilvmain.obj viewsico.res

ilvread.obj: "..\src\ilvread.cpp"
	-@IF EXIST ilvread.obj DEL ilvread.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" $(CCFLAGS) ..\src\ilvread.cpp

# --------------------------------------------------------------------------
# inter
# --------------------------------------------------------------------------
inter: inter.exe
inter.exe: inter.obj viewsico.res
	-@IF EXIST inter.exe DEL inter.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ inter.obj ilvmain.obj viewsico.res

inter.obj: "..\src\inter.cpp"
	-@IF EXIST inter.obj DEL inter.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" $(CCFLAGS) ..\src\inter.cpp

# --------------------------------------------------------------------------
# hull
# --------------------------------------------------------------------------
hull: hull.exe
hull.exe: hull.obj viewsico.res
	-@IF EXIST hull.exe DEL hull.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ hull.obj ilvmain.obj viewsico.res

hull.obj: "..\src\hull.cpp"
	-@IF EXIST hull.obj DEL hull.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" $(CCFLAGS) ..\src\hull.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST ilvread.obj DEL ilvread.obj
	-@IF EXIST inter.obj DEL inter.obj
	-@IF EXIST hull.obj DEL hull.obj
	-@IF EXIST ilvread.exe DEL ilvread.exe
	-@IF EXIST inter.exe DEL inter.exe
	-@IF EXIST hull.exe DEL hull.exe

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

