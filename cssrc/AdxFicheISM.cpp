// AdxFicheISM.cpp
// ---------------
// project : Adonix X3 Centrale de Pesee
// author : EP		15/05/01
//--------------------------------------------------------------
//
// Declaration de la classe decrivant les fiches ISM

#include "stdafx.h"
#include "AdxFicheISM.h"
#include <string.h>

AdxFicheISM::~AdxFicheISM()
{
	if( _ficheISM != 0)
		delete [] _ficheISM;
	if( _melangeLotLib != 0)
		delete [] _melangeLotLib;
	if( _controlePeseurLib != 0)
		delete [] _controlePeseurLib;
	if( _controleQualiteLib != 0)
		delete [] _controleQualiteLib;
	if( _codeEmballageLib != 0)
		delete [] _codeEmballageLib;
	if( _modePeseeLib != 0)
		delete [] _modePeseeLib;
	if( _precaution1 != 0)
		delete [] _precaution1;
	if( _pictogramme1 != 0)
		delete [] _pictogramme1;
	if( _precaution2 != 0)
		delete [] _precaution2;
	if( _pictogramme2 != 0)
		delete [] _pictogramme2;
	if( _precaution3 != 0)
		delete [] _precaution3;
	if( _pictogramme3 != 0)
		delete [] _pictogramme3;
	if( _precaution4 != 0)
		delete [] _precaution4;
	if( _pictogramme4 != 0)
		delete [] _pictogramme4;
	if( _precaution5 != 0)
		delete [] _precaution5;
	if( _pictogramme5 != 0)
		delete [] _pictogramme5;
	if( _precaution6 != 0)
		delete [] _precaution6;
	if( _pictogramme6 != 0)
		delete [] _pictogramme6;
	if( _precaution7 != 0)
		delete [] _precaution7;
	if( _pictogramme7 != 0)
		delete [] _pictogramme7;
	if( _precaution8 != 0)
		delete [] _precaution8;
	if( _pictogramme8 != 0)
		delete [] _pictogramme8;
	if( _codeToxicite1 != 0)
		delete [] _codeToxicite1;
	if( _pictogramme9 != 0)
		delete [] _pictogramme9;
	if( _codeToxicite2 != 0)
		delete [] _codeToxicite2;
	if( _pictogramme10 != 0)
		delete [] _pictogramme10;
	if( _codeToxicite3 != 0)
		delete [] _codeToxicite3;
	if( _pictogramme11 != 0)
		delete [] _pictogramme11;
	if( _codeToxicite4 != 0)
		delete [] _codeToxicite4;
	if( _pictogramme12 != 0)
		delete [] _pictogramme12;
	if( _contenuEtiquette != 0)
		delete [] _contenuEtiquette;
}

void AdxFicheISM::setFicheISM( const char* str)
{ 
		if( _ficheISM != 0) {
			delete [] _ficheISM;
		}
		_ficheISM = new char[ strlen( str) +1];
		strcpy( _ficheISM, str);
}

void AdxFicheISM::setMelangeLotCode( const long& value)
{
		_melangeLotCode = value;
}

void AdxFicheISM::setMelangeLotLib( const char* str)
{ 
		if( _melangeLotLib != 0) {
			delete [] _melangeLotLib;
		}
		_melangeLotLib = new char[ strlen( str) +1];
		strcpy( _melangeLotLib, str);
}

void AdxFicheISM::setControlePeseurCode( const long& value)
{
		_controlePeseurCode = value;
}

void AdxFicheISM::setControlePeseurLib( const char* str)
{ 
		if( _controlePeseurLib != 0) {
			delete [] _controlePeseurLib;
		}
		_controlePeseurLib = new char[ strlen( str) +1];
		strcpy( _controlePeseurLib, str);
}

void AdxFicheISM::setControleQualiteCode( const long& value)
{
		_controleQualiteCode = value;
}

void AdxFicheISM::setControleQualiteLib( const char* str)
{ 
		if( _controleQualiteLib != 0) {
			delete [] _controleQualiteLib;
		}
		_controleQualiteLib = new char[ strlen( str) +1];
		strcpy( _controleQualiteLib, str);
}

void AdxFicheISM::setCodeEmballage( const int& value)
{
		_codeEmballage = value;
}

void AdxFicheISM::setCodeEmballageLib( const char* str)
{ 
		if( _codeEmballageLib != 0) {
			delete [] _codeEmballageLib;
		}
		_codeEmballageLib = new char[ strlen( str) +1];
		strcpy( _codeEmballageLib, str);
}

