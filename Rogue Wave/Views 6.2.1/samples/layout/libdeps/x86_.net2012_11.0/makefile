# --------------------------------------------------------------------------
#
#   Makefile for the 'layout' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x86_.net2012_11.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SYSTEM       = x86_.net2012_11.0
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



PROGRAMS	= libdeps

all: $(PROGRAMS)

OBJS		= objsel.obj dialog.obj
# --------------------------------------------------------------------------
# libdeps
# --------------------------------------------------------------------------
libdeps: libdeps.exe
libdeps.exe: $(OBJS) libdeps.obj viewsico.res
	-@IF EXIST libdeps.exe DEL libdeps.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvhierarchical.lib ilvlayout.lib ilvgrapher.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ libdeps.obj $(OBJS) ilvmain.obj viewsico.res

libdeps.obj: "$(ROOTDIR)\src\libdeps.cpp"
	-@IF EXIST libdeps.obj DEL libdeps.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ROOTDIR)\include" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\libdeps.cpp

objsel.obj: "$(ROOTDIR)\src\objsel.cpp"
	-@IF EXIST objsel.obj DEL objsel.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ROOTDIR)\include" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\objsel.cpp

dialog.obj: "$(ROOTDIR)\src\dialog.cpp"
	-@IF EXIST dialog.obj DEL dialog.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ROOTDIR)\include" /I"$(VIEWSINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\dialog.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST libdeps.obj DEL libdeps.obj
	-@IF EXIST objsel.obj DEL objsel.obj
	-@IF EXIST dialog.obj DEL dialog.obj
	-@IF EXIST libdeps.exe DEL libdeps.exe

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

