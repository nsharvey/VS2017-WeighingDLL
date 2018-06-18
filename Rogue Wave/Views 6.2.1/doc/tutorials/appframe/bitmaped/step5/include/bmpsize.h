// -------------------------------------------------------------- -*- C++ -*-
// File: /nfs/views-work/work.dupuy/doc/tutorials/appframe/bitmaped/step4/include/bmpsize.h
// IlogViews 4 generated header file
// File generated Tue Jun 27 18:52:03 2000
//      by Rogue Wave Views Studio
// --------------------------------------------------------------------------
#ifndef __bmpsize__header__
#define __bmpsize__header__

#include <ilviews/gadgets/button.h>
#include <ilviews/graphics/relfline.h>
#include <ilviews/gadgets/msglabel.h>
#include <ilviews/gadgets/idialog.h>
#include <ilviews/gadgets/frame.h>
#include <ilviews/gadgets/textfd.h>

// --------------------------------------------------------------------------
class BitmapSizeDialog
: public IlvDialog {
public:
    BitmapSizeDialog(IlvDisplay*  display,
                     const char*   name, 
                     const char*   title,
                     IlvRect*      size         = 0,
                     IlvBoolean    ignored      = IlvFalse,
                     IlvBoolean    visible      = IlvFalse,
                     IlvUInt       properties   = 0,
                     IlvSystemView transientFor = 0)
      : IlvDialog(display,
                  name,
                  title,
                  size ? *size : IlvRect(0, 0, 349, 138),
                  properties,
                  transientFor)
        {
            initialize();
            if (visible) show();
        }
    // ____________________________________________________________
    IlvTextField* getWidth() const
	{ return (IlvTextField*)getObject("Width"); }
    IlvTextField* getHeight() const
	{ return (IlvTextField*)getObject("Height"); }
    IlvFrame* getframe1() const
	{ return (IlvFrame*)getObject("frame1"); }
protected:
    void initialize();
};

#endif /* !__bmpsize__header__*/
