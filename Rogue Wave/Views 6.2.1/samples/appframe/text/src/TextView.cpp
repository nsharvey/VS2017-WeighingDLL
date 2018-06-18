// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/text/src/TextView.cpp
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
// IlogViews 4 generated source file
// File generated Thu Mar 09 20:27:35 2000
//      by Rogue Wave Views AppFrame Wizard
// --------------------------------------------------------------------------
#include <TextView.h>
#include <TextDocument.h>
#include <ilviews/appframe/command.h>
#include <ilviews/appframe/gadgets/events.h>
#include <ilviews/gadgets/scombo.h>

// --------------------------------------------------------------------------
// TextView methods
// --------------------------------------------------------------------------
IlvDvBeginInterface(TextView)
    InitializeGadget("StyleComboBox", selectFont, IlvScrolledComboBox)
    GadgetNotification("StyleComboBox", IlvGadget::CallbackSymbol(), fontChanged, IlvScrolledComboBox)
    InitializeGadget("SizeComboBox", fillSizes, IlvScrolledComboBox)
    GadgetNotification("SizeComboBox", IlvGadget::CallbackSymbol(), sizeChanged, IlvScrolledComboBox)
    GadgetNotification("SizeComboBox", IlvGadget::FocusOutSymbol(), sizeChanged, IlvScrolledComboBox)
    Action(Bold, toggleBold)
    RefreshAction(Bold, boldUI)
    Action(Italic, toggleItalic)
    RefreshAction(Italic, ItalicUI)
    Action(Underline, toggleUnderline)
    RefreshAction(Underline, underlineUI)
IlvDvEndInterface1(IlvDvTextView)

// --------------------------------------------------------------------------
// Constructor / destructor
TextView::TextView(IlvDisplay* display)
: IlvDvTextView(display)
{
}

// --------------------------------------------------------------------------
TextView::~TextView()
{
}

// --------------------------------------------------------------------------
// Overridables
void
TextView::initializeView()
{
    IlvDvTextView::initializeView();
    
    TextDocument* document = getTextDocument();
    // Add here your initialization code
    document->setText("This is a short sample that illustrates\nhow to insert gadgets within toolbar and \nhow to check states of toolbar items");
    document->setModified(IlvFalse);
}

// --------------------------------------------------------------------------
// Basic properties
TextDocument*
TextView::getTextDocument() const
{
    return (TextDocument*)getDocument();
}

// --------------------------------------------------------------------------
const char*
TextView::getFontFamily() const
{
    IlvFont* font = getFont();
    if (!font)
	return 0;
    const char* family = font->getFamily();
    return family? family : "System";
}

// --------------------------------------------------------------------------
void
TextView::selectFont(IlvScrolledComboBox* cb)
{
    const char* family = getFontFamily();
    IlvUShort newSelection = family? cb->getPosition(family) : (IlvShort)-1;
    if (newSelection != cb->whichSelected())
	cb->setSelected(newSelection);

    getDvApplication()->refreshAction(IlvGetSymbol("SizeCombo"));
}

// --------------------------------------------------------------------------
void
TextView::fontChanged(IlvScrolledComboBox* cb)
{
    IlvFont* font = getFont();
    if (!font)
	return;

    const char* newFamily = cb->getLabel();
    if (!newFamily)
	return;

    IlvFontStyle style =
	(IlvFontStyle)((int)font->getStyle() &
				((int)IlvBoldFontStyle |
				 (int)IlvUnderlinedFontStyle |
				 (int)IlvItalicFontStyle));
    font = getDisplay()->getFont(newFamily,
				 font->getSize(),
				 style);
    if (font) {
	setFont(font);
	reDraw();
    }

    getDvApplication()->refreshAction(IlvGetSymbol("SizeCombo"));
    getDvApplication()->refreshAction(IlvGetSymbol("Bold"));
    getDvApplication()->refreshAction(IlvGetSymbol("Italic"));
    getDvApplication()->refreshAction(IlvGetSymbol("Underline"));
}

