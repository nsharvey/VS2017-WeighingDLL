// AdxFicheISM.h
// --------------
// project : Adonix X3 Centrale de Pesee
// author : EP		15/05/01
//--------------------------------------------------------------
//
// Declaration de la classe decrivant les fiches ISM

#if !defined _ADXFICHEISM_H_
#define _ADXFICHEISM_H_

//#include "AdxDate.h"

class AdxFicheISM  {
  // CTOR - DTOR
public:
	virtual ~AdxFicheISM();
	AdxFicheISM(){init();};

	void setFicheISM( const char* str);
	void setMelangeLotCode( const long& value);
	void setMelangeLotLib(  const char* str);
	void setControlePeseurCode( const long& value);
	void setControlePeseurLib(  const char* str);
	void setControleQualiteCode( const long& value);
	void setControleQualiteLib(  const char* str);
	void setCodeEmballage( const int& value);
	void setCodeEmballageLib(  const char* str);
    void setSoldeEmballage( const double& value);
	void setModePeseeCode( const long& value);
	void setModePeseeLib(  const char* str);
	void setMessageObligatoire( const int& value) ; 
	void setPrecaution1(  const char* str);
	void setPictogramme1(  const char* str);
	void setPrecaution2(  const char* str);
	void setPictogramme2(  const char* str);
	void setPrecaution3(  const char* str);
	void setPictogramme3(  const char* str);
	void setPrecaution4(  const char* str);
	void setPictogramme4(  const char* str);
	void setPrecaution5(  const char* str);
	void setPictogramme5(  const char* str);
	void setPrecaution6(  const char* str);
	void setPictogramme6(  const char* str);
	void setPrecaution7(  const char* str);
	void setPictogramme7(  const char* str);
	void setPrecaution8(  const char* str);
	void setPictogramme8(  const char* str);
	void setCodeToxicite1(  const char* str);
	void setPictogramme9(  const char* str);
	void setCodeToxicite2(  const char* str);
	void setPictogramme10(  const char* str);
	void setCodeToxicite3(  const char* str);
	void setPictogramme11(  const char* str);
	void setCodeToxicite4(  const char* str);
	void setPictogramme12(  const char* str);
	void setContenuEtiquette(  const char* str);
 	void setRedressementManuel( const long& value);
	void setPeseeMultiArticle(const long& value);

	const char* getFicheISM ()const{ return _ficheISM;}
	const long getMelangeLotCode ()const{ return _melangeLotCode;}
	const char* getMelangeLotLib ()const{ return _melangeLotLib;}
	const long getControlePeseurCode ()const{ return _controlePeseurCode;}
	const char* getControlePeseurLib ()const{ return _controlePeseurLib;}
	const long getControleQualiteCode ()const{ return _controleQualiteCode;}
	const char* getControleQualiteLib ()const{ return _controleQualiteLib;}
	const int getCodeEmballage ()const{ return _codeEmballage;}
	const char* getCodeEmballageLib ()const{ return _codeEmballageLib;}
	const double getSoldeEmballage ()const{ return _soldeEmballage;}
    const long getModePeseeCode ()const{ return _modePeseeCode;}
	const char* getModePeseeLib ()const{ return _modePeseeLib;}
	const int getMessageObligatoire ()const{ return _messageObligatoire;}
	const char* getPrecaution1 ()const{ return _precaution1;}
	const char* getPictogramme1 ()const{ return _pictogramme1;}
	const char* getPrecaution2 ()const{ return _precaution2;}
	const char* getPictogramme2 ()const{ return _pictogramme2;}
	const char* getPrecaution3 ()const{ return _precaution3;}
	const char* getPictogramme3 ()const{ return _pictogramme3;}
	const char* getPrecaution4 ()const{ return _precaution4;}
	const char* getPictogramme4 ()const{ return _pictogramme4;}
	const char* getPrecaution5 ()const{ return _precaution5;}
	const char* getPictogramme5 ()const{ return _pictogramme5;}
	const char* getPrecaution6 ()const{ return _precaution6;}
	const char* getPictogramme6 ()const{ return _pictogramme6;}
	const char* getPrecaution7 ()const{ return _precaution7;}
	const char* getPictogramme7 ()const{ return _pictogramme7;}
	const char* getPrecaution8 ()const{ return _precaution8;}
	const char* getPictogramme8 ()const{ return _pictogramme8;}
	const char* getCodeToxicite1 ()const{ return _codeToxicite1;}
	const char* getPictogramme9 ()const{ return _pictogramme9;}
	const char* getCodeToxicite2 ()const{ return _codeToxicite2;}
	const char* getPictogramme10 ()const{ return _pictogramme10;}
	const char* getCodeToxicite3 ()const{ return _codeToxicite3;}
	const char* getPictogramme11 ()const{ return _pictogramme11;}
	const char* getCodeToxicite4 ()const{ return _codeToxicite4;}
	const char* getPictogramme12 ()const{ return _pictogramme12;}
	const char* getContenuEtiquette ()const{ return _contenuEtiquette;}
    const long  getRedressementManuel ()const{ return _redressementManuel;}
	const long  getPeseeMultiArticle () const{return _peseeMultiArticle;}


protected :
// donnees
	char*						_ficheISM;
	long						_melangeLotCode;
	char*						_melangeLotLib;
	long						_controlePeseurCode;
	char*						_controlePeseurLib;
	long						_controleQualiteCode;
	char*						_controleQualiteLib;
//	long						_codeEmballage;
	int 						_codeEmballage;
	char*						_codeEmballageLib;
    double						_soldeEmballage;
	long						_modePeseeCode;
	char*						_modePeseeLib;
	int							_messageObligatoire;	// 06.07 mm - Forcer la lecture d'une icone
	char*						_precaution1;
	char*						_pictogramme1;
	char*						_precaution2;
	char*						_pictogramme2;
	char*						_precaution3;
	char*						_pictogramme3;
	char*						_precaution4;
	char*						_pictogramme4;
	char*						_precaution5;
	char*						_pictogramme5;
	char*						_precaution6;
	char*						_pictogramme6;
	char*						_precaution7;
	char*						_pictogramme7;
	char*						_precaution8;
	char*						_pictogramme8;
	char*						_codeToxicite1;
	char*						_pictogramme9;
	char*						_codeToxicite2;
	char*						_pictogramme10;
	char*						_codeToxicite3;
	char*						_pictogramme11;
	char*						_codeToxicite4;
	char*						_pictogramme12;
	char*						_contenuEtiquette;
    long						_redressementManuel;
	int							_peseeMultiArticle;
	
// fonctions
	void init();

private :
	AdxFicheISM( const AdxFicheISM& ficheISM);
};

#endif /*_ADXFICHEISM_H_*/