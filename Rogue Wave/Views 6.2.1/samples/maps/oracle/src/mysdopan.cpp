// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/maps/oracle/src/mysdopan.cpp
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
// Rogue Wave Views - Maps add-on
// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
#include <mysdopan.h>
#include <defdbmsfact.h>

#include <ildblink/ilddbms.h>
#include <ildblink/dblink.h>
#include <ildblink/dberr.h>
#include <ildblink/ilderr.h>

#include <ilviews/gadgets/combo.h>
#include <ilviews/gadgets/button.h>
#include <ilviews/gadgets/numfield.h>
#include <ilviews/gadgets/toolbar.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilviews/gadgets/toggle.h>
#include <ilviews/graphics/gauge.h>
#include <ilviews/graphics/tooltip.h>
#include <ilviews/bitmaps/png.h>
#include <ilviews/util/runtime.h>
#include <ilviews/base/error.h>
#include <ilviews/manager/zoomint.h>
#include <ilviews/manager/paninter.h>
#include <ilviews/manager/magview.h>
#include <ilviews/maps/tiling/tilecache.h>
#include <ilviews/maps/dftrenderer.h>
#include <ilviews/maps/mapfeature.h>
#include <ilviews/maps/coord.h>
#include <ilviews/maps/mapinfo.h>
#include <ilviews/maps/projection/allprojs.h>
#include <ilviews/maps/attribute/all.h>
#include <ilviews/maps/rendering/all.h>
#include <ilviews/maps/format/maploader.h>
#include <ilviews/maps/format/oracle/sdowrite.h>
#include <ilviews/maps/format/oracle/sdoread.h>
#include <ilviews/maps/format/oracle/sdolayer.h>
#include <ilviews/maps/format/oracle/sdotileload.h>
#include <ilviews/maps/format/oracle/sdoutil.h>
#include <ilviews/maps/format/oracle/objectmodel/8iutil.h>
#include <ilviews/maps/format/oracle/objectmodel/8itileload.h>
#include <ilviews/maps/format/oracle/objectmodel/8iread.h>
#include <ilviews/maps/format/oracle/objectmodel/8iwrite.h>
#include <ilviews/maps/format/oracle/objectmodel/8ilayer.h>

#if defined(IL_STD)
#  include <fstream>
#else
#  include <fstream.h>
#endif

// --------------------------------------------------------------------------
extern char* IlvGetStringFrom(ILVSTDPREF ostrstream&);

// --------------------------------------------------------------------------
// Static and callback functions
// --------------------------------------------------------------------------

static void
SetVisibleFieldsLayer(IlvGadgetContainer* cont,IlBoolean visible)
{
    cont->getObject("labelid")->setVisible(visible);
    cont->getObject("id")->setVisible(visible);
    cont->getObject("labelwidth")->setVisible(visible);
    cont->getObject("tileWidth")->setVisible(visible);
    cont->getObject("labelheight")->setVisible(visible);
    cont->getObject("tileHeight")->setVisible(visible);
    cont->getObject("extentof")->setVisible(visible);
}

// --------------------------------------------------------------------------
static void
DestroyCB(IlvView* v, IlvAny a)
{
    AttributesPanel* view = (AttributesPanel*)v;
    MySdopan* pan = view->_pan;
    delete view;
    pan->_select->_attrPan = 0;
}

// --------------------------------------------------------------------------
static void
CloseAttributePanelCB(IlvGraphic* g, IlvAny a)
{
    AttributesPanel* view = (AttributesPanel*)a;
    MySdopan* pan = view->_pan;
    delete view;
    pan->_select->_attrPan = 0;
}

// --------------------------------------------------------------------------
static void
DeselectCB(IlvGraphic* g, IlvAny a)
{
    AttributesPanel* attrpan = (AttributesPanel*)a;
    IlUInt count = attrpan->getCardinal();
    for (IlUInt i = 0; i < count; i++) {
	IlvGraphic* gr = attrpan->getObject(i);
	if (gr->getClassInfo()->isSubtypeOf(IlvToggle::ClassInfo()) &&
	    gr != g &&
	    ((IlvToggle*)gr)->getState()) {
	    ((IlvToggle*)gr)->setState(IlFalse);
	    ((IlvToggle*)gr)->reDraw();
	}
    }
}

// --------------------------------------------------------------------------
// Updates the feature attribute
// --------------------------------------------------------------------------
static void
UpdateCB(IlvGraphic* g, IlvAny a)
{
    AttributesPanel* attrpan = (AttributesPanel*)a;
    MySdopan* sdopanel = attrpan->_pan;
    IlvTextField* tf = (IlvTextField*)g;
    IlString tfName = IlString(tf->getName());
    IlString number = tfName.getSubString(5);
    IlvToggle* label = (IlvToggle*)
    	attrpan->getObject((IlString("label") + number).getValue());
    const char* name = label->getLabel();
    IlvFeatureAttribute* attributeToUpdate = 0;
    IlUInt nb = 0;
    IlvGraphic* const* graphics =
	sdopanel->_select->getManager()->getSelections(nb);
    IlvGraphic* gr = graphics[0];
    IlvFeatureAttributeProperty* ap = (IlvFeatureAttributeProperty*)
	gr->getNamedProperty(IlvFeatureAttributeProperty::GetName());
    const IlvFeatureAttributeInfo* info = ap->getInfo();
    IlUInt intNumber = atoi(number.getValue());
    if (info->getAttributeClass(intNumber)
	->isSubtypeOf(IlvIntegerAttribute::ClassInfo())) {
	attributeToUpdate = new IlvIntegerAttribute(tf->getIntValue());
    }
    else if (info->getAttributeClass(intNumber)
	     ->isSubtypeOf(IlvDoubleAttribute::ClassInfo())) {
	attributeToUpdate = new IlvDoubleAttribute((IlDouble)
						   tf->getFloatValue());
    }
    else {
	attributeToUpdate = new IlvStringAttribute(tf->getLabel());
    }
    const char* key = 0;
    IlvFeatureAttribute* keyAttribute = 0;
    IlUInt count = attrpan->getCardinal() / 2;
    IlvToggle* tog = 0;
    IlUInt i = 0;
    for (i = 0; i < count; i++) {
	IlString toggleName = IlString("label");
	toggleName += IlString(i);
	tog = (IlvToggle*)attrpan->getObject(toggleName.getValue());
	if (tog->getState()) {
	    break;
	}
	else {
	    tog = 0;
	}
    }
    if (!tog) {
	sdopanel->reportDBError("Must select a KEY attribute");
	delete attributeToUpdate;
	return;
    }
    key = tog->getLabel();
    IlvTextField* keyTf =
	(IlvTextField*)attrpan->getObject((IlString("value")
					   + IlString(i)).getValue());
    if (info->getAttributeClass(i)
	->isSubtypeOf(IlvIntegerAttribute::ClassInfo())) {
	keyAttribute = new IlvIntegerAttribute(keyTf->getIntValue());
    }
    else if (info->getAttributeClass(i)
	     ->isSubtypeOf(IlvDoubleAttribute::ClassInfo())) {
	keyAttribute = new IlvDoubleAttribute((IlDouble)keyTf
					      ->getFloatValue());
    }
    else {
	keyAttribute = new IlvStringAttribute(keyTf->getLabel());
    }
    // Use an IlvObjectSDOWriter in order to update the attribute.
    IlvObjectSDOWriter* objWriter =
    	new IlvObjectSDOWriter(sdopanel->getDbms(),
			       sdopanel->getLayerName(),
			       sdopanel->getGeometryName(),
			       "X", "Y");
    objWriter->setCheckingStringAttributes(IlTrue);
    // In order to update a feature attribute, you have to give a key
    // column name and the it's value that identifies the row in he DB
    // to be updated.
    //
    // Checking if the row is unique:
    IlString checkQuery =
	IlString("select count(*) from ") +  sdopanel->getLayerName()
        + IlString(" where ") + IlString(key) + IlString(" = '")
        + IlString(keyTf->getLabel()) + IlString("'");
    IldRequest* req = sdopanel->executeQuery(checkQuery.getValue(), 1);
    req->fetch();
    IlUInt nbRows = req->getColIntegerValue(0);
    if (nbRows > 1) {
	IlString message("The key value corresponds to ");
	message += IlString(nbRows);
	message += IlString(" rows.\nWould you like to update them all?");
	IlvIQuestionDialog dialog(sdopanel->getDisplay(),
				  message.getValue());
	dialog.moveToMouse();
	IlBoolean ok = dialog.get();
	if (!ok) {
	    delete objWriter;
	    delete keyAttribute;
	    delete attributeToUpdate;
	    return;
	}
    }
    IlvMapsError error =
	objWriter->updateFeatureAttribute(
	    			key,
				(const IlvFeatureAttribute*)keyAttribute,
				name,
				(const IlvFeatureAttribute*)attributeToUpdate);
    delete keyAttribute;
    delete attributeToUpdate;
    // You can commit the updated data at any time but don't forget to do it!
    if (error == IlvMaps::NoError()) {
	sdopanel->getDbms()->commit();
    }
    else {
	sdopanel->reportDBError(IlvMaps::GetErrorMessage(error,
						sdopanel->getDisplay()));
    }
    delete objWriter;
}

