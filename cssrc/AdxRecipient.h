// AdxRecipient.h
// --------------
// project : Adonix X3 Centrale de Pesee
// author : EP		15/05/01
//--------------------------------------------------------------
//
// Declaration de la classe decrivant les recipients

#if !defined _ADXRECIPIENT_H_
#define _ADXRECIPIENT_H_

#include <ilog\list.h>
//#include "AdxDate.h"

class AdxRecipient  {
public:
	virtual ~AdxRecipient();
	AdxRecipient(){init();};

	void setRecipient( const char* str);
	void setLibRecipient( const char* str);
	void setUnitePoids( const char* str);
	void setPoidsMaxi( const double& value);

	void setTypeRecipient( const int& value);
	void setLibTypeRecipient( const char* str);
	void setTareTheo( const double& value);
	void setTareTheoSvg( const double& value);		// 02.09 Sauvegarde de la tare theo	
	void setTolerance( const double& value);
	void setGuideOperateur( const char* str);
	void setFormatEtiquette( const char* str);
	void setNbBalances( const int value);
	void setTareModifiable( const int& value );		// 04.07 gestion d'une tare modifiable
	void setSaisiePoids( const int& value );		// 10.07 pesee en mode degrade selon la valeur de saisie Poids	
	void chargementBalance();

	const char* getRecipient ()const{ return _recipient;}
	const char* getLibRecipient ()const{ return _libRecipient;}
	const char* getUnitePoids ()const{ return _unitePoids;}
	const double getPoidsMaxi ()const{ return _poidsMaxi;}
	const int getTypeRecipient ()const{ return _typeRecipient;}
	const char* getLibTypeRecipient ()const{ return _libTypeRecipient;}
	const double getTareTheo ()const{ return _tareTheo;}
	const double getTareTheoSvg ()const{ return _tareTheoSvg;}
	const double getTolerance ()const{ return _tolerance;}
	const char* getGuideOperateur ()const{ return _guideOperateur;}
	const char* getFormatEtiquette ()const{ return _formatEtiquette;}
	const int getTareModifiable ()const{ return _tareModifiable;}	// 04.07 gestion d'une tare modifiable
	const int getSaisiePoids ()const{ return _saisiePoids;} // 10.07 pesee en mode degrade selon la valeur de saisie Poids
	const int getNbBalances()const{return _nbBalances;}

	IlList* getBalanceList() const {return _balanceList;}

protected :
// donnees
	char*						_recipient;
	char*						_libRecipient;
	char*						_unitePoids;
	double						_poidsMaxi;
	int  						_typeRecipient;
	char*						_libTypeRecipient;
	double						_tareTheo;
	double						_tareTheoSvg;		// 02.09 Sauvegarde de la tare theo, sinon écrasée par tare saisie
	double						_tolerance;
	char*						_guideOperateur;
	char*						_formatEtiquette;

	IlList*						_balanceList;
	int							_nbBalances;
	int							_tareModifiable;	// 04.07 gestion d'une tare modifiable
	int							_saisiePoids;		// 10.07 pesee en mode degrade selon la valeur de saisie Poids

// fonctions
	void init();

private :
	AdxRecipient( const AdxRecipient& recipient);
};

#endif /*_ADXRECIPIENT_H_*/