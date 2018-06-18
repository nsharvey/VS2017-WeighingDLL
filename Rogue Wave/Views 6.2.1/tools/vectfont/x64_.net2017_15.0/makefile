# --------------------------------------------------------------------------
#
#   Makefile for the 'vectfont' Rogue Wave Views Tools
#
# --------------------------------------------------------------------------
#   platform: x64_.net2017_15.0
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

SYSTEM       = x64_.net2017_15.0
FORMAT       = dll_mda

CCC          = CL
COMPILERFLAGS= /c /DIL_DLL /MD /W3 /EHsc /GR /D_CRT_SECURE_NO_WARNINGS
LD           = LINK
LDFLAGS      = $(LDDBGFLAGS) /NOLOGO /SUBSYSTEM:WINDOWS /MACHINE:X64 /INCREMENTAL:NO	
AR           = LINK /NOLOGO $(ARFLAGS) $(LDDBGFLAGS) /INCREMENTAL:NO /SUBSYSTEM:WINDOWS /DLL /MACHINE:X64 /VERSION:6.2
OUTPUTFILE   = -Fo
RC           = RC
RCFLAGS      = /c1252 /I"$(VIEWSDIR)\data\res" $(RCDEFINES)
SYSLIBS      = winspool.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib shell32.lib advapi32.lib wsock32.lib imm32.lib
RANLIB       = 
SHLIBEXT     = 
SHLIBEXTFLAGS= 

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
ARFLAGS   = /debug /DEBUGTYPE:CV
!else
LDDBGFLAGS   = 
ARFLAGS   = 
!endif

CCFLAGSSYS   = $(DEBUGFLAGS) $(COMPILERFLAGS)
CCVIEWSFLAGS = -DILVNODEFAULTLOOK
CCFLAGS      = $(OPTIMFLAGS) $(COMPILERFLAGS) $(CCVIEWSFLAGS)
ALLSYSLIBS   = $(ADDLIBS) $(BIDILIBS) $(SYSLIBS)

LIBEXT       = .lib



ILVFONTSLIBNAME= ilvfonts.lib

# --------------------------------------------------------------------------
PROGRAMS     = hershey2ilv mgrvect

all: $(ILVFONTSLIBNAME) $(PROGRAMS)

hershey2ilv.obj: "$(ROOTDIR)\src\hershey2ilv.cpp"
	-@IF EXIST hershey2ilv.obj DEL hershey2ilv.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" /DWINDOWS $(CCFLAGS) $(ROOTDIR)\src\hershey2ilv.cpp

hershey2ilv: hershey2ilv.exe

hershey2ilv.exe: hershey2ilv.obj
	-@if exist hershey2ilv.exe del hershey2ilv.exe
	$(LD) $(LDDBGFLAGS) /NOLOGO /SUBSYSTEM:CONSOLE /MACHINE:X64 $(SYSLIBS) -OUT:$@ hershey2ilv.obj

# --------------------------------------------------------------------------
mgrvect: mgrvect.exe
mgrvect.exe: $(ILVFONTSLIBNAME) mgrvect.obj viewsico.res
	-@IF EXIST mgrvect.exe DEL mgrvect.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(FONTSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvfonts.lib ilvpng.lib ilvgadmgr.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(FONTSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ mgrvect.obj ilvmain.obj viewsico.res

mgrvect.obj: "$(ROOTDIR)\src\mgrvect.cpp"
	-@IF EXIST mgrvect.obj DEL mgrvect.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" $(CCFLAGS) $(ROOTDIR)\src\mgrvect.cpp


# --------------------------------------------------------------------------
ilvfonts$(LIBEXT) ilvfonts.dll: vect.obj vfhash.obj stroke.obj vectlab.obj romans.obj gothgbt.obj romand.obj scriptc.obj scripts.obj gothgrt.obj gothitt.obj truetype.obj "$(VIEWSLIBDIR)\views$(LIBEXT)" "$(VIEWSLIBDIR)\winviews$(LIBEXT)" "$(VIEWSLIBDIR)\ilog$(LIBEXT)"
	-@IF EXIST ilvfonts$(LIBEXT) DEL ilvfonts$(LIBEXT)
	$(AR) /LIBPATH:"$(VIEWSLIBDIR)" views$(LIBEXT) winviews$(LIBEXT) ilog$(LIBEXT) $(ALLSYSLIBS) /OUT:ilvfonts.dll /IMPLIB:ilvfonts$(LIBEXT) @<<
vect.obj
vfhash.obj
stroke.obj
vectlab.obj
romans.obj
gothgbt.obj
romand.obj
scriptc.obj
scripts.obj
gothgrt.obj
gothitt.obj
truetype.obj
<<

truetype.obj: "$(ROOTDIR)\src\truetype.cpp"
	-@IF EXIST truetype.obj DEL truetype.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) $(ROOTDIR)\src\truetype.cpp

vect.obj: "$(ROOTDIR)\src\vect.cpp"
	-@IF EXIST vect.obj DEL vect.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) $(ROOTDIR)\src\vect.cpp

