// -------------------------------------------------------------- -*- C++ -*-
// Studio commands
// 

command Quit {
    label   "&menu_quit";
    tooltip   "&ttmenu_quit";
    acceleratorText "Ctrl+Q";
    acceleratorDefinition "<Ctrl><Key Q>";
    prompt  "&quitEditor";
    category studio;
}

command ShowPropertiesPanel {
    label "&psPanel";
    prompt "&psPanelPrompt";
    acceleratorText "Alt+Enter";
    acceleratorDefinition "<Meta><Key RETURN>";
    category studio;
    category panel;
    bitmap "ivstudio/icons/icprtree.png";
}

command MakeFilteredGraphic {
    label "&mkFiltered";
    prompt "&mkFilteredprompt";
    tooltip  "&ttMkFiltered";
    acceleratorText "Ctrl+F";
    acceleratorDefinition "<Ctrl><Key F>";
    category studio;
    category command;
    bitmap "ivstudio/icons/icfilter.png";
}

command ShowInfoPanel {
    label "&infoPanel";
    prompt "&infoPanelPrompt";
    category studio;
    category panel;
}

command SelectPlugIns {
    label   "&cmdSelectPlugIns";
    prompt  "&cprSelectPlugIns";
    category studio;
}

command PlayerStart {
    label "&playerStart";
    prompt "&playerStartPrompt";
    category player;
}

command PlayerStop {
    label "&playerStop";
    prompt "&playerStopPrompt";
    category player;
}

command PlayerPlay {
    label "&playerPlay";
    prompt "&playerPlayPrompt";
    category player;
}


command PlayerSaveAs {
    label "&playerSaveAs";
    prompt "&playerSaveAsPrompt";
    category player;
}

command PlayerOpen {
    label "&playerOpen";
    prompt "&playerOpenPrompt";
    category player;
}

command PlayerSpeed {
    label  "&playerSpeed";
    prompt "&playerSpeedPrompt";
    category player;
}

command NewEventSequence {
    label "&newEventSeq";
    prompt "&newEventSeqP";
    bitmap "ivstudio/icons/ivicn39.png";
    category player;
    messages ChangeEventSequence, ChangeEventSequenceFileName;
}

command OpenEventSequence {
    label  "&openEventSeq";
    prompt "&openEventSeqP";
    bitmap "icopen";
    category player;
    messages ChangeEventSequence, ChangeEventSequenceFileName;
}

command ExecuteEventSequence {
    label  "&execEventSeq";
    prompt "&execEventSeqP";
    bitmap "icredo";
    category player;
}

command SaveEventSequence {
    label "&saveEventSeq";
    prompt "&saveEventSeqP";
    bitmap "icsave";
    category player;
}

command SaveEventSequenceAs {
    label "&saveEventSeqAs";
    prompt "&saveEventSeqAsP";
    bitmap "ivstudio/icons/ivicn38.png";
    category player;
    messages ChangeEventSequenceFileName;
}

command ShowEventSequencerPanel {
    label "&eventSeqPan";
    prompt "&showEventSeqPanP";
    category player;
    category panel;
}

command HideEventSequencerPanel {
    label "&hideEventSeqPan";
    bitmap "icquit";
    category player;
}

// Panel commands

command ShowCommandPanel {
    label  "&showCmdPan";
    tooltip  "&ttshowCmdPan";
    bitmap "iccmdpan";
    prompt "&cmdPanPrompt";
    acceleratorText "Ctrl+Shift+C";
    acceleratorDefinition "<Ctrl><Shift><Key C>";
    category panel;
}

command ShowMainPanel {
    label  "&showMainPan";
    category panel;
}; 

command ShowMessagePanel {
    label  "&showMessagePanel";
    prompt "&msgPanPrompt";
    acceleratorText "Ctrl+Shift+M";
    acceleratorDefinition "<Ctrl><Shift><Key M>";
    category panel;
}

command HideMessagePanel {
    label "&hideMessagePanel";
    category panel;
}

