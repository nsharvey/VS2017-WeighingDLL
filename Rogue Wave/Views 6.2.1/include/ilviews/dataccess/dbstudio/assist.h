// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/dbstudio/assist.h
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
// Rogue Wave Views - Data Access add-on
// --------------------------------------------------------------------------
// Declaration of the IliAssistant class
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Assist_H
#define __Ili_Assist_H

#ifndef __Ilv_Base_View_H
#  include <ilviews/base/view.h>
#endif

#ifndef __IlvSt_Studio_H
#  include <ivstudio/studio.h>
#endif

#ifndef __IlvSt_Panel_H
#  include <ivstudio/panel.h>
#endif

#ifndef __Ilv_Manager_Manager_H
#  include <ilviews/manager/manager.h>
#endif

#ifndef __Ilv_Gadgets_Notebook_H
#  include <ilviews/gadgets/notebook.h>
#endif

#ifndef __Ilv_Gadgets_Colorch_H
#  include <ilviews/gadgets/colorch.h>
#endif

#ifndef __Ilv_Gadgets_Fontsel_H
#  include <ilviews/gadgets/fontsel.h>
#endif

#ifndef __Ili_Dbfield_H
#  include <ilviews/dataccess/gadgets/dbfield.h>
#endif

// --------------------------------------------------------------------------
// enum
// --------------------------------------------------------------------------
enum IliOptNavigator {
  IliOptNavigNavigation = 0,
  IliOptNavigInsert,
  IliOptNavigDelete,
  IliOptNavigValidation,
  IliOptNavigSelect,
  IliOptNavigClear,
  IliOptNavigPosition,
  IliOptNavigRowsCount,
  IliOptNavigQueryMode,
  IliOptNavigNbTag
};

enum IliNavigatorPosition {
  IliNavigPosTop = 0,
  IliNavigPosBottom,
  IliNavigPosNbTag
};

enum IliLayoutField {
  IliTopToBottom,
  IliLeftToRight,
  IliLayoutFieldNbTag
};

enum IliColorType {
  IliColorTitle = 0,
  IliColorLabel,
  IliColorField,
  IliColorTypeNbTag
};

enum IliFontType {
  IliFontTitle = 0,
  IliFontLabel,
  IliFontField,
  IliFontTypeNbTag
};

class IliDlgAssData;
class IliDlgAssLabel;
class IliDlgAssNavig;
class IliDlgAssTitle;
class IliAssistant;

// --------------------------------------------------------------------------
// IliAssistDefine
// --------------------------------------------------------------------------
class IliAssistDefine : public IliRefCounted {
public:
  IliAssistDefine(IlvDisplay*);
  IliAssistDefine(IliAssistDefine&);

  void resetColumns();
  inline IlInt getColumnsCount();
  void allocColumns(IlInt, IlBoolean = IlTrue);
  inline void setColumnName(IlInt, const char*);
  inline void setColumnTitle(IlInt,const char*);
  inline void setColumnStyle(IlInt, IliDbFieldStyle);
  inline void setColumnVisible(IlInt, IlBoolean);
  inline const char* getColumnName(IlInt);
  const char* getColumnTitle(IlInt);
  inline IliDbFieldStyle getColumnStyle(IlInt);
  inline IlBoolean isColumnVisible(IlInt);

  inline void useTableGadget(IlBoolean);
  inline IlBoolean isUsedTableGadget() const;

  inline void setPositionLabel(IlInt);
  inline IlInt getPositionLabel();

  inline void setOptionNavigator(IliOptNavigator, IlBoolean);
  inline IlBoolean isOptionNavigator(IliOptNavigator);
  IlBoolean isThereNavigator();
  inline void setNavigatorPosition(IliNavigatorPosition);
  inline IliNavigatorPosition getNavigatorPosition();

  IliAssistDefine& operator=(IliAssistDefine&);

