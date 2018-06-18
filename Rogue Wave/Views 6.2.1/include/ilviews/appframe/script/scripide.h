// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/appframe/script/scripide.h
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
// Declaration of the script IDE classes
// --------------------------------------------------------------------------
#if !defined(__Ilv_Appframe_Scripide_H)
#define __Ilv_Appframe_Scripide_H

#if !defined(__Ilv_Appframe_Interf_H)
#include <ilviews/appframe/interf.h>
#endif
#if !defined(__Ilv_Appframe_Project_Prjdoc_H)
#include <ilviews/appframe/project/prjdoc.h>
#endif
#if !defined(__Ilv_Appframe_Doctext_H)
#include <ilviews/appframe/doctext.h>
#endif
#if !defined(__Ilv_Appframe_Viewgadg_H)
#include <ilviews/appframe/viewgadg.h>
#endif
#if !defined(__Ilv_Appframe_Viewgadg_H)
#include <ilviews/appframe/viewgadg.h>
#endif
#if !defined(__Ilv_Appframe_Project_Prjview_H)
#include <ilviews/appframe/project/prjview.h>
#endif
#if !defined(__Ilv_Base_Link_H)
#include <ilviews/base/link.h>
#endif

#if !defined(ILVNOSCRIPT)
class IlvDvAppScript;
class IlvDvDocTemplate;
class IlvDvTextScriptDocument;
class IlvDvRunningContext;

// --------------------------------------------------------------------------
// IlvDvScriptProjectDocument class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvScriptProjectDocument : public IlvDvProjectDocument
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvScriptProjectDocument();
    virtual ~IlvDvScriptProjectDocument();

    // ----------------------------------------------------------------------
    // Main operations
    IlBoolean		execute();
    IlBoolean		stepInto();
    IlBoolean		stepOver();
    IlBoolean		stepOut();

    // ----------------------------------------------------------------------
    // Basic attributes
    inline IlvDvAppScript*	getAppScript() const { return _appScript; }
    inline void			setAppScript(IlvDvAppScript* script)
				{
				    _appScript = script;
				}

    // ----------------------------------------------------------------------
    IlvDvDeclareInterface();

protected:
    IlvDvAppScript*	_appScript;

    IlBoolean		executeStepByStep();
    void		compileUI(IlvDvActionDescriptor*);
    void		executeUI(IlvDvActionDescriptor*);
    void		stepUI(IlvDvActionDescriptor*);

    IlBoolean		needToCompile() const;
    virtual IlUInt	getChildInterfacesCount() const;
    virtual IlvDvInterface*	getChildInterface(IlUInt nInterface) const;

public:
    static IlvDvDocument*	CreateProjectScriptDocument(IlvDvDocTemplate*,
							    IlAny param);
};

// --------------------------------------------------------------------------
// IlvDvScriptProjectView class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvScriptProjectView : public IlvDvProjectView
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvScriptProjectView(IlvDisplay*);
    virtual ~IlvDvScriptProjectView();

    // ----------------------------------------------------------------------
    IlvDvDeclareInterface();

protected:
    void		insertFile();
};

// --------------------------------------------------------------------------
// IlvDvTextMark class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvTextMark
{
public:

    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvTextMark(IlUInt line, const IlSymbol* markType = 0);
    ~IlvDvTextMark();

    // ----------------------------------------------------------------------
    inline int			getLine() const { return _line; }
    inline const IlSymbol*	getType() const { return _type; }

protected:
    IlUInt			_line;
    const IlSymbol*		_type;
};

// --------------------------------------------------------------------------
// IlvDvTextScriptDocument class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvTextScriptDocument : public IlvDvTextDocument
{
    IlvDvDeclareDynCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvTextScriptDocument();
    virtual ~IlvDvTextScriptDocument();

    // ----------------------------------------------------------------------
    // Main methods
    IlBoolean		execute();
    IlBoolean		stepInto();
    IlBoolean		stepOver();
    IlBoolean		stepOut();

    // ----------------------------------------------------------------------
    // Basic attributes
    inline IlvDvAppScript*	getAppScript() const { return _appScript; }
    inline void			setAppScript(IlvDvAppScript* script)
				{
				    _appScript = script;
				}

    inline IlvDvScriptProjectDocument*	getProject() const { return _project; }
    void		setProject(IlvDvScriptProjectDocument*);

    // ----------------------------------------------------------------------
    // Marks
    void		addMark(IlvDvTextMark*, IlBoolean update = IlTrue);
    void		removeMark(IlvDvTextMark*, IlBoolean update = IlTrue);
    void		removeMarks(IlBoolean update = IlTrue);

    IlvDvTextMark*	getMark(IlUInt nMark) const;
    inline IlUInt	getMarksCount() const { return _marks.getLength(); }
    // ----------------------------------------------------------------------
    IlvDvDeclareInterface();

    static IlSymbol*		_SetMark;
    static IlSymbol*		_RemoveMark;

protected:
    IlvDvAppScript*		_appScript;
    IlvDvScriptProjectDocument*	_project;
    IlArray			_marks;

    IlBoolean			executeStepByStep();
    void			executeUI(IlvDvActionDescriptor*);
    void			stepUI(IlvDvActionDescriptor*);

    virtual IlUInt		getChildInterfacesCount() const;
    virtual IlvDvInterface*	getChildInterface(IlUInt nInterface) const;

public:
    static IlvDvDocument*	CreateTextScriptDocument(IlvDvDocTemplate*,
							 IlAny);
};

// --------------------------------------------------------------------------
// IlvDvTextScriptView class
// --------------------------------------------------------------------------
class ILVDVCLASS IlvDvTextScriptView : public IlvDvTextView
{
    IlvDvDeclareGadgetViewCreate();
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvDvTextScriptView(IlvDisplay*);
    virtual ~IlvDvTextScriptView();

    // ----------------------------------------------------------------------
    // Basic properties

    IlvDvTextScriptDocument* getTextScript() const;
    // ----------------------------------------------------------------------
    IlvDvDeclareInterface();

    // ----------------------------------------------------------------------
    // Specific callbacks

    static IlSymbol*	_DefaultMarkSymbol;

protected:
    IlAList		_graphics;
    IlUInt		getMarksCount() const;
    IlvDvTextMark*	getMark(IlUInt iMark) const;
    void		setDocMark(IlAny);
    void		removeDocMark(IlAny);

    virtual IlvGraphic*	getMarkGraphic(const IlSymbol* markType) const;

    int			_logicalStartLine;

    inline void		setLogicalStartLine(int logicalStartLine)
			{
			    _logicalStartLine = logicalStartLine;
			}

    IlvRect		getMarginBox() const;
    void		reDrawMargin();

protected:
    void		removeHeadLines(int nlines);
    inline int		getLogicalStartLine() const
			{
			    return _logicalStartLine;
			}

    void		clearText();

public:

    virtual void	draw(IlvPort* dst,
			     const IlvTransformer* t = 0,
			     const IlvRegion* clip = 0) const;

    void		scrollBarMoved();
    void		attachMark(IlvDvTextMark* mark);
};

// --------------------------------------------------------------------------
IlvDECLAREINITDVCLASS(scripide)
// --------------------------------------------------------------------------
#endif /* !ILVNOSCRIPT */
#endif /* !__Ilv_Appframe_Script_Scripide_H */
