# --------------------------------------------------------------------------
#                                                                          
# Makefile for the cadrg viewer demo
#                                                                          
# --------------------------------------------------------------------------
#   platform: x64_.net2013_12.0
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


ILVMAPSDIR = $(ROOTDIR)\..\..\..


PROGRAMS     = multires

all: $(PROGRAMS)


# --------------------------------------------------------------------------
multires: multires.exe
multires.exe: multiraster.obj multishape.obj viewer.obj filesel.obj alert.obj main.obj viewsico.res
	-@IF EXIST multires.exe DEL multires.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvjpg.lib ilvmaps.lib ilvtiff.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ main.obj multiraster.obj multishape.obj viewer.obj filesel.obj alert.obj ilvmain.obj viewsico.res

main.obj: "$(ROOTDIR)\src\main.cpp"
	-@IF EXIST main.obj DEL main.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\main.cpp

multishape.obj: "$(ROOTDIR)\src\multishape.cpp"
	-@IF EXIST multishape.obj DEL multishape.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\multishape.cpp

multiraster.obj: "$(ROOTDIR)\src\multiraster.cpp"
	-@IF EXIST multiraster.obj DEL multiraster.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\multiraster.cpp

viewer.obj: "$(ROOTDIR)\src\viewer.cpp"
	-@IF EXIST viewer.obj DEL viewer.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\viewer.cpp

filesel.obj: "$(ROOTDIR)\src\filesel.cpp"
	-@IF EXIST filesel.obj DEL filesel.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\filesel.cpp

alert.obj: "$(ROOTDIR)\src\alert.cpp"
	-@IF EXIST alert.obj DEL alert.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\alert.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST main.obj DEL main.obj
	-@IF EXIST multishape.obj DEL multishape.obj
	-@IF EXIST multiraster.obj DEL multiraster.obj
	-@IF EXIST viewer.obj DEL viewer.obj
	-@IF EXIST filesel.obj DEL filesel.obj
	-@IF EXIST alert.obj DEL alert.obj
	-@IF EXIST multires.exe DEL multires.exe

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

