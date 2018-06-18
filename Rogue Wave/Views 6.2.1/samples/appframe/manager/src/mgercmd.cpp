// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/appframe/manager/src/mgercmd.cpp
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
// Definition of ManagerCommand classes
// --------------------------------------------------------------------------
#include "mgercmd.h"
#include <ManagerView.h>
#include <ilviews/manager/manager.h>

#if defined(IL_STD)
#include <string>
IL_STDUSE
#else  /* !IL_STD */
#include <string.h>
#endif /* IL_STD */

// --------------------------------------------------------------------------
// ManagerCommand methods
// --------------------------------------------------------------------------
// Constructor / destructor
ManagerCommand::ManagerCommand(IlvManager* manager,
			       const char* name)
: IlvDvCommand(name),
  _manager(manager)
{
    IlvGraphic* const* selGraphics = _manager->getSelections(_count);
    if (_count) {
	_graphics = new IlvGraphic*[_count];
	for(IlUInt iGraphic = 0; iGraphic < _count; iGraphic++)
	    _graphics[iGraphic] = selGraphics[iGraphic];
    }
    else 
	_graphics = 0;
}

// --------------------------------------------------------------------------
ManagerCommand::ManagerCommand(const ManagerCommand& cmd)
: IlvDvCommand(cmd),
  _manager(cmd._manager)
{
    _count = cmd._count;
    if (_count) {
	_graphics = new IlvGraphic*[_count];
	for(IlUInt iGraphic = 0; iGraphic < _count; iGraphic++)
	    _graphics[iGraphic] = cmd._graphics[iGraphic];
    }
    else
	_graphics = 0;
}

// --------------------------------------------------------------------------
ManagerCommand::~ManagerCommand()
{
    if (_graphics)
	delete[] _graphics;
}

// --------------------------------------------------------------------------
struct ApplyObjectParam {
    ManagerCommand*			_mgerCmd;
    ManagerCommand::CmdGraphicCallback	_callback;
    IlAny				_param;
};

static void ILVCALLBACK
ApplyObjectCallback(IlvGraphic* g, IlAny arg)
{
    struct ApplyObjectParam* applyParam = (struct ApplyObjectParam*)arg;
    ManagerCommand::CmdGraphicCallback method = applyParam->_callback;
    (applyParam->_mgerCmd->*method)(g, applyParam->_param);
}

// ---------------------------------------------------------------------------
void
ManagerCommand::forEachGraphic(CmdGraphicCallback callback,
			       IlAny p)
{
    struct ApplyObjectParam param;
    param._mgerCmd = this;
    param._callback = callback;
    param._param    = p;

    _manager->applyToObjects(_count,
			     (IlvGraphic* const*)_graphics,
			     ApplyObjectCallback,
			     (IlAny)&param,
			     IlTrue);
}

// --------------------------------------------------------------------------
// TranslateSelectionCommand methods
// --------------------------------------------------------------------------
// Constructor / destructor
TranslateSelectionCommand::TranslateSelectionCommand(IlvManager* manager,
						     const IlvPoint& point,
						     const IlvTransformer* t,
						     const char* name)
: ManagerCommand(manager, name? name : "&MoveObjects"),
  _offset(point)
{
    if (t)
	_t.compose(*t);
}

// --------------------------------------------------------------------------
TranslateSelectionCommand::TranslateSelectionCommand(
			const TranslateSelectionCommand& cmd)
: ManagerCommand(cmd),
  _offset(cmd._offset)
{
    _t.compose(cmd._t);
}

// --------------------------------------------------------------------------
IlvDvCommand*
TranslateSelectionCommand::copy() const
{
    return new TranslateSelectionCommand(*this);
}

// --------------------------------------------------------------------------
// Main operations
void
TranslateSelectionCommand::doIt()
{
    forEachGraphic((CmdGraphicCallback)
			&TranslateSelectionCommand::translateObject,
		   (IlAny)&_offset);
}

// --------------------------------------------------------------------------
void
TranslateSelectionCommand::undo()
{
    IlvPoint offset(-_offset.x(), -_offset.y());
    forEachGraphic((CmdGraphicCallback)
			&TranslateSelectionCommand::translateObject,
		   (IlAny)&offset);
}

