
		Rogue Wave Views - Version 6.2.1
		    (March 2018)

		        README File

Migration from previous releases
--------------------------------
All known incompatibilities of this version of Rogue Wave Views with
previous versions are described in the file "COMPAT.TXT".
Please read it if you have any problems migrating your existing applications.

Getting assistance
------------------
If you have problems using the Rogue Wave Views libraries please contact
Rogue Wave customer support at support@roguewave.com. Information may be
found in the product documentation.

Legal information
-----------------
The directory "license" contains the following files:
    - Software License Agreement; "license_agreement"
      (plain text and PDF versions)
    - Notices for third-party software; "notices"

Some directories containing images (both bitmap and vectorial) may also
contain a file called notices.txt indicating, when it is relevant, the
license information for these images.

The use of ILM (ex-ILOG License Manager), related files (access.ilm) and API,
is deprecated since Views 5.4.

Documentation
-------------
If you have installed the Rogue Wave Views documentation set, you can
directly access it by loading these files in a web browser:
    - "doc/html/views.html" (English version)
    - "doc/html_ja/views.html" (Japanese version)

The documentation is also available online at
"http://www.roguewave.com/support/product-documentation.aspx"

Compilation
-----------
Rogue Wave Views is delivered with a set of libraries that are stored 
in a directory that depends on the type of machine you are using, the
operating system it runs on, and the compiler you plan to use.
This directory can be one of:

      hp32_11_3.73           Machine:  HP 9700
                             OS:       HP-UX 11.11 or higher
                             Compiler: HP ANSI C++ A.03.73 or higher
                                       using -mt -AA options

      hp64_11_3.73           Machine:  HP 9700
                             OS:       HP-UX 11.11 or higher
                             Compiler: HP ANSI C++ A.03.73 or higher
                                       in 64bit mode (+DA2.0W)
                                       using -mt -AA options

      ia64_hpux11_6.17       Machine:  ia64 (Itanium 2)
                             OS:       HP-UX 11.11 or higher
                             Compiler: HP ANSI C++ A.06.17 or higher
                                       in 64bit mode (+DD64)

      ia64-32_hpux11_6.17    Machine:  ia64 (Itanium 2)
                             OS:       HP-UX 11.11 or higher
                             Compiler: HP ANSI C++ A.06.17 or higher
                                       in 32bit mode

      x86_sles10.0_4.1       Machine:  x86
                             OS:       SUSE Linux Enterprise Server 10
                                       (linux 2.6, glibc 2.4)
                             Compiler: gcc4.1
                             OS:       SUSE Linux Enterprise Server 11
                                       (linux 2.6, glibc 2.11)
                             Compiler: gcc4.3
                             OS:       SUSE Linux Enterprise Server 12
                                       (linux 3.12, glibc 2.19)
                             Compiler: gcc4.8

      x64_sles10.0_4.1       Machine:  x64 (x86-64)
                             OS:       SUSE Linux Enterprise Server 10
                                       (linux 2.6, glibc 2.4)
                             Compiler: gcc4.1
                             OS:       SUSE Linux Enterprise Server 11
                                       (linux 2.6, glibc 2.11)
                             Compiler: gcc4.3
                             OS:       SUSE Linux Enterprise Server 12
                                       (linux 3.12, glibc 2.19)
                             Compiler: gcc4.8

      x86_rhel5.0_4.1        Machine:  x86
                             OS:       RedHat Enterprise Linux 5.0
                                       (linux 2.6, glibc 2.5)
                             Compiler: gcc4.1
                             OS:       RedHat Enterprise Linux 6.0
                                       (linux 2.6, glibc 2.12)
                             Compiler: gcc4.4
                             OS:       RedHat Enterprise Linux 7.2
                                       (linux 3.10, glibc 2.17)
                             Compiler: gcc4.8

      x64_rhel5.0_4.1        Machine:  x64 (x86-64)
                             OS:       RedHat Enterprise Linux 5.0
                                       (linux 2.6, glibc 2.5)
                             Compiler: gcc4.1
                             OS:       RedHat Enterprise Linux 6.0
                                       (linux 2.6, glibc 2.12)
                             Compiler: gcc4.4
                             OS:       RedHat Enterprise Linux 7.2
                                       (linux 3.10, glibc 2.17)
                             Compiler: gcc4.8

      x86_.net2010_10.0      Machine:  x86
                             OS:       Windows 7, Server 2003/2008/2012
                             Compiler: Microsoft Visual C++ .NET 2010

      x64_.net2010_10.0      Machine:  x64 (x86-64)
                             OS:       x64 Windows 7, Server 2003/2008/2012
                             Compiler: Microsoft Visual C++ .NET 2010

      x86_.net2012_11.0      Machine:  x86
                             OS:       Windows 7/8, Server 2003/2008/2012
                             Compiler: Microsoft Visual C++ .NET 2012

      x64_.net2012_11.0      Machine:  x64 (x86-64)
                             OS:       x64 Windows 7/8, Server 2003/2008/2012
                             Compiler: Microsoft Visual C++ .NET 2012

      x86_.net2013_12.0      Machine:  x86
                             OS:       Windows 7/8, Server 2003/2008/2012
                             Compiler: Microsoft Visual C++ .NET 2013

      x64_.net2013_12.0      Machine:  x64 (x86-64)
                             OS:       x64 Windows 7/8, Server 2003/2008/2012
                             Compiler: Microsoft Visual C++ .NET 2013

      x86_.net2015_14.0      Machine:  x86
                             OS:       Windows 7/8/10, Server 2003/2008/2012
                             Compiler: Microsoft Visual C++ .NET 2015

      x64_.net2015_14.0      Machine:  x64 (x86-64)
                             OS:       x64 Windows 7/8/10 Server 2003/2008/2012
                             Compiler: Microsoft Visual C++ .NET 2015

      x86_.net2017_15.0      Machine:  x86
                             OS:       Windows 7/8/10, Server 2003/2008/2012
                             Compiler: Microsoft Visual C++ .NET 2017

      x64_.net2017_15.0      Machine:  x64 (x86-64)
                             OS:       x64 Windows 7/8/10 Server 2003/2008/2012
                             Compiler: Microsoft Visual C++ .NET 2017

      power32_aix6.1_10.1    Machine:  PowerPC
                             OS:       AIX 6.1 or higher
                             Compiler: Visual Age 10.1

      power64_aix6.1_10.1    Machine:  PowerPC
                             OS:       AIX 6.1 or higher
                             Compiler: Visual Age 10.1 in 64bit mode
                                       (-q64)

      ultrasparc32_10_11     Machine:  Sun Ultra Sparc
                             OS:       Solaris 2.10 or higher
                             Compiler: SunStudio 11

      ultrasparc64_10_11     Machine:  Sun Ultra Sparc
                             OS:       Solaris 2.10 or higher
                             Compiler: SunStudio 11 in 64bit mode
                                       (-xtarget=ultra -xarch=v9)

      x86_solaris10_11       Machine:  x86
                             OS:       Solaris 2.10 or higher
                             Compiler: SunStudio 11

      x64_solaris10_11       Machine:  x64 (x86-64)
                             OS:       Solaris 2.10 or higher
                             Compiler: SunStudio 11 in 64bit mode
                                       (-xarch=adm64)


