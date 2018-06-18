ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

ILVMAPSDIR   = $(ILVMAPSHOME)
ILVMAPSINCDIR= $(ILVMAPSDIR)\include
ILVMAPSLIBDIR= $(ILVMAPSDIR)\lib\$(SYSTEM)\$(FORMAT)

VPFDIR       = $(ILVMAPSDIR)\tools\readers\vpf
VPFINCDIR    = $(VPFDIR)\include
VPFLIBDIR    = $(VPFDIR)\$(SYSTEM)

SYSTEM       = x86_.net2015_14.0
FORMAT       = dll_mda

CCC          = CL
COMPILERFLAGS= /c /DIL_DLL /MD /W3 /EHsc /GR /D_CRT_SECURE_NO_WARNINGS
LD           = LINK
LDFLAGS      = $(LDDBGFLAGS) /NOLOGO /SUBSYSTEM:WINDOWS /MACHINE:I386 /INCREMENTAL:NO
AR           = LINK /NOLOGO $(ARFLAGS) $(LDDBGFLAGS) /INCREMENTAL:NO /SUBSYSTEM:WINDOWS /DLL /MACHINE:I386 /VERSION:6.2
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

VPFDIR       = $(ROOTDIR)
VPFSRCDIR    = $(VPFDIR)\src
VPFINCDIR    = $(VPFDIR)


VPFLIBNAME   = vpf.lib

# ##########################################################################
PROGRAMS=readvpf
# ##########################################################################
all: $(PROGRAMS)

# --------------------------------------------------------------------------
vpf$(LIBEXT) vpf.dll: area.obj areafeature.obj attribute.obj coordinate.obj coverage.obj cursor.obj database.obj date.obj edg.obj error.obj extent.obj feature.obj featureclass.obj featureitem.obj featuretype.obj file.obj header.obj library.obj linefeature.obj point.obj pointfeature.obj projectn.obj reader.obj rng.obj row.obj segment.obj set.obj string.obj table.obj text.obj textfeature.obj thematicindex.obj theme.obj tile.obj tripletid.obj txt.obj vdt.obj vpf.obj "$(ILVMAPSLIBDIR)\ilvmaps$(LIBEXT)" "$(VIEWSLIBDIR)\ilvgadmgr$(LIBEXT)" "$(VIEWSLIBDIR)\ilvtiff$(LIBEXT)" "$(VIEWSLIBDIR)\ilvadvgdt$(LIBEXT)" "$(VIEWSLIBDIR)\ilvgadgt$(LIBEXT)" "$(VIEWSLIBDIR)\ilvmgr$(LIBEXT)" "$(VIEWSLIBDIR)\views$(LIBEXT)" "$(VIEWSLIBDIR)\winviews$(LIBEXT)" "$(VIEWSLIBDIR)\ilog$(LIBEXT)"
	-@IF EXIST vpf$(LIBEXT) DEL vpf$(LIBEXT)
	$(AR) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps$(LIBEXT) ilvgadmgr$(LIBEXT) ilvtiff$(LIBEXT) ilvadvgdt$(LIBEXT) ilvgadgt$(LIBEXT) ilvmgr$(LIBEXT) views$(LIBEXT) winviews$(LIBEXT) ilog$(LIBEXT) $(ALLSYSLIBS) /OUT:vpf.dll /IMPLIB:vpf$(LIBEXT) @<<
area.obj
areafeature.obj
attribute.obj
coordinate.obj
coverage.obj
cursor.obj
database.obj
date.obj
edg.obj
error.obj
extent.obj
feature.obj
featureclass.obj
featureitem.obj
featuretype.obj
file.obj
header.obj
library.obj
linefeature.obj
point.obj
pointfeature.obj
projectn.obj
reader.obj
rng.obj
row.obj
segment.obj
set.obj
string.obj
table.obj
text.obj
textfeature.obj
thematicindex.obj
theme.obj
tile.obj
tripletid.obj
txt.obj
vdt.obj
vpf.obj
<<

area.obj: "$(VPFSRCDIR)\area.cpp"
	-@IF EXIST area.obj DEL area.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\area.cpp

areafeature.obj: "$(VPFSRCDIR)\areafeature.cpp"
	-@IF EXIST areafeature.obj DEL areafeature.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\areafeature.cpp

attribute.obj: "$(VPFSRCDIR)\attribute.cpp"
	-@IF EXIST attribute.obj DEL attribute.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\attribute.cpp