  inline void setDataSourceName(const char*);
  inline const char* getDataSourceName();
  inline void setDataSource(IliDataSource*);
  inline IliDataSource* getDataSource();

  inline void setTitle(const char*);
  inline const char* getTitle();
  inline void displayTitleFrame(IlBoolean);
  inline IlBoolean isDisplayTitleFrame();
  inline IlBoolean isThereTitle();

  inline void defineLayoutField(IliLayoutField);
  inline IliLayoutField getLayoutField();

  inline void setColorTitle(IlvColor*);
  inline void setColorLabel(IlvColor*);
  inline void setColorField(IlvColor*);
  inline IlvColor* getColorTitle();
  inline IlvColor* getColorLabel();
  inline IlvColor* getColorField();
  inline const char* getColorTitleName();
  inline const char* getColorLabelName();
  inline const char* getColorFieldName();

  inline void setFontTitle(IlvFont*);
  inline void setFontLabel(IlvFont*);
  inline void setFontField(IlvFont*);
  inline IlvFont* getFontTitle();
  inline IlvFont* getFontLabel();
  inline IlvFont* getFontField();
  inline const char* getFontTitleName();
  inline const char* getFontLabelName();
  inline const char* getFontFieldName();

protected:
  ~IliAssistDefine();
  void init();
  inline IlBoolean checkColumn(IlInt);

  IliString _dataSourceName;
  IliDataSource* _dataSource;

  IlInt _columnsCount;
  IliString* _columnsName;
  IliString* _columnsTitle;
  IlBoolean* _columnsVisible;
  IlInt _positionLabel;
  IliDbFieldStyle* _columnsStyle;
  IlBoolean _useTableGadget;

  IliString _paramColor[IliColorTypeNbTag+1];
  IliString _paramFont[IliFontTypeNbTag+1];

  IlBoolean _optionNavigator[IliOptNavigNbTag+1];
  IlInt _navigatorPosition;

  IliString _title;
  IlBoolean  _titleFrame;

  IlInt _layoutField;

  IlvDisplay *_display;
};

// --------------------------------------------------------------------------
// IliAssistDialog
// --------------------------------------------------------------------------
class IliAssistDialog
  : public IlvDialog {
public:
    IliAssistDialog (IliAssistant*);
    ~IliAssistDialog ();

    virtual void apply ();
    IlBoolean perform ();

    void comboIsClosed(IlBoolean = IlTrue);

    inline IliTable* getTable();

    inline IlBoolean isColumnVisible(int col);

    void buttonModifyColor(const char*);
    void buttonModifyFont(const char*);

    void initData(IliAssistDefine*);
    void initBookData();
    void initBookTitle();
    void initBookLabels();
    void initBookNavig();
    void initDataBookData();
    void initDataBookTitle();
    void initDataBookLabels();
    void initDataBookNavig();
    IlBoolean applyBookData();
    IlBoolean applyBookTitle();
    IlBoolean applyBookLabels();
    IlBoolean applyBookNavig();

    IlvNotebook* getNTNoteBook() const
    { return (IlvNotebook*)getObject("NTNoteBook"); }

    void checkBoxTgClicked();
  void checkQueryModeOption();
protected:

    IliDlgAssData* _ntData;
    IliDlgAssLabel* _ntLabels;
    IliDlgAssNavig* _ntNavig;
    IliDlgAssTitle* _ntTitle;

    IliAssistDefine*  _data;
    IliAssistDefine*  _tmpData;
    //IlvStringHashTable* _hshTable;

    IlvColorSelector*   _colorDlg;
    IlvFontSelector* _fontDlg;

    IliAssistant* _assistant;
};

