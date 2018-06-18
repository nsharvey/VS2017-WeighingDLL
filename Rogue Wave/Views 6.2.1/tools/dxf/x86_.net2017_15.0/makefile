# --------------------------------------------------------------------------
#
#   Makefile for the 'dxf' Rogue Wave Views Tools
#
# --------------------------------------------------------------------------
#   platform: x86_.net2017_15.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

FONTSDIR     = $(VIEWSDIR)\tools\vectfont
FONTSINCDIR  = $(FONTSDIR)
FONTSLIBDIR  = $(FONTSDIR)\$(SYSTEM)

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



ILVFONTSLIBNAME= ilvfonts.lib

ILVFONTSDEP  = "$(FONTSLIBDIR)\$(ILVFONTSLIBNAME)"

# --------------------------------------------------------------------------
PROGRAMS     = readdxf dxf2ilv ilv2dxf

all: $(PROGRAMS)

# --------------------------------------------------------------------------
readdxf: readdxf.exe
readdxf.exe: dxread.obj $(ILVFONTSDEP) readdxf.obj viewsico.res
	-@IF EXIST readdxf.exe DEL readdxf.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(FONTSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvfonts.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(FONTSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ readdxf.obj dxread.obj ilvmain.obj viewsico.res

readdxf.obj: "$(ROOTDIR)\src\readdxf.cpp" $(ROOTDIR)\dxfincl\dxread.h
	-@IF EXIST readdxf.obj DEL readdxf.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)" /I"$(FONTSINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\readdxf.cpp

dxread.obj: "$(ROOTDIR)\src\dxread.cpp" $(ROOTDIR)\dxfincl\dxread.h
	-@IF EXIST dxread.obj DEL dxread.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)" /I"$(FONTSINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\dxread.cpp

# --------------------------------------------------------------------------
dxf2ilv: dxf2ilv.exe
dxf2ilv.exe: dxread.obj $(ILVFONTSDEP) dxf2ilv.obj viewsico.res
	-@IF EXIST dxf2ilv.exe DEL dxf2ilv.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(FONTSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvfonts.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(FONTSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ dxf2ilv.obj dxread.obj ilvmain.obj viewsico.res

dxf2ilv.obj: "$(ROOTDIR)\src\dxf2ilv.cpp" $(ROOTDIR)\dxfincl\dxread.h
	-@IF EXIST dxf2ilv.obj DEL dxf2ilv.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)" /I"$(FONTSINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\dxf2ilv.cpp

dxwrite.obj: "$(ROOTDIR)\src\dxwrite.cpp" $(ROOTDIR)\dxfincl\dxwrite.h
	-@IF EXIST dxwrite.obj DEL dxwrite.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)" /I"$(FONTSINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\dxwrite.cpp

# --------------------------------------------------------------------------
ilv2dxf: ilv2dxf.exe
ilv2dxf.exe: dxwrite.obj ilv2dxf.obj viewsico.res
	-@IF EXIST ilv2dxf.exe DEL ilv2dxf.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ ilv2dxf.obj dxwrite.obj ilvmain.obj viewsico.res

ilv2dxf.obj: "$(ROOTDIR)\src\ilv2dxf.cpp" $(ROOTDIR)\dxfincl\dxwrite.h
	-@IF EXIST ilv2dxf.obj DEL ilv2dxf.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)" /I"$(FONTSINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\ilv2dxf.cpp

# --------------------------------------------------------------------------
$(ILVFONTSDEP):
	cd $(FONTSLIBDIR)
	nmake $(ILVFONTSLIBNAME)
	cd ..\..\dxf\$(SYSTEM)

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST readdxf.obj DEL readdxf.obj
	-@IF EXIST dxread.obj DEL dxread.obj
	-@IF EXIST dxf2ilv.obj DEL dxf2ilv.obj
	-@IF EXIST dxwrite.obj DEL dxwrite.obj
	-@IF EXIST ilv2dxf.obj DEL ilv2dxf.obj
	-@IF EXIST readdxf.exe DEL readdxf.exe
	-@IF EXIST dxf2ilv.exe DEL dxf2ilv.exe
	-@IF EXIST ilv2dxf.exe DEL ilv2dxf.exe

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