// --------------------------------------------------------------------------
// Just hides the container.
// --------------------------------------------------------------------------
static void
CancelCB(IlvGraphic* g, IlvAny a)
{
    IlvGadgetContainer* cont = (IlvGadgetContainer*)a;
    cont->hide();
}

// --------------------------------------------------------------------------
static void
CancelWhichLayerCB(IlvGraphic* g, IlvAny a)
{
    MySdopan* sdopan = (MySdopan*)a;
    sdopan->setLayerName(0);
    sdopan->getWhichLayerPanel()->hide();
}

// --------------------------------------------------------------------------
// Hides the tiling level panel
// --------------------------------------------------------------------------
static void
CancelTilingCB(IlvGraphic* g, IlvAny a)
{
    MySdopan* sdopan = (MySdopan*)a;
    sdopan->setTilingLevel(0);
    sdopan->getTilingPanel()->hide();
}

// --------------------------------------------------------------------------
static void
DropItCB(IlvGraphic* g, IlvAny a)
{
    MySdopan* sdopan = (MySdopan*)a;
    IldDbms* dbms = sdopan->getDbms();
    if (!sdopan->checkDbms())
	return;
    IlvContainer* cont = sdopan->getWhichLayerPanel();
    IlvComboBox* layers = (IlvComboBox*)cont->getObject("layers");
    const char* sel = sdopan->getLayerName();
    if (sel && sel[0] && layers->getSelection()) {
	// ask for confirmation
	IlString tmp = IlString("Do you want to delete the ") +
	               IlString(sel) + IlString(" SDO Layer?");
	IlvIQuestionDialog question(sdopan->getDisplay(),
				    tmp,
				    0,
				    IlvDialogOkCancel,
				    cont->getSystemView());
	question.moveToView(cont);
	IlBoolean ok = question.get();
	if (ok) {
	    sdopan->waitCursor();
	    // Drop the layer
	    IlvMapsError status;
	    IlvObjectSDOUtil::DropLayer(dbms, sel, status);
	    sdopan->computeCB(layers);
	    sdopan->defaultCursor();
	    IlString tmp("Layer " + IlString(sdopan->getLayerName())
			 + " dropped.\n");
	    sdopan->reportInfo(tmp.getValue());
	}
    }
}

// --------------------------------------------------------------------------
static void
ComputeItCB(IlvGraphic* g, IlvAny a)
{
    MySdopan* sdopan = (MySdopan*)a;
    sdopan->computeCB(sdopan->getWhichLayerPanel()->getObject("layers"));
}

// --------------------------------------------------------------------------
static void
UseExtentOfCB(IlvGraphic* g, IlvAny a)
{
    MySdopan* pan = (MySdopan*)a;
    pan->setUseExtentOf(!pan->isUseExtentOf());
}

// --------------------------------------------------------------------------
IlString
GetTableName(IlString& layerName)
{
    IlInt dotPosition = layerName.getLastIndexOf(IlString("."));
    if (dotPosition < 1) {
	return IlString();
    }
    return layerName.getSubString(0, dotPosition);
}

// --------------------------------------------------------------------------
IlString
GetGeometryName(IlString& layerName)
{
    IlInt dotPosition = layerName.getLastIndexOf(IlString("."));
    if (dotPosition < 0) {
	return layerName;
    }
    return layerName.getSubString(dotPosition + 1);
}

// --------------------------------------------------------------------------
// Sets the layer name of the MySdopan
// --------------------------------------------------------------------------
static void
WhichLayerCB(IlvGraphic* g, IlvAny a)
{
    MySdopan* sdopan = (MySdopan*)a;
    IlvGadgetContainer* cont = sdopan->getWhichLayerPanel();
    IlvComboBox* layers = (IlvComboBox*)cont->getObject("layers");
    if (!strcmp(g->getName(), "cancel")) {
	sdopan->setLayerName(0);
	cont->hide();
	return;
    }
    const char* sel = layers->getSelection();
    if (!sel || !sel[0]) {
	return;
    }
    if (sdopan->_isDropping) {
	sdopan->setLayerName(IlString(sel));
    }
    else {
	IlString ils(sel);
	sdopan->setLayerName(GetTableName(ils));
	sdopan->setGeometryColumnName(GetGeometryName(ils));
    }
    IlBoolean visible = cont->getObject("labelwidth")->isVisible();
    if (!visible) {
	IlBoolean err;
        IlDouble tileWidth =
	    (IlDouble) ((IlvNumberField*)cont->getObject("tileWidth"))
	->getFloatValue(err);
	IlDouble tileHeight =
	    (IlDouble) ((IlvNumberField*)cont->getObject("tileHeight"))->getFloatValue(err);
	if (tileWidth <= 0.0 || tileHeight <= 0.0 || err) {
	    IlvIErrorDialog er(cont->getDisplay(),
		"Tile width and Tile height should be greater than 0");
	    er.moveToMouse();
	    er.get();
	    return;
	}
    }
    cont->hide();
}

// --------------------------------------------------------------------------
// Sets the col array size of the MySdopan
// --------------------------------------------------------------------------
static void
ColArrayCB(IlvGraphic* g, IlvAny a)
{
    MySdopan* sdopan = (MySdopan*)a;
    IlvGadgetContainer* cont = sdopan->getColArrayPanel();
    IlvNumberField* tf = (IlvNumberField*)cont->getObject("tilingLevel");
    IlBoolean err;
    IlInt colarray = tf->getIntValue(err);
    if (!err) {
	sdopan->setColArraySize(colarray);
    }
    cont->hide();
}

// --------------------------------------------------------------------------
// Sets the tiling level of the MySdopan
// --------------------------------------------------------------------------
static void
TilingCB(IlvGraphic* g, IlvAny a)
{
    MySdopan* sdopan = (MySdopan*)a;
    IlvGadgetContainer* cont = sdopan->getTilingPanel();
    IlvNumberField* tf = (IlvNumberField*)cont->getObject("tilingLevel");
    IlBoolean err;
    IlInt tilingLevel = tf->getIntValue(err);
    if (!err) {
	sdopan->setTilingLevel(tilingLevel);
    }
    cont->hide();
}

