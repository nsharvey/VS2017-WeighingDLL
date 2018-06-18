// AdxPesee_OF.h
// -------------
// project : Adonix X3 Scales
// author : EP
// V130 : EP 2001.05.28
//--------------------------------------------------------------
#ifndef __AdxPesee_OF__header__
#define __AdxPesee_OF__header__

#include "pesee_OF.h"
#include <ilviews/gadgets/menu.h>

class AdxInterface;
class AdxFicheISM;
class AdxBalance;
class AdxRecipient;
class AdxLot;
class AdxComposant;

class AdxPesee_OF
: public Pesee_OF {
public:
   AdxPesee_OF(IlvDisplay* display,
                const char* name,
                const char* title,
				AdxInterface* m_interface,
                IlvRect*    size            = 0,
                IlvBoolean  useAccelerators = IlvFalse,
                IlvBoolean  visible         = IlvFalse,
                IlvUInt     properties      = 0,
                IlvSystemView transientFor  = 0)
      : Pesee_OF(display,
                 name,
                 title,
                 size,
                 useAccelerators,
                 visible,
                 properties,
                 transientFor)
        {init(m_interface);}

//--------------------------------------------------------------
	virtual ~AdxPesee_OF();
    virtual void secu1CB(IlvGraphic*);
    virtual void secu2CB(IlvGraphic*);
    virtual void secu3CB(IlvGraphic*);
    virtual void secu4CB(IlvGraphic*);
    virtual void secu5CB(IlvGraphic*);
    virtual void secu6CB(IlvGraphic*);
    virtual void secu7CB(IlvGraphic*);
    virtual void secu8CB(IlvGraphic*);
    virtual void secu9CB(IlvGraphic*);
    virtual void secu10CB(IlvGraphic*);
    virtual void SaisieLotCB(IlvGraphic*);
	virtual void SaisieSousLotCB(IlvGraphic*);		// mm 05.10
	virtual void SaisieCuveCB(IlvGraphic*);
	virtual void FocusOutLotCB(IlvGraphic*);
	virtual void FocusOutSousLotCB(IlvGraphic* g);	// mm 02.11
	virtual void EntreeTextFieldCB(IlvGraphic* g);
	virtual void EntreeNumberFieldCB(IlvGraphic* g);
    virtual void ListeLotCB(IlvGraphic*);
    virtual void mettreAZeroCB(IlvGraphic*);
    virtual void SaisieEmplacementCB(IlvGraphic*);
	virtual void SaisieVanneCB(IlvGraphic*);
	virtual void FocusOutEmplacementCB(IlvGraphic*);
    virtual void aideCB(IlvGraphic*);
    virtual void SaisieRecipientCB(IlvGraphic*);
	virtual void FocusOutRecipientCB(IlvGraphic*);
    virtual void validerCB(IlvGraphic*);
	virtual void validerPlusCB(IlvGraphic*);	// 08.11 mm - Pesée multi-article
    virtual void SaisiePoidsPeseCB(IlvGraphic*);
//	virtual void EnterPoidsPeseCB(IlvGraphic*);
    virtual void ListeBalanceCB(IlvGraphic*);
    virtual void tarerCB(IlvGraphic*);
    virtual void peserCB(IlvGraphic*);
	virtual void SaisieBalanceCB(IlvGraphic*);
	virtual void FocusOutBalanceCB(IlvGraphic*);
    virtual void quitterCB(IlvGraphic*);
    virtual void ListeEmplacementCB(IlvGraphic*);
    virtual void ListeRecipientCB(IlvGraphic*);
    virtual void tactileCB(IlvGraphic*);
   
	void RclicJauge(IlvGraphic*);

	virtual void draw(const IlvRegion* region = 0);
	virtual void draw(IlvPort* dst,
					  const IlvTransformer* t = 0,
					  const IlvRegion* clip = 0) ;
	virtual void reDraw(const IlvRegion* region = 0);
	virtual void reDraw(const IlvRect* rect);

	void quitter();
	void afficherOrdre(long numo,long nump,long numc);
	void afficherLot(AdxLot* lot, bool AfficheQuantite = true);
	void chargement();
	void evolutionPoids();
	void drawScaleLines();
	void adaptationEchelle();
	bool propositionLot();
	bool propositionBalance();
	bool propositionRecipient();
	bool controleLot();
	bool controleEmplacement();
	bool controleBalance(bool pourChangement);
	bool controleRecipient();
	bool erreurRecipient();
	bool controleTare();
	bool affecteBalance();
	void envoiPeseePartielle();
	void envoiFinLot();
	void envoiFinComposant();
	void envoiFinComposant_Art();
	void envoiFinPhase();
	void envoiFinOF();
	void envoiFinXxx();
	void consommationQuantite(bool finLot = false);
	void annulePesee();
	void annuleTarage();
    //	void envoiSoldeEmballage();
    bool lookLot();
	void lanceProcedureEnAttente();
	void chargeTexte(const char* texte);
	CString formatMessage(CString texte);
	IlvBitmap* erreurBitmap(char* pszFileIcons);
	void chargementRecipient();
	void chargementBalance(AdxRecipient* recipient);
	void chargementAffichage();
	void recontroleOF();
	bool envoieMessage(CString mess, bool OUINON);
	// 09.11 mm
	void alimentationZonesNumeriques();
	void suiteChoixLot();
	void suiteChoixRecipient();
	void suiteChoixBalance();
	void attenteSaisieLot();
	void attenteSaisieRecipient();
	void attenteSaisieBalance();
	void setChampsAlphaEditable(bool editable);
	void setRecipientChoisi(AdxRecipient* recipient);
	void setBalanceChoisie(AdxBalance* balance);
	// 09.11 mm - Pesée Multi-article
	void setRecipientMulti(AdxRecipient* recipient) { _recipientMulti = recipient;};
	void setBalanceMulti(AdxBalance*	balance) { _balanceMulti = balance ;};
	void setIndexComposantSuivantMulti(int index) { _indexComposantSuivantMulti = index;};
	void setPoidsTareMulti( double poidsTare) {_poidsTareMulti = poidsTare; };
	void setPoidsMatDejaPese( double poidsPese) {_poidsMatDejaPese = poidsPese;} ;
	void setPoidsPeseMatEncours( double poidsPese){ _poidsPeseMatEncours = poidsPese; };
	void setTitreSlo( double titreSloCourant) {  _titreSlo = titreSloCourant; };		
	void setUnitePoidsMat1( const char* unit);
	void boutonValiderPlus();                                                
    void setBoutonValidation(const int value) {_boutonValidation = value;}
	bool controleRecipientMulti();
	bool controleRecipientPrevu(); // sr 01.12 APCPRD-728
	void suiteChoixLotMulti();
	void suiteChoixRecipientMulti();
	bool controleBalanceMulti();
	void suiteChoixBalanceMulti();
    void validerPeseeFinale(double toleranceArticleNegative, double soldeEmb);	// 111908 mm 01.2016

	AdxRecipient* getRecipientChoisi() {return _recipientChoisi;};
	AdxBalance*	getBalanceChoisie()	{return	_balanceChoisie;};
	AdxRecipient* getRecipientPrevu() {return _recipientPrevu;};
	AdxBalance*	getBalancePrevue()	{return	_balancePrevue;};

	// 09.11 mm
	AdxRecipient*	getRecipientMulti() { return 	_recipientMulti;}
	AdxBalance*		getBalanceMulti() {return 	_balanceMulti;}
	int	getIndexComposantSuivantMulti(){ return 	_indexComposantSuivantMulti; }
	double getPoidsTareMulti() {return _poidsTareMulti ;};
	double getPoidsMatDejaPese() {return _poidsMatDejaPese;};
	double getPoidsPeseMatEncours() {return _poidsPeseMatEncours;};
	double getPoidsPeseTotal() {return _poidsPeseTotal;};		
	double getTotalAPeserInitial() {return _totalAPeserInitial;};		
    const char*	getUnitePoidsMat1() const { return _UPMat1;}	
	int getBoutonValidation() { return _boutonValidation ;} // 1  bt valider 
														    // 2  bt validerPlus 
	bool getEnPeseeMultiArticle() {return _enPeseeMultiArticle ;}

	double getPoidsDejaPese() {return _poidsDejaPese ;}
	double getTitreSlo() {return _titreSlo ;}		
	double getWeightMin() {return _weightMin ;}
	double getWeightMax(){return _weightMax;}

	void setRecontroleFait(bool recontroleFait)	{_recontroleFait = recontroleFait;};
	bool getRecontroleFait(){ return _recontroleFait; }		// mm 08.2013
	void setWeightMin( double weightMin){_weightMin = weightMin;}; // 113445 mm 06.2016
	void setWeightMax( double weightMax){_weightMax = weightMax;}; // 113445 mm 06.2016

	// mm 10.12	
	void setMat1( const char* str);
	const char*		getMat1() const { return _mat1;}
	// 116324 mm 08.2016
	void setDepassementPoidsMax( double depassementPoidsMax) { _depassementPoidsMax = depassementPoidsMax;};
	double getDepassementPoidsMax() { return _depassementPoidsMax; }
	
	AdxInterface* getInterface() {return _interface;};

	//pour ajouter la gestion des raccourcis
	virtual void handleInput(IlvEvent& event) ;

	AdxInterface*		_interface;
	AdxFicheISM*		_ficheISM;
	AdxRecipient*		_recipientChoisi;
	AdxBalance*			_balanceChoisie;
	AdxRecipient*		_recipientPrevu;
	AdxBalance*			_balancePrevue;

	bool                _recontroleFait;
	bool                _soldeEmballage;
   	bool                _redressement;
    bool                _redressementFin;
    bool                _redressementDesactive;
	bool			    _redressementPositif;		// 41440 mm 03.08 - bug en cas de redressement positif
//	bool                _saisieFaite;

	bool                _lotOK;
	bool                _dernierLot;
    bool                _recipientOK;
	bool                _balanceOK;

	bool                _miseAZeroOK;
	bool                _tarageOK;
	bool                _peseeOK;

	bool                _attenteTarage;
	bool                _attentePesee;
	bool				_balanceBegin;
	bool				_stockReelInfInfo;
	bool				_peseeLimiteeParBalance;
	bool				_peseeParEcart;
	bool				_peseeParConsigne;
	bool				_messageLu;		// 06.07 mm - Forcer la lecture d'une icone
	bool				_peseeCumuleeForcee;	// 11.07 mm - modif mode de pesee en emb.mixte
	bool				_razTare ;				// 12.08 mm - Recontrôle lot invalide
	bool				_modifAllocations;		// SR 12.11 APCPRD-724
	bool				_btVPlus;				// 01.2013 mm APCPRD-2787
	bool				_btV;				// 01.2013 mm APCPRD-2787

	int					_occup[10];

	char*				_lignes [10];
	char*				_blanc;


// zones de calcul des poids de la transaction de pesee

	double				_totalAPeser;
	double				_totalAPeserInitial;
	double				_poidsCumule;			
	double				_poidsTare;
	double				_poidsPese;
	double				_poidsPeseTheo;
	double				_poidsPeseTotalPhysique; // 09.12 mm - somme des poids pesés exprimés en titre physique
	double				_titreSlo;				// 09.12 mm		
	double				_poidsPeseTotal;
	double				_poidsAPeser;
	double				_poidsDejaPese;
	double				_poidsPeseParEcart;		// 09.09 mm - modif mode de pesee en emb.mixte
	// gbe pour les lignes de jauge
	double              _weightMin;
	double              _weightMax;
	//sr 01.12 pb de poids cumulé balance non connecté
	double				_poidsEncours;

// sr 02.05 test dose
	double				_poidsTest;
	void init(AdxInterface* m_interface);
	bool initClavier_Tactile();

// gbe 10.08 pour savoir quand on est en pesée
	bool				_enPesee;

// mm 08.11 - pesée multi-article 
	int					_boutonValidation;
						// 1 bouton valider 
						// 2 bouton validerPlus 
// variables pour récupérer le contexte
	AdxRecipient*		_recipientMulti ;
	AdxBalance*			_balanceMulti;
	AdxComposant*		_composantSuivant;     // 01.12 APCPRD-728
	int					_indexComposantSuivantMulti;
	double				_poidsTareMulti;
	double				_poidsMatDejaPese ;
	double				_poidsPeseMatEncours;
	char*				_UPMat1;
	bool				_enPeseeMultiArticle ;	// si flag = VRAI -> pesée multi-article
	double				_poidsCumuleMulti;
	double				_poidsCumuleCible;
	double				_depassementPoidsMax;	// 116324 mm 08.2016
	// mm 10.12  APCPRD-1596
	char*				_mat1;		
	// gbe 26/03/12 gestion de l'affichage de la graduation et de la tolérance de la jauge
	bool				_showGraduation;
	bool				_showTolerance;
	// Hauteur de la police du poids
	IlvUShort			_weightFontHeight;

protected:
	IlvPopupMenu*       _popupJauge;


};
#endif
