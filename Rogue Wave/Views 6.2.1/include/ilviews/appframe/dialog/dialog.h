// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/dialog/dialog.h
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
// Declaration of the IlvDvDialog class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Dialog_Dialog_H)
#define __Ilv_Appframe_Dialog_Dialog_H

#if !defined(__Ilv_Gadgets_Idialog_H)
#include <ilviews/gadgets/idialog.h>
#endif
#if !defined(__Ilv_Appframe_Dialog_Inspect_H)
#include <ilviews/appframe/dialog/inspect.h>
#endif

class IlvSplitterGadget;

// --------------------------------------------------------------------------
// IlvDvDialog class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDialog : public IlvDialog, public IlvDvInspector
{
    IlvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvDialog(IlvDisplay*,
		const char*   name,
	        const char*   title,
		const char*   filename,
		IlvDvOptions* options = 0,
		IlUInt        properties = 0,
		IlvSystemView transientFor = 0);

    IlvDvDialog(IlvDisplay*,
		const char*   name,
	        const char*   title,
		const IlvRect&,
		IlvDvOptions* options = 0,
		IlUInt        properties = 0,
		IlvSystemView transientFor = 0);
    virtual ~IlvDvDialog();

    // ----------------------------------------------------------------------
    // Main overridables
    void		apply();
    void		close();
    virtual void	initialize();

    // ----------------------------------------------------------------------
    virtual ApplyMode	getApplyMode() const;
    IlvGraphic*		getGraphic(const char*, IlvGraphicHolder** = 0) const;
    void		setGadgetSensitive(IlvGadget*, IlBoolean sensitive);
    void		setGadgetSensitive(const char*, IlBoolean sensitive);
    void		setGadgetText(const char* gadgetName,
				      const char* text);
    const char*		getGadgetText(const char* gadgetName) const;
    void		setGadgetEditable(const char* gadgetName,
					  IlBoolean   editable);

    IlvSplitterGadget*	addSplitter(IlvDirection,
				    IlUInt ndx,
				    IlUInt from,
				    IlUInt to,
				    IlvDim size = (IlvDim)6,
				    IlvGadgetContainer* = 0);

    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*	_OptionsDialogSymbol;

protected:
    ApplyMode		_mode;
    IlvRect		_dlgRect;
    IlvDvOptions*	_options;
    IlArray		_splitters;

    const IlvDvClass*	getClass(const char*) const;
    const IlvDvClass*	getClass(const IlSymbol*) const;

    virtual IlvDvOptions*	getOptions() const;
    inline void		setOptions(IlvDvOptions* options)
			{
			    _options = options;
			}
    void		basicInitialize();
    virtual void	doUpdateModified();
    void		updateGadget(const IlSymbol*);

    virtual IlvButton*	getApplyButton() const;
    virtual IlvButton*	getUndoButton() const;
    virtual IlvButton*	getResetAllButton() const;
    virtual IlvButton*	getCloseButton() const;

    // Options management
    virtual const char*	getOptionsName() const;
    virtual void	readOptions();
    virtual void	readFromVar(IlvDvNodeValue*);
    virtual void	updateOptions();
    virtual void	updateVariable(IlvDvNodeValue*);


public:
    static void		UndoCallback(IlvGraphic*, IlAny);
    static void		ResetAllCallback(IlvGraphic*, IlAny);
    static void		ApplyCallback(IlvGraphic*, IlAny);
    static void		CloseCallback(IlvGraphic*, IlAny);
};

// --------------------------------------------------------------------------
// class IlvDvNotebookPage
// --------------------------------------------------------------------------
#if !defined(__Ilv_Gadgets_Notebook_H)
#include <ilviews/gadgets/notebook.h>
#endif
class ILVDVCLASS IlvDvNotebookPage: public IlvNotebookPage
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvNotebookPage(IlvNotebook* notebook,
		      const char*  label,
		      IlvBitmap*   bitmap,
		      IlBoolean    transparent,
		      const char*  filename);
    virtual ~IlvDvNotebookPage();

    // ----------------------------------------------------------------------
    virtual IlvView*	createView(IlvAbstractView* parent,
				   const IlvRect&   size);

    inline void		getInitialSize(IlvDim& w, IlvDim& h)const
			{
			    w = _initialWidth;
			    h = _initialHeight;
			}

protected:
    IlvDim		_initialWidth;
    IlvDim		_initialHeight;
};

// --------------------------------------------------------------------------
// class IlvDvPropertySheet
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvPropertySheet : public IlvDvDialog
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvPropertySheet(IlvDisplay*,
		       const char*   name,
		       const char*   title,
		       IlvDvOptions* options = 0,
		       IlvSystemView transientFor = 0,
		       ApplyMode     applyMode = Direct,
		       const char*   filename = 0,
		       IlUInt        properties = 0);
    virtual ~IlvDvPropertySheet();

    // ----------------------------------------------------------------------
    virtual void initialize();
    IlvNotebookPage*	addPage(const char* title,
				const char* filename,
				IlUShort    idx = (IlUShort)-1,
				IlvBitmap*  bitmap = 0,
				IlBoolean   transparent = IlTrue);

    void		addSplitterPage(int nbookPageIndex = -1,
					IlvDirection = IlvHorizontal,
					IlUInt ndx = 1,
					IlUInt from = 0,
					IlUInt to = (IlUInt)-1,
					IlvDim size = (IlvDim)6);

    inline IlBoolean	isSavingLastSelectedPage() const
			{
			    return _saveLastSelectedPage;
			}
    inline void		setSavingLastSelectedPage(IlBoolean b = IlTrue)
			{
			    _saveLastSelectedPage = b;
			}
    // ----------------------------------------------------------------------
    static IlvPos	_DefaultNotebookXMargin;
    static IlvPos	_DefaultNotebookYMargin;
    static IlvPos	_DefaultButtonSpacing;
    static IlvPos	_DefaultButtonBottomMargin;
    static IlvPos	_DefaultButtonToLineMargin;
    static IlvPos	_DefaultLineToNotebookMargin;

protected:
    IlvNotebook*	_notebook;
    IlvPoint		_notebookOffset;
    IlvPoint		_notebookMargins;
    int			_selectedPage;
    IlBoolean		_saveLastSelectedPage;

    virtual void	connectHolder(IlvGraphicHolder* holder);
    virtual void	readFromVar(IlvDvNodeValue*);
    virtual void	updateVariable(IlvDvNodeValue*);
    void		getPagesMaxSize(IlvDim& w, IlvDim& h) const;
    void		resizeDialog();
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(dialog)
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Dialog_Dialog_H */