command ShowPalettePanel {
    label  "&showObjectPalette";
    prompt "&showObjectPaletteP";
    acceleratorText "Ctrl+Shift+P";
    acceleratorDefinition "<Ctrl><Shift><Key P>";
    category panel;
}

command ShowGridPanel {
    label "&showGridPanel";
    prompt "&gridPanPrompt";
    category panel;
}

command HideGridPanel {
    label "&hideGridPanel";
    category panel;
}

command ShowCallbackInspector {
    label  "&showCallbackInspector";
    prompt "&showCallbackInspectorP";
    category panel;
}

command ShowResourcePanel {
    label "&showResourcePanel";
    tooltip "&ttshowResourcePanel";
    acceleratorText "Ctrl+Shift+R";
    acceleratorDefinition "<Ctrl><Shift><Key R>";
    bitmap "icrespan";
    prompt "&resPanPrompt";
    category panel;
};

command HideResourcePanel {
    label "&hideResourcePanel";
    category panel;
};

command ShowAlignPanel {
    label "&showAlignPanel";
    tooltip "&ttshowAlignPanel";
    bitmap "icalign";
    acceleratorText "Ctrl+Shift+K";
    acceleratorDefinition "<Ctrl><Shift><Key K>";
    prompt "&alignPanPrompt";
    category align;
    category panel;
};

command ShowAttachPanel {
    label "&showAttachPanel";
    acceleratorText "Ctrl+Shift+A";
    acceleratorDefinition "<Ctrl><Shift><Key A>";
    prompt "&attPanPrompt";
    category panel;
};

command HideAttachPanel {
    label "&hideAttachPanel";
    category panel;
};

command ShowErrorPanel {
    label  "&merrors";
    prompt "&errorsP";
    acceleratorText "Ctrl+Shift+E";
    acceleratorDefinition "<Ctrl><Shift><Key E>";
    category panel;
};

command ClearErrorPanel {
    label "&clean";
    prompt "&cleanErrorPanelPrompt";
    bitmap "ivstudio/icons/clean.png";
    category panel;
}

command HelpErrorPanel {
    label "&help";
    prompt "&helpErrorPanelPrompt";
    bitmap "ivstudio/icons/ichelp.png";
    category panel;
}

command ShowLayerPanel {
    label  "&layPan";
    prompt "&layPanP";
    acceleratorText "Ctrl+Shift+L";
    acceleratorDefinition "<Ctrl><Shift><Key L>";
    bitmap "ivstudio/icons/iclayer.png";
    category panel;
}

command InspectPanel {
    label  "&inspPan";
    prompt "&inspPanPrompt";
    bitmap "icinsp";
    category application;
};

// Inspector 

command ShowInspector {
    label "&inspect";
    tooltip "&ttinspect";
    prompt "&inspSelObj";
    acceleratorText "Ctrl+Shift+I";
    acceleratorDefinition "<Ctrl><Shift><Key I>";
    bitmap "icinsp";
    category inspector;
    category panel;
}

command HideInspector {
    label "&hideInspector";
    bitmap  "icquit";
    category inspector;
}

// Edit

command SelectAll {
    label  "&selectAll";
    prompt "&selectAllPrompt";
    acceleratorText "Ctrl+A";
    acceleratorDefinition "<Ctrl><Key A>";
    category edit;
}

command UnDo {
    label  "&unDo";
    tooltip  "&ttunDo";
    prompt "&unDoPrompt";
    acceleratorText "Ctrl+Z";
    acceleratorDefinition "<Ctrl><Key Z>";
    bitmap "icundo";
    category edit;
}

command ReDo {
    label  "&reDo";
    tooltip  "&ttreDo";
    prompt "&reDoPrompt";
    acceleratorText "Ctrl+R";
    acceleratorDefinition "<Ctrl><Key R>";
    category edit;
}

command Redo {
    label  "&redo";
    tooltip  "&ttredo";
    prompt "&redoPrompt";
    acceleratorText "Ctrl+Shift+Z";
    acceleratorDefinition "<Ctrl><Shift><Key Z>";
    bitmap "icredo";
    category edit;
}

