// AdxOrder.h
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : EP		30/04/01
//--------------------------------------------------------------
//
// Declaration des classes decrivant un OF et une liste d'OF

#if !defined _ADXORDER_H_
#define _ADXORDER_H_

#include "AdxDate.h"


class AdxOrder  {
public:
	virtual ~AdxOrder();
	AdxOrder(){init();};

	void setNumOF( const char* str);
	void setArticle( const char* str);
	void setLibArticle( const char* str);
	void setLotLance( const char* str);
	void setQuantiteLance (const double& quantiteLance);
	void setUnite( const char* str);
	void setStatut( const int s);
	void setLibStatut( const char* str);
	void setDateFin( AdxDate* date);
	void setPriorite( const int p);
	void setLibPriorite( const char* str);
	void setQuantiteLanceeEnPoids (const double& quantite);
	void setUnitePoids( const char* str);
	void setTotalementPese(const bool b);
	// SMO : 18/08/2010
	void setTotalAPeser(const double& totAPeser);
	void setUnitePoidsCompo( const char* str);


	const char*		getNumOF() const { return _numOF;}
	const char*		getArticle() const { return _article;}
	const char*		getLibArticle() const { return _libArticle;}
	const char*		getLotLance() const { return _lotLance;}
	const double	getQuantiteLance () const { return _quantiteLance;}
	const char*		getUnite() const { return _unite;}
	const int		getStatut() const { return _statut;}
	const char*		getLibStatut() const { return _libStatut;}
	AdxDate*		getDateFin() const { return _dateFin;}
	const int		getPriorite() const { return _priorite;}
	const char*		getLibPriorite() const { return _libPriorite;}
	const double	getQuantiteLanceeEnPoids () const { return _quantiteLanceeEnPoids;}
	const char*		getUnitePoids() const { return _unitePoids;}
	bool			getTotalementPese() const {return _totalementPese;}
	// SMO : 18/08/2010
	const double	getTotalAPeser() const { return _totalAPeser;}
	const char*		getUnitePoidsCompo() const { return _unitePoidsCompo;}

protected :
// donnees
	char*						_numOF;
	char*						_article;
	char*						_libArticle;
	char*						_lotLance;
	double						_quantiteLance;
	char*						_unite;
	int							_statut;
	char*						_libStatut;
	AdxDate*					_dateFin;
	int							_priorite;
	char*						_libPriorite;
	double						_quantiteLanceeEnPoids;
	char*						_unitePoids;
	bool						_totalementPese;
	// SMO : 18/08/2010
	int							_statutMatiere;
	double						_totalAPeser;
	char*						_unitePoidsCompo;

	
// fonctions
	void init();

private :
	AdxOrder( const AdxOrder& order);
	const AdxOrder& operator=( const AdxOrder& order);

};

//ADXANYSTACK( AdxOrder);

#endif /*_ADXORDER_H_*/