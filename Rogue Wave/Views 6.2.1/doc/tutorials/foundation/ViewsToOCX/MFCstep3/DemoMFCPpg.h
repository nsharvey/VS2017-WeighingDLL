#if !defined(AFX_DEMOMFCPPG_H__3D31E7C8_400B_11D3_B74F_00C04F68A89D__INCLUDED_)
#define AFX_DEMOMFCPPG_H__3D31E7C8_400B_11D3_B74F_00C04F68A89D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DemoMFCPpg.h : Declaration of the CDemoMFCPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CDemoMFCPropPage : See DemoMFCPpg.cpp.cpp for implementation.

class CDemoMFCPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CDemoMFCPropPage)
	DECLARE_OLECREATE_EX(CDemoMFCPropPage)

// Constructor
public:
	CDemoMFCPropPage();

// Dialog Data
	//{{AFX_DATA(CDemoMFCPropPage)
	enum { IDD = IDD_PROPPAGE_DEMOMFC };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CDemoMFCPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOMFCPPG_H__3D31E7C8_400B_11D3_B74F_00C04F68A89D__INCLUDED)
