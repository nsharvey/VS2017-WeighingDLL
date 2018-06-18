// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/dataccess/fielditf.h
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
// Declaration of the IliFieldItf class
// Defined in library dataccess
// --------------------------------------------------------------------------
#ifndef __Ili_Fielditf_H
#define __Ili_Fielditf_H

#if !defined(__Ilv_Base_Graphic_H)
#  include <ilviews/base/graphic.h>
#endif
#if !defined(__Ilv_Base_Gadget_H)
#  include <ilviews/base/gadget.h>
#endif
#if !defined(__Ili_Reposit_H)
#  include <ilviews/dataccess/reposit.h>
#endif

class IliFieldItf;
class IliDataSource;
class IliTable;
class IlvInputFile;
class IlvOutputFile;

#ifdef DOXYGEN_GENERATION
IlBoolean IliIsAField(IlvGraphic* g);
IliFieldItf* IliGraphicToField(IlvGraphic* g);
#else
extern ILV_INF_EXPORTEDFN(IlBoolean) IliIsAField(IlvGraphic*);
extern ILV_INF_EXPORTEDFN(IliFieldItf*) IliGraphicToField(IlvGraphic*);
#endif

enum IliFieldAccessorTag {
    IliAccValue = 0,
    IliAccAlignment,
    IliAccDataSourceColumnName,
    IliAccCompletion,
    IliAccContrained,
    IliAccDataSourceName,
    IliAccForeignDataSourceName,
    IliAccForeignDisplayColumnName,
    IliAccForeignValueColumnName,
    IliAccFormat,
    IliAccInputModified,
    IliAccLabel,
    IliAccMask,
    IliAccMaxLength,
    IliAccReadOnly,
    IliAccVisibleRowsCount,
    IliAccUseTableProperties,
    IliAccTablePropertyManagerName,
    IliAccTagsCount
};

typedef IlBoolean (*IliSupportsAccessors)(IliFieldAccessorTag);

enum IliInputPolicy {
    IliDefaultInputPolicy,
    IliStandardInputPolicy,
    IliLocalInputPolicy
};

// --------------------------------------------------------------------------
// NOTE: the methods of class IliFieldItf are prefixed with 'f_'
//	 in order to avoid conflicts with IlvGraphic and its subclasses
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// IliFieldItf
// --------------------------------------------------------------------------
class ILV_INF_EXPORTED IliFieldItf
{
public:
    IliFieldItf();
    virtual ~IliFieldItf();

    // Value
    virtual
    const IliValue&	f_getValue(IlBoolean internal = IlFalse) const;
    virtual IlBoolean	f_setValue(const IliValue& val,
				   IlBoolean internal = IlFalse);

    virtual void	f_refresh();

    virtual IlBoolean	f_isConsistent() const;
    virtual void	f_internalToExternal();
    virtual IlBoolean	f_externalToInternal();

    virtual IlBoolean	f_complete();

    virtual IlShort	f_getMaxLength() const;
    virtual void	f_setMaxLength(IlShort vmax);

    // Gadget

    inline
    const IlvGraphic*	f_getGraphic() const { return _graphic; }
    inline IlvGraphic*	f_getGraphic() { return _graphic; }

    const IlvGadget*	f_getGadget() const;
    IlvGadget*		f_getGadget();

    virtual IlBoolean	f_supportsTableProperties() const;

    IlBoolean		f_isUsingTableProperties() const;
    virtual void	f_useTableProperties(IlBoolean flag);

    const char*		f_getTablePropertyManagerName() const;
    virtual void	f_setTablePropertyManagerName(const char* name);

    virtual const IliTablePropertyManager*
    f_getEffectiveTablePropertyManager() const;
    virtual IliTablePropertyManager*
    f_getEffectiveTablePropertyManager();

    virtual IlBoolean	f_isReadOnly() const;
    virtual void	f_setReadOnly(IlBoolean flag);
    virtual void	f_selectTextForAppend();
    virtual void	f_selectTextForOverwrite();

