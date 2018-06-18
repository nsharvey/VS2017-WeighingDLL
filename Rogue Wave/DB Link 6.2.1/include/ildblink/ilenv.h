// -------------------------------------------------------------- -*- C++ -*-
//					       Rogue Wave DB Link source file
// File: include/ildblink/ilenv.h
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
// Handling ressources, options, and environment variables.
//
// Based on ICU4C, the class IlEnvironment is able to:
//	- use or change current locale
//	- load resource bundles in set locale
//	- handle options
//	- retrieve a specific resource using a given resource callback
//
// Notes:
//	- For any top level resource bundle to be loaded, there must exist
//	a first level sub-bundle named 'messages'
//	- Other sub-bundles will be accessed through getResources
//
// ----------------------------------------------------------------------------

#ifndef __Il_Env_H
#define __Il_Env_H

#if !defined(__ILD_ILD_H)
# include <ildblink/ild.h>
#endif
#if !defined(__Il_List_H)
# include <ilog/list.h>
#endif
#if !defined(__Il_Array_H)
# include <ilog/array.h>
#endif

// ----------------------------------------------------------------------------
// Typedef for get resource callback
// Provides for extensibility
// First argument is application specific data (e.g. for Views an IlvDisplay*)
//	which had been stored when setting the callback function.
// Second argument is the resource name
// Third argument is a default value (can be null)
// ----------------------------------------------------------------------------
typedef const char* (*IlGetResFunc) (IlAny,
				     const char*,
				     const char*);

typedef void (*IlChangeLocaleFunc) (IlAny,
				    const char*,
				    const char*,
				    const char*,
				    const char*);

// ----------------------------------------------------------------------------
//
class ILD_EXPORTED
IlDeclareArrayWithoutEquality(char*, IlPathArray);

IlDefineExpAListOf(Options, char*, char*, ILD_EXPORTED);

// ----------------------------------------------------------------------------
class ILD_EXPORTED IlEnvironment {
public:
    virtual ~IlEnvironment			();
    static IlEnvironment* Get			();
    static IlBoolean Exists			();
    /*
     * \short  Gets the error code name from the last execution of a function
     *   on this instance.
     *
     * \param code The ICU error code to translate.
     *
     * \return An error code name as defined by ICU (source type is \c UErrorCode).
     */
    const char*		getErrorCode		(int code = 0) const;
    /*
     * \short  Indicates if the object is in a bogus state or not.
     *
     * @return \c IlTrue if the object is in a bogus state.
     * 
     * Whenever a call to \c isBad() returns \c IlTrue,
     * any result that should have been computed by the previous function call
     * are undefined.
     */
    IlBoolean		isBad			() const;
    /*
     * @short  Tell if the last function call encountered an error in the 
     * underlying ICU API calls.
     *
     * @return \c IlTrue if an error occured.
     * 
     * Whenever a call to \c hasError() returns \c IlTrue,
     * any result that should have been computed by the previous function call
     * are undefined.
     */
    IlBoolean		hasError		() const;
    /*
     * @short  Tell if the last function call performed without error.
     *
     * @return \c IlTrue if the last call performed properly.
     * 
     * Whenever a call to this function returns \c IlTrue, no error,
     * either detected by the class methods or the ICU API calls, was raised.
     * 
     */
    inline
    IlBoolean		isClean			() const
    {
	return !isBad() && !hasError();
    }
    /*
     * @short  Tell if the last function call received a warning from the 
     * underlying ICU API calls.
     *
     * @return \c IlTrue if a warning occured.
     * 
     * Whenever a call to this function returns \c IlTrue, the result
     * that have been computed by this function are correct notwithstanding
     * the possible effect mentioned by the warning.
     */
    IlBoolean		hasWarning		() const;
    /*
     * @short  Find the data directory path set in the object.
     *
     * @param i The index of the data directory to return.
     *
     * @return The data directory at index \a i as a const string.
     * 
     * This function cannot fail but may return a null pointer if no data
     * directory was set previously on this object or the given index is 
     * greater than the size of the directories array.
     *
     */
    const char*		getDataDir		(const IlUInt i) const;
    /*
     * @short  Set the unique directory where to look for resource bundles to
     * load.
     *
     * @param dir The unique directory to use in future searches.
     *
     * @return \c IlFalse only if the allocation of the copy of the
     * argument failed.
     * 
     * All previous contents of the directories array are lost.
     * If the argument is null or empty, deletes the old contents if any and
     * returns true.
     *
     */
    IlBoolean		setDataDir		(const char* dir = 0);
    /*
     * @short  Adds a directory where to look for resource bundles to load to 
     * the existing array of directories.
     *
     * @param dir The new directory to use in future searches.
     *
     * @return \c IlFalse if the allocation of the copy of the argument failed
     * or the argument is null or the empty string, \c IlTrue otherwise.
     * 
     * The argument should not be null or empty.
     * 
     * The given directory will not be added if it is already present in the
     * array but the call will return \c IlTrue.
     *
     */
    IlBoolean		addDataDir		(const char* dir);
    IlGetResFunc	setGetResourceCallback	(IlGetResFunc f,
						 IlAny cbkData = 0);
    // ---------------
    // Locale handling
    // ---------------
    IlChangeLocaleFunc	setChangeLocaleCallback	(IlChangeLocaleFunc f,
						 IlAny cbkData = 0);
    virtual 
    IlBoolean		setLocale		(const char* language,
						 const char* country = 0,
						 const char* variant = 0,
						 const char* keysAndVals = 0);

    // ------------------
    // Resources handling
    // ------------------    
    IlBoolean		loadResources		(const char* bName = 0);

    IlBoolean		linkResources		(const char* bName,
						 const void** ptr);
    char*		getMessage		(const char* key,
						 const char* bName = 0);

    char*		getMessageUTF8		(const char* key,
						 const char* bName = 0);


    // Intentional: only 'simple' types are returned,
    //		For complex types, use the same but one level deeper.
    IlInt		getIntResource		(int level,
						 const char* bundleNames[],
						 const char* key = 0);

    IlInt*		getIntVectResource	(int level,
						 const char* bundleNames[],
						 IlInt& len,
						 const char* key = 0);

    IlInt		getIntVectNthResource	(int level,
						 const char* bundleNames [],
						 IlInt nth,
						 const char* key = 0);

    IlUChar*		getBinaryResource	(int level,
						 const char* bundleNames[],
						 IlInt& len,
						 const char* key = 0);

    // ----------------
    // Options handling
    // ----------------
    const char*		getOptionValue		(char* key) const;

    void		setOption		(char* key,
						 char* value);

    IlBoolean		setOptionValue		(char* key,
						 char* value);

    const char*		getEnvOrOption		(const char* name,
						 const char* resName = 0,
						 const char* def = 0) const;

    const char*		getOption		(const char* name,
						 const char* def = 0) const;

    const char*		getEnvOrResource	(const char* name,
						 const char* resName = 0,
						 const char* def = 0) const;

    const char*		getResource		(const char* name,
						 const char* def = 0) const;

    void setBad() { _bad = IlTrue; }
protected:
    IlBoolean		_bad;
    IlOptionsAList	_options;
    IlPathArray		_dirs;
    IlGetResFunc	_getResCbk;
    IlAny		_resCbkData;
    IlChangeLocaleFunc	_chgLocCbk;
    IlAny		_locCbkData;

private:
    IlEnvironment();
    void		reset			();
    // Wrapper for getenv: most probably useless.
    const char*		getEnv			(const char* var) const;

    static IlEnvironment*	_singleton;
public:
    // Internals
    struct		P;
    struct P*		_p;
};

#endif
