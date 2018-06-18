// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/graphics/adapter.h
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
// Declaration of the IlvGraphicAdapter class and some auxiliary functions.
// --------------------------------------------------------------------------
#ifndef __Ilv_Graphics_Adapter_H
#define __Ilv_Graphics_Adapter_H

#if !defined(__Ilv_Base_Graphic_H)
#include <ilviews/base/graphic.h>
#endif /* !__Ilv_Base_Graphic_H */
#if !defined(__Ilv_Util_Refcount_H)
#include <ilviews/util/refcount.h>
#endif /* !__Ilv_Util_Refcount_H */

#if !defined(ILVSTD)
#include <fstream.h>
#endif /* !ILVSTD */

// --------------------------------------------------------------------------
template<class OBJECT> void
IlvWrite(IlvOwnership<OBJECT>&	ownership,
	 IlvOutputFile&		os,
	 IlvReferenceStreamer&	streamer)
{
    os.getStream() << (int)ownership.isOwner() << IlvSpc();
    os.writeReference(streamer, ownership.get());
    os.getStream() << IlvSpc();
}

// --------------------------------------------------------------------------
template<class OBJECT> IlvRefCountPtr<IlvOwnership<OBJECT> >
IlvRead(IlvInputFile& is, IlvReferenceStreamer& streamer)
{
    int owner;
    is.getStream() >> owner;
    return IlvOwnership<OBJECT>::Factory(ILVCAST(OBJECT*,
						 is.readReference(streamer)),
					 owner ? IlTrue : IlFalse);
}

// --------------------------------------------------------------------------
template <class ADAPTEE>
class IlvGraphicAdapter : public IlvGraphic
{
public:
    IlvGraphicAdapter(ADAPTEE* obj, IlBoolean owner = IlFalse)
	: IlvGraphic(),
	  _owner(IlvOwnership<ADAPTEE>::Factory(obj, owner))
    {}
    virtual ~IlvGraphicAdapter() = 0;

    //
    // ACCESSORS.
    //

    // Specific functions
    inline IlBoolean	isOwner() const 
			{
			    return _owner.get()->isOwner();
			}

    inline
    ADAPTEE* const	getAdaptee() const { return _owner.get()->get(); }

    // Member functions inherited from IlvGraphic.
    /*
       The following member functions will have to be defined :
    virtual void boundingBox(IlvRect& rect, const IlvTransformer* t = 0) const
    virtual IlBoolean contains(const IlvPoint&		p,
				const IlvPoint&		tp,
				const IlvTransformer*	t = 0) const;
    virtual void draw(IlvPort*				dst,
		      const IlvTransformer*		t = 0,
		      const IlvRegion*			clip = 0) const;
    */

    /*
       The following member function is likely to be defined :
    virtual void drawPalette(const IlvPalette*		pal,
			     IlvPort*			dst,
			     const IlvTransformer*	t = 0,
			     const IlvRegion*		clip = 0) const;
    */
    virtual IlBoolean	handleEvent(IlvEvent& event,
				    const IlvTransformer* t = 0) const = 0;

    virtual void	write(IlvOutputFile& os) const = 0;

    //
    // MODIFIERS.
    //

    // Specific functions
    inline void		setAdaptee(ADAPTEE* adaptee, IlBoolean owner)
			{
			    beforeSetAdaptee();
			    _owner = IlvOwnership<ADAPTEE>::Factory(adaptee,
								    owner);
			    afterSetAdaptee();
			}

    // Member functions inherited from IlvGraphic.
    /*
       The following member functions will have to be defined :
    virtual void applyTransform(const IlvTransformer* t);
    */

    /*
       The following member functions are likely to be defined :
    virtual void setBackground(IlvColor* c);
    virtual void setForeground(IlvColor* c);
    virtual void setFont(IlvFont* f);
    virtual void setColorPattern(IlvColorPattern* b);
    virtual void setPattern(IlvPattern* p);
    virtual void setGradientPattern(IlvGradientPattern* g);
    virtual void setMode(IlvDrawMode m);
    virtual void setArcMode(IlvArcMode m);
    virtual void setFillRule(IlvFillRule m);
    virtual void setFillStyle(IlvFillStyle f);
    virtual void setLineStyle(IlvLineStyle* style);
    virtual void setLineWidth(IlUShort width);
    virtual void setOverwrite(IlBoolean overwrite);
    virtual void setAlpha(IlvIntensity alpha);
    virtual void setAntialiasingMode(IlvAntialiasingMode mode);
    virtual IlBoolean zoomable() const;
    virtual void setPalette(IlvPalette* pal);
    virtual void print(ILVSTDPREF ostream&, int level = 0) const;
    */
    DeclareIOConstructors(IlvGraphicAdapter);

protected:
    IlvGraphicAdapter() : IlvGraphic(), _owner() {}
    virtual void	writeAdaptee(IlvOutputFile& os) const = 0;
    virtual void	beforeSetAdaptee() {}
    virtual void	afterSetAdaptee() {}
    virtual
    IlvReferenceStreamer* factory() const = 0;
    inline void		setAdaptee(const IlvRefCountPtr<IlvOwnership<ADAPTEE> >& other)
			{
			    _owner = other;
			}

private:
    IlvRefCountPtr<IlvOwnership<ADAPTEE> > _owner;
};

// --------------------------------------------------------------------------
template<class ADAPTEE> inline
IlvGraphicAdapter<ADAPTEE>::~IlvGraphicAdapter()
{
    // The deletion of the adaptee is done by the IlvRefCountPtr if needed.
}

// --------------------------------------------------------------------------
template<class ADAPTEE> inline void
IlvGraphicAdapter<ADAPTEE>::write(IlvOutputFile& os) const
{
    IlvReferenceStreamer* streamer = factory();
    IlvWrite(*_owner, os, *streamer);
    delete streamer;
    // The derived class must save the specific data after having
    // called this function.
}

// --------------------------------------------------------------------------
template<class ADAPTEE> inline
IlvGraphicAdapter<ADAPTEE>::IlvGraphicAdapter(
		IlvGraphicAdapter<ADAPTEE> const& src)
: IlvGraphic(src),
  _owner(src._owner)
{
}

// --------------------------------------------------------------------------
template<class ADAPTEE> inline
IlvGraphicAdapter<ADAPTEE> ::IlvGraphicAdapter(IlvInputFile& is, IlvPalette*)
    : IlvGraphic(),
      _owner(0)
{
    // The inherited class must read the adaptee.
}

// --------------------------------------------------------------------------
#define IlvRegisterGraphicAdapterClass(classname, adaptee)	\
IlvPredefinedIOMembers(classname);				\
IlvRegisterClass(classname, IlvGraphic);			\
IlHashTable* IlvOwnership<adaptee>::_Hash = 0

#define IlvPreRegisterGraphicAdapterClass(classname, adaptee)	\
IlvPredefinedIOMembers(classname);				\
IlvPreRegisterClass(classname);					\
IlHashTable* IlvOwnership<adaptee>::_Hash = 0

#endif /* !__Ilv_Graphics_Adapter_H */
