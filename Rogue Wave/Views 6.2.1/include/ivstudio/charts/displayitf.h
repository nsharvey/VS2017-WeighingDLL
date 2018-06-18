// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/charts/displayitf.h
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
// Declaration of the IlvStIDisplayerInterface class
// Defined in studio charts library
// --------------------------------------------------------------------------
#if !defined(__IlvSt_Charts_Displayitf_H)
#define __IlvSt_Charts_Displayitf_H

#if !defined(__IlvSt_Genselpg_H)
#include <ivstudio/inspectors/genselpg.h>
#endif

#if !defined(__IlvSt_Charts_Stchart_H)
#include <ivstudio/charts/stchart.h>
#endif

#if !defined(__Ilv_Charts_Display_H)
#include <ilviews/charts/display.h>
#endif

class ILVSTCHARTCLASS IlvStIChartPanel;
class ILVSTCHARTCLASS IlvStIDisplayerAccessor;
class ILVSTCHARTCLASS IlvStIDisplayerEditor;

// --------------------------------------------------------------------------
// Class IlvStIDisplayerInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIDisplayerInterface(IlvDisplay* display,
			     const char* name,
			     const char* label,
			     const char* fileName,
			     const char* panelName);
    virtual ~IlvStIDisplayerInterface();

    // ----------------------------------------------------------------------
    // Set / get
    const char* getFileName() const { return _fileName; }
    IlSymbol* getSymbol() const { return _symbol; }
    const char* getLabel() const { return _label; }
    const char* getPanelName() const { return _panelName; }

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer() = 0;
    virtual const IlvClassInfo* getDisplayerClassInfo() = 0;
    virtual IlBoolean isMulti() const;
    virtual IlUInt getMaxDataSetsCount() const;
    virtual IlUInt getChildDisplayersCount(IlUInt selectedDataSetsCount) const;
    virtual IlvAbstractChartDisplayer* createChildDisplayer(IlUInt selectedDataSetsCount);

    virtual void createPanel(IlvStIChartPanel* panel,
			     IlvStIListPageSelector* selector,
			     const char* displayerRectangleName,
			     IlUShort itemIndex);
    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDisplayerAccessor* displayerAcc,
			       IlvStIDisplayerEditor* displayerEditor);

protected:
    IlvDisplay* _display;
    IlSymbol*  _symbol;
    const char* _label;
    const char* _fileName;
    const char* _panelName;
};

// --------------------------------------------------------------------------
// Class IlvStIPolylineInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIPolylineInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIPolylineInterface(IlvDisplay* display,
			    const char* name,
			    const char* label,
			    const char* fileName,
			    const char* panelName);
    virtual ~IlvStIPolylineInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();

};

// --------------------------------------------------------------------------
// Class IlvStIPolygonInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIPolygonInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIPolygonInterface(IlvDisplay* display,
			   const char* name,
			   const char* label,
			   const char* fileName,
			   const char* panelName);
    virtual ~IlvStIPolygonInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();
};

// --------------------------------------------------------------------------
// Class IlvStIStairInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIStairInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIStairInterface(IlvDisplay* display,
			 const char* name,
			 const char* label,
			 const char* fileName,
			 const char* panelName);
    virtual ~IlvStIStairInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();
};

// --------------------------------------------------------------------------
// Class IlvStIStepInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIStepInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIStepInterface(IlvDisplay* display,
			const char* name,
			const char* label,
			const char* fileName,
			const char* panelName);
    virtual ~IlvStIStepInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();
};

// --------------------------------------------------------------------------
// Class IlvStIScatterInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIScatterInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIScatterInterface(IlvDisplay* display,
			   const char* name,
			   const char* label,
			   const char* fileName,
			   const char* panelName);
    virtual ~IlvStIScatterInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();

    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDisplayerAccessor* displayerAcc,
			       IlvStIDisplayerEditor* displayerEditor);
};

// --------------------------------------------------------------------------
// Class IlvStIMarkedPolylineInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIMarkedPolylineInterface
: public IlvStIScatterInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIMarkedPolylineInterface(IlvDisplay* display,
				  const char* name,
				  const char* label,
				  const char* fileName,
				  const char* panelName);
    virtual ~IlvStIMarkedPolylineInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();

    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDisplayerAccessor* displayerAcc,
			       IlvStIDisplayerEditor* displayerEditor);
};

// --------------------------------------------------------------------------
// Class IlvStIFixedStepInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIFixedStepInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIFixedStepInterface(IlvDisplay* display,
			     const char* name,
			     const char* label,
			     const char* fileName,
			     const char* panelName);
    virtual ~IlvStIFixedStepInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();

    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDisplayerAccessor* displayerAcc,
			       IlvStIDisplayerEditor* displayerEditor);
};

// --------------------------------------------------------------------------
// Class IlvStIBarInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIBarInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIBarInterface(IlvDisplay* display,
		       const char* name,
		       const char* label,
		       const char* fileName,
		       const char* panelName);
    virtual ~IlvStIBarInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();

    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDisplayerAccessor* displayerAcc,
			       IlvStIDisplayerEditor* displayerEditor);
};

// --------------------------------------------------------------------------
// Class IlvStI3dBarInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStI3dBarInterface
: public IlvStIBarInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStI3dBarInterface(IlvDisplay* display,
			 const char* name,
			 const char* label,
			 const char* fileName,
			 const char* panelName);
    virtual ~IlvStI3dBarInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();

    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDisplayerAccessor* displayerAcc,
			       IlvStIDisplayerEditor* displayerEditor);
};