command Duplicate {
    label  "&duplicate";
    tooltip  "&ttduplicate";
    prompt "&duplicatePrompt";
    acceleratorText "Ctrl+D";
    acceleratorDefinition "<Ctrl><Key D>";
    bitmap "icdup";
    category edit;
}

command Push {
    label  "&pushCmd";
    prompt "&pushCmdP";
    category edit;
    bitmap "ivstudio/icons/icback.png"
}

command Pop {
    label  "&popCmd";
    prompt "&popCmdP";
    category edit;
    bitmap "ivstudio/icons/icfront.png"
}

command ClipboardCopy {
    label  "&mcopy";
    tooltip  "&ttmcopy";
    bitmap "iccopy";
    acceleratorText "Ctrl+C";
    acceleratorDefinition "<Ctrl><Key C>";
    prompt "&copyPrompt";
    category edit;
}

command ClipboardCut {
    label  "&mcut";
    tooltip  "&ttmcut";
    bitmap "iccut";
    acceleratorText "Ctrl+X";
    acceleratorDefinition "<Ctrl><Key X>";
    prompt "&cutPrompt";
    category edit;
}

command ClipboardPaste {
    label  "&mpaste";
    tooltip  "&ttmpaste";
    bitmap "icpaste";
    acceleratorText "Ctrl+V";
    acceleratorDefinition "<Ctrl><Key V>";
    prompt "&pastePrompt";
    category edit;
}

command Delete {
    label  "&delete";
    tooltip  "&ttdelete";
    prompt "&delSelObjs";
    acceleratorText "Del";
    bitmap "icdel";
    messages ObjectDeleted;
    category edit;
}

command AddObject {
    interactive false;
    messages 	AddObject;
}

command AddZoomableLabel {
    label "IlvZoomableLabel";
    prompt "&addZoomableLabelPrompt";
    category add;
}

command AddIcon {
    label "IlvIcon";
    prompt "&addIconPrompt";
    category add;
}

command AddTransparentIcon {
    label "IlvTransparentIcon";
    prompt "&transpIconPrompt";
    category add;
}

command AddZoomableIcon {
    label "IlvZoomableIcon";
    prompt "&zoomIconPrompt";
    category add;
}

command AddZoomableTransparentIcon {
    label "IlvZoomableTransparentIcon";
    prompt "&zoomTranspIconPrompt";
    category add;
}

command Group {
    label "&mgroup"
    prompt "&groupPrompt";
    acceleratorText "Ctrl+G";
    acceleratorDefinition "<Ctrl><Key G>";
    category group;
    bitmap "ivstudio/icons/icgroup.png"
}

command GroupIntoGraphicSet {
    label  "IlvGraphicSet";
    prompt "&graphsetPrompt";
    category group;
    selector group;
}

command GroupIntoSelector {
    label  "IlvSelector";
    prompt "&selectorPrompt";
    category group;
    selector group;
}

command GroupIntoSmartSet {
    label  "IlvSmartSet";
    prompt "&smartSetPrompt";
    category group;
    selector group;
}

command UnGroup {
    label "&ungroup";
    prompt "&ungroupPrompt";
    acceleratorText "Ctrl+U";
    acceleratorDefinition "<Ctrl><Key U>";
    category group;
    bitmap "ivstudio/icons/icungroup.png"
}

command EditGroup {
    label "&EditGroup";
    prompt "&EditGroupPrompt";
    acceleratorText "Ctrl+E";
    acceleratorDefinition "<Ctrl><Key E>";
    category group;
}

command MoveObject {
    interactive false;
    messages    MoveObject;
}

command ResizeObject {
    interactive false;
    messages    ResizeObject;
}

command SetObjectName {
    interactive false;
    messages    SetObjectName;
}

command SetObjectCallback {
    interactive false;
    messages    SetObjectCallback;
}

command SetObjectThickness {
    interactive false;
    messages    SetObjectThickness;
}

command SetObjectLayer {
    interactive false;
    acceleratorText "Ctrl+L";
    acceleratorDefinition "<Ctrl><Key L>";
    bitmap "ivstudio/icons/iclayer.png";
    messages    SetObjectLayer;
}

