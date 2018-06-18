// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/stdesc.h
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
// Declaration of Studio descriptive objects classes
// --------------------------------------------------------------------------
#ifndef __IlvSt_Stdesc_H
#define __IlvSt_Stdesc_H

#include <ilviews/ilv.h>
#include <ilviews/base/hash.h>
#include <ivstudio/util.h>
#if !defined(__IlvSt_Stprop_H)
#include <ivstudio/stprop.h>
#endif


class IlvContainer;

class ILVSTUDIOCLASS IlvStDescriptiveObject : public IlvStPropertySet
{
public:
  IlvStDescriptiveObject(const IlSymbol* cl, const char* name);
  IlvStDescriptiveObject(const IlvStDescriptiveObject&);
  virtual ~IlvStDescriptiveObject();
  virtual const char* getKeyWord() const = 0;
  // --- IO ---
  virtual IlvStProperty* readProperty(ILVSTDPREF istream&, const IlSymbol*);
  virtual void 	writeProperties(ILVSTDPREF ostream&) const;

protected:
  void		set(const IlvStDescriptiveObject&);
  IlvAList*		_allProps;

  static IlSymbol*	_S_properties;

public:
  static int GlobalInit();

  // --- String properties ---
  virtual const char*	getStringProperty(IlSymbol* section,
					  IlSymbol* propName) const;
  virtual void	setStringProperty(IlSymbol* section,
				  IlSymbol* propName,
				  const char* propValue);
  virtual void	removeStringProperty(IlSymbol* section,
				     IlSymbol* propName);
  virtual void	removeStringProperties(IlSymbol* section);
  virtual void	removeStringProperties();
  const char*		getStringProperty(const char* section,
					  const char* propName) const
    { return getStringProperty(IlvGetSymbol(section),
			       IlvGetSymbol(propName)); }
  void		setStringProperty(const char* section,
				  const char* propName,
				  const char* propValue)
    { setStringProperty(IlvGetSymbol(section), IlvGetSymbol(propName),
			propValue); }
  void		removeStringProperty(const char* section,
				     const char* propName)
    { removeStringProperty(IlvGetSymbol(section),
			   IlvGetSymbol(propName)); }
  void		removeStringProperties(const char* section)
    { removeStringProperties(IlvGetSymbol(section)); }
  virtual IlBoolean	readStringProperties(ILVSTDPREF istream&);
  virtual void	copyProperties(const IlvStDescriptiveObject&);

}; // class IlvStDescriptiveObject

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStClassDescriptor : public IlvStDescriptiveObject
{
public:
  IlvStClassDescriptor(const IlSymbol* cl, const char* name);

  IlvStClassDescriptor(const IlvStClassDescriptor&);

  // --- IO ---
  virtual IlvStProperty* readProperty(ILVSTDPREF istream&, const IlSymbol*);
  virtual void 	writeProperties(ILVSTDPREF ostream&) const;

  // --- props ---
  void setFileName(const char* filePath);

  const char* getFileBaseName() const;

  void setFileBaseName(const char* name);

  const char* getDataDir() const;

  void setDataDir(const char* dir);

  const char* getSrcDir() const;

  void setSrcDir(const char* dir);

  const char* getHeaderDir() const;

  void setHeaderDir(const char* dir);

  const char* getObjDir() const;

  void setObjDir(const char* dir);

  const char* getClassName() const;

  void setClassName(const char* cls);

  virtual const char* getDefaultBaseClass() const = 0;

  const char* getBaseClass() const;

  void setBaseClass(const char* bc);

  // --- User Code ---
  const IlvStStringArray& getUserHeaderCode() const
    { return _userHeaderCode; }
  void 		setUserHeaderCode(const IlvStStringArray& exps)
    { _userHeaderCode.setStrings(exps); }
  const IlvStStringArray& getUserSourceCode() const
    { return _userSourceCode; }
  void 		setUserSourceCode(const IlvStStringArray& exps)
    { _userSourceCode.setStrings(exps); }

  // --- code flags ---
  IlBoolean 	accessorWanted() const
    { return getPropertyBoolean(_S_accessors); }
  void 	wantAccessor(IlBoolean val)
    { setPropertyBoolean(_S_accessors, val); }
  IlBoolean 	dataWanted() const
    { return getPropertyBoolean(_S_data); }
  void 	wantData(IlBoolean val)
    { setPropertyBoolean(_S_data, val); }
  IlBoolean 	callbackWanted() const
    { return getPropertyBoolean(_S_callbacks); }
  void 	wantCallback(IlBoolean val)
    { setPropertyBoolean(_S_callbacks, val); }

  // --- misc ---
  IlBoolean		isModified() const { return _modified; }
  virtual void 	setModified(IlBoolean);

  // --- file extensions ---
  virtual const char* getDataFileExtension() const;
  virtual const char* getApplicationFileExtension() const;
  virtual const char* getStateFileExtension() const;
  virtual const char* getHeaderFileExtension() const;
  virtual const char* getSourceFileExtension() const;
  virtual const char* getMakeFileExtension() const;
  static const char*	GetDataFileExtension();
  static void		SetDataFileExtension(const char* str)
    { IlvStSetString(_DataFileExt, str); }
  static const char*	GetApplicationFileExtension();
  static void		SetApplicationFileExtension(const char* str)
    { IlvStSetString(_AppliFileExt, str); }
  static const char*	GetStateFileExtension();
  static void		SetStateFileExtension(const char* str)
    { IlvStSetString(_StateFileExt, str); }
  static const char*	GetHeaderFileExtension();
  static void		SetHeaderFileExtension(const char* str)
    { IlvStSetString(_HeaderFileExt, str); }
  static const char*	GetSourceFileExtension();
  static void		SetSourceFileExtension(const char* str)
    { IlvStSetString(_SourceFileExt, str); }
  static const char*	GetMakeFileExtension();
  static void		SetMakeFileExtension(const char* str)
    { IlvStSetString(_MakeFileExt, str); }

  static int GlobalInit();

  static IlSymbol*	_S_class;
  static IlSymbol*	_S_baseClass;

  static IlSymbol*	_S_fileBase;
  static IlSymbol*	_S_dataDir;
  static IlSymbol*	_S_headerDir;
  static IlSymbol*	_S_srcDir;
  static IlSymbol*	_S_objDir;

  static IlSymbol*	_S_accessors;
  static IlSymbol*	_S_data;
  static IlSymbol*	_S_callbacks;
  static IlSymbol*	_S_main;
  static IlSymbol*	_S_make;

protected:
  IlvStStringArray    _userHeaderCode;
  IlvStStringArray    _userSourceCode;
  IlBoolean		_modified	ILVSTBF;

  static char*	_DataFileExt;
  static char*	_AppliFileExt;
  static char*	_StateFileExt;
  static char*	_HeaderFileExt;
  static char*	_SourceFileExt;
  static char*	_MakeFileExt;
}; // class IlvStClassDescriptor

