
                             Rogue Wave Views 6.2
                               Gadgets Package

                              Samples 'inspect'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'inspect'
-----------------
  This sample shows how to implement a small generic inspector using the
  IlvHierarchicalSheet class.

  You can load Rogue Wave Views files and inspect their content in the
  hierarchical sheet. The items of the first level are the names of the loaded
  files. When you expand them, the sheet displays all the objects contained in
  the corresponding file. Then you can inspect each object property, and modify
  it, the changes are automatically applied.

  Classes involved:
    - IlvHierarchicalSheet
    - IlvTreeGadgetItem
    - IlvLabelMatrixItem
    - IlvGadgetItem
    - IlvButton
    - IlvValue
    - IlvFileBrowser
    - IlvPathName
    - IlvGadgetContainer
    - IlvGadgetItemHolder
    - IlvGraphicHolder
    - IlvPalette

  Source files:
    - src/inspect.cpp

