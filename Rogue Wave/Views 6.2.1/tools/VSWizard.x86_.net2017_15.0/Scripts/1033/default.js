function OnFinish(selProj, selObj)
{
    try {
	var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
	var strProjectName = wizard.FindSymbol('PROJECT_NAME');

	selProj = CreateProject(strProjectName, strProjectPath);
	AddConfig(selProj, strProjectName);
	AddFilters(selProj);

	var InfFile = CreateInfFile();
	AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
	PchSettings(selProj);
	InfFile.Delete();
	
	selProj.Object.Save();
    }
    catch(e) {
	if (e.description.length != 0)
	    SetErrorInfo(e);
	return e.number
    }
}

function AddFilters(proj)
{
    try {
	// Add the folders to your project
	var strSrcFilter = wizard.FindSymbol('SOURCE_FILTER');
	var group = proj.Object.AddFilter('Source Files');
	group.Filter = strSrcFilter;
    }
    catch(e) {
	throw e;
    }
}

function AddConfig(proj, strProjectName)
{
    try {
	// Add common config
	AddCommonConfig(proj, strProjectName);

	// Add specific config
	// Get the symbols
	var strILVHOME = wizard.FindSymbol('ILVHOME');
	if (!strILVHOME) {
	    strILVHOME = "C:\\Program Files (x86)\\Rogue Wave\\Views 6.2.1";
	}
	if (strILVHOME.charAt(strILVHOME.length -1) != "\\") {
	    strILVHOME += "\\";
	}
	var strIFCHOME = wizard.FindSymbol('IFCHOME');
	if (strIFCHOME) {
	    if (strIFCHOME.charAt(strIFCHOME.length -1) != "\\") {
		strIFCHOME += "\\";
	    }
	}
	var use_stat_mta = wizard.FindSymbol('LIBFORMAT_STAT_MTA');
	var use_stat_mda = wizard.FindSymbol('LIBFORMAT_STAT_MDA');
	var use_dll_mda = wizard.FindSymbol('LIBFORMAT_DLL_MDA');
	var useScript = wizard.FindSymbol('ILOGSCRIPT');
	var useGDIPlus = wizard.FindSymbol('GDI');
	var usePrinting	= wizard.FindSymbol('PRINTING');
	var useBitmapFilters= wizard.FindSymbol('FILTERS');
	var useBidi	= wizard.FindSymbol('BIDI');
	var useOLE = wizard.FindSymbol('COM');
	var usePPM = wizard.FindSymbol('PPM');
	var usePNG = wizard.FindSymbol('PNG');
	var useBMP = wizard.FindSymbol('BMP');
	var useJPG = wizard.FindSymbol('JPG');
	var useWBMP = wizard.FindSymbol('WBMP');
	var useRGB = wizard.FindSymbol('RGB');
	var useTIFF	= wizard.FindSymbol('TIFF');
	var useGadgets = wizard.FindSymbol('GADGETS');
	var useDocView = wizard.FindSymbol('APPFRAME');
	var useNoDefaultLook = wizard.FindSymbol('NODEFAULTLOOK');
	var useMotifLook = wizard.FindSymbol('MOTIF');
	var useWin31Look = wizard.FindSymbol('WINDOWS31');
	var useWin95Look = wizard.FindSymbol('WINDOWS95');
	var useWinXPLook = wizard.FindSymbol('WINDOWSXP');
	var useViewsXLook = wizard.FindSymbol('VIEWSX');
	var useManager = wizard.FindSymbol('MANAGER');
	var useGrapher = wizard.FindSymbol('GRAPHER');
	var useProtos = wizard.FindSymbol('PROTO');
	var useCharts = wizard.FindSymbol('CHARTS');
	var useGantt = wizard.FindSymbol('GANTT');
	var useGraphLayout = wizard.FindSymbol('LAYOUT');
	var useMaps	= wizard.FindSymbol('MAPS');

        // Get the required libraries
	var otherLibs = new String("ilvmain.obj ilog.lib views.lib winviews.lib");
	if (useScript) {
	    otherLibs += " iljs.lib iljsgide.lib ilvjs.lib";
	}
	if (useBidi) {
	    otherLibs += " ilvbidi.lib";
	}
	if (usePrinting) {
	    otherLibs += " ilvprint.lib";
	}
	if (useBitmapFilters) {
	    otherLibs += " ilvbmpflt.lib";
	}
	if (useGDIPlus) {
	    otherLibs += " ilvgdiplus.lib";
	}
	if (useMotifLook) {
	    otherLibs += " ilvmlook.lib";
	}
	if (useWin31Look) {
	    otherLibs += " ilvwlook.lib";
	}
	if (useWin95Look) {
	    otherLibs += " ilvw95look.lib";
	}
	if (useWinXPLook) {
	    otherLibs += " ilvwxplook.lib";
	}
	if (useViewsXLook) {
	    otherLibs += " ilvvxlook.lib";
	}
	if (useOLE) {
	    otherLibs += " oledlg.lib ilvcom.lib";
	}
	if (useBMP) {
	    otherLibs += " ilvbmp.lib";
	}
	if (useJPG) {
	    otherLibs += " ilvjpg.lib";
	}
	if (usePNG) {
	    otherLibs += " ilvpng.lib";
	}
	if (usePPM) {
	    otherLibs += " ilvppm.lib";
	}
	if (useRGB) {
	    otherLibs += " ilvrgb.lib";
	}
	if (useTIFF) {
	    otherLibs += " ilvtiff.lib";
	}
	if (useWBMP) {
	    otherLibs += " ilvwbmp.lib";
	}
	if (useGadgets) {
	    otherLibs += " ilvgadgt.lib ilvadvgdt.lib ilvatext.lib";
	    if (usePrinting) {
		otherLibs += " ilvprtdlg.lib";
	    }
	    if (useManager) {
		otherLibs += " ilvadvgadmgr.lib";
	    }
	    if (useMotifLook) {
		otherLibs += " ilvamlook.lib";
	    }
	    if (useWin31Look) {
		otherLibs += " ilvawlook.lib";
	    }
	    if (useWin95Look) {
		otherLibs += " ilvaw95look.lib";
	    }
	    if (useWinXPLook) {
		otherLibs += " ilvawxplook.lib";
	    }
	    if (useViewsXLook) {
		otherLibs += " ilvavxlook.lib";
	    }
	}
	if (useDocView) {
	    otherLibs += " ilvappframe.lib";
	}
	if (useProtos) {
	    otherLibs += " ilvproto.lib";
	}
	if (useManager) {
	    otherLibs += " ilvmgr.lib";
	    if (usePrinting) {
		otherLibs += " ilvmgrprint.lib";
	    }
	    if (useGadgets) {
		otherLibs += " ilvgadmgr.lib";
	    }
	}
	if (useGrapher) {
	    otherLibs += " ilvgrapher.lib";
	    if (useGadgets) {
		otherLibs += " ilvgadgraph.lib";
	    }
	}
	if (useMaps) {
	    otherLibs += " ilvmaps.lib";
	}
	if (useGantt) {
	    otherLibs += " ilvgantt.lib";
	}
	if (useCharts) {
	    otherLibs += " ilvcharts.lib";
	}
	if (useGraphLayout) {
	    otherLibs += " ilvlayout.lib ilvhierarchical.lib ilvbus.lib";
	    otherLibs += " ilvrandom.lib ilvorthlink.lib ilvtree.lib";
	}
	otherLibs += " wsock32.lib imm32.lib";

	var config_debug = proj.Object.Configurations('Debug');
	config_debug.IntermediateDirectory = 'Debug\\';
	config_debug.OutputDirectory = 'Debug\\';
	var config_release = proj.Object.Configurations('Release');
	config_release.IntermediateDirectory = 'Release\\';
	config_release.OutputDirectory = 'Release\\';

	// Add compiler settings
	var CLTool_debug = config_debug.Tools('VCCLCompilerTool');
	var CLTool_release = config_release.Tools('VCCLCompilerTool');

	// Add the include path
	var includeDir = ".;" + strILVHOME + "include";
	if (strIFCHOME) {
	    includeDir += ";" + strIFCHOME + "include";
	}
	CLTool_debug.AdditionalIncludeDirectories += includeDir;
	CLTool_release.AdditionalIncludeDirectories += includeDir;

	// Choose the correct runtime library format
	if (use_stat_mta) {
	    CLTool_debug.RuntimeLibrary = runtimeLibraryOption.rtMultiThreaded;
	    CLTool_release.RuntimeLibrary = runtimeLibraryOption.rtMultiThreaded;
	}
	else {
	    CLTool_debug.RuntimeLibrary = runtimeLibraryOption.rtMultiThreadedDLL;
	    CLTool_release.RuntimeLibrary = runtimeLibraryOption.rtMultiThreadedDLL;
	}

	// Take care of the /EHsc /GR options
	CLTool_debug.ExceptionHandling = cppExceptionHandling.cppExceptionHandlingYes;
	CLTool_debug.RuntimeTypeInfo = true;
	CLTool_release.ExceptionHandling = cppExceptionHandling.cppExceptionHandlingYes;
	CLTool_release.RuntimeTypeInfo = true;

	// Take care of the possible needed compilation flags
	// useless since RW Views 5.7: CLTool_debug.PreprocessorDefinitions += "IL_STD";
	// useless since RW Views 5.7: CLTool_release.PreprocessorDefinitions = "IL_STD";
	// useless since RW Views 5.7: if (useScript) {
	// useless since RW Views 5.7: 	CLTool_debug.PreprocessorDefinitions += ";ILJSTDH";
	// useless since RW Views 5.7: 	CLTool_release.PreprocessorDefinitions += ";ILJSTDH";
	// useless since RW Views 5.7: }
	if (use_dll_mda) {
	    CLTool_debug.PreprocessorDefinitions += ";IL_DLL";
	    CLTool_release.PreprocessorDefinitions += ";IL_DLL";
	}
	if (useNoDefaultLook) {
	    CLTool_debug.PreprocessorDefinitions += ";ILVNODEFAULTLOOK";
	    CLTool_release.PreprocessorDefinitions += ";ILVNODEFAULTLOOK";
	}

	// No debug for the release mode
	CLTool_release.DebugInformationFormat = debugDisabled;
	
	// Incompatible with /INCREMANTAL linker option		
	CLTool_release.WholeProgramOptimization = false;

	// Add linker settings
	var LinkTool_debug = config_debug.Tools('VCLinkerTool');
	var LinkTool_release = config_release.Tools('VCLinkerTool');

	// Set the correct library path
	var strLibFormat;
	if (use_stat_mta) {
	    strLibFormat = "stat_mta";
	}
	else if (use_stat_mda) {
	    strLibFormat = "stat_mda";
	}
	else {
	    strLibFormat = "dll_mda";
	}
	var libraryDir = ".;" + strILVHOME + "lib\\x86_.net2017_15.0\\" + strLibFormat;
	if (strIFCHOME) {
	    libraryDir += ";" + strIFCHOME + "lib\\x86_.net2017_15.0\\" + strLibFormat;
	}
	LinkTool_debug.AdditionalLibraryDirectories += libraryDir;
	LinkTool_release.AdditionalLibraryDirectories += libraryDir;

	// Link incrementally
	LinkTool_debug.LinkIncremental = linkIncrementalType.linkIncrementalYes;
	LinkTool_release.LinkIncremental = linkIncrementalType.linkIncrementalYes;

	// Add the libraries
	LinkTool_debug.AdditionalDependencies += otherLibs;
	LinkTool_release.AdditionalDependencies += otherLibs;

	// No debug for the release mode
	LinkTool_release.GenerateDebugInformation = false;
	
	// Incompatible flags with /INCREMENTAL
	LinkTool_release.LinkTimeCodeGeneration = false;
	LinkTool_release.EnableCOMDATFolding = false;
	LinkTool_release.OptimizeReferences = optReferencesDefault;

    }
    catch(e) {
	throw e;
    }
}

