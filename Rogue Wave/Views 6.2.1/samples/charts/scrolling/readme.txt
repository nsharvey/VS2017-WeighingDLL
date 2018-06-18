
                             Rogue Wave Views 6.2
                                Charts Package

                             Samples 'scrolling'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'shiftcar'
------------------
  Demonstration of the automatic shift scroll mode of the charts.

  This sample demonstrates the automatic scrolling feature of the Rogue Wave
  Views Charts package. It creates a Cartesian chart and connects it to several
  data sets. New random data points are added to these data sets at a given
  timer period. You can specify this period, in milliseconds, as the only
  parameter of the command line. For example, to add new points every 100
  milliseconds, run:
  shiftcar 100.

  In the code of this sample, you can specify several other values:

    * The number of data points added by the timer (NbAddedPts).

    * The number of shown data points (NbShownPts).

    * The number of displayers. Each displayer is associated to a data set (NbDisplayers).

  The timer can be suspended by pressing the 's' key, and resumed by pressing
  the 'r' key.

  Classes involved:
    - IlvCartesianChart
    - IlvChartYValueSet
    - IlvPolylineChartDisplayer

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/shiftcar.cpp


Sample: 'shiftpol'
------------------
  Demonstration of the automatic shift scroll mode of the charts.

  This sample demonstrates the automatic scrolling feature of the Rogue Wave
  Views Charts package. This sample is similar to the shiftcar sample, except
  that it uses a polar coordinate system. It creates a polar chart and connects
  it to several data sets. New random data points are added to these data sets
  at a given timer period. You can specify this period, in milliseconds, as the
  only parameter of the command line. For example, to add new points every 100
  milliseconds, run:
  shiftpol 100.

  In the code of this sample, you can specify several other values:

    * The number of data points added by the timer (NbAddedPts).

    * The number of shown data points (NbShownPts).

    * The number of displayers. Each displayer is associated to a data set (NbDisplayers).

  The timer can be suspended by pressing the 's' key, and resumed by pressing
  the 'r' key.

  Classes involved:
    - IlvPolarChart
    - IlvChartPointSet
    - IlvPointInfoMap
    - IlvChartDataPointInfo
    - IlvMarkedPolylineChartDisplayer

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/shiftpol.cpp


Sample: 'cyclic'
----------------
  Demonstration of the automatic cycle scroll mode of the charts.

  This sample demonstrates the cycle scrolling feature of the Rogue Wave Views
  Charts package.

  When new points are added and cannot be displayed on the right side of the
  chart, they are translated to the left side of the chart, where the minimum
  x-value is replaced by the previous maximum x-value. Previous data points are
  therefore dropped. Note how the x-scale values are updated to match the real
  translation. The color of the new markers depends on the actual values they
  represent. You can specify the period of the timer, in milliseconds, as the
  only parameter of the command line. For example, to add new points every 100
  milliseconds, run:
  cyclic 100.

  The timer can be suspended by pressing the 's' key, and resumed by pressing
  the 'r' key.

  Classes involved:
    - IlvCartesianChart
    - IlvChartPointSet
    - IlvPointInfoMap
    - IlvChartDataPointInfo
    - IlvScatterChartDisplayer

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/cyclic.cpp


Sample: 'listener'
------------------
  Synchronization of several data sets using listeners.

  This sample shows you how to synchronize several data sets using listeners.
  This sample simulates the visualization of successive temperature samples. To
  do this, it uses two chart objects:

    * The first one is used to display the actual temperature measures. The
      temperature is rendered with bars whose color depends on the value of the
      temperature (blue for negative values, red for positive values). The
      temperature measures are handled by a data set updated randomly at a
      given period. The example assumes that a measure is carried out every
      hour of the day.

    * The second one is used to display the temperature variations across a
      given period of time (in the case of the example, a day). To do this, it
      is connected to four data sets representing:

      * The lowest temperature during the day.

      * The highest temperature during the day.

      * The temperature at the beginning of the day.

      * The temperature at the end of the day (during the day, the value is set
        to the last measure).

    These four data sets are updated through a listener set on the temperature
    data set. This listener is notified whenever a new measure is available and
    updates the high/low start/end values accordingly. To render these data
    sets, an instance of IlvHiLoOpenCloseChartDisplayer is used. The color of
    the start-end bar depends on whether the temperature at the end of the day
    is greater or lower than the temperature at the beginning of the day.

  Every drawing update (scrolling/invalidation of the variations display) is
  carried out automatically by the chart.

  Classes involved:
    - IlvCartesianChart
    - IlvChartDataSetListener
    - IlvChartYValueSet
    - IlvBarChartDisplayer
    - IlvHiLoOpenCloseChartDisplayer
    - IlvChartLegend

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/listener.cpp

