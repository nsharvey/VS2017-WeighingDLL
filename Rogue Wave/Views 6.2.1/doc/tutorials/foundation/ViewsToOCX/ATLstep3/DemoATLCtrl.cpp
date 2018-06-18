// DemoATLCtrl.cpp : Implementation of CDemoATLCtrl

#include "stdafx.h"
#include "DemoATL.h"
#include "DemoATLCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDemoATLCtrl


STDMETHODIMP CDemoATLCtrl::get_FileName(BSTR *pVal)
{
	// TODO: Add your implementation code here
	// Added for Rogue Wave Views.
	return m_FileName.CopyTo(pVal);
	// End Added for Rogue Wave Views.
	return S_OK;
}

STDMETHODIMP CDemoATLCtrl::put_FileName(BSTR newVal)
{
	// TODO: Add your implementation code here
	// Added for Rogue Wave Views.
	if (!newVal)
	    return S_OK;
	if (m_FileName != newVal) {
	    m_FileName = newVal;
	    if (!m_FileName.Length())
		m_FileName.Empty();
	    if (m_Ctrl && !!m_FileName)
		m_Ctrl->setFileName(m_FileName);
	}
	// End Added for Rogue Wave Views.
	return S_OK;
}

STDMETHODIMP CDemoATLCtrl::get_Background(OLE_COLOR *pVal)
{
	// TODO: Add your implementation code here
	// Added for Rogue Wave Views.
	*pVal = m_Background;
	// End Added for Rogue Wave Views.
	return S_OK;
}

STDMETHODIMP CDemoATLCtrl::put_Background(OLE_COLOR newVal)
{
	// TODO: Add your implementation code here
	// Added for Rogue Wave Views.
	if (m_Background != newVal) {
	    m_Background = newVal;
	    if (m_Ctrl && (m_Background != -1))
		m_Ctrl->setBackground(m_Background);
	}
	// End Added for Rogue Wave Views.
	return S_OK;
}
