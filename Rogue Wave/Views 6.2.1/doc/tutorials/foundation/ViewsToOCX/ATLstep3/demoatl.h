/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Aug 21 14:50:23 2000
 */
/* Compiler settings for M:\public\views40\doc\tutorials\foundation\viewstoocx\atlstep3\DemoATL.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DemoATL_h__
#define __DemoATL_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDemoATLCtrl_FWD_DEFINED__
#define __IDemoATLCtrl_FWD_DEFINED__
typedef interface IDemoATLCtrl IDemoATLCtrl;
#endif 	/* __IDemoATLCtrl_FWD_DEFINED__ */


#ifndef ___IDemoATLCtrlEvents_FWD_DEFINED__
#define ___IDemoATLCtrlEvents_FWD_DEFINED__
typedef interface _IDemoATLCtrlEvents _IDemoATLCtrlEvents;
#endif 	/* ___IDemoATLCtrlEvents_FWD_DEFINED__ */


#ifndef __DemoATLCtrl_FWD_DEFINED__
#define __DemoATLCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class DemoATLCtrl DemoATLCtrl;
#else
typedef struct DemoATLCtrl DemoATLCtrl;
#endif /* __cplusplus */

#endif 	/* __DemoATLCtrl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDemoATLCtrl_INTERFACE_DEFINED__
#define __IDemoATLCtrl_INTERFACE_DEFINED__

/* interface IDemoATLCtrl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDemoATLCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3B10417C-3E6C-11D3-B74F-00C04F68A89D")
    IDemoATLCtrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Background( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Background( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDemoATLCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDemoATLCtrl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDemoATLCtrl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDemoATLCtrl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDemoATLCtrl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDemoATLCtrl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDemoATLCtrl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDemoATLCtrl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileName )( 
            IDemoATLCtrl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FileName )( 
            IDemoATLCtrl __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Background )( 
            IDemoATLCtrl __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Background )( 
            IDemoATLCtrl __RPC_FAR * This,
            /* [in] */ OLE_COLOR newVal);
        
        END_INTERFACE
    } IDemoATLCtrlVtbl;

    interface IDemoATLCtrl
    {
        CONST_VTBL struct IDemoATLCtrlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDemoATLCtrl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDemoATLCtrl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDemoATLCtrl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDemoATLCtrl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDemoATLCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDemoATLCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDemoATLCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDemoATLCtrl_get_FileName(This,pVal)	\
    (This)->lpVtbl -> get_FileName(This,pVal)

#define IDemoATLCtrl_put_FileName(This,newVal)	\
    (This)->lpVtbl -> put_FileName(This,newVal)

#define IDemoATLCtrl_get_Background(This,pVal)	\
    (This)->lpVtbl -> get_Background(This,pVal)

#define IDemoATLCtrl_put_Background(This,newVal)	\
    (This)->lpVtbl -> put_Background(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDemoATLCtrl_get_FileName_Proxy( 
    IDemoATLCtrl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDemoATLCtrl_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDemoATLCtrl_put_FileName_Proxy( 
    IDemoATLCtrl __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDemoATLCtrl_put_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDemoATLCtrl_get_Background_Proxy( 
    IDemoATLCtrl __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IDemoATLCtrl_get_Background_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDemoATLCtrl_put_Background_Proxy( 
    IDemoATLCtrl __RPC_FAR * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IDemoATLCtrl_put_Background_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDemoATLCtrl_INTERFACE_DEFINED__ */



#ifndef __DEMOATLLib_LIBRARY_DEFINED__
#define __DEMOATLLib_LIBRARY_DEFINED__

/* library DEMOATLLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DEMOATLLib;

#ifndef ___IDemoATLCtrlEvents_DISPINTERFACE_DEFINED__
#define ___IDemoATLCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IDemoATLCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IDemoATLCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("3B10417E-3E6C-11D3-B74F-00C04F68A89D")
    _IDemoATLCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IDemoATLCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IDemoATLCtrlEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IDemoATLCtrlEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IDemoATLCtrlEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IDemoATLCtrlEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IDemoATLCtrlEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IDemoATLCtrlEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IDemoATLCtrlEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IDemoATLCtrlEventsVtbl;

    interface _IDemoATLCtrlEvents
    {
        CONST_VTBL struct _IDemoATLCtrlEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IDemoATLCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IDemoATLCtrlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IDemoATLCtrlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IDemoATLCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IDemoATLCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IDemoATLCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IDemoATLCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IDemoATLCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DemoATLCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("3B10417D-3E6C-11D3-B74F-00C04F68A89D")
DemoATLCtrl;
#endif
#endif /* __DEMOATLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
