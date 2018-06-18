# --------------------------------------------------------------------------
#
#   Package 'foundation'
#   Makefile for the 'printing' Rogue Wave Views Samples
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



PROGRAMS     = headfoot photops photpspr photpsdlg photowin phowindc phowinpr

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# headfoot
# --------------------------------------------------------------------------
headfoot: headfoot.exe
headfoot.exe: headfoot.obj viewsico.res
	-@IF EXIST headfoot.exe DEL headfoot.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvprtdlg.lib ilvmgrprint.lib ilvprint.lib ilvbmp.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ headfoot.obj ilvmain.obj viewsico.res

headfoot.obj: "..\src\headfoot.cpp"
	-@IF EXIST headfoot.obj DEL headfoot.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) ..\src\headfoot.cpp

# --------------------------------------------------------------------------
# photops
# --------------------------------------------------------------------------
photops: photops.exe
photops.exe: photops.obj viewsico.res
	-@IF EXIST photops.exe DEL photops.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvmgrprint.lib ilvprint.lib ilvbmp.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ photops.obj ilvmain.obj viewsico.res

photops.obj: "..\src\photops.cpp"
	-@IF EXIST photops.obj DEL photops.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) ..\src\photops.cpp

# --------------------------------------------------------------------------
# photpspr
# --------------------------------------------------------------------------
photpspr: photpspr.exe
photpspr.exe: photpspr.obj viewsico.res
	-@IF EXIST photpspr.exe DEL photpspr.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvprtdlg.lib ilvmgrprint.lib ilvprint.lib ilvbmp.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ photpspr.obj ilvmain.obj viewsico.res

photpspr.obj: "..\src\photpspr.cpp"
	-@IF EXIST photpspr.obj DEL photpspr.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) ..\src\photpspr.cpp

# --------------------------------------------------------------------------
# photpsdlg
# --------------------------------------------------------------------------
photpsdlg: photpsdlg.exe
photpsdlg.exe: photpsdlg.obj viewsico.res
	-@IF EXIST photpsdlg.exe DEL photpsdlg.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvprtdlg.lib ilvmgrprint.lib ilvprint.lib ilvbmp.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ photpsdlg.obj ilvmain.obj viewsico.res

photpsdlg.obj: "..\src\photpsdlg.cpp"
	-@IF EXIST photpsdlg.obj DEL photpsdlg.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) ..\src\photpsdlg.cpp

# --------------------------------------------------------------------------
# photowin
# --------------------------------------------------------------------------
photowin: photowin.exe
photowin.exe: photowin.obj viewsico.res
	-@IF EXIST photowin.exe DEL photowin.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvprint.lib ilvbmp.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ photowin.obj ilvmain.obj viewsico.res

photowin.obj: "..\src\photowin.cpp"
	-@IF EXIST photowin.obj DEL photowin.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) ..\src\photowin.cpp

# --------------------------------------------------------------------------
# phowindc
# --------------------------------------------------------------------------
phowindc: phowindc.exe
phowindc.exe: windcfac.obj phowindc.obj viewsico.res
	-@IF EXIST phowindc.exe DEL phowindc.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvprint.lib ilvbmp.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ phowindc.obj windcfac.obj ilvmain.obj viewsico.res

phowindc.obj: "..\src\phowindc.cpp"
	-@IF EXIST phowindc.obj DEL phowindc.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) ..\src\phowindc.cpp

windcfac.obj: "..\src\windcfac.cpp"
	-@IF EXIST windcfac.obj DEL windcfac.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) ..\src\windcfac.cpp

# --------------------------------------------------------------------------
# phowinpr
# --------------------------------------------------------------------------
phowinpr: phowinpr.exe
phowinpr.exe: phowinpr.obj viewsico.res
	-@IF EXIST phowinpr.exe DEL phowinpr.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvprint.lib ilvbmp.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ phowinpr.obj ilvmain.obj viewsico.res

phowinpr.obj: "..\src\phowinpr.cpp"
	-@IF EXIST phowinpr.obj DEL phowinpr.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) ..\src\phowinpr.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST headfoot.obj DEL headfoot.obj
	-@IF EXIST photops.obj DEL photops.obj
	-@IF EXIST photpspr.obj DEL photpspr.obj
	-@IF EXIST photpsdlg.obj DEL photpsdlg.obj
	-@IF EXIST photowin.obj DEL photowin.obj
	-@IF EXIST phowindc.obj DEL phowindc.obj
	-@IF EXIST windcfac.obj DEL windcfac.obj
	-@IF EXIST phowinpr.obj DEL phowinpr.obj
	-@IF EXIST headfoot.exe DEL headfoot.exe
	-@IF EXIST photops.exe DEL photops.exe
	-@IF EXIST photpspr.exe DEL photpspr.exe
	-@IF EXIST photpsdlg.exe DEL photpsdlg.exe
	-@IF EXIST photowin.exe DEL photowin.exe
	-@IF EXIST phowindc.exe DEL phowindc.exe
	-@IF EXIST phowinpr.exe DEL phowinpr.exe

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

