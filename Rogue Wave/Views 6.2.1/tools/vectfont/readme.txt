	               Rogue Wave Views version 6.2.1

			tools/vectfont README File

This directory contains the needed source files to use vectorial fonts
in Rogue Wave Views. This tool builds both a library and a sample program that
uses this library. As the sample program is a small editor that uses the
IlvManager class, you need to have the Rogue Wave Views Package 'Manager'
installed on your computer to be able to compile and run the sample.

Vectorial fonts are implemented using Hershey fonts on Unix platforms,
and True Type fonts on Windows platforms.

--------------------------------------------------------------------------
Here are the basic classes that are used in this tool:

vect.h:
-------
IlvVectCharDesc:
	Describes a character
		(virtual draw, boundingBox, contains, intersects)

IlvStrokeCharDesc (: public IlvVectCharDesc):
	Has a list of x-y pairs

IlvVirtualVectFont:
	Virtual description of a vectorial font
	Contains an array of 256 IlvVectCharDesc*

IlvVectFont:
	Actual description of a vectorial font
	Owns a pointer to an IlvVirtualVectFont and
	the sizing parameters.

vectlab.h
---------
IlvVectLabel (: public IlvSimpleGraphic):
	Contains a IlvVectFont field
		(drawString, boundingBox, contains, intersects)
--------------------------------------------------------------------------
