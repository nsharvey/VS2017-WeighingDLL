
                             Rogue Wave Views 6.2
                                Charts Package

                               Samples 'simple'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'cartesian'
-------------------
  Creation of a simple Cartesian chart with several displayers.

  This sample shows how to create a simple Cartesian chart using the
  IlvCartesianChart class. Once created, the chart is used to display three
  data sets using a standard displayer: IlvPolylineChartDisplayer.

  Classes involved:
    - IlvCartesianChart
    - IlvChartPointSet
    - IlvPolylineChartDisplayer

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/cartesian.cpp


Sample: 'polar'
---------------
  Creation of a simple polar chart with several displayers.

  This sample shows how to create a chart using a polar projector. To do so, it
  uses the IlvPolarChart class.

  Note the two different scale types: rectangular for the rho coordinate that
  is displayed radially, and circular for the theta coordinate.

  Two callback functions are used as input data and are rendered with two
  displayers:

    * A polygon representation representing the function y = abs(2*sin(2x)).

    * A bar representation representing the function y = abs(sin(3x)).

  Classes involved:
    - IlvPolarChart
    - IlvCallbackChartFunction
    - IlvPolygonChartDisplayer
    - IlvBarChartDisplayer

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/polar.cpp


Sample: 'xml'
-------------
  Creation of a simple Cartesian chart out of an XML data file.

  This sample shows you how to create a simple chart using the IlvXMLChartData
  class. You can load a new dataset (either dataset_sample.xml or
  dataset_sample2.xml) and try various kind of displayers.

  Classes involved:
    - IlvXMLChartData
    - IlvChartPointSet
    - IlvPolylineChartDisplayer
    - IlvBarChartDisplayer
    - IlvHiLoChartDisplayer
    - IlvHiLoBarChartDisplayer
    - IlvHiLoOpenCloseChartDisplayer

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/xml.cpp
    - data/dataset_sample.xml
    - data/dataset_sample2.xml


Sample: 'xml_date'
------------------
  Creation of a Cartesian chart out of an XML data file defining dates.

  This sample shows you how to extract dates from an XML data file using the
  IlvXMLChartData class.

  Classes involved:
    - IlvXMLChartData
    - IlvChartPointSet
    - IlvPolylineChartDisplayer

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/xml_date.cpp
    - data/dataset_sample_date.xml

