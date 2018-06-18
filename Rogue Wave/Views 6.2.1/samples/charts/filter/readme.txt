
                             Rogue Wave Views 6.2
                                Charts Package

                               Samples 'filter'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'chfilter'
------------------
  Shows how to use a predefined filter to display a large number of points.

  This sample shows you how the IlvChartPointsFilter class can be associated
  with displayers that are connected to huge data sets. The predefined
  IlvChartPointsFilterFactory class is used to set the filtering mechanism on
  the displayers. You can invoke the sample program with three optional
  parameters:

    *  The first parameter gives the number of points of each displayers.

    *  The second parameter gives the number of displayers.

    *  The third parameter gives the cluster size of the filter. This value,
      expressed in screen pixels, gives the size of the area where points are
      pruned by the filter.

  If no parameter is given, the sample creates three displayers with 500000
  points each. The cluster default size is 5.

  The following interactions are available:

    * Zooming (Drag with the left button to zoom, shift key + drag with the
      left button to unzoom).

    * Panning (Drag with the right button).

    * Scrolling (With the arrow keys).

  Classes involved:
    - IlvCartesianChart
    - IlvPolylineChartDisplayer
    - IlvChartPointsFilter
    - IlvChartPointsFilterFactory
    - IlvChartInteractorManager
    - IlvChartInteractor

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/chfilter.cpp