function PchSettings(proj)
{
    // Specify pch settings
    SetNoPchSettings(proj);
}

function DelFile(fso, strWizTempFile)
{
    try {
	if (fso.FileExists(strWizTempFile)) {
	    var tmpFile = fso.GetFile(strWizTempFile);
	    tmpFile.Delete();
	}
    }
    catch(e) {
	throw e;
    }
}

function GetTargetName(strName, strProjectName)
{
    try {
	// Set the name of the rendered file based on the template filename
	var strTarget = strName;

	if (strName == 'readme.txt') {
	    strTarget = 'ReadMe.txt';
	}
	if (strName == 'container.cpp') {
	    strTarget = 'main.cpp';
	}
	if (strName == 'gadcont.cpp') {
	    strTarget = 'main.cpp';
	}
	if (strName == 'manager.cpp') {
	    strTarget = 'main.cpp';
	}
	if (strName == 'grapher.cpp') {
	    strTarget = 'main.cpp';
	}
	return strTarget;
    }
    catch(e) {
	throw e;
    }
}

function AddFilesToCustomProj(proj, strProjectName, strProjectPath, InfFile)
{
    try {
	var projItems = proj.ProjectItems

	var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');

	var strTpl = '';
	var strName = '';

	var strTextStream = InfFile.OpenAsTextStream(1, -2);
	while (!strTextStream.AtEndOfStream) {
	    strTpl = strTextStream.ReadLine();
	    if (strTpl != '') {
		strName = strTpl;
		var strTarget = GetTargetName(strName, strProjectName);
		var strTemplate = strTemplatePath + '\\' + strTpl;
		var strFile = strProjectPath + '\\' + strTarget;

		var bCopyOnly = false;  // "true" will only copy the file from
		                        // strTemplate to strTarget without rendering/adding
		                        // to the project
		var strExt = strName.substr(strName.lastIndexOf("."));
		if(strExt==".bmp" || strExt==".ico" || strExt==".gif" || strExt==".rtf" || strExt==".css")
		    bCopyOnly = true;
		wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);
		proj.Object.AddFile(strFile);
	    }
	}
	strTextStream.Close();
    }
    catch(e) {
	throw e;
    }
}
