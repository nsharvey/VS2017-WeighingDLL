
                             Rogue Wave Views 6.2
                              Prototypes Package

                          Samples 'custom_accessor'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'Custom Accessor Creation and Use'
------------------------------------------
  Shows how to define a new class of accessors.

  The new accessor class is IlvGraphicPathAccessor, and can be used in a
  prototype to move an object along a graphic path (defined by a set of
  polylines). When the value of the accessor is changed, the object is moved on
  the graphic path to a percentage of the total length of the path. The class
  IlvGraphicPathAccessor is declared in the C++ file gpacc.h and defined in
  gpacc.cpp. The program gppanel shows an example of use of the class
  IlvGraphicPathAccessor: the panel contains a slider gadget connected to an
  instance of a prototype representing an object moving along a graphic path.
  When the user moves the slider, the object moves along the path accordingly.

  Classes involved:
    - IlvUserAccessor
    - IlvGroup

  Source files:
    - include/gpacc.h
    - src/gpacc.cpp
    - src/gppanel.cpp
    - data/bunnypan.ilv
    - data/grpath.ipl


Sample: 'Extending Studio to Use a Custom Accessor'
---------------------------------------------------
  Shows how to integrate a new class of accessors in Studio, if you have the 2D
  Controls module of Views.

  The gpstudio is a version of Studio linked with the IlvGraphicPathAccessor
  class. When you use gpstudio to edit prototypes, the new graphic path
  accessor class appears automatically as a new action in the Action combo box
  of the Accessors page of the Prototype Inspector. To see it:

    *  load the panel file data/bunnypan.ilv,

    *  select the prototype library grpath in the Prototypes palette,

    *  double-click the "movbunny" prototype,

    *  select the Graphic Behaviors page in the Group Inspector,

    *  select the "distance" attribute in the list of behaviors.

  You will see the definition of the GraphicPath accessor in Display menu of
  the behaviors page of the group inspector. Note that in its current state,
  the sample does not use dynamic modules.

  Classes involved:
    - IlvStExtension
    - IlvStudio

  Source files:
    - include/gpacc.h
    - src/gpacc.cpp
    - src/gpstmain.cpp
    - src/libini.cpp
    - src/defaultx.cpp