command NudgeUp {
	interactive true;
	label "&nudgeup"
	prompt "&nudgeupPrompt";
	acceleratorText "Ctrl+Up Arrow";
	acceleratorDefinition "<Ctrl><Key Up>";
	bitmap "ivstudio/icons/icnudgeup.png"
	category edit;
}
command NudgeLeft {
	interactive true;
	label "&nudgeleft"
	prompt "&nudgeleftPrompt";
	acceleratorText "Ctrl+Left Arrow";
	acceleratorDefinition "<Ctrl><Key Left>";
	bitmap "ivstudio/icons/icnudgeleft.png"
	category edit;
}
command NudgeDown {
	interactive true;
	label "&nudgedown"
	prompt "&nudgedownPrompt";
	acceleratorText "Ctrl+Down Arrow";
	acceleratorDefinition "<Ctrl><Key Down>";
	bitmap "ivstudio/icons/icnudgedown.png"
	category edit;
}
command NudgeRight {
	interactive true;
	label "&nudgeright"
	prompt "&nudgerightPrompt";
	acceleratorText "Ctrl+Right Arrow";
	acceleratorDefinition "<Ctrl><Key Right>";
	bitmap "ivstudio/icons/icnudgeright.png"
	category edit;
}
command	FlipHorizontal {
	interactive true;
	label "&fliph"
	prompt "&fliphPrompt";
	bitmap "ivstudio/icons/icfliphor.png"
	category edit;
}
command	FlipVertical {
	interactive true;
	label "&flipv"
	prompt "&flipvPrompt";
	bitmap "ivstudio/icons/icflipver.png"
	category edit;
}
command	Rotate90 {
	interactive true;
	label "&rotatec"
	prompt "&rotatecPrompt";
	bitmap "ivstudio/icons/icrightrot.png"
	category edit;
}
command	Rotatem90 {
	interactive true;
	label "&rotatecc"
	prompt "&rotateccPrompt";
	bitmap "ivstudio/icons/icleftrot.png"
	category edit;
}

command AlignLeft {
    label  "&alignLeft";
    prompt "&alignLeftPrompt";
    bitmap "ivstudio/icons/icalleft.png";
    category align;
    htmlHelpFile "AlignLeftCmd.html";
    compiledHtmlHelpFile "studio.chm";
}

command AlignRight {
    label  "&alignRight";
    prompt "&alignRightPrompt";
    bitmap "ivstudio/icons/icalrght.png";
    category align;
    htmlHelpFile "AlignRightCmd.html";
    compiledHtmlHelpFile "studio.chm";
}

command AlignVertical {
    label  "&alignVertical";
    prompt "&alignVerticalPrompt";
    bitmap "ivstudio/icons/icalvcnt.png";
    category align;
    htmlHelpFile "AlignVerticalCmd.html";
    compiledHtmlHelpFile "studio.chm";
}

command SameWidth {
    label  "&sameWidth";
    prompt "&sameWidthPrompt";
    bitmap "ivstudio/icons/icalsamw.png";
    category align;
    htmlHelpFile "SameWidthCmd.html";
    compiledHtmlHelpFile "studio.chm";
}

command HorizontalSpaces {
    label  "&horizontalDistribute";
    prompt "&horizontalDistributePrompt";
    bitmap "ivstudio/icons/icalhspc.png";
    category align;
    htmlHelpFile "HorizontalSpacesCmd.html";
    compiledHtmlHelpFile "studio.chm";
}

command AlignTop {
    label  "&alignTop";
    prompt "&alignTopPrompt";
    bitmap "ivstudio/icons/icaltop.png";
    category align;
    htmlHelpFile "AlignTopCmd.html";
    compiledHtmlHelpFile "studio.chm";
}

command AlignBottom {
    label  "&alignBottom";
    prompt "&alignBottomPrompt";
    bitmap "ivstudio/icons/icalbot.png";
    category align;
    htmlHelpFile "AlignBottomCmd.html";
    compiledHtmlHelpFile "studio.chm";
}