class ILVSTUDIOCLASS IlvStPanelClass : public IlvStClassDescriptor
{
public:
  IlvStPanelClass(const char* name = 0);
  IlvStPanelClass(const IlvStPanelClass&);
  virtual const char* getKeyWord() const;
  virtual const char* getDefaultBaseClass() const;
  const char*		getDataString() const { return _dataString; }
  void		setDataString(const char* str) { _dataString = str; }
  IlBoolean		systemViewConstructorWanted() const
    { return getPropertyBoolean(_S_systemViewConstructor); }
  void		wantSystemViewConstructor(IlBoolean val)
    { setPropertyBoolean(_S_systemViewConstructor, val); }

  IlBoolean		systemViewChildConstructorWanted() const
    { return getPropertyBoolean(_S_systemViewChildConstructor); }
  void		wantSystemViewChildConstructor(IlBoolean val)
    { setPropertyBoolean(_S_systemViewChildConstructor, val); }

  IlBoolean		topViewConstructorWanted() const
    { return getPropertyBoolean(_S_topViewConstructor); }
  void		wantTopViewConstructor(IlBoolean val)
    { setPropertyBoolean(_S_topViewConstructor, val); }

  IlBoolean		viewChildConstructorWanted() const
    { return getPropertyBoolean(_S_viewChildConstructor); }
  void		wantViewChildConstructor(IlBoolean val)
    { setPropertyBoolean(_S_viewChildConstructor, val); }

  IlBoolean		callbackDeclarationWanted() const
    { return getPropertyBoolean(_S_callbackDeclarations); }
  void		wantCallbackDeclaration(IlBoolean val)
    { setPropertyBoolean(_S_callbackDeclarations, val); }

