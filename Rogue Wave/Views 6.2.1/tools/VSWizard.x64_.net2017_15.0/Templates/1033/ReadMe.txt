========================================================================
    Rogue Wave Views Application Wizard : "[!output PROJECT_NAME]" Project Overview
========================================================================

Rogue Wave Views Application Wizard has created this "[!output PROJECT_NAME]" project for you as a starting point.

This file contains a summary of what you will find in each of the files that make up your project.

[!output PROJECT_NAME].sln
     This is the main project file generated for your application.

[!if EMPTYAPP]
     The application is empty. You have to provide the main function.

[!else]     
main.cpp
     This file contains the code of your application.
[!if CONTAINERAPP]
     The generated application is based on a container.
[!endif]
[!if GADGETCONTAINERAPP]
     The generated application is based on a gadget container.
[!if DEFAULTCLASS]
     It uses an IlvGadgetContainer.
[!else]
     It uses a subclass of IlvGadgetContainer.
[!endif]
[!if GADCONTBUTTON]
     A button and its callback was added to the gadget container.
[!endif]
[!if GADCONTRECT]
     An IlvSCManagerRectangle was added to the gadget container.
[!endif]
[!endif]
[!if MANAGERAPP]
     The generated application is based on a manager.
[!if DEFAULTCLASS]
     It uses an IlvManager.
[!else]
     It uses a subclass of IlvManager.
[!endif]
[!if ADDOBJS]
     Some objects were added to the manager.
[!endif]
[!if INTERMANAGER]
     An IlvSelectInteractor was added to the view of the manager.
[!endif]
[!if OBSERVER]
     An observer was added to the manager.
[!endif]
[!endif]
[!if GRAPHER]
     The generated application is based on a grapher.
[!if DEFAULTCLASS]
     It uses an IlvGrapher.
[!else]
     It uses a subclass of IlvGrapher.
[!endif]
[!if ADDOBJS]
     Some nodes were added to the grapher.
[!endif]
[!if ADDLINKS]
     Some links were added to the grapher.
[!endif]
[!if OBSERVER]
     An observer was added to the grapher.
[!endif]
[!if INTERGRAPHSEL]
     An IlvGraphSelectInteractor was added to the view of the grapher.
[!endif]
[!if INTERGRAPHIMG]
     An IlvMakeLinkImageInteractor was added to the view of the grapher.
[!endif]
[!endif]
[!endif]
