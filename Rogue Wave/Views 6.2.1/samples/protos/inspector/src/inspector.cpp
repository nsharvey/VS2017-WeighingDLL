// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/protos/inspector/inspector.cpp
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

/*
 * This examples shows how to link an Application object here, the transformer
 * of a view, to a user-editable graphical representation, using prototypes.
 *
 * the class EditableTransformer establishes a link between the GUI
 * and the internal values of the prototype.
 *
 * whenever one of the values is changed by the user (when she manipulates
 * the prototype), the changes are propagated to the View's transformer.
 * When the user or the application changes the transformer by other means
 * (say, moving the scrollbars), the prototypes is notified to show the
 * new values of the transformer.
 */

#include <ilviews/base/string.h>
#include <ilviews/graphics/all.h>
#include <ilviews/graphics/set.h>
#include <ilviews/graphics/inter.h>
#include <ilviews/gadmgr/rectscmg.h>
#include <ilviews/protos/allaccs.h>
#include <ilviews/protos/protogr.h>
#include <ilviews/protos/group.h>
#include <ilviews/protos/groupholder.h>
#include <ilviews/protos/grouplin.h>

#if defined(IL_STD)
IL_STDUSE;
#include <cstdlib> // for srand() and rand() and getenv()
#include <cmath>
#include <cstring>
#include <iostream>
#if defined(WINDOWS)
#include <fstream>
#endif /* WINDOWS */
#else  /* !IL_STD */
#include <stdlib.h> // for srand() and rand() and getenv()
#include <math.h>
#include <strings.h>
#include <iostream.h>
#if defined(WINDOWS)
#include <fstream.h>
#endif /* WINDOWS */
#endif /* !IL_STD */

#define DATAFILE "tfrmdemo.ilv"

#ifndef M_PI
#define M_PI 3.141592653589793238462643384279
#endif

// ---------------------------------------------------------------------------
// the link between the BGO and its functional kernel:

struct EditableTransformer : public IlvGroupMediator, public IlvManagerViewHook
{
    EditableTransformer (IlvManager*,
			 IlvView*,
			 IlvGroup*);
    ~EditableTransformer() {}
// overloaded from ManagerViewHook
    void transformerChanged (const IlvTransformer*,
			     const IlvTransformer*);
// overloaded from GroupMediator
    IlvBoolean changeValues (const IlvValue*,
			     IlUShort);
    void queryValues (IlvValue*,
		      IlUShort) const;
};

// --------------------------------------------------------------------------
EditableTransformer::EditableTransformer (IlvManager* mgr,
					  IlvView* v,
					  IlvGroup* g)
    : IlvGroupMediator(g, v),
      IlvManagerViewHook(mgr, v)
{
    mgr->installViewHook(this);
}

// ---------------------------------------------------------------------------
void
EditableTransformer::transformerChanged (const IlvTransformer*,
					 const IlvTransformer*)
{
    // called when the transformer is changed from somewhere
    // in the application: synchronizes the UI with the current transformer.
    // this is called for instance when scrollbars change the view
    update();
}

// ---------------------------------------------------------------------------
void
EditableTransformer::queryValues (IlvValue* values,
				  IlUShort n) const
{
    if (!getManager() || !getView())
        return;
    // get the values from the view's transformer
    IlvTransformer* t = getManager()->getTransformer(getView());
    IlvTransfoParam m11, m12, m21, m22, x, y;
    if (t)
      t->getValues(m11,m12,m21,m22,x,y);
    else { 
        m11 = m22 = 1;
	m12 = m21 = x = y = 0;
    }

    // transform them into the desired user representation
    IlFloat angle, sx, sy;
    angle = (IlFloat)((m22 != 0) ? atan(m21 / m22) : M_PI / 2);
    if (fabs(angle) < M_PI / 4) {
	sx = (IlFloat)(m11 / cos(angle));
	sy = (IlFloat)(m22 / cos(angle));
    } else {
	sx = (IlFloat)(-m12 / sin(angle));
	sy = (IlFloat)(m21 / sin(angle));
    }
    angle *= (IlFloat)(M_PI / 180.0); // because Views uses degrees, not radians
    if (angle < 0)
        angle += 360.0; // because the UI expects positive angles

    // export this representation to the user interface
    for (IlUInt i = 0; i < n ; i++) {
#define SET_VALUE(N,V)    \
    if (!strcmp(values[i].getName()->name(), N)) values[i] = V;
	SET_VALUE("Rotation", angle);
	SET_VALUE("X_Scale", sx);
	SET_VALUE("Y_Scale", sy);
	SET_VALUE("X_Translate", x);
	SET_VALUE("Y_Translate", y);
    }
}

