# --------------------------------------------------------------------------
#                                                                          
# Makefile for the map builder
#                                                                          
# --------------------------------------------------------------------------
#   platform: x86_.net2017_15.0
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

DBLINKDIR    = $(ILDHOME)
DBLINKINCDIR = $(DBLINKDIR)\include
DBLINKLIBDIR = $(DBLINKDIR)\lib\$(SYSTEM)\$(FORMAT)

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


ILVMAPSDIR = $(ROOTDIR)\..\..



MAPBUILDEROBJFILES=dockapp.obj builder.obj builder_ui.obj buffer.obj desktop.obj readctrl.obj prjselector.obj adpselect.obj legend.obj coloreditor.obj paleditor.obj dasheditor.obj lineeditor.obj pointeditor.obj defdbmsfact.obj sdoreadctrl.obj scalecombo.obj multiraster.obj multishape.obj

all: mapbuilder

#---------------------------------------------------------------------------
#
# mapbuilder
#

# --------------------------------------------------------------------------
mapbuilder: mapbuilder.exe
mapbuilder.exe: $(MAPBUILDEROBJFILES) mapbuilder.obj viewsico.res
	-@IF EXIST mapbuilder.exe DEL mapbuilder.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(ILVMAPSLIBDIR)" /LIBPATH:"$(DBLINKLIBDIR)" /LIBPATH:"$(VIEWSLIBDIR)" ilvjpg.lib ilvaw95look.lib ilvawlook.lib ilvw95look.lib ilvpng.lib ilvdbmaps.lib ilvmaps.lib ilvppm.lib ilvwlook.lib ilvadvgadmgr.lib ilvgadmgr.lib ilvbmp.lib ilvtiff.lib dblnkdyn.lib ilvadvgdt.lib ilvgadgt.lib ilvmgr.lib dbkernel.lib views.lib winviews.lib ilog.lib ilddb.lib $(VIEWSMAPSSYSLIBS) $(DBLINKSYSLIBS) $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ mapbuilder.obj $(MAPBUILDEROBJFILES) ilvmain.obj viewsico.res

mapbuilder.obj: "$(ROOTDIR)\src\mapbuilder.cpp"
	-@IF EXIST mapbuilder.obj DEL mapbuilder.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\mapbuilder.cpp

dockapp.obj: "$(ROOTDIR)\src\dockapp.cpp"
	-@IF EXIST dockapp.obj DEL dockapp.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\dockapp.cpp

builder_ui.obj: "$(ROOTDIR)\src\builder_ui.cpp"
	-@IF EXIST builder_ui.obj DEL builder_ui.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\builder_ui.cpp

builder.obj: "$(ROOTDIR)\src\builder.cpp"
	-@IF EXIST builder.obj DEL builder.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\builder.cpp

buffer.obj: "$(ROOTDIR)\src\buffer.cpp"
	-@IF EXIST buffer.obj DEL buffer.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\buffer.cpp

desktop.obj: "$(ROOTDIR)\src\desktop.cpp"
	-@IF EXIST desktop.obj DEL desktop.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\desktop.cpp

readctrl.obj: "$(ROOTDIR)\src\readctrl.cpp"
	-@IF EXIST readctrl.obj DEL readctrl.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\readctrl.cpp

prjselector.obj: "$(ROOTDIR)\src\prjselector.cpp"
	-@IF EXIST prjselector.obj DEL prjselector.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\prjselector.cpp

adpselect.obj: "$(ROOTDIR)\src\adpselect.cpp"
	-@IF EXIST adpselect.obj DEL adpselect.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\adpselect.cpp

legend.obj: "$(ROOTDIR)\src\legend.cpp"
	-@IF EXIST legend.obj DEL legend.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\legend.cpp

coloreditor.obj: "$(ROOTDIR)\src\coloreditor.cpp"
	-@IF EXIST coloreditor.obj DEL coloreditor.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\coloreditor.cpp

paleditor.obj: "$(ROOTDIR)\src\paleditor.cpp"
	-@IF EXIST paleditor.obj DEL paleditor.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\paleditor.cpp

dasheditor.obj: "$(ROOTDIR)\src\dasheditor.cpp"
	-@IF EXIST dasheditor.obj DEL dasheditor.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\dasheditor.cpp

lineeditor.obj: "$(ROOTDIR)\src\lineeditor.cpp"
	-@IF EXIST lineeditor.obj DEL lineeditor.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\lineeditor.cpp

pointeditor.obj: "$(ROOTDIR)\src\pointeditor.cpp"
	-@IF EXIST pointeditor.obj DEL pointeditor.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\pointeditor.cpp

defdbmsfact.obj: "$(ROOTDIR)\src\defdbmsfact.cpp"
	-@IF EXIST defdbmsfact.obj DEL defdbmsfact.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\defdbmsfact.cpp

sdoreadctrl.obj: "$(ROOTDIR)\src\sdoreadctrl.cpp"
	-@IF EXIST sdoreadctrl.obj DEL sdoreadctrl.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\sdoreadctrl.cpp

scalecombo.obj: "$(ROOTDIR)\src\scalecombo.cpp"
	-@IF EXIST scalecombo.obj DEL scalecombo.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\scalecombo.cpp

multiraster.obj: "$(ROOTDIR)\src\multiraster.cpp"
	-@IF EXIST multiraster.obj DEL multiraster.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\multiraster.cpp

multishape.obj: "$(ROOTDIR)\src\multishape.cpp"
	-@IF EXIST multishape.obj DEL multishape.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(ILVMAPSINCDIR)" /I"$(VIEWSINCDIR)" /I"$(DBLINKINCDIR)" /I"$(ROOTDIR)\include" -DHAS_SDO_SUPPORT $(CCFLAGS) $(ROOTDIR)\src\multishape.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST mapbuilder.obj DEL mapbuilder.obj
	-@IF EXIST dockapp.obj DEL dockapp.obj
	-@IF EXIST builder_ui.obj DEL builder_ui.obj
	-@IF EXIST builder.obj DEL builder.obj
	-@IF EXIST buffer.obj DEL buffer.obj
	-@IF EXIST desktop.obj DEL desktop.obj
	-@IF EXIST readctrl.obj DEL readctrl.obj
	-@IF EXIST prjselector.obj DEL prjselector.obj
	-@IF EXIST adpselect.obj DEL adpselect.obj
	-@IF EXIST legend.obj DEL legend.obj
	-@IF EXIST coloreditor.obj DEL coloreditor.obj
	-@IF EXIST paleditor.obj DEL paleditor.obj
	-@IF EXIST dasheditor.obj DEL dasheditor.obj
	-@IF EXIST lineeditor.obj DEL lineeditor.obj
	-@IF EXIST pointeditor.obj DEL pointeditor.obj
	-@IF EXIST defdbmsfact.obj DEL defdbmsfact.obj
	-@IF EXIST sdoreadctrl.obj DEL sdoreadctrl.obj
	-@IF EXIST scalecombo.obj DEL scalecombo.obj
	-@IF EXIST multiraster.obj DEL multiraster.obj
	-@IF EXIST multishape.obj DEL multishape.obj
	-@IF EXIST mapbuilder.exe DEL mapbuilder.exe

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