  IlBoolean		useAccelerators() const
    { return getPropertyBoolean(_S_useAccelerators); }
  void		useAccelerators(IlBoolean val)
    { setPropertyBoolean(_S_useAccelerators, val); }
  const char* getFolder() const { return getPropertyString(_S_folder); }
  void setFolder(const char* folder) { setPropertyString(_S_folder, folder); }
  static int GlobalInit();

  static IlSymbol* _S_useAccelerators;
  static IlSymbol* _S_systemViewConstructor;
  static IlSymbol* _S_systemViewChildConstructor;
  static IlSymbol* _S_topViewConstructor;
  static IlSymbol* _S_viewChildConstructor;
  static IlSymbol* _S_callbackDeclarations;
  static IlSymbol* _S_folder;

protected:
  IlvStString		_dataString;
}; // class IlvStPanelClass

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStPanelInstance
: public IlvStDescriptiveObject
{
public:
    IlvStPanelInstance(const char* name = 0);
    IlvStPanelInstance(const IlvStPanelInstance&);

    // --- General Page ---
    const char*		getClassName() const
	{ return getPropertyString(_S_class); }
    void		setClassName(const char* str)
	{ setPropertyString(_S_class, str); }
    const char*		getUserClass() const
	{ return getPropertyString(_S_userClass); }
    void		setUserClass(const char* str)
	{ setPropertyString(_S_userClass, str); }
    const char*		getTitle() const
	{ return getPropertyString(_S_title); }
    void		setTitle(const char* str)
	{ setPropertyString(_S_title, str); }
    const char*		getTransientFor() const
	{ return getPropertyString(_S_transientFor); }
    void		setTransientFor(const char* str)
	{ setPropertyString(_S_transientFor, str); }
    const char*		getDestroyCallbackName() const
	{ return getPropertyString(_S_destroyCallback); }
    void		setDestroyCallbackName(const char* str)
	{ setPropertyString(_S_destroyCallback, str); }
    const char*		getBackgroundBitmap() const
	{ return getPropertyString(_S_backgroundBitmap); }
    void		setBackgroundBitmap(const char* name)
	{ setPropertyString(_S_backgroundBitmap, name); }
    IlBoolean		isVisible() const
	{ return getPropertyBoolean(_S_visible); }
    void		setVisible(IlBoolean visible)
	{ setPropertyBoolean(_S_visible,  visible); }
    IlBoolean		useAccelerators() const
	{ return getPropertyBoolean(_S_useAccelerators); }
    void		useAccelerators(IlBoolean val)
	{ setPropertyBoolean(_S_useAccelerators, val); }
    IlBoolean		isDoubleBuffering() const
	{ return getPropertyBoolean(_S_doubleBuffering); }
    void		setDoubleBuffering(IlBoolean val)
	{ setPropertyBoolean(_S_doubleBuffering, val); }
    // --- Properties ---
    IlBoolean		isNoBorder() const
	{ return getPropertyBoolean(_S_noBorder); }
    void		setNoBorder(IlBoolean val)
	{ setPropertyBoolean(_S_noBorder, val); }
    IlBoolean		isNoResizeBorder() const
	{ return getPropertyBoolean(_S_noResizeBorder); }
    void		setNoResizeBorder(IlBoolean val)
	{ setPropertyBoolean(_S_noResizeBorder, val); }
    IlBoolean		isNoTitleBar() const
	{ return getPropertyBoolean(_S_noTitleBar); }
    void		setNoTitleBar(IlBoolean val)
	{ setPropertyBoolean(_S_noTitleBar, val); }
    IlBoolean		isNoSysMenu() const
	{ return getPropertyBoolean(_S_noSysMenu); }
    void		setNoSysMenu(IlBoolean val)
	{ setPropertyBoolean(_S_noSysMenu, val); }
    IlBoolean		isNoMinBox() const
	{ return getPropertyBoolean(_S_noMinBox); }
    void		setNoMinBox(IlBoolean val)
	{ setPropertyBoolean(_S_noMinBox, val); }
    IlBoolean		isNoMaxBox() const
	{ return getPropertyBoolean(_S_noMaxBox); }
    void		setNoMaxBox(IlBoolean val)
	{ setPropertyBoolean(_S_noMaxBox, val); }
    IlBoolean		isSaveUnder() const
	{ return getPropertyBoolean(_S_saveUnder); }
    void		setSaveUnder(IlBoolean val)
	{ setPropertyBoolean(_S_saveUnder, val); }
    IlBoolean		isIconified() const
	{ return getPropertyBoolean(_S_iconified); }
    void		setIconified(IlBoolean val)
	{ setPropertyBoolean(_S_iconified, val); }
    IlBoolean		isMaximized() const
	{ return getPropertyBoolean(_S_maximized); }
    void		setMaximized(IlBoolean val)
	{ setPropertyBoolean(_S_maximized, val); }
    IlBoolean		isMDIChild() const
	{ return getPropertyBoolean(_S_MDIChild); }
    void		setMDIChild(IlBoolean val)
	{ setPropertyBoolean(_S_MDIChild, val); }
    // --- Sizes ---
    IlvPos		getX() const { return (IlvPos)getPropertyInt(_S_x); }
    void		setX(IlvPos x) { setPropertyInt(_S_x, (IlInt)x); }
    IlvPos		getY() const { return (IlvPos)getPropertyInt(_S_y); }
    void		setY(IlvPos y) { setPropertyInt(_S_y, (IlInt)y); }
    IlvDim		getWidth() const
	{ return (IlvDim)getPropertyInt(_S_width); }
    void		setWidth(IlvDim width)
	{ setPropertyInt(_S_width, (IlInt)width); }
    IlvDim		getHeight() const
	{ return (IlvDim)getPropertyInt(_S_height); }
    void		setHeight(IlvDim height)
	{ setPropertyInt(_S_height, (IlInt)height); }
    IlBoolean		hasDimensions() const
	{ return getPropertyBoolean(_S_dims); }
    void		hasDimensions(IlBoolean dims)
	{ setPropertyBoolean(_S_dims, dims); }
    IlvDim		getMinWidth() const
	{ return (IlvDim)getPropertyInt(_S_minWidth); }
    void		setMinWidth(IlvDim val)
	{ setPropertyInt(_S_minWidth, (IlInt)val); }
    IlvDim		getMinHeight() const
	{ return (IlvDim)getPropertyInt(_S_minHeight); }
    void		setMinHeight(IlvDim val)
	{ setPropertyInt(_S_minHeight, (IlInt)val); }
    IlvDim		getMaxWidth() const
	{ return (IlvDim)getPropertyInt(_S_maxWidth); }
    void		setMaxWidth(IlvDim val)
	{ setPropertyInt(_S_maxWidth, (IlInt)val); }
    IlvDim		getMaxHeight() const
	{ return (IlvDim)getPropertyInt(_S_maxHeight); }
    void		setMaxHeight(IlvDim val)
	{ setPropertyInt(_S_maxHeight, (IlInt)val); }

protected:
    void		set(const IlvStPanelInstance&);
    IlvContainer*	_container;
    IlvStPanelInstance* _parent;

    static IlSymbol* _S_class;
    static IlSymbol* _S_userClass;
    static IlSymbol* _S_title;
    static IlSymbol* _S_transientFor;
    static IlSymbol* _S_x;
    static IlSymbol* _S_y;
    static IlSymbol* _S_width;
    static IlSymbol* _S_height;
    static IlSymbol* _S_dims;
    static IlSymbol* _S_visible;
    static IlSymbol* _S_useAccelerators;
    static IlSymbol* _S_doubleBuffering;
    static IlSymbol* _S_destroyCallback;
    static IlSymbol* _S_backgroundBitmap;
    static IlSymbol* _S_noBorder;
    static IlSymbol* _S_noResizeBorder;
    static IlSymbol* _S_noTitleBar;
    static IlSymbol* _S_noSysMenu;
    static IlSymbol* _S_noMinBox;
    static IlSymbol* _S_noMaxBox;
    static IlSymbol* _S_saveUnder;
    static IlSymbol* _S_iconified;
    static IlSymbol* _S_maximized;
    static IlSymbol* _S_MDIChild;
    static IlSymbol* _S_minWidth;
    static IlSymbol* _S_minHeight;
    static IlSymbol* _S_maxWidth;
    static IlSymbol* _S_maxHeight;

public:
    static int		GlobalInit();
    virtual const char* getKeyWord() const;
    virtual void	addedToSet(IlvStPropertySet*);
    IlvStPanelInstance& operator=(const IlvStPanelInstance&);
    IlvContainer*	getContainer() const { return _container; }
    void		setContainer(IlvContainer* cont);
    static IlvStPanelInstance* Get(const IlvContainer*);
    IlvStPanelInstance* getParent() const { return _parent; }
    void		setParent(IlvStPanelInstance* parent)
	{ _parent = parent; }
    void		addSubPanel(IlvStPanelInstance*);
    IlvStPanelInstance*	getTopPanelInstance() const;
    IlvStPanelInstance*	getSubPanel(const char* name,
				    IlBoolean recursive = IlTrue);
    IlBoolean		attachContainerToParent(IlvContainer* parcont,
						IlvContainer* cont);
    IlBoolean		hasSubPanels() const;
}; // class IlvStPanelInstance