// --------------------------------------------------------------------------
// Creates an new SDO Layer
// --------------------------------------------------------------------------
static void
NewlayerCB(IlvGraphic* g, IlvAny a)
{
    MySdopan* sdopan = (MySdopan*)a;
    IlvGadgetContainer* cont = sdopan->getNewLayerPanel();
    IlvTextField* tf = (IlvTextField*)cont->getObject("layer");
    const char* layerName = tf->getLabel();
    IlString tmp(layerName);
    if (tmp.isEmpty()) {
	return;
    }
    const char* fileName = sdopan->getFileName();
    // default boundaries: not used in object model
    sdopan->setLayerUpperLeftCorner(IlvCoordinate(-360, 90));
    sdopan->setLayerLowerRightCorner(IlvCoordinate(360, -90));
    sdopan->waitCursor();
    IlvCoordinate* ul = 0;
    IlvCoordinate* lr = 0;
    IlvCoordinate ulRef, lrRef;
    IlvObjectSDOWriter* writer = 0;
    IlvMapFeatureIterator* reader = sdopan->_reader;
    if (reader &&
	reader->getUpperLeftCorner(ulRef) &&
	reader->getLowerRightCorner(lrRef)) {
	ul = &ulRef;
	lr = &lrRef;
	writer = new IlvObjectSDOWriter(sdopan->getDbms(),
					layerName,
					"GEOMETRY",
					"X",
					"Y",
					IlTrue,
					(const IlvFeatureAttributeInfo*)
					sdopan->_info, // this parameter
					// will allow the creation of the corresponding
					// columns if there is any IlvFeatureAttributeInfo
					// attached.
					ul,
					lr);
	// Allways test the init status of a reader/writer after instanciation.
	IlvMapsError error = IlvMaps::NoError();
	if (writer->getInitStatus() == IlvMaps::NoError()) {
	    error = writer->close(); // will update the SDO_GEOM_METATA table.
	}
	IlString tmp2;
	if (writer->getInitStatus() == IlvMaps::NoError() &&
	    error == IlvMaps::NoError()) {
	    tmp2 = IlString(layerName) + IlString(" layer created.\n");
	}
	else {
	    tmp2 = IlString(IlString(layerName)
			    +  IlString(" layer creation failed.\n"));
	}
	sdopan->reportInfo(tmp2.getValue());
	delete writer;
    }
    cont->hide();
    sdopan->defaultCursor();
    sdopan->reportTraces();
}

// --------------------------------------------------------------------------
// Error Reporter class for dblink
// If an error occurs, it will be raised in the reportError method of
// MySdopan
// --------------------------------------------------------------------------
class SDOErrorReporter
    : public IldErrorReporter
{
public:
    SDOErrorReporter(MySdopan* panel)
	: IldErrorReporter(),
	  _panel(panel)
	{}

    void dbmsError(IlInt funcCode,
		   const char* funcName,
		   const char* message,
		   IldDbms* dbms,
		   IldRequest* request = 0,
		   const char* query = 0) const
    {
	IldErrorReporter::dbmsError(funcCode, funcName, message,
				    dbms, request, query);
	_panel->reportDBError(message);
    }

    void dblinkError(IlInt funcCode,
		     const char* funcName,
		     const char* message,
		     IldDbms* dbms,
		     IldRequest* request = 0,
		     const char* query = 0,
		     IlInt index = 0,
		     const IldRelation* rel = 0) const
    {
	IldErrorReporter::dblinkError(funcCode, funcName, message,
				      dbms, request, query, index, rel);
	char* tmp = new char[strlen(message) + 2];
	strcpy(tmp, message);
	strcat(tmp, "\n");
	_panel->reportDBError(tmp);
	delete [] tmp;
    }

    void warn(IlInt code,
	      IldFuncId funcId,
	      const char* message,
	      IldDbms* dbms = 0,
	      IldRequest* req = 0) const
    {
	IldErrorReporter::warn(code, funcId, message, dbms, req);
	char* tmp = new char[strlen(message) + 2];
	strcpy(tmp, message);
	strcat(tmp, "\n");
	_panel->reportDBError(tmp);
	delete [] tmp;
    }

private:
    MySdopan* _panel;
};

// --------------------------------------------------------------------------
// a tile listener class for Errors
// --------------------------------------------------------------------------
class MyTileListener
    : public IlvTileListener
{
public:
    MyTileListener(MySdopan* pan)
        : _pan(pan)
    {}

    virtual void beginGroupedNotification(IlvTileController* c) {}
    virtual void endGroupedNotification(IlvTileController* c) {}
    virtual void tileChanged(IlvTile* tile,
			     IlvTileStatus oldStatus,
			     IlvTileStatus newStatus) {}
    virtual void controllerDeleted(IlvTileController*) {}
    // Always, override this method in order to raise the Data Base error
    // that may have occured in an IlvTile load process.
    virtual void loadError(IlvTile* tile, IlvMapsError error)
	{ _pan->reportDBError(IlvMaps::GetErrorMessageId(error)); }

    MySdopan* _pan;
};

// --------------------------------------------------------------------------
// A panel designed for showing the attributes of the map features and for
// allowing their update in the DB.
// --------------------------------------------------------------------------
AttributesPanel::AttributesPanel(MySdopan* pan,
				 IlvFeatureAttributeProperty* ap)
    : IlvGadgetContainer(pan->getDisplay(),
			 "Attributes",
			 "Attributes",
			 IlvRect(0, 0, 100, 100),
			 IlvNoResizeBorder,
			 IlFalse,
			 IlFalse,
			 pan->getSystemView()),
      _pan(pan),
      _labelBBox()
{
    init(pan, ap);
    moveToMouse(IlvTopLeft, (IlvPos)10);
}

// --------------------------------------------------------------------------
void
AttributesPanel::init(MySdopan* pan, IlvFeatureAttributeProperty* ap)
{
    const IlvFeatureAttributeInfo* info = ap->getInfo();
    // Building the toggle's labels nad the text field's ones.
    IlUInt count = 0;
    if (info) {
        count = info->getAttributesCount();
	for (IlUInt i = 0; i < count; i++) {
	    IlString label, value;
	    label = IlString(info->getAttributeName(i));
	    const IlvMapClassInfo* clsinfo = info->getAttributeClass(i);
	    const IlvFeatureAttribute* fa = ap->getAttribute(i);
	    if (!fa) {
		continue;
	    }
	    if (clsinfo->isSubtypeOf(IlvStringAttribute::ClassInfo())) {
		value = IlString(((IlvStringAttribute*)fa)->getValue());
	    }
	    else if (clsinfo->isSubtypeOf(IlvIntegerAttribute::ClassInfo())){
		value = IlString(((IlvIntegerAttribute*)fa)->getValue());
	    }
	    else if (clsinfo->isSubtypeOf(IlvDoubleAttribute::ClassInfo())) {
		value = IlString(((IlvDoubleAttribute*)fa)->getValue());
	    }
	    else if (clsinfo->isSubtypeOf(IlvBooleanAttribute::ClassInfo())){
		value =IlString((int)((IlvBooleanAttribute*)fa)->getValue());
	    }
	    addAttribute(label, value);
	}
    }
    fitToContents();
    IlvRect bbox;
    boundingBox(bbox);
    // adding a close button allowing to hide the container
    IlvButton* close = new IlvButton(getDisplay(),
				     "Close",
				     IlvRect(bbox.x(),
					     bbox.y() + bbox.h() + 5,
					     bbox.w(), 20));
    addObject(close);
    close->setCallback(CloseAttributePanelCB, this);
    fitToContents();
}

// --------------------------------------------------------------------------
// Adding the toggles and text fields. If you want to update a field, click
// on a toggle which represents a KEY in the SDO layer and then choose a text
// field, change it's value and then press return.
// --------------------------------------------------------------------------
void
AttributesPanel::addAttribute(IlString& name, IlString& value)
{
    IlUInt count = getCardinal();
    IlvPos y = (IlvPos)(11 * count);
    IlvToggle* label = new IlvToggle(getDisplay(), IlvPoint(0, y),
				     name.getValue());
    label->setPosition(IlvRight);
    IlvRect bbox;
    label->boundingBox(bbox);
    if (bbox.w() > _labelBBox.w()) {
	_labelBBox = bbox;
    }
    IlvTextField* tf = new IlvTextField(getDisplay(),
					IlvPoint(_labelBBox.w() + 6, y),
					value.getValue());
    tf->boundingBox(bbox);
    tf->moveResize(IlvRect(bbox.x(), bbox.y() - 1, 150, bbox.h() + 2));
    label->setName((IlString("label") + IlString(count/2)).getValue());
    tf->setName((IlString("value") + IlString(count/2)).getValue());
    tf->setCallback(UpdateCB, this);
    label->setCallback(DeselectCB, this);
    addObject(label);
    addObject(tf);
    const char* ttipText = "If you want to update a field in the DataBase,\n"
	"click on a toggle which represents a KEY in the\n"
	"SDO layer and then choose a text field, change \n"
	"it's value and then press return.";
    label->setNamedProperty(new IlvToolTip(ttipText));
    tf->setNamedProperty(new IlvToolTip(ttipText));
}

// --------------------------------------------------------------------------
// A select interactor allowing to pop the attributes' panel on a graphic
// selection.
// --------------------------------------------------------------------------
MySelectInteractor::MySelectInteractor(IlvManager* manager, MySdopan* pan)
  : IlvSelectInteractor(manager, pan->getscm()->getView()),
    _pan(pan),
    _attrPan(0)
{
}

