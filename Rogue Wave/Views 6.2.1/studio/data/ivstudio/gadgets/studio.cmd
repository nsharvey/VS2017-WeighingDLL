// 
// Rogue Wave Views Studio Command Descript file
// 
//	Gadgets Extension
// 

command NewGadgetBuffer {
    label   "&newGadgetBuffer";
    prompt  "&newGadgetBufferP";
    category buffer;
    bitmap "ivstudio/gadgets/icfocus.png";
    // this command execute the NewBuffer command
}

command RemoveAllAttachments {
    label  "&removeAllAttachments";
    prompt "&removeAllAttachmentsP";
    category attachments;
}

command RemoveAttachments {
    label  "&removeAttachments";
    prompt "&removeAttachmentsP";
    category attachments;
}

command SelectAttachmentsMode {
    label "&attachmentMode";
    prompt "&attachmentModeP";
    bitmap "ivstudio/gadgets/icattach.png";
    category mode;
    category gadgets;
}

command SelectFocusMode {
    label  "&focusMode";
    prompt "&focusModeP";
    bitmap "ivstudio/gadgets/icfocus.png";
    category mode;
    category gadgets;
}

command AddNumberField {
    // interactive false;
    label "IlvNumberField";
    category add;
}

command AddPasswordTextField {
    interactive false;
    label "IlvPasswordTextField";
    category add;
};

command AddDateField {
    interactive false;
    label "IlvDateField";
    category add;
};

command AddToolbar {
    interactive true;
    label "IlvToolbar";
    category add;
};

command SelectMenuMode {
    label "&menuMode";
    tooltip "&ttmenuMode";
    prompt "&menuModePrompt";
    bitmap "ivstudio/gadgets/icmenu.png";
    category mode;
}

command SelectMatrixMode {
    label "&matrixMode";
    tooltip "&ttmatrixMode";
    prompt "&matrixModePrompt";
    bitmap "ivstudio/gadgets/icmatrix.png";
    category mode;
}

command SelectSpinBoxMode {
    label "&spinBoxMode";
    prompt "&spinBoxModePrompt";
    bitmap "ivstudio/gadgets/icspinb.png";
    category mode;
}

command SelectSCManagerRectangleMode {
    label "IlvSCManagerRectangle";
    prompt "&scMgrPrompt";
    bitmap "ivstudio/gadgets/icscmgr.png";
    category mode;
}
