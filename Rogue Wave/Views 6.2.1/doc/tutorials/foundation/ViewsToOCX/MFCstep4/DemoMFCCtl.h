#if !defined(AFX_DEMOMFCCTL_H__3D31E7C6_400B_11D3_B74F_00C04F68A89D__INCLUDED_)
#define AFX_DEMOMFCCTL_H__3D31E7C6_400B_11D3_B74F_00C04F68A89D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DemoMFCCtl.h : Declaration of the CDemoMFCCtrl ActiveX Control class.

// Added for Rogue Wave Views.
class DemoCtrl;
class TrackInteractor;
// End Added for Rogue Wave Views.

/////////////////////////////////////////////////////////////////////////////
// CDemoMFCCtrl : See DemoMFCCtl.cpp for implementation.

class CDemoMFCCtrl : public COleControl
{
	friend class TrackInteractor;
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
	afx_msg BSTR GetFilename();
	afx_msg void SetFilename(LPCTSTR lpszNewValue);
	afx_msg OLE_COLOR GetBackground();
	afx_msg void SetBackground(OLE_COLOR nNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CDemoMFCCtrl)
	void FirePointerPosition(BSTR FAR* name, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
		{FireEvent(eventidPointerPosition,EVENT_PARAM(VTS_PBSTR  VTS_XPOS_PIXELS  VTS_YPOS_PIXELS), name, x, y);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CDemoMFCCtrl)
	dispidFilename = 1L,
	dispidBackground = 2L,
	eventidPointerPosition = 1L,
	//}}AFX_DISP_ID
	};
private:
	OLE_COLOR m_Background;
	CString m_FileName;
	DemoCtrl* m_Ctrl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOMFCCTL_H__3D31E7C6_400B_11D3_B74F_00C04F68A89D__INCLUDED)
