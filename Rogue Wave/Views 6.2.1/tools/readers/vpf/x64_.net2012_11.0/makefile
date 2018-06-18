# --------------------------------------------------------------------------
#                                                                          
# Makefile for the vpf viewer
#                                                                          
# --------------------------------------------------------------------------
#   platform: x64_.net2012_11.0
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

VPFDIR       = $(ILVMAPSDIR)\tools\readers\vpf
VPFINCDIR    = $(VPFDIR)\include
VPFLIBDIR    = $(VPFDIR)\$(SYSTEM)

SYSTEM       = x64_.net2012_11.0
FORMAT       = dll_mda

CCC          = cl
COMPILERFLAGS= /c /DWIN64 /DIL_DLL /MD /nologo /W3 /EHsc /GR /D_CRT_SECURE_NO_DEPRECATE
LD           = link
LDFLAGS      = $(LDDBGFLAGS) /NOLOGO /SUBSYSTEM:WINDOWS /MACHINE:X64 /INCREMENTAL:NO	
AR           = link $(LDDBGFLAGS) /INCREMENTAL:NO /NOLOGO /SUBSYSTEM:WINDOWS /DLL $(ARFLAGS) /MACHINE:X64 /VERSION:6.2
OUTPUTFILE   = -Fo
RC           = rc
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

ILVMAPSDIR = $(ROOTDIR)\..\..\..


VPFSRCDIR    = $(VPFDIR)\src

VPFLIBNAME   = vpf.lib

# ##########################################################################
PROGRAMS=vpfviewer
# ##########################################################################
all: $(VPFLIBNAME) $(PROGRAMS)

# --------------------------------------------------------------------------
vpf$(LIBEXT) vpf.dll: area.obj areafeature.obj attribute.obj coordinate.obj coverage.obj cursor.obj database.obj date.obj edg.obj error.obj extent.obj feature.obj featureclass.obj featureitem.obj featuretype.obj file.obj header.obj library.obj linefeature.obj point.obj pointfeature.obj query.obj queryparse.obj rng.obj row.obj segment.obj set.obj string.obj table.obj text.obj textfeature.obj thematicindex.obj theme.obj tile.obj tripletid.obj txt.obj vdt.obj vpf.obj parser.obj "$(ILVMAPSLIBDIR)\ilvmaps$(LIBEXT)" "$(VIEWSLIBDIR)\ilvgadmgr$(LIBEXT)" "$(VIEWSLIBDIR)\ilvtiff$(LIBEXT)" "$(VIEWSLIBDIR)\ilvadvgdt$(LIBEXT)" "$(VIEWSLIBDIR)\ilvgadgt$(LIBEXT)" "$(VIEWSLIBDIR)\ilvmgr$(LIBEXT)" "$(VIEWSLIBDIR)\views$(LIBEXT)" "$(VIEWSLIBDIR)\winviews$(LIBEXT)" "$(VIEWSLIBDIR)\ilog$(LIBEXT)"
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
query.obj
queryparse.obj
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
parser.obj
<<

area.obj: "$(ROOTDIR)\src\area.cpp"
	-@IF EXIST area.obj DEL area.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\area.cpp

areafeature.obj: "$(ROOTDIR)\src\areafeature.cpp"
	-@IF EXIST areafeature.obj DEL areafeature.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\areafeature.cpp

attribute.obj: "$(ROOTDIR)\src\attribute.cpp"
	-@IF EXIST attribute.obj DEL attribute.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\attribute.cpp

coordinate.obj: "$(ROOTDIR)\src\coordinate.cpp"
	-@IF EXIST coordinate.obj DEL coordinate.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\coordinate.cpp

coverage.obj: "$(ROOTDIR)\src\coverage.cpp"
	-@IF EXIST coverage.obj DEL coverage.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\coverage.cpp

cursor.obj: "$(ROOTDIR)\src\cursor.cpp"
	-@IF EXIST cursor.obj DEL cursor.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\cursor.cpp

database.obj: "$(ROOTDIR)\src\database.cpp"
	-@IF EXIST database.obj DEL database.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\database.cpp

date.obj: "$(ROOTDIR)\src\date.cpp"
	-@IF EXIST date.obj DEL date.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\date.cpp

