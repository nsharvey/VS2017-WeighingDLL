#ifndef _DEMOATLCP_H_
#define _DEMOATLCP_H_


template <class T>
class CProxy_IDemoATLCtrlEvents : public IConnectionPointImpl<T, &DIID__IDemoATLCtrlEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_PointerPosition(BSTR name, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[3];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				VariantClear(&varResult);
				pvars[2] = name;
				pvars[1] = x;
				pvars[0] = y;
				DISPPARAMS disp = { pvars, NULL, 3, 0 };
				pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
};
#endif