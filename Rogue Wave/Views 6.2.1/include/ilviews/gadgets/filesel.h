// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/gadgets/filesel.h
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
// Declaration of the classes IlvIFileSelector and IlvIBitmapSelector
// Defined in library ilvgadgt
// --------------------------------------------------------------------------
#ifndef __Ilv_Gadgets_Filesel_H
#define __Ilv_Gadgets_Filesel_H

#if !defined(__Ilv_Gadgets_Idialog_H)
#  include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Contain_Inter_H)
#  include <ilviews/contain/inter.h>
#endif
#if !defined(__Ilv_Graphics_Label_H)
#  include <ilviews/graphics/label.h>
#endif
#if !defined(__Ilv_Graphics_Rectangl_H)
#  include <ilviews/graphics/rectangl.h>
#endif
#if !defined(__Ilv_Graphics_Relfline_H)
#  include <ilviews/graphics/relfline.h>
#endif
#if !defined(__Ilv_Gadgets_Button_H)
#  include <ilviews/gadgets/button.h>
#endif
#if !defined(__Ilv_Gadgets_Slist_H)
#  include <ilviews/gadgets/slist.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#  include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Graphics_Attach_H)
#  include <ilviews/graphics/attach.h>
#endif
#if !defined(__Ilv_Graphics_Icon_H)
#  include <ilviews/graphics/icon.h>
#endif
#if !defined(__Ilv_Gadgets_Optmenu_H)
#  include <ilviews/gadgets/optmenu.h>
#endif
#if !defined(__Ilv_Base_Pathname_H)
#  include <ilviews/base/pathname.h>
#endif
#if !defined(__Ilv_Gadgets_Macrosadv_H)
#  include <ilviews/gadgets/macrosadv.h>
#endif
#if !defined(__Ilv_Util_Fseltype_H)
#  include <ilviews/util/fseltype.h>
#endif

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvIFileSelector : public IlvDialog
{
public:

    IlvIFileSelector(IlvDisplay*   display,
                     const char*   dir          = 0,
                     const char*   filter       = 0,
                     const char*   fileordata   = 0,
		     IlvSystemView transientFor = 0,
		     IlUInt	   properties   = 0);

    ~IlvIFileSelector();
    // ____________________________________________________________
    virtual void	show();

    const char*		getFilter() const;

    void		setFilter(const char* filter,
				  IlBoolean reset = IlFalse);

    void		setLabel(const char* label);
    void		setString(const char* label);

    void		reset();

    inline void		setDirectory(const char* dir,
				     IlBoolean reset = IlFalse)
			{
			    IlPathName temp;
			    temp.setDirName(dir);
			    setDirectory(temp, reset);
			}
    void		setDirectory(const IlPathName&,
				     IlBoolean reset = IlFalse);

    void		setFilterPath(const char* path, IlBoolean = IlFalse);

    const char*		getResult() const;

    const char*		getDirectory() const;

    const char*		get(IlBoolean grab = IlFalse, IlvCursor* cursor = 0);

    virtual void	apply();
    virtual void	setResult(const char* text=0);
    virtual IlBoolean	handleKeyDown(IlvEvent&);
    virtual IlBoolean	handleKeyUp(IlvEvent&);
    virtual void	writtenChoice();
    void		setOptions(IlUShort		nOptions,
				   const char* const*	filters,
				   const char* const*	names = 0);
    void		setOption(IlUShort);
    IlUShort		getOption() const;
    inline const char*	getFilter(IlUShort i) const { return _filters[i]; }
    inline
    IlvFileSelectorType	getType() const { return _type; }
    inline void		setType(IlvFileSelectorType type) { _type = type; }
    inline IlBoolean	needsInputContext() const { return _needsInputContext;}
    virtual void	setNeedsInputContext(IlBoolean);

protected:
    char**		_filters;
    IlPathName		_filterPath;	// basename is the filter.
    IlvFileSelectorType _type;
    IlBoolean		_needsInputContext;
};

// --------------------------------------------------------------------------
class ILVADVGDTEXPORTED IlvIBitmapSelector : public IlvIFileSelector
{
public:
    IlvIBitmapSelector(IlvDisplay*,
                       const char*   dir          = 0,
                       const char*   filter       = 0,
                       const char*   fileordata   = 0,
		       IlvSystemView transientFor = 0);

    virtual void	setResult(const char* text=0);
    virtual void	writtenChoice();

private:
    IlBoolean		_showBitmap;
};

#endif /* !__Ilv_Gadgets_Filesel_H */
