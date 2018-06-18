// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/project/prjdoc.h
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
// Declaration of the IlvDvProjectDocument class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Project_Prjdoc_H)
#define __Ilv_Appframe_Project_Prjdoc_H

#if !defined(__Ilv_Appframe_Document_H)
#include <ilviews/appframe/document.h>
#endif

class IlvDvFileInfo;
class IlvDvDocumentProjectItem;
class IlvDvProjectItem;
class IlvPopupMenu;
// --------------------------------------------------------------------------
// IlvDvProjectDocument class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvProjectDocument : public IlvDvDocument
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvProjectDocument();
    virtual ~IlvDvProjectDocument();

    // ----------------------------------------------------------------------
    // Main operations
    void		removeTreeItems(IlArray&);
    void		removeTreeItems(IlvDvProjectItem* const* items,
					IlUInt count);
    IlBoolean		insertFile(IlvDvProjectItem* parent,
				   const IlPathName& filename);
    IlBoolean		insertItem(IlvDvProjectItem* item,
				   IlvDvProjectItem* parent = 0,
				   IlUShort index = (IlUShort)-1);
    IlBoolean		insertFolder(IlvDvProjectItem* parent,
				     const char* name,
				     const char* extensions = 0);
    IlUInt		getFileInfosCount() const;
    IlvDvFileInfo*	getFileInfo(IlUInt index) const;
    IlUInt		getIndexOfFileInfo(const IlvDvFileInfo* fInfo) const;
    IlBoolean		activateItems(const IlArray&);
    IlBoolean		activateItems(IlvDvProjectItem* const* items,
				      IlUInt count);
    virtual IlBoolean	activateItem(IlvDvProjectItem* item);
    virtual void	selectionChanged(IlvDvDocumentProjectItem* lastSel,
					 const IlArray& selections);
    virtual void	itemSelected(IlvDvDocumentProjectItem*);

    // ----------------------------------------------------------------------
    // Initialization / close
    virtual IlBoolean	initializeDocument(IlAny data = 0);
    virtual void	clean();

    // ----------------------------------------------------------------------
    // Basic properties
    inline IlvDvDocumentProjectItem*	getProjectRootItem() const
					{
					    return _prjItemRoot;
					}
    inline IlvDvDocumentProjectItem*	getActiveProjectItem() const
					{
					    return _prjItemRoot;
					}

    // ----------------------------------------------------------------------
    // IO
    virtual void	setTitle(const char* title, IlBoolean update = IlTrue);
    virtual void	serialize(IlvDvStream& stream);

    // ----------------------------------------------------------------------
    // Query / apply values
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    static void		GetAccessors(const IlSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
    virtual IlBoolean	getValueDescriptor(IlvValue& value) const;

    static IlSymbol*	_AddProjectItemSymbol;
    static IlSymbol*	_RemoveProjectItemSymbol;
    static IlSymbol*	_UpdateTreeItemSymbol;
    static IlSymbol*	_SelectTreeItemSymbol;
    static IlSymbol*	_ActivatedTreeItemSymbol;

    IlvDvDeclareInterface();

protected:
    IlvDvDocumentProjectItem*	_prjItemRoot;
    IlBoolean			_explicitTreeItemRootLabel;
    IlvPopupMenu**		_popups;
    IlArray _fileInfos;

    // Name of root tree item processing
    virtual const IlString&	getRootLabel(IlString&,
					     const char* title) const;
    virtual const char*		getRootFmtLabel() const;

    // Popup menu management
    virtual IlvPopupMenu*	getPopupMenu(IlvDvDocumentProjectItem*);
    virtual void		initializePopupMenus();

    // File infos management
    void			addFileInfos(IlvDvFileInfo*);
    IlBoolean			extractFileInfo(IlvDvFileInfo*);
    virtual IlvDvFileInfo*	buildFileInfos(const IlPathName&);
    IlvDvFileInfo*		findFileInfo(const IlPathName& pathName);
    IlvDvFileInfo*		ensureFileInfo(const IlPathName& pathName);

    virtual IlvDvDocumentProjectItem*	createDocumentProjectItem();
    virtual IlvDvProjectItem*	createProjectFileItem(IlvDvFileInfo* fileInfo);
    virtual IlvDvProjectItem*	createProjectFileItem(const char*);
    virtual IlvDvProjectItem*	createProjectFolderItem(const char* name,
							const char* extensions = 0);
    virtual void		removeTreeItemData(IlvDvProjectItem* item);
    virtual void		initializeDocManager();

    friend class IlvDvFileInfo;
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(prjdoc);
// --------------------------------------------------------------------------
#endif /* !__Ilv_Appframe_Project_Prjdoc_H */
