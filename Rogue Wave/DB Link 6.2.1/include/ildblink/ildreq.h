// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ildreq.h
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
// DBLink Cursor class
// ----------------------------------------------------------------------------

#ifndef __ILD_ILDREQ_H
#define __ILD_ILDREQ_H

#ifndef __Il_INum_H
#   include <ildblink/ilinum.h>
#endif
#ifndef __Il_Ilidtime_H
#   include <ildblink/ilidtime.h>
#endif
#ifndef __ILD_ILDTUPLE_H
#   include <ildblink/ildtuple.h>
#endif
#ifndef __ILD_ILDBASE_H
#   include <ildblink/ildbase.h>
#endif

class IldDbmsModel;
class IldDbmsImp;
class IldRequestImp;
class IldADTValue;

// ============================================================================
// IldRequest class.
// ============================================================================
class ILD_EXPORTED IldRequest : public virtual IldIldBase {

public:
    virtual
    ~IldRequest              () {}

    inline 
    IlBoolean         isDbms                   () const
    { return IlFalse; }

    // Should be private
    // --------------------------
    // Global accessors/modifiers
    // --------------------------
    virtual
    IldDbms&          getDbms                  () const = 0;

    virtual
    IlBoolean         isFree                   () = 0;

    virtual
    const char*       getCursorName            () const = 0;

    virtual
    IldRequest&       setCursorName            (const char* cursName) = 0;

    virtual
    IlBoolean         hasTuple                 () const = 0;

    virtual
    IlInt             getStatus                () const = 0;

    virtual
    IldRequest&       setReadOnly              (IlBoolean flag = IlTrue) = 0;

    virtual
    IlBoolean         isReadOnly               () const = 0;

    virtual
    IldRequest&       setCursorModeOn          (IlBoolean flag = IlTrue) = 0;

    virtual
    IlBoolean         isCursorModeOn           () const = 0;

    virtual
    IldRequest&       setScrollable            (IlBoolean flag = IlTrue) = 0;

    virtual
    IlBoolean         isScrollable             () const = 0;

    // -------------------------
    // Overall handling
    // -------------------------
    virtual
    IldRequest&       release                  () = 0;

    virtual
    IldRequest&       closeCursor              () = 0;

    virtual
    IldRequest&       parse                    (const char* query) = 0;

    virtual
    IldRequest&       execute                  (IlInt* rowCount = 0,
						IlInt count = -1) = 0;

    virtual
    IldRequest&       execute                  (const char* query,
						IlInt* rowCount = 0) = 0;

    virtual
    IldRequest&       fetch                    () = 0;

    virtual
    IldRequest&       fetchScroll              (IlInt fetchOrientation = 
						IldFetchDirectionNext,
						IlInt fetchOffset = 0) = 0;

    virtual
    IlAny             getHook                  () const = 0;

    virtual
    IldErrorReporter* getErrorReporter         () const = 0;

    virtual
    IldRequest&       setErrorReporter         (IldErrorReporter* rep) = 0;

    // -------------------------
    // BLOBs handling
    // -------------------------
    virtual
    IldRequest&       insertLongText           (const char* text,
						IlUInt textSize,
						const char* tableName,
						const char* columnName,
						const char* where = 0) = 0;

    virtual
    IldRequest&       insertBinary             (IldBytes& binaryData,
						const char* tableName,
						const char* columnName,
						const char* where = 0) = 0;

    virtual
    IldRequest&       getLargeObject           (const char* tableName,
						const char* columnName,
						const char* whereCond,
						const char* fileName) = 0;

    virtual
    IldRequest&       startGetLargeObject      (const char* tableName,
						const char* columnName,
						const char* whereCond) = 0;

    virtual
    IldRequest&       getLargeObjectChunk      (IlUInt size,
						IlUChar* data,
						IlUInt* offset) = 0;

    // --------------------------
    // Results Set management
    // --------------------------
    // Binding
    virtual
    IldRequest&       bindCol                  (IlUShort index,
						IldColumnType type,
						IlAny buffer,
						IlUInt size = 0,
						short* indicators = 0) = 0;

    virtual
    IldRequest&       bindCol                  (const char* columnName,
						IldColumnType type,
						IlAny buffer,
						IlUInt size = 0,
						short* indicators = 0) = 0;

    // ------------------------
    // Array fetch handling
    // ------------------------
    virtual
    IldRequest&       setColArraySize          (IlUInt size) = 0;

    virtual
    IldRequest&       removeColArraySize       () = 0;

    virtual
    IlUInt            getColArraySize          () const = 0;

    virtual
    IlUInt            getRowProcessedCount     () const = 0;

    virtual
    IldRequest&       setRowPos                (IlUInt pos) = 0;

    virtual
    IlUInt            getRowPos                () const = 0;

    // ----------------------------------
    // Results Set Descriptor (ARD & IRD)
    // ----------------------------------
    virtual
    IlUShort          getColCount              () const = 0;

    virtual
    IldAppDescriptor* getColDescriptor         (IlUShort col) = 0;

    virtual
    short             getColIndex              (const char* colName) = 0;

    virtual
    const char*       getColName               (IlUShort index) = 0;