// --------------------------------------------------------------------------
void
MySelectInteractor::doSelect()
{
    IlUInt nb = 0;
    IlvGraphic* const* graphics = getManager()->getSelections(nb);
    if (nb != 1) {
	delete _attrPan;
	_attrPan = 0;
	return;
    }
    IlvGraphic* gr = graphics[0];
    IlvFeatureAttributeProperty* ap = (IlvFeatureAttributeProperty*)
    	gr->getNamedProperty(IlvFeatureAttributeProperty::GetName());
    if (!ap) {
	return;
    }
    if (!_attrPan) {
	_attrPan = new AttributesPanel(_pan, ap);
	_attrPan->setDestroyCallback(DestroyCB);
    }
    else {
	_attrPan->removeObjects();
	_attrPan->init(_pan, ap);
	_attrPan->reDraw();
    }
    _attrPan->show();
}

// --------------------------------------------------------------------------
// MySdopan
// --------------------------------------------------------------------------

IlvTileCache* MySdopan::_Cache = new IlvDefaultTileCache(36);

// --------------------------------------------------------------------------
// Constructors
// --------------------------------------------------------------------------
MySdopan::MySdopan(IlvDisplay* display,
		   const char* name,
		   const char* title,
		   IlvRect*    size,
		   IlBoolean   useAccelerators,
		   IlBoolean   visible,
		   IlUInt      properties,
		   IlvSystemView transientFor)
    : Sdopan(display,
	     name,
	     title,
	     size,
	     useAccelerators,
	     visible,
	     properties,
	     transientFor),
      _reader(0),
      _info(0),
      _dbms(0),
      _userName(0),
      _layerName(0),
      _whichLayerPanel(0),
      _debugView(0),
      _sdoReader(0),
      _mag(0),
      _nbFeatures(0),
      _listener(0),
      _colarraysize(10),
      _useExtentOf(IlFalse)
{
    init();
    initializeFileBrowser();
}

// --------------------------------------------------------------------------
MySdopan::MySdopan(IlvAbstractView* parent,
		   IlvRect* size,
		   IlBoolean useacc,
		   IlBoolean visible)
    : Sdopan(parent,
	     size,
	     useacc,
	     visible),
      _reader(0),
      _info(0),
      _dbms(0),
      _userName(0),
      _layerName(0),
      _whichLayerPanel(0),
      _debugView(0),
      _sdoReader(0),
      _mag(0),
      _nbFeatures(0),
      _listener(0)
{
    init();
    initializeFileBrowser();
}

// --------------------------------------------------------------------------
MySdopan::~MySdopan()
{
    if (_Cache) {
	_Cache->unLock();
    }
    resetCB(0);
    IlvManager* manager = getscm()->getManager();
    manager->deleteAll(IlTrue, IlTrue);
    if (_debugView) {
	manager->removeInteractor(_debugView);
    }
    manager->removeInteractor(manager->getFirstView());
    if (_mapinfo) {
	_mapinfo->detach();
	delete _mapinfo;
    }
    if (_pan) {
	delete _pan;
    }
    if (_select) {
	delete _select;
    }
    if (_zoom) {
	delete _zoom;
    }
    if (_mag) {
	delete _mag;
    }
    // the panels are deleted by the display's destruction
    if (_dbms) {
	delete _dbms;
    }
    if (_dbmsFactory) {
	delete _dbmsFactory;
    }
    if (_info) {
	_info->unLock();
    }
    if (_reader) {
	delete _reader;
    }
    if (_fileBrowserIlv) {
	delete _fileBrowserIlv;
    }
    if (_fileBrowserShp) {
	delete _fileBrowserShp;
    }
}

// --------------------------------------------------------------------------
// Initializes Mysdopan. Creates also the subpanels and their callbacks.
// --------------------------------------------------------------------------
void
MySdopan::init()
{
    _Cache->lock();
    _layerUpperLeftCorner = IlvCoordinate(-360., 90.);
    _layerLowerRightCorner = IlvCoordinate(360., -90.);
    _fileName = IlString();
    // the default Factory can be used in your application if you have
    // the Rogue Wave Views Gadgets library.
    _dbmsFactory = new IlvDefaultSDODbmsFactory();
    IlvSDOUtil::SetDbmsFactory(_dbmsFactory);
    //_oracleRelationalMode = IlFalse;
    // ----------------------------------------------
    // Set here your map adapter that fits your datas
    IlvProjection* proj = new IlvGeographicProjection();
    proj->setShared();
    IlvMapAdapter* adapter = new IlvMapAdapter(proj);
    _mapinfo = new IlvMapInfo(proj, adapter, IlFalse);
    // -----------------------------------------------
    IlvSCManagerRectangle* scm = getscm();
    scm->hideScrollBar(IlvVertical);
    scm->hideScrollBar(IlvHorizontal);
    IlvManager* manager = scm->getManager();
    manager->setKeepingAspectRatio(manager->getFirstView(), IlTrue);
    _mapinfo->attach(manager);
    _whichLayerPanel = new IlvGadgetContainer(getDisplay(),
					      "Choose an SDO layer",
					      "Choose an SDO layer",
					      IlvRect(0,0,10,10), 0,
					      IlFalse, IlFalse,
					      getSystemView());
    _whichLayerPanel->readFile("whichlay.ilv");
    IlvButton* ok = (IlvButton*)_whichLayerPanel->getObject("ok");
    IlvButton* cancel = (IlvButton*)_whichLayerPanel->getObject("cancel");
    IlvButton* recompute = (IlvButton*)
			   _whichLayerPanel->getObject("recompute");
    IlvToggle* useextentof = (IlvToggle*)
			     _whichLayerPanel->getObject("extentof");
    ok->setCallback(WhichLayerCB, this);
    cancel->setCallback(CancelWhichLayerCB, this);
    recompute->setCallback(ComputeItCB, this);
    useextentof->setCallback(UseExtentOfCB, this);
    _whichLayerPanel->setDefaultButton(ok);

    // init the new layer panel
    _newLayerPanel = new IlvGadgetContainer(getDisplay(),
					    "Create SDO Layer",
					    "Create SDO Layer",
					    IlvRect(0, 0, 10, 10), 0,
					    IlFalse, IlFalse,
					    getSystemView());
    _newLayerPanel->readFile("newlayer.ilv");
    ok = (IlvButton*)_newLayerPanel->getObject("ok");
    cancel = (IlvButton*)_newLayerPanel->getObject("cancel");
    cancel->setCallback(CancelCB, _newLayerPanel);
    ok->setCallback(NewlayerCB, this);
    _newLayerPanel->setDefaultButton(ok);
    // init the tiling level panel
    _tilingPanel = new IlvGadgetContainer(getDisplay(),
					  "Create SDO Layer",
					  "Create SDO Layer",
					  IlvRect(0, 0, 10, 10), 0,
					  IlFalse, IlFalse,
					  getSystemView());
    _tilingPanel->readFile("tiling.ilv");
    ok = (IlvButton*)_tilingPanel->getObject("ok");
    cancel = (IlvButton*)_tilingPanel->getObject("cancel");
    cancel->setCallback(CancelTilingCB, this);
    ok->setCallback(TilingCB, this);
    _tilingPanel->setDefaultButton(ok);
    // init the col array size panel

    _colarrayPanel = new IlvGadgetContainer(getDisplay(),
					    "Setting DataBase options",
					    "Setting DataBase options",
					    IlvRect(0,0,10,10), 0,
					    IlFalse, IlFalse,
					    getSystemView());
    _colarrayPanel->readFile("tiling.ilv");
    ok = (IlvButton*)_colarrayPanel->getObject("ok");
    cancel = (IlvButton*)_colarrayPanel->getObject("cancel");
    cancel->setCallback(CancelCB, _colarrayPanel);
    ok->setCallback(ColArrayCB, this);
    _colarrayPanel->setDefaultButton(ok);
    // init the interactors;
    _pan = new IlvPanZoomInteractor(manager, manager->getFirstView());
    _pan->setOpaqueMove(IlFalse);
    _select = new MySelectInteractor(manager, this);
    _zoom = new IlvZoomInteractor(manager, manager->getFirstView());
    _isDropping = IlFalse;
}

