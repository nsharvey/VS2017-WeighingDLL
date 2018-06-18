var page1Name = "Overview";
var page2Name = "Library Settings";
var page3Name = "Foundation Libraries";
var page4Name = "Controls Libraries";
var page5Name = "2D Graphics Libraries";
var page6Name = "Add-On Libraries";
var page7Name = "Application Settings";

// Functions to check the dependencies between the libraries
// Foundation libraries
// Bitmap readers
function OnPNG()
{
}

function OnJPG()
{
}

function OnTIFF()
{
    if (!document.all.TIFF.checked) {
	if (window.external.FindSymbol("MAPS")) {
	    window.external.AddSymbol("MAPS", false);
	}
    }
}

// Controls libraries
function OnGadgets()
{
    if (document.all.GADGETS.checked) {
	// Static case
	if (!window.external.FindSymbol("LIBFORMAT_DLL_MDA")) {
	    if (!document.all.MOTIF.checked) {
		document.all.MOTIF.checked = true;	
	    }
	    if (!document.all.VIEWSX.checked) {
		document.all.VIEWSX.checked = true;
	    }	
	    if (!document.all.WINDOWSXP.checked) {
		document.all.WINDOWSXP.checked = true;
	    }	
	    if (!document.all.WINDOWS31.checked) {
		document.all.WINDOWS31.checked = true;
	    }
	    if (!document.all.WINDOWS95.checked) {
		document.all.WINDOWS95.checked = true;
	    }
	}
    }
    else {
	if (document.all.APPFRAME.checked) {
	    document.all.APPFRAME.checked = false;
	}
	if (document.all.MOTIF.checked) {
	    document.all.MOTIF.checked = false;
	}
	if (document.all.VIEWSX.checked) {
	    document.all.VIEWSX.checked = false;
	}	
	if (document.all.WINDOWSXP.checked) {
	    document.all.WINDOWSXP.checked = false;
	}	
	if (document.all.WINDOWS95.checked) {
	    document.all.WINDOWS95.checked = false;
	}
	if (document.all.WINDOWS31.checked) {
	    document.all.WINDOWS31.checked = false;
	}
	if (window.external.FindSymbol("GANTT")) {
	    window.external.AddSymbol("GANTT", false);
	}
    }
}

function OnAppFrame()
{
    if (document.all.APPFRAME.checked) {
	if (!document.all.GADGETS.checked) {
	    document.all.GADGETS.checked = true;
	}
	if (!window.external.FindSymbol("MANAGER")) {
	    window.external.AddSymbol("MANAGER", true);
	}
    }
}

// Look & feel
function OnMotif()
{
    if (document.all.MOTIF.checked) {
	if (!document.all.GADGETS.checked) {
	    document.all.GADGETS.checked = true;
	}
    }
}

function OnWindows31()
{
    if (document.all.WINDOWS31.checked) {
	if (!document.all.GADGETS.checked) {
	    document.all.GADGETS.checked = true;
	}
    }
    else {
	if (document.all.WINDOWS95.checked) {
	    document.all.WINDOWS95.checked = false;
	    OnWindows95();
	}
	if (document.all.VIEWSX.checked) {
	    document.all.VIEWSX.checked = false;
	}
    }
}

function OnWindows95()
{
    if (document.all.WINDOWS95.checked) {
	if (!document.all.WINDOWS31.checked) {
	    document.all.WINDOWS31.checked = true;
	    OnWindows31();
	}
    }
    else {
	if (document.all.WINDOWSXP.checked) {
	    document.all.WINDOWSXP.checked = false;
	}
    }
}

function OnWindowsXP()
{
    if (document.all.WINDOWSXP.checked) {
	if (!document.all.WINDOWS95.checked) {
	    document.all.WINDOWS95.checked = true;
	    OnWindows95();
	}
    }
}

function OnViewsX()
{
    if (document.all.VIEWSX.checked) {
	if (!document.all.WINDOWS31.checked) {
	    document.all.WINDOWS31.checked = true;
	    OnWindows31();
	}
    }
}

// 2D Graphics libraries
function OnManager()
{
    if (!document.all.MANAGER.checked) {
	if (document.all.GRAPHER.checked) {
	    document.all.GRAPHER.checked = false;
	}
	if (document.all.PROTO.checked) {
	    document.all.PROTO.checked = false;
	}
	if (window.external.FindSymbol("APPFRAME")) {
	    window.external.AddSymbol("APPFRAME", false);
	}
	if (window.external.FindSymbol("MAPS")) {
	    window.external.AddSymbol("MAPS", false);
	}
	if (window.external.FindSymbol("LAYOUT")) {
	    window.external.AddSymbol("LAYOUT", false);
	}
	if (window.external.FindSymbol("GANTT")) {
	    window.external.AddSymbol("GANTT", false);
	}
    }	
}

function OnGrapher()
{
    if (document.all.GRAPHER.checked) {
	if (!document.all.MANAGER.checked) {
	    document.all.MANAGER.checked = true;
	}
    }		
    else {
	if (document.all.PROTO.checked) {
	    document.all.PROTO.checked = false;
	}	
	if (window.external.FindSymbol("LAYOUT")) {
	    window.external.AddSymbol("LAYOUT", false);
	}
	if (window.external.FindSymbol("GANTT")) {
	    window.external.AddSymbol("GANTT", false);
	}
    }
}

function OnPrototypes()
{
    if (document.all.PROTO.checked) {
	if (!document.all.GRAPHER.checked) {
	    document.all.GRAPHER.checked = true;
	}
	if (!document.all.MANAGER.checked) {
	    document.all.MANAGER.checked = true;
	}
    }
}

// Optional libraries
function OnGantt()
{
    if (document.all.GANTT.checked) {
	if (!window.external.FindSymbol("GRAPHER")) {
	    window.external.AddSymbol("GRAPHER", true);
	}
	if (!window.external.FindSymbol("MANAGER")) {
	    window.external.AddSymbol("MANAGER", true);
	}
	if (!window.external.FindSymbol("GADGETS")) {
	    window.external.AddSymbol("GADGETS", true);
	}
    }
}

function OnGraphLayout() 
{
    if (document.all.LAYOUT.checked) {
	if (!window.external.FindSymbol("GRAPHER")) {
	    window.external.AddSymbol("GRAPHER", true);
	}
	if (!window.external.FindSymbol("MANAGER")) {
	    window.external.AddSymbol("MANAGER", true);
	}
    }
}

function OnMaps()
{
    if (document.all.MAPS.checked) {
	if (!window.external.FindSymbol("MANAGER")) {
	    window.external.AddSymbol("MANAGER", true);
	}
	if (!window.external.FindSymbol("TIFF")) {
	    window.external.AddSymbol("TIFF", true);
	}
    }
}
