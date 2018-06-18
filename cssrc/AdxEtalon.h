// AdxEtalon.h
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : SR		30/11/01
//--------------------------------------------------------------
//
// Declaration de la classe decrivant les guides etalonnage entete

#if !defined _ADXETALON_H_
#define _ADXETALON_H_

#include "AdxDate.h"
#include "AdxEtalonLigne.h"

class AdxEtalon  {
  // CTOR - DTOR
public:
	virtual ~AdxEtalon();
	AdxEtalon(){init();};

	void setEtalon( const char* str);
	void setLibEtalon( const char* str);
	void setCurrentEtalonLigneIndex(unsigned long index);
	void setNbLignes( const long& value);
	void setNbLignesValidees( const long& value);
	void setNbLignesEffectuees( const long& value);
	void setTotalementEtalonne(const bool b);

	const char*  getEtalon ()const{ return _etalon;}
	const char*  getLibEtalon ()const{ return _libEtalon;}
	const long   getNbLignes ()const{ return _nbLignes;}
	const long   getNbLignesValidees ()const{ return _nbLignesValidees;}
	const long   getNbLignesEffectuees ()const{ return _nbLignesEffectuees;}
	bool getTotalementEtalonne() const {return _totalementEtalonne;}
	// je récupère l'objet correspondant à la ligne courante
	AdxEtalonLigne* getCurrentEtalonLigne() const {return _currentEtalonLigne;}
	// je récupère l'index de la ligne courante
	int	getCurrentEtalonLigneIndex() const{return _currentEtalonLigneIndex;}
//	int getIndexEtalonLigne(const char* etalonLigne);

	// acces liste des lignes etalonnage
	IlList* getEtalonLigneList() const {return _etalonLigneList;}
	AdxEtalonLigne* getEtalonLigne(unsigned int index) const {
				AdxEtalonLigne* etalonLigne = (AdxEtalonLigne*)(*_etalonLigneList)[index];
				return etalonLigne;}


protected :
// donnees
	char*						_etalon;
	char*						_libEtalon;
	IlList*						_etalonLigneList;
	long						_nbLignes;
	long						_nbLignesValidees;
	long						_nbLignesEffectuees;
	bool						_totalementEtalonne;

	AdxEtalonLigne*				_currentEtalonLigne;
//position de la ligne courante dans la liste de l'etalon courant
	unsigned long				_currentEtalonLigneIndex;
	
// fonctions
	void init();

private :

	AdxEtalon( const AdxEtalon& etalon);
	const AdxEtalon& operator=( const AdxEtalon& etalon);
};

#endif /*_ADXETALON_H_*/