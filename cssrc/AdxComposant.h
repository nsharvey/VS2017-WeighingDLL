// AdxComposant.h
// ----------------
// project : Adonix X3 Centrale de Pesee
// author : EP		11/06/01
//--------------------------------------------------------------
//
// Declaration des classes decrivant un composant

#if !defined _ADXCOMPOSANT_H_
#define _ADXCOMPOSANT_H_

#include <ilog\list.h>

class AdxData;
class AdxDate;
class AdxLot;
class AdxPhase;

class AdxComposant  {
  // CTOR - DTOR
public:
	virtual ~AdxComposant();
	AdxComposant(){init();};

	void setComposant( const char* str);
	void setLibComposant( const char* str);
	void setQuantitePrevue (const double& quantite);
	void setQuantiteRestante (const double& quantite);
	void setQuantiteTheorique (const double& quantite);
	void setQuantiteAllouee (const double& quantite);
	void setQuantiteConsommee (const double& quantite);
	void setQuantiteDisponible (const double& quantite);
	void setQuantiteDose (const double& quantite);
	void setToleranceArticlePositive( const double& value);
	void setToleranceArticleNegative( const double& value);
    void setUnite( const char* str);
	void setUniteStock( const char* str);
	void setCodeAServir( const int s);
	void setLibCodeAServir( const char* str);
	void setGestionStock( const int s);
	void setLibGestionStock( const char* str);
	void setTitreTheo (const double& titre);
	void setStockInfZero( const int s);
	void setLibStockInfZero( const char* str);
	void setLancementSiRupture( const int s);
	void setLibLancementSiRupture( const char* str);
	void setFicheISM( const char* str);
	void setNumeroLigne( const int s);
	void setSequenceNomenclature( const int s);
	void setDecimalePoids( const int s);
	void setTotalementPese( const bool b);
	void setFormat( const char* str);
	void setPhase(const int s) {_phase = s;}
	void setRedMod(const int s);
    void setNbPhases_Art(const int s)  {_nbPhases_Art = s;}
	void setQteDispoCompo(const double& qteDispo); // SMO : 19/08/2010
	void setQuantiteAlloueeRestante(const double& qteAll); // mm : qté allouée restante	
	void setQuantiteAlloueeTheorique(const double& qteAll); // mm 02.11
	void setQuantiteAlloueeDpOF(const double& qteAll); // mm 04.11
	void setNumOF( const char* str);	// mm 03.13 Performances
	void setLotAlloueInvalide( const int s) { _lotAlloueInvalide = s;};	//APCPRD-2438 mm 08.2013
	void setQuantitePEC(const double& qtePEC);	// mm 10.2013

