# --------------------------------------------------------------------------
#
#   Makefile for the 'htmlview' Rogue Wave Views Tools
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



ATEXTSRCDIR  = $(ROOTDIR)\src

# --------------------------------------------------------------------------
PROGRAMS     = htmlview

all: $(PROGRAMS)

HTMLVIEWOBJ  = htmlload.obj wheelint.obj
# --------------------------------------------------------------------------
htmlview: htmlview.exe
htmlview.exe: $(HTMLVIEWOBJ) htmlview.obj viewsico.res
	-@IF EXIST htmlview.exe DEL htmlview.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvpng.lib ilvatext.lib ilvadvgdt.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ htmlview.obj $(HTMLVIEWOBJ) ilvmain.obj viewsico.res

htmlview.obj: "$(ATEXTSRCDIR)\htmlview.cpp"
	-@IF EXIST htmlview.obj DEL htmlview.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" $(CCFLAGS) $(ATEXTSRCDIR)\htmlview.cpp

htmlload.obj: "$(ATEXTSRCDIR)\htmlload.cpp"
	-@IF EXIST htmlload.obj DEL htmlload.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" $(CCFLAGS) $(ATEXTSRCDIR)\htmlload.cpp

wheelint.obj: "$(ATEXTSRCDIR)\wheelint.cpp"
	-@IF EXIST wheelint.obj DEL wheelint.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" $(CCFLAGS) $(ATEXTSRCDIR)\wheelint.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST htmlview.obj DEL htmlview.obj
	-@IF EXIST htmlload.obj DEL htmlload.obj
	-@IF EXIST wheelint.obj DEL wheelint.obj
	-@IF EXIST htmlview.exe DEL htmlview.exe

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

