        Rogue Wave Views wizard for Microsoft Visual Studio 15 README file


VSWizard.x86_.net2017_15.0 is a Visual Studio 15 wizard allowing you
to quickly create Rogue Wave Views projects in any library format and with
the correct settings corresponding to both Debug and Release
configurations, for the Microsoft Visual Studio 15, 32 bits compiler.

The wizard can create four types of project:
1) An empty project (no file is added).
2) A gadget container project, where the main file creates and shows an empty 
gadget container.
3) A manager project, where the main file shows a panel made of a view 
connected to a manager.
4) A grapher project, where the main file shows a panel made of a view
connected to a grapher.

Each page of the wizard allows you to select settings for your project such as
the library format, the libraries you want to link with your project and so on.
The current settings are summarized on the Overview page.

How to install the wizard:
~~~~~~~~~~~~~~~~~~~~~~~~~~
In order to use it, you must:
1. Copy the files
       - RWViews.VSWizard.x86_.net2017_15.0.ico
       - RWViews.VSWizard.x86_.net2017_15.0.vsz
       - RWViews.VSWizard.x86_.net2017_15.0.vsdir
   to the directory
   <Program Files>\Microsoft Visual Studio\2017\<Edition>\Common7\IDE\VC\vcprojects.
2. Edit the copied RWViews.VSWizard.x86_.net2017_15.0.vsz file and set the
   value of the ABSOLUTE_PATH parameter to the absolute path for the
   VSWizard.x86_.net2017_15.0 directory. Typically, it will be
      C:\Program Files\Rogue Wave\Views M.m\tools\VSWizard.x86_.net2017_15.0

How to use the wizard:
~~~~~~~~~~~~~~~~~~~~~~
Once you installed the wizard, just create a new project.
In the list of all possible C++ projects, you will see a new item
called "Rogue Wave Views Application".
Select this project type and proceed as usual (give your project a
name and a directory and click OK).
Customize your project by selecting the settings you want.
Click Finish to create your project.

How to customize the wizard:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
You can customize the wizard by adding parameters in the 
RWViews.VSWizard.x86_.net2017_15.0.vsz file.

+ The default value of the ILVHOME environment variable is set to $(ILVHOME).
You can specify another default value by adding the following line to the
RWViews.VSWizard.x86_.net2017_15.0.vsz file:
Param="ILVHOME = <myILVHOMEpath>"
where <myILVHOMEpath> corresponds to the path to the Rogue Wave Views directory,
usually C:\Program Files\Rogue Wave\Views M.m.