// --------------------------------------------------------------------------
void
MySdopan::initializeFileBrowser()
{
    const char* const filters[1] = { "*.ilv" };
    const char* const messages[1] = { "*.ilv, Ilv files" };

    _fileBrowserIlv = new IlvFileBrowser(getDisplay(),this->getSystemView(),
					 "../",1,filters,messages);

    const char* const filters2[1] = { "*.shp" };
    const char* const messages2[1] = { "*.shp, Shapefile files" };

    _fileBrowserShp = new IlvFileBrowser(getDisplay(),this->getSystemView(),
					 "../",1,filters2,messages2);
}

// --------------------------------------------------------------------------
// sets the wait cursor on the main panel
// --------------------------------------------------------------------------
void
MySdopan::waitCursor()
{
    IlvDisplay* display = getDisplay();
    setCursor(display->getCursor("wait"));
    display->sync();
}

// --------------------------------------------------------------------------
// sets the default cursor on the main panel
// --------------------------------------------------------------------------
void
MySdopan::defaultCursor()
{
    IlvDisplay* display = getDisplay();
    setCursor(display->getCursor("default"));
    display->sync();
}

// --------------------------------------------------------------------------
void
MySdopan::setDbms(IldDbms* dbms)
{
    if (_dbms) {
	delete _dbms;
    }
    _dbms = dbms;
}

// --------------------------------------------------------------------------
// Checks whether the dbms is created or not
// --------------------------------------------------------------------------
IlBoolean
MySdopan::checkDbms()
{
    if (!_dbms) {
	connectCB(0);
    }
    if (!_dbms) {
	return IlFalse;
    }
    return IlTrue;
}

// --------------------------------------------------------------------------
// Initializes the gauge to 0%
// --------------------------------------------------------------------------
void
MySdopan::initGauge(IlvFloat max)
{
    IlvMessageLabel* percent = (IlvMessageLabel*)getObject("percent");
    IlvGauge* gauge =
	(IlvReliefGauge*)gettoolbar()->getItem(gettoolbar()
					       ->getCardinal() - 1)
				     ->getGraphic();
    gauge->setMax(max);
    percent->setLabel("0 %");
}

// --------------------------------------------------------------------------
// Updates the gauge with the value argument
// --------------------------------------------------------------------------
void
MySdopan::updateGauge(IlvFloat value)
{
    IlvMessageLabel* percent = (IlvMessageLabel*)getObject("percent");
    IlvGauge* gauge =
	(IlvReliefGauge*)gettoolbar()->getItem(gettoolbar()
					       ->getCardinal() - 1)
				     ->getGraphic();
    if ((IlInt)value % 50 == 0) { // Update every 50 rows
      gauge->setValue(value);
      IlString tmp((IlInt)(100 * value / gauge->getMax()));
      tmp += IlString(" %");
      percent->setLabel(tmp.getValue());
      percent->reDraw();
      gauge->reDraw();
    }
    if (value >= gauge->getMax() - 1) {
      gauge->setValue(gauge->getMax());
      percent->setLabel("100 %");
      percent->reDraw();
      gauge->reDraw();
    }
}

// --------------------------------------------------------------------------
/// Reports an error thanks to IlvWarning

// --------------------------------------------------------------------------
void
MySdopan::reportError(const char* text)
{
    IlString txt;
    if (text && text[0]) {
	txt += IlString(text);
	txt += IlString("\n");
    }
    IlvWarning(txt.getValue());
}

// --------------------------------------------------------------------------
void
MySdopan::reportDBError(const char* text)
{
    IlString txt;
    if (text && text[0]) {
	txt += IlString(text);
	txt += IlString("\n");
    }
    IlvWarning(txt.getValue());
    if (IlvSDOUtil::GetLastDbErrorCode() != 0) {
	IlvWarning(IlvSDOUtil::GetLastDbErrorMessage());
    }
}

// --------------------------------------------------------------------------
// Reports an information thanks to IlvPrint
// --------------------------------------------------------------------------
void
MySdopan::reportInfo(const char* text)
{
    IlvPrint("%s\n", text);
}

// --------------------------------------------------------------------------
// Reports the traces that may have been produced by SDO classes calls.
// If the you have enabled the SQL traces thanks to IlvSDOUtil, allways call
// this method after each SDO method call in order to see the produced
// traces.
// --------------------------------------------------------------------------
void
MySdopan::reportTraces()
{
    if (IlvSDOUtil::SQLTracesEnabled()) {
	// Extract the traces from the stream that has been set in the
	// IlvSDOUtil.
	const char* traces = IlvGetStringFrom(_stream);
	IlvPrint("%s\n", traces);
	_stream.seekp(0);
    }
}

// --------------------------------------------------------------------------
// Useful method in SDO relational model that returns a GID value that is
// usable for futur geometries to be written into the Data Base.
// --------------------------------------------------------------------------
IlInt
MySdopan::getAvailableGid(const char* sdoLayerName)
{
    // Extract the greater SDO_GID from the DB
    IldRequest* result =
	executeQuery(IlString("select SDO_GID from ")
		     + IlString(sdoLayerName) +
		     IlString("_SDOGEOM ORDER BY 1 DESC"), 1);
    result->fetch();
    if (result->hasTuple()) {
	IlInt gid = result->getColIntegerValue(0);
	result->release();
	return (IlInt)(gid + 1);
    }
    else {
	return 0;
    }
}

// --------------------------------------------------------------------------
void
MySdopan::whichLayer()
{
    IlvComboBox* layers = (IlvComboBox*)_whichLayerPanel
				        ->getObject("layers");
    layers->setLabel("");
    computeCB(layers);
    _whichLayerPanel->moveToView(this);
    _whichLayerPanel->showModal();
}

// --------------------------------------------------------------------------
// Executes the query passed as argument and returns the resulting
// IldRequest.
// The colArraySize parameter is a dblink parameter which allows to fetch
// into memory 'colArraySize' rows at time.
// --------------------------------------------------------------------------
IldRequest*
MySdopan::executeQuery(const char* query, IlUShort colArraySize)
{
    if (!_dbms) {
        reportDBError("No Dbms available!");
        return 0;
    }
    if (!query || !query[0]) {
        reportDBError("No query available!");
        return 0;
    }
    if (IlvSDOUtil::SQLTracesEnabled()) {
	reportInfo(query);
    }
    IldRequest* req = _dbms->getFreeRequest();
    if (req) {
	req->setColArraySize(colArraySize);
	req->execute(query);
    }
    return req;
}

// --------------------------------------------------------------------------
// The writer passed as 2nd argument writes the IlvMapFeatureIterator passed
// as 1st argument.
// This method does the same thing that IlvSDOWriter::writeFeatureIterator
// and updates the gauge.
// --------------------------------------------------------------------------
IlInt
MySdopan::writeFeatureIterator(IlvMapFeatureIterator* reader,
			       IlvSDOWriter* writer)
{
    IlInt i = 0;
    if (!reader) {
	return 0;
    }
    IlvMapsError status = IlvMaps::NoError();
    const IlvMapFeature* feature = reader->getNextFeature(status);
    while (feature) {
	status = writer->writeFeature(feature);
	if (status  != IlvMaps::NoError()) {
	    reportDBError(IlvMaps::GetErrorMessage(status, getDisplay()));
	}
	if (IlvSDOUtil::SQLTracesEnabled() && status != IlvMaps::NoError()) {
	    reportTraces();
	}
	i++;
	feature = reader->getNextFeature(status);
	updateGauge((IlvFloat)i);
	if (status != IlvMaps::NoError()) {
	    reportDBError(IlvMaps::GetErrorMessage(status, getDisplay()));
	}
	if (IlvSDOUtil::SQLTracesEnabled() && status != IlvMaps::NoError()) {
	    reportTraces();
	}
    }
    getDbms()->commit();
    return i;
}

