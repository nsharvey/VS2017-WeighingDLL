
command NewPrototypeEditionBuffer {
    label  "&IlvMsgStProto141";
    prompt "&IlvMsgStProto142";
    bitmap "ivstudio/protos/png/protopal.png";
    category prototypes;
}

command EditPrototypes {
    label  "&IlvMsgStProto143";
    prompt "&IlvMsgStProto144";
    category prototypes;
}

command ShowGroupInspector {
    label  "&IlvMsgStProto222";
    prompt "&IlvMsgStProto223";
    acceleratorText "Ctrl+Shift+G";
    acceleratorDefinition "<Ctrl><Shift><Key G>";
    category prototypes;
}

command ShowPrototypePalette {
    label  "&IlvMsgStProto147";
    prompt "&IlvMsgStProto148";
    category prototypes;
}

command GroupIntoGroup {
    label  "&IlvMsgStProto149";
    prompt "&IlvMsgStProto150";
    category edit;
    category group;
    selector group;
}

command PrGroupIntoGraphicSet {
    label  "IlvGraphicSet";
    prompt "&graphsetPrompt";
    category edit;
}

command PrGroupIntoSelector {
    label  "IlvSelector";
    prompt "&selectorPrompt";
    category edit;
}

command PrGroupIntoSmartSet {
    label  "IlvSmartSet";
    prompt "&smartSetPrompt";
    category edit;
}

command UngroupIlvGroups {
    label "&ungroup";
    prompt "&ungroupPrompt";
    acceleratorText "Ctrl+U";
    acceleratorDefinition "<Ctrl><Key U>";
    category edit;
}

command MakePrototypeNode {
    label "&makeNode";
    prompt "&makeNodeP";
    bitmap "icmknode";
    category prototypes;
}

command OpenPrototypeBuffer {
    label "&mopen...";
    acceleratorText "Ctrl+O";
    acceleratorDefinition "<Ctrl><Key O>";
    prompt "&openData";
    bitmap "icopen";
    messages SelectBuffer;
    category buffer;
}

// Palette commands

command NewProtoLibrary {
    label  "&IlvMsgStProto151";
    prompt "&IlvMsgStProto152";
    category prototypes;
}

command OpenProtoLibrary {
    label  "&IlvMsgStProto153";
    prompt "&IlvMsgStProto154";
    category prototypes;
}

command SaveProtoLibrary {
    label  "&IlvMsgStProto155";
    prompt "&IlvMsgStProto156";
    category prototypes;
}

command SaveProtoLibraryAs {
    label  "&IlvMsgStProto157";
    prompt "&IlvMsgStProto158";
    category prototypes;
}

command CloseProtoLibrary {
    label  "&IlvMsgStProto159";
    prompt "&IlvMsgStProto160";
    category prototypes;
}

command ClosePrototypePalette {
    label  "&close";
    prompt "&IlvMsgStProto162";
    category prototypes;
}

command NewPrototype {
    label  "&IlvMsgStProto163";
    prompt "&IlvMsgStProto164";
    category prototypes;
}

command LoadPrototype {
    label  "&IlvMsgStProto165";
    prompt "&IlvMsgStProto166";
    category prototypes;
}

command EditPrototype {
    label  "&IlvMsgStProto167";
    prompt "&IlvMsgStProto168";
    category prototypes;
}

command ToggleTimers {
    label  "&ToggleTimers";
    prompt "&ToggleTimersPrompt";
	acceleratorText "Ctrl+Shift+T";
    acceleratorDefinition "<Ctrl><Shift><Key T>";
    category prototypes;
}

command DeletePrototype {
    label  "&IlvMsgStProto169";
    prompt "&IlvMsgStProto170";
    category prototypes;
}

command RenamePrototype {
    label  "&IlvMsgStProto171";
    prompt "&IlvMsgStProto172";
    category prototypes;
}

command SelectGroupConnectionMode {
    label "&IlvMsgStProto179";
    prompt "&IlvMsgStProto180";
    bitmap "icgrpcon";
    category mode;
    category prototypes;
}
command SelectPrototypeCreationMode {
    label "&PrototypeCreation";
    prompt "&PrototypeCreation";
    category mode;
    category prototypes;
}