// --------------------------------------------------------------------------
// Class IlvStIHiLoInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIHiLoInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIHiLoInterface(IlvDisplay* display,
			const char* name,
			const char* label,
			const char* fileName,
			const char* panelName);
    virtual ~IlvStIHiLoInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();
    virtual IlUInt getMaxDataSetsCount() const;

    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDisplayerAccessor* displayerAcc,
			       IlvStIDisplayerEditor* displayerEditor);
};

// --------------------------------------------------------------------------
// Class IlvStIHiLoBarInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIHiLoBarInterface
: public IlvStIHiLoInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIHiLoBarInterface(IlvDisplay* display,
			   const char* name,
			   const char* label,
			   const char* fileName,
			   const char* panelName);
    virtual ~IlvStIHiLoBarInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();
    virtual IlUInt getMaxDataSetsCount() const;
};

// --------------------------------------------------------------------------
// Class IlvStIHiLoOpenCloseInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIHiLoOpenCloseInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIHiLoOpenCloseInterface(IlvDisplay* display,
				 const char* name,
				 const char* label,
				 const char* fileName,
				 const char* panelName);
    virtual ~IlvStIHiLoOpenCloseInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();
    virtual IlBoolean isMulti() const;
    virtual IlUInt getMaxDataSetsCount() const;
    virtual IlUInt getChildDisplayersCount(IlUInt selectedDataSetsCount) const;
    virtual IlvAbstractChartDisplayer* createChildDisplayer(IlUInt selectedDataSetsCount);

};

// --------------------------------------------------------------------------
// Class IlvStIBubbleInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIBubbleInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIBubbleInterface(IlvDisplay* display,
			  const char* name,
			  const char* label,
			  const char* fileName,
			  const char* panelName);
    virtual ~IlvStIBubbleInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();
    virtual IlUInt getMaxDataSetsCount() const;

    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDisplayerAccessor* displayerAcc,
			       IlvStIDisplayerEditor* displayerEditor);
};

// --------------------------------------------------------------------------
// Class IlvStIPieInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIPieInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIPieInterface(IlvDisplay* display,
		       const char* name,
		       const char* label,
		       const char* fileName,
		       const char* panelName);
    virtual ~IlvStIPieInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();

    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDisplayerAccessor* displayerAcc,
			       IlvStIDisplayerEditor* displayerEditor);
};

// --------------------------------------------------------------------------
// Class IlvStISideBySideBarInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStISideBySideBarInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStISideBySideBarInterface(IlvDisplay* display,
				 const char* name,
				 const char* label,
				 const char* fileName,
				 const char* panelName);
    virtual ~IlvStISideBySideBarInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();
    virtual IlBoolean isMulti() const;
    virtual IlUInt getMaxDataSetsCount() const;
    virtual IlUInt getChildDisplayersCount(IlUInt selectedDataSetsCount) const;
    virtual IlvAbstractChartDisplayer* createChildDisplayer(IlUInt selectedDataSetsCount);
};

// --------------------------------------------------------------------------
// Class IlvStIStackedBarInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIStackedBarInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIStackedBarInterface(IlvDisplay* display,
			      const char* name,
			      const char* label,
			      const char* fileName,
			      const char* panelName);
    virtual ~IlvStIStackedBarInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();
    virtual IlBoolean isMulti() const;
    virtual IlUInt getMaxDataSetsCount() const;
    virtual IlUInt getChildDisplayersCount(IlUInt selectedDataSetsCount) const;
    virtual IlvAbstractChartDisplayer* createChildDisplayer(IlUInt selectedDataSetsCount);

    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDisplayerAccessor* displayerAcc,
			       IlvStIDisplayerEditor* displayerEditor);
};

// --------------------------------------------------------------------------
// Class IlvStIStacked3dBarInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIStacked3dBarInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIStacked3dBarInterface(IlvDisplay* display,
				const char* name,
				const char* label,
				const char* fileName,
				const char* panelName);
    virtual ~IlvStIStacked3dBarInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();
    virtual IlBoolean isMulti() const;
    virtual IlUInt getMaxDataSetsCount() const;
    virtual IlUInt getChildDisplayersCount(IlUInt selectedDataSetsCount) const;
    virtual IlvAbstractChartDisplayer* createChildDisplayer(IlUInt selectedDataSetsCount);

    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDisplayerAccessor* displayerAcc,
			       IlvStIDisplayerEditor* displayerEditor);
};

// --------------------------------------------------------------------------
// Class IlvStIStackedPolygonInterface
// --------------------------------------------------------------------------
class ILVSTCHARTCLASS IlvStIStackedPolygonInterface
: public IlvStIDisplayerInterface {
public:
    // ----------------------------------------------------------------------
    // Constructor / destructor
    IlvStIStackedPolygonInterface(IlvDisplay* display,
				  const char* name,
				  const char* label,
				  const char* fileName,
				  const char* panelName);
    virtual ~IlvStIStackedPolygonInterface();

    // ----------------------------------------------------------------------
    // Overridables
    virtual IlvAbstractChartDisplayer* createDisplayer();
    virtual const IlvClassInfo* getDisplayerClassInfo();
    virtual IlBoolean isMulti() const;
    virtual IlUInt getMaxDataSetsCount() const;
    virtual IlUInt getChildDisplayersCount(IlUInt selectedDataSetsCount) const;
    virtual IlvAbstractChartDisplayer* createChildDisplayer(IlUInt selectedDataSetsCount);

    virtual void createEditors(IlvStIChartPanel* panel,
			       IlvStIDisplayerAccessor* displayerAcc,
			       IlvStIDisplayerEditor* displayerEditor);
};


// --------------------------------------------------------------------------
IlvDECLAREINITSTCHARTCLASS(sti_cht_displayitf)
// --------------------------------------------------------------------------
#endif /* !__IlvSt_Charts_Displayitf_H */
