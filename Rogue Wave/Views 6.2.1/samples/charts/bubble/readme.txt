
                             Rogue Wave Views 6.2
                                Charts Package

                               Samples 'bubble'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'bubble'
----------------
  Shows how to use a bubble displayer.

  This sample shows you how to display data with a bubble displayer. Three data
  sets are displayed by the two charts of this sample:

    * inputSet, which represents the original input data.

    * logSet, which is used to log the maximal value of each data in inputSet
      across the last 20 measures.

    * avgSet, which holds the average value of each data in inputSet across all
      measures.

  Both logSet and avgSet are updated by a listener positioned on inputSet.

  The bottom-most chart is used to display inputSet (bar displayer) and logSet
  (step displayer). The steps are annotated with an instance of the
  IlvChartDataPointLabel class that displays the values of logSet.

  The top-most chart uses a Bubble Displayer connected to the following data
  sets:

    * logSet, which gives the y value of the bubble.

    * avgSet, which gives the size of the bubble.

  The visual effect rendered by the displayer is that the longer a bubble stays
  at a high y value, the bigger its size is. The bubbles are annotated with the
  values of avgSet.

  The following interactions are available:

    *  Pressing the 'b' key changes the graphic representation of the bubbles.

    *  A timer is launched at the beginning of the program to simulate the
      measures stored in inputSet. You can suspend it with the 's' key, and
      resume it with the 'r' key.

    *  Pressing the space bar changes the orientation of the Cartesian
      projector of the two charts.

  Classes involved:
    - IlvCartesianChart
    - IlvPointInfoArray
    - IlvChartDataPointlabel
    - IlvBubbleChartDisplayer
    - IlvBarChartDisplayer
    - IlvFixedStepChartDisplayer

  Source files:
    - ../include/samputil.h
    - ../src/samputil.cpp
    - src/bubble.cpp

