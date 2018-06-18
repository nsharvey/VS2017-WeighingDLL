
                             Rogue Wave Views 6.2
                               Gadgets Package

                              Samples 'dragdrop'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'dragdrop'
------------------
  This sample shows how to use the drag-and-drop feature of the IlvGadgetItem
  class between two instances of the IlvTreeGadget class.

  You can drag and drop one item, or a whole hierarchy, from a tree gadget to
  the other one. When an item is being dragged over a possible target, the
  target is highlighted. If you press the CTRL key during the operation, the
  item being dragged will be copied and inserted into the target tree gadget.
  Otherwise, the item being dragged will be simply moved to its new location.

  Classes involved:
    - IlvTreeGadget
    - IlvTreeGadgetItem
    - IlvGadgetItem
    - IlvSplitterGadget
    - IlvContainer
    - IlvGadgetItemHolder
    - IlvGraphicHolder
    - IlvPalette

  Source files:
    - src/dragdrop.cpp

