	               Rogue Wave Views version 6.2.1

			tools/htmlview README File

This directory contains a Views-based implementation of
an Hyper Text object, called IlvAnnoText.

The code for this object is provided in a new
library called ilvatext.

This library contains an HTML parser that is one
of the possible HyperText format that can be connected
to IlvAnnoText.
Its code is provided in src/html.cc

An HTML reader is provided as an example of how to use this
object in the samples directory. It is called htmlview.
More information on this sample can be found in the User Guide.

The Rogue Wave Views Reference Manual completely describes
the classes used in the IlvAnnoText gadget.

---------------------------------------------------------------
Last minute addition:

Optional arguments to help browse the files of a local WWW server:
-----------------------------------------------------------------

Suppose you set up an HTML server with the name http::/www.foo.bar/ with
the root directory /nfs/one/two/three. In the html files of this server,
you may have addresses written as "/mydir/myfile.html", or 
"http://www.foo.bar/mydir/myfile.html", which refer to the file
/nfs/one/two/three/mydir/myfile.html

To allow the automatic transformation of 
"/mydir/myfile.html" and "http::/www.foo.bar/mydir/myfile.html" 
into /nfs/one/two/three/mydir/myfile.html,
two optional parameters can be provided to the 'htmlview' command:

  -server httpname     declares httpname as the http address of the server

  -path   rootdirname  declares rootdirname as the root directory of the server

In our example, you would enter the command :

htmlview -server http://www.foo.bar/ -path /nfs/one/two/three/

Optional verbose argument:
-------------------------

The optional argument -v causes htmlview to display warnings when encountering
difficult situations (unknown tags or special characters, tags not properly
nested, etc).
