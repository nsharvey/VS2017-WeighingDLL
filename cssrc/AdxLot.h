// AdxLot.h
// --------
// project : Adonix X3 Centrale de Pesee
// author : EP		18/06/01
//--------------------------------------------------------------
//
// Declaration des classes decrivant un Lot pour les allocations

#if !defined _ADXLOT_H_
#define _ADXLOT_H_

#include "AdxDate.h"

class AdxLot  {
public:
	virtual ~AdxLot();
	AdxLot(){init();};

	void setLot( const char* str);
	void setSlo( const char* str);
    void setEmplacement( const char* str);
	void setLibEmplacement( const char* str);
	void setQuantiteDisponible( const double& quantite);
	void setQuantiteAllouee( const double& quantite);
	void setQuantiteTotale( const double& quantite);
    void setUnite( const char* str);
	void setDatePeremption( AdxDate* date);
	void setStatut (const char* str);
	void setLibStatut( const char* str);
	void setTitre( const double& t);
	void setCuve( const char* str);
	void setLibSaisieCuve( const char* str);
	void setVanne( const char* str);
	void setChrono( const int t);
	void setSequence( const int t);
    //qté réellement disponible hors allocation pour cette matière
 	void setQuantiteReelDispo( const double& quantite); 
    //qté initiale de la ligne de stock (cécessaire pour solde emballagé)
	void setQuantiteInitiale( const double& quantite);

	const char* getLot() const { return _lot;}
	const char* getSlo() const { return _slo;}
    const char* getEmplacement() const { return _emplacement;}
    const char* getLibEmplacement() const { return _libEmplacement;}
	const double getQuantiteDisponible() const { return _quantiteDisponible;}
	const double getQuantiteAllouee() const { return _quantiteAllouee;}
	const double getQuantiteTotale() const { return _quantiteTotale;}
    const char* getUnite() const { return _unite;}
	AdxDate* getDatePeremption() const { return _datePeremption;}
	const char* getStatut() const { return _statut;}
	const char* getLibStatut() const { return _libStatut;}
	const double getTitre() const { return _titre;}
	const char* getCuve() const { return _cuve;}
	const char* getLibSaisieCuve() const { return _libCuve;}
	const char* getVanne() const { return _vanne;}
	const int getChrono() const { return _chrono;}
	const int getSequence() const { return _sequence;}
  	const double getQuantiteReelDispo() const { return _quantiteReelDispo;}
    const double getQuantiteInitiale() const { return _quantiteInitiale;}
	AdxLot* copy();
protected :
// donnees
	char*						_lot;
	char*						_slo;
    char*						_emplacement;
	char*						_libEmplacement;
	double						_quantiteDisponible;
	double						_quantiteAllouee;
	double						_quantiteTotale;
	char*						_unite;
	AdxDate*					_datePeremption;
	char*						_statut;
	char*						_libStatut;
	double						_titre;
	char*						_cuve;
	char*						_libCuve;
	char*						_vanne;
	int							_chrono;
	int							_sequence;
    double						_quantiteReelDispo;
    double						_quantiteInitiale;	
// fonctions
	void init();

private :
	AdxLot( const AdxLot& lot);
	const AdxLot& operator=( const AdxLot& lot);

};

#endif /*_ADXLOT_H_*/