It will be referred to as <system> in the following text.


You may need to change the provided makefiles to match your
own installation requirements:
    - VIEWSDIR must be set to the directory where you unpacked
      the product (usually /usr/local/roguewave/viewsXY on Unix or
      C:\Program Files\Rogue Wave\Views X.Y on Windows, where X.Y
      indicates the current version of Rogue Wave Views);
    - XINC and XLIBS should be set to the directory where your
      X11 include and lib directories are located
      (only on Unix platforms);
    - MINC and MLIBS should be set to the directory where your 
      Motif include and lib directories are located
      (only on Unix platforms);

Platforms no longer supported
-----------------------------
    <no deprecated platform in this version>

Execution requirements
----------------------
You need to set the environment variable ILVHOME to the directory where the
product has been installed to ensure that every provided binary works
properly. Usually, you will set:

(csh/tcsh):
        % setenv ILVHOME /usr/local/roguewave/viewsXY
(sh/bash):
        $ ILVHOME=/usr/local/roguewave/viewsXY
        $ export ILVHOME
(Windows platforms)
        C:\> set ILVHOME=C:\Program Files\Rogue Wave\Views X.Y

Please check with your system administrator the exact location where
Rogue Wave Views is installed.

Library build information (Unix platforms only)
-------------------------
If a problem occurs while running your applications, you can retrieve the
information on the platform that was used to build the library by using the 
shell script called ilvversion.sh, located in the Rogue Wave Views root
directory.

