// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/windows/comvadap.h
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
// Definitions of a view adapter for ActiveX controls.
// --------------------------------------------------------------------------
#ifndef __Ilv_Windows_Comvadap_H
#define __Ilv_Windows_Comvadap_H

#if !defined(__Ilv_Windows_Atl_H)
#  include <ilviews/windows/atl.h>
#endif /* !__Ilv_Windows_Atl_H */
#if !defined(__Ilv_Base_View_H)
#  include <ilviews/base/view.h>
#endif /* !__Ilv_Base_View_H */

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4251 )
#endif /* _MSC_VER */

// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvViewCOMAdapter
: public IlvView
{
public:
    IlvViewCOMAdapter(char const*	identifier,
		      IlvAbstractView*	parent,
		      IlvRect const&	size,
		      IlBoolean		visible = IlTrue);
    IlvViewCOMAdapter(char const*	identifier,
		      IlvDisplay*	display,
		      char const*	name,
		      char const*	title,
		      IlvRect const&	size,
		      IlBoolean		visible = IlTrue);
    IlvViewCOMAdapter(char const*	identifier,
		      IlvDisplay*	display,
		      char const*	name,
		      char const*	title,
		      IlvRect const&	size,
		      IlUInt		properties,
		      IlBoolean		visible      = IlTrue,
		      IlvSystemView	transientFor = 0);
    HRESULT queryInterface(REFIID iid, void** ppvObject);
    inline IOleObject* getOleInterface() const
	{
	    return _control;
	}
protected:
    void init();

private:
    // These two functions are intentionally not defined.
    IlvViewCOMAdapter();
    IlvViewCOMAdapter(IlvViewCOMAdapter const&);

    static void Resize(IlvView* view, IlvRect& size, IlAny arg);
    IlvATLInterface<IOleObject> _control;
};

#if defined(_MSC_VER)
#pragma warning( pop )
#endif /* _MSC_VER */

#endif /* __Ilv_Windows_Comvadap_H */
