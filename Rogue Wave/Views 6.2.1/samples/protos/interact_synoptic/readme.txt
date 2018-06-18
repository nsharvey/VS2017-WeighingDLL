
                             Rogue Wave Views 6.2
                              Prototypes Package

                         Samples 'interact_synoptic'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'Synoptic with Dynamically-Created Interactive Objects'
---------------------------------------------------------------
  Shows how to link a prototype to some application objects.

  Here the program uses the IlvProtoMediator to create multiple instances of
  'flight' prototypes. Each of these instances is synchronized to a
  corresponding 'Flight' in the air traffic simulator. The file
  data/easy_atc.cpp describes the airport and traffic schedule of the
  simulation. The basic prototypes given display only speed and direction of
  the planes. However, one can add controls onto the prototypes (using
  callbacks or event accessors) to enable the user to edit interactively the
  attributes of the flight, for example, speed, direction or altitude.

  Classes involved:
    - IlvGroupHolder
    - IlvGroup
    - IlvProtoMediator

  Source files:
    - src/plane.cpp
    - src/atc.cpp
    - include/atc.h
    - data/atc.ipl
    - data/easy_atc.txt

