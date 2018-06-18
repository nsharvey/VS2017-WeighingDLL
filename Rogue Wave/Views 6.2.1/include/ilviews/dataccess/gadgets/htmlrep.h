// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/gadgets/htmlrep.h
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
// Declaration of the IliHTMLReporter class
// Defined in library dbgadget
// --------------------------------------------------------------------------
#ifndef __Ili_Htmlrep_H
#define __Ili_Htmlrep_H

#if !defined(__Ilv_Macros_H)
#  include <ilviews/macros.h>
#endif
#if !defined(__Ilv_Base_View_H)
#  include <ilviews/base/view.h>
#endif
#if !defined(__Il_Xml_H)
#  include <ilog/xml.h>
#endif
#if !defined(__Ili_Reposit_H)
#  include <ilviews/dataccess/reposit.h>
#endif
#if !defined(__Ili_Dsusage_H)
#  include <ilviews/dataccess/gadgets/dsusage.h>
#endif
#if !defined(__Ili_Gdtmodel_H)
#  include <ilviews/dataccess/gadgets/gdtmodel.h>
#endif

#if defined(IL_STD)
#  include <fstream>
#else
#  include <fstream.h>
#endif

// --------------------------------------------------------------------------
enum IliHTMLModelName {
    IliHTMLModelTableClassicName = 0,
    IliHTMLModelFormClassicName,
    IliHTMLModelTableName,
    IliHTMLModelFormName,
    IliHTMLModelFormDynamicName,
    IliHTMLModelOtherName,
    IliHTMLModelNameCount
};

// --------------------------------------------------------------------------
enum IliXMLNotification {
    IliXMLInsertNotification = 0,
    IliXMLChangeNotification,
    IliXMLDeleteNotification,
    IliXMLNotificationCount
};

// --------------------------------------------------------------------------
enum IliXMLModelType {
    IliXMLExportModelType = 0,
    IliXMLImportModelType,
    IliXMLStreamModelType,
    IliXMLModelTypeCount
};

