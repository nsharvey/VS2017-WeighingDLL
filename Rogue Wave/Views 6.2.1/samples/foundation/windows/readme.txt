
                             Rogue Wave Views 6.2
                             Foundations Package

                              Samples 'windows'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'ilvwin'
----------------
  Integrate Windows components into a Rogue Wave Views application.

  This sample illustrates how to integrate Windows components into an Rogue
  Wave Views application.
  You can load files using the real Windows menus and change the zooming factor
  by moving the slider. The button lets you change the view background.
  You can drag and drop ILV files from the File Manager to the Rogue Wave Views
  container window.

  Source files:
    - src/ilvwin.cpp


Sample: 'winilv'
----------------
  Integrate Rogue Wave Views components into a Windows application.

  This sample illustrates how to integrate Rogue Wave Views components in a
  Windows application. Here, the whole interface was built in a Windows Dialog.
  You can load files using the real Windows menus and change the zooming factor
  by moving the slider. The button lets you change the view background.

  Classes involved:
    - IlvDisplay
    - IlvContainer

  Source files:
    - src/winilv.cpp


Sample: 'metafile'
------------------
  Convert Rogue Wave Views data files to a Windows metafile.

  This sample illustrates how to convert a Rogue Wave Views data file to a
  Windows metafile.
  The program is based on an extension of the IlvWindowsVirtualDevice class. To
  actually convert the graphic file, press the 'D' key when the focus is set in
  the container. You may also use the following accelerators:

    * 'P' to dump into a placeable metafile.

    * 'E' to dump into an enhanced metafile (only in 32 bits versions).

    * 'W' to dump into a Windows metafile.

  Source files:
    - src/metafile.cpp


Sample: 'ilvmdi'
----------------
  Use of the IlvMDIChild property on Rogue Wave Views views.

  This sample shows you how to use the IlvMDIChild property on Rogue Wave Views
  views.

  Classes involved:
    - IlvView

  Source files:
    - src/ilvmdi.cpp


Sample: 'gdiplus'
-----------------
  This sample shows the GDI+ features used in Rogue Wave Views.

  This sample shows the GDI+ features used in Rogue Wave Views : Transparency
  and Anti-aliasing. It allows you to change the transparency of the displayed
  objects, as well as the antialiasing mode used. Note that this sample use
  Rogue Wave Script to perform the actions, and that the C++ part only load the
  ILV file containing both the GUI and the script functions.

  Classes involved:
    - IlvGadgetContainer

  Source files:
    - data/guigdiplus.ilv
    - data/gdiplus.ilv
    - src/gdiplus.cpp