// --------------------------------------------------------------------------
// The writer passed as 2nd argument writes the IlvMapFeatureIterator passed
// as 1st argument.
// This method does the same thing that IlvSDOWriter::writeFeatureIterator
// and updates the gauge.
// --------------------------------------------------------------------------
IlInt
MySdopan::writeFeatureIterator(IlvMapFeatureIterator* reader,
			       IlvObjectSDOWriter* writer)
{
    IlInt i = 0;
    if (!reader) {
	return 0;
    }
    writer->setCheckingStringAttributes(IlTrue);
    IlvMapsError status = IlvMaps::NoError();
    const IlvMapFeature* feature = reader->getNextFeature(status);
    IlBoolean saveAttributes = IlFalse;
    if (feature && feature->getAttributeInfo()) {
	IlvIQuestionDialog question(getDisplay(),
				    "Do you want to save "
				    "the attributes of the map features?");
	question.setTitle("Save attributes ?");
	question.moveToView(this);
	IlBoolean ok = question.get();
	if (ok) {
	    saveAttributes = IlTrue;
	}
        else {
	    saveAttributes = IlFalse;
	}
    }
    while (feature) {
	status = writer->writeFeature(feature, saveAttributes);
	if (status != IlvMaps::NoError()) {
	    reportDBError(IlvMaps::GetErrorMessage(status, getDisplay()));
	}
	if (IlvSDOUtil::SQLTracesEnabled() && status != IlvMaps::NoError()) {
	    reportTraces();
	}
	i++;
	feature = reader->getNextFeature(status);
	updateGauge((IlvFloat)i);
	if (status != IlvMaps::NoError()) {
	    reportDBError(IlvMaps::GetErrorMessage(status, getDisplay()));
	}
	if (IlvSDOUtil::SQLTracesEnabled() && status != IlvMaps::NoError()) {
	    reportTraces();
	}
    }
    getDbms()->commit();
    writer->close();
    return i;
}

// --------------------------------------------------------------------------
// Creates the Load On Demand layer and starts it.
// --------------------------------------------------------------------------
void
MySdopan::lodCB(IlvGraphic* g)
{
    if (!checkDbms()) {
	return;
    }
    resetCB(0);
    IlvManager* manager = getscm()->getManager();
    IlvSetContentsChangedUpdate(IlFalse);
    IlvSDOLayer* layer = 0;
    SetVisibleFieldsLayer(_whichLayerPanel,IlTrue);
    whichLayer();
    if (!_layerName || !_layerName[0]) {
	return;
    }
    // Creating the Load On Demand layer.
    const char* keyColName =
	((IlvTextField*)_whichLayerPanel->getObject("id"))->getLabel();
    IlBoolean err;
    IlDouble tileWidth =
	(IlDouble)((IlvNumberField*)_whichLayerPanel
			       ->getObject("tileWidth"))->getFloatValue(err);
    IlDouble tileHeight =
	(IlDouble)((IlvNumberField*)_whichLayerPanel
			      ->getObject("tileHeight"))->getFloatValue(err);
    IlvCoordinate ul, lr;
    IlvMapsError status = IlvMaps::NoError();
    IlvObjectSDOUtil::GetLayerExtent(_dbms, _layerName, getGeometryName(),
				     0, 0, _useExtentOf, ul, lr, status);
    if (status != IlvMaps::NoError()) {
	reportDBError(IlvMaps::GetErrorMessageId(status));
    }
    IlvDefaultObjectSDOTileLoader* tileloader =
	new IlvDefaultObjectSDOTileLoader(IlvMapInfo::Get(manager)
							       ->getAdapter(),
					  _dbms, _layerName, 0,
					  tileWidth, tileHeight, 0, 0,
					  (keyColName && keyColName[0])
					  ? keyColName : 0,
					  &ul, &lr);
    tileloader->setRequestParameters(0, 0, 0, 0, 0, _colarraysize);
    layer = new IlvObjectSDOLayer(tileloader, _Cache);
    ((IlvObjectSDOLayer*)layer)->setAttachingAttributes(IlTrue);
    ((IlvDefaultObjectSDOTileLoader*)layer->getTileLoader())
						->setClippingRequest(IlTrue);
    IlvMapsError initError = layer->getInitStatus();
    // Allways check the init status after instanciation
    if (initError != IlvMaps::NoError()) {
	reportDBError(IlvMaps::GetErrorMessageId(initError));
    }
    manager->addLayer(layer);
    fitToTile(layer);
    _listener = new MyTileListener(this);
    layer->getTileController()->addTileListener(_listener);
    initDebugView(layer);
    // Fitting to the center of the LOD grid
    initMagView();
    _debugView->resize(301, 301);

    // start the layer at the end of all initializations
    layer->start();
    manager->reDraw();
    reportTraces();
}

// --------------------------------------------------------------------------
// Pops the connection dialog
// --------------------------------------------------------------------------
void
MySdopan::connectCB(IlvGraphic* g)
{
    IlvSDOUtil::EnableDbLink();
    if (_dbms) {
	setDbms(0);
    }
    // This will pop the default Connection factory delivered with the sample
    IlvMapsError error = IlvMaps::NoError();
    _dbms = IlvSDOUtil::GetDbmsFactory()->makeDbms(getDisplay(),
						   0, 0, 0, 0, error);
    reportTraces();
    if (error != IlvMaps::NoError() && _dbms) {
        reportDBError(IlvMaps::GetErrorMessageId(error));
        setDbms(0);
    }
    else if (_dbms) {
	setUserName(_dbms->getUser());
	if (getDbms()->isConnected()) {
	    // Allways use Error Reporters with DbLink Objects.
	    getDbms()->setErrorReporter(new SDOErrorReporter(this));
	    IlvMapsError status;
	    if (IlvSDOUtil::CheckSdoExistence(getDbms(), status)) {
		reportInfo("Found SDO Package.\n");
	    }
	    else {
		reportDBError("No SDO Package found. Can't continue...");
		setDbms(0);
	    }
	}
    }
}

// --------------------------------------------------------------------------
void
MySdopan::selectCB(IlvGraphic* g)
{
    IlvManager* manager = getscm()->getManager();
    manager->setInteractor(_select, manager->getFirstView());
    reportTraces();
    IlvToolBar* tb = gettoolbar();
    IlvMenuItem* item = tb->getItem(0);
    item->deSelect();
    item = tb->getItem(2);
    item->deSelect();
}

// --------------------------------------------------------------------------
// Computes the names of all the available SDO layers
// --------------------------------------------------------------------------
void
MySdopan::computeCB(IlvGraphic* g)
{
    IlvComboBox* layers = (IlvComboBox*)g;
    IlUShort count;
    waitCursor();
    IlvMapsError status;
    char** layerNames = 0;
    // getting all the layers' names
    layerNames = IlvObjectSDOUtil::GetAllLayers(count, _dbms, _userName,
						!_isDropping, status);
    // setting them in the combo box
    layers->setLabels((const char* const*)layerNames, count);
    if (layerNames) {
	for (IlInt i = 0; i < count; i++) {
	    delete [] layerNames[i];
	}
	delete [] layerNames;
    }
    defaultCursor();
    reportTraces();
}

// --------------------------------------------------------------------------
// The callback for layer dropping
// --------------------------------------------------------------------------
void
MySdopan::eraseCB(IlvGraphic* g)
{
    if (!checkDbms()) {
	return;
    }
    _isDropping = IlTrue;
    SetVisibleFieldsLayer(_whichLayerPanel,IlFalse);
    whichLayer();
    DropItCB(0, this);
    reportTraces();
    _isDropping = IlFalse;
}