// --------------------------------------------------------------------------
IlBoolean
EditableTransformer::changeValues (const IlvValue*,
				   IlUShort)
{
    // if the changeValues request comes from a update(), avoid loops
    // all changeValues bodies should start with this line.
    if (locked() || !getPresentation() || !getView() || !getManager())
	return IlTrue;

    // get the changed values from the user interface
    IlFloat angle, sx, sy, x, y;
    IlvValue v;
#define GET_VALUE(N, V) v = IlvValue(N); V = getPresentation()->queryValue(v);
    GET_VALUE("Rotation",angle);
    GET_VALUE("X_Scale",sx);
    GET_VALUE("Y_Scale",sy);
    GET_VALUE("X_Translate",x);
    GET_VALUE("Y_Translate",y);

    // update the application:
    // build the new transformer from the UI's values
    IlvTransformer new_t;
    new_t.scale(0, 0, sx, sy);
    new_t.rotate(0, 0, angle);
    new_t.translate(x, y);

    // make the effective changes. We set a lock, because
    // the setTransformer() call will in turn call transformerChanged()
    // therefore initiating an update loop.
    // this lock is _not_ necessary, but more efficient:
    // it avoids sending back the values to the interface.
    lock();
    getManager()->setTransformer(getView(), &new_t);
    getView()->erase(IlTrue);
    unlock();
    return IlTrue;
}

// --------------------------------------------------------------------------
// the main functions

static void
DestroyView(IlvView* top,
	    IlAny)
{
    IlvDisplay* d = top->getDisplay();
    delete top;
    delete d;
    IlvExit(0);
}

// ---------------------------------------------------------------------------
int
main(int argc,
     char* argv[])
{
    IlvDisplay* display = new IlvDisplay("PrototypeSample", "", argc, argv);
    if (!display || display->isBad()) {
	IlvFatalError("Couldn't open display");
	if (display)
	  delete display;
	return -1;
    }
    // The prototype and panel data files are located in the
    // parent directory, so add it to the display's path.
    IlString buf (getenv("ILVHOME"));
    buf += "/samples/protos/inspector/data";
    display->prependToPath(buf);

    // Create the main panel and window
    IlvManager* manager = new IlvManager(display);
    IlvView* view = new IlvView(display,
		"PrototypeSample",
		"Prototypes Sample (Transformer)",
		IlvRect(20, 100, 580, 400),
		IlTrue, IlFalse);
    view->setDestroyCallback(DestroyView);
    view->setBackground(display->getColor((IlFloat)0.,(IlFloat)0.,
					  (IlFloat).3));
    manager->addView(view);
    // Read the panel file: the prototypes used in the panel
    // are automatically loaded.
    manager->read(DATAFILE);

    // attach the transform's prototype to the view transformer
    IlvSCManagerRectangle* subview =
	(IlvSCManagerRectangle*) manager->getObject("transformed");
    if (!subview)
        IlvFatalError("transformed object not found\n");
    IlvGroupHolder* groupHolder=IlvGroupHolder::Get(manager);
    IlvGroup* group = groupHolder->getGroup("transformer");
    if (!group)
        IlvFatalError("transformer object not found\n");
    EditableTransformer* e =
        new EditableTransformer(subview->getManager(),
    				subview->getView(), group);
    // make the transform editor reflect the view's settings.
    e->update();

    // Show panel and run event loop.
    view->show();
    manager->setDoubleBuffering(view, IlTrue);
    IlvMainLoop();
    return 0;
}
