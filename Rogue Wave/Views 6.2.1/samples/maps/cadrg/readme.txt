
                             Rogue Wave Views 6.2
                                 Maps Package

                               Samples 'cadrg'


To compile the programs, go to the directory <system>, and run the 'make'
utility provided on your system.
Some ports are provided with compiler-specific project files.
Run the samples from the <system> directory.

Sample: 'cadrgview'
-------------------
  CADRG Viewer with Load-On-Demand implementation.

  This CADRG Viewer shows the Load-On-Demand implementation for the CADRG
  format in Rogue Wave Views Maps.


  Running the Sample
  ------------------

  To run the sample, you must have a CADRG database. Sample data can be
  retrieved from the US National Imagery and Mapping Agency (NIMA) web site,
  using the Geospatial Engine. You can use this search engine to retrieve CADRG
  data from many places in the world (the JOG-A products are in CADRG format).
  If you download the CADRG files at this URL, make sure that you download the
  three coverages (scale 1:1M, scale 1:250K, scale 1:50K) and that you expand
  the archive in the same directory.
  When you launch the sample, you must specify a table of content file as
  parameter. This file is named A.TOC and is placed in the main directory of a
  CADRG database, which is called rpf.
  You can select three coverages of different scale (from the smaller scale to
  the higher one).
  This viewer lets you see various ungeoreferenced frames of the CADRG
  database, such as the boundaries of the CADRG base and the legends of the
  various maps.


  About the CADRG Format
  ----------------------

  The CADRG format (Compressed ARC Digitized Raster Graphics) is a map format
  for raster data published by the US National Imagery and Mapping
  Agency(NIMA).

  The specifications of the CADRG format are public, and can be downloaded from
  the following URL: http://earth-info.nga.mil/publications/specs
  Full samples of CADRG databases can be downloaded from the Geospatial Engine.

  Basically, a CADRG database covers an area with scanned maps of various
  scales. It is composed of a main directory that includes a table of contents
  file, called A.TOC, which can be read with an IlvCADRGTocReader. This main
  directory is divided into subdirectories, each one corresponding to a
  specific coverage. These subdirectories contain the CADRG frames that make up
  the coverage. These frames can be read with an IlvCADRGFrameReader.
  To automatically read a CADRG coverage using the Rogue Wave Views
  load-on-demand mechanism, you can use an IlvCADRGLayer.

  Classes involved:
    - IlvCADRGLayer
    - IlvCADRGFrameReader

  Source files:
    - src/covchoose.cpp
    - src/viewer.cpp
    - src/main.cpp
    - include/covchoose.h
    - include/viewer.h

