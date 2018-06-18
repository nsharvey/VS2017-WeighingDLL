// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/bidi/interf.h
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
// Bidi interface class
// --------------------------------------------------------------------------
#ifndef __Ilv_Bidi_Interf_H
#define __Ilv_Bidi_Interf_H

#ifndef __Ilv_Macros_H
#include <ilviews/macros.h>
#endif
#ifndef __Ilv_Bidi_Type_H
#include <ilviews/bidi/type.h>
#endif

class IlvBidiContext;

// --------------------------------------------------------------------------
class ILVDSPEXPORTED IlvBidiInterface
{
public:
    virtual IlvBidiContext* getBidiContext(IlBoolean fallback=IlTrue) const;
    virtual IlvBidiContext* getDefaultBidiContext() const;
    virtual IlBoolean	    setBidiContext(IlvBidiContext*);
    virtual IlBoolean       setDefaultBidiAttributes();
    virtual IlBoolean       isRightToLeft() const;
    void                    setBidiAttributes(IlvNumerals,
					      IlvSwapping,
					      IlvLayoutDirection,
					      IlvShaping,
					      IlvWordBreak);
    IlBoolean               getBidiAttributes(IlvNumerals*,
					      IlvSwapping*,
					      IlvLayoutDirection*,
					      IlvShaping*,
					      IlvWordBreak*) const;
    IlBoolean               hasDefaultBidiAttributes() const
	{
	    return getBidiContext(IlFalse) ? IlFalse : IlTrue;
	}
    virtual void            changeLayoutAttributes(IlAny, IlAny);
    virtual                 ~IlvBidiInterface();
};

#endif /* __Ilv_Bidi_Interf_H */