// --------------------------------------------------------------------------
// IliAssistant
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliAssistant {
public:
  IliAssistant ();
  ~IliAssistant ();

  inline IlvView* getView () const;
  inline void setView (IlvView*);

  inline IlvManager* getManager () const;
  inline void setManager (IlvManager*);

  IlBoolean queryGenerateSimpleForm ();
  IlBoolean generateSimpleForm ();

  IliDbField* makeField (IlInt colno);
  IliTableGadget* makeTableGadget(IlvPoint& pos,IlvPoint& size, IlvPos);
  void makeNavigator(IlvPoint&);
  void makeTitle(IlvPoint&);

  inline IliAssistDefine* getAssistDefine();
protected:
  void cleanBeforeBuild();
  void getSizeDomain(IlvPoint&);
  void computeSizeTitle(IlvPoint&);
  void searchMenu();
  void adjustSizeObject(IliDbField*, IlInt);
  IliAssistDefine* _data;
  IlInt _heightTitle;
  IlInt _widthTitle;
  IlInt _heightMenu;

  IlvManager* _manager;
  IlvView* _view;
};


// --------------------------------------------------------------------------
// IliAssistDefine : inline functions
// --------------------------------------------------------------------------
inline void
IliAssistDefine::setDataSourceName(const char* name) {
  _dataSourceName = name;
}

inline const char*
IliAssistDefine::getDataSourceName() {
  return _dataSourceName;
}

inline void
IliAssistDefine::setDataSource(IliDataSource* ds) {
  _dataSource = ds;
}

inline IliDataSource*
IliAssistDefine::getDataSource() {
  return _dataSource;
}

inline IlBoolean
IliAssistDefine::checkColumn(IlInt col) {
  return ((col < 0) || (col >= _columnsCount))? IlFalse : IlTrue;
}

inline IlInt
IliAssistDefine::getColumnsCount() {
  return _columnsCount;
}

inline void
IliAssistDefine::setOptionNavigator(IliOptNavigator opt,
				      IlBoolean display) {
  _optionNavigator[opt] = display;
}

inline IlBoolean
IliAssistDefine::isOptionNavigator(IliOptNavigator opt) {
  return _optionNavigator[opt];
}

inline void
IliAssistDefine::setColumnName(IlInt col, const char* name) {
  if (checkColumn(col)) _columnsName[col] = name;
}

inline void
IliAssistDefine::setColumnTitle(IlInt col, const char* name) {
  if (checkColumn(col)) _columnsTitle[col] = name;
}

inline void
IliAssistDefine::setColumnVisible(IlInt col, IlBoolean visible) {
  if (checkColumn(col)) _columnsVisible[col] = visible;
}

inline void
IliAssistDefine::setPositionLabel(IlInt pos) {
  _positionLabel = pos;
}

inline IlInt
IliAssistDefine::getPositionLabel() {
  return _positionLabel;
}

inline void
IliAssistDefine::setColorTitle(IlvColor* color) {
  _paramColor[IliColorTitle] = color->getName();
}

inline void
IliAssistDefine::setColorLabel(IlvColor* color) {
  _paramColor[IliColorLabel] = color->getName();
}

inline void
IliAssistDefine::setColorField(IlvColor* color) {
  _paramColor[IliColorField] = color->getName();
}

inline IlvColor*
IliAssistDefine::getColorTitle() {
  return _display->getColor(_paramColor[IliColorTitle]);
}

inline IlvColor*
IliAssistDefine::getColorLabel() {
  return _display->getColor(_paramColor[IliColorLabel]);
}

inline IlvColor*
IliAssistDefine::getColorField() {
  return _display->getColor(_paramColor[IliColorField]);
}

inline const char*
IliAssistDefine::getColorTitleName() {
  return (const char*)(_paramColor[IliColorTitle]);
}

inline const char*
IliAssistDefine::getColorLabelName() {
  return (const char*)(_paramColor[IliColorLabel]);
}

inline const char*
IliAssistDefine::getColorFieldName() {
  return (const char*)(_paramColor[IliColorField]);
}

inline const char*
IliAssistDefine::getColumnName(IlInt col) {
  return (checkColumn(col))? (const char*)(_columnsName[col]) : 0;
}

