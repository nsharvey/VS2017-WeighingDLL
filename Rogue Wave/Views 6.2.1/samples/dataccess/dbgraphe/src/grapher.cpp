// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/dataccess/dbgraphe/src/grapher.cpp
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
// Customize a grapher
// --------------------------------------------------------------------------

#include <grapher.h>

#include <ilviews/dataccess/gadgets/tblcombo.h>
#include <ilviews/dataccess/gadgets/entryfld.h>
#include <ilviews/dataccess/gadgets/labelbmp.h>

#ifdef IL_STD
#  include <strstream>
#else
#ifdef ILVFATFILENAMES
#  include <strstrea.h>
#else
#  include <strstream.h>
#endif
#endif

IL_STDUSE

enum SpeedLink {
  Speed9600 = 0,
  Speed64K,
  Speed384K,
  Speed1M
};

enum TypeOfNode {
  TypeNodeTerminal = 0,
  TypeNodeCenter,
  TypeNodeParabol
};

// --------------------------------------------------------------------------
// Dialog for links
// --------------------------------------------------------------------------
class DialogLink :
  public IlvDialog 
{
public:
  DialogLink(IlvDisplay*,SpeedLink speed = Speed9600);
  virtual void apply();
  SpeedLink getSpeed() { return _speed; } 
protected:
  SpeedLink _speed;
};

DialogLink::DialogLink(IlvDisplay* display,SpeedLink speed) 
: IlvDialog(display, "grlink", "Link parameter", "grlink.ilv") {
  _speed = speed;
  IliTableComboBox* cbn = (IliTableComboBox*)getObject("COMBO");
  if (cbn) {
    IliValue val((IlvInt)_speed);
    cbn->f_setValue(val);
  }
}

void
DialogLink::apply() {
  IliTableComboBox* cbn = (IliTableComboBox*)getObject("COMBO");
  if (cbn) {
    IliValue val = cbn->f_getValue();
    if (!val.isNull()) {
      _speed = (SpeedLink)(val.asInteger());
    }
  }
  IlvDialog::apply();
}

// --------------------------------------------------------------------------
// Dialog for nodes
// --------------------------------------------------------------------------
class DialogNode :
  public IlvDialog 
{
public:
  DialogNode(IlvDisplay*,TypeOfNode = TypeNodeCenter,const char* = 0);
  virtual void apply();
  TypeOfNode getTypeOfNode() const { return _typeOfNode; }
  const char* getNameOfNode() const { return (const char*)_nameOfNode; }
protected:
  TypeOfNode _typeOfNode;
  IliString _nameOfNode;
};

DialogNode::DialogNode(IlvDisplay* display,TypeOfNode type,const char* name)
: IlvDialog(display, "grnode", "Node parameter", "grnode.ilv") {
  _typeOfNode = type;
  IliTableComboBox* cbn = (IliTableComboBox*)getObject("COMBO");
  if (cbn) {
    IliValue val((IlvInt)_typeOfNode);
    cbn->f_setValue(val);
  }
  _nameOfNode = name;
  IliEntryField* ent = (IliEntryField*)getObject("ENTRY");
  if (ent && name && *name) {
    IliValue val(name);
    ent->f_setValue(val);
  }
}

void
DialogNode::apply() {
  IliTableComboBox* cbn = (IliTableComboBox*)getObject("COMBO");
  IliEntryField* ent = (IliEntryField*)getObject("ENTRY");
  if (cbn && ent) {
    IliValue val1 = cbn->f_getValue();
    IliValue val2 = ent->f_getValue();
    if (!val1.isNull() && !val2.isNull()) {
      _typeOfNode = (TypeOfNode)(val1.asInteger());
      _nameOfNode = val2.getFormatted();
      IlvDialog::apply();
    }
  }
}

// --------------------------------------------------------------------------
// Callbacks methods
// --------------------------------------------------------------------------

static IlvBoolean 
MyDefineNodeCallback(IliTableBuffer* buff,IlvGraphic*,IlvAny any) {
  static int stId = 1000;

  if (buff->at("ID").isNull()) {
    buff->at("ID").importInteger(stId);
    stId++;
  }
  Grapher* panel = (Grapher*)any;
  if (buff->at("NAME").isNull() || buff->at("TYPE").isNull()) {
    DialogNode* dlg = new DialogNode(panel->getDisplay());
    dlg->wait();
    if (dlg->wasCanceled())
      return IlvFalse;
    buff->at("NAME").importString(dlg->getNameOfNode());
    buff->at("TYPE").importInteger(dlg->getTypeOfNode());
    delete dlg;
  }
  return IlvTrue;
}

