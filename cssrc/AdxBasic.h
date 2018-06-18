// AdxBasic.h
// ----------
// project : Adonix X3 Optimisation
// author : ILOG SCM Consulting 1999.12.08
//--------------------------------------------------------------
//

#if !defined _AdxBasic_h_
#define _AdxBasic_h_

#include <iostream>

using std::ostream;

class AdxDate;

class AdxBasic {

//----------------------------------------------------------
//	
// Properties
//
protected:
	// EXTDAT for all
	AdxDate* _extractDate;	

//----------------------------------------------------------
//	
// CTOR - DTOR
//
public: 

	virtual ~AdxBasic();
	AdxBasic();

//----------------------------------------------------------
//	
// display
//
public:

	virtual void display( ostream& os) const;
//----------------------------------------------------------
//
// operators
//
public:

	friend ostream& operator<<( ostream& os, const AdxBasic& basic);

//----------------------------------------------------------
//	
// accessors & modifiers
//
public:
	
	AdxDate* getExtractDate() const {
		return _extractDate;
	}

protected:
	
	void setExtractDate( AdxDate* date) {
		_extractDate = date;
	}

//----------------------------------------------------------
//	
// undefined methods
//
private:

	AdxBasic( const AdxBasic& value);
	const AdxBasic& operator=( const AdxBasic& value);
};

#endif /*_AdxBasic_h_*/