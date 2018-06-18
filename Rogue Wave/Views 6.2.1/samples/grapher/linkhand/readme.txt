
                             Rogue Wave Views 6.2
                               Grapher Package

                              Samples 'linkhand'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'linkhand'
------------------
  This sample demonstrates the use of IlvLinkHandle.

  This sample shows how the IlvLinkHandle class can be used to create grapher
  links from graphic objects. Links are created by a factory (a subclass of
  IlvMakeLinkInteractorFactory) that references a graphic model. These models
  are read from an ilv file and appear in a palette placed at the top of the
  panel. Below the palette, a grapher view displays nodes arranged in rows and
  columns.

  Each graphic model is associated with a button interactor. Clicking on a
  model in the palette sets it as graphic model for the link factory. As a
  visual feedback, an image of the model appears in the rightmost part of the
  palette. The actual models are copies of the graphic objects read from the
  file. This allows to safely share a model between both its visual
  representation (managed by an IlvTransformedGraphic instance) and all the
  created link handles.

  Pressing the spacebar switches between two editing modes:

    * Selection. This mode is implemented by the IlvGraphSelectInteractor
      class. When this mode is active, the visual representation of the graphic
      model in the palette disappears.

    * Link creation. In this mode, you can connect the nodes displayed in the
      grapher view. The created link will reference the current graphic model.

  Classes involved:
    - IlvGrapher
    - IlvMakeLinkInteractor
    - IlvMakeLinkInteractorFactory
    - IlvLinkHandle
    - IlvGraphSelectInteractor
    - IlvTransformedGraphic

  Source files:
    - src/linkhand.cpp

