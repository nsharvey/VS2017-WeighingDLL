// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/inspect/inspbook.h
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
// Declaration of the IliInspectorBook
// Defined in library dbstudio
// --------------------------------------------------------------------------
#ifndef __Ili_Inspbook_H
#define __Ili_Inspbook_H

#ifndef __IlvSt_Gadpnl_H
#  include <ivstudio/inspectors/gadpnl.h>
#endif

#ifndef __Ilv_Gadgets_Button_H
#  include <ilviews/gadgets/button.h>
#endif

#ifndef __Ilv_Gadgets_Colorch_H
#  include <ilviews/gadgets/colorch.h>
#endif

#ifndef __Ilv_Contain_Contain_H
#  include <ilviews/contain/contain.h>
#endif

#ifndef __Ilv_Util_Dialogs_H
#  include <ilviews/util/dialogs.h>
#endif

#ifndef __Ilv_Gadgets_Frame_H
#  include <ilviews/gadgets/frame.h>
#endif

#ifndef __Ilv_Gadgets_Gadcont_H
#  include <ilviews/gadgets/gadcont.h>
#endif

#ifndef __Ilv_Graphics_Holder_H
#  include <ilviews/graphics/holder.h>
#endif

#ifndef __Ilv_Base_Hash_H
#  include <ilviews/base/hash.h>
#endif

#ifndef __Ilv_Manager_Manager_H
#  include <ilviews/manager/manager.h>
#endif

#ifndef __Ilv_Base_Memory_H
#  include <ilviews/base/memory.h>
#endif

#ifndef __Ilv_Base_Message_H
#  include <ilviews/base/message.h>
#endif

#ifndef __Ilv_Manager_Holder_H
#  include <ilviews/manager/holder.h>
#endif

#ifndef __Ilv_Msglabel_H
#  include <ilviews/gadgets/msglabel.h>
#endif

#ifndef __Ilv_Gadgets_Notebook_H
#  include <ilviews/gadgets/notebook.h>
#endif

#ifndef __Ili_Clrcombo_H
#  include <ilviews/dataccess/gadgets/clrcombo.h>
#endif

#ifndef __Ili_Filecomb_H
#  include <ilviews/dataccess/gadgets/filecomb.h>
#endif

#ifndef __Ili_Inspnl_H
#  include <ilviews/dataccess/inspect/inspnl.h>
#endif

#ifndef __Ili_Inspgad_H
#  include <ilviews/dataccess/inspect/inspgad.h>
#endif

#define IliDeclInspBookAccess(typ,fct,num,nam) \
typ* get##fct() const { return (typ*)(_pages[num]->getObject(nam)); }

enum IliInspBookError {
  IliInspBookMissingDataSource = 0,
  IliInspBookMissingColumn,
  IliInspBookMissingFilename,
  IliInspBookSameAction,
  IliInspBookInvalidColumnName,
  IliInspBookErrorCount
};

class IliNotebookUsage;

// --------------------------------------------------------------------------
// IliInspectorServices
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliInspectorServices
{
public:
  IliInspectorServices(IlvDisplay*);
  ~IliInspectorServices();

  //---- Error ----
  IlBoolean addError(const char*);
  IlBoolean addError(IliInspBookError,const char* txt = 0);
  void reportErrors(IlvAbstractView*);

  //---- Format ----
  IliTable* getFormatsTable () const;
  void setFormatsDatatype (const IliDatatype*) const;
  void setFormatsAllDatatypes () const;

private:
  //---- Error ----
  IliErrorList _errors;
  IliErrorReporter _errorReporter;

  //---- Format ----
  IliTable* _formatsTable;

  //---- display ----
  IlvDisplay* _display;
};