// --------------------------------------------------------------------------
class ILVSTUDIOCLASS IlvStAppDescriptor
: public IlvStClassDescriptor
{
public:
    IlvStAppDescriptor(const char* name);
    IlvStAppDescriptor(const IlvStAppDescriptor&);
    ~IlvStAppDescriptor();
    virtual void	reset();
    void		preset();
    virtual const char* getDefaultBaseClass() const;
    virtual const char* getCreatorName() const;
    // --- IO ---
    virtual IlBoolean	read(ILVSTDPREF istream& istm);
    virtual IlvStProperty* readProperty(ILVSTDPREF istream&, const IlSymbol*);
    virtual void	write(ILVSTDPREF ostream&) const;
    virtual void 	writeProperties(ILVSTDPREF ostream&) const;
    virtual const char* getKeyWord() const;
    // --- properties ---
    const char*		getCreator() const
	{ return getPropertyString(_S_creator); }
    void		setCreator(const char* editorName)
	{ setPropertyString(_S_creator, editorName); }
    const char*		getUserClass() const
	{ return getPropertyString(_S_userClass); }
    void		setUserClass(const char* name)
    	{ setPropertyString(_S_userClass, name); }
    // --- panel classes ---
    const IlArray& 	getPanelClasses() const { return _pclasses; }
    IlvStPanelClass*	getPanelClass(const char*) const;
    IlvStPanelClass*	getPanelClass(const IlvStPanelInstance*) const;
    IlvStPanelClass*	getPanelClassByName(const char*) const;
    void		addPanelClass(IlvStPanelClass*);
    IlBoolean		removePanelClass(IlvStPanelClass*);
    virtual IlBoolean	readPanelClass(ILVSTDPREF istream&);
    // --- panel instances ---
    const IlArray& 	getPanelInstances() const { return _pinstances; }
    IlvStPanelInstance* getPanelInstance(const char* name,
					 IlBoolean subpanel = IlTrue) const;
    void		addPanelInstance(IlvStPanelInstance*);
    IlBoolean		removePanelInstance(IlvStPanelInstance*);
    virtual IlBoolean	readPanelInstance(ILVSTDPREF istream&);
    // --- flags ---
    IlBoolean 		makeFileWanted() const
	{ return getPropertyBoolean(_S_make); }
    void 		wantMakeFile(IlBoolean val)
	{ setPropertyBoolean(_S_make, val); }
    IlBoolean 		mainFunctionWanted() const
	{ return getPropertyBoolean(_S_main); }
    void 		wantMainFunction(IlBoolean val)
	{ setPropertyBoolean(_S_main, val); }
    IlBoolean		exitPanelWanted() const
	{ return getPropertyBoolean(_S_exitPanel); }
    void		wantExitPanel(IlBoolean val)
	{ setPropertyBoolean(_S_exitPanel, val); }
    IlBoolean		panelAccessorsWanted() const
	{ return getPropertyBoolean(_S_panelAccessors); }
    void		wantPanelAccessors(IlBoolean val)
	{ setPropertyBoolean(_S_panelAccessors, val); }
    IlBoolean		JvScriptWanted() const
	{ return getPropertyBoolean(_S_JvScript); }
    void		wantJvScript(IlBoolean val)
	{ setPropertyBoolean(_S_JvScript, val); }
    IlBoolean		includeInHeaderWanted() const
	{ return getPropertyBoolean(_S_includeInHeader); }
    void		wantIncludeInHeader(IlBoolean val)
	{ setPropertyBoolean(_S_includeInHeader, val); }
    IlBoolean		bmpBitmapReaderWanted() const
	{ return getPropertyBoolean(_S_bmpBitmapReader); }
    void		wantBmpBitmapReader(IlBoolean val)
	{ setPropertyBoolean(_S_bmpBitmapReader, val) ; }
    IlBoolean		dibBitmapReaderWanted() const
	{ return getPropertyBoolean(_S_dibBitmapReader); }
    void		wantDibBitmapReader(IlBoolean val)
	{ setPropertyBoolean(_S_dibBitmapReader, val); }
    IlBoolean		pngBitmapReaderWanted() const
	{ return getPropertyBoolean(_S_pngBitmapReader); }
    void		wantPngBitmapReader(IlBoolean val)
	{ setPropertyBoolean(_S_pngBitmapReader, val); }
    IlBoolean		jpgBitmapReaderWanted() const
	{ return getPropertyBoolean(_S_jpgBitmapReader); }
    void		wantJpgBitmapReader(IlBoolean val)
	{ setPropertyBoolean(_S_jpgBitmapReader, val); }
    IlBoolean		pbmBitmapReaderWanted() const
	{ return getPropertyBoolean(_S_pbmBitmapReader); }
    void		wantPbmBitmapReader(IlBoolean val)
	{ setPropertyBoolean(_S_pbmBitmapReader, val); }
    IlBoolean		pgmBitmapReaderWanted() const
	{ return getPropertyBoolean(_S_pgmBitmapReader); }
    void		wantPgmBitmapReader(IlBoolean val)
	{ setPropertyBoolean(_S_pgmBitmapReader, val); }
    IlBoolean		ppmBitmapReaderWanted() const
	{ return getPropertyBoolean(_S_ppmBitmapReader); }
    void		wantPpmBitmapReader(IlBoolean val)
	{ setPropertyBoolean(_S_ppmBitmapReader, val); }
    // --- path ---
    const char*		getRefDir() const;
    void		setRefDir(const char* dir)
	{ setPropertyString(_S_refDir, dir); }
    const char*		getHeaderFileScope() const
	{ return getPropertyString(_S_headerFileScope); }
    void		setHeaderFileScope(const char* str)
	{ setPropertyString(_S_headerFileScope, str); }
    const char*		getDataFile() const;
    const char*		getStateFile() const;
    const char*		getHeaderFile() const;
    const char*		getSourceFile() const;
    const char*		getMakeFile() const;
    const char*		getDataFile(const IlvStPanelClass*) const;
    const char*		getHeaderFile(const IlvStPanelClass*) const;
    const char*		getSourceFile(const IlvStPanelClass*) const;
    const char*		makeAbsDir(const char*) const;
    const char*		getStateFileDirectory() const;
    const char*		getHeaderDirectory() const;
    const char*		getHeaderDirectory(const IlvStPanelClass*) const;
    const char*		getSrcDirectory() const;
    const char*		getSrcDirectory(const IlvStPanelClass*) const;
    const char*		getObjDirectory() const;
    const char*		getObjDirectory(const IlvStPanelClass*) const;
    const char*		getDataDirectory(const IlvStPanelClass*) const;
    IlBoolean		isAbsolutePath() const
	{ return getPropertyBoolean(_S_absolutePath); }
    void		setAbsolutePath(IlBoolean val)
	{ setPropertyBoolean(_S_absolutePath, val); }

    static int GlobalInit();

    static IlSymbol* _S_version;
    static IlSymbol* _S_iref;
    static IlSymbol* _S_ViewsVersion;
    static IlSymbol* _S_system;
    static IlSymbol* _S_date;
    static IlSymbol* _S_creator;
    static IlSymbol* _S_main;
    static IlSymbol* _S_make;
    static IlSymbol* _S_exitPanel;
    static IlSymbol* _S_panelAccessors;
    static IlSymbol* _S_includeInHeader;
    static IlSymbol* _S_bmpBitmapReader;
    static IlSymbol* _S_dibBitmapReader;
    static IlSymbol* _S_pngBitmapReader;
    static IlSymbol* _S_jpgBitmapReader;
    static IlSymbol* _S_pbmBitmapReader;
    static IlSymbol* _S_pgmBitmapReader;
    static IlSymbol* _S_ppmBitmapReader;
    static IlSymbol* _S_userClass;
    static IlSymbol* _S_stateDir;
    static IlSymbol* _S_absolutePath;
    static IlSymbol* _S_JvScript;
    static IlSymbol* _S_refDir;
    static IlSymbol* _S_headerFileScope;

protected:
    IlArray			_pclasses;
    IlArray			_pinstances;

private:
    void		clean();
}; // class IlvStAppDescriptor

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(st_stdesc)
#endif /* IlvDECLAREINITCLASS */

// --------------------------------------------------------------------------
#endif /* __IlvSt_Stdesc_H */