void AdxFicheISM::setSoldeEmballage( const double& value)
{
		_soldeEmballage = value;
}

void AdxFicheISM::setModePeseeCode( const long& value)
{
		_modePeseeCode = value;
}

void AdxFicheISM::setModePeseeLib( const char* str)
{ 
		if( _modePeseeLib != 0) {
			delete [] _modePeseeLib;
		}
		_modePeseeLib = new char[ strlen( str) +1];
		strcpy( _modePeseeLib, str);
}

//06.07 mm - Forcer la lecture d'une icône
void AdxFicheISM::setMessageObligatoire( const int& value)
{
	_messageObligatoire = value ;
}

void AdxFicheISM::setRedressementManuel( const long& value)
{
	_redressementManuel = value;
}

//08.11 mm - Pesée multi-article
void AdxFicheISM::setPeseeMultiArticle( const long& value)
{
	_peseeMultiArticle = value;
}

void AdxFicheISM::setPrecaution1( const char* str)
{ 
		if( _precaution1 != 0) {
			delete [] _precaution1;
		}
		_precaution1 = new char[ strlen( str) +1];
		strcpy( _precaution1, str);
}

void AdxFicheISM::setPictogramme1( const char* str)
{ 
		if( _pictogramme1 != 0) {
			delete [] _pictogramme1;
		}
		_pictogramme1 = new char[ strlen( str) +1];
		strcpy( _pictogramme1, str);
}

void AdxFicheISM::setPrecaution2( const char* str)
{ 
		if( _precaution2 != 0) {
			delete [] _precaution2;
		}
		_precaution2 = new char[ strlen( str) +1];
		strcpy( _precaution2, str);
}

void AdxFicheISM::setPictogramme2( const char* str)
{ 
		if( _pictogramme2 != 0) {
			delete [] _pictogramme2;
		}
		_pictogramme2 = new char[ strlen( str) +1];
		strcpy( _pictogramme2, str);
}

void AdxFicheISM::setPrecaution3( const char* str)
{ 
		if( _precaution3 != 0) {
			delete [] _precaution3;
		}
		_precaution3 = new char[ strlen( str) +1];
		strcpy( _precaution3, str);
}

void AdxFicheISM::setPictogramme3( const char* str)
{ 
		if( _pictogramme3 != 0) {
			delete [] _pictogramme3;
		}
		_pictogramme3 = new char[ strlen( str) +1];
		strcpy( _pictogramme3, str);
}

void AdxFicheISM::setPrecaution4( const char* str)
{ 
		if( _precaution4 != 0) {
			delete [] _precaution4;
		}
		_precaution4 = new char[ strlen( str) +1];
		strcpy( _precaution4, str);
}

void AdxFicheISM::setPictogramme4( const char* str)
{ 
		if( _pictogramme4 != 0) {
			delete [] _pictogramme4;
		}
		_pictogramme4 = new char[ strlen( str) +1];
		strcpy( _pictogramme4, str);
}

void AdxFicheISM::setPrecaution5( const char* str)
{ 
		if( _precaution5 != 0) {
			delete [] _precaution5;
		}
		_precaution5 = new char[ strlen( str) +1];
		strcpy( _precaution5, str);
}

void AdxFicheISM::setPictogramme5( const char* str)
{ 
		if( _pictogramme5 != 0) {
			delete [] _pictogramme5;
		}
		_pictogramme5 = new char[ strlen( str) +1];
		strcpy( _pictogramme5, str);
}

void AdxFicheISM::setPrecaution6( const char* str)
{ 
		if( _precaution6 != 0) {
			delete [] _precaution6;
		}
		_precaution6 = new char[ strlen( str) +1];
		strcpy( _precaution6, str);
}

void AdxFicheISM::setPictogramme6( const char* str)
{ 
		if( _pictogramme6 != 0) {
			delete [] _pictogramme6;
		}
		_pictogramme6 = new char[ strlen( str) +1];
		strcpy( _pictogramme6, str);
}

void AdxFicheISM::setPrecaution7( const char* str)
{ 
		if( _precaution7 != 0) {
			delete [] _precaution7;
		}
		_precaution7 = new char[ strlen( str) +1];
		strcpy( _precaution7, str);
}

void AdxFicheISM::setPictogramme7( const char* str)
{ 
		if( _pictogramme7 != 0) {
			delete [] _pictogramme7;
		}
		_pictogramme7 = new char[ strlen( str) +1];
		strcpy( _pictogramme7, str);
}

