// DemoATLCtrl.h : Declaration of the CDemoATLCtrl

#ifndef __DEMOATLCTRL_H_
#define __DEMOATLCTRL_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

// Added for Rogue Wave Views.
#include "DemoCtrl.h"
// End Added for Rogue Wave Views.

#include "DemoATLCP.h"

/////////////////////////////////////////////////////////////////////////////
// CDemoATLCtrl
class ATL_NO_VTABLE CDemoATLCtrl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IDemoATLCtrl, &IID_IDemoATLCtrl, &LIBID_DEMOATLLib>,
	public CComControl<CDemoATLCtrl>,
	public IPersistStreamInitImpl<CDemoATLCtrl>,
	public IOleControlImpl<CDemoATLCtrl>,
	public IOleObjectImpl<CDemoATLCtrl>,
	public IOleInPlaceActiveObjectImpl<CDemoATLCtrl>,
	public IViewObjectExImpl<CDemoATLCtrl>,
	public IOleInPlaceObjectWindowlessImpl<CDemoATLCtrl>,
	public IConnectionPointContainerImpl<CDemoATLCtrl>,
	public IPersistStorageImpl<CDemoATLCtrl>,
	public ISpecifyPropertyPagesImpl<CDemoATLCtrl>,
	public IQuickActivateImpl<CDemoATLCtrl>,
	public IDataObjectImpl<CDemoATLCtrl>,
	public IProvideClassInfo2Impl<&CLSID_DemoATLCtrl, &DIID__IDemoATLCtrlEvents, &LIBID_DEMOATLLib>,
	public IPropertyNotifySinkCP<CDemoATLCtrl>,
	public CComCoClass<CDemoATLCtrl, &CLSID_DemoATLCtrl>,
	public CProxy_IDemoATLCtrlEvents< CDemoATLCtrl >
{
public:
	CDemoATLCtrl()
	// Added for Rogue Wave Views.
	: m_Ctrl(0), m_FileName(), m_Background(-1)
	// End Added for Rogue Wave Views.
	{
		m_bWindowOnly = TRUE;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DEMOATLCTRL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDemoATLCtrl)
	COM_INTERFACE_ENTRY(IDemoATLCtrl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CDemoATLCtrl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Added for Rogue Wave Views.
	PROP_ENTRY_TYPE("FileName", 1, CLSID_NULL, VT_BSTR)
	PROP_ENTRY_TYPE("Background", 2, CLSID_NULL, VT_COLOR)
	// End Added for Rogue Wave Views.
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CDemoATLCtrl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IDemoATLCtrlEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CDemoATLCtrl)
	CHAIN_MSG_MAP(CComControl<CDemoATLCtrl>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IDemoATLCtrl
public:
	STDMETHOD(get_Background)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_Background)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_FileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FileName)(/*[in]*/ BSTR newVal);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 3.0 : DemoATLCtrl");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		return S_OK;
	}
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		// Added for Rogue Wave Views.
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
		// End Added for Rogue Wave Views.
		return 0;
	}
private:
	OLE_COLOR m_Background;
	CComBSTR m_FileName;
	DemoCtrl* m_Ctrl;
};

#endif //__DEMOATLCTRL_H_
