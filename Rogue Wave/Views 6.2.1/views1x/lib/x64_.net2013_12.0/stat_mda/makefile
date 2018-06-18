ROOTDIR      = ..\..

VIEWSDIR     = $(ROOTDIR)\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

VIEWS31DIR   = $(VIEWSDIR)\views31
VIEWS31INCDIR= $(VIEWS31DIR)\include
VIEWS31LIBDIR= $(VIEWS31DIR)\lib\$(SYSTEM)\$(FORMAT)

VIEWS1XDIR   = $(VIEWSDIR)\views1x
VIEWS1XINCDIR= $(VIEWS1XDIR)\include
VIEWS1XLIBDIR= $(VIEWS1XDIR)\lib\$(SYSTEM)\$(FORMAT)

SYSTEM       = x64_.net2013_12.0
FORMAT       = stat_mda

CCC          = CL
COMPILERFLAGS= /c /MD /W3 /EHsc /GR /D_CRT_SECURE_NO_WARNINGS
LD           = LINK
LDFLAGS      = $(LDDBGFLAGS) /NOLOGO /SUBSYSTEM:WINDOWS /MACHINE:X64 /INCREMENTAL:NO	
AR           = LIB /NOLOGO /MACHINE:X64 /SUBSYSTEM:WINDOWS
OUTPUTFILE   = -Fo
RC           = RC
RCFLAGS      = /c1252 /I"$(VIEWSDIR)\data\res" $(RCDEFINES)
SYSLIBS      = winspool.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib shell32.lib advapi32.lib wsock32.lib imm32.lib
RANLIB       = 

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
CCFLAGS      = $(OPTIMFLAGS) $(COMPILERFLAGS)
ALLSYSLIBS   = $(ADDLIBS) $(BIDILIBS) $(SYSLIBS)

LIBEXT       = .lib
VIEWS1XDIR    = $(VIEWSDIR)\views1x
VIEWS1XSRCDIR = $(VIEWS1XDIR)\src




LIBVIEWS1X  = views1x.lib

DISPLAYDIR  = windows

# --------------------------------------------------------------------------
PROGRAMS     = 

SPECIALOBJS  = strinter.obj

all: libs $(SPECIALOBJS) $(PROGRAMS) 

libs: $(LIBVIEWS1X)

# #########################################################################
# Library
# #########################################################################
# --------------------------------------------------------------------------
views1x$(LIBEXT) views1x.dll: rcview.obj pyrrect.obj paledit.obj mkpyrint.obj mgrhook.obj mgrpal.obj cellpal.obj mgridint.obj grid.obj gridint.obj gview.obj vlabel.obj cliplab.obj highlow.obj
	-@IF EXIST views1x$(LIBEXT) DEL views1x$(LIBEXT)
	$(AR) /OUT:views1x$(LIBEXT) @<<
rcview.obj
pyrrect.obj
paledit.obj
mkpyrint.obj
mgrhook.obj
mgrpal.obj
cellpal.obj
mgridint.obj
grid.obj
gridint.obj
gview.obj
vlabel.obj
cliplab.obj
highlow.obj
<<

rcview.obj: "$(VIEWS1XSRCDIR)\rcview.cpp"
	-@IF EXIST rcview.obj DEL rcview.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS1XDIR)\include" /I"$(VIEWSINCDIR)" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\rcview.cpp

pyrrect.obj: "$(VIEWS1XSRCDIR)\pyrrect.cpp"
	-@IF EXIST pyrrect.obj DEL pyrrect.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS1XDIR)\include" /I"$(VIEWSINCDIR)" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\pyrrect.cpp

paledit.obj: "$(VIEWS1XSRCDIR)\paledit.cpp"
	-@IF EXIST paledit.obj DEL paledit.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS31INCDIR)" /I"$(VIEWSINCDIR)" /I"$(VIEWS1XDIR)\include" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\paledit.cpp

mkpyrint.obj: "$(VIEWS1XSRCDIR)\mkpyrint.cpp"
	-@IF EXIST mkpyrint.obj DEL mkpyrint.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS1XDIR)\include" /I"$(VIEWSINCDIR)" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\mkpyrint.cpp