coordinate.obj: "$(VPFSRCDIR)\coordinate.cpp"
	-@IF EXIST coordinate.obj DEL coordinate.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\coordinate.cpp

coverage.obj: "$(VPFSRCDIR)\coverage.cpp"
	-@IF EXIST coverage.obj DEL coverage.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\coverage.cpp

cursor.obj: "$(VPFSRCDIR)\cursor.cpp"
	-@IF EXIST cursor.obj DEL cursor.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\cursor.cpp

database.obj: "$(VPFSRCDIR)\database.cpp"
	-@IF EXIST database.obj DEL database.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\database.cpp

date.obj: "$(VPFSRCDIR)\date.cpp"
	-@IF EXIST date.obj DEL date.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\date.cpp

edg.obj: "$(VPFSRCDIR)\edg.cpp"
	-@IF EXIST edg.obj DEL edg.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\edg.cpp

error.obj: "$(VPFSRCDIR)\error.cpp"
	-@IF EXIST error.obj DEL error.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\error.cpp

extent.obj: "$(VPFSRCDIR)\extent.cpp"
	-@IF EXIST extent.obj DEL extent.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\extent.cpp

feature.obj: "$(VPFSRCDIR)\feature.cpp"
	-@IF EXIST feature.obj DEL feature.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\feature.cpp

featureclass.obj: "$(VPFSRCDIR)\featureclass.cpp"
	-@IF EXIST featureclass.obj DEL featureclass.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\featureclass.cpp

featureitem.obj: "$(VPFSRCDIR)\featureitem.cpp"
	-@IF EXIST featureitem.obj DEL featureitem.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\featureitem.cpp

featuretype.obj: "$(VPFSRCDIR)\featuretype.cpp"
	-@IF EXIST featuretype.obj DEL featuretype.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\featuretype.cpp

file.obj: "$(VPFSRCDIR)\file.cpp"
	-@IF EXIST file.obj DEL file.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\file.cpp

header.obj: "$(VPFSRCDIR)\header.cpp"
	-@IF EXIST header.obj DEL header.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\header.cpp

library.obj: "$(VPFSRCDIR)\library.cpp"
	-@IF EXIST library.obj DEL library.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\library.cpp

linefeature.obj: "$(VPFSRCDIR)\linefeature.cpp"
	-@IF EXIST linefeature.obj DEL linefeature.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\linefeature.cpp

point.obj: "$(VPFSRCDIR)\point.cpp"
	-@IF EXIST point.obj DEL point.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\point.cpp

pointfeature.obj: "$(VPFSRCDIR)\pointfeature.cpp"
	-@IF EXIST pointfeature.obj DEL pointfeature.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\pointfeature.cpp

projectn.obj: "$(VPFSRCDIR)\projectn.cpp"
	-@IF EXIST projectn.obj DEL projectn.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\projectn.cpp

reader.obj: "$(VPFSRCDIR)\reader.cpp"
	-@IF EXIST reader.obj DEL reader.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\reader.cpp

rng.obj: "$(VPFSRCDIR)\rng.cpp"
	-@IF EXIST rng.obj DEL rng.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\rng.cpp

row.obj: "$(VPFSRCDIR)\row.cpp"
	-@IF EXIST row.obj DEL row.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\row.cpp

segment.obj: "$(VPFSRCDIR)\segment.cpp"
	-@IF EXIST segment.obj DEL segment.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\segment.cpp

set.obj: "$(VPFSRCDIR)\set.cpp"
	-@IF EXIST set.obj DEL set.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\set.cpp

string.obj: "$(VPFSRCDIR)\string.cpp"
	-@IF EXIST string.obj DEL string.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\string.cpp

table.obj: "$(VPFSRCDIR)\table.cpp"
	-@IF EXIST table.obj DEL table.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\table.cpp

text.obj: "$(VPFSRCDIR)\text.cpp"
	-@IF EXIST text.obj DEL text.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\text.cpp

textfeature.obj: "$(VPFSRCDIR)\textfeature.cpp"
	-@IF EXIST textfeature.obj DEL textfeature.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\textfeature.cpp

thematicindex.obj: "$(VPFSRCDIR)\thematicindex.cpp"
	-@IF EXIST thematicindex.obj DEL thematicindex.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\thematicindex.cpp

theme.obj: "$(VPFSRCDIR)\theme.cpp"
	-@IF EXIST theme.obj DEL theme.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\theme.cpp

tile.obj: "$(VPFSRCDIR)\tile.cpp"
	-@IF EXIST tile.obj DEL tile.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\tile.cpp

