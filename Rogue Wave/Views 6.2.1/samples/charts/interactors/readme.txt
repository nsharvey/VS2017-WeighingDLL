
                             Rogue Wave Views 6.2
                                Charts Package

                            Samples 'interactors'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'stock'
---------------
  Association of different behaviors with a chart.

  This sample shows you how to associate several behaviors with a chart object.
  To do this, it uses an instance of the IlvChartInteractorManager class to
  register several predefined chart interactors (instances of subclasses of
  IlvChartInteractor).

  This sample defines the following behaviors:

    * Left drag: Zooms in the displayed data.

    * Shift key + left drag: Zooms out the displayed data.

    * Right drag: Translates the displayed data.

    * Arrow keys: Translate the displayed data.

    * 'i': Toggle the InfoView interactor.

    * 's': Toggle the picking mode of the InfoView interactor, between "nearest
      point" and "item".

    * 'm': Toggle the 'follow mouse' mode of the InfoView interactor.

  NOTE: If you use a mouse with two buttons, add the following line in the file
  views.ini in order to make the pan interactor work with the second button of
  your mouse:

  UseRightButton = true

  Classes involved:
    - IlvCartesianChart
    - IlvMemoryChartData
    - IlvChartYValueSet
    - IlvChartCoordinateInfo
    - IlvRectangularScaleDisplayer
    - IlvBarChartDisplayer
    - IlvHiLoOpenCloseChartDisplayer
    - IlvChartLegend
    - IlvChartInteractorManager
    - IlvChartZoomInteractor

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/stock.cpp
    - data/stock.dat


Sample: 'lens'
--------------
  Shows how to set a local zoom on a coordinate.

  This sample shows you how the IlvZoomCoordinateTransfomer class can be
  associated with a coordinate to simulate a local zoom. In this sample, the
  transformer is associated with the abscissa coordinate of a Cartesian chart.
  Several accelerators allow you to modify the properties of the transformer:

    *  The right and left keys let you translate the zoom window.

    *  The up and down keys let you expand or shrink the zoom window.

    *  The '+' and '-' keys let you increase or decrease the zoom factor.

    *  The 'c' key lets you toggle the continuous mode of the zoom.

    *  The 'p' key lets you toggle between a Polar and a Cartesian projector.

  Classes involved:
    - IlvCartesianChart
    - IlvMarkedPolylineChartDisplayer
    - IlvZoomCoordinateTransfomer
    - IlvZoomScaleStepsUpdater

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/lens.cpp

