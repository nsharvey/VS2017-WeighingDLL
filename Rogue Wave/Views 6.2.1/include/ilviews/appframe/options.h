// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/options.h
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
// Declaration of the IlvDvOptions class
// --------------------------------------------------------------------------
#if !defined(__IlvDv_Options_H)
#define __IlvDv_Options_H

#if !defined(__Ilv_Appframe_Serializ_H)
#include <ilviews/appframe/serializ.h>
#endif
#if !defined(__Ilv_Base_Hash_H)
#include <ilviews/base/hash.h>
#endif
#if !defined(__Ilv_Appframe_Nodeval_H)
#include <ilviews/appframe/nodeval.h>
#endif
#if !defined(__Ilv_Base_Pathname_H)
#include <ilviews/base/pathname.h>
#endif
#if !defined(__Ilv_Appframe_Utils_H)
#include <ilviews/appframe/utils.h>
#endif
#if !defined(__Il_Xml_H)
#include <ilog/xml.h>
#endif

class IlvDvClass;
class IlvDvTextStream;
class IlvDvOptions;
class IlvDvCommand;
class IlvDvApplication;
class IlvDvValue;
class IlvDvStringArray;
class IlvValueTypeClass;
class IlvAbstractMenu;
class IlvMenuItem;
class IlvGadgetItem;
class IlvPopupMenu;
extern ILVDVEXPORTEDVAR(IlvValueTypeClass*) IlvValueClassInstanceType;
extern ILVDVEXPORTEDVAR(IlvValueTypeClass*) IlvValueClassInstanceArrayType;

// --------------------------------------------------------------------------
// IlvDvXmlOptionsRootNode class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvOptions;

class ILVDVCLASS IlvDvXmlOptionsRootNode : public IlXmlElementI
{
public:
    IlvDvXmlOptionsRootNode(IlvDvOptions*);
    virtual const char*	getTag() const;
    virtual void	addChild(IlXmlNodeI*);
    virtual void	addAttribute(IlXmlAttributeI*);
    virtual
    IlXmlElementI*	createChildElement(char* tag) const;

protected:
    IlvDvOptions*	_options;
    IlXmlElement	_inclusionNode;
    IlXmlText*		_textElmt;

    virtual
    IlXmlNodeIteratorI*	createChildrenIterator() const;
    virtual void	storeTag(char* tag);
};

// --------------------------------------------------------------------------
// IlvDvXmlOptionsRootIterator class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvXmlOptionsRootIterator
    : public IlXmlNodeArrayIterator
{
public:
    IlvDvXmlOptionsRootIterator(const IlvDvOptions* options);

    virtual IlXmlNodeI*	getNextNode();

protected:
    const IlvDvOptions*	_options;
    IlXmlElement	_inclusionNode;
    IlXmlText*		_textElmt;
};