command AlignHorizontal {
    label  "&alignHorizontal";
    prompt "&alignHorizontalPrompt";
    bitmap "ivstudio/icons/icalhcnt.png";
    category align;
    htmlHelpFile "AlignHorizontalCmd.html";
    compiledHtmlHelpFile "studio.chm";
}

command SameHeight {
    label  "&sameHeight";
    prompt "&sameHeightPrompt";
    bitmap "ivstudio/icons/icalsamh.png";
    category align;
    htmlHelpFile "SameHeightCmd.html";
    compiledHtmlHelpFile "studio.chm";
}

command VerticalSpaces {
    label  "&verticalDistribute";
    prompt "&verticalDistributePrompt";
    bitmap "ivstudio/icons/icalvspc.png";
    category align;
    htmlHelpFile "VerticalSpacesCmd.html";
    compiledHtmlHelpFile "studio.chm";
}

// Buffer

command Refresh {
    label  "&refresh";
    prompt "&redrawWorkSpace";
    category buffer;
}

command SelectBuffer {
    label  "&selectBuffer";
    messages SelectBuffer;
    category buffer;
}

command SelectPreviousBuffer {
    label   "&prevBufPrompt";
    tooltip   "&ttprevBufPrompt";
    acceleratorText "Ctrl+F6";
    acceleratorDefinition "<Ctrl><Key F6>";
    prompt  "&prevBufPrompt";
    category buffer;
}

command NewBuffer {
    label "&mnew";
    tooltip "&ttmnew";
    bitmap "ivstudio/icons/icnew.png";
    acceleratorText "Ctrl+N";
    acceleratorDefinition "<Ctrl><Key N>";
    prompt "&newBufPrompt";
    messages SelectBuffer;
    category buffer;
}

command NewGraphicBuffer {
    label "&newGraphicBuffer";
    prompt "&newGraphicBufferP"
    category buffer;
    category 2d;
    bitmap "ivstudio/icons/icgraphic.png";
    // this command execute the NewBuffer command
}

command OpenBuffer {
    label "&mopen...";
    tooltip "&ttmopen...";
    acceleratorText "Ctrl+O";
    acceleratorDefinition "<Ctrl><Key O>";
    prompt "&openData";
    bitmap "icopen";
    messages SelectBuffer;
    category buffer;
}

command InsertBuffer {
    interactive false;
    label "&minsert...";
    prompt "&insBufPrompt";
    category buffer;
}

command CloseBuffer {
    label "&mclose";
    prompt "&closeBufPrompt";
    messages CloseBuffer, SelectBuffer;
    category buffer;
}

command CloseAllBuffers {
    label "&mcloseAll";
    prompt "&closeAllBufPrompt";
    messages CloseBuffer, SelectBuffer;
    category buffer;
}

command RevertBuffer {
    label  "&revert";
    prompt "&revertP";
    messages RevertBuffer;
    category buffer;
}

command SaveBuffer {
    label  "&msave";
    tooltip  "&ttmsave";
    acceleratorText "Ctrl+S";
    acceleratorDefinition "<Ctrl><Key S>";
    prompt "&saveData";
    messages SaveBuffer;
    bitmap "icsave";
    category buffer;
}

command SaveBufferAs {
    label "&msaveAs...";
    tooltip "&ttmsaveAs...";
    prompt "&saveBufAsPrompt";
    messages SaveBuffer, BufferRenamed;
    category buffer;
}

command GenerateStringData {
    label  "&genStringData...";
    prompt "&genStringDataPrompt";
    category buffer;
};

command FitToContents {
    label "&fitToContents";
    prompt "&fitContPrompt";
    category buffer;
}

command TestPanel {
    label "&mtestp";
    tooltip "&ttmtest";
    toggleLabel "&stopTest";
    prompt "&testCurPanel";
    togglePrompt "&stopTest";
    bitmap "icrun";
    category buffer;
}

command ResizePanel {
    label "&resizePanel...";
    category buffer;
}

command PrintCurrentBuffer {
    label "&printCurrentBuffer";
    prompt "&printCurrentBufferPrompt";
    category buffer;
}

