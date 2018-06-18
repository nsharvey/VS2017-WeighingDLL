// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/windows/com.h
// --------------------------------------------------------------------------
//
// Licensed Materials - Property of Rogue Wave Software, Inc.
// (c) Copyright Rogue Wave Software, Inc. 2012, 2018
// (c) Copyright IBM Corp. 2009, 2011
// (c) Copyright ILOG 1992, 2009
// All Rights Reserved.
//
// Note to U.S. Government Users Restricted Rights:
// The Software and Documentation were developed at private expense and
// are "Commercial Items" as that term is defined at 48 CFR 2.101,
// consisting of "Commercial Computer Software" and
// "Commercial Computer Software Documentation", as such terms are
// used in 48 CFR 12.212 or 48 CFR 227.7202-1 through 227.7202-4,
// as applicable.
//
// --------------------------------------------------------------------------
// Definitions of a class that encapsulates a COM interface and some useful
// classes.
// --------------------------------------------------------------------------
#ifndef __Ilv_Windows_Com_H
#define __Ilv_Windows_Com_H

#if !defined(__Ilv_Windows_Macros_H)
#include <ilviews/windows/macros.h>
#endif /* !__Ilv_Windows_Macros_H */
#if !defined(__Ilv_Base_String_H)
#include <ilviews/base/string.h>
#endif /* !__Ilv_Base_String_H */
#if !defined(__Ilv_Util_Refcount_H)
#include <ilviews/util/refcount.h>
#endif /* !__Ilv_Util_Refcount_H */

#include <oleidl.h>

// --------------------------------------------------------------------------
// Exception classes.
// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvCOMError
{
public:
    inline IlvCOMError(HRESULT hr) : _hr(hr) {}
    inline HRESULT	getErrorCode() const { return _hr; }
    inline DWORD	formatErrorMessage(IlString& message) const
			{
			    return FormatErrorMessage(getErrorCode(), message);
			}
    static DWORD	FormatErrorMessage(HRESULT hr, IlString& message);

private:
    HRESULT		_hr;
};

// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvCOMLibraryInitializationError : public IlvCOMError
{
public:
    inline IlvCOMLibraryInitializationError(HRESULT hr) : IlvCOMError(hr) {}
};

// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvCOMCreateInstanceError : public IlvCOMError
{
public:
    inline IlvCOMCreateInstanceError(HRESULT hr) : IlvCOMError(hr) {}
};

// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvCOMInterfaceError : public IlvCOMError
{
public:
    inline IlvCOMInterfaceError(HRESULT hr) : IlvCOMError(hr) {}
};

// --------------------------------------------------------------------------
//
// Pure abstract root class for library initializations.
//
// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvAbstractLibraryInitialization
{
public:
    virtual inline ~IlvAbstractLibraryInitialization() = 0;

protected:
    typedef IlvRefCountPtr<IlvAbstractLibraryInitialization> CntPtr;
    typedef
	IlvInitializedRefCountPtr<IlvAbstractLibraryInitialization> InitCntPtr;
};

// --------------------------------------------------------------------------
inline
IlvAbstractLibraryInitialization::~IlvAbstractLibraryInitialization()
{
}

// --------------------------------------------------------------------------
//
// Initialization of the COM library.
//
// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvCOMLibraryInitialization
    : public IlvAbstractLibraryInitialization
{
    friend CntPtr;
public:
    // May throw an IlvCOMLibraryInitializationError
    static CntPtr GetInstance();

private:
    IlvCOMLibraryInitialization();
    ~IlvCOMLibraryInitialization();
    // This function is intentionally not defined.
    IlvCOMLibraryInitialization(const IlvCOMLibraryInitialization&);
    // This operator is intentionally not defined.
    IlvCOMLibraryInitialization& operator=(IlvCOMLibraryInitialization const&);

    IlBoolean _mustBeReleased;

    static IlvCOMLibraryInitialization*	_Instance;
    static long*			_InstanceCounter;
};

