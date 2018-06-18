SYSTEM   = x86_.net2017_15.0
FORMAT   = stat_mda
CCC      = cl
INCDIRS  = /I"..\cssrc" 
CCFLAGS  =  /c /MD /nologo /W3 /EHsc /GR /I"$(ILVHOME)/include" $(INCDIRS) /Tp
LD       = link
ULDFLAGS =
LDFLAGS  =  /nologo /SUBSYSTEM:windows msvcrt.lib


ADDLIBS  = ilvgdpro.lib
DIRLIBS  = -LIBPATH:"$(ILVHOME)/lib/$(SYSTEM)/$(FORMAT)"
VIEWSLIBS= iljsgide.lib ilvjs.lib iljs.lib ilvavxlook.lib ilvaw95look.lib ilvawlook.lib ilvamlook.lib ilvadvgdt.lib ilvvxlook.lib ilvw95look.lib ilvwlook.lib ilvmlook.lib ilvgadgt.lib views.lib winviews.lib ilog.lib

STDLIBS  = kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib wsock32.lib imm32.lib winspool.lib
ALLLIBS  = $(ADDLIBS) $(VIEWSLIBS) $(STDLIBS)
RESDEP   = viewsico.res
RC       = rc
RCXFLAGS = /k /I"$(ILVHOME)\data\res"
RCFLAGS  = /I"$(ILVHOME)\data\res"

USEROBJS =

OBJS = Centr3.obj \
	clavier_tactile.obj \
	accueil.obj \
	selection_phase.obj \
	selection_OF.obj \
	pesee_OF.obj \
	Pesee_Etalon.obj \
	selection_Balance.obj \
	selection_EtalonLigne.obj \
	selection_LOT.obj \
	selection_MWF.obj \
	selection_Recipient.obj \
	Choix_Balance.obj \
	choix_OF.obj \
	message.obj \
	phrase_Secu.obj \
	recontrole_OF.obj

Centr3.exe: $(OBJS) $(USEROBJS) $(RESDEP)
	$(LD) @<<
$(DIRLIBS) $(ALLLIBS)
$(ULDFLAGS) $(LDFLAGS)
 -OUT:$@ 
$(OBJS)
$(USEROBJS)
"$(ILVHOME)\lib\$(SYSTEM)\$(FORMAT)\ilvmain.obj"
$(RESDEP)
<<

viewsico.res: "$(ILVHOME)\data\res\viewsico.rc"
	$(RC) $(RCFLAGS) -r -fo$(RESDEP) "$(ILVHOME)\data\res\viewsico.rc"

SRCDIR = "..\cssrc" 
Centr3.obj: $(SRCDIR)\Centr3.cpp
	$(CCC) $(CCFLAGS) $(SRCDIR)\Centr3.cpp

CLAVIER_TACTILESRC = "..\cssrc" 
clavier_tactile.obj: $(CLAVIER_TACTILESRC)\clavier_tactile.cpp
	$(CCC) $(CCFLAGS) $(CLAVIER_TACTILESRC)\clavier_tactile.cpp

ACCUEILSRC = "..\cssrc" 
accueil.obj: $(ACCUEILSRC)\accueil.cpp
	$(CCC) $(CCFLAGS) $(ACCUEILSRC)\accueil.cpp

SELECTION_PHASESRC = "..\cssrc" 
selection_phase.obj: $(SELECTION_PHASESRC)\selection_phase.cpp
	$(CCC) $(CCFLAGS) $(SELECTION_PHASESRC)\selection_phase.cpp

SELECTION_OFSRC = "..\cssrc" 
selection_OF.obj: $(SELECTION_OFSRC)\selection_OF.cpp
	$(CCC) $(CCFLAGS) $(SELECTION_OFSRC)\selection_OF.cpp

PESEE_OFSRC = "..\cssrc" 
pesee_OF.obj: $(PESEE_OFSRC)\pesee_OF.cpp
	$(CCC) $(CCFLAGS) $(PESEE_OFSRC)\pesee_OF.cpp

PESEE_ETALONSRC = "..\cssrc" 
Pesee_Etalon.obj: $(PESEE_ETALONSRC)\Pesee_Etalon.cpp
	$(CCC) $(CCFLAGS) $(PESEE_ETALONSRC)\Pesee_Etalon.cpp

SELECTION_BALANCESRC = "..\cssrc" 
selection_Balance.obj: $(SELECTION_BALANCESRC)\selection_Balance.cpp
	$(CCC) $(CCFLAGS) $(SELECTION_BALANCESRC)\selection_Balance.cpp

SELECTION_ETALONLIGNESRC = "..\cssrc" 
selection_EtalonLigne.obj: $(SELECTION_ETALONLIGNESRC)\selection_EtalonLigne.cpp
	$(CCC) $(CCFLAGS) $(SELECTION_ETALONLIGNESRC)\selection_EtalonLigne.cpp

SELECTION_LOTSRC = "..\cssrc" 
selection_LOT.obj: $(SELECTION_LOTSRC)\selection_LOT.cpp
	$(CCC) $(CCFLAGS) $(SELECTION_LOTSRC)\selection_LOT.cpp

SELECTION_MWFSRC = "..\cssrc" 
selection_MWF.obj: $(SELECTION_MWFSRC)\selection_MWF.cpp
	$(CCC) $(CCFLAGS) $(SELECTION_MWFSRC)\selection_MWF.cpp

SELECTION_RECIPIENTSRC = "..\cssrc" 
selection_Recipient.obj: $(SELECTION_RECIPIENTSRC)\selection_Recipient.cpp
	$(CCC) $(CCFLAGS) $(SELECTION_RECIPIENTSRC)\selection_Recipient.cpp

CHOIX_BALANCESRC = "..\cssrc" 
Choix_Balance.obj: $(CHOIX_BALANCESRC)\Choix_Balance.cpp
	$(CCC) $(CCFLAGS) $(CHOIX_BALANCESRC)\Choix_Balance.cpp

CHOIX_OFSRC = "..\cssrc" 
choix_OF.obj: $(CHOIX_OFSRC)\choix_OF.cpp
	$(CCC) $(CCFLAGS) $(CHOIX_OFSRC)\choix_OF.cpp

MESSAGESRC = "..\cssrc" 
message.obj: $(MESSAGESRC)\message.cpp
	$(CCC) $(CCFLAGS) $(MESSAGESRC)\message.cpp

PHRASE_SECUSRC = "..\cssrc" 
phrase_Secu.obj: $(PHRASE_SECUSRC)\phrase_Secu.cpp
	$(CCC) $(CCFLAGS) $(PHRASE_SECUSRC)\phrase_Secu.cpp

RECONTROLE_OFSRC = "..\cssrc" 
recontrole_OF.obj: $(RECONTROLE_OFSRC)\recontrole_OF.cpp
	$(CCC) $(CCFLAGS) $(RECONTROLE_OFSRC)\recontrole_OF.cpp

clean:
	-@FOR %i IN ($(OBJS)) DO del %i
	-@del Centr3.exe
	-@del $(RESDEP)
