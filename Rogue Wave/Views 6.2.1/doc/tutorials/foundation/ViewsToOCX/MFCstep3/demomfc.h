#if !defined(AFX_DEMOMFC_H__3D31E7BE_400B_11D3_B74F_00C04F68A89D__INCLUDED_)
#define AFX_DEMOMFC_H__3D31E7BE_400B_11D3_B74F_00C04F68A89D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DemoMFC.h : main header file for DEMOMFC.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemoMFCApp : See DemoMFC.cpp for implementation.

class CDemoMFCApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOMFC_H__3D31E7BE_400B_11D3_B74F_00C04F68A89D__INCLUDED)
