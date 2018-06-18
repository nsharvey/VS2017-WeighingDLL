// AdxEtalon.cpp
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : SR		30/11/01
//--------------------------------------------------------------
//
// Declaration de la classe decrivant les guides etalonnage

#include "stdafx.h"
#include "AdxEtalon.h"
#include <string.h>


AdxEtalon::~AdxEtalon()
{
	if( _etalon != 0)
		delete [] _etalon;
	if( _libEtalon != 0)
		delete [] _libEtalon;
	if(_etalonLigneList != NULL)
	{
		for (int i = 0; i < _etalonLigneList->length(); i++)
		{
			delete (AdxEtalonLigne*)(*_etalonLigneList)[i];
		}
		_etalonLigneList->empty();
		delete _etalonLigneList;
	}
}

void AdxEtalon::setEtalon( const char* str)
{ 
	if( _etalon != 0) {
		delete [] _etalon;
	}
	_etalon = new char[ strlen( str) +1];
	strcpy( _etalon, str);
}

void AdxEtalon::setLibEtalon( const char* str)
{ 
	if( _libEtalon != 0) {
		delete [] _libEtalon;
	}
	_libEtalon = new char[ strlen( str) +1];
	strcpy( _libEtalon, str);
}

//---------------------------------------------------------------------------
void AdxEtalon::setNbLignes( const long& value)
{
	_nbLignes = value;
}

//---------------------------------------------------------------------------
void AdxEtalon::setNbLignesValidees( const long& nb)
{
	_nbLignesValidees = nb;
}

//---------------------------------------------------------------------------
void AdxEtalon::setNbLignesEffectuees( const long& nb)
{
	_nbLignesEffectuees = nb;
}

//---------------------------------------------------------------------------
void AdxEtalon::setTotalementEtalonne( const bool b)
{
	_totalementEtalonne = b;
}

//--------------------------------------------------------------
// prend en parametre l'index dans la table etalon->getEtalonLigneList()
void AdxEtalon::setCurrentEtalonLigneIndex(unsigned long index)
{
	_currentEtalonLigne = getEtalonLigne(index);
	_currentEtalonLigneIndex = index;
}


//---------------------------------------------------------------------------
/*int AdxEtalon::getIndexEtalonLigne(const char* etalonLigne)
{
	int i=0;
	while (i < getNbLignes())
	{
		if (strcmp(etalonLigne, getEtalonLigne(i)->getEtalonLigne()) == 0)
			return i;
		i++;
	}
	return _nbLignes;
}*/
//--------------------------------------------------------------
// Protected
//--------------------------------------------------------------
void AdxEtalon::init()
{
	_etalon = NULL;
	_libEtalon = NULL;
	_etalonLigneList = new IlList;
	_nbLignes = 0;
	_totalementEtalonne = false;
}
