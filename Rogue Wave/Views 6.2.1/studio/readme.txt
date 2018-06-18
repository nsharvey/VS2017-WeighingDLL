

                       Rogue Wave Views version 6.2.1

                           Studio README File


The complete documentation of Rogue Wave Views Studio is in the
Rogue Wave Views User Manual.

ivfstudio: The Rogue Wave Views Foundation Studio

  Rogue Wave Views Foundation Studio is a customizable and extendable
  WYSIWYG editor. It lets you draw the 2D graphic objects and supports
  the Rogue Wave Script language for Rogue Wave Views.

  Other Rogue Wave Views packages come with their own Studio extensions
  that let you use the additional feature of the package. For example,
  with the Rogue Wave Views Gadgets package, you can use the GUI Application 
  extension to edit your GUI using Rogue Wave Views Gadgets and generate
  the C++ code for the GUI part of your application.

ILVHOME

  Studio needs to access some of the data files that are provided
  with the product (in data and studio/data) To be able to locate
  these files, you have to set the environment variable ILVHOME to
  the directory where the product has been installed.
  For instance
        on Unix platforms :
	           % ILVHOME=/usr/local/roguewave/viewsXY
                   % export ILVHOME
        on Window platforms :
                   > set ILVHOME="C:\Program Files\Rogue Wave\Views X.Y"
  where X and Y indicate the major and minor version numbers of
  Rogue Wave Views.


Using the dynamic libraries

  For most platforms, Rogue Wave Views Studio comes with a dynamically
  linked version of ivfstudio. To run this editor, you have to set,
  if needed, the environment variable(s) so the system can find the
  used libraries.

  Unix platforms:

	ivfstudio is installed in the $ILVHOME/studio/<system> directory.
	You have to set the environment variable LD_LIBRARY_PATH 
	(SHLIB_PATH on hp platforms) to the directory
        
		$ILVHOME/lib/<system>/<shared_subsystem>
	and 	$ILVHOME/studio/<system>/<shared_subsystem>,

	where <system> indicates the name of the platform you are using,
	such as 'ultrasparc32_10_11', 'x64_rhel5.0_4.1', and so on.
	<shared_subsystem> indicates the name of the sub-platform dedicated
	to shared/dynamic libraries on the system that you are using,
	such as 'shared', 'shared_mt', and so on.

  Windows platforms:

	ivfstudio.exe is installed in the %ILVHOME%\studio\<system> directory.
	To run this editor, set the PATH environment variable to
	the following directories:

	%ILVHOME%\lib\<system>\<dll_subsystem>	and
	%ILVHOME%\studio\<system>\<dll_subsystem>
	
	where <system> indicates the name of the platform you are using,
	such as x86_.net2012_11.0 or x64_.net2013_12.0.
	<dll_subsystem>	indicates the name of the sub-platform dedicated to
	dll's on the system that you are using, such as 'dll_mda'.


Loading plug-ins

	A plug-in is a Rogue Wave Views dynamic module which creates a
        Rogue Wave Studio extension. 

  Selecting plug-ins

      The first time

	When you use ivfstudio for the first time,
	ivfstudio prompts you to select the plug-ins it has detected.
	Select the plug-ins you want to load by checking the corresponding
	toggle buttons and click OK. If you click Cancel, ivfstudio starts
	without loading any plug-ins. The plug-ins you use in this session
	will be loaded again next time you launch ivfstudio. 

      -selectPlugIns command line argument

	If you want to select again your plug-ins before ivfstudio starts,
	you can run it with the -selectPlugIns argument.

      SelectPlugIns command

	You can execute the SelectPlugIns command (from the Tools menu,
	choose Select Plug-Ins...) to select plug-ins. In this case, you
	have to exit Studio and launch it again to make it load the
	selected plug-ins.

  Specifying plug-Ins using environment variables

        You can also specify a list of modules to load or a directory
	containing all the modules to load. In this case, the plug-ins
	loaded in the previous session are ignored.

        Before initializing, Studio loads all the extension
        modules contained in a plug-in directory. The plug-in directory
        defaults to <ILVHOME>/studio/plugins. If you want to put your
        plug-ins in another directory, you can use the ILVSTPLUGINSDIR
        environment variable to indicate that directory. After loading
        the modules found in that plug-in directory, Studio looks for
        a subdirectory named <system>.

        You can use the ILVSTPLUGINS environment variable to indicate
        a list of modules you want to load. You can specify the full
        paths or the paths relative to the working directory, 
        separated by a ';' character. 


