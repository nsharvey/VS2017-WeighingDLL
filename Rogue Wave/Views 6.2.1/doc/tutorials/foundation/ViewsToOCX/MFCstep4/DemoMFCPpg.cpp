// DemoMFCPpg.cpp : Implementation of the CDemoMFCPropPage property page class.

#include "stdafx.h"
#include "DemoMFC.h"
#include "DemoMFCPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CDemoMFCPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CDemoMFCPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CDemoMFCPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CDemoMFCPropPage, "DEMOMFC.DemoMFCPropPage.1",
	0x3d31e7b9, 0x400b, 0x11d3, 0xb7, 0x4f, 0, 0xc0, 0x4f, 0x68, 0xa8, 0x9d)


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCPropPage::CDemoMFCPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CDemoMFCPropPage

BOOL CDemoMFCPropPage::CDemoMFCPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_DEMOMFC_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCPropPage::CDemoMFCPropPage - Constructor

CDemoMFCPropPage::CDemoMFCPropPage() :
	COlePropertyPage(IDD, IDS_DEMOMFC_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CDemoMFCPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCPropPage::DoDataExchange - Moves data between page and properties

void CDemoMFCPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CDemoMFCPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CDemoMFCPropPage message handlers
