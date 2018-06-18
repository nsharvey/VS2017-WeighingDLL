# --------------------------------------------------------------------------
#
#   Makefile for the 'bitmaps' Rogue Wave Views Samples
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



PROGRAMS     = readbm bitmaps

all: $(PROGRAMS)

# --------------------------------------------------------------------------
# readbm
# --------------------------------------------------------------------------
readbm: readbm.exe
readbm.exe: readbm.obj viewsico.res
	-@IF EXIST readbm.exe DEL readbm.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ readbm.obj ilvmain.obj viewsico.res

readbm.obj: "..\src\readbm.cpp"
	-@IF EXIST readbm.obj DEL readbm.obj
	$(CCC) $(OUTPUTFILE)$@ /I"..\include" /I"$(VIEWSINCDIR)" $(CCFLAGS) ..\src\readbm.cpp

# --------------------------------------------------------------------------
# bitmaps
DDOBJS       = alpha.obj animate.obj animbm.obj app.obj contrast.obj createbm.obj jpgcomp.obj quantize.obj transition.obj

# --------------------------------------------------------------------------
bitmaps: bitmaps.exe
bitmaps.exe: $(DDOBJS) bitmaps.obj viewsico.res
	-@IF EXIST bitmaps.exe DEL bitmaps.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" ilvjpg.lib ilvpng.lib ilvbmp.lib ilvadvgdt.lib ilvgadgt.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ bitmaps.obj $(DDOBJS) ilvmain.obj viewsico.res

bitmaps.obj: "..\src\bitmaps.cpp"
	-@IF EXIST bitmaps.obj DEL bitmaps.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(CCFLAGS) ..\src\bitmaps.cpp

alpha.obj: "..\src\alpha.cpp"
	-@IF EXIST alpha.obj DEL alpha.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\alpha.cpp

animate.obj: "..\src\animate.cpp"
	-@IF EXIST animate.obj DEL animate.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\animate.cpp

animbm.obj: "..\src\animbm.cpp"
	-@IF EXIST animbm.obj DEL animbm.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\animbm.cpp

app.obj: "..\src\app.cpp"
	-@IF EXIST app.obj DEL app.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\app.cpp

contrast.obj: "..\src\contrast.cpp"
	-@IF EXIST contrast.obj DEL contrast.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\contrast.cpp

createbm.obj: "..\src\createbm.cpp"
	-@IF EXIST createbm.obj DEL createbm.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\createbm.cpp

jpgcomp.obj: "..\src\jpgcomp.cpp"
	-@IF EXIST jpgcomp.obj DEL jpgcomp.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\jpgcomp.cpp

quantize.obj: "..\src\quantize.cpp"
	-@IF EXIST quantize.obj DEL quantize.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\quantize.cpp

transition.obj: "..\src\transition.cpp"
	-@IF EXIST transition.obj DEL transition.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"..\include" $(MINC) $(CCFLAGS) ..\src\transition.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST readbm.obj DEL readbm.obj
	-@IF EXIST bitmaps.obj DEL bitmaps.obj
	-@IF EXIST alpha.obj DEL alpha.obj
	-@IF EXIST animate.obj DEL animate.obj
	-@IF EXIST animbm.obj DEL animbm.obj
	-@IF EXIST app.obj DEL app.obj
	-@IF EXIST contrast.obj DEL contrast.obj
	-@IF EXIST createbm.obj DEL createbm.obj
	-@IF EXIST jpgcomp.obj DEL jpgcomp.obj
	-@IF EXIST quantize.obj DEL quantize.obj
	-@IF EXIST transition.obj DEL transition.obj
	-@IF EXIST readbm.exe DEL readbm.exe
	-@IF EXIST bitmaps.exe DEL bitmaps.exe

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

