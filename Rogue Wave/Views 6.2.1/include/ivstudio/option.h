// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/option.h
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
// Declaration of IlvStOptions class
// --------------------------------------------------------------------------
#ifndef __IlvSt_Option_H
#define __IlvSt_Option_H

#if !defined(__Ilv_Ilv_H)
#include <ilviews/ilv.h>
#endif
#if !defined(__Ilv_Base_Resource_H)
#include <ilviews/base/resource.h>
#endif
#if !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif
#if !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif
#if      !defined(__IlvSt_Stprop_H)
#include <ivstudio/stprop.h>
#endif

class IlvStudio;
class IlvStCommand;

// --------------------------------------------------------------------------
extern ILVSTEXPORTEDVAR(const char*) IlvNmAutoResizing;
extern ILVSTEXPORTEDVAR(const char*) IlvNmDoubleBuffering;
extern ILVSTEXPORTEDVAR(const char*) IlvNmOpaqueMoving;

// --------------------------------------------------------------------------
typedef const char* (* IlvStSrcFileExtGetter)(IlvStudio*);

class ILVSTUDIOCLASS IlvStOptions : public IlvStPropertySet
{
public:
  IlvStOptions(IlvStudio* editor);
  ~IlvStOptions();
  // ____________________________________________________________
  virtual IlvStProperty* readProperty(IL_STDPREF istream&, const IlSymbol*);
  virtual void addProperty(IlvStProperty* prop, IlUInt ndx = (IlUInt)-1);
  void	getResources();

  const char* getDefaultApplicationName() const;

  void        setDefaultApplicationName(const char* name)
    { setPropertyString(_S_defaultApplicationName, name); }

  const char* getDefaultBufferName() const;

  void        setDefaultBufferName(const char* name)
    { setPropertyString(_S_defaultBufferName, name); }

  const char* getPanelBaseClass() const;

  void 	setPanelBaseClass(const char* name)
    { setPropertyString(_S_panelBaseClass, name); }

  const char* getApplicationBaseClass() const;

  void 	setApplicationBaseClass(const char* name)
    { setPropertyString(_S_applicationBaseClass, name); }

  const char* getApplicationHeaderFile() const
    { return getPropertyString(_S_applicationHeaderFile); }
  void	setApplicationHeaderFile(const char* name)
    { setPropertyString(_S_applicationHeaderFile, name); }

  const char* getPanelHeaderFile() const
    { return getPropertyString(_S_panelHeaderFile); }
  void	setPanelHeaderFile(const char* name)
    { setPropertyString(_S_panelHeaderFile, name); }

  void registerBaseClassHeader(const char* bclass, const char* file);
  const char* getBaseClassHeader(const char* bclass) const;
  const char* getGadgetPaletteFileName() const
    { return getPropertyString(_S_gadgetPaletteFileName); }
  void  setGadgetPaletteFileName(const char* name)
    { setPropertyString(_S_gadgetPaletteFileName, name); }
  const char* getGraphicPaletteFileName() const
    { return getPropertyString(_S_graphicPaletteFileName); }
  void  setGraphicPaletteFileName(const char* name)
    { setPropertyString(_S_graphicPaletteFileName, name); }
  const char* getEditorName() const
    { return getPropertyString(_S_studioName); }
  void  setEditorName(const char* name)
    { setPropertyString(_S_studioName, name); }
  const char* getEditorShortName() const
    { return getPropertyString(_S_studioShortName); }
  void  setEditorShortName(const char* name)
    { setPropertyString(_S_studioShortName, name); }
  IlvFont*	getMonospaceFont() const { return _monospaceFont; }
  void	setMonospaceFont(IlvFont*);
  IlvColor*   getPanelBackground() const     { return _panelBackground; }
  void	setPanelBackground(IlvColor*);
  IlvColor*   getWorkSpaceBackground() const { return _workSpaceBackground; }
  void	setWorkSpaceBackground(IlvColor*);
  IlvColor*   getMiscBackground() const     { return _miscBackground; }
  void	setMiscBackground(IlvColor*);
  IlvPalette* getMenuPalette() const { return _menuPalette; }
  void setMenuPalette(IlvPalette* pal) { setPalette(_menuPalette, pal); }
  IlvPalette* getToolBarPalette() const { return _toolBarPalette; }
  void setToolBarPalette(IlvPalette* pl) { setPalette(_toolBarPalette, pl); }
  IlvPalette* getToolTipPalette() const { return _toolTipPalette; }
  void setToolTipPalette(IlvPalette* pl) { setPalette(_toolTipPalette, pl); }