inline IlBoolean
IliAssistDefine::isColumnVisible(IlInt col) {
  return (checkColumn(col))? _columnsVisible[col] : IlFalse;
}

inline void
IliAssistDefine::setNavigatorPosition(IliNavigatorPosition pos) {
  _navigatorPosition = pos;
}

inline IliNavigatorPosition
IliAssistDefine::getNavigatorPosition() {
  return (IliNavigatorPosition)_navigatorPosition;
}

inline void
IliAssistDefine::setTitle(const char* title) {
  _title = title;
}

inline const char*
IliAssistDefine::getTitle() {
  return (const char*)_title;
}

inline void
IliAssistDefine::displayTitleFrame(IlBoolean draw) {
  _titleFrame = draw;
}

inline IlBoolean
IliAssistDefine::isDisplayTitleFrame() {
  return _titleFrame;
}

inline IlBoolean
IliAssistDefine::isThereTitle() {
  return (_title.length() > 0);
}

inline void
IliAssistDefine::defineLayoutField(IliLayoutField layout) {
  _layoutField = layout;
}

inline IliLayoutField
IliAssistDefine::getLayoutField() {
  return (IliLayoutField)_layoutField;
}

inline void
IliAssistDefine::setFontTitle(IlvFont* font) {
  _paramFont[IliFontTitle] = font->getName();
}

inline void
IliAssistDefine::setFontLabel(IlvFont* font) {
  _paramFont[IliFontLabel] = font->getName();
}

inline void
IliAssistDefine::setFontField(IlvFont* font) {
  _paramFont[IliFontField] = font->getName();
}

inline IlvFont*
IliAssistDefine::getFontTitle() {
  return _display->getFont(_paramFont[IliFontTitle]);
}

inline IlvFont*
IliAssistDefine::getFontLabel() {
  return _display->getFont(_paramFont[IliFontLabel]);
}

inline IlvFont*
IliAssistDefine::getFontField() {
  return _display->getFont(_paramFont[IliFontField]);
}

inline const char*
IliAssistDefine::getFontTitleName() {
  return (const char*)(_paramFont[IliFontTitle]);
}

inline const char*
IliAssistDefine::getFontLabelName() {
  return (const char*)(_paramFont[IliFontLabel]);
}

inline const char*
IliAssistDefine::getFontFieldName() {
  return (const char*)(_paramFont[IliFontField]);
}

inline void
IliAssistDefine::setColumnStyle(IlInt col, IliDbFieldStyle style) {
  if (checkColumn(col)) _columnsStyle[col] = style;
}

inline IliDbFieldStyle
IliAssistDefine::getColumnStyle(IlInt col) {
  return (checkColumn(col))? _columnsStyle[col] : IliEntryFieldStyle;
}

inline void
IliAssistDefine::useTableGadget(IlBoolean use) {
  _useTableGadget = use;
}

inline IlBoolean
IliAssistDefine::isUsedTableGadget() const {
  return _useTableGadget;
}

// --------------------------------------------------------------------------
// IliAssistDialog : inline functions
// --------------------------------------------------------------------------
inline IliTable*
IliAssistDialog::getTable() {
  return (_tmpData->getDataSource()
	  ? _tmpData->getDataSource()->getTable()
	  : (IliTable*)NULL);
}

inline IlBoolean
IliAssistDialog::isColumnVisible(int col) {
  return _tmpData->isColumnVisible(col);
}

// --------------------------------------------------------------------------
// IliAssistant : inline functions
// --------------------------------------------------------------------------
inline IliAssistDefine*
IliAssistant::getAssistDefine() {
  return _data;
}

inline IlvView*
IliAssistant::getView () const {
  return _view;
}

inline void
IliAssistant::setView (IlvView* view) {
  _view = view;
}

inline IlvManager*
IliAssistant::getManager () const {
  return _manager;
}

inline void
IliAssistant::setManager (IlvManager* mgr) {
  _manager = mgr;
}

#endif
