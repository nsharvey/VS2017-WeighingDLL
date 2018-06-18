// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ilog/pathname.h
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
// Declaration of the IlPathName class
// Defined in library <display>views
// --------------------------------------------------------------------------
#ifndef __Il_Pathname_H
#define __Il_Pathname_H

#if !defined(__Il_Macros_H)
#  include <ilog/macros.h>
#endif /* !__Il_Macros_H */
#if !defined(__Il_String_H)
#  include <ilog/string.h>
#endif /* !__Il_String_H */

#if defined(IL_STD)
#  include <ctime>
#  if !defined(IL_TIME_T_PREF)
#    if defined(_MSC_VER) && (_MSC_VER < 1300) /* msvc6 || msvc5 */
#      define IL_TIME_T_PREF
#    elif defined(sgi) && defined(_STANDARD_C_PLUS_PLUS)
       // <ctime> seems to be as buggy on sgi as on msvc6
#      define IL_TIME_T_PREF
#    else  /* !(msvc6 || msvc5) */
#      define IL_TIME_T_PREF IL_STDPREF
#    endif /* !(msvc6 || msvc5) */
#  endif /* !IL_TIME_T_PREF */
#else  /* !IL_STD */
#  include <time.h>
#  if !defined(IL_TIME_T_PREF)
#    define IL_TIME_T_PREF
#  endif /* !IL_TIME_T_PREF */
#endif /* !IL_STD */

// --------------------------------------------------------------------------
class ILOG_EXPORTED IlPathName
{
public:
    enum IlPathType {
	SystemPathType   = 0,
	IlSystemPathType = SystemPathType, // For post-5.8 compatibility
	UnixPathType     = 1,
	IlUnixPathType   = UnixPathType,   // For post-5.8 compatibility
	DosPathType,
	IlDosPathType = DosPathType        // For post-5.8 compatibility
    };
    enum SortMode {
	SortNone = 0,
	SortAlphabetically = 1,
	SortCaseInsensitive = 2,
	SortReverse         = 4,
	GroupDirectories    = 8,
	GroupExtensions     = 16
    };
    // *****************************************************************
    //
    // CONSTRUCTORS and DESTRUCTOR.
    //
    // *****************************************************************

    IlPathName();
    IlPathName(const IlString& path);
    IlPathName(const char* path);
    IlPathName(const IlPathName& path);
    ~IlPathName();

    // *****************************************************************
    //
    // ACCESSORS.
    //
    // *****************************************************************

    inline operator IlString() const
	{ return getString(); }

    inline operator const char*() const
	{ return IL_CAST(const char*, getString()); }

    inline IlBoolean operator!() const
	{ return isEmpty(); }
    IlBoolean operator==(const IlPathName& path) const;
    inline IlBoolean operator!=(const IlPathName& path) const
	{ return !(*this == path); }
#if !defined(__BORLANDC__)
    inline IlPathName operator+(const IlPathName& path) const
	{ return IlPathName(*this).merge(path); }
#else /* __BORLANDC__ */
    IlPathName operator+(const IlPathName& path) const;
#endif /* __BORLANDC__ */
#if !defined(__BORLANDC__)
    inline IlPathName operator+(const IlString& path) const
	{ return IlPathName(*this).merge(path); }
#else /* __BORLANDC__ */
    IlPathName operator+(const IlString& path) const;
#endif /* __BORLANDC__ */
#if !defined(__BORLANDC__)
    inline IlPathName operator+(const char* path) const
	{ return IlPathName(*this).merge(IlString(path)); }
#else /* __BORLANDC__ */
    IlPathName operator+(const char* path) const;
#endif /* __BORLANDC__ */

    inline IlString getFileName() const
	{ return _filename; }
    inline IlString getExtension() const
	{ return _extension; }
    IlString getBaseName() const;
    inline IlString getDevice() const
	{ return _device; }
    IlString getDirectory(IlBoolean  finalSep = IlTrue,
			  IlPathType type     = SystemPathType) const;
    IlString getDirName(IlBoolean  finalSep = IlTrue,
			IlPathType type     = SystemPathType) const;
    IlString getString(IlPathType type = SystemPathType) const;
    IlString getTruncatedValue(int level = 2) const;

