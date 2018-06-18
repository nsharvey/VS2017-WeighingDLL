// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilviews/manager/transition.h
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
// Miscellaneous classes to handle transformer transitions
// --------------------------------------------------------------------------
#ifndef __Ilv_Manager_Transition_H
#define __Ilv_Manager_Transition_H

#include <ilviews/util/transition.h>
#include <ilviews/bitmaps/transition.h>
#include <ilviews/manager/manager.h>

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerTransitionHandler : public IlvTransitionHandler
{
public:
    IlvManagerTransitionHandler(IlBoolean partialRedraw = IlTrue);
    ~IlvManagerTransitionHandler();
    inline IlBoolean	isUsingPartialRedraw() const { return _partialRedraw; }
    inline void		usePartialRedraw(IlBoolean redraw)
			{
			    _partialRedraw = redraw;
			}

protected:
    IlBoolean		_partialRedraw;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerLinearTransitionHandler
    : public IlvManagerTransitionHandler
{
public:
    IlvManagerLinearTransitionHandler(IlBoolean partialRedraw = IlTrue);
    virtual void	computeTransformers(IlDouble oldRate,
					    IlDouble newRate,
					    const IlvTransformer& from,
					    const IlvTransformer& to,
					    IlvTransformer& oldT,
					    IlvTransformer& curT) const;
    virtual void	doTransition(IlvTransitionScheduler& scheduler,
				     IlDouble old,
				     IlDouble current);
    virtual void	doManagerTransition(IlvManager& manager,
					    IlvView& view,
					    const IlvTransformer& from,
					    const IlvTransformer& to,
					    const IlvTransformer& current,
					    const IlvTransformer& next);
    static void ComputeTransitionTransformer(const IlvTransformer& from,
					     const IlvTransformer& to,
					     IlDouble step,
					     IlvTransformer& transition);
    static void ComputeTransitionTransformers(const IlvTransformer& from,
					      const IlvTransformer& to,
					      IlUInt steps,
					      IlvTransformer transitions[]);
};

class IlvManagerBitmapTransitionInfos;
class IlvManagerTransitionScheduler;

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerBitmapTransitionHandler
    : public IlvManagerTransitionHandler
{
public:
    IlvManagerBitmapTransitionHandler(IlvBitmapTransition& bitmapTransition,
				      IlBoolean owner = IlTrue,
				      IlBoolean partialRedraw = IlTrue);
    virtual ~IlvManagerBitmapTransitionHandler();

    virtual void	startTransition(IlvTransitionScheduler&);
    virtual void	stopTransition(IlvTransitionScheduler&);
    virtual void	doTransition(IlvTransitionScheduler& scheduler,
				     IlDouble old,
				     IlDouble current);
    IlvRGBBitmapData*	createBitmapData(const IlvManager& manager,
					 const IlvView& view,
					 const IlvTransformer& t,
					 IlBoolean optim = IlTrue) const;
 protected:
    IlvBitmapTransition&	_bitmapTransition;
    IlBoolean			_owner;
    IlAList			_list;

    IlvManagerBitmapTransitionInfos*
			getInfos(IlvManagerTransitionScheduler&) const;
};

// --------------------------------------------------------------------------
class ILVMGREXPORTED IlvManagerTransitionScheduler
    : public IlvTransitionScheduler
{
public:
    IlvManagerTransitionScheduler(IlvView* view,
				  IlvManagerTransitionHandler& handler,
				  IlUInt duration,
				  IlBoolean isSteps = IlFalse,
				  IlUInt delay = 0,
				  IlBoolean owner = IlTrue);
    ~IlvManagerTransitionScheduler();
    inline
    IlvManagerTransitionHandler& getTransitionHandler()
			{
			    return (IlvManagerTransitionHandler&)_handler;
			}
    inline
    const IlvManagerTransitionHandler& getTransitionHandler() const
			{
			    return (IlvManagerTransitionHandler&)_handler;
			}
    inline IlvView*	getView() const { return _view; }
    IlvManager*		getManager() const;
    virtual void	viewDeleted();
    virtual void	setView(IlvView* view);
    const IlvTransformer& getFrom() const { return _from; }
    const IlvTransformer& getTo() const { return _to; }
    void		composeTo(const IlvTransformer& t);
    inline void		setTransformers(const IlvTransformer& from,
					const IlvTransformer& to)
			{
			    _from = from; _to = to;
			}
protected:
    IlvView*    	_view;
    IlvTransformer	_from;
    IlvTransformer	_to;
};

#endif