// --------------------------------------------------------------------------
// Writes the map file read previously into the Data Base.
// The map file should contain vector data (handlable by Oracle SDO).
// --------------------------------------------------------------------------
void
MySdopan::dbSaveCB(IlvGraphic* g)
{
    if (!checkDbms()) {
	return;
    }
    SetVisibleFieldsLayer(_whichLayerPanel,IlFalse);
    whichLayer();
    if (_layerName.isEmpty() || _fileName.isEmpty()) {
	return;
    }
    IlString tmp(IlString("Do you want to save the '") + _fileName
		 + IlString("' file in the '") + _layerName
		 + IlString("' SDO Layer?"));
    IlvIQuestionDialog question(getDisplay(), tmp.getValue());
    question.moveToView(this);
    if (!question.get()) {
	return;
    }
    IlvManager* manager = getscm()->getManager();
    IlvRunTimeType time1 = IlvRunTime();
    waitCursor();
    IlvSDOWriter* sdoWriter = 0;
    IlvObjectSDOWriter* objWriter = 0;
    IlvCoordinate* ul = 0;
    IlvCoordinate* lr = 0;
    IlvCoordinate ulRef, lrRef;
    if (_reader &&
	_reader->getUpperLeftCorner(ulRef) &&
	_reader->getLowerRightCorner(lrRef)) {
	ul = &ulRef;
	lr = &lrRef;
	// 5% margin
	ul->x(ul->x() - ul->x() * .05);
	ul->y(ul->y() + ul->y() * .05);
	lr->x(lr->x() + lr->x() * .05);
	lr->y(lr->y() - lr->y() * .05);
    }
    objWriter = new IlvObjectSDOWriter(_dbms, _layerName, "GEOMETRY", "X",
				       "Y", IlFalse, 0, ul, lr);
    objWriter->setCheckingStringAttributes(IlTrue);
    objWriter->setUsingOrderedRings(IlTrue);
    IlvMapsError initError = objWriter->getInitStatus();
    if (initError != IlvMaps::NoError())
	reportDBError(IlvMaps::GetErrorMessageId(initError));
    IlvMapLoader loader(manager);
    if (_reader) {
	delete _reader;
	_reader = 0;
    }
    _reader = loader.makeFeatureIterator(_fileName.getValue());
    initGauge((IlvFloat) _nbFeatures);
    IlInt count = writeFeatureIterator(_reader, objWriter);
    IlString tmp2(IlString("Wrote ") + IlString(count)
		  + IlString(" features in the ") +
		  IlString(_layerName) + IlString(" SDO Layer in ") +
		  IlString(IlvRunTime() - time1) + IlString(" seconds.\n"));
    reportInfo(tmp2.getValue());
    IlvMapsError status;
    // Finally, terminating the save process by creating the spatial indexes.
    IlInt tilingLevel = IlvSDOUtil::EstimateTilingLevel(_dbms,
							_layerName,
						  IlvSDOUtil::ALL_GID_EXTENT,
							10000,
							status);
    IlString label(IlString("Enter the tiling level for the ") +
		   IlString(_layerName) +
		   IlString(" layer (0 => R-Tree index): "));
    ((IlvMessageLabel*)_tilingPanel->getObject("label"))
						->setLabel(label.getValue());
    IlvNumberField* nf = (IlvNumberField*)_tilingPanel
						  ->getObject("tilingLevel");
    nf->setLabel(IlString(tilingLevel).getValue());
    _tilingPanel->moveToView(this);
    _tilingPanel->showModal();
    IlvMapsError indexError;
    IlString lname(_layerName);
    indexError = objWriter->populateIndexes((IlUShort)_tilingLevel,
					    0,
					    (lname + IlString("_INDEX"))
								 .getValue(),
					    _layerName);
    if (indexError != IlvMaps::NoError()) {
	reportDBError(IlvMaps::GetErrorMessage(indexError, getDisplay()));
	if (indexError == IlvSDOUtil::DbLinkError()) {
	    reportDBError(IlvSDOUtil::GetLastDbErrorMessage());
	}
    }
    delete objWriter;
    defaultCursor();
    reportInfo(IlString("Total ellapsed time = ")
	       + IlString(IlvRunTime() - time1) + IlString("\n"));
    reportTraces();
}

// --------------------------------------------------------------------------
// Loads the datas stored in an SDO layer
// --------------------------------------------------------------------------
void
MySdopan::dbLoadCB(IlvGraphic* g)
{
    if (!checkDbms()) {
	return;
    }
    SetVisibleFieldsLayer(_whichLayerPanel,IlFalse);
    whichLayer();
    if (!_layerName || !_layerName[0]) {
	return;
    }
    IlvManager* manager = getscm()->getManager();
    waitCursor();
    IlvSetContentsChangedUpdate(IlFalse);
    IlInt nbTotalObjects = 0;
    IlvMapsError status;
    nbTotalObjects = IlvObjectSDOUtil::GetGeometriesCount(_dbms, _layerName,
							  status);
    if (nbTotalObjects == 0) {
	reportInfo("No object to load\n");
	defaultCursor();
	return;
    }
    IldRequest* req = 0;

    IlString tmp2(IlString("Loading ") + IlString(_layerName)
		  + IlString(" SDO Layer ...\n"));
    reportInfo(tmp2.getValue());
    initGauge((IlvFloat)nbTotalObjects);
    IlString tmp;
    // The main request that has to be passed to the feature iterators.
    // Note that you can use any type of request (for instance typical sdo
    // requests with primary and secondary filters) that produces the same
    // kind of IldRequest
    tmp = IlString("select * from " + IlString(_layerName));
    // setting the colArraySize of the request to the number of rows in the
    // SDOGEOM table. DON'T DO THIS if you have a lot of geometries: it would
    // cost too much memory (but it imitates the number of accesses to the DB
    // in order to retreive data).
    req = executeQuery(tmp.getValue(), (IlUShort)_colarraysize);
    _sdoReader = new IlvObjectSDOFeatureIterator(req,
						 getGeometryName(),
						 (const char*)0);

    IlvMapsError initError = _sdoReader->getInitStatus();
    if (initError != IlvMaps::NoError()) {
	reportDBError(IlvMaps::GetErrorMessageId(initError));
    }
    IlInt nbObjects = 0;
    IlvDefaultFeatureRenderer renderer(getDisplay());
    const IlvMapFeature* feature = 0;
    IlvMapInfo* mapinfo = IlvMapInfo::Get(manager);
    reportInfo("handling resultSet ...\n");
    IlvRunTimeType time1 = IlvRunTime();
    // typical way of extracting datas from an IlvMapFeatureIterator
    manager->initReDraws();
    do {
	// then, extracting the features one by one.
	feature = _sdoReader->getNextFeature(status);
	if (feature) {
	    IlvGraphic* g = renderer.makeGraphic(*feature, *mapinfo, status);
	    // attach a copy of the attributes (if any) to the graphic in
	    // order to display them later. It may be memory-expensive.
	    if (feature->getAttributes()) {
		g->setNamedProperty(feature->getAttributes()->copy());
	    }
	    if (g) {
		manager->addObject(g, IlFalse);
		manager->invalidateRegion(g);
	    }
	    nbObjects++;
	    updateGauge((IlvFloat)nbObjects);
	}
    } while (feature && (status == IlvMaps::NoError()));
    reportInfo(IlString(nbObjects) + " Objects loaded in " +
	       IlString(IlvRunTime() - time1) +  "seconds.\n");
    delete _sdoReader;
    _sdoReader = 0;
    req->release();
    manager->reDrawViews();
    IlvSetContentsChangedUpdate(IlTrue);
    manager->contentsChanged();
    defaultCursor();
    reportTraces();
}

// --------------------------------------------------------------------------
// Pops a subpanel for layer creation
// --------------------------------------------------------------------------
void
MySdopan::newCB(IlvGraphic* g)
{
    if (!checkDbms()) {
	return;
    }
    _newLayerPanel->moveToView(this);
    IlvTextField* tf = (IlvTextField*)_newLayerPanel->getObject("layer");
    tf->setLabel(_layerName);
    _newLayerPanel->showModal();
    _newLayerPanel->hide();
    if (IlvSDOUtil::SQLTracesEnabled()) {
	reportTraces();
    }
}

// --------------------------------------------------------------------------
// Loads a map file (Shape file, ...)
// --------------------------------------------------------------------------
void
MySdopan::loadCB(IlvGraphic* g)
{
    _fileName = _fileBrowserShp->get();
    IlvManager* manager = getscm()->getManager();
    if (!_fileName.isEmpty()) {
	waitCursor();
	IlvMapLoader loader(manager);
	if (_reader) {
	    delete _reader;
	    _reader = 0;
	}
	_reader = loader.makeFeatureIterator(_fileName.getValue());
	if (_reader && _reader->getInitStatus() == IlvMaps::NoError()) {
	    IlvDefaultFeatureRenderer renderer(getDisplay());
	    IlvMapsError status;
	    _nbFeatures = 0;
	    const IlvMapFeature* feature = _reader->getNextFeature(status);
	    // if the map feature has any info, copy it and keep it for the
	    // object layer creation.
	    if (!_info && feature && feature->getAttributeInfo()) {
		_info = feature->getAttributeInfo()->copy();
		_info->lock();
	    }
	    IlvMapInfo* mapinfo = IlvMapInfo::Get(manager);
	    IlvSetContentsChangedUpdate(IlFalse);
	    manager->initReDraws();
	    while (feature) {
		_nbFeatures++;
		IlvGraphic* g = renderer.makeGraphic(*feature, *mapinfo,
						     status);
		if (g) {
		    manager->addObject(g, IlFalse);
		    manager->invalidateRegion(g);
		}
		feature = _reader->getNextFeature(status);
	    }
	    IlvSetContentsChangedUpdate(IlTrue);
	    manager->contentsChanged();
	    manager->fitTransformerToContents(manager->getFirstView(),
					      IlvTrue, IlvTrue);
	}
	IlString str("read ");
	str += IlString(_nbFeatures) + IlString(" features.");
	reportInfo(str.getValue());
	defaultCursor();
    }
}