vfhash.obj: "$(ROOTDIR)\src\vfhash.cpp"
	-@IF EXIST vfhash.obj DEL vfhash.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) $(ROOTDIR)\src\vfhash.cpp

vectlab.obj: "$(ROOTDIR)\src\vectlab.cpp"
	-@IF EXIST vectlab.obj DEL vectlab.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) $(ROOTDIR)\src\vectlab.cpp

stroke.obj: "$(ROOTDIR)\src\stroke.cpp"
	-@IF EXIST stroke.obj DEL stroke.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) $(ROOTDIR)\src\stroke.cpp

# Fonts:
gothgbt.obj: "gothgbt.cpp"
	-@IF EXIST gothgbt.obj DEL gothgbt.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) gothgbt.cpp

gothgrt.obj: "gothgrt.cpp"
	-@IF EXIST gothgrt.obj DEL gothgrt.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) gothgrt.cpp

gothitt.obj: "gothitt.cpp"
	-@IF EXIST gothitt.obj DEL gothitt.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) gothitt.cpp

romand.obj: "romand.cpp"
	-@IF EXIST romand.obj DEL romand.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) romand.cpp

romans.obj: "romans.cpp"
	-@IF EXIST romans.obj DEL romans.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) romans.cpp

romant.obj: "romant.cpp"
	-@IF EXIST romant.obj DEL romant.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) romant.cpp

scriptc.obj: "scriptc.cpp"
	-@IF EXIST scriptc.obj DEL scriptc.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) scriptc.cpp

scripts.obj: "scripts.cpp"
	-@IF EXIST scripts.obj DEL scripts.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(FONTSINCDIR)" -DILVVFLIB -DWIN32_LEAN_AND_MEAN $(CCFLAGS) scripts.cpp

# Src files
gothgbt.cpp: hershey2ilv
	hershey2ilv gothgbt
gothgrt.cpp: hershey2ilv
	hershey2ilv gothgrt
gothitt.cpp: hershey2ilv
	hershey2ilv gothitt
romand.cpp: hershey2ilv
	hershey2ilv romand
romans.cpp: hershey2ilv
	hershey2ilv romans
romant.cpp: hershey2ilv
	hershey2ilv romant
scriptc.cpp: hershey2ilv
	hershey2ilv scriptc
scripts.cpp: hershey2ilv
	hershey2ilv scripts

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST hershey2ilv.obj DEL hershey2ilv.obj
	-@IF EXIST mgrvect.obj DEL mgrvect.obj
	-@IF EXIST truetype.obj DEL truetype.obj
	-@IF EXIST vect.obj DEL vect.obj
	-@IF EXIST vfhash.obj DEL vfhash.obj
	-@IF EXIST vectlab.obj DEL vectlab.obj
	-@IF EXIST stroke.obj DEL stroke.obj
	-@IF EXIST gothgbt.obj DEL gothgbt.obj
	-@IF EXIST gothgrt.obj DEL gothgrt.obj
	-@IF EXIST gothitt.obj DEL gothitt.obj
	-@IF EXIST romand.obj DEL romand.obj
	-@IF EXIST romans.obj DEL romans.obj
	-@IF EXIST romant.obj DEL romant.obj
	-@IF EXIST scriptc.obj DEL scriptc.obj
	-@IF EXIST scripts.obj DEL scripts.obj
	-@IF EXIST mgrvect.exe DEL mgrvect.exe
	-@IF EXIST gothgbt.cpp DEL gothgbt.cpp
	-@IF EXIST gothgrt.cpp DEL gothgrt.cpp
	-@IF EXIST gothitt.cpp DEL gothitt.cpp
	-@IF EXIST romand.cpp DEL romand.cpp
	-@IF EXIST romans.cpp DEL romans.cpp
	-@IF EXIST romant.cpp DEL romant.cpp
	-@IF EXIST scriptc.cpp DEL scriptc.cpp
	-@IF EXIST scripts.cpp DEL scripts.cpp

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