Go into the specific static subplatform subdirectory of 'lib', and type:
        ../../../ilvversion.sh

Two lines that have the following form will be printed out (these lines may
be swapped):

        IlvVersion: X.Y
        IlvBuild: OS - platform - compiler - display revision

The shell script just locates the strings 'IlvBuild' and 'IlvVersion' in the
library file libxviews.a, and prints out the result.

If you have installed multiple platforms in the directory ILVHOME, you can
check each of the platforms:
        $ cd $ILVHOME
        $ ./ilvversion.sh platform
where platform is the system identifier of the Rogue Wave Views library (that
is, the <system>, one of hp32_11_3.73, power32_aix6.1_10.1 ...). 


Contents
--------
Rogue Wave Views Studio:
    a GUI builder that will help you create and generate Rogue Wave Views
    applications.
      -  On Unix platforms, the executable file is called ivfstudio and is
         located in the directory studio/<system>.
      -  On Windows platforms, the executable file is called
         ivfstudio_<system>.exe and is located in the directory
         studio\<system>\dll_mda.

Directories:
    data/ilviews: Contains the data files used by the library (inspector
                  panels, message databases, and so on).
    data/images: Contains image data files.
    data/icon: Contains some icons.
    data/DCW: Contains some DCW-generated files.

    bin: Contains binary files, along with source code.
            The README file in the bin directory explains how to
            build these binary files.
            Two useful programs can be built in <ILVHOME>/bin/<system>:
                    ilv2data, which can build a "resource file" that
                            can be linked with your application in
                            order to make it environment-independent.
                    splitdbm, which converts pre-3.0 message databases
                            into the new format, including the new
                            language definition, and encoding.

    samples: Contains sample files.
            For each sample, you need to go to the platform directory
            and run the make utility to build it.

    tools: Contains more specific solutions to common problems.


Various versions
----------------
The libraries are stored in subdirectories of the directory
lib/<system>.