edg.obj: "$(ROOTDIR)\src\edg.cpp"
	-@IF EXIST edg.obj DEL edg.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\edg.cpp

end.obj: "$(ROOTDIR)\src\end.cpp"
	-@IF EXIST end.obj DEL end.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\end.cpp

error.obj: "$(ROOTDIR)\src\error.cpp"
	-@IF EXIST error.obj DEL error.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\error.cpp

extent.obj: "$(ROOTDIR)\src\extent.cpp"
	-@IF EXIST extent.obj DEL extent.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\extent.cpp

fac.obj: "$(ROOTDIR)\src\fac.cpp"
	-@IF EXIST fac.obj DEL fac.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\fac.cpp

fbr.obj: "$(ROOTDIR)\src\fbr.cpp"
	-@IF EXIST fbr.obj DEL fbr.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\fbr.cpp

fca.obj: "$(ROOTDIR)\src\fca.cpp"
	-@IF EXIST fca.obj DEL fca.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\fca.cpp

fcs.obj: "$(ROOTDIR)\src\fcs.cpp"
	-@IF EXIST fcs.obj DEL fcs.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\fcs.cpp

feature.obj: "$(ROOTDIR)\src\feature.cpp"
	-@IF EXIST feature.obj DEL feature.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\feature.cpp

featureclass.obj: "$(ROOTDIR)\src\featureclass.cpp"
	-@IF EXIST featureclass.obj DEL featureclass.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\featureclass.cpp

featureitem.obj: "$(ROOTDIR)\src\featureitem.cpp"
	-@IF EXIST featureitem.obj DEL featureitem.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\featureitem.cpp

featuretype.obj: "$(ROOTDIR)\src\featuretype.cpp"
	-@IF EXIST featuretype.obj DEL featuretype.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\featuretype.cpp

file.obj: "$(ROOTDIR)\src\file.cpp"
	-@IF EXIST file.obj DEL file.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\file.cpp

header.obj: "$(ROOTDIR)\src\header.cpp"
	-@IF EXIST header.obj DEL header.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\header.cpp

lat.obj: "$(ROOTDIR)\src\lat.cpp"
	-@IF EXIST lat.obj DEL lat.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\lat.cpp

lht.obj: "$(ROOTDIR)\src\lht.cpp"
	-@IF EXIST lht.obj DEL lht.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\lht.cpp

library.obj: "$(ROOTDIR)\src\library.cpp"
	-@IF EXIST library.obj DEL library.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\library.cpp

linefeature.obj: "$(ROOTDIR)\src\linefeature.cpp"
	-@IF EXIST linefeature.obj DEL linefeature.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\linefeature.cpp

point.obj: "$(ROOTDIR)\src\point.cpp"
	-@IF EXIST point.obj DEL point.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\point.cpp

pointfeature.obj: "$(ROOTDIR)\src\pointfeature.cpp"
	-@IF EXIST pointfeature.obj DEL pointfeature.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\pointfeature.cpp

query.obj: "$(ROOTDIR)\src\query.cpp"
	-@IF EXIST query.obj DEL query.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\query.cpp

queryparse.obj: "$(ROOTDIR)\src\queryparse.cpp"
	-@IF EXIST queryparse.obj DEL queryparse.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\queryparse.cpp

rng.obj: "$(ROOTDIR)\src\rng.cpp"
	-@IF EXIST rng.obj DEL rng.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\rng.cpp

row.obj: "$(ROOTDIR)\src\row.cpp"
	-@IF EXIST row.obj DEL row.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\row.cpp

segment.obj: "$(ROOTDIR)\src\segment.cpp"
	-@IF EXIST segment.obj DEL segment.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\segment.cpp

set.obj: "$(ROOTDIR)\src\set.cpp"
	-@IF EXIST set.obj DEL set.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\set.cpp

string.obj: "$(ROOTDIR)\src\string.cpp"
	-@IF EXIST string.obj DEL string.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\string.cpp

table.obj: "$(ROOTDIR)\src\table.cpp"
	-@IF EXIST table.obj DEL table.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\table.cpp

text.obj: "$(ROOTDIR)\src\text.cpp"
	-@IF EXIST text.obj DEL text.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\text.cpp

