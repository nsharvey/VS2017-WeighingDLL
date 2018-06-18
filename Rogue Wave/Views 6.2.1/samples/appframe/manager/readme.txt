
                             Rogue Wave Views 6.2
                        Application Framework Package

                              Samples 'manager'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'manager'
-----------------
  Example of a basic Views manager editor.

  This simple application shows you how to open and edit Rogue Wave Views
  managers using the Application Framework library. It allows you to move and
  reshape the graphic objects of a Views manager displayed in a manager view.
  It provides commands that perform different kinds of alignments on selected
  objects, or that give the size of the active selected object to a group of
  selected objects.

  The way the events that occur on the view are managed and sent to the
  document is typical of Application Framework mechanisms.

    * the event is tracked on the manager view by overriding a method of the
      select interactor (see IlvSelectInteractor).

    * a command specific to the event is built. This command can undo or redo
      the changes.

    * the new command is given to the associated document that notifies the
      other views of the changes. The document stores the command so that it
      will be able to undo the changes or redo them later.

  Classes involved:
    - IlvDvManagerDocument
    - IlvDvManagerView
    - IlvSelectInteractor
    - IlvDvCommand

  Source files:
    - include/ManagerDocument.h
    - include/ManagerView.h
    - include/mgercmd.h
    - include/selinter.h
    - src/manager.cpp
    - src/ManagerDocument.cpp
    - src/ManagerView.cpp
    - src/mgercmd.cpp
    - src/selinter.cpp

