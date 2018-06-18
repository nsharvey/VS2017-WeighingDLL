// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ilinum.h
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
// Handling numerics
//
// Based on ICU4C, the class IldNumeric is intended to handle numeric (or 
// decimal) data for display. Computation is not the main rationale for this 
// class: in most cases it is recommended to use the language computation 
// abilities rather than through the API of this class.
//  
//
// Notes:
//	- For compatibility, this class is derived from the class IlNumeric
//	which is now deprecated and should not be used directly anymore.
//	- As ICU does not support big numerics, the constructor of this 
//	class and its displaying capability are restricted to the default
//	format.
//
// --------------------------------------------------------------------------
#ifndef __Il_INum_H
#define __Il_INum_H

#ifndef __ILD_ILD_H
#  include <ildblink/ild.h>
#endif
#ifndef __Il_Ilnum_H
#  include <ilog/ilnum.h>
#endif
#ifndef __Il_Env_H
#  include <ildblink/ilenv.h>
#endif

// --------------------------------------------------------------------------
class ILD_EXPORTED IldNumeric
: public IlNumeric {
public:
    // New form: to be used
    IldNumeric(IlEnvironment* env)
    : IlNumeric(),
    _bad(IlFalse),
    _env(env)
    {}
    // New form: to be used
    IldNumeric(IlEnvironment* env,
	       const char* value)
    : IlNumeric(value),
      _env(env)
    {}
    IldNumeric(IlEnvironment* env,
	       long value)
    : IlNumeric(value),
      _env(env)
    {}
    IldNumeric(IlEnvironment* env,
	       double value);
    IldNumeric(const IldNumeric&);

    IlBoolean isBad () const
    {
	return _bad;
    }

    const IlEnvironment* getEnvironment() const
    {
	return _env;
    }

    const IlEnvironment* setEnvironment(IlEnvironment* env)
    {
	const IlEnvironment* old_env = _env;
	_env = env;
	return old_env;
    }

    IlBoolean set(const char* value);

    IlBoolean set(long value);

    IlBoolean set(double value);

    IldNumeric& operator=(const IldNumeric&);

    // Compatibility: do not use
    IldNumeric()
    : IlNumeric(),
      _env(0)
    {
    }
    // Compatibility: do not use
    IldNumeric(const char* value)
    : IlNumeric(),
      _env(0)
    {
	_bad = !IlNumeric::set(value);
    }
    // Compatibility: do not use
    IldNumeric(long value)
    : IlNumeric(),
      _env(0)
    {
	_bad = !IlNumeric::set(value);
    }
    // Compatibility: do not use
    void get(char* buff, IlInt len);
    void setBad() { _bad = IlTrue; }
protected:
    IlBoolean		_bad;
    IlEnvironment*	_env;
};

#endif /* !__Il_INum_H */
