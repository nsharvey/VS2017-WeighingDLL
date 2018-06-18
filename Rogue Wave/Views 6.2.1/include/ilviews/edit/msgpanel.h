// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/edit/msgpanel.h
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
// Declaration of the IlvMessagePanel class
// Defined in library ilvedit
// --------------------------------------------------------------------------

#ifndef __Ilv_Edit_Msgpanel_H
#define __Ilv_Edit_Msgpanel_H

#if !defined(__Ilv_Edit_Macros_H)
#include <ilviews/edit/macros.h>
#endif
#if !defined(__Ilv_Gadgets_Gadcont_H)
#include <ilviews/gadgets/gadcont.h>
#endif
#if !defined(__Ilv_Gadgets_Msglabel_H)
#include <ilviews/gadgets/msglabel.h>
#endif
#if !defined(__Ilv_Gadgets_Combo_H)
#include <ilviews/gadgets/combo.h>
#endif
#if !defined(__Ilv_Gadgets_Textfd_H)
#include <ilviews/gadgets/textfd.h>
#endif
#if !defined(__Ilv_Gadgets_Sheet_H)
#include <ilviews/gadgets/sheet.h>
#endif
#if !defined(__Ilv_Gadgets_Menu_H)
#include <ilviews/gadgets/menu.h>
#endif
#if !defined(__Ilv_Gadgets_Menubar_H)
#include <ilviews/gadgets/menubar.h>
#endif
#if !defined(__Ilv_Gadgets_Stdialog_H)
#include <ilviews/gadgets/stdialog.h>
#endif
#if !defined(__Ilv_Base_Message_H)
#include <ilviews/base/message.h>
#endif
#if !defined(__Ilv_Gadgets_Fbrowser_H)
#include <ilviews/gadgets/fbrowser.h>
#endif

class IlvDBMessage;
class IlvMessageSearchPanel;
class IlvMessageSavePanel;
// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvEditedMessageDatabase
    : public IlvMessageDatabase
{
 public:
    IlvEditedMessageDatabase();
    ~IlvEditedMessageDatabase();
    // ____________________________________________________________
    static IlSymbol* getDefaultLanguage();
    virtual void clean();
    virtual void writeLang(IL_STDPREF ostream&,
			   const IlSymbol*,
			   IlvEncoding encoding = IlvNoEncoding,
			   const IlSymbol* headerLang = 0) const;
    virtual IlBoolean read(IL_STDPREF istream&,
			   const IlvDisplay* d = 0,
			   const char* fName = 0);
    virtual IlvDBMessage* makeMessage(const char* message);
    virtual IlBoolean removeMessage(const char* message);
    IlvDBMessage* insertMessage(const char* message,
				IlUShort position);

    void sort(const IlSymbol* language = 0);
    const char** getMessages(IlUShort& number) const;
 private:
    char**            _messages;
    IlUShort          _numberMessages;
    IlUShort          _numberMaxMessages;
    static IlSymbol* _defaultLanguage;
    void allocateMessages(IlUShort count);
};

// --------------------------------------------------------------------------
class ILVEDTEXPORTED IlvMessagePanel
    : public IlvGadgetContainer {
 public:
    IlvMessagePanel(IlvDisplay*,
		    const char* name,
		    const char* title,
		    IlvRect*    size = 0,
		    IlBoolean  useAccelerators  = IlFalse,
		    IlBoolean  visible          = IlFalse,
		    IlvSystemView transientFor  = 0);
    IlvMessagePanel(IlvAbstractView* parent,
		    IlvRect* size = 0);
    virtual ~IlvMessagePanel();
     // ____________________________________________________________
    void                      moveDialogToMouse(IlvDialog*);
    const char*               getFileName() const;
    void                      setFileName(const char* fileName);
    IlvFileBrowser*	      getFileBrowser() const { return _fbrowser; }
    IlvEditedMessageDatabase* getDatabase() const { return _database; }
    IlvGadgetContainer*       getSearchPanel() const;
    void                      setSearchPanel(IlvMessageSearchPanel*);
    IlvGadgetContainer*       getSavePanel() const;
    void                      setSavePanel(IlvMessageSavePanel*);
    void                      showMessage(const char* name,
					  IlUShort row,
					  IlBoolean redraw = IlFalse);
    void                      showLanguages(IlBoolean redraw = IlTrue);
    void                      readMessages(IL_STDPREF istream& stream,
					   IlBoolean clean = IlTrue);
    void                      newFile();
    void                      open(const char* filename = 0,
				   IlBoolean clean = IlTrue);
    void                      save();
    void                      databaseSaved() { _modified = IlFalse; }
    void                      saveAs(const char* filename = 0);
    virtual void              quit();
    virtual IlBoolean         setLanguage(IlSymbol*);
    void                      removeMessage();
    void                      newMessage(IlUShort number = 1);
    void                      newLanguage();
    void                      removeLanguage();
    void                      sortLabel(IlSymbol* language,
					IlBoolean redraw = IlTrue);
    void                      sortName(IlBoolean redraw = IlTrue);
    void                      editMessage();
    virtual IlBoolean         appendDatabase();
    virtual IlBoolean         resetDatabase(const char* dbname = 0);
    void                      editDefaultDatabase();
    IlBoolean                 searchInLanguage(const char* filter,
					       IlUShort numlanguage,
					       IlBoolean redraw = IlTrue);
    IlBoolean                 searchInName(const char* filter,
					   IlBoolean redraw = IlTrue);
    IlBoolean                 searchEverywhere(const char* filter,
					       IlBoolean redraw = IlTrue);

    IlvSheet*                 getMessages() const
	{ return (IlvSheet*)getObject("messages"); }
    IlvTextField*             getMessage() const
	{ return (IlvTextField*)getObject("message"); }
protected:
    void                      initialize(IlvDisplay*);
    IlBoolean                canModify();
    void                      printMessage(const char* message,
					   IlBoolean redraw = IlTrue);
    IlBoolean                 search(const char* filter,
				     IlUShort col,
				     IlBoolean redraw);
    void                      found(const char* filter,
				    IlUShort col,
				    IlUShort row,
				    IlBoolean redraw);
    void                      notFound(const char* filter,
				       IlUShort col,
				       IlBoolean redraw);
private:
    char*                     _fileName;
    IlvFileBrowser*	      _fbrowser;
    IlBoolean                 _modified;
    IlvIQuestionDialog*       _dialog;
    IlvEditedMessageDatabase* _database;
    IlvPopupMenu*             _languageMenu;
    IlvMessageSearchPanel*    _searchPanel;
    IlvMessageSavePanel*      _savePanel;
    static char*              _buffer;
protected:
    char*                     getBuffer() { return _buffer; }
};

#endif /* !__Ilv_Msgpanel_H */