There are several library files (static and shared equivalent):

   Unix platforms:
        libxviews: Pure Xlib code of Rogue Wave Views.
        libmviews: Motif-dependent code of Rogue Wave Views.

   Windows platforms:
        winviews.lib: Windows-dependent code of Rogue Wave Views.

   For all platforms (the name should be prefixed with 'lib' on Unix
   platforms, and have the '.lib' extension on Windows platforms):

    Library name            |                               Description
    ------------------------+---------------------------------------------
    Foundation Package
    ilog                    | Rogue Wave utility classes: arrays, lists, ...
    views                   | Core library. Includes Standard 2D graphics.
    ilvgadgt                | Core Gadgets Library.
                            | This library is provided with the
                            | Foundation Package, but can be used and
                            | deployed only if you have the 
                            | "Rogue Wave Views" or "Rogue Wave Views Controls"
                            | license. 
                            | This library contains the following classes:
                            |     IlvMessageLabel, IlvFrame,
                            |     IlvButton, IlvToggle,
                            |     IlvColoredToggle, IlvComboBox,
                            |     IlvTextField, IlvNumberField,
                            |     IlvPasswordField, IlvPopupMenu,
                            |     IlvToolBar, IlvMenuBar,
                            |     IlvScrollBar, IlvSlider,
                            |     IlvGadgetItem, IlvMenuItem,
                            |     IlvGadgetContainer,
                            |     IlvScrolledView, IlvDialog,
                            |     IlvIMessageDialog,
                            |     IlvIInformationDialog,
                            |     IlvIErrorDialog, IlvIWarner,
                            |     IlvIQuestionDialog,
                            |     IlvGadgetContainerRectangle,
                            |     IlvSCGadgetContainerRectangle,
                            |     and IlvSCViewRectangle.
    ilvcss                  | Base classes for CSS styling. Used by gadgets.
    ilvvxlook               | Views X (VX) Look and Feel Library.
    ilvmlook                | Motif Look and Feel Library.
    ilvwlook                | Windows 3.11 Look and Feel Library.
    ilvw95look              | Windows 95 Look and Feel Library.
    ilvwxplook              | Windows XP Look and Feel Library
                            | (Windows only). 
    ilvprint                | Printing support Library.
    ilvbmpflt               | Bitmap Filters Library.
    ilvbmp                  | BMP bitmap streamer.
    ilvwbmp                 | WBMP bitmap streamer.
    ilvpng                  | PNG bitmap streamer.
    ilvjpg                  | JPG bitmap streamer.
    ilvppm                  | PBM-PPM bitmap streamer.
    ilvtiff                 | TIFF bitmap streamer.
    ilvrgb                  | SGI RGB bitmap streamer.
    iljs                    | Rogue Wave Script library.
    ilvjs                   | Rogue Wave Views Script implementation.
    iljsgide                | Rogue Wave Script debugger interface.
    ilvbuild                | Resource-handling classes for binaries.
    ------------------------+---------------------------------------------
    Gadgets Package (Controls)
    ilvadvgdt               | Advanced Gadgets Library (IlvMatrix,
                            |   IlvTreeGadget, ...).
    ilvadvgadmgr            | Manager classes using advanced gadgets.
    ilvatext                | IlvAnnotext and related classes.
    ilvedit                 | Inspector classes (Color chooser,
                            |   Font chooser, ...).
    ilvstates               | States Library.
    ilvavxlook              | Advanced Views X (VX) Look and Feel Library.
    ilvamlook               | Advanced Motif Look and Feel Library.
    ilvawlook               | Advanced Windows 3.11 Look and Feel Library.
    ilvaw95look             | Advanced Windows 95 Look and Feel Library.
    ilvawxplook             | Advanced Windows XP Look and Feel Library
                            | (Windows only).
    ilvprtdlg               | Printing dialogs Library.
    ------------------------+---------------------------------------------
    Application Framework Package (Controls)
    ilvappframe             | Application Framework Library.
    ilvappmgr               | Application Framework classes using
                            |   the Manager package
                            | (IlvDvManagerDocument, ...).
    ilvappgrapher           | Application Framework classes using
                            |   the Grapher package
                            | (IlvDvGrapherDocument, ...).
    ilvappwizard            | Application Framework Library for dvwizard.
    ------------------------+---------------------------------------------
    Manager Package (2D Standard)
    ilvmgr                  | Manager Library (IlvManager and
                            |   related classes).
    ilvgadmgr               | Manager classes using gadgets
                            |   (IlvGadgetManager, ...).
    ilvmgrprint             | Manager Printing support Library.
    ------------------------+---------------------------------------------
    Grapher Package (Advanced 2D)
    ilvgrapher              | Grapher Library (IlvGrapher and
                            |   related classes).
    ilvgadgraph             | Grapher classes using gadgets
                            |   (IlvSCGrapherRectangle).
    ------------------------+---------------------------------------------
    Prototypes Package (Advanced 2D)
    ilvproto                | Prototypes Base Library.
    ilvgdpro                | Compatibility Prototype classes.
    ------------------------+---------------------------------------------
    Data Access Add-On
    dataccess               | Core Data Access libraries (was
                            |   'inform' in Rogue Wave InForm 3.0).
    dbaccess                | Relational databases libraries (was
                            |   'dbinform' in Rogue Wave InForm 3.0).
    dbchart                 | Charts-based Data Access classes library.
    dbgadget                | Gadgets-based Data Access classes
                            |   library.
    dbgantt                 | Gantt Chart-based Data Access
                            |   classes library.
    dbgraphe                | Grapher-based Data Access classes library.
    dbsqlgad                | Relational Databases Gadgets classes
                            |  library.
    ------------------------+---------------------------------------------
    Charts Add-On
    ilvcharts               | Charts Library (IlvChartGraphic and
                            |   related classes).
    ------------------------+---------------------------------------------
    Graph Layout Add-On
    ilvlayout               | Core Graph Layout library.
    ilvbus                  | Bus layout library.
    ilvhierarchical         | Hierarchical layout library.
    ilvorthlink             | Orthogonal Link layout.
    ilvrandom               | Random layout library.
    ilvtree                 | Tree layout library.
    ------------------------+---------------------------------------------
    Gantt Add-On
    ilvgantt                | Gantt Chart Library (IlvGanttChart
                            |   and related classes).
    ------------------------+---------------------------------------------
    Maps Add-On
    ilvmaps                 | Core Maps Library.
    ilvdbmaps               | Database-based maps library.
    ------------------------+---------------------------------------------

