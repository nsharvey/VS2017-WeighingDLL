# --------------------------------------------------------------------------
#
#   Makefile for the 'windows' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x64_.net2013_12.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SYSTEM       = x64_.net2013_12.0
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


DATADIR      = ..\data

PROGRAMS     = ilvwin winilv metafile ilvmdi gdiplus
all: $(PROGRAMS)

# --------------------------------------------------------------------------
# ilvwin
# --------------------------------------------------------------------------
ilvwin: ilvwin.exe
ilvwin.exe: ilvwin.obj windows.res
	-@IF EXIST ilvwin.exe DEL ilvwin.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ ilvwin.obj ilvmain.obj windows.res

ilvwin.obj: "..\src\ilvwin.cpp"
	-@IF EXIST ilvwin.obj DEL ilvwin.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" $(CCFLAGS) ..\src\ilvwin.cpp

# --------------------------------------------------------------------------
# winilv
# --------------------------------------------------------------------------
winilv: winilv.exe
winilv.exe: winilv.obj windows.res
	-@IF EXIST winilv.exe DEL winilv.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ winilv.obj windows.res

winilv.obj: "..\src\winilv.cpp"
	-@IF EXIST winilv.obj DEL winilv.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" $(CCFLAGS) ..\src\winilv.cpp

# --------------------------------------------------------------------------
# metafile
# --------------------------------------------------------------------------
metafile: metafile.exe
metafile.exe: metafile.obj viewsico.res
	-@IF EXIST metafile.exe DEL metafile.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ metafile.obj ilvmain.obj viewsico.res

metafile.obj: "..\src\metafile.cpp"
	-@IF EXIST metafile.obj DEL metafile.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" $(CCFLAGS) ..\src\metafile.cpp

# --------------------------------------------------------------------------
# ilvmdi
# --------------------------------------------------------------------------
ilvmdi: ilvmdi.exe
ilvmdi.exe: ilvmdi.obj viewsico.res
	-@IF EXIST ilvmdi.exe DEL ilvmdi.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ ilvmdi.obj ilvmain.obj viewsico.res

ilvmdi.obj: "..\src\ilvmdi.cpp"
	-@IF EXIST ilvmdi.obj DEL ilvmdi.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" $(CCFLAGS) ..\src\ilvmdi.cpp

# --------------------------------------------------------------------------
# gdiplus
# --------------------------------------------------------------------------
gdiplus: gdiplus.exe
gdiplus.exe: gdiplus.obj viewsico.res
	-@IF EXIST gdiplus.exe DEL gdiplus.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvjs.lib ilvgadgt.lib views.lib winviews.lib ilog.lib iljs.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ gdiplus.obj ilvmain.obj viewsico.res

gdiplus.obj: "..\src\gdiplus.cpp"
	-@IF EXIST gdiplus.obj DEL gdiplus.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" $(CCFLAGS) ..\src\gdiplus.cpp

# --------------------------------------------------------------------------
# windows.res
# --------------------------------------------------------------------------
windows.res: $(DATADIR)\windows.rc
	$(RC) $(RCFLAGS) -r -fowindows.res /I$(VIEWSDIR)\data\res $(DATADIR)\windows.rc

# --------------------------------------------------------------------------
# clean
# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST ilvwin.obj DEL ilvwin.obj
	-@IF EXIST winilv.obj DEL winilv.obj
	-@IF EXIST metafile.obj DEL metafile.obj
	-@IF EXIST ilvmdi.obj DEL ilvmdi.obj
	-@IF EXIST gdiplus.obj DEL gdiplus.obj
	-@IF EXIST ilvwin.exe DEL ilvwin.exe
	-@IF EXIST winilv.exe DEL winilv.exe
	-@IF EXIST metafile.exe DEL metafile.exe
	-@IF EXIST ilvmdi.exe DEL ilvmdi.exe
	-@IF EXIST gdiplus.exe DEL gdiplus.exe
	-@IF EXIST windows.res DEL windows.res

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

