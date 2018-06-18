
                             Rogue Wave Views 6.2
                               Gadgets Package

                               Samples 'table'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'matrix'
----------------
  This sample shows how to subclass the IlvAbstractMatrix class to implement a
  matrix that has in infinite number of rows.

  When trying to reach the last row of the matrix using the scroll bar, new
  rows are added to the matrix.

  Classes involved:
    - IlvAbstractMatrix

  Source files:
    - src/matrix.cpp


Sample: 'huge'
--------------
  This sample shows how to scroll in a large number of data items.

  The actual number of items is larger than an IlvUShort, which is the basic
  type for table indexes. This sample demonstrates how to handle an IlvUInt
  index, using logical scroll on a smaller table.

  Classes involved:
    - IlvAbstractMatrix
    - IlvScrolledGadget

  Source files:
    - src/hugetabl.cpp


Sample: 'random'
----------------
  This sample displays an animated IlvAbstractMatrix of 1000 rows and 3
  columns.

  The first column shows the row index, from 0 to 999. The second column
  receives a random integer from 0 to 1000. The third column stores an
  IlvRectangularGauge that represents this value. Random numbers are modified
  periodically using a timer. The sample lets you edit a threshold. When the
  number becomes greater than this threshold the number turns red.

  Classes involved:
    - IlvAbstractMatrix
    - IlvTimer
    - IlvRectangularGauge
    - IlvFont
    - IlvNumberField
    - IlvToggle

  Source files:
    - src/random.cpp


Sample: 'edit'
--------------
  This sample shows how to create a subclass of the IlvAbstractMatrixItem
  class. It also shows how to create specific matrix item editors.

  The sample shows a matrix with several rows and 4 columns. The first column
  contains labels (IlvLabelMatrixItem class). The second column contains
  integer values (IlvIntMatrixItem class). The third column contains float
  values (IlvFloatMatrixItem class). The fourth column also contains float
  values, but here a subclass of IlvFloatMatrixItem is used. This subclass
  allow the user to control the display format of the float value.

  A matrix item editor factory is set on the matrix to control the edition of
  each cell. Two new editors classes are created : An editor for float value
  that uses a spinbox, and an editor for integer values that uses a slider.

  Classes involved:
    - IlvAbstractMatrixItem
    - IlvMatrix
    - IlvMatrixItemEditor
    - IlvSpinBox
    - IlvNumberField
    - IlvSlider

  Source files:
    - src/edit.cpp