Using shared libraries
----------------------
    Rogue Wave Views libraries are provided in both static and shared
    mode on all platforms (please see the next section for Unix users
    and Motif-based libraries).

    If you use shared libraries on a Unix platform, make sure the
    dynamic loader can find the Rogue Wave Views libraries. You do that
    by setting the environment variable LD_LIBRARY_PATH
    (or SHLIB_PATH on HP platforms or LIBPATH on AIX platforms)
    to $ILVHOME/lib/<system>/<shareDir>.
    To run Rogue Wave Views Studio (ivfstudio), you must also add
    $ILVHOME/studio/<system>/<shareDir> directory to this library path.

    If you use shared libraries on a Windows platform, make sure
    that the system will actually access the Rogue Wave Views
    DLLs. Check the system documentation for more information.

Note for Unix users
-------------------
    On Unix platforms, when you plan to link your application with
    Rogue Wave Views, you have to decide whether or not it will include pure
    Motif code. If this is the case, you need to link with libmviews.
    If you need your application to be a pure Xlib application, you
    need to link with libxviews.
    Never link with both, and always link with one of these two.
    The library "views" is likely to be necessary for every application.

    Important note about Motif and shared libraries
    -----------------------------------------------
        The use of libmviews (Motif based) is deprecated in shared
        library format.
        Since version 4.0, all shared libraries provided by Rogue Wave Views
        are built using libxviews and are incompatible with libmviews.
        libmviews is only provided as a static library and can only
        be used with the static version of other Rogue Wave Views libraries.

Note for Windows users
----------------------
    On Windows, Rogue Wave Views libraries are provided in several formats
    due to different versions of the run-time system libraries.
    Each format has its own subdirectory in lib\<system>\<format>.
    Each format needs specific compiler flags as described below:

        stat_mta: Static library in multithread with static run-time
                  library using new IOStreams.
                 Flags: /EHsc /GR /MT (Multithreaded).
        stat_mda: Static library in multithread with dynamic run-time
                  library using new IOStreams.
                 Flags: /EHsc /GR /MD (Multithreaded  DLL).
        dll_mda:  Dynamic library in multithread with dynamic run-time
                  library using new IOStreams.
                 Flags: /EHsc /GR /MD /DILVDLL (Multithreaded DLL).

     Note: You must link with the system libraries wsock32.lib and imm32.lib.

     Note: You must also use the compilation flag /DILJSTDH if you want to
     use Rogue Wave Script in these modes.

Note for Microsoft Visual C++ users
-----------------------------------
  - For all your projects, make sure that wsock32.lib and imm32.lib are
    specified in the link command line.

  - To debug your program more easily, add the following lines to the
    section [AutoExpand] of the file
          %INSTALLDIR%\Common7\Packages\Debugger\autoexp.dat

    ; from Rogue Wave Views
    IlvRect=x=<_orig._x,d> y=<_orig._y,d> width=<_w,u> height=<_h,u>
    IlvPoint=x=<_x,d> y=<_y,d>
    IlvFloatRect=x1=<_x1,f> y1=<_y1,f> x2=<_x2,f> y2=<_y2,f>
    IlvFloatPoint=x=<_x,f> y=<_y,f>
    IlvTransformer=x11=<_x11,g> x12=<_x12,g> x21=<_x21,g> x22=<_x22,g> x0=<_x0,g> y0=<_y0,g>

    These lines let you visualize the values of the objects that these
    classes define (instead of their address) in the tooltip that appears
    when the mouse is positioned over a variable.

  - You may get a series of link errors when using the Visual C++
    integrated development environments to build your project in
    Debug mode.
    In Debug mode, to be able to link your application with Visual C++ and
    the libraries provided in Rogue Wave Views, follow these instructions:
        -  In Microsoft Visual Studio, select your projects
           in the Solution Explorer window
        -  right-click on the selection and choose the Properties item
        -  In the Property Pages window, select
              Configuration Properties -> C/C++ -> Preprocessor
        -  In the Preprocessor Definitions field, remove _DEBUG
        -   Recompile and relink the application.
