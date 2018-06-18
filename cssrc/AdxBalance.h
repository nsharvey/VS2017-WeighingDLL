// AdxBalance.h
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : EP		15/05/01
//--------------------------------------------------------------
//
// Declaration de la classe decrivant les balances

#if !defined _ADXBALANCE_H_
#define _ADXBALANCE_H_

#include "AdxDate.h"

class AdxBalance  {
  // CTOR - DTOR
public:
	virtual ~AdxBalance();
	AdxBalance(){init();};

	void setBalance( const char* str);
	void setLibBalance( const char* str);
	void setPort( const long& value);
	void setPilote( const char* str);
	void setNbEntiers( const long& value);
	void setNbDecimales( const long& value);
	void setSeparateur( const char* str);
	void setLibSeparateur( const char* str);
	void setConsigne (const bool value);
	void setUnite( const char* str);
	void setPorteeMini( const double& value);
	void setPorteeMaxi( const double& value);
	void setTareMaxi( const double& value);
	void setTolerance( const double& value);
	void setCodeCalibrage( const long& value);
	void setLibCalibrage( const char* str);
	void setGuideCalibrage( const char* str);
	void setNbJours( const long& value);
	void setNbPesees( const long& value);
	void setCodeDispo( const long& value);
	void setLibCodeDispo( const char* str);
	void setDateDernierCalibrage( AdxDate* date);
	void setNbPeseesCalibrage( const long& value);
	void setEtiquetteCalibrage( const char* str);
	void setVitesse(const int& value);
	void setParite(const int& value);
	void setStopBit(const int& value);
	void setFormat(const int& value);
	void setTempo(const long& value);   // sr 02.03 g�rer la tempo

	void setEtalonnee( const bool b);
	void setConnecte( const long& value);
	void setNoDriver( const long& value);
	void setSerialNumber( const char* str);
    void setKeyRazSca(const char* str);		//114545 mm 09.2016
    void setKeyTarSca(const char* str);		//114545 mm 09.2016	

	const char* getBalance ()const{ return _balance;}
	const char* getLibBalance ()const{ return _libBalance;}
	const long getPort ()const{ return _port;}
	const char* getPilote ()const{ return _pilote;}
	const long getNbEntiers ()const{ return _nbEntiers;}
	const long getNbDecimales ()const{ return _nbDecimales;}
	const char* getSeparateur ()const{ return _separateur;}
	const char* getLibSeparateur ()const{ return _libSeparateur;}
	const bool getConsigne ()const{ return _consigne;}
	const char* getUnite ()const{ return _unite;}
	const double getPorteeMini ()const{ return _porteeMini;}
	const double getPorteeMaxi ()const{ return _porteeMaxi;}
	const double getTareMaxi ()const{ return _tareMaxi;}
	const double getTolerance ()const{ return _tolerance;}
	const long getCodeCalibrage ()const{ return _codeCalibrage;}
	const char* getLibCalibrage ()const{ return _libCalibrage;}
	const char* getGuideCalibrage ()const{ return _guideCalibrage;}
	const long getNbJours ()const{ return _nbJours;}
	const long getNbPesees ()const{ return _nbPesees;}
	const long getCodeDispo ()const{ return _codeDispo;}
	const char* getLibCodeDispo ()const{ return _libCodeDispo;}
	AdxDate* getDateDernierCalibrage() const { return _dateDernierCalibrage;}
	const long getNbPeseesCalibrage ()const{ return _nbPeseesCalibrage;}
	const char* getEtiquetteCalibrage ()const{ return _etiquetteCalibrage;}
	const int getVitesse() const{return _vitesse;}
	const int getParite() const{return _parite;}
	const int getStopBit() const{return _stopBit;}
	const int getFormat() const{return _format;}
	const long getTempo ()const{ return _tempo;}
	
	const bool getEtalonnee ()const{ return _etalonnee;}
	const long getConnecte ()const{ return _connecte;}
	const long getNoDriver ()const{ return _noDriver;}
	const char* getSerialNumber ()const{ return _serialNumber;}
	const char* getKeyRazSca() const {return _keyRazSca;}	//114545 mm 09.2016
	const char* getKeyTarSca() const {return _keyTarSca;}	//114545 mm 09.2016

	void setMultiPlate(bool value);
	bool IsMultiPlate();
	void setPlateIndex(short value);
	short getPlateIndex();
	// Changement de plateau
	bool getMultiPlateOK()
	{
		return _bMultiPlateOK;
	}
	void setMultiPlateOK(bool value)
	{
		_bMultiPlateOK = value;
	}

protected :
// donnees
	char*						_balance;
	char*						_libBalance;
	long						_port;
	char*						_pilote;
	long						_nbEntiers;
	long						_nbDecimales;
	char*						_separateur;
	char*						_libSeparateur;
	bool						_consigne;
	char*						_unite;
	double						_porteeMini;
	double						_porteeMaxi;
	double						_tareMaxi;
	double						_tolerance;
	long						_codeCalibrage;
	// 1 pas d'etalonnage
	// 2 etalonnage au nombre de jours
	// 3 etalonnage au nombre de pesees
	// 4 etalonnage aux nombres de jours et de pesees
	// 5 etalonnage a chaque pesee
	char*						_libCalibrage;
	char*						_guideCalibrage;
	long						_nbJours;
	long						_nbPesees;
	long						_codeDispo;
	char*						_libCodeDispo;
	AdxDate*					_dateDernierCalibrage;
	long						_nbPeseesCalibrage;
	char*						_etiquetteCalibrage;
	int							_vitesse;
	int							_parite;
	int							_stopBit;
	int							_format;
	long						_tempo;

	bool						_etalonnee;
	long						_connecte;
	long						_noDriver;
	// Ajout du num�ro de s�rie
	char*						_serialNumber;
	// Prise en compte des codes touche cmd K des balances Mettler, protocole SICS
	//114545 mm 09.2016
	char*						_keyTarSca;
	char*						_keyRazSca;

	// Gestion du multi plateau
	bool						_bMultiPlate;
	short						_plateIndex;
	// Gestion multi plateaux
	bool	 _bMultiPlateOK;    // Changement de plateau OK
	
// fonctions
	void init();

private :
	AdxBalance( const AdxBalance& balance);
};

#endif /*_ADXBALANCE_H_*/