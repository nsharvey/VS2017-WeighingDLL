// AdxUnit.cpp
// -----------
// project : Adonix X3 Centrale de Pesee
// author : EP		27/09/01
//--------------------------------------------------------------
//
// Declaration des classes decrivant la table des conversion unite

#include "stdafx.h"
#include "AdxUnit.h"
#include <string.h>

//---------------------------------------------------------------------------
AdxUnit::~AdxUnit()
{
	if( _unite1 != 0)
		delete [] _unite1;
	if( _unite2 != 0)
		delete  [] _unite2;
}

//---------------------------------------------------------------------------
void AdxUnit::setUnite1( const char* str) 
{ 
	if( _unite1 != 0) {
		delete [] _unite1;
	}
	_unite1 = new char[ strlen( str) +1];
	strcpy( _unite1, str);
}

//---------------------------------------------------------------------------
void AdxUnit::setUnite2( const char* str) 
{ 
	if( _unite2 != 0) {
		delete [] _unite2;
	}
	_unite2 = new char[ strlen( str) +1];
	strcpy( _unite2, str);
}

//---------------------------------------------------------------------------
void AdxUnit::setCoefficient (const double& valeur)
{
	_coefficient = valeur;
}

//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
//---------------------------------------------------------------------------
void AdxUnit::init()
{
	_unite1	= NULL;
	_unite2 = NULL;
	_coefficient = 0;
}
/*
//---------------------------------------------------------------------------
const AdxUnit& AdxUnit::operator=( const AdxUnit& unit)
{
	setUnite1(unit._unite1);
	setUnite2(unit._unite2);
	setCoefficient(unit._coefficient);
	return *this;
}
*/