// AdxEtalonligne.h
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : SR		30/11/01
//--------------------------------------------------------------
//
// Declaration de la classe decrivant les guides etalonnage lignes

#if !defined _ADXETALONLIGNE_H_
#define _ADXETALONLIGNE_H_

class AdxEtalon;

class AdxEtalonLigne  {
  // CTOR - DTOR
public:
	virtual ~AdxEtalonLigne();
	AdxEtalonLigne(){init();};

	void setEtalon( AdxEtalon* etalon);
	void setLigne( const long& value);
	void setPoids( const double& value);
	void setUnite( const char* str);
	void setNbPesees( const long& value);
	void setTypPesee( const long& value);
	void setLibTypPesee( const char* str);
	void setTolerance( const double& value);
	void setEcartMaxi( const double& value);
	void setPoidsPese( const double& value);
	void setDecimalePoids( const int s);
	void setFormat( const char* str);
	void setNbPeseesOk( const long& value);
	void setNbPeseesEffectuees( const long& value);
	void setPeseeEffectuee( const bool be);
	void setPeseeValidee( const bool bv);
	void setArrPoidsPese(const int index,const double& value);

	const AdxEtalon*  getEtalon ()const{ return _etalon;}
	const long   getLigne ()const{ return _ligne;}
	const double getPoids ()const{ return _poids;}
	const char*  getUnite ()const{ return _unite;}
	const long   getNbPesees ()const{ return _nbPesees;}
	const long   getTypPesee ()const{ return _typPesee;}
	const char*  getLibTypPesee ()const{ return _libTypPesee;}
	const double getTolerance ()const{ return _tolerance;}
	const double getEcartMaxi ()const{ return _ecartMaxi;}
	const double getPoidsPese ()const{ return _poidsPese;}
//	const char* getEtalonLigne() const { return _etalonLigne;}
	const int getDecimalePoids() const { return _decimalePoids;}
	const char* getFormat() const { return _format;}
	const long   getNbPeseesOk ()const{ return _nbPeseesOk;}
	const long   getNbPeseesEffectuees ()const{ return _nbPeseesEffectuees;}
	const double getArrPoidsPese(unsigned int index)const{ return _arrPoidsPese[index];}
	
	bool getPeseeEffectuee() const {return _peseeEffectuee;}
	bool getPeseeValidee() const {return _peseeValidee;}

//  Tableau des poids peses
	double*						_arrPoidsPese;

protected :
// donnees
//	char*						_etalonLigne;
	AdxEtalon*					_etalon;
	long						_ligne;
	double						_poids;
	char*						_unite;
	long						_nbPesees;
	long						_typPesee;
	char*						_libTypPesee;
	double						_tolerance;
	int							_decimalePoids;
	double						_poidsPese;
	char*						_format;
	long						_nbPeseesEffectuees;
	long						_nbPeseesOk;
	double						_ecartMaxi;



	bool						_peseeEffectuee;
	bool						_peseeValidee;	

	
// fonctions
	void init();

private :

	AdxEtalonLigne( const AdxEtalonLigne& etalonLigne);
};

#endif /*_ADXETALONLIGNE_H_*/