class IliHTMLReporter;

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliHTMLReporterModel
    : public IliGadgetModel
{
public:
    friend class IliHTMLReporter;

    IliHTMLReporterModel(IliHTMLReporter* = 0);
    virtual ~IliHTMLReporterModel();

    virtual void	write(IL_STDPREF ostream&);
    virtual void	read(IL_STDPREF istream&);

    // Basic methods
    IliDeclareModel();

    // Gadget
    void		setHTMLReporter(IliHTMLReporter*);
    IliHTMLReporter*	getHTMLReporter() const;

    // Stream
    IL_STDPREF ostream& getStream() const;

    // Table
    const IliTable*	getTable() const;
    const IliTableBuffer* getTableBuffer() const;
    IlInt		getRowCount() const;
    IlInt		getRowNumber() const;

    // Document properties
    void		setDocumentBackground(const char*);
    const char*		getDocumentBackground() const;
    void		setDocumentTitle(const char*);
    const char*		getDocumentTitle() const;
    void		setDocumentCopyright(const char*);
    const char*		getDocumentCopyright() const;

    // Table of contents properties
    void		setTableOfContents(IlBoolean);
    IlBoolean		hasTableOfContents() const;
    void		setTableOfContentsTitle(const char*);
    const char*		getTableOfContentsTitle() const;
    void		setTableOfContentsAtBeginning(IlBoolean);
    IlBoolean		isTableOfContentsAtBeginning() const;
    void		setTableOfContentsColumnName(const char*);
    const char*		getTableOfContentsColumnName() const;

    const char*		getTableOfContentsEntry() const;
    const char*		getTableOfContentsLocation() const;
    IlInt		getTableOfContentsNumber() const;

    IlBoolean		isTableOfContentsGenerated() const;
    // First page properties
    void		setFirstPageTitle(const char*);
    const char*		getFirstPageTitle() const;
    void		setFirstPagePictureName(const char*);
    const char*		getFirstPagePictureName() const;

    // Pages properties
    const char*		getRowLocationName() const;

    // Last page properties

    // Document
    virtual void	initialize(IL_STDPREF ostream*);
    virtual void	reportBeginDocument();
    virtual void	reportEndDocument();

    // First page
    virtual void	reportFirstPageHeading();
    virtual void	reportFirstPageContents();
    virtual void	reportFirstPageFooting();

    // Table of contents
    virtual void	reportTableHeading();
    virtual void	reportTableTitle();
    virtual void	reportTableBeginEntries();
    virtual void	reportTableEntry();
    virtual void	reportTableEndEntries();
    virtual void	reportTableFooting();

    // Pages
    virtual void	reportPages();
    virtual void	reportHeading();
    virtual void	reportBeginRows();
    virtual void	reportRowContent();
    virtual void	reportEndRows();
    virtual void	reportFooting();

    // Last page
    virtual void	reportLastPageHeading();
    virtual void	reportLastPageContents();
    virtual void	reportLastPageFooting();

    // Tools
    const char*		getColumnName(IlInt) const;
    const char*		getColumnValue(IliTableBuffer*, IlInt);
    IlvAlignment	getColumnAlignment(IlInt) const;

    // Tools html
    const char*		getTagForAlignment(IlvAlignment) const;

    // html single tag
    virtual void	tagParagraph();
    virtual void	tagTradeMark();
    virtual void	tagSpace();

    // complexe tag
    virtual void	tagNewLine(IlInt = 1);
    virtual void	tagBar(IlInt = 2);
    virtual void	tagText(const char*);
    virtual void	tagInput(const char*, const char* = 0);
    virtual void	tagDefineLocation(const char*, const char*);
    virtual void	tagLinkToLocation(const char*, const char*);
    virtual void	tagLinkToFile(const char*, const char*);
    virtual void	tagLinkToFileLocation(const char*,
					      const char*,
					      const char*);
    virtual void	tagBeginBody(const char* = 0, const char* opt = 0);
    virtual void	tagHeadTitle(const char*);
    virtual void	tagBeginHeader(IlInt = 2, IlvAlignment = IlvLeft);
    virtual void	tagEndHeader(IlInt = 2);
    virtual void	tagPicture(const char*, const char* opt = 0);

    // DataAccess html tag
    virtual void	tagDataAccessChapiter(const char*,
					      const char*,
					      const char*,
					      IlvAlignment,
					      IlInt);
    virtual void	tagDataAccessLinkToLocation(const char*,
						    const char*,
						    IlInt);
    // html begin tag
    virtual void	tagBeginCenter();
    virtual void	tagBeginStrong();
    virtual void	tagBeginBold();
    virtual void	tagBeginItalic();
    virtual void	tagBeginUnderline();
    virtual void	tagBeginList();
    virtual void	tagBeginListOrdered();
    virtual void	tagBeginListItem();
    virtual void	tagBeginHtml();
    virtual void	tagBeginHead();
    virtual void	tagBeginCodeListing();
    virtual void	tagBeginTable(const char* opt = 0);
    virtual void	tagBeginFont(const char* opt = 0);
    virtual void	tagBeginTableHeader(const char* opt = 0);
    virtual void	tagBeginTableRow(const char* opt = 0);
    virtual void	tagBeginTableColumn(const char* opt = 0);
    virtual void	tagBeginScript(const char* opt = 0);
    virtual void	tagBeginForm(const char* opt = 0);

    // html end tag
    virtual void	tagEndCenter();
    virtual void	tagEndStrong();
    virtual void	tagEndBold();
    virtual void	tagEndItalic();
    virtual void	tagEndUnderline();
    virtual void	tagEndTable();
    virtual void	tagEndList();
    virtual void	tagEndListOrdered();
    virtual void	tagEndListItem();
    virtual void	tagEndBody();
    virtual void	tagEndHtml();
    virtual void	tagEndHead();
    virtual void	tagEndCodeListing();
    virtual void	tagEndFont();
    virtual void	tagEndTableHeader();
    virtual void	tagEndTableRow();
    virtual void	tagEndTableColumn();
    virtual void	tagEndScript();
    virtual void	tagEndForm();

    // Other
    virtual void	initFrom(const IliHTMLReporterModel&);

protected:
    IliHTMLReporter*	_reporter;
    IL_STDPREF ostream* _file;
    IlvDisplay*		_display;

    // Table
    IliTable*		_table;
    IliTableBuffer*	_buffer;
    IlInt		_rowCount;
    IlInt		_rowno;

    // Document properties
    IliString		_docBackground;
    IliString		_docTitle;
    IliString		_docCopyright;

    // Table of contents properties
    IlBoolean		_tableOfContents;
    IlBoolean		_tocBegin;
    IliString		_tocTitle;
    IliString		_tocColName;
    IliString		_tocEntry;
    IliString		_tocLocation;
    IlInt		_tocNumber;

    // First page properties
    IliString		_firstTitle;
    IliString		_firstPicture;

    // Pages properties
    IliString		_rowLocationName;

    // Last page properties

protected:
    // Internal tag
    void		drawCell(const char*,
				 const char*,
				 const char*,
				 const char*,
				 IlvAlignment,
				 IlBoolean,
				 const char* = 0);
    // Other
    const char*		readMessage(const char*, const char*);

private:
    // Table of contents accessor for reporter
    void		setTableOfContentsEntry(const char*);
    void		setTableOfContentsLocation(const char*);
    void		setTableOfContentsNumber(IlInt);
};