textfeature.obj: "$(ROOTDIR)\src\textfeature.cpp"
	-@IF EXIST textfeature.obj DEL textfeature.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\textfeature.cpp

thematicindex.obj: "$(ROOTDIR)\src\thematicindex.cpp"
	-@IF EXIST thematicindex.obj DEL thematicindex.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\thematicindex.cpp

theme.obj: "$(ROOTDIR)\src\theme.cpp"
	-@IF EXIST theme.obj DEL theme.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\theme.cpp

tile.obj: "$(ROOTDIR)\src\tile.cpp"
	-@IF EXIST tile.obj DEL tile.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\tile.cpp

tripletid.obj: "$(ROOTDIR)\src\tripletid.cpp"
	-@IF EXIST tripletid.obj DEL tripletid.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\tripletid.cpp

txt.obj: "$(ROOTDIR)\src\txt.cpp"
	-@IF EXIST txt.obj DEL txt.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\txt.cpp

vdt.obj: "$(ROOTDIR)\src\vdt.cpp"
	-@IF EXIST vdt.obj DEL vdt.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\vdt.cpp

vpf.obj: "$(ROOTDIR)\src\vpf.cpp"
	-@IF EXIST vpf.obj DEL vpf.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\vpf.cpp

parser.obj: "$(ROOTDIR)\src\parser.cpp"
	-@IF EXIST parser.obj DEL parser.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(ROOTDIR)\src\parser.cpp

# ##########################################################################
# ReadVpf
# ##########################################################################
READVPFOBJS = application.obj arearesourcedialog.obj g_database.obj databaselist.obj g_error.obj extentdialog.obj layer.obj layers.obj lineresourcedialog.obj manager.obj palette.obj pointresourcedialog.obj reader.obj resourcedialog.obj serialize.obj textresourcedialog.obj views.obj

