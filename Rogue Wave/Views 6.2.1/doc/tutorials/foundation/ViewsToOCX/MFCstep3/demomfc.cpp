// DemoMFC.cpp : Implementation of CDemoMFCApp and DLL registration.

#include "stdafx.h"
#include "DemoMFC.h"

// Added for Rogue Wave Views.
#include <DemoCtrl.h>
// End Added for Rogue Wave Views.

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDemoMFCApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x3d31e7b5, 0x400b, 0x11d3, { 0xb7, 0x4f, 0, 0xc0, 0x4f, 0x68, 0xa8, 0x9d } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

////////////////////////////////////////////////////////////////////////////
// CDemoMFCApp::InitInstance - DLL initialization

BOOL CDemoMFCApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
		// Added for Rogue Wave Views.
#if defined(USE_VIEWS)
		bInit = DemoCtrl::InitDisplay(AfxGetInstanceHandle());
#endif
		// End Added for Rogue Wave Views.
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CDemoMFCApp::ExitInstance - DLL termination

int CDemoMFCApp::ExitInstance()
{
	// TODO: Add your own module termination code here.
	// Added for Rogue Wave Views.
#if defined(USE_VIEWS)
	DemoCtrl::CleanDisplay();
#endif
	// End Added for Rogue Wave Views.
	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