    inline char* copyFileName() const
	{ return getFileName().copyValue(); }
    inline char* copyExtension() const
	{ return getExtension().copyValue(); }
    inline char* copyBaseName() const
	{ return getBaseName().copyValue(); }
    inline char* copyDevice() const
	{ return getDevice().copyValue(); }
    inline char* copyDirectory(IlBoolean  finalSep = IlTrue,
			       IlPathType type     = SystemPathType) const
	{ return getDirectory(finalSep, type).copyValue(); }
    inline char* copyDirName(IlBoolean  finalSep = IlTrue,
			     IlPathType type     = SystemPathType) const
	{ return getDirName(finalSep, type).copyValue(); }
    inline char* copyValue(IlPathType type = SystemPathType) const
	{ return getString(type).copyValue(); }

    IlString getUnixDirectory(IlBoolean finalSep = IlTrue) const;
    IlString getDosDirectory(IlBoolean finalSep = IlTrue) const;
    IlString getUnixValue() const;
    IlString getDosValue() const;
    IlString get83DosValue() const;
    inline char* copyUnixDirectory(IlBoolean finalSep = IlTrue) const
	{ return getUnixDirectory(finalSep).copyValue(); }
    inline char* copyDosDirectory(IlBoolean finalSep = IlTrue) const
	{ return getDosDirectory(finalSep).copyValue(); }
    inline char* copyUnixValue() const
	{ return getUnixValue().copyValue(); }
    inline char* copyDosValue() const
	{ return getDosValue().copyValue(); }
    inline char* copy83DosValue() const
	{ return get83DosValue().copyValue(); }
    inline IlBoolean isEmpty() const
	{
	    return (!_filename && !_extension && !_directory && !_device)
		    ? IlTrue : IlFalse;
	}
    inline IlBoolean isAbsolute() const
	{
	    return (!_directory.isEmpty() && (_directory.getIndexOf("/")==0)
		   ? IlTrue : IlFalse);
	}
    inline IlBoolean isDirectory() const
	{ return (!_filename && !_extension) ? IlTrue : IlFalse; }

    inline IlBoolean isCurrentDirectory() const
	{ return (isDirectory() && !_directory) ? IlTrue : IlFalse; }

    inline IlBoolean isInCurrentDirectory() const
	{ return (!_directory) ? IlTrue : IlFalse; }
    IlBoolean isSubDirectory(const IlPathName& path) const;
    IlBoolean isSystemDirectory() const;
    IlBoolean isEmptyDirectory() const;
    int computeLevelNumber() const;
    IlString getSubDirectory(IlInt level, IlInt count = 1) const;
    IlBoolean match(const IlPathName& filter) const;
    IlBoolean changeCurrentDirectory() const;
    IlBoolean doesExist() const;
    IlBoolean isReadable() const;
    IlBoolean isWritable() const;
    IlBoolean isExecutable() const;
    IlBoolean isSensitive() const;
    IlBoolean openDir() const;
    IlBoolean readDir(IlPathName& result) const;
    IlBoolean closeDir() const;
    void rewindDir() const;
    IlBoolean create(short mode = -1, IlBoolean recursive = IlTrue) const;
    IlBoolean remove(IlBoolean recursive = IlFalse) const;
    IlBoolean changeMode(short newMode) const;
    IlBoolean queryMode(short& mode) const;
    IlBoolean queryAccessTime(IL_TIME_T_PREF time_t& time) const;
    IlBoolean queryChangedStatusTime(IL_TIME_T_PREF time_t& time) const;
    IlBoolean queryModificationTime(IL_TIME_T_PREF time_t& time) const;
    IlBoolean isNewer(const IlPathName& path) const;

    // *****************************************************************
    //
    // MODIFIERS.
    //
    // *****************************************************************

    inline IlPathName& operator=(const IlPathName& pathname)
	{
	    if (this != &pathname) {
		setDevice(pathname._device);
		setUnixDirectory(pathname.getUnixDirectory());
		setFileName(pathname.getFileName());
		setExtension(pathname.getExtension());
		if (_dirdesc)
		    closeDir();
	    }
	    return *this;
	}
    inline IlPathName& operator=(const IlString& pathname)
	{
	    setValue(pathname);
	    if (_dirdesc)
		closeDir();
	    return *this;
	}
    inline IlPathName& operator=(const char* pathname)
	{
	    setValue(IlString(pathname));
	    if (_dirdesc)
		closeDir();
	    return *this;
	}
    inline IlPathName& operator+=(const IlPathName& path)
	{ return merge(path); }
    inline IlPathName& operator+=(const IlString& path)
	{ return merge(path); }
    inline IlPathName& operator+=(const char* path)
	{ return merge(IlString(path)); }
    inline void setFileName(const IlString&	filename,
			    int			end = -1,
			    int			start = 0)
	{
	    _modified = IlTrue;
	    _filename = filename.getSubString(start, end);
	}