# --------------------------------------------------------------------------
vpfviewer: vpfviewer.exe
vpfviewer.exe: $(READVPFOBJS) vpfviewer.obj viewsico.res
	-@IF EXIST vpfviewer.exe DEL vpfviewer.exe
	$(LD) $(LDFLAGS) $(VPFLIBNAME) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvmaps.lib ilvgadmgr.lib ilvtiff.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib views.lib winviews.lib ilog.lib $(VIEWSMAPSSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ vpfviewer.obj $(READVPFOBJS) ilvmain.obj viewsico.res

vpfviewer.obj: "$(VPFSRCDIR)\gui\vpfviewer.cpp"
	-@IF EXIST vpfviewer.obj DEL vpfviewer.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\vpfviewer.cpp

arearesourcedialog.obj: "$(VPFSRCDIR)\gui\arearesourcedialog.cpp"
	-@IF EXIST arearesourcedialog.obj DEL arearesourcedialog.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\arearesourcedialog.cpp

application.obj: "$(VPFSRCDIR)\gui\application.cpp"
	-@IF EXIST application.obj DEL application.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\application.cpp

g_database.obj: "$(VPFSRCDIR)\gui\database.cpp"
	-@IF EXIST g_database.obj DEL g_database.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\database.cpp

databaselist.obj: "$(VPFSRCDIR)\gui\databaselist.cpp"
	-@IF EXIST databaselist.obj DEL databaselist.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\databaselist.cpp

g_error.obj: "$(VPFSRCDIR)\gui\error.cpp"
	-@IF EXIST g_error.obj DEL g_error.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\error.cpp

extentdialog.obj: "$(VPFSRCDIR)\gui\extentdialog.cpp"
	-@IF EXIST extentdialog.obj DEL extentdialog.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\extentdialog.cpp

layer.obj: "$(VPFSRCDIR)\gui\layer.cpp"
	-@IF EXIST layer.obj DEL layer.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\layer.cpp

layers.obj: "$(VPFSRCDIR)\gui\layers.cpp"
	-@IF EXIST layers.obj DEL layers.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\layers.cpp

lineresourcedialog.obj: "$(VPFSRCDIR)\gui\lineresourcedialog.cpp"
	-@IF EXIST lineresourcedialog.obj DEL lineresourcedialog.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\lineresourcedialog.cpp

manager.obj: "$(VPFSRCDIR)\gui\manager.cpp"
	-@IF EXIST manager.obj DEL manager.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\manager.cpp

palette.obj: "$(VPFSRCDIR)\gui\palette.cpp"
	-@IF EXIST palette.obj DEL palette.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\palette.cpp

pointresourcedialog.obj: "$(VPFSRCDIR)\gui\pointresourcedialog.cpp"
	-@IF EXIST pointresourcedialog.obj DEL pointresourcedialog.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\pointresourcedialog.cpp

reader.obj: "$(VPFSRCDIR)\gui\reader.cpp"
	-@IF EXIST reader.obj DEL reader.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\reader.cpp

resourcedialog.obj: "$(VPFSRCDIR)\gui\resourcedialog.cpp"
	-@IF EXIST resourcedialog.obj DEL resourcedialog.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\resourcedialog.cpp

serialize.obj: "$(VPFSRCDIR)\gui\serialize.cpp"
	-@IF EXIST serialize.obj DEL serialize.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\serialize.cpp

textresourcedialog.obj: "$(VPFSRCDIR)\gui\textresourcedialog.cpp"
	-@IF EXIST textresourcedialog.obj DEL textresourcedialog.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\textresourcedialog.cpp

views.obj: "$(VPFSRCDIR)\gui\views.cpp"
	-@IF EXIST views.obj DEL views.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)\include" $(CCFLAGS) $(VPFSRCDIR)\gui\views.cpp

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
	-@IF EXIST end.obj DEL end.obj
	-@IF EXIST error.obj DEL error.obj
	-@IF EXIST extent.obj DEL extent.obj
	-@IF EXIST fac.obj DEL fac.obj
	-@IF EXIST fbr.obj DEL fbr.obj
	-@IF EXIST fca.obj DEL fca.obj
	-@IF EXIST fcs.obj DEL fcs.obj
	-@IF EXIST feature.obj DEL feature.obj
	-@IF EXIST featureclass.obj DEL featureclass.obj
	-@IF EXIST featureitem.obj DEL featureitem.obj
	-@IF EXIST featuretype.obj DEL featuretype.obj
	-@IF EXIST file.obj DEL file.obj
	-@IF EXIST header.obj DEL header.obj
	-@IF EXIST lat.obj DEL lat.obj
	-@IF EXIST lht.obj DEL lht.obj
	-@IF EXIST library.obj DEL library.obj
	-@IF EXIST linefeature.obj DEL linefeature.obj
	-@IF EXIST point.obj DEL point.obj
	-@IF EXIST pointfeature.obj DEL pointfeature.obj
	-@IF EXIST query.obj DEL query.obj
	-@IF EXIST queryparse.obj DEL queryparse.obj
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
	-@IF EXIST tripletid.obj DEL tripletid.obj
	-@IF EXIST txt.obj DEL txt.obj
	-@IF EXIST vdt.obj DEL vdt.obj
	-@IF EXIST vpf.obj DEL vpf.obj
	-@IF EXIST parser.obj DEL parser.obj
	-@IF EXIST vpfviewer.obj DEL vpfviewer.obj
	-@IF EXIST arearesourcedialog.obj DEL arearesourcedialog.obj
	-@IF EXIST application.obj DEL application.obj
	-@IF EXIST g_database.obj DEL g_database.obj
	-@IF EXIST databaselist.obj DEL databaselist.obj
	-@IF EXIST g_error.obj DEL g_error.obj
	-@IF EXIST extentdialog.obj DEL extentdialog.obj
	-@IF EXIST layer.obj DEL layer.obj
	-@IF EXIST layers.obj DEL layers.obj
	-@IF EXIST lineresourcedialog.obj DEL lineresourcedialog.obj
	-@IF EXIST manager.obj DEL manager.obj
	-@IF EXIST palette.obj DEL palette.obj
	-@IF EXIST pointresourcedialog.obj DEL pointresourcedialog.obj
	-@IF EXIST reader.obj DEL reader.obj
	-@IF EXIST resourcedialog.obj DEL resourcedialog.obj
	-@IF EXIST serialize.obj DEL serialize.obj
	-@IF EXIST textresourcedialog.obj DEL textresourcedialog.obj
	-@IF EXIST views.obj DEL views.obj
	-@IF EXIST vpfviewer.exe DEL vpfviewer.exe

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

