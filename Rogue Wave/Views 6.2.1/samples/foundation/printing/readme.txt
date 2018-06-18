
                             Rogue Wave Views 6.2
                             Foundations Package

                              Samples 'printing'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'headfoot'
------------------
  Header and footer usage with IlvPrintableLayout.

  An example of how to use to print a chart on two pages, with header and
  footer using an IlvPrintableLayoutMultiplePages instance.

  Classes involved:
    - IlvPrintableLayoutMultiplePages
    - IlvPrintableText
    - IlvPrintableDocument

  Source files:
    - src/headfoot.cpp


Sample: 'photops'
-----------------
  An example of how to print using Postscript printing.

  This sample prints a bitmap on an A6 paper in landscape mode using an
  IlvPSPrinter without displaying any printing dialog box.

  Classes involved:
    - IlvPSPrinter
    - IlvPrintableDocument
    - IlvPrintableGraphic

  Source files:
    - src/photops.cpp


Sample: 'photpsdlg'
-------------------
  An example of how to print using an IlvPSPrinter and an
  IlvPostscripPrinterDialog instance.

  This sample prints a bitmap on an A6 paper in landscape mode using an
  IlvPSPrinter with an IlvPostscripPrinterDialog to allow the user to change
  the printing settings.

  Classes involved:
    - IlvPSPrinter
    - IlvPostscripPrinterDialog
    - IlvPrintableDocument
    - IlvPrintableGraphic

  Source files:
    - src/photpsdlg.cpp


Sample: 'photpspr'
------------------
  An example of how to print using Postscript printing with a printing preview
  displayer.

  This sample prints a bitmap on an A6 paper in landscape mode using an
  IlvPSPrinter and an IlvPrinterPreviewDialog.

  Classes involved:
    - IlvPSPrinter
    - IlvPrinterPreviewDialog
    - IlvPrintableDocument
    - IlvPrintableGraphic

  Source files:
    - src/photpspr.cpp


Sample: 'photowin'
------------------
  An example of how to print using a Windows printer.

  This sample prints a bitmap on an A6 paper in landscape mode using an
  IlvWindowsPrinter. During this print operation, an OS-dependent printing
  dialog box is displayed.
  This sample only runs under Windows.

  Classes involved:
    - IlvWindowsPrinter
    - IlvPrintableDocument
    - IlvPrintableGraphic

  Source files:
    - src/photowin.cpp


Sample: 'phowindc'
------------------
  An example of how to print using IlvWindowsPrinter and an
  IlvWindowsPrinterDCFactory subclass.

  This sample prints a bitmap on an A6 paper in landscape mode using an
  IlvWindowsPrinter without displaying any printing dialog box.
  To achieve that, a subclass of IlvWindowsPrinterDCFactory has been
  implemented. This subclass sets the paper size to A6, and the orientation to
  Landscape. The usage of this subclass gives the possibility to print with
  these non default settings without any dialog box.
  This sample only runs under Windows.

  Classes involved:
    - IlvWindowsPrinter
    - IlvWindowsPrinterDCFactory
    - IlvPrintableDocument
    - IlvPrintableGraphic

  Source files:
    - src/phowindc.cpp
    - src/windcfac.cpp
    - include/windcfac.h


Sample: 'phowinpr'
------------------
  An example of how to print using IlvWindowsPrinter printing with a printing
  preview displayer.

  This sample prints a bitmap on an A6 paper in landscape mode using an
  IlvWindowsPrinter and an IlvPrinterPreviewDialog.
  The IlvWindowsPrinterDCDialogFactory is also used in this sample to allow the
  user to update the printing settings while the printer preview is displayed.
  IlvWindowsPrinterDCDialogFactory is a subclass of IlvWindowsPrinterDCFactory.
  This sample only runs under Windows.

  Classes involved:
    - IlvWindowsPrinter
    - IlvWindowsPrinterDCDialogFactory
    - IlvPrinterPreviewDialog
    - IlvPrintableDocument
    - IlvPrintableGraphic

  Source files:
    - src/phowinpr.cpp