  const char* getDefaultDataDir() const;
  void	setDefaultDataDir(const char* dir)
    { IlvStSetString(_defaultDataDir, dir); }

  const char* getDefaultHeaderDir() const;

  void	setDefaultHeaderDir(const char* dir)
    { setPropertyString(_S_defaultHeaderDir, dir); }

  const char* getDefaultSrcDir() const;

  void	setDefaultSrcDir(const char* dir)
    { setPropertyString(_S_defaultSrcDir, dir); }

  const char* getDefaultObjDir() const;

  void	setDefaultObjDir(const char* dir)
    { setPropertyString(_S_defaultObjDir, dir); }

  const char* getDefaultHeaderFileScope() const
    { return getPropertyString(_S_defaultHeaderFileScope); }
  void	setDefaultHeaderFielScope(const char* sco)
    { setPropertyString(_S_defaultHeaderFileScope, sco); }

  const char* getHelpDir() const
    { return getPropertyString(_S_helpDir); }
  void	setHelpDir(const char* dir)
    { setPropertyString(_S_helpDir, dir); }

  // --- Flags ---
  IlBoolean  isDoubleBuffering() const   { return _doubleBuffering; }
  void setDoubleBuffering(IlBoolean val) { _doubleBuffering = val;  }
  IlBoolean  isOpaqueMoving() const      { return _opaqueMoving;    }
  void setOpaqueMoving(IlBoolean val)    { _opaqueMoving = val;     }
  IlBoolean  isAutoResizing() const      { return _autoResizing;    }
  void setAutoResizing(IlBoolean val)    { _autoResizing = val ;    }
  IlBoolean isUsingCOut() const          { return _usingCOut;       }
  void setUsingCOut(IlBoolean val)       { _usingCOut = val;        }
  IlBoolean isSavingData() const	    { return _savingData;      }
  void setSavingData(IlBoolean val)      { _savingData = val;       }
  IlBoolean isToolTip() const	    { return _toolTip;         }
  void setToolTip(IlBoolean val)  	    { _toolTip = val;          }
  IlBoolean isMovingPointer() const
    { return getPropertyBoolean(_S_movingPointer); }
  void setMovingPointer(IlBoolean val)
    { setPropertyBoolean(_S_movingPointer, val); }
  IlBoolean getIgnoringSize() const
    { return getPropertyBoolean(_S_ignoringSize); }
  void       setIgnoringSize(IlBoolean val)
    { setPropertyBoolean(_S_ignoringSize, val); }
  IlBoolean getIgnoringBackground() const
    { return getPropertyBoolean(_S_ignoringBackground); }
  void       setIgnoringBackground(IlBoolean val)
    { setPropertyBoolean(_S_ignoringBackground, val); }
  IlBoolean isAbsolutePath() const
    { return getPropertyBoolean(_S_absolutePath); }
  void       setAbsolutePath(IlBoolean val)
    { setPropertyBoolean(_S_absolutePath, val); }
  IlBoolean isSortingRequirements() const
    { return getPropertyBoolean(_S_sortingRequirements); }
  void       setSortingRequirements(IlBoolean val)
    { setPropertyBoolean(_S_sortingRequirements, val); }
  // --- Code ---
  const char* getFileExtension(const IlSymbol* pname) const;
  const char* getDataFileExtension() const
    { return getFileExtension(_S_dataFileExtension); }
  void setDataFileExtension(const char* str) {
    if (*str == '.')
      str++;
    setPropertyString(_S_dataFileExtension, str);
  }
  const char* getHeaderFileExtension() const
    { return getFileExtension(_S_headerFileExtension); }
  void setHeaderFileExtension(const char* str) {
    if (*str == '.')
      str++;
    setPropertyString(_S_headerFileExtension, str);
  }
  const char* getSourceFileExtension() const;
  void setSourceFileExtension(const char* str) {
    if (*str == '.')
      str++;
    setPropertyString(_S_sourceFileExtension, str);
  }
  const char* getApplicationFileExtension() const
    { return getFileExtension(_S_applicationFileExtension); }
  void setApplicationFileExtension(const char* str) {
    if (*str == '.')
      str++;
    setPropertyString(_S_applicationFileExtension, str);
  }
  const char* getStateFileExtension() const
    { return getFileExtension(_S_stateFileExtension); }
  void	setStateFileExtension(const char* str) {
    if (*str == '.')
      str++;
    setPropertyString(_S_stateFileExtension, str);
  }
  const char* getMakeFileExtension() const
    { return getFileExtension(_S_makeFileExtension); }
  void setMakeFileExtension(const char* str) {
    if (*str == '.') str++;
    setPropertyString(_S_makeFileExtension, str);
  }
  const char* getDefaultSystemName() const
    { return getPropertyString(_S_defaultSystemName); }
  void setDefaultSystemName(const char* name)
    { setPropertyString(_S_defaultSystemName, name); }
  const char* getAdditionalLibraries() const;
  void setAdditionalLibraries(const char* libs);
  void addAdditionalLibraries(const char* libs);
  IlBoolean hasAdditionalLibrary(const char* lib) const;
  void addAdditionalLibrary(const char* lib);
  void removeAdditionalLibrary(const char*);
  // --- Misc ---
  IlUShort	getAlignmentSpacing() const
    { return (IlUShort)getPropertyInt(_S_alignmentSpacing); }
  void	setAlignmentSpacing(IlUShort val)
    { setPropertyInt(_S_alignmentSpacing, (IlInt)val); }
  IlUInt	getPlayerSpeed() const
    { return (IlUInt)getPropertyInt(_S_playerSpeed); }
  void	setPlayerSpeed(IlUInt val)
    { setPropertyInt(_S_playerSpeed, (IlInt)val); }
  const char*	getBitmapAlias(const char*) const;
  void	setBitmapAlias(const char*, const char*);
  IlvDim	getToolBarItemWidth() const
    { return (IlvDim)getPropertyInt(_S_toolBarItemWidth); }
  void	setToolBarItemWidth(IlvDim val)
    { setPropertyInt(_S_toolBarItemWidth, (IlInt)val); }
  IlvDim	getToolBarItemHeight() const
    { return (IlvDim)getPropertyInt(_S_toolBarItemHeight); }
  void	setToolBarItemHeight(IlvDim val)
    { setPropertyInt(_S_toolBarItemHeight, val); }
  void	addLanguage(IlSymbol*, const char*, const char*);
  const IlvArray& getLanguages() const { return _languages; }
  IlvArray&	getLanguages() { return _languages; }
  void 	initializeCommands();
  void	addStartUpCommand(const char* cmdName);
  void	addStartUpCommand(const char* cmdName, const char* arg);
  void	emptyStartUpCommands();
  void	executeStartUpCommands(IlAny caller = 0);
  IlvArray&	getStartUpCommands() { return _startUpCommands; }
  void	addObjectInteractor(const char* name);
  void	addFilter(const char* name);
  IlvArray&	getObjectInteractors() { return _objectInteractors; }
    IlvArray&     getFilters() { return _filters; }
  const char* getStringResource(const char* name);
  IlBoolean  getBooleanResource(const char* name,
				 IlBoolean defaultValue = IlFalse);
  void 	setPalette(IlvPalette*& palvar, IlvPalette*);
  IlvPalette* getPalette(IlvDisplay* display,
			 const char* prefix,
			 IlvColor* = 0,
			 IlvColor* = 0,
			 IlvFont*  = 0);
  IlvFont*	getFont(IlvDisplay*, const char* resname, IlvFont* = 0);
  IlvColor* 	getColor(IlvDisplay*, const char* resname, IlvColor* = 0);
  const char* const* getToolBarCommands(const char* name,
					IlUShort& count) const;
  void	    addToolBarCommand(const char* cmdName,
			      const char* toolBarName,
			      const char* beforeCmd = 0);
  // --- File Browser types ---
  void addFileBrowserType(const char* filter,const char* label,
			  IlUInt ndx = (IlUInt)-1);
  IlUInt	    getNumberOfFileBrowserTypes() const
    { return _fbTypeLabels.getLength(); }
  void	    getFileBrowserType(IlUInt ndx,
			       const char*& filter,
			       const char*& label) const
    { filter = _fbTypeFilters[ndx]; label = _fbTypeLabels[ndx]; }
  IlvStStringArray&	getFileBrowserTypeLabels() { return _fbTypeLabels; }
  IlvStStringArray&	getFileBrowserTypeFilters()
    { return _fbTypeFilters; }