// --------------------------------------------------------------------------
void
TranslateSelectionCommand::translateObject(IlvGraphic* graphic,
					   IlAny pPoint)
{
    IlvPoint* point = (IlvPoint*)pPoint;
    IlvPos dx = point->x(), dy = point->y();
    if (!_t.isIdentity()) {
	IlvRect bbox;
	IlvPoint p;
	graphic->boundingBox(bbox);
	p.move(bbox.centerx(), bbox.centery());
	_t.apply(p);
	p.translate(dx, dy);
	_t.inverse(p);
	IlvPos objdx = p.x() - bbox.centerx();
	IlvPos objdy = p.y() - bbox.centery();
	graphic->translate(objdx, objdy);
    }
    else graphic->translate(dx, dy);
}

// --------------------------------------------------------------------------
// ActiveSelectionCommand methods
// --------------------------------------------------------------------------
// Constructor / destructor
ActiveSelectionCommand::ActiveSelectionCommand(IlvManager* manager,
					const IlvGraphic* activeSelection)
  : ManagerCommand(manager),
    _activeIndex((IlUInt)-1)
{
    updateActiveIndex(activeSelection);
}

// --------------------------------------------------------------------------
ActiveSelectionCommand::ActiveSelectionCommand(
					const ActiveSelectionCommand& src)
  : ManagerCommand(src),
    _activeIndex(src._activeIndex)
{
}

// --------------------------------------------------------------------------
void
ActiveSelectionCommand::updateActiveIndex(const IlvGraphic* graphic)
{
    _activeIndex = (IlUInt)-1;
    if (!_manager)
	return;
    IlUInt count;
    IlvGraphic* const* selGraphics = _manager->getSelections(count);
    if (!count)
	return;
    for(_activeIndex = 0; _activeIndex < count; _activeIndex++)
	if (selGraphics[_activeIndex] == graphic)
	    return;
    _activeIndex = (IlUInt)-1;
}

// --------------------------------------------------------------------------
const IlvGraphic*
ActiveSelectionCommand::getActiveGraphic() const
{
    if (_activeIndex == (IlUInt)-1)
	return 0;
    IlUInt count;
    IlvGraphic* const* selGraphics = _manager->getSelections(count);
    if (!count)
	return 0;
    return selGraphics[_activeIndex];
}

// --------------------------------------------------------------------------
void
ActiveSelectionCommand::doIt()
{
    _activeGraphic = getActiveGraphic();
}

// --------------------------------------------------------------------------
void
ActiveSelectionCommand::undo()
{
    _activeGraphic = getActiveGraphic();
}

// --------------------------------------------------------------------------
// ReshapeCommand methods
// --------------------------------------------------------------------------
// Constructor / destructor
ReshapeCommand::ReshapeCommand(IlvManager* manager,
			       const IlvGraphic* activeSelection,
			       const IlvRect& reshapeRect)
  : ActiveSelectionCommand(manager, activeSelection),
    _reshapedRect(reshapeRect)
{
    IlvDvAssert(activeSelection);
    activeSelection->boundingBox(_previousRect);
}

// --------------------------------------------------------------------------
ReshapeCommand::ReshapeCommand(const ReshapeCommand& src)
  : ActiveSelectionCommand(src),
    _previousRect(src._previousRect),
    _reshapedRect(src._reshapedRect)
{
}

// --------------------------------------------------------------------------
IlvDvCommand*
ReshapeCommand::copy() const
{
    return new ReshapeCommand(*this);
}

// --------------------------------------------------------------------------
void
ReshapeCommand::doIt()
{
    ActiveSelectionCommand::doIt();
    forEachGraphic((CmdGraphicCallback)&ReshapeCommand::reshapeObject,
		   (IlAny)&_reshapedRect);
}

// --------------------------------------------------------------------------
void
ReshapeCommand::undo()
{
    ActiveSelectionCommand::undo();
    forEachGraphic((CmdGraphicCallback)&ReshapeCommand::reshapeObject,
		   (IlAny)&_previousRect);
}

// --------------------------------------------------------------------------
void
ReshapeCommand::reshapeObject(IlvGraphic* graphic,
			      IlAny pRect)
{
    if (graphic == _activeGraphic)
	graphic->moveResize(*(IlvRect*)pRect);
}

// --------------------------------------------------------------------------
// ManagerDeleteCommand methods
// --------------------------------------------------------------------------
// Constructor / destructor
ManagerDeleteCommand::ManagerDeleteCommand(ManagerView* mgerView,
					   const IlvGraphic* activeSelection)
  : ActiveSelectionCommand(mgerView->getManager(), activeSelection),
    _editor(mgerView),
    _graphics(0),
    _count(0)
{
    createCopies();
}