vpf.obj: "$(VPFSRCDIR)\vpf.cpp"
	-@IF EXIST vpf.obj DEL vpf.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\vpf.cpp

tripletid.obj: "$(VPFSRCDIR)\tripletid.cpp"
	-@IF EXIST tripletid.obj DEL tripletid.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\tripletid.cpp

txt.obj: "$(VPFSRCDIR)\txt.cpp"
	-@IF EXIST txt.obj DEL txt.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\txt.cpp

vdt.obj: "$(VPFSRCDIR)\vdt.cpp"
	-@IF EXIST vdt.obj DEL vdt.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\vdt.cpp

# ##########################################################################
# ReadVpf
# ##########################################################################
READVPFOBJS = xorlists.obj vpfilv.obj
# --------------------------------------------------------------------------
readvpf: readvpf.exe
readvpf.exe: $(READVPFOBJS) $(VPFLIBNAME) readvpf.obj viewsico.res
	-@IF EXIST readvpf.exe DEL readvpf.exe
	$(LD) $(LDFLAGS) $(VPFLIBNAME) /LIBPATH:"$(VIEWSLIBDIR)" ilvgadmgr.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ readvpf.obj $(READVPFOBJS) ilvmain.obj viewsico.res

readvpf.obj: "$(VPFSRCDIR)\readvpf.cpp"
	-@IF EXIST readvpf.obj DEL readvpf.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\readvpf.cpp

xorlists.obj: "$(VPFSRCDIR)\xorlists.cpp"
	-@IF EXIST xorlists.obj DEL xorlists.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\xorlists.cpp

vpfilv.obj: "$(VPFSRCDIR)\vpfilv.cpp"
	-@IF EXIST vpfilv.obj DEL vpfilv.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(VPFINCDIR)" /I"$(ILVMAPSINCDIR)" $(CCFLAGS) $(VPFSRCDIR)\vpfilv.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST area.obj DEL area.obj
	-@IF EXIST areafeature.obj DEL areafeature.obj
	-@IF EXIST attribute.obj DEL attribute.obj
	-@IF EXIST coordinate.obj DEL coordinate.obj
	-@IF EXIST coverage.obj DEL coverage.obj
	-@IF EXIST cursor.obj DEL cursor.obj
	-@IF EXIST database.obj DEL database.obj
	-@IF EXIST date.obj DEL date.obj
	-@IF EXIST edg.obj DEL edg.obj
	-@IF EXIST error.obj DEL error.obj
	-@IF EXIST extent.obj DEL extent.obj
	-@IF EXIST feature.obj DEL feature.obj
	-@IF EXIST featureclass.obj DEL featureclass.obj
	-@IF EXIST featureitem.obj DEL featureitem.obj
	-@IF EXIST featuretype.obj DEL featuretype.obj
	-@IF EXIST file.obj DEL file.obj
	-@IF EXIST header.obj DEL header.obj
	-@IF EXIST library.obj DEL library.obj
	-@IF EXIST linefeature.obj DEL linefeature.obj
	-@IF EXIST point.obj DEL point.obj
	-@IF EXIST pointfeature.obj DEL pointfeature.obj
	-@IF EXIST projectn.obj DEL projectn.obj
	-@IF EXIST reader.obj DEL reader.obj
	-@IF EXIST rng.obj DEL rng.obj
	-@IF EXIST row.obj DEL row.obj
	-@IF EXIST segment.obj DEL segment.obj
	-@IF EXIST set.obj DEL set.obj
	-@IF EXIST string.obj DEL string.obj
	-@IF EXIST table.obj DEL table.obj
	-@IF EXIST text.obj DEL text.obj
	-@IF EXIST textfeature.obj DEL textfeature.obj
	-@IF EXIST thematicindex.obj DEL thematicindex.obj
	-@IF EXIST theme.obj DEL theme.obj
	-@IF EXIST tile.obj DEL tile.obj
	-@IF EXIST vpf.obj DEL vpf.obj
	-@IF EXIST tripletid.obj DEL tripletid.obj
	-@IF EXIST txt.obj DEL txt.obj
	-@IF EXIST vdt.obj DEL vdt.obj
	-@IF EXIST readvpf.obj DEL readvpf.obj
	-@IF EXIST xorlists.obj DEL xorlists.obj
	-@IF EXIST vpfilv.obj DEL vpfilv.obj
	-@IF EXIST readvpf.exe DEL readvpf.exe

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