    inline void setExtension(const IlString&	extension,
			     int		end = -1,
			     int		start = 0)
	{
	    _modified = IlTrue;
	    _extension = extension.getSubString(start, end);
	}
    void setBaseName(const IlString& basename, int end = -1, int start = 0);
    void setDevice(const IlString& device, int end = -1, int start = 0);
    void setDirectory(const IlString&	directory,
		      int		end = -1,
		      IlPathType	type = SystemPathType,
		      int		start = 0);
    void addDirectory(const IlString&	directory,
		      int		end = -1,
		      IlPathType	type = SystemPathType,
		      int		start = 0);
    void setDirName(const IlString&	dirName,
		    int			end = -1,
		    IlPathType		type = SystemPathType,
		    int			start = 0);
    void setValue(const IlString&	value,
		  int			end = -1,
		  IlPathType		type = SystemPathType,
		  int			start = 0);

    IlPathName& merge(const IlPathName& path);
    inline IlPathName& merge(const IlString& path)
	{
	    IlPathName temp(path);
	    return merge(temp);
	}
    inline IlPathName& merge(const char* path)
	{
	    IlPathName temp(path);
	    return merge(temp);
	}
    IlPathName& prepend(const IlPathName& path);
    inline IlPathName& prepend(const IlString& path)
	{ IlPathName temp(path); return prepend(temp); }
    inline IlPathName& prepend(const char* path)
	{ IlPathName temp(path); return prepend(temp); }

    // Format specific.
    void setUnixDirectory(const IlString& directory,
			  int end = -1, int start = 0);
    void setDosDirectory(const IlString& directory,
			 int end = -1, int start = 0);
    void addUnixDirectory(const IlString& directory,
			  int end = -1, int start = 0);
    void addDosDirectory(const IlString& directory,
			 int end = -1, int start = 0);
    void setUnixDirName(const IlString& dirName,
			int end = -1, int start = 0);
    void setDosDirName(const IlString& dirName,
		       int end = -1, int start = 0);
    void setUnixValue(const IlString& value, int end = -1, int start = 0);
    void setDosValue(const IlString& value, int end = -1, int start = 0);
    void forceAbsolute();
    void forceRelative();
    void forceDirectory();
    IlPathName& computeSameLeading(const IlPathName& path);
    IlPathName& computeSameTrailing(const IlPathName& path);
    IlPathName& computeDifferLeading(const IlPathName& path);
    IlPathName& computeDifferTrailing(const IlPathName& path);
    IlPathName& computeFirstSubDirectory();
    IlPathName& computeLastSubDirectory();
    IlPathName& computeAllButFirstSubDirectory();
    IlPathName& computeAllButLastSubDirectory();
    IlPathName& computeRelativePath(const IlPathName& path);
    void queryCurrentDirectory(IlString* drive = 0);
    void localize();

    // *****************************************************************
    //
    // STATIC FUNCTIONS.
    //
    // *****************************************************************

    static void QueryCurrentDirectory(char	currentDir[],
				      int	size,
				      IlString* drive = 0);
    static inline IlBoolean doesExist(const IlString& pathname)
	{ return IlPathName(pathname).doesExist(); }
    static inline IlBoolean isReadable(const IlString& pathname)
	{ return IlPathName(pathname).isReadable(); }
    static inline IlBoolean isWritable(const IlString& pathname)
	{ return IlPathName(pathname).isWritable(); }
    static inline IlBoolean isExecutable(const IlString& pathname)
	{ return IlPathName(pathname).isExecutable(); }
    static IlString Localize(const IlString& pathname);
private:
    // Computes the canonical form of the path name.
    // Called every time the directory part of the path name is modified.
    void normalize();
    // Sets the directory part of the path name. Internal path syntax.
    void setInternalDir(const IlString& string, int end = -1, int start = 0);
    // Sets the whole path name. Internal path syntax.
    void setInternalVal(const IlString& string, int end = -1, int start = 0);

    // Private data members.
    IlString		_device;
    IlString		_directory;
    IlString		_filename;
    IlString		_extension;
    IlString		_value;
    IlBoolean		_modified;
    // Used for opendir, readdir, closedir. Should be mutable.
    IL_MUTABLE void*	_dirdesc;
};

#endif /* !__Il_Pathname_H */
