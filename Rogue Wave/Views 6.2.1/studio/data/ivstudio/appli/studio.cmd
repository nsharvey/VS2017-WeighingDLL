//
//    Rogue Wave Views Studio Command Description file 
//
//	Application Extension
//

command NewApplicationFolder {
    label "&newApplicationFolder";
    prompt "&newApplicationFolderP";
    category application;
}

command RemoveApplicationFolder {
    label "&removeApplicationFolder";
    prompt "&removeApplicationFolderP";
    category application;
}

command NewPanelClass {
    label "&newPanelClass";
    prompt "&newPanelClassP";
    bitmap "ivstudio/appli/icaddbuf.png";
    category application;
}

command RemovePanelClass {
    label  "&removePanelClass";
    prompt "&removePanelClassP";
    bitmap "ivstudio/appli/icrembuf.png";
    category application;
}

command AddPanel {
    label "&addPan";
    prompt "&addPanPrompt";
    category application;
}

command RemovePanel {
    label "&remPan";
    prompt "&remPanPrompt";
    category application;
}

command NewApplication {
    label "&application";
    prompt "&newAppPrompt";
    category application;
    bitmap "ivstudio/appli/iciva.png"
    messages NewApplication;
}

command MakeDefaultApplication {
    label  "&makeDefaultApplication";
    prompt "&makeDefaultApplicationP";
    category application;
}

command OpenApplication {
    label "&mopen...";
    tooltip "&ttmopen...";
    acceleratorText "Ctrl+O";
    acceleratorDefinition "<Ctrl><Key O>";
    prompt "&openAppliPrompt";
    bitmap "icopen";
    messages NewApplication;
    category application;
}

command SaveApplication {
    label  "&msave";
    tooltip  "&ttmsave";
    acceleratorText "Ctrl+S";
    acceleratorDefinition "<Ctrl><Key S>";
    prompt "&saveAppli";
    bitmap "icsave";
    category application;
}

command SaveApplicationAs {
    label  "&msaveAs...";
    tooltip  "&ttmsaveAs...";
    prompt "&saveAppliAs...";
    category application;
    messages SaveApplicationAs;
}

command ShowAllTestPanels {
    label "&mshowTestPan";
    prompt "&showTestPanPrompt";
    category application;
    category panel;
}

command KillTestPanels {
    label "&mkillTestPan";
    prompt "&killTestPanPrompt";
    category application;
    messages KillTestPanels;
}

command TestApplication {
    label "&mtest";
    tooltip "&ttmtest";
    toggleLabel "&stopTest";
    prompt "&testAppPrompt";
    togglePrompt "&stopTest";
    bitmap "icrun";
    category application;
    messages TestApplication;
}

command ShowClassPalette {
    label "&classesItem";
    prompt "&showClassPaletteP";
    bitmap   "ivstudio/appli/icshowcp.png";
    category application;
    category panel;
}

command HideClassPalette {
    label "&close";
    prompt "&closeClassPaletteP";
    bitmap  "icquit";
    category application;
    category panel;
}

command EditApplication {
    label  "&editAppli";
    prompt "&editAppliP";
    bitmap "ivstudio/appli/icapped.png";
    category application;
}

command ShowPanelClassInspector {
    label  "&inspPanClass";
    prompt "&inspPanClassP";
    bitmap "ivstudio/appli/icpci.png";
    category application;
    category panel;
};

command ShowApplicationInspector {
    label   "&inspAppli";
    prompt  "&inspAppliP";
    bitmap "ivstudio/appli/icappi.png";
    category application;
    category panel;
}

command SelectParentState {
    label   "&selectParentState";
    prompt  "&selectParentStateP";
    bitmap  "ivstudio/icons/icup.png";
    category state;
}

command NewStateSubset {
    label   "&newStateSubset";
    prompt  "&newStateSubsetP";
    bitmap  "ivstudio/appli/icnewss.png";
    category state;
}

command RenameStateSubset {
    label   "&rename";
    prompt  "&renameStateSubsetP";
    bitmap  "ivstudio/appli/icrenss.png";
    category state;
}

command RemoveStateSubset {
    label   "&remove";
    prompt  "&removeStateSubsetP";
    bitmap  "ivstudio/appli/icremss.png";
    category state;
}

command NewState {
    label   "&newState";
    prompt  "&newStateP";
    bitmap  "ivstudio/appli/icnewst.png";
    category state;
}

command NewRootState {
    label    "&newRootState";
    prompt   "&newRootStateP";
    bitmap   "ivstudio/appli/icnewst.png";
    category state;
}

command RenameState {
    label   "&rename";
    prompt  "&renameStateP";
    bitmap  "ivstudio/appli/icrenst.png";
    category state;
}

command RemoveState {
    label   "&remove";
    prompt  "&removeStateP";
    bitmap  "ivstudio/appli/icremst.png";
    category state;
}

command NewStateRequirement {
    label   "&newStateRequirement";
    prompt "&newStateRequirementP";
    bitmap "ivstudio/icons/icnew.png";
    category state;
}

command RemoveStateRequirement {
    label   "&removeStateRequirement";
    acceleratorText "Del";
    prompt "&removeStateRequirementP";
    bitmap "ivstudio/icons/icrem.png";
    category state;
}

command OpenStateFile {
    category state;
    category debug;
}

command SaveStateFile {
    category state;
    category debug;
}

command ShowStateTree {
    label  "&stateTree";
    prompt "&stateTreeP";
    category state;
    category panel;
}

command ShowStateInspector {
    label   "&stateInsp";
    prompt  "&stateInspP";
    category state;
    category panel;
}

command EditStates {
    label   "&editStates"
    prompt  "&editStatesP";
    category state;
    category panel;
}

command HelpStateInspector {
    label  "&help";
    prompt "&helpStateInspectorP";
    bitmap "ivstudio/icons/ichelp.png";
    category panel;
}

command HelpStateTree {
    label "&help";
    prompt "&helpStateTreeP";
    bitmap "ivstudio/icons/ichelp.png";
    category panel;
}

command HelpClassPalette {
    label "&help";
    prompt "&helpClassPaletteP";
    bitmap "ivstudio/icons/ichelp.png";
    category panel;
}