// --------------------------------------------------------------------------
// Saves an .ilv file
// --------------------------------------------------------------------------
void
MySdopan::saveCB(IlvGraphic* g)
{
    _fileBrowserIlv->setType(IlvFileSelectorSave);
    _fileName = _fileBrowserIlv->get();
    _fileBrowserIlv->setType(IlvFileSelectorLoad);
    if (!_fileName.isEmpty()) {
	waitCursor();
	ILVSTDPREF ofstream ofs(_fileName.getValue());
	getscm()->getManager()->save(ofs);
	ofs.close();
	defaultCursor();
    }
}

// --------------------------------------------------------------------------
void
MySdopan::panCB(IlvGraphic* g)
{
    IlvManager* manager = getscm()->getManager();
    manager->setInteractor(_pan, manager->getFirstView());
    IlvToolBar* tb = gettoolbar();
    IlvMenuItem* item = tb->getItem(1);
    item->deSelect();
    item = tb->getItem(2);
    item->deSelect();
}

// --------------------------------------------------------------------------
void
MySdopan::zoomInCB(IlvGraphic* g)
{
    IlvManager* manager = getscm()->getManager();
    manager->setInteractor(_zoom, manager->getFirstView());
    IlvToolBar* tb = gettoolbar();
    IlvMenuItem* item = tb->getItem(0);
    item->deSelect();
    item = tb->getItem(1);
    item->deSelect();
}

// --------------------------------------------------------------------------
void
MySdopan::zoomCB(IlvGraphic* g)
{
    IlvManager* manager = getscm()->getManager();
    IlvRect visibleRect;
    getscm()->getView()->sizeVisible(visibleRect);
    manager->zoomView(manager->getFirstView(),
			IlvPoint(visibleRect.centerx(),
				 visibleRect.centery()),
			1.5, 1.5);
}

// --------------------------------------------------------------------------
void
MySdopan::unzoomCB(IlvGraphic* g)
{
    IlvManager* manager = getscm()->getManager();
    IlvRect visibleRect;
    getscm()->getView()->sizeVisible(visibleRect);
    manager->zoomView(manager->getFirstView(),
			IlvPoint(visibleRect.centerx(),
				 visibleRect.centery()),
			(float) (1./1.5),
			(float) (1./1.5));
}

// --------------------------------------------------------------------------
void
MySdopan::fitToSizeCB(IlvGraphic* g)
{
    IlvManager* manager = getscm()->getManager();
    manager->fitTransformerToContents(manager->getFirstView(),
				      IlvTrue, IlvTrue);
}

// --------------------------------------------------------------------------
void
MySdopan::tracesCB(IlvGraphic* g)
{
    IlvMenuItem* item = ((IlvPopupMenu*)g)->getItem(1);
    if (item->isChecked()) {
	IlvSDOUtil::DisableSQLTraces();
	item->setChecked(IlFalse);
    }
    else {
	IlvSDOUtil::EnableSQLTraces(&_stream);
	item->setChecked(IlTrue);
    }
}

// --------------------------------------------------------------------------
// Opens a .ilv file.
// --------------------------------------------------------------------------
void
MySdopan::openCB(IlvGraphic* g)
{
    _fileName = _fileBrowserIlv->get();
    if (!_fileName.isEmpty()) {
	waitCursor();
	IlvManager* manager = getscm()->getManager();
	if (_mapinfo) {
	    _mapinfo->detach();
	    delete _mapinfo;
	    _mapinfo = 0;
	}
	manager->read(_fileName.getValue());
	IlvTiledLayer* layer = IlvTiledLayer::GetFirstTiledLayer(manager);
	if (layer) {
	    initDebugView(layer);
	    initMagView();
	    IlvTiledLayer::StartAll(manager);
	    manager->fitTransformerToContents(manager->getFirstView(),
					      IlvTrue,IlvTrue);

	}
	defaultCursor();
    }
}

// --------------------------------------------------------------------------
// Resets all in order to delete the tiled layer (IlvSDOLayer or
// IlvObjectSDOLayer)
// --------------------------------------------------------------------------
void
MySdopan::resetCB(IlvGraphic* g)
{
    IlvManager* manager = getscm()->getManager();
    IlUInt count = manager->getNumLayers();
    for (IlUInt i = 2; i < count; i++) {
	IlvManagerLayer* layer = manager->getManagerLayer(i);
        if (layer &&
	    layer->getClassInfo()->isSubtypeOf(IlvTiledLayer::ClassInfo())) {
	    IlvTileController* cont =  ((IlvTiledLayer*)layer)
						       ->getTileController();
	    cont->removeTileListener(_listener);
	    delete _listener;
	    _listener = 0;
	    manager->deleteAll(i, IlTrue, IlTrue);
	    manager->removeLayer(i);
	}
    }
    if (_debugView) {
	delete _debugView;
	_debugView = 0;
    }
    manager->deleteAll(IlTrue, IlTrue);

}

// --------------------------------------------------------------------------
// Exits the application
// --------------------------------------------------------------------------
void
MySdopan::exitCB(IlvGraphic* g)
{
    if (_debugView) {
	delete _debugView;
	_debugView = 0;
    }
    IlvDisplay* d = getDisplay();
    delete d;
    IlvExit(0);
}

// --------------------------------------------------------------------------
// Initilizes the debug view of the tiled layer.
// --------------------------------------------------------------------------
void
MySdopan::initDebugView(IlvTiledLayer* layer)
{
    IlvManager* manager = getscm()->getManager();
   if (_debugView) {
       manager->removeInteractor(_debugView);
       delete _debugView;
   }
   _debugView = new IlvView(getDisplay(),
			    "Debug view",
			    "Debug view",
			    IlvRect(600, 0, 300, 300));
   layer->setDebugView(_debugView);
   manager->addView(_debugView);
   _debugView->show();
}

// --------------------------------------------------------------------------
// Fits the layer passed as argument to the central tile of the Load On
// Demand grid.
// --------------------------------------------------------------------------
void
MySdopan::fitToTile(IlvTiledLayer* layer)
{
    IlvManager* manager = getscm()->getManager();
    IlInt col = 0;
    IlInt row = 0;
    if (layer->getSize()) {
	IlInt upperRow, lowerRow, leftCol, rightCol;
	layer->getTileController()->getTileIndexes(layer->getSize(),
						   upperRow,
						   lowerRow,
						   leftCol,
						   rightCol);
	col = leftCol + rightCol / 2;
	row = upperRow + lowerRow / 2;
    }
    layer->fitTransformerToTile(manager->getFirstView(), row, col);
}


// --------------------------------------------------------------------------
// Initializes the mag view interactor.
// --------------------------------------------------------------------------
void
MySdopan::initMagView()
{
    IlvManager* manager = getscm()->getManager();
    if (_mag) {
	delete _mag;
    }
    _mag = new IlvManagerMagViewInteractor(manager,
					   _debugView,
					   manager->getFirstView());
    manager->setInteractor(_mag, _debugView);
    _mag->setAutoZooming(IlTrue);
    _mag->setAutoTranslating(IlTrue);
}

// --------------------------------------------------------------------------
void
MySdopan::colarrayCB(IlvGraphic* g)
{
    IlvMessageLabel* label = (IlvMessageLabel*)_colarrayPanel
							->getObject("label");
    label->setLabel("Enter the col array size for requests:");
    IlvNumberField* nf = (IlvNumberField*)_colarrayPanel
						  ->getObject("tilingLevel");
    nf->setLabel(IlString(_colarraysize).getValue());
    _colarrayPanel->moveToView(this);
    _colarrayPanel->showModal();
}
