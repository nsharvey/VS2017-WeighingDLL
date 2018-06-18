// DemoMFCCtl.cpp : Implementation of the CDemoMFCCtrl ActiveX Control class.

#include "stdafx.h"
#include "DemoMFC.h"
#include "DemoMFCCtl.h"
#include "DemoMFCPpg.h"

// Added for Rogue Wave Views.
#include <DemoCtrl.h>
// End Added for Rogue Wave Views.

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CDemoMFCCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CDemoMFCCtrl, COleControl)
	//{{AFX_MSG_MAP(CDemoMFCCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CDemoMFCCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CDemoMFCCtrl)
	DISP_PROPERTY_EX(CDemoMFCCtrl, "Filename", GetFilename, SetFilename, VT_BSTR)
	DISP_PROPERTY_EX(CDemoMFCCtrl, "Background", GetBackground, SetBackground, VT_COLOR)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CDemoMFCCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CDemoMFCCtrl, COleControl)
	//{{AFX_EVENT_MAP(CDemoMFCCtrl)
	EVENT_CUSTOM("PointerPosition", FirePointerPosition, VTS_PBSTR  VTS_XPOS_PIXELS  VTS_YPOS_PIXELS)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CDemoMFCCtrl, 1)
	PROPPAGEID(CDemoMFCPropPage::guid)
END_PROPPAGEIDS(CDemoMFCCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CDemoMFCCtrl, "DEMOMFC.DemoMFCCtrl.1",
	0x3d31e7b8, 0x400b, 0x11d3, 0xb7, 0x4f, 0, 0xc0, 0x4f, 0x68, 0xa8, 0x9d)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CDemoMFCCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DDemoMFC =
		{ 0x3d31e7b6, 0x400b, 0x11d3, { 0xb7, 0x4f, 0, 0xc0, 0x4f, 0x68, 0xa8, 0x9d } };
const IID BASED_CODE IID_DDemoMFCEvents =
		{ 0x3d31e7b7, 0x400b, 0x11d3, { 0xb7, 0x4f, 0, 0xc0, 0x4f, 0x68, 0xa8, 0x9d } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwDemoMFCOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CDemoMFCCtrl, IDS_DEMOMFC, _dwDemoMFCOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCCtrl::CDemoMFCCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CDemoMFCCtrl

BOOL CDemoMFCCtrl::CDemoMFCCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegInsertable | afxRegApartmentThreading to afxRegInsertable.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_DEMOMFC,
			IDB_DEMOMFC,
			afxRegInsertable | afxRegApartmentThreading,
			_dwDemoMFCOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCCtrl::CDemoMFCCtrl - Constructor

CDemoMFCCtrl::CDemoMFCCtrl()
// Added for Rogue Wave Views.
: m_Ctrl(0), m_FileName(), m_Background(-1)
// End Added for Rogue Wave Views.
{
	InitializeIIDs(&IID_DDemoMFC, &IID_DDemoMFCEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCCtrl::~CDemoMFCCtrl - Destructor

CDemoMFCCtrl::~CDemoMFCCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCCtrl::OnDraw - Drawing function

void CDemoMFCCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCCtrl::DoPropExchange - Persistence support

void CDemoMFCCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCCtrl::OnResetState - Reset control to default state

void CDemoMFCCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCCtrl::AboutBox - Display an "About" box to the user

void CDemoMFCCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_DEMOMFC);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCCtrl message handlers

int CDemoMFCCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	// Added for Rogue Wave Views.
#if defined(USE_VIEWS)
	try {
	    m_Ctrl = new DemoCtrl(m_hWnd, *this);
            // Added for the FileName property.
	    m_Ctrl->setFileName(m_FileName);
	    // Added for the Background property.
	    m_Ctrl->setBackground(m_Background);
	} catch (...) {
	    if (m_Ctrl) {
		delete m_Ctrl;
		m_Ctrl = 0;
	    }
	}
#endif
	// End Added for Rogue Wave Views.
	return 0;
}

BSTR CDemoMFCCtrl::GetFilename() 
{
	CString strResult;
	// TODO: Add your property handler here
        // Added for Rogue Wave Views.
	strResult = m_FileName;
	// End Added for Rogue Wave Views.
	return strResult.AllocSysString();
}

void CDemoMFCCtrl::SetFilename(LPCTSTR lpszNewValue) 
{
	// TODO: Add your property handler here
        // Added for Rogue Wave Views.
#if defined(USE_VIEWS)
	if (!lpszNewValue || !*lpszNewValue)
	    return;
	if (m_FileName != lpszNewValue) {
	    m_FileName = lpszNewValue;
	    if (m_Ctrl && m_FileName.GetLength())
		m_Ctrl->setFileName(lpszNewValue);
	}
#endif
	// End Added for Rogue Wave Views.
	SetModifiedFlag();
}

OLE_COLOR CDemoMFCCtrl::GetBackground() 
{
	// TODO: Add your property handler here
	return m_Background;
}

void CDemoMFCCtrl::SetBackground(OLE_COLOR nNewValue) 
{
	// TODO: Add your property handler here
        // Added for Rogue Wave Views.
#if defined(USE_VIEWS)
	if (m_Background != nNewValue) {
	    m_Background = nNewValue;
	    if (m_Ctrl && (m_Background != -1))
		m_Ctrl->setBackground(m_Background);
	}
#endif
	// End Added for Rogue Wave Views.
	SetModifiedFlag();
}
