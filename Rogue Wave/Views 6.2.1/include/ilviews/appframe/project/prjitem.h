// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/project/prjitem.h
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
// Declaration of the IlvDvProjectItem class
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Project_Prjitem_H)
#define __Ilv_Appframe_Project_Prjitem_H

#if !defined(__Ilv_Appframe_Macros_H)
#include <ilviews/appframe/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Tree_H)
#include <ilviews/gadgets/tree.h>
#endif
#if !defined(__Ilv_Base_Pathname_H)
#include <ilviews/base/pathname.h>
#endif

class IlvDvProjectDocument;
class IlvDvFileInfo;

//---------------------------------------------------------------------------
// IlvDvProjectItem class
//---------------------------------------------------------------------------
class ILVDVCLASS IlvDvProjectItem
: public IlvTreeGadgetItem {
public:
    //-----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvProjectItem(const char* label,
		     IlvBitmap*  bitmap   = 0,
		     IlvPosition position = IlvRight,
		     IlUShort    spacing  = IlvDefaultGadgetItemSpacing);

    IlvDvProjectItem*	duplicate(IlBoolean bDuplicateChilds = IlFalse) const;

    //-----------------------------------------------------------------------
    // Main operations
    inline void		addChild(IlvDvProjectItem* item) { insertChild(item); }
    virtual IlBoolean	removeChild(IlvDvProjectItem* item);

    //-----------------------------------------------------------------------
    // Basic properties
    inline IlBoolean	isParentItem() const
			{
			    return _child? IlTrue : IlFalse;
			}
    inline virtual IlBoolean	isFolder() const { return IlFalse; }
    inline virtual IlBoolean	isFile() const { return IlFalse; }
    virtual const IlSymbol*	getPopupMenuResouceId() const;
    void		setParent(IlvDvProjectItem* parent)
			{
			    _parent = parent;
			}

    IlBoolean		find(const IlvDvProjectItem* item) const;

    //-----------------------------------------------------------------------
    // Serialization
    virtual void	prepareWriting(IlvDvProjectDocument*);
    virtual void	initializeOnProjectDoc(IlvDvProjectDocument*);

    DeclareGadgetItemInfo();
    DeclareGadgetItemIOConstructors(IlvDvProjectItem);

    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*	_MenuResourceId;

protected:
    virtual IlvDvProjectItem*	_duplicate() const;
};

//---------------------------------------------------------------------------
// IlvDvFileItem class
//---------------------------------------------------------------------------
class ILVDVCLASS IlvDvFileItem : public IlvDvProjectItem
{
public:
    //-----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvFileItem(IlvDisplay* display, IlvDvFileInfo* fileInfo);
    ~IlvDvFileItem();

    //-----------------------------------------------------------------------
    // Main operations
    IlBoolean			open();

    //-----------------------------------------------------------------------
    // Basic properties
    virtual const IlSymbol*	getPopupMenuResouceId() const;
    inline virtual IlBoolean	isFile() const { return IlTrue; }
    inline IlvDvFileInfo*	getFileInfos() { return _fileInfo; }

    // Own properties
    const IlPathName&		getPathName() const;
    void			setFileInfo(IlvDvFileInfo* fileInfo);

    //-----------------------------------------------------------------------
    // Serialization
    virtual void		prepareWriting(IlvDvProjectDocument*);
    virtual void		initializeOnProjectDoc(IlvDvProjectDocument*);

    DeclareGadgetItemInfo();
    DeclareGadgetItemIOConstructors(IlvDvFileItem);

    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*		_MenuResourceId;

protected:
    IlString			_shortName;
    IlvDvFileInfo*		_fileInfo;
    int				_internalSerialIndex; // for serialization

protected:
    inline virtual IlvDvProjectItem*	_duplicate() const
					{
					    return new IlvDvFileItem(*this);
					}
};

//---------------------------------------------------------------------------
// IlvDvFolderItem class
//---------------------------------------------------------------------------
class ILVDVCLASS IlvDvFolderItem : public IlvDvProjectItem
{
public:
    //-----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvFolderItem(IlvDisplay* display,
		    const char* name,
		    const char* extensions);
    ~IlvDvFolderItem();

    //-----------------------------------------------------------------------
    // Basic properties
    virtual const IlSymbol*	getPopupMenuResouceId() const;
    inline virtual IlBoolean	isFolder() const { return IlTrue; }

    // Own properties
    inline const char*		getExtentions() const { return _extensions; }
    inline void			setExtentions(const char* szExtentions)
				{
				    _extensions = szExtentions;
				}

    //-----------------------------------------------------------------------
    // Serialization
    DeclareGadgetItemInfo();
    DeclareGadgetItemIOConstructors(IlvDvFolderItem);

    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*		_MenuResourceId;

protected:
    IlString			_extensions;

    inline virtual IlvDvProjectItem*	_duplicate() const
					{
					    return new IlvDvFolderItem(*this);
					}
};

//---------------------------------------------------------------------------
// IlvDvDocumentProjectItem class
//---------------------------------------------------------------------------
class ILVDVCLASS IlvDvDocumentProjectItem : public IlvDvProjectItem
{
public:
    //-----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvDocumentProjectItem(IlvDvProjectDocument* projectDocument);
    ~IlvDvDocumentProjectItem();

    //-----------------------------------------------------------------------
    // Basic properties
    inline virtual IlBoolean	isFolder() const { return IlTrue; }
    virtual const IlSymbol*	getPopupMenuResouceId() const;

    // Own properties
    inline IlvDvProjectDocument*	getProjectDoc() const
					{
					    return _projectDoc;
					}
    void			setProjectDoc(IlvDvProjectDocument* prjDoc);

    //-----------------------------------------------------------------------
    // Serialization
    virtual void		initializeOnProjectDoc(IlvDvProjectDocument*);

    DeclareGadgetItemInfo();
    DeclareGadgetItemIOConstructors(IlvDvDocumentProjectItem);

    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*		_MenuResourceId;

protected:
    IlvDvProjectDocument*	_projectDoc;
    IlString			_name;

    inline virtual IlvDvProjectItem*	
				_duplicate() const
				{
				    return new IlvDvDocumentProjectItem(*this);
				}
};

//---------------------------------------------------------------------------
// IlvDvResultRootTreeItem class
//---------------------------------------------------------------------------
class ILVDVCLASS IlvDvResultRootTreeItem : public IlvDvProjectItem
{
public:
    //-----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvResultRootTreeItem(const char* name);

    //-----------------------------------------------------------------------
    // Basic properties
    virtual const IlSymbol*	getPopupMenuResouceId() const;

    //-----------------------------------------------------------------------
    // Serialization
    DeclareGadgetItemInfo();
    DeclareGadgetItemIOConstructors(IlvDvResultRootTreeItem);

    // ----------------------------------------------------------------------
    // Statics
    static IlSymbol*		_MenuResourceId;

protected:
    inline virtual IlvDvProjectItem*
				_duplicate() const
				{
				    return new IlvDvResultRootTreeItem(*this);
				}
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(prjitem);
//---------------------------------------------------------------------------
#endif /* __Ilv_Appframe_Prjitem_H */
