# --------------------------------------------------------------------------
#                                                                          
# Makefile for the dxf reader and dxf viewer
#                                                                          
# --------------------------------------------------------------------------
#   platform: x86_.net2012_11.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ILVHOME)
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

ILVMAPSDIR   = $(ILVMAPSHOME)
ILVMAPSINCDIR= $(ILVMAPSDIR)\include
ILVMAPSLIBDIR= $(ILVMAPSDIR)\lib\$(SYSTEM)\$(FORMAT)

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


ILVMAPSDIR = $(ROOTDIR)\..\..\..


all: dxfviewer

#---------------------------------------------------------------------------
#
# dxfviewer
#

# --------------------------------------------------------------------------
dxfviewer: dxfviewer.exe
dxfviewer.exe: dxfreader.obj dxffactory.obj dxfbasic.obj dxfviewer.obj viewsico.res
	-@IF EXIST dxfviewer.exe DEL dxfviewer.exe
	$(LD) $(LDFLAGS) $(DXFLIBS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps.lib ilvgadmgr.lib ilvtiff.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ dxfviewer.obj dxfreader.obj dxffactory.obj dxfbasic.obj ilvmain.obj viewsico.res

dxfviewer.obj: "$(ROOTDIR)\src\dxfviewer.cpp"
	-@IF EXIST dxfviewer.obj DEL dxfviewer.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" -DUSE_ADVGDT $(CCFLAGS) $(ROOTDIR)\src\dxfviewer.cpp

dxfbasic.obj: "$(ROOTDIR)\src\dxfbasic.cpp"
	-@IF EXIST dxfbasic.obj DEL dxfbasic.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" -DUSE_ADVGDT $(CCFLAGS) $(ROOTDIR)\src\dxfbasic.cpp

dxfreader.obj: "$(ROOTDIR)\src\dxfreader.cpp"
	-@IF EXIST dxfreader.obj DEL dxfreader.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" -DUSE_ADVGDT $(CCFLAGS) $(ROOTDIR)\src\dxfreader.cpp

dxffactory.obj: "$(ROOTDIR)\src\dxffactory.cpp"
	-@IF EXIST dxffactory.obj DEL dxffactory.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" -DUSE_ADVGDT $(CCFLAGS) $(ROOTDIR)\src\dxffactory.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST dxfviewer.obj DEL dxfviewer.obj
	-@IF EXIST dxfbasic.obj DEL dxfbasic.obj
	-@IF EXIST dxfreader.obj DEL dxfreader.obj
	-@IF EXIST dxffactory.obj DEL dxffactory.obj
	-@IF EXIST dxfviewer.exe DEL dxfviewer.exe

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