// --------------------------------------------------------------------------
// IlvDvOptions class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvOptions : public IlvDvSerializable, public IlXmlDocumentI
{
    IlvDvDeclareClassInfo();

public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvOptions(IlvDisplay* display = 0, IlvDvOptions* parent = 0);
    virtual ~IlvDvOptions();

    // ----------------------------------------------------------------------
    // Main operations
    IlvDvNodeValue*	getNodeValue(const char* type, const char* name) const;
    IlvDvNodeValue*	getNodeValue(const IlSymbol* type,
				     const IlSymbol* name) const;
    IlvDvNodeValue*	findVariable(const IlSymbol* type,
				     const IlSymbol* name,
				     IlvDvOptions** options = 0) const;
    IlvDvNodeValueArray* getValues(const IlSymbol* type,
				   IlBoolean bAllTree = IlFalse) const;
    const IlvValue&	getValue(const char* type, const char* name) const;
    const IlvValue&	getValue(const IlSymbol* type,
				 const IlSymbol* name) const;
    const IlvValue&	getFieldValue(const char* type,
				      const char* name,
				      const char* fieldName) const;
    const IlvValue&	getFieldValue(const IlSymbol* type,
				      const IlSymbol* name,
				      const IlSymbol* fieldName) const;
    IlBoolean		setValue(const char* type,
				 const char* name,
				 const IlvDvValue&);
    IlBoolean		setValue(const IlSymbol* type,
				 const IlSymbol* name,
				 const IlvDvValue&);
    IlvDvNodeValue*	createNodeValue(const char* name,
					const IlvDvClass*,
					IlBoolean isArray = IlFalse,
					IlvDvNodeValue::NodeValueType =
					IlvDvNodeValue::Value) const;
    IlvDvNodeValue*	createNodeValue(const char* name,
					const char* classname,
					IlBoolean isArray = IlFalse,
					IlvDvNodeValue::NodeValueType =
					IlvDvNodeValue::Value) const;
    IlvDvNodeValue*	createNodeValue(const IlSymbol* name,
					const IlSymbol* classname,
					IlBoolean isArray = IlFalse,
					IlvDvNodeValue::NodeValueType =
					IlvDvNodeValue::Value) const;
    void		optimizeNodeValues();

    // ----------------------------------------------------------------------
    // Action management
    IlvDvNodeValue*	getCommandVariable(const IlSymbol* actionName) const;
    const char*		getActionDescription(const IlSymbol* actionName) const;
    void		getActionCategories(const IlSymbol* actionName,
					    IlvDvStringArray&) const;
    static void		GetCommandCategories(const IlvDvNodeValue* cmdVar,
					     IlvDvStringArray&);

    // ----------------------------------------------------------------------
    // Adding options
    void		addOptions(IlvDvOptions* options);
    void		mergeOptions(IlvDvOptions* options);
    IlBoolean		containsOptions(const IlvDvOptions* options) const;
    void		getIncludedOptions(IlvArray& options) const;
    void		removeOptions(IlvDvOptions* options,
				      IlBoolean deleteIt = IlTrue);
    IlBoolean		addOptionsPath(const char* optionsPath,
				       IlBoolean inFile = IlFalse);

    // ----------------------------------------------------------------------
    // Basic properties
    const IlvDvClass*	getClass(const IlSymbol* classname,
				 IlBoolean allowPrimaryClasses = IlTrue) const;
    const IlvDvClass*	getClass(const IlvDvNodeValue*) const;
    static const char*	GetOptionsClassName(const IlvDvNodeValue*);
    IlvValueTypeClass*	getValueType(const IlvString& typeName,
				     const IlvDvClass** = 0) const;
    const IlvDvClass*	getPrimaryClass(const IlvValueTypeClass*) const;
    IlBoolean		isPrimaryClass(const IlvDvClass*) const;
    IlvDisplay*		getDisplay() const;
    IlBoolean		isWritable() const;
    void		setWritable(IlBoolean writable,
				    IlBoolean subOptions = IlFalse);
    IlBoolean		isModified(IlBoolean recursive = IlTrue) const;
    void		addClass(IlvDvClass*, IlBoolean inFile = IlFalse);
    void		addNodeValue(IlvDvNodeValue* var,
				     IlBoolean inFile = IlFalse,
				     IlBoolean merge = IlFalse);
    void		removeNodeValue(IlvDvNodeValue* var,
					IlBoolean deleteIt = IlTrue);
    void		renameVariable(IlvDvNodeValue*, const IlSymbol*);

    void		addComment(const char* comment);

    static IlSymbol*	_IntClassSymbol;
    static IlSymbol*	_BooleanClassSymbol;
    static IlSymbol*	_StringClassSymbol;
    static IlSymbol*	_FloatClassSymbol;
    static IlSymbol*	_DoubleClassSymbol;
    static IlSymbol*	_ClassSymbol;
    static IlSymbol*	_IncludeSymbol;
    static IlSymbol*	_CommentSymbol;

    // ----------------------------------------------------------------------
    // Serialization
    IlBoolean		readFile(const char* filename = 0);
    IlBoolean		writeFile(const char* filename = 0,
				  IlvDvOptions* writableOptions = 0,
				  IlBoolean onlyModifs = IlTrue);
    void		setPathName(const IlvPathName&);
    const IlvString&	getPathName() const;

    // ----------------------------------------------------------------------
    // Serialization
    IlBoolean		readXML(ILVSTDPREF istream& is);
    IlBoolean		writeXML(IL_STDPREF ostream& stream);

    // Implementation of the IlXmlDocumentI interface
    IlListOf(IlXmlNodeI)&	getNodes() const;
    virtual
    IlXmlElementI*	createElement(char* tag) const;
    virtual void	addNode(IlXmlNodeI* node);
    virtual void	endElement(IlXmlElementI* element);

    static IlSymbol*	_OptionMenuSymbol;
    static IlSymbol*	_OptionCommandSymbol;
    static IlSymbol*	_OptionCommandCategoriesSymbol;
    static IlSymbol*	_OptionCommandAcceleratorsSymbol;
    static IlSymbol*	_OptionCommandMenuDescSymbol;
    static IlSymbol*	_OptionCommandTooltipSymbol;
    static IlSymbol*	_OptionCommandDescSymbol;
    static IlSymbol*	_OptionIsCustomCommandSymbol;
    static IlSymbol*	_OptionShowTooltipSymbol;
    static IlSymbol*	_OptionWithShortcutsSymbol;
    static IlSymbol*	_OptionBigIconsSymbol;

    static IlSymbol*	_OptionDocTemplSymbol;
    static IlSymbol*	_OptionDocClassSymbol;
    static IlSymbol*	_OptionDocTemplDynMenuSymbol;
    static IlSymbol*	_OptionDocTemplToolBarSymbol;
    static IlSymbol*	_OptionDocTemplDescSymbol;
    static IlSymbol*	_OptionTplDocIsMDISymbol;
    static IlSymbol*	_OptionTplViewClassesSymbol;
    static IlSymbol*	_OptionTplBitmapSymbol;
    static IlSymbol*	_OptionTplDefaultDocNameSymbol;
    static IlSymbol*	_OptionTplFiltersSymbol;
    static IlSymbol*	_OptionTplFiltersOnOpenSymbol;
    static IlSymbol*	_OptionTplILVSymbol;
    static IlSymbol*	_OptionTplInMDIChildSymbol;
    static IlSymbol*	_OptionTplFrameMaximizedSymbol;
    static IlSymbol*	_OptionTplMultiWindowSymbol;
    static IlSymbol*	_OptionTplCloseDocumentWhenClosedSymbol;
    static IlSymbol*	_OptionTplAlwaysShowMenuSymbol;
    static IlSymbol*	_OptionTplNewCommandSymbol;
    static IlSymbol*	_OptionTplOpenCommandSymbol;
    static IlSymbol*	_OptionTplRecentFileCommandSymbol;
    static IlSymbol*	_OptionTplShowHidePaneActionSymbol;
    static IlSymbol*	_OptionTplMaxFilesSymbol;
    static IlSymbol*	_PopupSymbol;
    static const char*	_OptionMenuSeparatorName;
    static const char*	_OptionMenuIsPopupField;
    static IlSymbol*	_OptionBarSymbol;
    static IlSymbol*	_OptionIsUserBarSymbol;

    static const char*	_XmlClassTag;
    static const char*	_XmlNameAttribute;
    static const char*	_XmlIsArrayTag;
    static const char*	_XmlInclusioTag;
    static const char*	_XmlMainNodeTag;

protected:
    IlvDisplay*		_display;
    IlvDvOptions*	_parent;
    IlvString		_pathName;
    IlvString		_shortPathName;
    IlvString		_version;
    IlvHashTable	_primaryClasses; // Array of IlvDvClass
    IlvHashTable	_classes; // Array of IlvDvClass
    IlvArray		_options;
    IlvHashTable	_variables; // Array of IlvDvNodeValue
    IlUInt		_flags; // Modification, is writable, is merged

    // XML data
    IlListOf(IlXmlNodeI)	_nodes;
    IlvDvXmlOptionsRootNode*	_rootNode;
    void		emptyXmlNodes();

    const IlvDvClass*	findPrimaryClass(const IlSymbol* classname) const;
    void		_getVariables(const IlvDvClass*,
				      IlvDvNodeValueArray*) const;
    IlvDvNodeValue*	getNodeValue(const IlSymbol* type,
				     const IlSymbol* name,
				     IlvDvOptions** options,
				     const IlvDvOptions* except = 0) const;
    const IlvDvClass*	_getClass(const IlSymbol* classname,
				  const IlvDvOptions* except) const;
    const IlvDvOptions*	getTopOptions() const;

    friend class ILVDVCLASS IlvDvClass;

    // ----------------------------------------------------------------------
    // Option file components
    class OptionFileComponent
    {
    public:
	union {
	    IlXmlComment*    _comment;
	    IlvDvOptions*    _options;
	    const IlSymbol* _className;
	    struct {
		const IlSymbol* _className;
		const IlSymbol* _name;
	    } _variable;
	} _data;
	enum { COMMENT, CLASS, VARIABLE, INCLUSION } _type;
	OptionFileComponent(IlvDvClass* pClass);
	OptionFileComponent(const IlSymbol* className,
			    const IlSymbol* name);
	OptionFileComponent(IlvDvOptions* options);
	OptionFileComponent(IlXmlComment* comment);
	~OptionFileComponent();
	IlBoolean	equals(const OptionFileComponent& src) const;
    };

    IlvArray		_optionFileComponents; // Array of OptionFileComponent

    void		clean();
    void		cleanFileComponents();
    IlBoolean		writeInOptions(IlvDvOptions*,
				       IlBoolean onlyModifs = IlTrue);
    IlUInt		findComponent(const OptionFileComponent&,
				      IlvDvOptions** options = 0) const;

    void		initializePrimaryClasses();

    // Implementation of the IlXmlDocumentI interface
    virtual void	storeVersion(char* version);
    virtual void	storeDoctype(char* name, char* rest);
    virtual
    IlXmlNodeIteratorI*	createNodesIterator() const;

    friend class IlvDvXmlOptionsRootIterator;
    friend class IlvDvXmlOptionsRootNode;
};

// --------------------------------------------------------------------------
// IlvDvNodeValuesIterator class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvNodeValuesIterator
{
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvNodeValuesIterator(IlvDvOptions* options,
			    const IlSymbol* classname);
    virtual ~IlvDvNodeValuesIterator();

    // ----------------------------------------------------------------------
    IlvDvNodeValue*	getNodeValue() const;
    void		goNextNodeValue();

protected:
    IlvDvNodeValueArray* _values;
    IlBoolean		_deleteValues;
    IlUInt		_index;
};

// --------------------------------------------------------------------------
ILVDVEXPORTEDFUNCTION(IlvMenuItem*)
IlvDvCopyMenuItem(IlvMenuItem*); // copy the item and its properties

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(options);
// --------------------------------------------------------------------------
#endif /* !__IlvDv_Options_H */