void AdxFicheISM::setPrecaution8( const char* str)
{ 
		if( _precaution8 != 0) {
			delete [] _precaution8;
		}
		_precaution8 = new char[ strlen( str) +1];
		strcpy( _precaution8, str);
}

void AdxFicheISM::setPictogramme8( const char* str)
{ 
		if( _pictogramme8 != 0) {
			delete [] _pictogramme8;
		}
		_pictogramme8 = new char[ strlen( str) +1];
		strcpy( _pictogramme8, str);
}

void AdxFicheISM::setCodeToxicite1( const char* str)
{ 
		if( _codeToxicite1 != 0) {
			delete [] _codeToxicite1;
		}
		_codeToxicite1 = new char[ strlen( str) +1];
		strcpy( _codeToxicite1, str);
}

void AdxFicheISM::setPictogramme9( const char* str)
{ 
		if( _pictogramme9 != 0) {
			delete [] _pictogramme9;
		}
		_pictogramme9 = new char[ strlen( str) +1];
		strcpy( _pictogramme9, str);
}

void AdxFicheISM::setCodeToxicite2( const char* str)
{ 
		if( _codeToxicite2 != 0) {
			delete [] _codeToxicite2;
		}
		_codeToxicite2 = new char[ strlen( str) +1];
		strcpy( _codeToxicite2, str);
}

void AdxFicheISM::setPictogramme10( const char* str)
{ 
		if( _pictogramme10 != 0) {
			delete [] _pictogramme10;
		}
		_pictogramme10 = new char[ strlen( str) +1];
		strcpy( _pictogramme10, str);
}

void AdxFicheISM::setCodeToxicite3( const char* str)
{ 
		if( _codeToxicite3 != 0) {
			delete [] _codeToxicite3;
		}
		_codeToxicite3 = new char[ strlen( str) +1];
		strcpy( _codeToxicite3, str);
}

void AdxFicheISM::setPictogramme11( const char* str)
{ 
		if( _pictogramme11 != 0) {
			delete [] _pictogramme11;
		}
		_pictogramme11 = new char[ strlen( str) +1];
		strcpy( _pictogramme11, str);
}

void AdxFicheISM::setCodeToxicite4( const char* str)
{ 
		if( _codeToxicite4 != 0) {
			delete [] _codeToxicite4;
		}
		_codeToxicite4 = new char[ strlen( str) +1];
		strcpy( _codeToxicite4, str);
}

void AdxFicheISM::setPictogramme12( const char* str)
{ 
		if( _pictogramme12 != 0) {
			delete [] _pictogramme12;
		}
		_pictogramme12 = new char[ strlen( str) +1];
		strcpy( _pictogramme12, str);
}

void AdxFicheISM::setContenuEtiquette( const char* str)
{ 
		if( _contenuEtiquette != 0) {
			delete [] _contenuEtiquette;
		}
		_contenuEtiquette = new char[ strlen( str) +1];
		strcpy( _contenuEtiquette, str);
}


//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
void AdxFicheISM::init()
{
	_ficheISM = NULL;
	_melangeLotCode = 0;
	_melangeLotLib = NULL;
	_controlePeseurCode = 0;
	_controlePeseurLib = NULL;
	_controleQualiteCode = 0;
	_controleQualiteLib = NULL;
	_codeEmballage = 0;
	_codeEmballageLib = NULL;
	_soldeEmballage = 0.0;
    _modePeseeCode = 0;
	_modePeseeLib = NULL;
	_messageObligatoire = 0 ;			// 06.07 mm - Forcer la lecture d'une icône
	_precaution1 = NULL;
	_pictogramme1 = NULL;
	_precaution2 = NULL;
	_pictogramme2 = NULL;
	_precaution3 = NULL;
	_pictogramme3 = NULL;
	_precaution4 = NULL;
	_pictogramme4 = NULL;
	_precaution5 = NULL;
	_pictogramme5 = NULL;
	_precaution6 = NULL;
	_pictogramme6 = NULL;
	_precaution7 = NULL;
	_pictogramme7 = NULL;
	_precaution8 = NULL;
	_pictogramme8 = NULL;
	_codeToxicite1 = NULL;
	_pictogramme9 = NULL;
	_codeToxicite2 = NULL;
	_pictogramme10 = NULL;
	_codeToxicite3 = NULL;
	_pictogramme11 = NULL;
	_codeToxicite4 = NULL;
	_pictogramme12 = NULL;
	_contenuEtiquette = NULL;
    _redressementManuel = 0;
	_peseeMultiArticle = 0;
}