command PrinterPreviewCurrentBuffer {
    label  "&printerPreviewCurrentBuffer...";
    prompt "&printerPreviewCurrentBufferPrompt";
    category buffer;
}

command Print {
    label "&print...";
    prompt "&printPrompt";
    category buffer;
}

command PrinterPreview {
    label  "&printerPreview...";
    prompt "&printerPreviewPrompt";
    category buffer;
}

command CascadeWindows {
    label "&mCascade";
    prompt "&CascadeWindowsP";
    bitmap "ivstudio/icons/iccascade.png";
    category buffer;
}

command TileHorizontally {
    label "&mTileHorizontally";
    prompt "&TileHorizontallyP";
    bitmap "ivstudio/icons/ictileh.png";
    category buffer;
}

command TileVertically {
    label "&mTileVertically";
    prompt "&TileVertically";
    bitmap "ivstudio/icons/ictilev.png";
    category buffer;
}

command MinimizeAllWindows {
    label "&minimizeAll";
    prompt "&MinimizeAllWindowsP";
    category buffer;
}

command RestoreAllWindows {
    label "&restoreAll";
    prompt "&RestoreAllWindowsP";
    category buffer;
}

// Editor properties

command EditOptions {
    label "&EditOptions";
    category studio;
    messages EditOptions;
}

command DoubleBuffering {
    label "&doubleBuffering";
    category studio;
    messages DoubleBuffering;
}

command OpaqueMoving {
    label "&opaqueMove";
    category studio;
    messages OpaqueMoving;
}

command WindowsLook {
    label "&wlook";
    prompt "&wlookPrompt";
    category studio;
    category look;
    selector look;
}

command Windows95Look {
    label "&w95look";
    prompt "&w95lookPrompt";
    category studio;
    category look;
    selector look;
}

command VXLook {
    label "&vxlook";
    prompt "&vxlookPrompt";
    category studio;
    category look;
    selector look;
}

command MotifLook {
    label "&mlook";
    prompt "&mlookPrompt";
    category studio;
    category look;
    selector look;
};

command LockInspector {
    label  "&lockInspector";
    prompt "&lockInspectorPrompt";
    category studio;
    category inspector;
}

// Meta

// Modes

command SelectSelectionMode {
    label "&selectionMode";
    tooltip "&ttselectionMode";
    prompt "&selModePrompt";
    bitmap "icselect";
    category mode;
}

command SelectActiveMode {
    label  "&activeMode";
    prompt "&activeModePrompt";
    bitmap "ictest";
    category mode;
}

command SelectGadgetContainerRectangleMode {
    label "IlvGadgetContainerRectangle";
    prompt "&gadContPrompt";
    bitmap "icgadcont";
    category mode;
}

command SelectSCGadgetContainerRectangleMode {
    label "IlvSCGadgetContainerRectangle";
    prompt "&scGadContPrompt";
    bitmap "icscgadcont";
    category mode;
}

command SelectLineMode {
    label "IlvLine";
    prompt "&linePrompt";
    bitmap "icline";
    category mode;
}

command SelectReliefLineMode {
    label "IlvReliefLine";
    prompt "&relLinePrompt";
    bitmap "icrline";
    category mode;
}

command SelectArrowLineMode {
    label "IlvArrowLine";
    prompt "&arrowLinePrompt";
    bitmap "icarrow";
    category mode;
}

command SelectArcMode {
    label "IlvArc";
    prompt "&arcPrompt";
    bitmap "icarc";
    category mode;
}

command SelectFilledArcMode {
    label "IlvFilledArc";
    prompt "&farcPrompt";
    bitmap "icfarc";
    category mode;
}

command SelectPolylineMode {
    label "IlvPolyline";
    prompt "&polyLinePrompt";
    bitmap "icpline";
    category mode;
}

command SelectPolygonMode {
    label "IlvPolygon";
    prompt "&polygonPrompt";
    bitmap "icpgon";
    category mode;
}

