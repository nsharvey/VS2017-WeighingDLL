// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/document.h
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
// Declaration of the IlvDvDocument class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Document_H)
#define __Ilv_Appframe_Document_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Appframe_Clssinfo_H)
#include <ilviews/appframe/clssinfo.h>
#endif
#if !defined(__Ilv_Base_Pathname_H)
#include <ilviews/base/pathname.h>
#endif
#if !defined(__Ilv_Appframe_Interf_H)
#include <ilviews/appframe/interf.h>
#endif
#if !defined(__Ilv_Appframe_Command_H)
#include <ilviews/appframe/command.h>
#endif
#if !defined(__Ilv_Appframe_App_H)
#include <ilviews/appframe/app.h>
#endif
#if !defined(__Ilv_Appframe_Stream_H)
#include <ilviews/appframe/stream.h>
#endif
#if !defined(__Ilv_Util_Proplist_H)
#include <ilviews/util/proplist.h>
#endif

#if defined(ILVSTD)
#include <ctime>
#else
#include <time.h>
#endif

class IlvDvStream;
class IlvDvDocViewInterface;
class IlvDvDocTemplate;
class IlvDvDocManager;
class IlvDvViewContainerInterface;
class IlvDvApplication;
// --------------------------------------------------------------------------
// IlvDvDocument class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDocument
    : public IlvDvSerializable, public IlvDvInterface
{
    IlvDvDeclareDynCreate();
public:
    IlvDvDocument();
    virtual ~IlvDvDocument();

    // ----------------------------------------------------------------------
    // Initialization / close
    virtual void	initialize();
    virtual IlBoolean	initializeDocument(IlAny userArg = 0);

    virtual IlBoolean	close(IlBoolean askForSaving = IlTrue);
    virtual void	clean();
    virtual void	activated(IlBoolean active = IlTrue);

    // ----------------------------------------------------------------------
    // DocumentView management
    IlUInt		getNumberOfViews() const;
    IlBoolean		removeView(IlvDvDocViewInterface* view,
				   IlBoolean destroyIt = IlTrue,
				   IlBoolean update = IlTrue);
    void		removeViews(IlBoolean destroyThem = IlFalse);
    void		addView(IlvDvDocViewInterface*,
				IlBoolean update = IlTrue);
    IlvDvDocViewInterface* getDocView(IlUInt index) const;
    IlvDvDocViewInterface** getDocViews(IlUInt& count,
					IlBoolean create = IlTrue) const;
    void		activateView(IlUInt iView = 0);
    IlvDvDocViewInterface* getActiveView() const;
    void		updateViews();

    // ----------------------------------------------------------------------
    // DocViewContainer management
    void		updateViewContainerTitles();
    IlUInt		getViewContainersCount(IlBoolean vis = IlTrue) const;
    void		getViewContainers(IlvArray&,
					  IlBoolean vis = IlTrue) const;
    virtual
    IlBoolean		canCloseViewContainer(IlvDvViewContainerInterface* v);
    virtual void	preCloseViewContainer(IlvDvViewContainerInterface*);

    // ----------------------------------------------------------------------
    // Undo / redo / repeat
    virtual IlBoolean	canUndo() const;
    virtual void	undo(IlBoolean updateUI = IlTrue);
    virtual IlBoolean	canRedo() const;
    virtual void	redo(IlBoolean updateUI = IlTrue);
    virtual IlBoolean	canRepeat() const;
    virtual void	repeat(IlBoolean updateUI = IlTrue);
    virtual void	doCommand(IlvDvCommand* command,
				  IlBoolean updateUI = IlTrue,
				  IlBoolean modified = IlTrue);
    void		addDoneCommand(IlvDvCommand* command,
				       IlBoolean updateUI = IlTrue,
				       IlBoolean modified = IlTrue);
    // ----------------------------------------------------------------------
    // Basic properties
    inline IlBoolean	isModified() const { return _modified; }
    virtual void	setModified(IlBoolean modified,
				    IlBoolean notify = IlTrue);
    inline
    const IlString&	getTitle() const { return _title; }
    virtual void	setTitle(const char* title, IlBoolean update = IlTrue);
    inline IlvDvDocTemplate*	getDocTemplate() const { return _docTemplate; }
    inline void		setDocTemplate(IlvDvDocTemplate* docTemplate)
			{
			    _docTemplate = docTemplate;
			}

    IlvDvDocManager*	getDocManager() const;
    IlvDvApplication*	getDvApplication() const;
    inline IlBoolean	isAutoDelete() const { return _autoDelete; }
    inline void		setAutoDelete(IlBoolean autoDelete)
			{
			    _autoDelete = autoDelete;
			}
    IlvDisplay*		getDisplay() const;

    // ----------------------------------------------------------------------
    inline
    const IlvPathName&	getPathName() const { return _pathName; }
    virtual void	setPathName(const IlvPathName& pathName,
				    IlBoolean addToMRU = IlTrue);
    virtual IlBoolean	open(const IlvPathName& pathname);
    virtual IlBoolean	readDocument(const IlvPathName& pathname);
    IlBoolean		revert();
    IlBoolean		save();
    IlBoolean		saveAs();
    IlBoolean		save(IlvPathName& pathName,
			     IlBoolean replace = IlTrue);
    virtual IlBoolean	saveDocument(const IlvPathName& pathName);
    virtual void	serialize(IlvDvStream& stream);
    virtual IlBoolean	saveModifications();

    // ----------------------------------------------------------------------
    // Query / apply values
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static void		GetAccessors(const IlSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_ViewsCountSymbol;
    static IlSymbol*	_SetModifiedMethod;

    IlvDvDeclareInterface();

    // ----------------------------------------------------------------------
    IlvDeclareBasePropertyListOwner();

protected:
    IlvPathName		_pathName;
#if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0530)
			  std::
#endif /* Borland C++ Builder 3.0 */
    time_t		_lastUpdate;
    IlString		_title;
    IlBoolean		_modified;
    IlBoolean		_autoDelete;
    IlvDvDocTemplate*	_docTemplate;

    IlvArray		_docViews;
    void		callMethodDocViews(const IlSymbol* name,
					   const IlvDvValue& param1,
					   IlvDvDocViewInterface* except = 0);
    void		notifyViews(const IlSymbol* name,
				    IlvDvDocViewInterface* except,...);
    void		applyValueDocViews(const IlSymbol* name,
					   const IlvDvValue& param1,
					   IlvDvDocViewInterface* except = 0);
    inline
    IlvDvDocViewInterface* getCurrentCallerView() const
			{
			    return _currentCallerView;
			}
    inline void		setCurrentCallerView(IlvDvDocViewInterface* view)
			{
			    _currentCallerView = view;
			}

    friend class ILVDVCLASS IlvDvDocViewInterface;

    void		applyValueFromDocView(IlvValue&,
					      IlvDvDocViewInterface* caller);
    inline virtual void	updateModificationFlag() {}
    virtual void	viewsListChanged();
    virtual void	ensureUpdatedOnDisk(IlBoolean ask = IlTrue);

    // Commands
    IlvDvCommandHistory	_cmdHistory;
    void		undoUI(IlvDvActionDescriptor*);
    void		redoUI(IlvDvActionDescriptor*);
    void		repeatUI(IlvDvActionDescriptor*);
    void		doRefreshAction(const char*);
    void		doRefreshUndoRedo();

private:
    IlvDvDocViewInterface*	_currentCallerView; // Internal use
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(document);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Document_H */