  // --- File Types ---
  void registerFileType(const char* type,const char* commandName);
  const char* getFileLoader(const char* type) const;

  static int GlobalInit();
private:
  void		initToolBarCommands(IlvStPropertySet*);
  void		initValueInterfacePart();

  IlvStudio* 		_editor;
  char*		_defaultDataDir;
  IlvFont*		_monospaceFont;
  IlvColor* 		_panelBackground;
  IlvColor*		_workSpaceBackground;
  IlvColor* 		_miscBackground;
  IlvPalette*		_menuPalette;
  IlvPalette*		_toolBarPalette;
  IlvPalette*		_toolTipPalette;
  IlvStHash		_bitmapAliases;
  IlvArray		_languages;
  IlvArray		_startUpCommands;
  IlvStStringArray	_objectInteractors;
  IlvStStringArray	_filters;
  IlvStStringArray	_fbTypeLabels;
  IlvStStringArray	_fbTypeFilters;
  IlvStHash		_fileLoaders;
  IlvAList		_toolBarCommands;
  IlvStString		_additionalLibraries;

  void initializePalettes(IlvDisplay*);

  // --- Bit fields ---
  IlBoolean _doubleBuffering		ILVSTBF;
  IlBoolean _opaqueMoving		ILVSTBF;
  IlBoolean _autoResizing		ILVSTBF;
  IlBoolean _usingCOut		ILVSTBF;
  IlBoolean _savingData		ILVSTBF;
  IlBoolean _toolTip			ILVSTBF;

