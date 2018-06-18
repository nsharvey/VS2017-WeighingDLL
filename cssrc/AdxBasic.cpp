// AdxBasic.cpp
// ------------
// project : Adonix X3 Optimisation
// author : ILOG SCM Consulting 1999.12.08
//--------------------------------------------------------------
//

#include "stdafx.h"
#include <cstdlib>

#include "AdxDate.h"
#include "AdxBasic.h"

using std::flush;

AdxBasic::AdxBasic() :
	_extractDate	( NULL)
{}

AdxBasic::~AdxBasic() {
	if( _extractDate != NULL)
		delete _extractDate;
}

void AdxBasic::display( ostream& os) const{
	const char* const SEP = "\t";
	if( getExtractDate() != NULL) {
		os<<(*getExtractDate())<<SEP<<flush;
	}
}

ostream& operator<<( ostream& os, const AdxBasic& basic) {
	basic.display( os);
	return os;
}