    virtual
    IliInputPolicy	f_getInputPolicy() const;
    virtual void	f_setInputPolicy(IliInputPolicy ip);

    virtual IlBoolean	f_isInputModified() const;
    virtual void	f_setInputModified(IlBoolean flag);

    virtual IlBoolean	f_isModifiedStateIgnored() const;

    virtual void	f_ignoreModifiedState(IlBoolean ignore);
    virtual
    const IliFormat&	f_getFormat() const;
    virtual void	f_setFormat(const IliFormat& fmt);
    virtual
    const IliInputMask& f_getMask() const;
    virtual void	f_setMask(const IliInputMask& msk);
    virtual
    IlvAlignment	f_getAlignment() const;
    virtual void	f_setAlignment(IlvAlignment align);

    virtual IlBoolean	f_canMapValue() const;
    virtual void	f_mapValue(IliValue&) const;

    virtual IlBoolean	f_canDrawValue() const;
    virtual void	f_drawValue(IlvPort* dst,
				    const IlvRect& bbox,
				    const IliValue& value,
				    IlBoolean selected,
				    IlvPalette* fillPalette,
				    IlvPalette* textPalette,
				    const IlvRegion* clip = 0) const;

    virtual IlBoolean	f_opensADialog() const;
    virtual IlBoolean	f_hasLabel() const;
    virtual const char* f_getLabel() const;
    virtual void	f_setLabel(const char* label);
    virtual IlBoolean	f_isAutoFitPullDown() const;
    virtual void	f_setAutoFitPullDown(IlBoolean flag);

    const IlvGraphic*	f_getOwner() const;
    IlvGraphic*		f_getOwner();
    void		f_setOwner(IlvGraphic*);

    void		f_callCallbacks(const IlvSymbol*);
    void		f_callPrimaryCallback();
    virtual void	f_callInputModifiedFinalizer();

    // Data source
    const char*		f_getDataSourceName() const;
    virtual void	f_setDataSourceName(const char* name);
    const IliDataSource* f_getDataSource() const;
    IliDataSource*	f_getDataSource();

    virtual void	f_setDataSource(IliDataSource* ds,
					IlBoolean owner = IlFalse);
    IlBoolean		f_isDataSourceOwner() const;

    const char*		f_getDataSourceColumnName() const;
    virtual void	f_setDataSourceColumnName(const char* name);

    IlBoolean		f_isAutoConnectEnabled() const;
    virtual void	f_enableAutoConnect(IlBoolean);

    IlBoolean		f_isAutoReDrawEnabled() const;
    virtual void	f_enableAutoReDraw(IlBoolean);

    IlBoolean		f_connectToDataSource();
    void		f_disconnectFromDataSource();
    IlBoolean		f_isConnectedToDataSource() const;

    virtual void	f_dataSourceToField(IlInt colno);
    virtual void	f_fieldToDataSource(IlInt colno);
    virtual IlBoolean	f_isColumnModified(IlInt colno) const;

    const IliDataSource* f_getEffectiveDataSource() const;

    // Foreign table
    const char*		f_getForeignDataSourceName() const;
    virtual void	f_setForeignDataSourceName(const char* name);
    const IliTable*	f_getForeignTable() const;
    IliTable*		f_getForeignTable();
    virtual void	f_setForeignTable(IliTable* tbl,
					  IlBoolean owner = IlFalse);
    IlBoolean		f_isForeignTableOwner() const;

    const char*		f_getForeignValueColumnName() const;
    virtual void	f_setForeignValueColumnName(const char* name);

    const char*		f_getForeignDisplayColumnName() const;
    virtual void	f_setForeignDisplayColumnName(const char* name);
    IlBoolean		f_isConstrained() const;
    virtual void	f_setConstrained(IlBoolean flag);
    IlBoolean		f_isCompletionEnabled() const;
    virtual void	f_enableCompletion(IlBoolean flag);