Some common plug-ins

        Some Rogue Wave Views modules come with their own plug-ins for
        Rogue Wave Views Studio. For more information, see the documentation
        of the Rogue Wave Views modules you use. Following is a list of some
        common plug-ins, located in the <ILVHOME>/studio/<system>/<subsystem> 
        directory:

        - If you have the Rogue Wave Views Gadgets module, you can use 
        the Studio GUI Application plug-in to edit and generate 
        GUI applications with gadgets panels. The corresponding 
        dynamic module is libsmguiapp.<ext>, where <ext> is .so, 
        .sl, and so on, according to your platform.

        - If you have the Rogue Wave Views Grapher module, you can use 
        the Studio Grapher plug-in to edit your graphers, nodes and links. 
        The corresponding dynamic module is libsmgrapher.<ext>, 
        where <ext> is .so, .sl, and so on, according to your platform.


Required packages

       ivfstudio can be used with the Rogue Wave Views Foundation product. 

       However, you need the Gadgets and Manager packages to build any
       version of Rogue Wave Views Studio.


ivstudio: The Rogue Wave Views GUI editor.
        
        ivstudio is a version of Studio which includes the Application and 
        Grapher plug-ins.

        With ivstudio, you can build graphic user interfaces using
        Rogue Wave Views gadgets. It lets you interactively edit your panels
        and generate C++ application code which recreates these panels. 

        This editor is not part of the distribution. To compile it,
        go to your specific platform directory, and use the 'make' utility
        to build the executable.

                % cd <ILVHOME>/studio/<system>/<subsystem>
                % make (or nmake) ivstudio

Note for Windows users: Studio and ActiveX support
-----------------------

Rogue Wave Views Foundation Studio can convert a panel and all the
graphic objects it contains as a standalone ActiveX that can be
inserted in a Visual Basic application, or any other ActiveX-aware
Windows application.
This feature is available only for the 'dll_mda' version of Rogue Wave Views 
Studio, which is the one that is provided by default with all Rogue Wave Views
distributions.

  - Setup

     To set up Rogue Wave Studio for ActiveX support, do the following:

     1- Your environment variable PATH must point to directories where 
        Rogue Wave Views libraries can be found. A simple way to ensure
        this is to add both %ILVHOME%\lib\<system>\dll_mda and
        %ILVHOME%\studio\<system>\dll_mda (where ILVHOME indicates the
        drive and directory where you installed Rogue Wave Views) to the
        PATH environment variable.

     2- A Rogue Wave Views OLE server must be registered in your
        system. This server is provided at the following location:
                %ILVHOME%\lib\<system>\dll_mda\ilvactivex.dll
        To register this server, you must enter the following line in
        a command prompt:
                regsvr32 %ILVHOME%\lib\<system>\dll_mda\ilvactivex.dll
        The application called 'regsvr32' is provided by Microsoft
        with the regular Windows distribution and should be located
        in the 'system' or 'system32' directory of your main Windows
        directory.

     3- Studio must be able to locate the ActiveX plugin that is
        distributed with Rogue Wave Views. By default, when using ivfstudio
	on <system>\dll_mda for the first time, you are asked to select
	the plug-ins you want to load. If you want to explicitly
	declare this plug-in, as described in the section
	'Loading Plug-Ins' above, you can copy the file:
                %ILVHOME%\studio\<system>\dll_mda\ilvstdynact.dll
        to %ILVHOME%\studio\plugins, or add the full pathname of this
        file to the environment variable ILVSTPLUGINS.

  - Using the ActiveX plug-in
     Here are the steps to follow in order to generate an ActiveX for
     a Rogue Wave Views data file.

     1- Run ivfstudio.exe.
        In the main menu bar, a new item labeled "ActiveX" should be
        available. If this is not the case, please exit Studio, and
        check your environment variables as described in the 'Setup'
        section above.

     2- Create or load a Studio buffer. Select this buffer so that it
        is the active buffer.

     3- Click the "SaveAsActiveX" item in the "File" menu. A popup dialog
        will prompt you for a name and a location of the generated
        ActiveX. Choose a name for the ActiveX (the ".dll" extension
        will automatically be added), and press the "OK" button.
        Note: you may be requested to choose between a version using
        the container or a version using the manager before the dialog
        asking for the name of the ActiveX.

     4- If an error occurs at this point, it is likely to be due to
        one of the following:
          *  Wrong setting of your environment variables,
          *  The Rogue Wave Views ActiveX server 'ilvactivex.dll' has not been
             registered
          * One library that this ActiveX depends on could not be found.
            This library could be:
              - Any Rogue Wave Views library
              - cgeneric.dll for the container based version
              - mgeneric.dll for the manager based version
            All these libraries are originally located in
            %ILVHOME%\lib\<system>\dll_mda.
