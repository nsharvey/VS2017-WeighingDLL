// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/reqmodl.h
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
// Model for inheritance of DBLink Cursor class : IldRequest.
// ----------------------------------------------------------------------------

#ifndef __ILD_REQMODL_H
#define __ILD_REQMODL_H

#ifndef __ILD_BASEMODL_H
#   include <ildblink/basemodl.h>
#endif
#ifndef __ILD_ILDREQ_H
#   include <ildblink/ildreq.h>
#endif

class IldDbms;
class IldADTValue;

#ifdef WINDOWS
// MSVC not really STD conformant: using clause!
#pragma warning(disable : 4250)
#endif
// ============================================================================
// IldRequest class.
// ============================================================================
class ILD_EXPORTED IldRequestModel
    : public IldBaseModel, public IldRequest {

protected:
    IldRequest*		_ptr;
    IldRequest&		_req;
    IldDbmsModel*	_dbms;

    IldRequest&		setErrorReporter	();
    // release() is not publicly available for IldRequestModel class.
    // It still is used internally against the twin class.
    // The destructor of the class must be used instead.
    virtual
    IldRequest&		release			();
    // As release(), this function is deprecated for IldRequestModel class
    // public interface.
    virtual
    IlBoolean		isFree			();

public:
    using IldBaseModel::initializeError;
    using IldBaseModel::fillError;
    using IldBaseModel::fillInformation;
    using IldBaseModel::operator!;
    using IldBaseModel::isErrorRaised;
    using IldBaseModel::isInformationRaised;
    using IldBaseModel::getError;
    using IldBaseModel::getInformation;
    using IldBaseModel::getInformationCode;
    using IldBaseModel::getInformationMessage;
    using IldBaseModel::getErrorCode;
    using IldBaseModel::getErrorMessage;
    using IldBaseModel::getErrorOrigin;
    using IldBaseModel::getErrorSqlstate;
    using IldBaseModel::getErrorConnection;
    using IldBaseModel::getErrorName;
    using IldBaseModel::useStringDate;
    using IldBaseModel::setStringDateUse;
    using IldBaseModel::useStringNumeric;
    using IldBaseModel::setStringNumericUse;
    using IldBaseModel::useNumeric;
    using IldBaseModel::setNumericUse;

			IldRequestModel		(IldDbmsModel*);

    virtual
			~IldRequestModel	();

    inline
    IldRequest&		getReqRef		() const
    { return _req; }

    inline
    IlBoolean		isDbms			() const
    { return IlFalse; }

    // --------------------------
    // Global accessors/modifiers
    // --------------------------
    virtual
    IldDbms&		getDbms			() const;

    virtual
    const char*		getCursorName		() const;

    virtual
    IldRequest&		setCursorName		(const char* cName);

    virtual
    IlBoolean		hasTuple		() const;

    virtual
    IlInt		getStatus		() const ;

    virtual
    IldRequest&		setReadOnly		(IlBoolean f = IlTrue);

    virtual
    IlBoolean		isReadOnly		() const;

    virtual
    IldRequest&		setCursorModeOn		(IlBoolean f = IlTrue);

    virtual
    IlBoolean         isCursorModeOn		() const;

    virtual
    IldRequest&		setScrollable		(IlBoolean f = IlTrue);

    virtual
    IlBoolean		isScrollable		() const;

    // -------------------------
    // Overall handling
    // -------------------------
    virtual
    IldRequest&		closeCursor		();

    virtual
    IldRequest&		parse			(const char* query);

    virtual
    IldRequest&		execute			(IlInt* rowCount = 0,
						 IlInt count = -1);

    virtual
    IldRequest&		execute			(const char* query,
						 IlInt* rowCount = 0);

    virtual
    IldRequest&		fetch			();

    virtual
    IldRequest&		fetchScroll		(IlInt orient = 
						 IldFetchDirectionNext,
						 IlInt offset = 0);

    virtual
    IlAny		getHook			() const;

    virtual
    IldErrorReporter*	getErrorReporter	() const;

    virtual
    IldRequest&		setErrorReporter	(IldErrorReporter* rep);

    // -------------------------
    // BLOBs handling
    // -------------------------
    virtual
    IldRequest&		insertLongText		(const char* text,
						 IlUInt size,
						 const char* table,
						 const char* column,
						 const char* where = 0);

    virtual
    IldRequest&		insertBinary		(IldBytes& data,
						 const char* table,
						 const char* column,
						 const char* where = 0);

    virtual
    IldRequest&		getLargeObject		(const char* table,
						 const char* column,
						 const char* where,
						 const char* file);

    virtual
    IldRequest&		startGetLargeObject	(const char* table,
						 const char* column,
						 const char* where);

    virtual
    IldRequest&		getLargeObjectChunk	(IlUInt size,
						 IlUChar* data,
						 IlUInt* offset);

    // --------------------------
    // Results Set management
    // --------------------------
    // Binding
    virtual
    IldRequest&		bindCol			(IlUShort i,
						 IldColumnType t,
						 IlAny buf,
						 IlUInt size = 0,
						 short* inds = 0);

    virtual
    IldRequest&		bindCol			(const char* name,
						 IldColumnType t,
						 IlAny buff,
						 IlUInt size = 0,
						 short* inds = 0);

    // ---------------------
    // Array fetch handling
    // ---------------------
    virtual
    IldRequest&		setColArraySize		(IlUInt size);

    virtual
    IldRequest&		removeColArraySize	();

    virtual
    IlUInt		getColArraySize		() const;

    virtual
    IlUInt		getRowProcessedCount	() const;

    virtual
    IldRequest&		setRowPos		(IlUInt);

    virtual
    IlUInt		getRowPos		() const;

    // --------------------------
    // Results Set Descriptor (ARD & IRD)
    // --------------------------
    virtual
    IlUShort		getColCount		() const;

    virtual
    IldAppDescriptor*	getColDescriptor	(IlUShort c);

    virtual
    short		getColIndex		(const char* name);

    virtual
    const char*		getColName		(IlUShort i);

    virtual
    IldColumnType	getColType		(IlUShort i) const;

    virtual
    short		getColSQLType		(IlUShort i) const;

    virtual
    const char*		getColSQLTypeName	(IlUShort i) const;

    virtual
    IlUInt		getColSize		(IlUShort i) const;

    // ----------------------
    // Columns Data Accessors
    // ----------------------
    virtual
    IlBoolean		isColNull		(IlUShort c,
						 IlUInt r = 0);

    virtual
    IlUChar		getColByteValue		(IlUShort c,
						 IlUInt r = 0);

    virtual
    IlInt		getColIntegerValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    double		getColRealValue		(IlUShort c,
						 IlUInt r = 0);

    virtual
    double		getColMoneyValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    const char*		getColDateValue		(IlUShort c,
						 IlUInt r = 0);

    virtual
    IlNumeric		getColNumericValue	(IlUShort c,
						 IlUInt r = 0);

    virtual 
    IldDateTime		getColDateTimeValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    IldDateTime		getColDateTimeValue	(const unsigned char*);

    virtual
    const char*		getColStringValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    const char*		getColRTrimedStringValue(IlUShort c,
						 IlUInt r = 0);

    virtual
    const char*		getColLongTextValue	(IlUShort c,
						 IlUInt r = 0,
						 IlInt* s = 0);

    virtual
    IldBytes		getColBinaryValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    IldADTValue*	getColADTValue		(IlUShort c,
						 IlUInt r = 0);

    virtual
    IldBytes		getColRefValue		(IlUShort c,
						 IlUInt r = 0);  
    // ----------------------
    // Parameters management
    // ----------------------
    // Binding
    virtual
    IldRequest&		bindParam		(IlUShort i,
						 IldColumnType t,
						 IlInt s = -1,
						 IlAny buff = 0,
						 short* inds = 0,
						 IlBoolean out = IlFalse,
						 IlUShort aSize = 0,
						 IldADTDescriptor* adt = 0);

    virtual
    IldRequest&		bindParam		(const char* name,
						 IldColumnType t,
						 IlInt s = -1,
						 IlAny buff = 0,
						 short* inds = 0,
						 IlBoolean out = IlFalse,
						 IlUShort aSize = 0,
						 IldADTDescriptor* adt = 0);

    // ---------------------
    // Push parameter values
    // ---------------------
    virtual
    IldRequest&		setParamValue		(char v,
						 IlUShort c,
						 IlUInt r = 0);

    virtual
    IldRequest&		setParamValue		(IlInt v,
						 IlUShort c,
						 IlUInt r = 0);

    virtual
    IldRequest&		setParamValue		(double v,
						 IlUShort c,
						 IlUInt r = 0);

    virtual
    IldRequest&		setParamValue		(const char* v,
						 IlUShort c,
						 IlUInt r = 0);

    virtual
    IldRequest&		setParamValue		(IldBytes& v,
						 IlUShort c,
						 IlUInt r = 0);

    virtual
    IldRequest&		setParamValue		(const IldDateTime* v,
						 IlUShort c,
						 IlUInt r = 0);

    virtual
    IldRequest&		setParamValue		(const IlNumeric* v,
						 IlUShort c,
						 IlUInt r = 0);

    virtual
    IldRequest&		setParamValue		(const IldADTValue* v,
						 IlUShort c,
						 IlUInt r = 0);

    virtual
    IldRequest&		setParamNullInd		(IlUShort c,
						 IlUInt r = 0);

    // -------------------
    // Array bind handling
    // -------------------
    virtual
    IldRequest&		setParamArraySize	(IlUInt s);

    virtual
    IldRequest&		removeParamArraySize	();

    virtual
    IlUInt		getParamArraySize	() const;

    // -------------------------
    // Parameters Set Descriptor (APD & IPD)
    // -------------------------
    virtual
    IlUShort		getParamCount		() const;

    virtual
    IldAppDescriptor*	getParamDescriptor	(IlUShort i);

    virtual
    short		getParamIndex		(const char* name);

    virtual
    const char*		getParamName		(IlUShort i);

    virtual
    IldColumnType	getParamType		(IlUShort i) const;

    virtual
    short		getParamSQLType		(IlUShort i) const;

    virtual
    const char*		getParamSQLTypeName	(IlUShort i) const;

    virtual
    IlUInt		getParamSize		(IlUShort i) const;

    virtual
    IlUInt		getParamBufferSize	(IlUShort i) const;

    virtual
    void		setParamSize		(IlUShort i,
						 IlUInt s);

    // --------------------
    // Get parameter values
    // --------------------
    virtual
    IlBoolean		isParamNull		(IlUShort c,
						 IlUInt r = 0);

    virtual
    double		getParamMoneyValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    IlUChar		getParamByteValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    IldBytes		getParamBinaryValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    const char*		getParamLongTextValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    IlNumeric		getParamNumericValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    IlInt		getParamIntegerValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    double		getParamRealValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    const char*		getParamStringValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    const char*		getParamDateValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    IldDateTime		getParamDateTimeValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    IldADTValue*	getParamADTValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    IldBytes		getParamRefValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    IldRequest*		getParamCursorValue	(IlUShort c,
						 IlUInt r = 0);

    virtual
    IlBoolean		isNullIndicatorOn	(short* buff,
						 IlUInt r = 0) const;

    /* Asynchronous management functions : */
    // Checks whether an Asynchronous operation is running or not :
    virtual
    IlBoolean		isCompleted		() const;
} ;

#endif // __ILD_REQMODL_H