static IlvBoolean 
MyDefineLinkCallback(IliTableBuffer* buff,IlvGraphic*,IlvAny any) {
  Grapher* panel = (Grapher*)any;

  if (buff->at("TYPE").isNull()) {
    DialogLink* dlg = new DialogLink(panel->getDisplay());
    dlg->wait();
    if (dlg->wasCanceled())
      return IlvFalse;
    buff->at("TYPE").importInteger(dlg->getSpeed());
    delete dlg;
  } 
  return IlvTrue;
}

static IlvGraphic* 
MyCreateNodeCallback(IliTableBuffer* buff,IlvAny any) {
  IliDbGrapher* gr = (IliDbGrapher*)any;
  IliString picture;
  switch(buff->at("TYPE").asInteger()) {
  case TypeNodeCenter : picture = "center.xpm"; break;
  case TypeNodeParabol : picture = "parabol.xpm"; break;
  default : picture = "terminal.xpm"; break;
  }
  gr->setBitmapName((const char*)picture);

  IlvGraphic* obj  = gr->createDefaultObjectNode(buff);
  IliLabeledBitmap* node = (IliLabeledBitmap*)obj;

  node->setLabelName(buff->at("NAME").getFormatted());

  return node;
}

static IlvGraphic* 
MyCreateLinkCallback(IliTableBuffer* buff,IlvAny any) {
  IliDbGrapher* gr = (IliDbGrapher*)any;
  IlvColor* color;
  switch(buff->at("TYPE").asInteger()) {
  case Speed64K : color = gr->getDisplay()->getColor("red"); break;
  case Speed384K : color = gr->getDisplay()->getColor("blue"); break;
  case Speed1M : color = gr->getDisplay()->getColor("green"); break;
  default : color = gr->getDisplay()->getColor("black"); break;
  }
  if (! color)
    color = gr->getDisplay()->getColor("black");
  gr->setColor(IliGrapherLinkColor, color);
  return gr->createDefaultObjectLink(buff);
}

static void
MyDoubleClickNodeCallback(IlvGraphic* g,IlvAny any) {
  Grapher* panel = (Grapher*)any;
  IliDbGrapher* gr = (IliDbGrapher*)g;
  IliValue val((IlvInt)0);
    val.importString(gr->getObjectNameDoubleClicked());
  if (val.isNull())
    return;
  IliDataSource* ds = (IliDataSource*)panel->getObject("NODES_MS");
  IliTable* tbl = (ds)? ds->getTable() : 0;
  IliTableBuffer* buff = (tbl)? tbl->getBuffer() : 0;
  if (buff) {
    IlvInt col = tbl->getColumnIndex("ID");
    IlvInt row = tbl->findRow(val, col, IlvFalse);
    if (row != -1) {
      buff->rowToBuffer(row);
      IliString s = buff->at("NAME").getFormatted();
      DialogNode* dlg = new DialogNode(panel->getDisplay(),
				       (TypeOfNode)(buff->at("TYPE").asInteger()),
				       (const char*)s);
      dlg->wait();
      if (!dlg->wasCanceled()) {
	buff->at("NAME").importString(dlg->getNameOfNode());
	buff->at("TYPE").importInteger(dlg->getTypeOfNode());
	tbl->updateRow(row, buff);
      }
      delete dlg;
    }
    tbl->releaseBuffer(buff);
  }
}