    IlInt		f_getVisibleRowsCount() const;
    virtual void	f_setVisibleRowsCount(IlInt count);

    static IlBoolean	FetchMoreRows(IliTable* table,
				      IlInt firstRow,
				      IlInt visibleCount);

    static IlvSymbol*	InputModifiedSymbol();

    void		f_addInputModifiedHook(IlvGraphicCallback hook,
					       IlAny arg);
    void		f_replaceInputModifiedHook(IlvGraphicCallback hook,
						   IlAny arg);
    void		f_removeInputModifiedHook(IlvGraphicCallback hook,
						  IlAny arg);
    void		f_callInputMofifiedHooks();

    void		f_applyReferences(IlvApplyObject f, IlAny a);
    void		f_killFocus();
    void		f_setFocus();
    void		f_needsReDraw();
    void		f_needsReDraw(const IlvRect&);
    void		f_needsReDraw(const IlvRegion&);

    // Accessors
    virtual IlvValueTypeClass*	f_getValueType(const IlvSymbol*) const;
    virtual IlBoolean	f_getValueDescriptor(IlvValue&) const;
    virtual IlBoolean	f_queryValue(IlvValue&) const;
    virtual IlBoolean	f_applyValue(const IlvValue&);
    virtual IlBoolean	f_supportsAccessor(IliFieldAccessorTag) const = 0;
    static void		F_getAccessors(const IlvSymbol* const**,
				       const IlvValueTypeClass* const**,
				       IlUInt&,
				       IliSupportsAccessors);

protected:
    IlvGraphic*		_graphic;
    IlvGraphic*		_owner;
    IlBoolean		_inputModified;
    IlBoolean		_ignoreModifiedState;
    IlBoolean		_isConnectedToDataSource;
    IlBoolean		_autoReDraw;
    IlBoolean		_autoConnect;
    IlBoolean		_primaryDataSourceOwner;
    IlBoolean		_foreignTableOwner;
    IlBoolean		_notifyOnInputModified;
    IlBoolean		_isConstrained;
    IlBoolean		_isCompletionEnabled;
    IlBoolean		_isSubscribedToPrimary;
    IlBoolean		_isSubscribedToForeign;
    IlBoolean		_inSetValue;
    IlBoolean		_useTableProperties;
    IliDataSource*	_primaryDataSource;
    IliTable*		_foreignTable;
    IliString		_primaryDataSourceName;
    IliString		_primaryDataSourceColumnName;
    IliString		_foreignDataSourceName;
    IliString		_foreignValueColumnName;
    IliString		_foreignDisplayColumnName;
    IliString		_tablePropMgrName;
    IlInt		_visibleRowsCount;
    IlvAList		_inputModifiedHooks;

    inline IlBoolean	f_isInSetValue() const { return _inSetValue; }
    inline void		f_setInSetValue(IlBoolean f) { _inSetValue = f; }

    IlBoolean		f_isNotifyOnInputModified() const
	{ return _notifyOnInputModified; }
    void		f_setNotifyOnInputModified(IlBoolean f)
	{ _notifyOnInputModified = f; }
    void		f_setConnectedToDataSource(IlBoolean f)
	{ _isConnectedToDataSource = f; }

    void		setFieldProperty(IlvGraphic*);

    void		f_setGadget(IlvGadget*);
    void		f_setGraphic(IlvGraphic* g);
    void		f_set(IlvGraphic* g, const IliFieldItf& other);
    void		f_read(IlvInputFile& input);
    void		f_write(IlvOutputFile& output) const;

    void f_subscribe();
    void		f_unsubscribe();
    void		f_subscribeToPrimary();
    void		f_unsubscribeToPrimary();
    void		f_subscribeToForeign();
    void		f_unsubscribeToForeign();

    virtual IlBoolean	f_doConnect();
    virtual void	f_doDisconnect();

    IlBoolean		f_closeValue() const;
};

#endif /* !__Ili_Fielditf_H */
