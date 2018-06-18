// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/charts/xml.h
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
// Declaration of IlvXMLChartData
// --------------------------------------------------------------------------
#if !defined(__Ilv_Charts_XML_H)
#define __Ilv_Charts_XML_H

#include <ilog/xml.h>
#include <ilog/string.h>
#include <ilog/list.h>
#include <ilog/gregocal.h>

#include <ilviews/charts/data.h>

// ----------------------------------------------------------------------

class ILVCHTEXPORTED IlvXMLProperty
{
public:
    IlvXMLProperty();
    virtual ~IlvXMLProperty();

    IlString	name;
    IlAny	value;
};

// ----------------------------------------------------------------------

class IlvXMLSeries
{
public:
    IlvXMLSeries(IlString i) : id(i), isTime(IlFalse) {}

    IlString		id;

    IlBoolean		isTime;

    IlvChartDoubleArray	values;

    IlArray		properties;
};

// ----------------------------------------------------------------------

class ILVCHTEXPORTED IlvXMLValueListProcessor
{
public:
    IlvXMLValueListProcessor();
    virtual ~IlvXMLValueListProcessor();

    virtual
    IlvXMLSeries*	processValueList(IlvXMLSeries* serie,
					 IlXmlElement* el,
					 IlString sep);
};

// ----------------------------------------------------------------------

class ILVCHTEXPORTED IlvXMLDateListProcessor : public IlvXMLValueListProcessor
{
public:
    IlvXMLDateListProcessor();

    virtual
    IlvXMLSeries*	processValueList(IlvXMLSeries* serie,
					 IlXmlElement* el,
					 IlString sep);

    virtual void	parseDate(IlGregorianCalendar& res,
				  IlString dateString);
};

// ----------------------------------------------------------------------
class ILVCHTEXPORTED IlvXMLPropertyReader
{
public:
    virtual ~IlvXMLPropertyReader();

    virtual
    IlvXMLProperty*	readProperty(IlXmlElement* propertyElt) = 0;

    virtual IlBoolean	setProperty(IlvChartDataSet* dataSet,
				    IlString propertyName,
				    IlAny value) = 0;
};

// ----------------------------------------------------------------------
class IlvStringAnyAList;

class ILVCHTEXPORTED IlvXMLChartData : public IlvAbstractChartData
{
public:
    IlvXMLChartData(IlvDisplay *display, const char* fileName);

    virtual ~IlvXMLChartData();

    void		parse();

    virtual IlUInt	getDataSetsCount() const;

    virtual IlBoolean	isLimited() const;

    virtual IlBoolean	isWritable() const;

    virtual IlBoolean	isRemovalAllowed() const;

    virtual
    IlvChartDataSet* const* getDataSets(IlUInt& count) const;

    virtual
    IlvChartDataSet*	getDataSet(IlUInt index=0) const;

    IlvChartDataSet*	getDataSetByName(const char* name) const;

    virtual IlBoolean	setDataSets(IlUInt& count,
				    IlvChartDataSet* const* dataSets,
				    IlBoolean copy = IlFalse);
    virtual IlBoolean	setDataSet(IlUInt dataSetIndex,
				   IlvChartDataSet* dataSet,
				   IlBoolean copy = IlFalse);
    virtual IlBoolean	addDataSet(IlvChartDataSet* dataSet,
				   IlBoolean copy = IlFalse);
    virtual IlBoolean	insertDataSet(IlvChartDataSet* dataSet,
				      IlUInt index = IlvLastPositionIndex,
				      IlBoolean copy = IlFalse);
    virtual IlBoolean	removeDataSet(IlUInt dataSetIndex);
    virtual void	removeDataSets();

    //== Virtual copy constructor
    virtual
    IlvAbstractChartData* copy() const;

    virtual void	write(IlvOutputFile& file) const;

    void		registerValueListProcessor(IlString typeName,
						   IlvXMLValueListProcessor*
						   processor);

    void		registerPropertyReader(IlString propertyName,
					       IlvXMLPropertyReader* reader);

    virtual
    IlvChartDataSet*	createDataSet(IlString name,
				      IlvChartDoubleArray xvalues,
				      IlvChartDoubleArray yvalues);

protected:
    void		setValueListProcessor(IlvXMLValueListProcessor*);

    void		extractDataSets(IlXmlElement* rootElement);
    void		buildDataSets();
    void		setProperties(IlvChartDataSet*, IlvXMLSeries*);

    void		processData(IlXmlElement*);
    void		processSeries(IlXmlElement*);
    IlvXMLSeries*	processValueList(IlvXMLSeries* series,
					 IlXmlElement*,
					 IlString sep = ",");
    IlvXMLProperty*	processProperty(IlXmlElement*, IlString name);

    IlvXMLPropertyReader* getPropertyReader(IlString);
    IlvXMLValueListProcessor* getValueListProcessor(IlString);

    IlString		_fileName;
    IlvDisplay*		_display;

    IlArray		_series; // array of IlvXMLSeries*
    IlArray		_properties;

    IlvXMLSeries*	_xSeries;

    IlvStringAnyAList*	_valProcTable;
    IlvStringAnyAList*	_propReaderTable;

    IlvXMLValueListProcessor* _valueListProcessor;

    IlXmlDocument	_xmlDocument;

    IlvChartDataSetCollection _dataSetCollection;

    IlString		_xSeriesName;
    IlvChartYValueSet	_xTmpDataSet;

    IlBoolean		_docParsed;
};

#endif