static void
MyDoubleClickLinkCallback(IlvGraphic* g,IlvAny any) {
  IlvLinkImage* lnk;
  Grapher* panel = (Grapher*)any;
  IliDbGrapher* gr = (IliDbGrapher*)g;
  IlvGrapher* gra = gr->getGrapher();
  lnk = (IlvLinkImage*)(gra->getObject(gr->getObjectNameDoubleClicked()));
  IlvGraphic* gfrom = (lnk)? lnk->getFrom() : 0;
  IlvGraphic* gto   = (lnk)? lnk->getTo() : 0;
  if (!lnk || !gfrom || !gto)
    return;

  IliString from = gfrom->getName();
  IliString to = gto->getName();
  if (from.isNull() || to.isNull())
    return;

  IliDataSource* ds = (IliDataSource*)panel->getObject("LINK_MS");
  IliTable* tbl = (ds)? ds->getTable() : 0;
  IliTableBuffer* buff = (tbl)? tbl->getBuffer() : 0;
  if (buff) {
    IlvBoolean up;
    IlvInt count = tbl->getRowsCount();
    IlvInt i;
    for(i = 0; i < count; i++) {
      buff->rowToBuffer(i);
      up = (from == buff->at("FROM").getFormatted())? IlvTrue : IlvFalse;
      up = ((to == buff->at("TO").getFormatted()) && up)? IlvTrue : IlvFalse;
      if (up) {
	SpeedLink sp = (SpeedLink)(buff->at("TYPE").asInteger());
	DialogLink* dlg = new DialogLink(panel->getDisplay(),sp);
	dlg->wait();
	if (!dlg->wasCanceled()) {
	  buff->at("TYPE").importInteger(dlg->getSpeed());
	  tbl->updateRow(i, buff);
	}
	delete dlg;
	tbl->releaseBuffer(buff);
	return;
      }
    }
    tbl->releaseBuffer(buff);
  }
}

// --------------------------------------------------------------------------
// Grapher
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
Grapher::Grapher(IlvAbstractView* view, const char* filename)
  :PageNoteBook(view, filename) {
    initGrapher();
}

// --------------------------------------------------------------------------
// Set the callbacks and flags
// --------------------------------------------------------------------------
void
Grapher::initGrapher() {

  IliDbGrapher* gr = getGRAPHER();
  if (gr) {
    gr->setDefineObjectCallback(MyDefineNodeCallback,this,IlvTrue);
    gr->setCreateObjectCallback(MyCreateNodeCallback,gr,IlvTrue);
    gr->setDefineObjectCallback(MyDefineLinkCallback,this,IlvFalse);
    gr->setCreateObjectCallback(MyCreateLinkCallback,gr,IlvFalse);
    gr->addCallback(IliDbGrapher::NodeDoubleClickedSymbol(),
		    MyDoubleClickNodeCallback,this);
    gr->addCallback(IliDbGrapher::LinkDoubleClickedSymbol(),
		    MyDoubleClickLinkCallback,this);
    gr->setBackgroundPictureName("europe.ilv");
    gr->refreshAll();
  }
}

// --------------------------------------------------------------------------
// Called after build page
// --------------------------------------------------------------------------
void 
Grapher::afterBuild() {
  IliDbGrapher* gr = getGRAPHER();
  if (gr) {
    IlvManager* manager = gr->getManager();
    IlvView* view = gr->getView();
    manager->fitTransformerToContents(view, IlvTrue, IlvTrue);
  }
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageGrapher(Pan* mainPanel) {
  Grapher* panel = new Grapher(mainPanel,"grapher.ilv");
  mainPanel->addPageNoteBook(panel, "&Grapher", "grapher.txt");
}


// --------------------------------------------------------------------------
// NodeGrapher
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
NodeGrapher::NodeGrapher(IlvAbstractView* view, const char* filename)
  :PageNoteBook(view, filename) {
    initNodeGrapher();
}

// --------------------------------------------------------------------------
// Set the callbacks and flags
// --------------------------------------------------------------------------
void
NodeGrapher::initNodeGrapher() {

  IliTableGadget* tg = getTG();
  if (tg) {
      tg->f_setDataSourceName("NODES_MS");
      tg->setAutoFittingMode(IliFitProportional);
  }
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageNodeGrapher(Pan* mainPanel) {
  NodeGrapher* panel = new NodeGrapher(mainPanel,"table.ilv");
  mainPanel->addPageNoteBook(panel, "Nodes", "nodes.txt");
}

// --------------------------------------------------------------------------
// LinkGrapher
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
LinkGrapher::LinkGrapher(IlvAbstractView* view, const char* filename)
  :PageNoteBook(view, filename) {
    initLinkGrapher();
}

// --------------------------------------------------------------------------
// Set the callbacks and flags
// --------------------------------------------------------------------------
void
LinkGrapher::initLinkGrapher() {

  IliTableGadget* tg = getTG();
  if (tg) {
      tg->f_setDataSourceName("LINK_MS");
      tg->setAutoFittingMode(IliFitProportional);
  }
}

// --------------------------------------------------------------------------
// Defines the note page
// --------------------------------------------------------------------------
void 
DefinePageLinkGrapher(Pan* mainPanel) {
  LinkGrapher* panel = new LinkGrapher(mainPanel,"table.ilv");
  mainPanel->addPageNoteBook(panel, "Links", "links.txt");
}

