# --------------------------------------------------------------------------
#                                                                          
# Makefile for the vector projection demo
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


ILVMAPSDIR = $(ROOTDIR)\..\..\..\


PROGRAMS     = loadOnDemand mainpol useproj proj_step1 proj_step2 proj_step3 useviews shapeLOD imageReader tiff maptileloader

all: $(PROGRAMS)


# --------------------------------------------------------------------------
loadOnDemand: loadOnDemand.exe
loadOnDemand.exe: loadOnDemand.obj
	-@IF EXIST loadOnDemand.exe DEL loadOnDemand.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps.lib ilvtiff.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ loadOnDemand.obj ilvmain.obj

loadOnDemand.obj: "$(ROOTDIR)\src\loadOnDemand.cpp"
	-@IF EXIST loadOnDemand.obj DEL loadOnDemand.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\loadOnDemand.cpp

# --------------------------------------------------------------------------
mainpol: mainpol.exe
mainpol.exe: simplePolylineReader.obj mainpol.obj
	-@IF EXIST mainpol.exe DEL mainpol.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps.lib ilvtiff.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ mainpol.obj simplePolylineReader.obj ilvmain.obj

mainpol.obj: "$(ROOTDIR)\src\mainpol.cpp"
	-@IF EXIST mainpol.obj DEL mainpol.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\mainpol.cpp

simplePolylineReader.obj: "$(ROOTDIR)\src\simplePolylineReader.cpp"
	-@IF EXIST simplePolylineReader.obj DEL simplePolylineReader.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\simplePolylineReader.cpp

# --------------------------------------------------------------------------
useviews: useviews.exe
useviews.exe: useviews.obj viewsico.res
	-@IF EXIST useviews.exe DEL useviews.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps.lib ilvgadmgr.lib ilvtiff.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ useviews.obj ilvmain.obj viewsico.res

useviews.obj: "$(ROOTDIR)\src\useviews.cpp"
	-@IF EXIST useviews.obj DEL useviews.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\useviews.cpp

# --------------------------------------------------------------------------
useproj: useproj.exe
useproj.exe: useproj.obj
	-@IF EXIST useproj.exe DEL useproj.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps.lib ilvtiff.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ useproj.obj ilvmain.obj

useproj.obj: "$(ROOTDIR)\src\useproj.cpp"
	-@IF EXIST useproj.obj DEL useproj.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\useproj.cpp

# --------------------------------------------------------------------------
proj_step1: proj_step1.exe
proj_step1.exe: proj_step1.obj
	-@IF EXIST proj_step1.exe DEL proj_step1.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps.lib ilvtiff.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ proj_step1.obj ilvmain.obj

proj_step1.obj: "$(ROOTDIR)\src\proj_step1.cpp"
	-@IF EXIST proj_step1.obj DEL proj_step1.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\proj_step1.cpp

# --------------------------------------------------------------------------
proj_step2: proj_step2.exe
proj_step2.exe: proj_step2.obj
	-@IF EXIST proj_step2.exe DEL proj_step2.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps.lib ilvtiff.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ proj_step2.obj ilvmain.obj

proj_step2.obj: "$(ROOTDIR)\src\proj_step2.cpp"
	-@IF EXIST proj_step2.obj DEL proj_step2.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\proj_step2.cpp

# --------------------------------------------------------------------------
proj_step3: proj_step3.exe
proj_step3.exe: proj_step3.obj
	-@IF EXIST proj_step3.exe DEL proj_step3.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps.lib ilvtiff.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ proj_step3.obj ilvmain.obj

proj_step3.obj: "$(ROOTDIR)\src\proj_step3.cpp"
	-@IF EXIST proj_step3.obj DEL proj_step3.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\proj_step3.cpp

# --------------------------------------------------------------------------
shapeLOD: shapeLOD.exe
shapeLOD.exe: shapeLOD.obj
	-@IF EXIST shapeLOD.exe DEL shapeLOD.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps.lib ilvtiff.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ shapeLOD.obj ilvmain.obj

shapeLOD.obj: "$(ROOTDIR)\src\shapeLOD.cpp"
	-@IF EXIST shapeLOD.obj DEL shapeLOD.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\shapeLOD.cpp

# --------------------------------------------------------------------------
imageReader: imageReader.exe
imageReader.exe: imageReader.obj viewsico.res
	-@IF EXIST imageReader.exe DEL imageReader.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvjpg.lib ilvmaps.lib ilvtiff.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ imageReader.obj ilvmain.obj viewsico.res

imageReader.obj: "$(ROOTDIR)\src\imageReader.cpp"
	-@IF EXIST imageReader.obj DEL imageReader.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\imageReader.cpp

# --------------------------------------------------------------------------
tiff: tiff.exe
tiff.exe: tiff.obj viewsico.res
	-@IF EXIST tiff.exe DEL tiff.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps.lib ilvtiff.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ tiff.obj ilvmain.obj viewsico.res

tiff.obj: "$(ROOTDIR)\src\tiff.cpp"
	-@IF EXIST tiff.obj DEL tiff.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\tiff.cpp

# --------------------------------------------------------------------------
maptileloader: maptileloader.exe
maptileloader.exe: maptileloader.obj viewsico.res
	-@IF EXIST maptileloader.exe DEL maptileloader.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps.lib ilvtiff.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ maptileloader.obj ilvmain.obj viewsico.res

maptileloader.obj: "$(ROOTDIR)\src\maptileloader.cpp"
	-@IF EXIST maptileloader.obj DEL maptileloader.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\maptileloader.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST loadOnDemand.obj DEL loadOnDemand.obj
	-@IF EXIST mainpol.obj DEL mainpol.obj
	-@IF EXIST simplePolylineReader.obj DEL simplePolylineReader.obj
	-@IF EXIST useviews.obj DEL useviews.obj
	-@IF EXIST useproj.obj DEL useproj.obj
	-@IF EXIST proj_step1.obj DEL proj_step1.obj
	-@IF EXIST proj_step2.obj DEL proj_step2.obj
	-@IF EXIST proj_step3.obj DEL proj_step3.obj
	-@IF EXIST shapeLOD.obj DEL shapeLOD.obj
	-@IF EXIST imageReader.obj DEL imageReader.obj
	-@IF EXIST tiff.obj DEL tiff.obj
	-@IF EXIST maptileloader.obj DEL maptileloader.obj
	-@IF EXIST loadOnDemand.exe DEL loadOnDemand.exe
	-@IF EXIST mainpol.exe DEL mainpol.exe
	-@IF EXIST useviews.exe DEL useviews.exe
	-@IF EXIST useproj.exe DEL useproj.exe
	-@IF EXIST proj_step1.exe DEL proj_step1.exe
	-@IF EXIST proj_step2.exe DEL proj_step2.exe
	-@IF EXIST proj_step3.exe DEL proj_step3.exe
	-@IF EXIST shapeLOD.exe DEL shapeLOD.exe
	-@IF EXIST imageReader.exe DEL imageReader.exe
	-@IF EXIST tiff.exe DEL tiff.exe
	-@IF EXIST maptileloader.exe DEL maptileloader.exe

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

