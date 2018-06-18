#if !defined(AFX_DEMOMFCCTL_H__3D31E7C6_400B_11D3_B74F_00C04F68A89D__INCLUDED_)
#define AFX_DEMOMFCCTL_H__3D31E7C6_400B_11D3_B74F_00C04F68A89D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DemoMFCCtl.h : Declaration of the CDemoMFCCtrl ActiveX Control class.

// Added for Rogue Wave Views.
class DemoCtrl;
// End Added for Rogue Wave Views.

/////////////////////////////////////////////////////////////////////////////
// CDemoMFCCtrl : See DemoMFCCtl.cpp for implementation.

class CDemoMFCCtrl : public COleControl
{
	DECLARE_DYNCREATE(CDemoMFCCtrl)

// Constructor
public:
	CDemoMFCCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoMFCCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CDemoMFCCtrl();

	DECLARE_OLECREATE_EX(CDemoMFCCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CDemoMFCCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CDemoMFCCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CDemoMFCCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CDemoMFCCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CDemoMFCCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CDemoMFCCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CDemoMFCCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
private:
	DemoCtrl* m_Ctrl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOMFCCTL_H__3D31E7C6_400B_11D3_B74F_00C04F68A89D__INCLUDED)