// --------------------------------------------------------------------------
void
TextView::fillSizes(IlvScrolledComboBox* cb)
{
    IlString fontFamily = getFontFamily();
    if (_currentSizesFontName.equals(fontFamily))
	return;
    if (!getFontFamily())
	return;

    IlvFont* font = getFont();
    _currentSizesFontName = fontFamily;
    int count    = 0;
    IlvDim* dims = getDisplay()->getFontSizes(getFontFamily(),
					      font->getStyle(),
					      count,
					      font->getFoundary());

    static IlvDim newdims[] =
	{ 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72 };
#if defined(WINDOWS)
    if (count && (dims[0] == 0)) {
	if (count == 1) {
	    dims  = newdims;
	    count = 16;
	} else {
	    ++dims;
	    --count;
	}
    }
#else  /* !WINDOWS */
    if (count && (dims[0] == 0)) {
	++dims;
	--count;
    }
#endif /* !WINDOWS */
    
    cb->empty();

    if (!count) {
	count = sizeof(newdims) / sizeof(newdims[0]);
	dims = newdims;
    }
    cb->initReDrawItems();
    IlUShort selection = (IlUShort)-1;
    int  shortestDiff = -1;
    for (int i = 0; i < count; ++i) {
	int diff = (int)dims[i] - (int)font->getSize();
	if ((shortestDiff == -1) || 
	        ((diff < 0? -diff : diff) < 
	             (shortestDiff < 0? -shortestDiff : shortestDiff))) {
	    shortestDiff = diff;
	    selection = (IlUShort)i;
	}
	IlString dimName(dims[i]);
	cb->addLabel(IL_CAST(char const*, dimName),
		     IlCastIlUIntToIlAny(dims[i]));
    }
    cb->setSelected(selection);
    
    // If no size for the selected font could fit with the requiered size
    // (usually size that was selected for a previous selected family font)
    // then give to the current font the possible size that fit the best
    // with the previous selected size.
    if (shortestDiff) {
	font = getDisplay()->getFont(getFontFamily(),
				     IL_CAST(IlvFontSize, dims[selection]),
				     font->getStyle());
	if (font) {
	    setFont(font);
	    reDraw();
	}
    }
    cb->reDrawItems();
}

// --------------------------------------------------------------------------
void
TextView::sizeChanged(IlvScrolledComboBox* cb)
{
    IlvFont* font = getFont();
    if (!font)
	return;

    IlUShort selection = cb->getSelectionIndex();
    if (selection == (IlUShort)-1)
	return;
    IlvFontSize size =
	IL_CAST(IlvFontSize,
		IlCastIlAnyToIlUIntPtr(cb->getItemData(selection)));

    font = getDisplay()->getFont(getFontFamily(),
				 size,
				 font->getStyle());
    if (font) {
	setFont(font);
	reDraw();
    }
}

// --------------------------------------------------------------------------
void
TextView::toggleBold()
{
    toggleFontStyle(IlvBoldFontStyle);
    getDvApplication()->refreshAction(IlvGetSymbol("Bold"));
}

// --------------------------------------------------------------------------
void
TextView::toggleItalic()
{
    toggleFontStyle(IlvItalicFontStyle);
    getDvApplication()->refreshAction(IlvGetSymbol("Italic"));
}

// --------------------------------------------------------------------------
void
TextView::toggleUnderline()
{
    toggleFontStyle(IlvUnderlinedFontStyle);
    getDvApplication()->refreshAction(IlvGetSymbol("Underline"));
}

// --------------------------------------------------------------------------
void
TextView::toggleFontStyle(IlvFontStyle toggleStyle)
{
    IlvFont* font = getFont();
    if (!font)
	return;
    IlvFontStyle style = font->getStyle();
    if (style & IlvSystemStyle)
	return;
    if (style & toggleStyle)
	style = (IlvFontStyle) ((int)style ^ (int)toggleStyle);
    else
	style = (IlvFontStyle) ((int)style | (int)toggleStyle);

    font = getDisplay()->getFont(font->getFamily(),
				 font->getSize(),
				 style);
    if (font) {
	setFont(font);
	reDraw();
    }
}

// --------------------------------------------------------------------------
void
TextView::boldUI(IlvDvActionDescriptor* desc)
{
    fontStyleUI(desc, IlvBoldFontStyle);
}

// --------------------------------------------------------------------------
void
TextView::ItalicUI(IlvDvActionDescriptor* desc)
{
    fontStyleUI(desc, IlvItalicFontStyle);
}

// --------------------------------------------------------------------------
void
TextView::underlineUI(IlvDvActionDescriptor* desc)
{
    fontStyleUI(desc, IlvUnderlinedFontStyle);
}

// --------------------------------------------------------------------------
void
TextView::fontStyleUI(IlvDvActionDescriptor* desc,
		      IlvFontStyle fontStyle)
{
    IlvFont* font = getFont();
    if (!font) {
	desc->setChecked(IlFalse);
	desc->setValid(IlFalse);
	return;
    }
    IlvFontStyle style = font->getStyle();
    if (style & IlvSystemStyle) {
	desc->setChecked(IlFalse);
	desc->setValid(IlFalse);
	return;
    }
    desc->setValid(IlTrue);
    desc->setChecked(style & fontStyle? IlTrue : IlFalse);
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterGadgetViewClass(TextView, IlvDvTextView);

IL_BEGINMODULEINITDEF(TextView)
    IlvDvPostRegisterGadgetViewClass(TextView, IlvDvTextView);
IL_ENDMODULEINITDEF(TextView)

#if !defined(ILVBUILDLIBS)
static int TextView_ini = (IL_MODINIT(TextView)(), 0);
#endif