strinter.obj: "$(VIEWS1XSRCDIR)\$(DISPLAYDIR)\strinter.cpp"
	-@IF EXIST strinter.obj DEL strinter.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS1XDIR)\include" /I"$(VIEWSINCDIR)" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\$(DISPLAYDIR)\strinter.cpp

mgrhook.obj: "$(VIEWS1XSRCDIR)\mgrhook.cpp"
	-@IF EXIST mgrhook.obj DEL mgrhook.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS1XDIR)\include" /I"$(VIEWSINCDIR)" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\mgrhook.cpp

mgrpal.obj: "$(VIEWS1XSRCDIR)\mgrpal.cpp"
	-@IF EXIST mgrpal.obj DEL mgrpal.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS1XDIR)\include" /I"$(VIEWSINCDIR)" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\mgrpal.cpp

cellpal.obj: "$(VIEWS1XSRCDIR)\cellpal.cpp"
	-@IF EXIST cellpal.obj DEL cellpal.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS31INCDIR)" /I"$(VIEWSINCDIR)" /I"$(VIEWS1XDIR)\include" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\cellpal.cpp

mgridint.obj: "$(VIEWS1XSRCDIR)\mgridint.cpp"
	-@IF EXIST mgridint.obj DEL mgridint.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS1XDIR)\include" /I"$(VIEWSINCDIR)" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\mgridint.cpp

grid.obj: "$(VIEWS1XSRCDIR)\grid.cpp"
	-@IF EXIST grid.obj DEL grid.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS1XDIR)\include" /I"$(VIEWSINCDIR)" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\grid.cpp

gridint.obj: "$(VIEWS1XSRCDIR)\gridint.cpp"
	-@IF EXIST gridint.obj DEL gridint.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS1XDIR)\include" /I"$(VIEWSINCDIR)" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\gridint.cpp

gview.obj: "$(VIEWS1XSRCDIR)\gview.cpp"
	-@IF EXIST gview.obj DEL gview.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS1XDIR)\include" /I"$(VIEWSINCDIR)" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\gview.cpp

vlabel.obj: "$(VIEWS1XSRCDIR)\vlabel.cpp"
	-@IF EXIST vlabel.obj DEL vlabel.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS1XDIR)\include" /I"$(VIEWSINCDIR)" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\vlabel.cpp

cliplab.obj: "$(VIEWS1XSRCDIR)\cliplab.cpp"
	-@IF EXIST cliplab.obj DEL cliplab.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS1XDIR)\include" /I"$(VIEWSINCDIR)" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\cliplab.cpp

highlow.obj: "$(VIEWS1XSRCDIR)\highlow.cpp"
	-@IF EXIST highlow.obj DEL highlow.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWS31INCDIR)" /I"$(VIEWSINCDIR)" /I"$(VIEWS1XDIR)\include" -DILVBUILDLIBS -DILVVIEWS1X $(CCFLAGS) $(VIEWS1XSRCDIR)\highlow.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST rcview.obj DEL rcview.obj
	-@IF EXIST pyrrect.obj DEL pyrrect.obj
	-@IF EXIST paledit.obj DEL paledit.obj
	-@IF EXIST mkpyrint.obj DEL mkpyrint.obj
	-@IF EXIST strinter.obj DEL strinter.obj
	-@IF EXIST mgrhook.obj DEL mgrhook.obj
	-@IF EXIST mgrpal.obj DEL mgrpal.obj
	-@IF EXIST cellpal.obj DEL cellpal.obj
	-@IF EXIST mgridint.obj DEL mgridint.obj
	-@IF EXIST grid.obj DEL grid.obj
	-@IF EXIST gridint.obj DEL gridint.obj
	-@IF EXIST gview.obj DEL gview.obj
	-@IF EXIST vlabel.obj DEL vlabel.obj
	-@IF EXIST cliplab.obj DEL cliplab.obj
	-@IF EXIST highlow.obj DEL highlow.obj

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

