
                             Rogue Wave Views 6.2
                                Charts Package

                             Samples 'multiscale'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'multiscale'
--------------------
  Creation of a chart with several stacked scales for the ordinate.

  This sample shows you how to define a chart with several stacked scales along
  the ordinate.

  It creates a chart using a Cartesian projector and another one using a Polar
  projector. Both charts display three data sets. Each data set is displayed
  relatively to a different ordinate scale with a different displayer.

  Classes involved:
    - IlvChartGraphic
    - IlvCartesianProjector
    - IlvPolarProjector
    - IlvChartCoordinateInfo
    - IlvRectangularScaleDisplayer
    - IlvCircularScaleDisplayer
    - IlvRectangularGridDisplayer
    - IlvCircularGridDisplayer
    - IlvStairChartDisplayer
    - IlvPolylineChartDisplayer
    - IlvStepChartDisplayer

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/multiscale.cpp

