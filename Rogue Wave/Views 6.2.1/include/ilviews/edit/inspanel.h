// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/inspanel.h
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
// Declaration of the IlvInspectorPanel class
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Inspanel_H
#define __Ilv_Edit_Inspanel_H

#if !defined(__Ilv_Edit_Macros_H)
#include <ilviews/edit/macros.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Graphics_Label_H)
#include <ilviews/graphics/label.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif

class ILVGDTEXPORTED IlvIFileSelector;
class ILVVWSEXPORTED IlvManager;
class ILVEDTEXPORTED IlvInspector;

// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvInspectorPanel : public IlvDialog
{
public:
    virtual ~IlvInspectorPanel();
    // ____________________________________________________________
    void		load();
    inline IlBoolean	isLoaded() const
			{
			    return (IlBoolean)(_list.getFirst() != 0);
			}
    virtual void	init();
    virtual void	show();
    virtual void	apply();
    virtual void	applyChange(IlvGraphic*);
    virtual void	initFrom(IlvGraphic*) = 0;
    inline IlvManager*	getManager() const   { return _manager; }
    inline void		setManager(IlvManager* mgr) { _manager = mgr; }
    inline const char*	className() const { return _className; }
    // Utilities
    const char*		getTextFieldLabel(const char* name) const;
    void		setTextFieldLabel(const char* name,
					  const char* label);
    void		setTextFieldValue(const char* name, IlInt);
    void		setTextFieldValue(const char* name,
					  IlFloat,
					  const char* format);
    void		setNumberFieldValue(const char* name, IlFloat);
    void		setNumberFieldValue(const char* name, IlInt);
    IlBoolean		getToggleState(const char* name) const;
    void		setToggleState(const char* name, IlBoolean value);
    static IlvIFileSelector*	getFileSelector();

    inline IlvInspector*	getInspector() const { return _inspector; }
    inline void		setInspector(IlvInspector* inspector)
			{
			    _inspector = inspector;
			}

#if defined(WINDOWS)
    static void		setDefaultBackground(IlvColor* color);
    static IlvColor*	getDefaultBackground();
#else  /* !WINDOWS */
    static void		setDefaultBackground(IlvColor* color)
			{
			    _background = color;
			}
    static IlvColor*	getDefaultBackground() { return _background; }
#endif /* !WINDOWS */

protected:
    char*		_className;
    static IlvColor*	_background;
    const char*		_ilvdata;
    const char*		_filename;
    IlvInspector*	_inspector;

    void		setBasicProperties(IlvGraphic*);
    void		getBasicProperties(IlvGraphic*);
    const char*		selectFileName() const;

    IlvInspectorPanel(IlvManager*,
		      const char*   className,
		      const char*   title,
		      const char*   icon,
		      const char*   data,
		      const char*   filename = 0, // if present, overloads data
		      IlvSystemView transientFor = 0);
private:
    IlvManager*		_manager;
};

// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvInspector
{
public:
    IlvInspector();
    virtual ~IlvInspector();
    // ----------------------------------------------------------------------
    virtual void		use(IlvInspectorPanel*);
    virtual void		inspect(IlvGraphic*);
    virtual IlvInspectorPanel*	getPanel(IlvGraphic*) const;
    virtual void		setExclusive(IlBoolean flag);
    inline IlBoolean		isExclusive() const { return _exclusive; }
    inline IlvGadgetContainer*	getCurrentInspector() const { return _current; }

    static IlvBitmap*		getBitmap(IlvDisplay*, const char*);
    static IlvIFileSelector*	getFileSelector() { return _filesel; }
    static void			setIFileSelector(IlvIFileSelector* fsel)
				{
				    _filesel = fsel;
				}

protected:
    IlvArray			_panels;
    IlvGadgetContainer*		_current;
    IlBoolean			_exclusive;
    static IlvIFileSelector*	_filesel;
};

#endif /*  ! __Ilv_Edit_Inspanel_H */