command SelectSplineMode {
    label "IlvSpline";
    prompt "&splinePrompt";
    bitmap "icspline"
    category mode;
}

command SelectFilledSplineMode {
    label "IlvFilledSpline";
    prompt "&fsplinePrompt";
    bitmap "icfspline";
    category mode;
}

command SelectClosedSplineMode {
    label "IlvClosedSpline";
    prompt "&closedSplinePrompt";
    bitmap "iccspline";
    category mode;
}
command SelectPolySelectionMode {
    label "IlvPolySelection";
    prompt "&polySelectionPrompt";
    bitmap "icedpoly";
    category mode;
}

command SelectRectangularObjectCreationMode {
    label "&rectangularObjectCreation";
    prompt "&rectangularObjectCreation";
    category mode;
}

command SelectLabelMode {
    label "IlvLabel";
    prompt "&labelPrompt";
    bitmap "iclabel";
    category mode;
}

command SelectLabelListMode {
    label "IlvListLabel";
    prompt "&labelListPrompt";
    bitmap "icllabel";
    category mode;
}

command SelectZoomMode {
    label  "&sZoomM";
    prompt "&sZoomMP";
    bitmap "ivstudio/icons/iczoomint.png";
    category mode;
    category 2d;
}

command SelectUnZoomMode {
    label  "&sUZoomM";
    prompt "&sUZoomMP";
    bitmap "ivstudio/icons/icuzoomint.png";
    category mode;
    category 2d;
}

command SelectTranslateMode {
    label  "&sTranslateM";
    prompt "&sTranslateMP";
    bitmap "ivstudio/icons/icpan.png";
    category mode;
    category 2d;
}

command SelectPanZoomMode {
    label  "&sPanZoomM";
    prompt "&sPanZoomMP";
    bitmap "ivstudio/icons/icpan.png";
    category mode;
    category 2d;
}

command SelectRotateMode {
    label  "&sRotateM";
    prompt "&sRotateMP";
    bitmap "ivstudio/icons/icrotate.png";
    category mode;
    category 2d;
}


// Object properties

command SelectObject {
    bitmap	"icselect";
    messages	SelectObject;
    category	property;
}

command SetName {
    label "&mname";
    prompt "&namePrompt";
    category property;
}

command SetCallback {
    label "&mcallback";
    prompt "&callbackPrompt";
    category property;
    messages SetObjectCallback;
}

command SetObjectInteractor {
    label "&minteractor";
    prompt "&setObjectInteractorP";
    category property;
}

command SetToolTip {
    label "&toolTip";
    prompt "&toolTipP";
    category property;
};

command SetThickness {
    label "&mthickness";
    prompt "&thicknessPrompt";
    category property;
}

command SetLayer {
    label "&mlayer";
    prompt "&layerPrompt";
    acceleratorText "Ctrl+L";
    acceleratorDefinition "<Ctrl><Key L>";
    category edit;
    bitmap "ivstudio/icons/iclayer.png";
}

command ToggleState {
    label "&mstate";
    prompt "&statePrompt";
    category property;
}

command OpenDocument {
    label  "&mopen...";
    tooltip  "&ttmopen...";
    prompt "&openDocumentP";
    acceleratorText "Ctrl+O";
    acceleratorDefinition "<Ctrl><Key O>";
    bitmap "icopen";
    category document;
}

command CloseDocument{
    label "&mclose";
    prompt "&closeDocumentP";
    category document;
}

command GenerateDocument {
    label "&generate";
    tooltip "&ttgenerate";
    prompt "&genDocumentP";
    bitmap "iccode";
    category document;
}

command InspectDocument {
    label  "&inspectDocument";
    prompt "&inspectDocumentP";
    // bitmap "icinsp";
    category document;
};

command RevertDocument {
    label  "&revert";
    prompt "&revertP";
    category document;
}

command SaveDocument{
    label  "&msave";
    tooltip  "&ttmsave";
    acceleratorText "Ctrl+S";
    acceleratorDefinition "<Ctrl><Key S>";
    prompt "&saveDocumentP";
    bitmap "icsave";
    category document;
}

