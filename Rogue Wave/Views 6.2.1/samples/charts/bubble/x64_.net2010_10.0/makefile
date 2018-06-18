# --------------------------------------------------------------------------
#
#   Makefile for the 'charts/bubble' Rogue Wave Views Sample
#
# --------------------------------------------------------------------------
#   platform: x64_.net2010_10.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SYSTEM       = x64_.net2010_10.0
FORMAT       = dll_mda

CCC          = cl
COMPILERFLAGS= /c /DWIN64 /DIL_DLL /MD /nologo /W3 /EHsc /GR /D_CRT_SECURE_NO_DEPRECATE
LD           = link
LDFLAGS      = $(LDDBGFLAGS) /NOLOGO /SUBSYSTEM:WINDOWS /MACHINE:X64 /INCREMENTAL:NO	
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


SAMPLEOBJS   = samputil.obj

PROGRAMS     = bubble

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# bubble
# --------------------------------------------------------------------------
bubble: bubble.exe
bubble.exe: $(SAMPLEOBJS) bubble.obj viewsico.res
	-@IF EXIST bubble.exe DEL bubble.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvpng.lib ilvcharts.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ bubble.obj $(SAMPLEOBJS) ilvmain.obj viewsico.res

bubble.obj: "$(ROOTDIR)\src\bubble.cpp"
	-@IF EXIST bubble.obj DEL bubble.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\src\bubble.cpp

# --------------------------------------------------------------------------
samputil.obj: "$(ROOTDIR)\..\src\samputil.cpp"
	-@IF EXIST samputil.obj DEL samputil.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" /I"$(ROOTDIR)\..\include" $(CCFLAGS) $(ROOTDIR)\..\src\samputil.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST bubble.obj DEL bubble.obj
	-@IF EXIST samputil.obj DEL samputil.obj
	-@IF EXIST bubble.exe DEL bubble.exe

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

