
                             Rogue Wave Views 6.2
                               Grapher Package

                              Samples 'graphed'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'graphed'
-----------------
  This sample shows how to create a small grapher editor.

  This sample shows how to use the predefined interactors of the grapher
  library to build a small editor. The GUI of this sample uses a toolbar that
  enables to switch between several editing modes:

    * [IMAGE] Selection. This mode is implemented by the
      IlvGraphSelectInteractor class.

    * [IMAGE] Link creation. This mode is implemented by the
      IlvMakeLinkInteractor class. The type of link created by the interactor
      is specified by a factory. This factory is a subclass of
      IlvMakeLinkInteractorFactory that creates a copy of a link model. You can
      use the combo box to choose the link model that must be used. The [IMAGE]
      toggle in the toolbar lets you specify whether created links are
      oriented.

    * [IMAGE] Pin editing. This mode is implemented by the
      IlvPinEditorInteractor class and lets you interactively edit the
      connection pins of a node.

  Classes involved:
    - IlvGrapher
    - IlvMakeLinkInteractor
    - IlvMakeLinkInteractorFactory
    - IlvPinEditorInteractor
    - IlvGraphSelectInteractor

  Source files:
    - src/graphed.cpp

