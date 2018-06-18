// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/docmanag.h
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
// Declaration of the IlvDvDocManager class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Docmanag_H)
#define __Ilv_Appframe_Docmanag_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Base_Array_H)
#include <ilviews/base/array.h>
#endif
#if !defined(__Ilv_Base_Pathname_H)
#include <ilviews/base/pathname.h>
#endif
#if !defined(__Ilv_Appframe_Filelst_H)
#include <ilviews/appframe/filelst.h>
#endif

class IlvDvStream;
class IlvDvDocTemplate;
class IlvDvDocument;
class IlvDvApplication;
class IlvDvActionDescriptor;
class IlvAbstractMenu;
class IlvDvOptions;
// --------------------------------------------------------------------------
// DlgOpenFile modes
typedef enum {
    IlvOpenModeNone = 0,
    IlvOpenMultiple = 1,
    IlvFileMustExists = 2,
    IlvHideReadOnly = 4,
    IlvModeOpen = 8
} IlvDvDialogOpenMode;

// --------------------------------------------------------------------------
// IlvDvDocManager class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvDocManager : public IlvDvSerializable {
    IlvDeclareClassInfo();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvDocManager(IlvDvApplication*);
    virtual ~IlvDvDocManager();

    // ----------------------------------------------------------------------
    // Main overridables
    virtual
    IlvDvDocument*	openDocument(const IlvPathName&,
				     IlBoolean createWindow = IlTrue,
				     IlBoolean addToMRU = IlTrue);
    virtual
    IlvDvDocument*	getOpenedDocument(const IlvPathName&);
    void		openRecentFile(IlUInt nFile);
    virtual
    IlvDvDocument*	newDocument(IlBoolean createWindow = IlTrue,
				    IlvSystemView transientFor = 0);
    virtual
    IlvDvDocument*	openDocument(IlBoolean createWindow = IlTrue,
				     IlvSystemView transientFor = 0);

    // helper for standard commdlg dialogs
    virtual IlBoolean	doPromptFileName(IlvPathName& fileName,
					 const IlvString& title,
					 IlvDvDialogOpenMode mode,
					 IlvDvDocTemplate* pTmplt = 0,
					 IlvSystemView transientFor=0);

    virtual IlBoolean	saveAllModifiedDocs(); // save before exit
    virtual void	saveAllModifiedDocsUI(IlvDvActionDescriptor*);
    virtual IlBoolean	saveDocument(IlvDvDocument*);
    virtual IlBoolean	saveAsDocument(IlvDvDocument*);
    virtual IlBoolean	closeAllDocuments(IlBoolean endSession);
    virtual IlBoolean	saveModifications();
    virtual IlUInt	getOpenedDocumentCount() const;
    virtual void	addToRecentFileList(const IlvPathName&);
    virtual void	updateRecentFileListMenu(IlvAbstractMenu*,
						 IlBoolean = IlTrue) const;

    // ----------------------------------------------------------------------
    // Working with document templates
    virtual void	addDocTemplate(IlvDvDocTemplate*);
    virtual void	removeDocTemplate(IlvDvDocTemplate*,
					  IlBoolean bDelete = IlTrue);
    IlvDvDocTemplate*	getDocTemplate(IlUInt index) const;
    IlUInt		getDocTemplatesCount() const;
    IlvDvDocTemplate*	findDocTemplate(const char*) const;

    // ----------------------------------------------------------------------
    // Basic properties

    IlvDisplay*		getDisplay() const;
    IlvDvApplication*	getDvApplication() const
			{
			    return _application;
			}
    void		readRegistries();
    void		writeRegistries();
    void		readFileListOptions(IlvDvOptions*);
    void		updateFileListOptions(IlvDvOptions*);
    IlvDvRecentFileList& getRecentFilesList()
			{
			    return _recentFileList;
			}
    // ----------------------------------------------------------------------
    // IO
    virtual void	serialize(IlvDvStream&);

    static int		_MaxOpenFiles;
    static IlSymbol*	_RecentFilesCommandSymbol;

protected:
    IlvDvApplication*	_application;
    IlvArray		_templates;
    IlvDvRecentFileList	_recentFileList;
    IlvPathName		_lastOpenedFile;

public:
    static IlBoolean	OpenCallback(IlAny itemData, IlAny param);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(docmanag);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Docmanag_H */