// --------------------------------------------------------------------------
//
// Abstract class. Root for the classes that encapsulate COM interfaces.
//
// --------------------------------------------------------------------------
template<class INTERFACE> class IlvAbstractCOMInterface
{
    typedef IlvRefCountPtr<IlvAbstractLibraryInitialization> CntPtr;
public:
    inline virtual ~IlvAbstractCOMInterface() = 0;
    inline INTERFACE*	getInterface() const;
    inline operator	INTERFACE*() const;
    inline operator	INTERFACE const*() const;
    inline
    INTERFACE* operator	->() const;

    inline HRESULT	setInterface(IUnknown* iunk, REFIID iid);
    inline void		setInterface(INTERFACE* interf);

protected:
    inline IlvAbstractCOMInterface();
    inline IlvAbstractCOMInterface(IlvAbstractCOMInterface const& other);
    inline IlvAbstractCOMInterface(CntPtr const& initObj);

    inline IlvAbstractCOMInterface&
	operator=(IlvAbstractCOMInterface const& other);

    inline CntPtr const& getInitializer() const;

private:
    CntPtr		_initializeObject;
    INTERFACE*		_interface;
};

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvAbstractCOMInterface<INTERFACE>::~IlvAbstractCOMInterface()
{
    if (_interface) {
	_interface->Release();
	_interface = 0;
    }
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline INTERFACE*
IlvAbstractCOMInterface<INTERFACE>::getInterface() const
{
    return _interface;
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvAbstractCOMInterface<INTERFACE>::operator INTERFACE*() const
{
    return _interface;
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline INTERFACE*
IlvAbstractCOMInterface<INTERFACE>::operator->() const
{
    return _interface;
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvAbstractCOMInterface<INTERFACE>::operator INTERFACE const*() const
{
    return _interface;
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline HRESULT
IlvAbstractCOMInterface<INTERFACE>::setInterface(IUnknown* iunk, REFIID iid)
{
    INTERFACE* interf = _interface;
    HRESULT hr =
	iunk->QueryInterface(iid, IL_REINTERPRETCAST(void**, &_interface));
    if (FAILED(hr)) {
      _interface = interf;
    } else if (interf) {
      interf->Release();
    }
    return hr;
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline void
IlvAbstractCOMInterface<INTERFACE>::setInterface(INTERFACE* interf)
{
    if (interf) {
	interf->AddRef();
    }
    if (_interface) {
	_interface->Release();
    }
    _interface = interf;
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvAbstractCOMInterface<INTERFACE>::IlvAbstractCOMInterface()
: _initializeObject(IlvCOMLibraryInitialization::GetInstance()),
  _interface(0)
{
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvAbstractCOMInterface<INTERFACE>::IlvAbstractCOMInterface(
					IlvAbstractCOMInterface const& other)
: _initializeObject(other._initializeObject),
  _interface(0)
{
    setInterface(other._interface);
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvAbstractCOMInterface<INTERFACE>::IlvAbstractCOMInterface(
						CntPtr const& initializer)
: _initializeObject(initializer),
  _interface(0)
{
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline IlvAbstractCOMInterface<INTERFACE>&
IlvAbstractCOMInterface<INTERFACE>::operator=(
					IlvAbstractCOMInterface const& other)
{
    _initializeObject = other._initializeObject;
    setInterface(other._interface);
    return *this;
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline
typename IlvAbstractCOMInterface<INTERFACE>::CntPtr const&
IlvAbstractCOMInterface<INTERFACE>::getInitializer() const
{
    return _initializeObject;
}

// --------------------------------------------------------------------------
//
// Simple class to query for a specific interface from an IUnknown* or
// from another IlvAbstractCOMInterface.
//
// --------------------------------------------------------------------------
template<class INTERFACE> class IlvCOMInterface
    : public IlvAbstractCOMInterface<INTERFACE>
{
public:
    inline IlvCOMInterface();
    inline IlvCOMInterface(IlvCOMInterface const&);
    inline IlvCOMInterface(INTERFACE* interf);
    inline IlvCOMInterface(IUnknown* iUnknown, REFIID rIID);
    inline IlvCOMInterface(IlvAbstractCOMInterface<INTERFACE>*	inter,
			   REFIID				rIID);
    inline virtual ~IlvCOMInterface();
};

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvCOMInterface<INTERFACE>::IlvCOMInterface()
: IlvAbstractCOMInterface<INTERFACE>()
{
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvCOMInterface<INTERFACE>::IlvCOMInterface(IlvCOMInterface const& interf)
: IlvAbstractCOMInterface<INTERFACE>(interf)
{
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvCOMInterface<INTERFACE>::IlvCOMInterface(INTERFACE* interf)
: IlvAbstractCOMInterface<INTERFACE>()
{
    setInterface(interf);
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvCOMInterface<INTERFACE>::IlvCOMInterface(IUnknown* iUnknown, REFIID rIID)
: IlvAbstractCOMInterface<INTERFACE>()
{
    HRESULT hr = setInterface(iUnknown, rIID);
    if (FAILED(hr)) {
	throw IlvCOMInterfaceError(hr);
    }
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvCOMInterface<INTERFACE>::IlvCOMInterface(
				IlvAbstractCOMInterface<INTERFACE>* inter,
				REFIID rIID)
: IlvAbstractCOMInterface<INTERFACE>(inter.getInitializer())
{
    if (FAILED(setInterface(inter->getInterface(), riid))) {
	throw IlvCOMInterfaceError(hr);
    }
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvCOMInterface<INTERFACE>::~IlvCOMInterface()
{
}

// --------------------------------------------------------------------------
//
// Gets an interface from an CLSID.
//
// --------------------------------------------------------------------------
template<class INTERFACE> class IlvCOMInterfaceFromCLSID
    : public IlvAbstractCOMInterface<INTERFACE>
{
public:
    inline IlvCOMInterfaceFromCLSID(
		REFCLSID	clsID,
		REFIID		rIID,
		DWORD		dwClsContext = CLSCTX_INPROC_SERVER);
    inline virtual ~IlvCOMInterfaceFromCLSID();

private:
    // These two constructors are intentionally not defined.
    IlvCOMInterfaceFromCLSID();
    IlvCOMInterfaceFromCLSID(const IlvCOMInterfaceFromCLSID&);
    // This operator is intentionally not defined.
    IlvCOMInterfaceFromCLSID<INTERFACE>&
	operator=(IlvCOMInterfaceFromCLSID const&);
};

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvCOMInterfaceFromCLSID<INTERFACE>::IlvCOMInterfaceFromCLSID(
					REFCLSID	clsID,
					REFIID		rIID,
					DWORD		dwClsContext)
: IlvAbstractCOMInterface<INTERFACE>(
	IlvCOMLibraryInitialization::GetInstance())
{
    HRESULT hr = CoCreateInstance(clsID,
				  NULL,
				  dwClsContext,
				  rIID,
				  ILVREINTERPRETCAST(void**, &_interface));
    if (FAILED(hr)) {
	_interface = 0;
	throw IlvCOMCreateInstanceError(hr);
    }
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvCOMInterfaceFromCLSID<INTERFACE>::~IlvCOMInterfaceFromCLSID()
{
}

#endif /* __Ilv_Windows_Com_H */
