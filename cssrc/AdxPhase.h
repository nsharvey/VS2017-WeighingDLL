// AdxPhase.h
// ----------
// project : Adonix X3 Centrale de Pesee
// author : EP		11/05/01
//--------------------------------------------------------------
//
// Declaration des classes decrivant une Phase

#if !defined _ADXPHASE_H_
#define _ADXPHASE_H_

#include "AdxDate.h"

class AdxComposant;

class AdxPhase  {
public:
	virtual ~AdxPhase();
	AdxPhase(){init();};

	void setNumOF( const char* str);
	void setNumPhase( const int p);
	void setStatut( const int s);
	void setLibStatut( const char* str);
	void setDate( AdxDate* date);
	void setPriorite( const int p);
	void setLibPriorite( const char* str);
	void setCurrentComposantIndex(unsigned long index);
	void setNbComposants(const int nb);
	void setNbComposantsPeses(const int nb);
	void setTotalementPese(const bool b);
	void setRectif(const int nb);
	// SMO : 18/08/2010
	void setQteRestaPeser(const double qte);
	void setQteAllouee(const double qte);
	void setUnite(const char* str);

	const char*		getNumOF()				const { return _numOF;}
	/*const*/ int	getNumPhase()			const { return _numPhase;}
	const int		getStatut()				const { return _statut;}
	const char*		getLibStatut()			const { return _libStatut;}
	AdxDate*		getDate()				const { return _date;}
	const int		getPriorite()			const { return _priorite;}
	const char*		getLibPriorite()		const { return _libPriorite;}
	// acces liste des matieres
	IlList*			getComposantList()		const {return _composantList;}
	AdxComposant*	getComposant(unsigned long index) const {
						AdxComposant* composant = (AdxComposant*)(*_composantList)[index];
						return composant;
					}
	int				getNbComposants()		const {return _nbComposants;}
	int				getNbComposantsPeses()	const {return _nbComposantsPeses;}
	bool			getTotalementPese()		const {return _totalementPese;}
	int				getRectif()				const {return _rectif;}
    int				getIndexComposant(const char* composant);
	// SMO : 18/08/2010
	const double	getQteRestaPeser()		const {return _qteRestaPeser;}
	const double	getQteAllouee()			const {return _qteAllouee;}
	const char*		getUnite()				const {return _unite;}


protected :
// donnees
	char*						_numOF;
	int							_numPhase;
	int							_statut;
	char*						_libStatut;
	AdxDate*					_date;
	int							_priorite;
	char*						_libPriorite;
	IlList*						_composantList;
	int							_nbComposants;
	int							_nbComposantsPeses;
	bool						_totalementPese;
	int							_rectif;
	// SMO : 18/08/2010
	double						_qteRestaPeser;
	double						_qteAllouee;
	char*						_unite;

// fonctions
	void init();

private :
	AdxPhase( const AdxPhase& phase);
	const AdxPhase& operator=( const AdxPhase& phase);

};

#endif /*_ADXPHASE_H_*/