// --------------------------------------------------------------------------
// IliInspectorBook
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliInspectorBook
  : public IlvStIGadgetInspectorPanel, public IliInspectorServices {
public:
  IliInspectorBook(IlvDisplay* display, const char*,
		   IlvSystemView transientFor = 0,
		   IlvStIAccessor::UpdateMode = IlvStIAccessor::OnApply);
  ~IliInspectorBook();

  virtual void initializeEditors();
  virtual void applyChange(IlvGraphic*);
  virtual void initFrom(IlvGraphic*);

  //---- Pages ----
  virtual void pagesDefine();
  virtual void pageInit(IlInt);
  virtual void pageInitFrom(IlInt,IlvGraphic*);
  virtual IlBoolean pageValidate(IlInt);
  virtual void pageApply(IlInt,IlvGraphic*);
  virtual void pageResetInputModified(IlInt);
  virtual void pageCustomGeneralPage(IlInt);
  void disableGadget(IlInt pageno,const char* name);

  //---- Errors ----
  void setCurrentPageForError(IlInt);
  IlInt getCurrentPageForError() const;

  //---- columns ----
  IlBoolean isValidColumnForDataSource(IliDataSource*,const char*) const;
  IlBoolean isValidColumnForDataSource(const char*,const char*) const;
  IlBoolean isValidColumnsForDataSource(const char*,IliString*,IlInt) const;
  IliDataSource* getDataSourceFromName(const char*) const;

  //---- Others ----
  void selectNewColor(IliString& s);
  void selectNewHtmlColor(IliString& s);

  IlvGraphicHolder* getObjectHolder() const;
  IlvGraphic* getObject(IlInt,const char*) const;
  IlvGadgetContainer* getPage(IlInt) const;

  //---- Notification ----
  void addInputModifiedCallback(IlInt,const char*,IlvSymbol*);
  void addFieldItfModifiedCallback(IlInt,const char*);
  void addDsDeleteRowModifiedCallback(IlInt,const char*);
  void setModified();

protected:
  IlBoolean _enableModified;
  IlvStIPropertyAccessor* _access;

  //---- Notebook ----
  IlvGadgetContainer** _pages;
  IlInt _pageCount;

  //---- Color ----
  IlvColorSelector* _colorDlg;

  //---- Errors ----
  IlInt _pageForError;
};

// --------------------------------------------------------------------------
// IliInspectorProperties
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliInspectorProperties
  : public IliInspectorBook
{
public:
  IliInspectorProperties(IlvDisplay*, const char*,IlvSystemView transient = 0);
  ~IliInspectorProperties();

  virtual void initializeEditors();
  virtual void applyChange(IlvGraphic*);
  virtual void initFrom(IlvGraphic*);

  //---- Tags ----
  virtual void defineTags(IlInt,IliDbGadgetPanel*);

  //---- Pages ----
  virtual void pagesDefine();

  //---- Properties ----
  virtual void propertiesPageDefine(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageInitFrom(IlInt,IliDbGadgetPanel*,IlvGraphic*);
  virtual IlBoolean propertiesPageValidate(IlInt,IliDbGadgetPanel*);
  virtual void propertiesPageApply(IlInt,IliDbGadgetPanel*,IlvGraphic*);

  void addPageProperties(const char*,IlInt = 0);

  //---- Other ----
  IliInspectorGadget* getInspectorGadget(IlInt pageno);
  IliDbGadgetPanel* getGadgetProperties(IlInt pageno);

protected:
  IliDbGadgetPanel** _inspProps;
};

#define IliDeclNotebookAccess(usage,typ,fct,num,nam) \
typ* get##fct() const { return (typ*)(usage->getObject(num,nam)); }

// --------------------------------------------------------------------------
// IliNotebookUsage
// --------------------------------------------------------------------------
class ILV_DBS_EXPORTED IliNotebookUsage : public IliInspectorServices
{
public:
  IliNotebookUsage(IlvStInspectorPanel* pnl,const char*,IlInt count = -1);
  ~IliNotebookUsage();

  //---- Pages ----
  IlvGraphic* getObject(IlInt,const char*);
  IlvGadgetContainer* getPage(IlInt page);
  IlvDisplay* getDisplay();
  void disableGadget(IlInt pageno,const char* name);
  IlInt getPageCount() const;

  //---- Data sources and tables ----
  void buildDataSourceList(IlvGraphicHolder*,IliTable*,IlInt = 1);
  IliDataSource* getDataSourceFromName(const char*) const;

  void addNullRow(IliTable* tbl,IlInt count);

  //---- Notification ----
  void setModified();

protected:
  //---- Panel ----
  IlvStInspectorPanel* _panel;
  IliString _accessor;

  //---- Pages ----
  IlvGadgetContainer** _pages;
  IlInt _pageCount;

  //---- Data sources ----
  IlvStringHashTable* _hshTable;
};

#endif