    virtual
    IldColumnType     getColType               (IlUShort index) const = 0;

    virtual
    short             getColSQLType            (IlUShort index) const = 0;

    virtual
    const char*       getColSQLTypeName        (IlUShort index) const = 0;

    virtual
    IlUInt            getColSize               (IlUShort index) const = 0;

    // Columns Data Accessors
    virtual
    IlBoolean         isColNull                (IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IlUChar           getColByteValue          (IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IlInt             getColIntegerValue       (IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    double            getColRealValue          (IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    double            getColMoneyValue         (IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    const char*       getColDateValue          (IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IlNumeric         getColNumericValue       (IlUShort col,
						IlUInt row = 0) = 0;

    virtual 
    IldDateTime       getColDateTimeValue      (IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IldDateTime       getColDateTimeValue      (const unsigned char* buffer) = 0;

    virtual
    const char*       getColStringValue        (IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    const char*       getColRTrimedStringValue (IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    const char*       getColLongTextValue      (IlUShort col,
						IlUInt row = 0,
						IlInt* size = 0) = 0;

    virtual
    IldBytes          getColBinaryValue        (IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IldADTValue*      getColADTValue           (IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IldBytes          getColRefValue           (IlUShort col,
						IlUInt row = 0) = 0;

    // ----------------------
    // Parameters management
    // ----------------------
    // ----------------
    // Binding
    // ----------------
    virtual
    IldRequest&       bindParam                (IlUShort index,
						IldColumnType type,
						IlInt size = -1,
						IlAny buffer = 0,
						short* indicators = 0,
						IlBoolean out = IlFalse,
						IlUShort arrSize = 0,
						IldADTDescriptor* adt = 0) = 0;

    virtual
    IldRequest&       bindParam                (const char* varName,
						IldColumnType type,
						IlInt size = -1,
						IlAny buffer = 0,
						short* indicators = 0,
						IlBoolean out = IlFalse,
						IlUShort arrSize = 0,
						IldADTDescriptor* adt = 0) = 0;

    // ---------------------------
    // Push parameter values
    // ---------------------------
    virtual
    IldRequest&       setParamValue            (char value,
						IlUShort col,
						IlUInt row = 0) = 0;
    virtual
    IldRequest&       setParamValue	       (IlInt value,
						IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IldRequest&       setParamValue            (double value,
						IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IldRequest&       setParamValue            (const char* value,
						IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IldRequest&       setParamValue            (IldBytes& value,
						IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IldRequest&       setParamValue            (const IldDateTime* value,
						IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IldRequest&       setParamValue            (const IlNumeric* value,
						IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IldRequest&       setParamValue            (const IldADTValue* value,
						IlUShort col,
						IlUInt row = 0) = 0;

    virtual
    IldRequest&       setParamNullInd          (IlUShort col,
						IlUInt row = 0) = 0;

    // -------------------------------
    // Array bind handling
    // -------------------------------
    virtual
    IldRequest&       setParamArraySize        (IlUInt size) = 0;

    virtual
    IldRequest&       removeParamArraySize     () = 0;

    virtual
    IlUInt            getParamArraySize        () const = 0;

    // -------------------------------------
    // Parameters Set Descriptor (APD & IPD)
    // -------------------------------------
    virtual
    IlUShort          getParamCount            () const = 0;

    virtual
    IldAppDescriptor* getParamDescriptor       (IlUShort index) = 0;

    virtual
    short             getParamIndex            (const char* varName) = 0;

    virtual
    const char*       getParamName             (IlUShort index) = 0;

    virtual
    IldColumnType     getParamType             (IlUShort index) const = 0;

    virtual
    short             getParamSQLType          (IlUShort index) const = 0;

    virtual
    const char*       getParamSQLTypeName      (IlUShort index) const = 0;

    virtual
    IlUInt             getParamSize             (IlUShort index) const = 0;

    virtual
    IlUInt             getParamBufferSize       (IlUShort index) const = 0;

    virtual
    void              setParamSize             (IlUShort i,
						IlUInt size) = 0;
    // --------------------
    // Get parameter values
    // --------------------
    virtual
    IlBoolean         isParamNull              (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    double            getParamMoneyValue       (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    IlUChar           getParamByteValue        (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    IldBytes          getParamBinaryValue      (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    const char*       getParamLongTextValue    (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    IlNumeric         getParamNumericValue     (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    IlInt             getParamIntegerValue     (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    double            getParamRealValue        (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    const char*       getParamStringValue      (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    const char*       getParamDateValue        (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    IldDateTime       getParamDateTimeValue    (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    IldADTValue*      getParamADTValue         (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    IldBytes          getParamRefValue         (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    IldRequest*       getParamCursorValue      (IlUShort index,
						IlUInt row = 0) = 0;

    virtual
    IlBoolean         isNullIndicatorOn        (short* buffer,
						IlUInt row = 0) const = 0;

    /* Asynchronous management functions : */
    // Checks whether an Asynchronous operation is running or not :
    virtual 
    IlBoolean         isCompleted              () const = 0;
} ;

#endif // __ILD_ILDREQ_H
