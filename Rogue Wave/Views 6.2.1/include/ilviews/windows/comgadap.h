// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/windows/comgadap.h
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
// Definitions of a graphic adapter for ActiveX controls.
// --------------------------------------------------------------------------
#ifndef __Ilv_Windows_Comgadap_H
#define __Ilv_Windows_Comgadap_H

#if !defined(__Ilv_Windows_Atl_H)
#  include <ilviews/windows/atl.h>
#endif /* !__Ilv_WindowsATL_H */
#if !defined(__Ilv_Graphics_Adapter_H)
#  include <ilviews/graphics/adapter.h>
#endif /* !__Ilv_Graphics_Adapter_H */
#if !defined(__Ilv_Base_String_H)
#  include <ilviews/base/string.h>
#endif /* !__Ilv_Base_String_H */

#if defined(_MSC_VER)
#if defined(IL_DLL)
#pragma warning( disable : 4661 )
#endif /* IL_DLL */
#pragma warning( push )
#pragma warning( disable : 4251 4275 )
#endif /* _MSC_VER */

class IlvGraphicCOMAdapter;
class IlvCOMGraphicFacadeAccessorsMap;
interface IMyAdviseSink;

// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvCOMGraphicFacade
{
    friend IMyAdviseSink;
public:
    IlvCOMGraphicFacade(IlString const&	identifier,
			IlvDisplay*	display,
			IlvRect const&	bbox);
    virtual ~IlvCOMGraphicFacade();

    inline IlvDisplay*		getDisplay() const
	{
	    return _bitmap->getDisplay();
	}
    inline IOleObject*	getOleInterface() const
	{
	    return _IOleObject;
	}
    void		refresh();
    inline void		subscribe(IlvGraphicCOMAdapter* adapter)
	{
	    _subscribers.append(adapter);
	}
    inline void		unsubscribe(IlvGraphicCOMAdapter* adapter)
	{
	    _subscribers.remove(adapter);
	    if (adapter == _master) {
		_master = 0;
	    }
	}
    HRESULT		queryInterface(REFIID iid, void** ppvObject) const;

    virtual void	boundingBox(IlvRect& bbox,
				    IlvTransformer const* t = 0) const;
    // The point is in absolute Rogue Wave Views coordinates.
    // The transformer is used to compute in ActiveX coordinates.
    virtual IlBoolean	contains(IlvPoint const& p,
				 IlvTransformer const& t) const;
    virtual void	draw(IlvPort*			port,
			     IlvTransformer const&	t,
			     IlvRegion const*		clip) const;
    virtual IlBoolean	handleEvent(IlvEvent const&	 event,
				    IlvTransformer const& t);
    virtual void	write(IlvOutputFile& os) const;
    IlvCOMGraphicFacadeAccessorsMap*	getAccessorsMap();
    inline IlBoolean	isMaster(IlvGraphicCOMAdapter const& adapter) const
	{
	    return &adapter == _master;
	}
    inline IlvGraphicCOMAdapter* getMaster() const
	{
	    return _master;
	}
    inline void		setMaster(IlvGraphicCOMAdapter* newMaster,
				  IlBoolean update = IlTrue)
	{
	    _master = newMaster;
	    if (update && _master) {
		resize(*_master);
	    }
	}
    void		resize(IlvGraphicCOMAdapter const& adapter);

    static IlvCOMGraphicFacade*
			Read(IlvInputFile& is,
			     IlvGraphicCOMAdapter const* const adapter);

private:
    // These two functions are intentionally not defined.
    IlvCOMGraphicFacade(IlvCOMGraphicFacade const&);
    IlvCOMGraphicFacade const& operator=(IlvCOMGraphicFacade const&);

    IlvATLInterface<IOleObject>		_IOleObject;
    IlvCOMInterface<IViewObject>	_IViewObject;
    IlString				_identifier;
    IlvRect				_bbox;
    IlvBitmap*				_bitmap;
    IlList				_subscribers;
    IMyAdviseSink*			_sink;
    IlvCOMGraphicFacadeAccessorsMap*	_accessorsMap;
    IlvGraphicCOMAdapter*		_master;
};

// --------------------------------------------------------------------------
#if defined(IL_DLL)
template class ILVCOMEXPORTED IlvOwnership<IlvCOMGraphicFacade, 7>;
template class ILVCOMEXPORTED
    IlvRefCountPtr<IlvOwnership<IlvCOMGraphicFacade, 7> >;
template class ILVCOMEXPORTED IlvGraphicAdapter<IlvCOMGraphicFacade>;
#endif /* IL_DLL */

// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvGraphicCOMAdapter
: public IlvGraphicAdapter<IlvCOMGraphicFacade>
{
    friend class IlvCOMGraphicFacade;
public:
    IlvGraphicCOMAdapter(IlvRect const&	bbox,
			 char const*	identifier,
			 IlvDisplay*	display);
    IlvGraphicCOMAdapter(IlvCOMGraphicFacade*	facade,
			 IlvRect const&		bbox,
			 IlBoolean		owner = IlTrue);
    virtual ~IlvGraphicCOMAdapter();
    virtual void	boundingBox(IlvRect& rect,
				    IlvTransformer const* t = 0) const;
    IlBoolean		contains(IlvPoint const& p,
				 IlvPoint const& tp,
				 IlvTransformer const* t = 0) const;
    virtual void	draw(IlvPort* dst,
			     IlvTransformer const* t = 0,
			     IlvRegion const* clip = 0) const;
    virtual void	applyTransform(IlvTransformer const* t);
    virtual IlBoolean	handleEvent(IlvEvent& event,
				    IlvTransformer const* t = 0) const;
    virtual void	writeAdaptee(IlvOutputFile& os) const;
    virtual void	setOverwrite(IlBoolean mode);
    virtual void	setMode(IlvDrawMode mode);
    virtual void	setPalette(IlvPalette* pal);
    inline IlvPalette*	getPalette() const
	{
	    return _palette;
	}
    inline HRESULT	queryInterface(REFIID iid, void** ppvObject) const
	{
	    return getAdaptee()->queryInterface(iid, ppvObject);
	}
    virtual IlvAccessorsMap*	getAccessorsMap() const;
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;
    virtual void	getAccessors(const IlSymbol* const** accessors,
				     const IlvValueTypeClass* const** types,
				     IlUInt& count) const;
    virtual IlvValue&	queryValue(IlvValue& val) const;
    virtual IlBoolean	applyValue(const IlvValue& val);

    DeclareLazyTypeInfo();
    DeclareIOConstructors(IlvGraphicCOMAdapter);

    char const*		getDefaultInteractor() const;

protected:
    virtual IlvReferenceStreamer*	factory() const;

    IlvTransformer	_t;

private:
    void		computeTransformer(IlvRect const& bbox);

    IlvPalette*		_palette;
};

// --------------------------------------------------------------------------
class ILVCOMEXPORTED IlvCOMGraphicFacadeDrawError : public IlvCOMError
{
public:
    IlvCOMGraphicFacadeDrawError(HRESULT hr)
    : IlvCOMError(hr) {}
};

ILVCOMMODULEINIT(graphiccomadapter);

#if defined(_MSC_VER)
#pragma warning( pop )
#endif /* _MSC_VER */

#endif /* __Ilv_Windows_Comgadap_H */