	const char*		getComposant() const { return _composant;}
	const char*		getLibComposant() const { return _libComposant;}
	const double	getQuantitePrevue () const { return _quantitePrevue;}
	const double	getQuantiteRestante () const { return _quantiteRestante;}
	const double	getQuantiteTheorique () const { return _quantiteTheorique;}
	const double	getQuantiteAllouee () const { return _quantiteAllouee;}
	const double	getQuantiteDisponible () const { return _quantiteDisponible;}
	const double	getQuantiteConsommee () const { return _quantiteConsommee;}	
	const double	getQuantiteDose () const { return _quantiteDose;}
	const double	getToleranceArticlePositive ()const{ return _toleranceArticlePositive;}
	const double	getToleranceArticleNegative ()const{ return _toleranceArticleNegative;}
    const char*		getUnite() const { return _unite;}	
	const char*		getUniteStock() const { return _uniteStock;}
	const int		getCodeAServir() const { return _codeAServir;}
	const char*		getLibCodeAServir() const { return _libCodeAServir;}
	const int		getGestionStock() const { return _gestionStock;}
	const char*		getLibGestionStock() const { return _libGestionStock;}
	const double	getTitreTheo () const { return _titreTheo;}
	const int		getStockInfZero() const { return _stockInfZero;}
	const char*		getLibStockInfZero() const { return _libStockInfZero;}
	const int		getLancementSiRupture() const { return _lancementSiRupture;}
	const char*		getLibLancementSiRupture() const { return _libLancementSiRupture;}
	const char*		getFicheISM() const { return _ficheISM;}
	const int		getNumeroLigne() const { return _numeroLigne;}
	const int		getSequenceNomenclature() const { return _sequenceNomenclature;}
	const int		getDecimalePoids() const { return _decimalePoids;}
	const bool		getTotalementPese() const { return _totalementPese;}
	const char*		getFormat() const { return _format;}
	const int		getPhase() const { return _phase;}
    const int		getRedMod() const { return _redMod;}
	const double	getQteDispoCompo() const { return _qteDispoCompo;} // SMO : 19/08/2010
	const double	getQuantiteAlloueeRestante() const { return _quantiteAlloueeRestante;}	// mm 11.10
	const double	getQuantiteAlloueeTheorique() const { return _quantiteAlloueeTheorique;}	// mm 11.10
	const double	getQuantiteAlloueeDpOF() const { return _quantiteAlloueeDpOF;}	// mm 11.10
	const char*		getNumOF()				const { return _numOF;}	// mm 03.13 Performances
	const int		getLotAlloueInvalide()	const { return _lotAlloueInvalide;} // APCPRD-2438 mm 08.2013
	const double	getQuantitePEC()		const{ return _quantitePEC; }	// mm 10.2013

// acces liste des phases
	IlList* getPhaseList_Art() const {return _phaseList_Art;}
	AdxPhase* getPhase_Art(unsigned long index) const {
				AdxPhase* phase = (AdxPhase*)(*_phaseList_Art)[index];
				return phase;}
	int getNbPhases_Art() const {return _nbPhases_Art;}
	int getIndexPhase_Art(const AdxPhase* phase);
	int getIndexPhase_Art(const int phase);
	void recalculeAlloueEtDisponible(AdxData* data);

protected :
// donnees
	char*						_composant;
	char*						_libComposant;
// quantites prevues et restantes au niveau de l'OF: quantites actives
	double						_quantitePrevue;
	double						_quantiteRestante;
// quantite a peser theorique: quantite reelle si titre-composant == titre-lot
	double						_quantiteTheorique;
// quantites allouees, disponibles et consommees cumulees pour tous les lots
// ces quantites sont des quantites reelles
	double						_quantiteAllouee;
	double						_quantiteDisponible;
	double						_quantiteConsommee;
	double						_quantiteDose;
    char*						_unite;
	char*						_uniteStock;
	int							_codeAServir;
	//	1	non pese en centrale
	//	2	pese en centrale
	//	3	pesee en fabrication
	//	4	excipient fin phase en centrale
	//	5	excipient fin phase en fabrication
	//	6	excipient fin fabrication en centrale
	//	7	excipient fin fabrication en fabrication
	//	8	matiere de rectification en centrale
	//	9	matiere de rectification en fabrication
	//	10	QSP en fin de fabrication
	char*						_libCodeAServir;
	int							_gestionStock;
	char*						_libGestionStock;
	double						_titreTheo;
	int							_stockInfZero;
	char*						_libStockInfZero;
	int							_lancementSiRupture;
	char*						_libLancementSiRupture;
	char*						_ficheISM;
	int							_numeroLigne;
	int							_sequenceNomenclature;
	int							_decimalePoids;
	bool						_totalementPese;
	char*						_format;
	int							_phase;
	int							_redMod; // mode de redressement négatif : 1 au lot, 2 à l'allocation

	IlList*						_phaseList_Art;
	int							_nbPhases_Art;
	double						_toleranceArticlePositive;	// 05.10 mm - Différenciation des tolérances +/-
	double						_toleranceArticleNegative;	// 05.10 mm - Différenciation des tolérances +/-

	double						_qteDispoCompo; // SMO : 19/08/2010

//  mm 11.10 - qté allouée depuis l'OF à l'initialisation, puis = à la qté allouée composant ensuite,exprimée en unité physique
	double						_quantiteAlloueeRestante;														
//  mm 02.11 - qté allouée depuis l'OF à l'initialisation, puis = à la qté allouée composant ensuite,en UA
	double						_quantiteAlloueeTheorique;		
//  mm 04.11 - sauvegarde de la qté allouée dp l'OF
	double						_quantiteAlloueeDpOF;
	char*						_numOF;	// 03.13 mm - Persormances
	int							_lotAlloueInvalide ;	// APCPRD-2438 08.2013 mm 
														// _lotAlloueInvalide = 1 -> lot périmé
														// _lotAlloueInvalide = 2 -> mélange lot interdit
														// _lotAlloueInvalide = 3 -> lot non consommable

// 91035 mm 10.2013 - filtre des qtés à PEC pour le calcul de la qté à peser de l'excipient de fin de phase
	double						_quantitePEC;
													
// fonctions
	void init();

private :
	AdxComposant( const AdxComposant& composant);
	const AdxComposant& operator=( const AdxComposant& composant);

};

#endif /*_ADXCOMPOSANT_H_*/