  static IlBoolean	_Initialized;

public:
  // static symbol
  static IlSymbol* _S_defaultApplicationName;
  static IlSymbol* _S_defaultBufferName;
  static IlSymbol* _S_panelBaseClass;
  static IlSymbol* _S_panelHeaderFile;
  static IlSymbol* _S_applicationBaseClass;
  static IlSymbol* _S_applicationHeaderFile;
  static IlSymbol* _S_gadgetPaletteFileName;
  static IlSymbol* _S_graphicPaletteFileName;
  static IlSymbol* _S_applicationFileExtension;
  static IlSymbol* _S_stateFileExtension;
  static IlSymbol* _S_dataFileExtension;
  static IlSymbol* _S_headerFileExtension;
  static IlSymbol* _S_sourceFileExtension;
  static IlSymbol* _S_makeFileExtension;
  static IlSymbol* _S_defaultSystemName;
  static IlSymbol* _S_alignmentSpacing;
  static IlSymbol* _S_playerSpeed;
  static IlSymbol* _S_lokingPanel;
  static IlSymbol* _S_toolTip;
  static IlSymbol* _S_movingPointer;
  static IlSymbol* _S_ignoringSize;
  static IlSymbol* _S_ignoringBackground;
  static IlSymbol* _S_absolutePath;
  static IlSymbol* _S_sortingRequirements;
  static IlSymbol* _S_system;
  static IlSymbol* _S_baseClassHeader;
  static IlSymbol* _S_bitmapAlias;
  static IlSymbol* _S_toolBarCommands;
  static IlSymbol* _S_toolBarItem;
  static IlSymbol* _S_toolBarItemWidth;
  static IlSymbol* _S_toolBarItemHeight;
  static IlSymbol* _S_language;
  static IlSymbol* _S_include;
  static IlSymbol* _S_startUpCommand;
  static IlSymbol* _S_startUpCommandString;
  static IlSymbol* _S_messageDB;
  static IlSymbol* _S_objectInteractor;
  static IlSymbol* _S_filter;
  static IlSymbol* _S_helpDir;
  static IlSymbol* _S_fileBrowserType;
  static IlSymbol* _S_fileLoader;
  static IlSymbol* _S_additionalLibraries;
  static IlSymbol* _S_studioName;
  static IlSymbol* _S_studioShortName;
  static IlSymbol* _S_defaultDataDir;
  static IlSymbol* _S_defaultHeaderDir;
  static IlSymbol* _S_defaultSrcDir;
  static IlSymbol* _S_defaultObjDir;
  static IlSymbol* _S_defaultHeaderFileScope;

  IlvStSrcFileExtGetter _srcFileExtGetter;
}; // class IlvStOptions

// --------------------------------------------------------------------------
#if defined(IlvDECLAREINITCLASS)
IlvDECLAREINITSTUDIOCLASS(st_option)
#endif /* IlvDECLAREINITCLASS */

#endif /* __IlvSt_Option_H */
