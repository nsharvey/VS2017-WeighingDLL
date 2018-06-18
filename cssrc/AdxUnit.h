// AdxUnit.h
// ---------
// project : Adonix X3 Centrale de Pesee
// author : EP		27/09/01
//--------------------------------------------------------------
//
// Declaration des classes decrivant la table de conversion unite

#if !defined _ADXUNIT_H_
#define _ADXUNIT_H_

class AdxUnit  {
public:
	virtual ~AdxUnit();
	AdxUnit(){init();};

	void setUnite1( const char* str);
	void setUnite2( const char* str);
	void setCoefficient (const double& valeur);

	const char* getUnite1() const { return _unite1;}
	const char* getUnite2() const { return _unite2;}
	const double getCoefficient () const { return _coefficient;}

protected :
// donnees
	char*						_unite1;
	char*						_unite2;
	double						_coefficient;
	
// fonctions
	void init();

private :
	AdxUnit( const AdxUnit& unit);
	const AdxUnit& operator=( const AdxUnit& unit);

};

//ADXANYSTACK( AdxUnit);

#endif /*_ADXUNIT_H_*/