// --------------------------------------------------------------------------
// Macro for IliHTMLReporterModel
// --------------------------------------------------------------------------
#define IliRegisterHTMLReporterModel(cl) IliHTMLReporter::RegisterModel(new cl)

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliHTMLModelTableClassic
    : public IliHTMLReporterModel
{
public:
    IliHTMLModelTableClassic(IliHTMLReporter* = 0);

    virtual void	initialize(IL_STDPREF ostream*);

    // Basic methods
    IliDeclareModel();
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliHTMLModelFormClassic
    : public IliHTMLReporterModel
{
public:
    IliHTMLModelFormClassic(IliHTMLReporter* = 0);

    virtual void	initialize(IL_STDPREF ostream*);

    // Basic methods
    IliDeclareModel();

    // Pages
    virtual void	reportPages();
    virtual void	reportHeading();
    virtual void	reportBeginRows();
    virtual void	reportRowContent();
    virtual void	reportEndRows();
    virtual void	reportFooting();

protected:
    // Internal tag
    void		drawRow(const char*,
				const char*,
				const char*,
				const char*,
				IlvAlignment);
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliHTMLModelTable
    : public IliHTMLModelTableClassic
{
public:
    IliHTMLModelTable(IliHTMLReporter* = 0);

    // Basic methods
    IliDeclareModel();

    // Document
    virtual void	initialize(IL_STDPREF ostream*);

    virtual void	reportFirstPageFooting();

    virtual void	reportTableTitle();
    virtual void	reportTableEndEntries();
    virtual void	reportHeading();
    virtual void	reportBeginRows();
    virtual void	reportRowContent();
    virtual void	reportEndRows();
    virtual void	reportFooting();
    virtual void	reportLastPageFooting();
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliHTMLModelForm
    : public IliHTMLModelFormClassic
{
public:
    IliHTMLModelForm(IliHTMLReporter* =0);

    // Basic methods
    IliDeclareModel();

    // Document
    virtual void	initialize(IL_STDPREF ostream*);

    virtual void	reportFirstPageFooting();

    virtual void	reportTableTitle();
    virtual void	reportTableEndEntries();
    virtual void	reportHeading();
    virtual void	reportRowContent();
    virtual void	reportFooting();
    virtual void	reportLastPageFooting();
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliHTMLModelFormDynamic
    : public IliHTMLModelTableClassic
{
public:
    IliHTMLModelFormDynamic(IliHTMLReporter* = 0);

    // Basic methods
    IliDeclareModel();

    // Document
    virtual void	initialize(IL_STDPREF ostream*);

    // First page
    virtual void	reportFirstPageHeading();
    virtual void	reportFirstPageContents();
    virtual void	reportFirstPageFooting();

    // Table of contents
    virtual void	reportTableTitle();
    virtual void	reportTableBeginEntries();
    virtual void	reportTableEntry();
    virtual void	reportTableEndEntries();

    // Main page
    virtual void	reportHeading();
    virtual void	reportBeginRows();
    virtual void	reportRowContent();
    virtual void	reportEndRows();
    virtual void	reportFooting();

    // Last page
    virtual void	reportLastPageFooting();

protected:
    virtual void	createFunctionRow();
    virtual void	createFunctionDisplay();
    virtual void	createDataTable();
    virtual void	createFunctionGo();
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliHTMLReporter
    : public IliDataGem
{
public:
    IliHTMLReporter(IlvDisplay*		display,
		    const IlvPoint&	at,
		    IlUShort		thickness = IlvDefaultGadgetThickness,
		    IlvPalette*		palette = 0);
    virtual ~IliHTMLReporter();

    DeclareTypeInfo();
    DeclareIOConstructors(IliHTMLReporter);

    // Look
    virtual IlvBitmap*	getBitmap() const;

    // Stream
    IL_STDPREF ostream&	getStream() const;

    // Reporter
    void		setFilename(const char* name);
    const char*		getFilename() const;
    void		report();
    void		reportTableOfContents();

    // Data Source
    void		setDataSourceName(const char* name);
    const char*		getDataSourceName() const;
    void		setDataSource(IliDataSource* ds);
    IliDataSource*	getDataSource() const;

    // Table
    const IliTable*	getTable() const;
    const IliTableBuffer* getTableBuffer() const;
    IlInt		getRowCount() const;
    IlInt		getRowNumber() const;

    // Model
    void		setPredefinedModel(IliHTMLModelName mod);
    IliHTMLModelName	getPredefinedModel() const;
    void		setModelName(const char* mod);
    const char*		getModelName() const;
    IliHTMLReporterModel* getModel() const;

    IliDeclareDataAccessorForModel(IliHTMLReporterModel);
    IliDeclareAccessorForModel(IliHTMLReporterModel);

    // Document properties
    void		setDocumentBackground(const char* color);
    const char*		getDocumentBackground() const;
    void		setDocumentTitle(const char* title);
    const char*		getDocumentTitle() const;
    void		setDocumentCopyright(const char* cop);
    const char*		getDocumentCopyright() const;

    void		enableHTMLComments(IlBoolean);
    IlBoolean		isHTMLCommentsEnabled() const;

    // Table of contents properties
    void		setTableOfContents(IlBoolean has);
    IlBoolean		hasTableOfContents() const;
    void		setTableOfContentsTitle(const char* title);
    const char*		getTableOfContentsTitle() const;
    void		setTableOfContentsAtBeginning(IlBoolean beginning);
    IlBoolean		isTableOfContentsAtBeginning() const;
    void		setTableOfContentsColumnName(const char* name);
    const char*		getTableOfContentsColumnName() const;

    // First page properties
    void		setFirstPageTitle(const char* title);
    const char*		getFirstPageTitle() const;
    void		setFirstPagePictureName(const char* name);
    const char*		getFirstPagePictureName() const;

    // Pages properties
    const char*		getRowLocationName() const;

    // Last page properties

    // Document
    virtual void	reportBeginDocument();
    virtual void	reportEndDocument();

    // First page
    virtual void	reportFirstPageHeading();
    virtual void	reportFirstPageContents();
    virtual void	reportFirstPageFooting();

    // Table of contents
    virtual void	reportTableHeading();
    virtual void	reportTableTitle();
    virtual void	reportTableBeginEntries();
    virtual void	reportTableEntry();
    virtual void	reportTableEndEntries();
    virtual void	reportTableFooting();

    // Pages
    virtual void	reportPages();
    virtual void	reportHeading();
    virtual void	reportBeginRows();
    virtual void	reportRowContent();
    virtual void	reportEndRows();
    virtual void	reportFooting();

    // Last page
    virtual void	reportLastPageHeading();
    virtual void	reportLastPageContents();
    virtual void	reportLastPageFooting();

    // Tools
    IlBoolean		isColumnVisible(IlInt colno) const;
    const char*		getColumnName(IlInt colno) const;
    const char*		getColumnValue(IlInt colno) const;
    const char*		getColumnValue(IliTableBuffer*	buff,
				       IlInt		colno) const;
    const char*		getTableOfContentsEntry() const;
    const char*		getTableOfContentsLocation() const;
    IlInt		getTableOfContentsNumber() const;

    // html single tag
    void		tagParagraph();
    void		tagTradeMark();
    void		tagSpace();

    // Complex tag
    void		tagNewLine(IlInt count = 1);
    void		tagBar(IlInt size = 2);
    void		tagText(const char* text);
    void		tagInput(const char*, const char* = 0);
    void		tagDefineLocation(const char* loc, const char* text);
    void		tagLinkToLocation(const char* link, const char* text);
    void		tagLinkToFile(const char* file, const char* text);
    void		tagLinkToFileLocation(const char* file,
					      const char* loc,
					      const char* txt);
    void		tagBeginBody(const char* color = 0,
				     const char* opt = 0);
    void		tagHeadTitle(const char* title);
    void		tagBeginHeader(IlInt		size = 2,
				       IlvAlignment	align = IlvLeft);
    void		tagEndHeader(IlInt size = 2);
    void		tagPicture(const char* filename, const char* opt = 0);

    // DataAccess html tag
    void		tagDataAccessChapiter(const char*,
					      const char*,
					      const char*,
					      IlvAlignment,
					      IlInt);
    void		tagDataAccessLinkToLocation(const char*,
						    const char*,
						    IlInt);
    // html begin tag
    void		tagBeginCenter();
    void		tagBeginStrong();
    void		tagBeginBold();
    void		tagBeginItalic();
    void		tagBeginUnderline();
    void		tagBeginList();
    void		tagBeginListOrdered();
    void		tagBeginListItem();
    void		tagBeginHtml();
    void		tagBeginHead();
    void		tagBeginCodeListing();
    void		tagBeginTable(const char* opt = 0);
    void		tagBeginFont(const char* opt = 0);
    void		tagBeginTableHeader(const char* opt = 0);
    void		tagBeginTableRow(const char* opt = 0);
    void		tagBeginTableColumn(const char* opt = 0);
    void		tagBeginScript(const char* opt = 0);
    void		tagBeginForm(const char* opt = 0);

    // html end tag
    void		tagEndCenter();
    void		tagEndStrong();
    void		tagEndBold();
    void		tagEndItalic();
    void		tagEndUnderline();
    void		tagEndTable();
    void		tagEndList();
    void		tagEndListOrdered();
    void		tagEndListItem();
    void		tagEndBody();
    void		tagEndHtml();
    void		tagEndHead();
    void		tagEndCodeListing();
    void		tagEndFont();
    void		tagEndTableHeader();
    void		tagEndTableRow();
    void		tagEndTableColumn();
    void		tagEndScript();
    void		tagEndForm();

    // Callbacks
    virtual IlUInt	getCallbackTypes(const char* const **,
					 const IlvSymbol* const**) const;

    // Document symbol
    static IlvSymbol*	ReportBeginDocumentSymbol();
    static IlvSymbol*	ReportEndDocumentSymbol();

    // First page symbol
    static IlvSymbol*	ReportFirstPageHeadingSymbol();
    static IlvSymbol*	ReportFirstPageContentsSymbol();
    static IlvSymbol*	ReportFirstPageFootingSymbol();

    // Table of contents symbol
    static IlvSymbol*	ReportTableHeadingSymbol();
    static IlvSymbol*	ReportTableTitleSymbol();
    static IlvSymbol*	ReportTableBeginEntriesSymbol();
    static IlvSymbol*	ReportTableEntrySymbol();
    static IlvSymbol*	ReportTableEndEntriesSymbol();
    static IlvSymbol*	ReportTableFootingSymbol();

    // Pages symbol
    static IlvSymbol*	ReportPagesSymbol();
    static IlvSymbol*	ReportHeadingSymbol();
    static IlvSymbol*	ReportBeginRowsSymbol();
    static IlvSymbol*	ReportRowContentSymbol();
    static IlvSymbol*	ReportEndRowsSymbol();
    static IlvSymbol*	ReportFootingSymbol();

    // Last page symbol
    static IlvSymbol*	ReportLastPageHeadingSymbol();
    static IlvSymbol*	ReportLastPageContentsSymbol();
    static IlvSymbol*	ReportLastPageFootingSymbol();

    // Accessors
    virtual IlBoolean	getValueDescriptor(IlvValue&) const;
    virtual IlvValue&	queryValue(IlvValue&) const;
    virtual IlBoolean	applyValue(const IlvValue&);
    virtual IlBoolean	applyValueBeginTag(const IlvValue&);
    virtual IlBoolean	applyValueEndTag(const IlvValue&);
    static  void	GetAccessors(const IlvSymbol* const**,
				     const IlvValueTypeClass* const**,
				     IlUInt&);
protected:
    // Reporter
    IliString		_fileName;
    IL_STDPREF ofstream* _file;

    // Data source
    IliString		_dsName;
    IliDataSource*	_ds;
    IliTable*		_table;
    IliTableBuffer*	_buffer;
    IlInt		_rowCount;
    IlBoolean		_comments;

    // Initialize
    void		init();

private:
    void		setTableOfContentsEntry(const char*);
    void		setTableOfContentsLocation(const char*);
    void		setTableOfContentsNumber(IlInt);
};

#define INLINEPROPS1(typ, name, nget, nset)				\
    inline typ IliHTMLReporter::nget##name() const			\
    { return _model->nget##name(); }					\
    inline void IliHTMLReporter::nset##name(typ val)			\
    { _model->nset##name(val); } //

// Document properties
INLINEPROPS1(const char*,	DocumentBackground,		get, set);
INLINEPROPS1(const char*,	DocumentTitle,			get, set);
INLINEPROPS1(const char*,	DocumentCopyright,		get, set);
// Table of contents properties
INLINEPROPS1(IlBoolean,		TableOfContents,		has, set);
INLINEPROPS1(const char*,	TableOfContentsTitle,		get, set);
INLINEPROPS1(IlBoolean,		TableOfContentsAtBeginning,	is,  set);
INLINEPROPS1(const char*,	TableOfContentsColumnName,	get, set);
// First page properties
INLINEPROPS1(const char*,	FirstPageTitle,			get, set);
INLINEPROPS1(const char*,	FirstPagePictureName,		get, set);
// Pages properties
// Last page properties

#undef INLINEPROPS1

class IliXML;

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliXMLModel
    : public IliModel
{
public:
    IliXMLModel();
    virtual ~IliXMLModel();

    // Basic methods
    IliDeclareModel();

    // Xml
    void	  setXMLObject(IliXML*);
    IliXML*	  getXMLObject() const;

protected:
    IliXML*	  _xml;
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliXMLStreamModel
    : public IliXMLModel
{
public:
    IliXMLStreamModel();
    virtual ~IliXMLStreamModel();

    // Basic methods
    IliDeclareModel();

    // In
    virtual
    IL_STDPREF istream*	  openInputStream(IlBoolean notify = IlTrue);
    virtual void	  closeInputStream(IL_STDPREF istream* istr);

    // Out
    IL_STDPREF ostream*	  openOutputStream(IlBoolean notify = IlTrue);
    virtual void	  closeOutputStream(IL_STDPREF ostream* ostr);

    // Model
    IliDeclareDataAccessorForModel(IliXMLStreamModel);
    IliDeclareAccessorForModel(IliXMLStreamModel);
};

// --------------------------------------------------------------------------
// Macro for IliXMLStreamModel
// --------------------------------------------------------------------------
#ifdef DOXYGEN_GENERATION
IliRegisterXMLStreamModel(cl);
#else
#define IliRegisterXMLStreamModel(cl) IliXMLStreamModel::RegisterModel(new cl)
#endif

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliXMLDocumentModel
    : public IliXMLModel
{
public:
    IliXMLDocumentModel();
    virtual ~IliXMLDocumentModel();

    // Basic methods
    IliDeclareModel();

    // Document
    void		  readDocument(IL_STDPREF istream& from);
    IlXmlDocument*	  getDocument() const;

    virtual
    IlBoolean		  isGoodRoot(const char*) const;
    virtual IlXmlElement* isGoodNode(const char*, IlXmlNodeI*) const;
    virtual IlXmlTextI*	  getTextNode(IlXmlElement*) const;

    virtual IlBoolean	  getAttributeValue(const char*,
					    IlXmlElementI*,
					    IliString&) const;
    virtual IlBoolean	  getAttributeValue(const char*,
					    IlXmlElementI*,
					    IlBoolean&) const;
    virtual IlBoolean	  getAttributeValue(const char*,
					    IlXmlElementI*,
					    IlInt&) const;
    virtual IlBoolean	  getAttributeValue(const char*,
					    IlXmlElementI*,
					    IlvAlignment&) const;
    void		  closeDocument();

protected:
    IlXmlDocument*	  _document;
};

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliXMLImportModel
    : public IliXMLDocumentModel
{
public:
    IliXMLImportModel();
    virtual ~IliXMLImportModel();

    // Basic methods
    IliDeclareModel();

    // Event
    virtual void	  importNotification(IL_STDPREF istream& from);

    virtual void	  importDefinition(IL_STDPREF istream& from);

    // Model
    IliDeclareDataAccessorForModel(IliXMLImportModel);
    IliDeclareAccessorForModel(IliXMLImportModel);
};

// --------------------------------------------------------------------------
// Macro for IliXMLImportModel
// --------------------------------------------------------------------------
#ifdef DOXYGEN_GENERATION
IliRegisterXMLImportModel(cl);
#else
#define IliRegisterXMLImportModel(cl) IliXMLImportModel::RegisterModel(new cl)
#endif

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliXMLExportModel
    : public IliXMLDocumentModel
{
public:
    IliXMLExportModel();
    virtual ~IliXMLExportModel();

    // Basic methods
    IliDeclareModel();

    // Events to export
    virtual void	  exportNotification(IL_STDPREF ostream&	to,
					     IliXMLNotification		no,
					     const IliModelHookInfo&	info);

    virtual void	  exportDefinition(IL_STDPREF ostream& to);

    // Model
    IliDeclareDataAccessorForModel(IliXMLExportModel);
    IliDeclareAccessorForModel(IliXMLExportModel);
};

// --------------------------------------------------------------------------
// Macro for IliXMLExportModel
// --------------------------------------------------------------------------
#ifdef DOXYGEN_GENERATION
IliRegisterXMLExportModel(cl);
#else
#define IliRegisterXMLExportModel(cl) IliXMLExportModel::RegisterModel(new cl)
#endif

// --------------------------------------------------------------------------
class ILV_DBG_EXPORTED IliXML
    : public IliDataGem
{
public:
    IliXML(IlvDisplay*		display,
	   const IlvPoint&	at,
	   IlUShort		thickness = IlvDefaultGadgetThickness,
	   IlvPalette*		palette = 0);
    virtual ~IliXML();

    DeclareTypeInfo();
    DeclareIOConstructors(IliXML);

    // Look
    virtual IlvBitmap*	  getBitmap() const;

    // Import
    void		  setImportModelName(const char* name);

    const char*		  getImportModelName() const;
    IliXMLImportModel*	  getImportModel() const;

    void		  importNotification();

    void		  importDefinition();

    // Export
    void		  setExportModelName(const char* name);
    const char*		  getExportModelName() const;
    IliXMLExportModel*	  getExportModel() const;

    void		  exportDefinition();

    void		  setAutomaticExport(IlBoolean flag);

    IlBoolean		  isAutomaticExport() const;

    // Stream
    void		  setStreamModelName(const char* name);
    const char*		  getStreamModelName() const;
    IliXMLStreamModel*	  getStreamModel() const;

    // Properties

    IlInt		  getModelPropertyCount(IliXMLModelType type) const;
    IlInt		  getModelPropertyIndex(IliXMLModelType	type,
						const char*	name) const;
    const char*		  getModelPropertyName(IliXMLModelType	type,
					       IlInt		index) const;
    const IliValue&	  getModelPropertyValue(IliXMLModelType	type,
						const char*	name) const;
    const IliValue&	  getModelPropertyValue(IliXMLModelType	type,
						IlInt		index) const;
    void		  setModelPropertyValue(IliXMLModelType	type,
						const char*	name,
						const IliValue&	val);
    void		  setModelPropertyValue(IliXMLModelType	type,
						IlInt		index,
						const IliValue&	val);
    void		  copyModelProperties(IliXMLModelType	type,
					      IliPropertiesManager&) const;

    // Data source
#ifdef DOXYGEN_GENERATION
    void		  setDataSourceName(const char* name);
    const char*		  getDataSourceName() const;
#else
    IliSingleDsUsageDeclareDSAccessDirect();
    IliDsUsageDeclareFctConnectDirect();
    IliDsUsageDeclareBatchDirect();
#endif
    IlInt		  getBatchCount() const;
    IlBoolean		  isBatchMode() const;

    // Overloads IlvGraphic
    virtual void	  setHolder(IlvGraphicHolder*);

    // Error reporting
    void		  addErrorSink(IliErrorSink* sink);
    void		  removeErrorSink(IliErrorSink* sink);
    void		  setErrorReporter(IliErrorReporter* reporter);
    IliErrorReporter*	  getErrorReporter() const;
    void		  reportErrors(const IliErrorList& errorList) const;

    // Accessors
    virtual IlvValue&	  queryValue(IlvValue&) const;
    virtual IlBoolean	  applyValue(const IlvValue&);
    virtual IlBoolean	  getValueDescriptor(IlvValue&) const;
    static void		  GetAccessors(const IlvSymbol* const**,
				       const IlvValueTypeClass* const**,
				       IlUInt&);
    // Callbacks
    static IlvSymbol*	  NotificationExportedSymbol();
    virtual IlUInt	  getCallbackTypes(const char* const **,
					   const IlvSymbol* const**) const;
protected:
    void		  init();

    // Properties
    IliPropertiesManager  _props[IliXMLModelTypeCount];

    // Import
    IliXMLStreamModel*	  _streamModel;

    // Import
    IliXMLImportModel*	  _importModel;

    // Export
    IliXMLExportModel*	  _exportModel;
    IlBoolean		  _autoExport;

    // DataSource
    IliSingleDataSourceUsage* _ds;

    // Refresh
    IlBoolean		  _ignoreEvent;
    IlBoolean		  _inEndOfBatch;
    IlBoolean		  _needRefresh;
    IlInt		  _batchCount;
};

IliSingleDsUsageCodeDSAccessDirect(IliXML, _ds);

IlvDeclareEnumTypeClass(ILV_DBG_EXPORTED, ModelName);

IliModuleDECL_exp(ILV_DBG_EXPORTED, ModelName);
IliModuleDECL_exp(ILV_DBG_EXPORTED, IliHTMLReporter);

#endif /* !__Ili_Htmlrep_H */