// --------------------------------------------------------------------------
ManagerDeleteCommand::ManagerDeleteCommand(const ManagerDeleteCommand& src)
  : ActiveSelectionCommand(src),
    _graphics(0),
    _count(src._count)
{
    if (_count) {
	_graphics = new IlvGraphic*[_count];
	for(IlUInt i = 0; i < _count; i++)
	    _graphics[i] = (src._graphics[i])->copy();
    }
}

// --------------------------------------------------------------------------
ManagerDeleteCommand::~ManagerDeleteCommand()
{
    deleteGraphics();
}

// --------------------------------------------------------------------------
void
ManagerDeleteCommand::deleteGraphics()
{
    if (_count && _graphics) {
	for(IlUInt i = 0; i < _count; i++)
	    if (_graphics[i])
		delete _graphics[i];
	delete[] _graphics;
	_graphics = 0;
	_count = 0;
    }
}

// --------------------------------------------------------------------------
IlvDvCommand*
ManagerDeleteCommand::copy() const
{
    return new ManagerDeleteCommand(*this);
}

// --------------------------------------------------------------------------
#define  MAXSELECTIONS 10
void
ManagerDeleteCommand::doIt()
{
    createCopies();
    if (!_count)
	return;
    if (_count <= MAXSELECTIONS)
	_manager->deleteSelections();
    else {
	_manager->deleteSelections(IlFalse);
	_manager->reDraw();
    }
}

// --------------------------------------------------------------------------
void
ManagerDeleteCommand::undo()
{
    if (!_count)
	return;
    _manager->deSelectAll(IlFalse);
    for(IlUInt iObject = 0; iObject < _count; iObject++) {
	int layer =
	    IlCastIlAnyToInt(_graphics[iObject]->getProperty(_LayerProperty));
	_manager->addObject(_graphics[iObject], IlFalse, layer);
	_manager->setSelected(_graphics[iObject]);
    }
    _manager->reDraw();
    if (_activeIndex != (IlUInt)-1)
	_editor->setActiveSelection(_graphics[_activeIndex]);

    if (_graphics && _count) {
	delete[] _graphics;
	_graphics = 0;
	_count = 0;
    }
}

// --------------------------------------------------------------------------
void
ManagerDeleteCommand::createCopies()
{
    if (_graphics && _count)
	delete[] _graphics;
    IlvGraphic* const* selections = _manager->getSelections(_count);
    if (_count) {
	_graphics = new IlvGraphic*[_count];
	for(IlUInt i = 0; i < _count; i++) {
	    _graphics[i] = copyGraphic(selections[i]);
	}
    }
}

// --------------------------------------------------------------------------
IlvGraphic*
ManagerDeleteCommand::copyGraphic(const IlvGraphic* graphic) const
{
    IlvGraphic* copyGr = graphic->copy();
    copyGr->setProperty(_LayerProperty,
			IlCastIntToIlAny(_manager->getLayer(graphic)));
    return copyGr;
}

// --------------------------------------------------------------------------
// ManagerAlignCommand methods
// --------------------------------------------------------------------------
// Constructor / destructor
ManagerAlignCommand::ManagerAlignCommand(IlvManager*       manager,
					 const IlvGraphic* activeSelection,
					 IlvPosition       side)
  : ActiveSelectionCommand(manager, activeSelection),
    _side(side),
    _rects(0),
    _rectNumbers(0)
{
    createRects();
}

// --------------------------------------------------------------------------
ManagerAlignCommand::ManagerAlignCommand(const ManagerAlignCommand& src)
  : ActiveSelectionCommand(src),
    _rects(0)
{
    _rectNumbers = src._rectNumbers;
    if (_rectNumbers) {
	_rects = new IlvRect[_rectNumbers];
	::memcpy((IlAny)_rects, src._rects, _rectNumbers * sizeof(IlvRect));
    }
}

// --------------------------------------------------------------------------
ManagerAlignCommand::~ManagerAlignCommand()
{
    if (_rects && _rectNumbers)
	delete[] _rects;
}

// --------------------------------------------------------------------------
IlvDvCommand*
ManagerAlignCommand::copy() const
{
    return new ManagerAlignCommand(*this);
}

// --------------------------------------------------------------------------
void
ManagerAlignCommand::doIt()
{
    createRects();
    ActiveSelectionCommand::doIt();

    IlvDvAssert(_activeGraphic);
    IlvRect bbox;
    _activeGraphic->boundingBox(bbox);
    forEachGraphic((CmdGraphicCallback)&ManagerAlignCommand::alignObject,
		   (IlAny)&bbox);
}

