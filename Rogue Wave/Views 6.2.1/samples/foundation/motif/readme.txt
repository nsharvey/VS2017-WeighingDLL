
                             Rogue Wave Views 6.2
                             Foundations Package

                               Samples 'motif'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'ilvmotif'
------------------
  This sample shows you how to create a Rogue Wave Views application on top of
  a Motif application.

  A regular Motif DrawingArea gadget is created, then a Rogue Wave Views
  IlvContainer is built using this gadget.
  A few objects are created to populate the container.

  Classes involved:
    - IlvDisplay
    - IlvContainer

  Source files:
    - src/ilvmotif.cpp


Sample: 'dragdrop'
------------------
  Demonstration of Motif Drag-and-Drop from and to Rogue Wave Views.

  To be able to build this sample, the Manager package must be installed.
  A specific subclass of IlvInteractor is defined to enable the drag-and-drop
  from a Motif-based gadget.
  Four windows are created:

    * Source Container: contains a few Rogue Wave Views graphic objects that
      you can drag and drop in one of the two Motif drop sites.

    * Destination Container: a Motif drop site displaying Rogue Wave Views
      graphic objects. If you drop a Motif gadget in there, an IlvLabel is
      created.

    * DragArea: a Motif Shell containing a Label gadget that can be dragged and
      dropped in one of the drop sites.

    * DropArea: a Motif Shell that accepts drop requests. If you drop a Rogue
      Wave Views object in there, a Label gadget displaying the graphic object
      class is created at the drop location.

  A new Atom is created (ILVOBJECT_Atom) to specify that the drop source is a
  Rogue Wave Views object.

  Classes involved:
    - IlvContainer
    - IlvInteractor

  Source files:
    - src/dragdrop.cpp
    - src/ddmotif.cpp
    - include/ddmotif.h
    - src/ddinter.cpp
    - include/ddinter.h
    - src/ddpanels.cpp
    - include/ddpanels.h


Sample: 'multidd'
-----------------
  Another demonstration of Motif drag-and-drop between two separated Rogue Wave
  Views applications.

  To be able to build this sample, the Manager package must be installed.
  This sample is very similar to dragdrop, except that it lets you drag objects
  from one application, and drop them in another one.
  Note that you will have to run two instances of the sample in order to
  manipulate it.

  Classes involved:
    - IlvContainer
    - IlvInteractor

  Source files:
    - src/dragdrop.cpp
    - src/ddmotif.cpp
    - include/ddmotif.h
    - src/ddinter.cpp
    - include/ddinter.h
    - src/ddpanels.cpp
    - include/ddpanels.h


Sample: 'scrollhk'
------------------
  This sample shows how to connect an IlvManagerViewHook to a Motif
  ScrolledWindow gadget.

  The Grapher package must be installed to be able to build this sample.
  A ScrolledWindow gadget is created inside an IlvView controlled by an
  IlvGrapher through an IlvManagerViewHook.
  The hook controls the gadget scrollbars.
  On the other hand, callbacks are added to the scrollbars of the Motif gadget
  to update the view hook attached to it (see IlvScrollViewHook::initScrollBars).

  Classes involved:
    - IlvManageViewHook

  Source files:
    - src/scrollhk.cpp

