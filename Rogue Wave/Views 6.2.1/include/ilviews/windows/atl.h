// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/windows/atl.h
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
// Declaration of classes that encapsulate ATL stuff.
// --------------------------------------------------------------------------
#ifndef __Ilv_Windows_Atl_H
#define __Ilv_Windows_Atl_H

#if !defined(__Ilv_Windows_Com_H)
#  include <ilviews/windows/com.h>
#endif /* !__Ilv_WindowsCOM_H */

// --------------------------------------------------------------------------
//
// Exception classes.
//
// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvATLLibraryInitializationError
    : public IlvCOMError
{
public:
    inline
    IlvATLLibraryInitializationError(HRESULT hr) : IlvCOMError(hr) {}

};

// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvATLInterfaceError
    : public IlvCOMError
{
public:
    inline IlvATLInterfaceError(HRESULT hr) : IlvCOMError(hr) {}
};

// --------------------------------------------------------------------------
//
// Initialization of the ATL library.
//
// --------------------------------------------------------------------------
class IlvDisplay;
class IlvView;
class IlvRect;

class ILVCOMEXPORTED IlvATLModuleInitialization
    : public IlvAbstractLibraryInitialization
{
    friend CntPtr;
public:
    // May throw an IlvATLLibraryInitializationError
    virtual HWND	createControl(char const*	identifier,
				      IlvRect const&	bbox,
				      REFIID		rIID,
				      void**		interf,
				      IlvView*		parent = 0) const;
    static CntPtr	GetInstance(IlvDisplay* display);
    inline HINSTANCE	getHInstance() const { return _hInstance; }


protected:
    IlvATLModuleInitialization(IlvDisplay* display);
    virtual ~IlvATLModuleInitialization();
    static void DestroyCallBack(IlvView*, IlAny);

private:
    friend int IlvDynamicATLInitialization();
    friend int IlvStaticATLInitialization();

    void		initParent();

    static IlvATLModuleInitialization*	_Instance;
    static long*			_InstanceCounter;
    IlvView*				_parent;
    HINSTANCE				_hInstance;
    IlvDisplay*				_display;
};

// --------------------------------------------------------------------------
//
// Gets an interface using ATLHOST.
//
// --------------------------------------------------------------------------
template<class INTERFACE> class ILVCOMEXPORTED IlvATLInterface
    : public IlvAbstractCOMInterface<INTERFACE>
{
public:
    inline IlvATLInterface(REFIID		rIID,
			   char const*		identifier,
			   IlvDisplay*		display,
			   IlvRect const&	bbox,
			   IlvView*		parent = 0);
    inline HWND getHWnd() const;

private:
    // These two constructors are intentionally not defined.
    IlvATLInterface();
    IlvATLInterface(const IlvATLInterface&);
    // This operator is intentionally not defined.
    IlvATLInterface<INTERFACE>& operator=(IlvATLInterface const&);

    HWND _hWnd;
};

// --------------------------------------------------------------------------
template<class INTERFACE> inline
IlvATLInterface<INTERFACE>::IlvATLInterface(REFIID		rIID,
					    char const*		identifier,
					    IlvDisplay*		display,
					    IlvRect const&	bbox,
					    IlvView*		parent)
: IlvAbstractCOMInterface<INTERFACE>(IlvATLModuleInitialization
					::GetInstance(display)),
    _hWnd(0)
{
    IlvATLModuleInitialization* initObj =
	ILVDYNAMICCAST(IlvATLModuleInitialization*, getInitializer().get());
    INTERFACE* interf;
    _hWnd = initObj->createControl(identifier,
				   bbox,
				   rIID,
				   ILVREINTERPRETCAST(void**, &interf),
				   parent);
    setInterface(interf);
}

// --------------------------------------------------------------------------
template<class INTERFACE> inline HWND
IlvATLInterface<INTERFACE>::getHWnd() const
{
    return _hWnd;
}

#endif /* __Ilv_Windows_Atl_H */