// --------------------------------------------------------------------------
void
ManagerAlignCommand::undo()
{
    if (!_rectNumbers)
	return;
    ActiveSelectionCommand::undo();
    
    IlvRect* pRect = _rects;
    forEachGraphic((CmdGraphicCallback)&ManagerAlignCommand::setObjectBBox,
		   (IlAny)&pRect);
}

// --------------------------------------------------------------------------
void
ManagerAlignCommand::createRects()
{
    if (_rects && _rectNumbers)
	delete[] _rects;
    IlvGraphic* const* selections = _manager->getSelections(_rectNumbers);
    if (_rectNumbers) {
	_rects = new IlvRect[_rectNumbers];
	for(IlUInt i = 0; i < _rectNumbers; i++)
	    selections[i]->boundingBox(_rects[i]);
    }
    else
	_rects = 0;
}

// --------------------------------------------------------------------------
void
ManagerAlignCommand::alignObject(IlvGraphic* g,
				 IlAny pRect)
{
    IlvRect bboxObj;
    g->boundingBox(bboxObj);
    IlvRect rectRef = *(IlvRect*)pRect;

    switch(_side) {
    case IlvLeft:
	g->move(rectRef.left(), bboxObj.top());
	break;
    case IlvTop:
	g->move(bboxObj.left(), rectRef.top());
	break;
    case IlvRight:
	g->move(rectRef.right() - bboxObj.w(), bboxObj.top());
	break;
    case IlvBottom:
	g->move(bboxObj.left(), rectRef.bottom() - bboxObj.h());
	break;
    case IlvHorizontal:
	g->resize(rectRef.w(), bboxObj.h());
	break;
    case IlvVertical:
	g->resize(bboxObj.w(), rectRef.h());
	break;
    default:
	if (_side == CenterVerticaly)
	    g->move(bboxObj.left(),
		    rectRef.top() + rectRef.h() / 2 - (bboxObj.h() / 2));
	else if (_side == CenterHorizontaly)
	    g->move(rectRef.left() + rectRef.w() / 2 - (bboxObj.w() / 2),
		    bboxObj.top());
	break;
    }
}

// --------------------------------------------------------------------------
void
ManagerAlignCommand::setObjectBBox(IlvGraphic* graphic, IlAny
				   ppRect)
{
    IlvRect* pRect = *(IlvRect**)ppRect;
    if (graphic != _activeGraphic)
	graphic->moveResize(*pRect);
    *(IlvRect**)ppRect = pRect + 1;
}

// --------------------------------------------------------------------------
// Static initializations

IlvDvPreRegisterClass(ManagerCommand, IlvDvCommand);
IlvDvPreRegisterClass(TranslateSelectionCommand, ManagerCommand);
IlvDvPreRegisterClass(ActiveSelectionCommand, ManagerCommand);
IlvDvPreRegisterClass(ReshapeCommand, ActiveSelectionCommand);
IlvDvPreRegisterClass(ManagerDeleteCommand, ActiveSelectionCommand);
IlvDvPreRegisterClass(ManagerAlignCommand, ActiveSelectionCommand);
IlvDvPreRegisterSymbol(ManagerDeleteCommand::_LayerProperty, "_Layer");
IlvPosition ManagerAlignCommand::CenterVerticaly = (IlvPosition)0x100;
IlvPosition ManagerAlignCommand::CenterHorizontaly = (IlvPosition)0x200;

IL_BEGINMODULEINITDEF(mgercmd)
    IlvDvPostRegisterClass(ManagerCommand, IlvDvCommand);
    IlvDvPostRegisterClass(TranslateSelectionCommand, ManagerCommand);
    IlvDvPostRegisterClass(ActiveSelectionCommand, ManagerCommand);
    IlvDvPostRegisterClass(ReshapeCommand, ActiveSelectionCommand);
    IlvDvPostRegisterClass(ManagerDeleteCommand, ActiveSelectionCommand);
    IlvDvPostRegisterClass(ManagerAlignCommand, ActiveSelectionCommand);
    IlvDvPostRegisterSymbol(ManagerDeleteCommand::_LayerProperty, "_Layer");
    ManagerAlignCommand::CenterVerticaly = (IlvPosition)0x100;
    ManagerAlignCommand::CenterHorizontaly = (IlvPosition)0x200;
IL_ENDMODULEINITDEF(mgercmd)

#if !defined(ILVBUILDLIBS)
static int mgercmd_ini = (IL_MODINIT(mgercmd)(), 0);
#endif
