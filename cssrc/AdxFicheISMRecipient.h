// AdxFicheISMRecipient.h
// ----------------------
// project : Adonix X3 Centrale de Pesee
// author : EP		15/05/01
//--------------------------------------------------------------
//
// Declaration de la classe decrivant les fiches ISM recipient

#if !defined _ADXFICHEISMRECIPIENT_H_
#define _ADXFICHEISMRECIPIENT_H_

//#include "AdxDate.h"

class AdxFicheISMRecipient  {
  // CTOR - DTOR
public:
	virtual ~AdxFicheISMRecipient();
	AdxFicheISMRecipient(){init();};

	void setFicheISMRecipient( const char* str);
	void setRecipient( const char* str);
	void setUnitePoids( const char* str);
	void setPoidsMaxi( const double& value);

	void setLibRecipient( const char* str);
	void setTypeRecipient( const int& value);
	void setLibTypeRecipient( const char* str);
	void setTareTheo( const double& value);
	void setToleranceTare( const double& value);
	void setUnite2( const char* str);
	void setGuideOperateur( const char* str);
	void setFormatEtiquette( const char* str);
	void setTareModifiable(const int& value);	// 04.07 gestion d'une tare modifiable 
	void setSaisiePoids(const int& value);  // 10.07 pesee en mode degrade selon la valeur de saisie Poids

	const char* getFicheISMRecipient ()const{ return _ficheISMRecipient;}
	const char* getRecipient ()const{ return _recipient;}
	const char* getUnitePoids ()const{ return _unitePoids;}
	const double getPoidsMaxi ()const{ return _poidsMaxi;}

	const char* getLibRecipient ()const{ return _libRecipient;}
	const int getTypeRecipient ()const{ return _typeRecipient;}
	const char* getLibTypeRecipient ()const{ return _libTypeRecipient;}
	const double getTareTheo ()const{ return _tareTheo;}
	const double getToleranceTare ()const{ return _toleranceTare;}
	const char* getUnite2 ()const{ return _unite2;}
	const char* getGuideOperateur ()const{ return _guideOperateur;}
	const char* getFormatEtiquette ()const{ return _formatEtiquette;}
	const int getTareModifiable ()const{ return _tareModifiable ;}	// 04.07 gestion d'une tare modifiable 
	const int getSaisiePoids ()const{return _saisiePoids ;} // 10.07 pesee en mode degrade selon la valeur de saisie Poids 

protected :
// donnees
	char*						_ficheISMRecipient;
	char*						_recipient;
	char*						_unitePoids;
	double						_poidsMaxi;

	char*						_libRecipient;
	int  						_typeRecipient;
	char*						_libTypeRecipient;
	double						_tareTheo;
	double						_toleranceTare;
	char*						_unite2;
	char*						_guideOperateur;
	char*						_formatEtiquette;
	int							_tareModifiable;	// 04.07 gestion d'une tare modifiable 
	int							_saisiePoids;		// 10.07 saisie poids 
	
// fonctions
	void init();

private :
	AdxFicheISMRecipient( const AdxFicheISMRecipient& ficheISMRecipient);
};

#endif /*_ADXFICHEISMRECIPIENT_H_*/