command SaveDocumentAs {
    label "&msaveAs...";
    tooltip "&ttmsaveAs...";
    prompt "&saveDocumentAsP";
    category document;
}

command TestDocument {
    label "&mtest";
    tooltip "&ttmtest";
    toggleLabel "&stopTest";
    prompt "&testDocumentP";
    togglePrompt "&stopTest";
    bitmap "icrun";
    category document;
}

command HelpMainPanel {
    label   "&helpMainPanel";
    prompt  "&helpMainPanelP";
    bitmap "ivstudio/icons/ichelp.png";
    category panel;
}

command LoadMessageDatabase {
    label "&loadMessageDatabase";
    prompt "&loadMessageDatabaseP";
    category studio;
}

command ShowTextEditor {
    label  "&showTextEditor";
    prompt "&showTextEditorP";
    category panel;
}

command HideTextEditor{
    label  "&hideTextEditor";
    prompt "&hideTextEditorP";
    category panel;
}

command ShowGenericInspector {
    label "&showGenericInspector";
    prompt "&showGenericInspectorP";
    bitmap "ivstudio/icons/icginsp.png";
    category panel;
}

command SaveAll {
    label  "&saveAll";
    prompt "&saveAllP";
    category buffer;
    bitmap "ivstudio/icons/icsaveall.png";
}
command ToggleGrid {
	label "&tgrid";
	prompt "&tgridPrompt";
//    acceleratorDefinition "<Shift><Key G>";
	category view;
}
command ToggleActiveGrid {	
	label "&tagrid";
	prompt "&tagridPrompt";
//    acceleratorDefinition "<Shift><Key S>";
	category view;
}
command ToggleForegroundGrid {	
	label "&tfgrid";
	prompt "&tfgridPrompt";
//    acceleratorDefinition "<Shift><Key S>";
	category view;
}
command ShowGridOptionsPanel {
	label "&gridoptions";
	prompt "&gridoptionsPrompt";
	bitmap "ivstudio/icons/icgrid.png"
	category view;
}
command HideGridOptionsPanel {
	label "&gridoptions";
	prompt "&gridoptionsPrompt";
	category view;
}
command ShowViewOptionsPanel {
	label "&mviewo";
	prompt "&viewoptionsPrompt";
	category view;
}
command HideViewOptionsPanel {
	label "&mviewo";
	prompt "&viewoptionsPrompt";
	category view;
}
command ZoomLevel {
	label  "&zoomlevel";
	prompt "&zoomlevelPrompt";
	comboLabels "10%,25%,50%,75%,100%,150%,200%,500%";
	width 80;
	category view;
}
command ZoomIn {
	label "&zoomin";
	prompt "&zoominPrompt";
	bitmap "ivstudio/icons/iczoomin.png";
	acceleratorText "Shift+Z";
    	acceleratorDefinition "<Shift><Key Z>";
	category view;
}
command ZoomOut {	
	label "&zoomout";
	prompt "&zoomoutPrompt";
	bitmap "ivstudio/icons/iczoomout.png";
	acceleratorText "Shift+U";
	acceleratorDefinition "<Shift><Key U>";
	category view;
}
command ResetView {
	label "&resetview";
	prompt "&resetviewPrompt";
	acceleratorText "I";
	acceleratorDefinition "<Shift><Key I>";
	bitmap "ivstudio/icons/icident.png";
	category view;
}
command FitViewToContents {
	label "&fitview";
	prompt "&fitviewPrompt";
	acceleratorText "Shift+F";
    	acceleratorDefinition "<Shift><Key F>";
	bitmap "ivstudio/icons/icfittr.png";
	category view;
}
command ToggleTransformed {
	label "&settransformed";
	prompt "&settransformedPrompt";
	acceleratorText "Ctrl+T";
    	acceleratorDefinition "<Ctrl><Key T>";
	category edit;
}
command ToggleCrossCursor {
	label "&toggleCrossCursor";
	prompt "&toggleCrossCursorPrompt";
	acceleratorText "Shift+C";
    	acceleratorDefinition "<Shift><Key C>";
	category view;
}

