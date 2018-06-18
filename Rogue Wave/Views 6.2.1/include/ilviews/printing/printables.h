// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/printing/printables.h
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
// Definition of classical inherited classes of IlvPrintable.
// --------------------------------------------------------------------------
#ifndef __Ilv_Printing_Printables_H
#define __Ilv_Printing_Printables_H

#if !defined(__Ilv_Printing_Printable_H)
#include <ilviews/printing/printable.h>
#endif

// --------------------------------------------------------------------------
// Forward declarations.
class IlvContainer;
class IlvGraphic;

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableContainer : public IlvPrintableScalable
{
public:
    IlvPrintableContainer(IlvContainer const*	container,
			  IlvRect const*	scalableArea = 0,
			  IlvRegion const*	clip = 0,
			  IlvTransformer const*	t = 0);
    inline
    IlvContainer const*	getContainer() const { return _container; }

protected:
    virtual IlBoolean	internalPrint(IlvPrintableJob const& job) const;

private:
    IlvContainer const*	_container;
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableText : public IlvPrintable
{
public:
    IlvPrintableText(IlvPalette*	palette,
		     IlString const&	text,
		     IlvPosition	alignment = IlvCenter);
    ~IlvPrintableText();
    virtual IlvRect	getBBox(IlvPrintableJob const& job) const;
    inline IlvPalette*	getPalette() const { return _palette; }
    inline void		setPalette(IlvPalette* palette)
			{
			    palette->lock();
			    _palette->unLock();
			    _palette = palette;
			}
    inline IlString	getText() const { return _text; }
    inline void		setText(IlString const& text) { _text = text; }
    inline IlvPosition	getAlignment() const { return _alignment; }
    inline void		setAlignment(IlvPosition alignment)
			{
			    _alignment = alignment;
			}

protected:
    virtual IlBoolean	internalPrint(IlvPrintableJob const& job) const;
    inline void		modifyText(IlString const& newText) const
			{
			    IL_ACCESSMUTABLE(IlvPrintableText, _text) =
				newText;
			}

private:
    IlvPalette*		_palette;
    IL_MUTABLE IlString	_text;
    IlvPosition		_alignment;
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableFormattedText : public IlvPrintableText
{
public:
    IlvPrintableFormattedText(IlvPalette*	palette,
			      IlString const&	text,
			      IlvPosition	alignment = IlvCenter);
    virtual IlvRect	getBBox(IlvPrintableJob const& job) const;

protected:
    virtual IlBoolean	internalPrint(IlvPrintableJob const& job) const;

private:
    IlString		getActualText(IlvPrintableJob const& job) const;
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableGraphic : public IlvPrintableScalable
{
public:
    IlvPrintableGraphic(IlvGraphic*		graphic,
			IlBoolean		owner = IlTrue,
			IlvRegion const*	clip = 0,
			IlvTransformer const*	t = 0);
    ~IlvPrintableGraphic();
    inline
    IlvGraphic const*	getGraphic() const { return _graphic; }
    void		setGraphic(IlvGraphic* graphic,
				   IlBoolean owner = IlTrue);

protected:
    virtual IlBoolean	internalPrint(IlvPrintableJob const& job) const;

private:
    IlvGraphic*		_graphic;
    IlBoolean		_owner;
};

// --------------------------------------------------------------------------
class ILVPRINTINGEXPORTED IlvPrintableFrame : public IlvPrintable
{
public:
    IlvPrintableFrame(IlvPalette* palette);
    ~IlvPrintableFrame();
    virtual IlvRect	getBBox(IlvPrintableJob const& job) const;
    inline IlvPalette*	getPalette() const { return _palette; }
    inline void		setPalette(IlvPalette* palette)
			{
			    palette->lock();
			    _palette->unLock();
			    _palette = palette;
			}

protected:
    virtual IlBoolean	internalPrint(IlvPrintableJob const& job) const;

private:
    IlvPalette*		_palette;
};

#endif /* __Ilv_Printing_Printables_H */
