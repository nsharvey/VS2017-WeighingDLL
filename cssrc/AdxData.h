// AdxData.h
// --------------
// project : Adonix X3 Centrales
// author : EP
// V130 :  2001/05/14
//--------------------------------------------------------------
//

#if !defined _ADXDATA_H_
#define _ADXDATA_H_

#include <ilog\list.h>
#include <fstream>
#include "AdxCsvfiles.h"
#include "StdAfx.h"							// 06.04 Unicode

class AdxUnit;
class AdxOrder;
class AdxPhase;
class AdxComposant;
class AdxLot;
class AdxBalance;
class AdxFicheISM;
class AdxFicheISMRecipient;
class AdxRecipient;
class AdxAccueil;
class AdxDate;
class AdxInterface;
//class AdxCsvFiles;
class AdxGadgetContainer;
class AdxEtalon;
class AdxEtalonLigne;

const char Decimal = '.';
const char* const FieldSeparator = ";,";
const char* const Comment = "//";

class AdxData  {
public:
	virtual ~AdxData();
	AdxData(AdxInterface* m_interface){init(m_interface);};

//--------------------------------------------------------------
// accessors & modifiers
	char* getSzCheminCsv1() const { return _szCheminCsv1;}
	void setSzCheminCsv1(const char* deb, const char* fin);
	char* getSzCheminCsv2() const { return _szCheminCsv2;}
	void setSzCheminCsv2(const char* deb, const char* fin);
	char* getSzCheminCsv3() const { return _szCheminCsv3;}
	void setSzCheminCsv3(const char* deb, const char* fin);
	char* getSzCheminCsv4() const { return _szCheminCsv4;}
	void setSzCheminCsv4(const char* deb, const char* fin);
	char* getSzCheminCsv5() const { return _szCheminCsv5;}
	void setSzCheminCsv5(const char* deb, const char* fin);
	char* getSzCheminCsv6() const { return _szCheminCsv6;}
	void setSzCheminCsv6(const char* deb, const char* fin);
	char* getSzCheminCsv7() const { return _szCheminCsv7;}
	void setSzCheminCsv7(const char* deb, const char* fin);
	char* getSzCheminCsv8() const { return _szCheminCsv8;}
	void setSzCheminCsv8(const char* deb, const char* fin);
	char* getSzCheminCsv9() const { return _szCheminCsv9;}
	void setSzCheminCsv9(const char* deb, const char* fin);
	char* getSzCheminCsv10() const { return _szCheminCsv10;}
	void setSzCheminCsv10(const char* deb, const char* fin);
	char* getSzCheminCsv11() const { return _szCheminCsv11;}
	void setSzCheminCsv11(const char* deb, const char* fin);
	char* getSzCheminCsv12() const { return _szCheminCsv12;}
	void setSzCheminCsv12(const char* deb, const char* fin);
	char* getSzCheminCsv13() const { return _szCheminCsv13;}
	void setSzCheminCsv13(const char* deb, const char* fin);
	char* getSzCheminCsv14() const { return _szCheminCsv14;}		//X3-67237
	void setSzCheminCsv14(const char* deb, const char* fin);		//X3-67237

	AdxInterface* getInterface() const {return _interface;}
	char* getLanguage() const {return _language;}
	void setLanguage(const char* str);
	
	AdxDate* getDateJour() const {return _dateJour;}
	char* getUtilisateur() const {return _utilisateur;}
	void setUtilisateur(const char* str);
	char* getApplication() const {return _application;}
	void setApplication(const char* str);
	char* getLieu() const {return _lieu;}
	void setLieu(const char* str);
	char* getBox() const {return _box;}
	void setBox(const char* str);
	char* getOuvertureBox() const { return _ouvertureBox;}
	void setOuvertureBox(const char* str);
	int getOuvertureBoxOblig() const { return _ouvertureBoxOblig;}
	void setOuvertureBoxOblig( const int p);
	char* getVideBoxFinOF() const { return _videBoxFinOF;}
	void setVideBoxFinOF(const char* str);
	int getVideBoxFinOFOblig() const { return _videBoxFinOFOblig;}
	void setVideBoxFinOFOblig( const int p);
	char* getVideBoxFinPhase() const { return _videBoxFinPhase;}
	void setVideBoxFinPhase(const char* str);
	int getVideBoxFinPhaseOblig() const { return	_videBoxFinPhaseOblig;}
	void setVideBoxFinPhaseOblig( const int p);
	char* getVideBoxFinMatiere() const { return _videBoxFinMatiere;}			// SMO : STD-PR-OO1 : Pesee Matiere
	void setVideBoxFinMatiere(const char* str);									// SMO : STD-PR-OO1 : Pesee Matiere
	int getVideBoxFinMatiereOblig() const { return	_videBoxFinMatiereOblig;}	// SMO : STD-PR-OO1 : Pesee Matiere
	void setVideBoxFinMatiereOblig( const int p);								// SMO : STD-PR-OO1 : Pesee Matiere
	char* getPeseePartielle() const { return _peseePartielle;}
	void setPeseePartielle(const char* str);
	int getPeseePartielleCode() const { return _peseePartielleCode;}
	void setPeseePartielleCode( const int p);
	char* getModifLigneStock() const { return _modifLigneStock;}
	void setModifLigneStock(const char* str);
	int getModifLigneStockCode() const { return	_modifLigneStockCode;}
	void setModifLigneStockCode( const int p);
	char* getRecontroleArticle() const { return _recontroleArticle;}
	void setRecontroleArticle(const char* str);
	int getRecontroleArticleCode() const { return _recontroleArticleCode;}
	void setRecontroleArticleCode( const int p);
	// mm 03.10 - modification du recontrole
	char* getRecontroleCuve() const { return _recontroleCuve;}
	void  setRecontroleCuve(const char* str);
	int	  getRecontroleCuveCode() const { return _recontroleCuveCode;}
	void  setRecontroleCuveCode( const int p);
	// mm 02.11 - magasin avancé
	char* getPrioriteAllocation() const { return _prioriteAllocation;}
	void  setPrioriteAllocation(const char* str);
	int	  getPrioriteAllocationCode() const { return _prioriteAllocationCode;}
	void  setPrioriteAllocationCode( const int p);
	char* getDepotBox() const { return _depotBox;}	
	void  setDepotBox(const char* str);
	char* getEmplacementBox() const { return _emplacementBox;}	
	void  setEmplacementBox(const char* str);
	char* getAllocationAuto() const { return _allocationAuto;}
	void  setAllocationAuto(const char* str);
	int	  getAllocationAutoCode() const { return _allocationAutoCode;}
	void  setAllocationAutoCode( const int p);
	// 90456 mm 06.13 - Gestion du param GLISMAT 
	int	  getChargementListMat() const { return _chargementListMat;}
	void  setChargementListMat( const int p);
	// 113445 mm 07.2016 - Management of GAPTOPW param - Application of Tolerance in Partial Weighing
	int	  getApplicationTolerance() const {return _applicationTolerance; } 
	void  setApplicationTolerance(const int p);
	// 116324 mm 08.2016 - Management of GPOSTOL param - Authorization to exceed the tolerance +
	int   getExceedingTolerancePos() const { return _exceedingTolerancePos ;}
	void  setExceedingTolerancePos( const int p);
	// sr 05.02 Gestion mélange lot
	int   getLongueurLot() const { return _longueurLot;}
	void  setLongueurLot(const int p);
	// mm 03.10 - paramétrage redressement négatif
	int   getRedressementNegatif() const { return _redressementNegatif; }
	void  setRedressementNegatif(const int p);
	//
	int	getCodeOFEnCoursPesee() const { return _codeOFEnCoursPesee;}
	void setCodeOFEnCoursPesee( const int p);
	char* getLibOFEnCoursPesee	() const { return _libOFEnCoursPesee;}
	void setLibOFEnCoursPesee(const char* str);
	int	getCodeOFPeseBox() const { return _codeOFPeseBox;}
	void setCodeOFPeseBox( const int p);
	char* getLibOFPeseBox() const { return _libOFPeseBox;}
	void setLibOFPeseBox(const char* str);
	int	getCodeMatEnCoursPesee() const { return _codeMatEnCoursPesee;}
	void setCodeMatEnCoursPesee( const int p);
	char* getLibMatEnCoursPesee() const { return _libMatEnCoursPesee;}
	void setLibMatEnCoursPesee(const char* str);
	int	getCodeMatPese() const { return _codeMatPese;}
	void setCodeMatPese( const int p);
	char* getLibMatPese	() const { return _libMatPese;}
	void setLibMatPese(const char* str);
	//103422 mm 01.2015 - Découpage du CAB dans le cadre du recontrôle
	int	getDecoupageCAB() const { return _decoupageCAB ;}	
	void setDecoupageCAB( const int p);
	char* getLibDecoupageCAB() const { return _libDecoupageCAB;}
	void setLibDecoupageCAB(const char* str);
	int getTypeCAB()const { return _typeCAB ;}	
	void setTypeCAB(const int p);
	int getSuppBlanc()const { return _suppBlanc;}	
	void setSuppBlanc(const int p);
	int getNumZoneArt()const { return _numZoneArticle;}	
	void setNumZoneArt(const int p);
	char* getSeparateurArt() const { return _separateurArt; }
	void setSeparateurArt(const char* str);
	int getNumZoneLot()const { return _numZoneLot;}
	void setNumZoneLot(const int p);
	char* getSeparateurLot() const { return _separateurLot; }
	void setSeparateurLot(const char* str);
	int getNumZoneSlo()const { return _numZoneSlo;}
	void setNumZoneSlo(const int p);
	char* getSeparateurSlo() const { return _separateurSlo; }
	void setSeparateurSlo(const char* str);
	int getLongueurArt() const { return _longueurArt; }
	void setLongueurArt(const int p);
	int getDebutArt()const {return _debutArt; }
	void setDebutArt(const int p);
	int getLongueurLot2() const { return _longueurLot2; }
	void setLongueurLot2(const int p);
	int getDebutLot()const {return _debutLot; }
	void setDebutLot(const int p);
	int getLongueurSlo() const { return _longueurSlo; }
	int getDebutSlo()const {return _debutSlo; }
	void setLongueurSlo(const int p);
	void setDebutSlo(const int p);

	void setUsrWei(const int p);					//X3-67237: Set the USRWEI flag 
	int getUsrWei() const {return _usrwei;}			//X3-67237: Return the USRWEI flag
	void setBoxPwd(const int p);					//X3-67237: Set the Credential Check at Open Box Flag
	int getBoxPwd() const {return _boxpwd;}			//X3-67237: Return the Credential Check at Open Box Flag
	void setEwoPwd(const int p);					//X3-67237: Set the Credential Check at End of W/O
	int getEwoPwd() const {return _ewopwd;}			//X3-67237: Return the Credential Check at End of W/O
	void setPhaPwd(const int p);					//X3-67237: Set the Credential Check at End of Phase (Operation)
	int getPhaPwd() const {return _phapwd;}			//X3-67237: Return the Credential Check at Empty Station Phase
	void setMatPwd(const int p);					//X3-67237: Set the Credential Check at Empty Station Phase
	int getMatPwd() const {return _matpwd;}			//X3-67237: Return the Credential Check at Empty Station Phase
	void setUserID(const char* str);				//X3-67237: Set the User ID from X3 Credential Validation
	char* getUserID() const {return _X3UserID;}		//X3-67237: Return the User ID from X3 Credential Validation
	void setX3Ver(const int p);						//X3-67237: Set the X3 Version 
	int getX3Ver() const {return _X3Ver;}			//X3-67237: Return the X3 Version


//acces OF
	IlList* getOrderList() const {return _orderList;}
	AdxOrder* getCurrentOrder() const {return _currentOrder;}
	void setCurrentOrderIndex(unsigned long index,bool premiereFois = 0);
	int	getCurrentOrderIndex() const{return _currentOrderIndex;}
	AdxOrder* getOrder(unsigned long index) const {
				AdxOrder* order = (AdxOrder*)(*_orderList)[index];
				return order;}
	int getNbOrders() const {return _nbOrders;}
	void setNbOrders(int nbOrders) { _nbOrders = nbOrders;}
	bool getOrderBegin() const {return _orderBegin;}
	void setOrderBegin (const bool& b)	{_orderBegin = b;}
	bool acquisitionOF(unsigned long indexAncien,unsigned long indexNouveau);
	void sendX3_ChangeOF(unsigned long indexAncien,unsigned long indexNouveau);
	bool sendX3_GetMatOF(); // SMO : STD-PR-OO1 : Pesee Matiere : pour recuperation liste OF depuis une matiere
	AdxOrder* getLockedOrder()const { return _lockedOrder;}
	void setLockedOrder(AdxOrder* _order ){ _lockedOrder = _order; }

// acces phases
	IlList* getPhaseList() const {return _phaseList;}
	AdxPhase* getCurrentPhase() const {return _currentPhase;}
	void setCurrentPhaseIndex(unsigned long index);
	int	getCurrentPhaseIndex() const{return _currentPhaseIndex;}
	AdxPhase* getPhase(unsigned long index) const {
				AdxPhase* phase = (AdxPhase*)(*_phaseList)[index];
				return phase;}
	int getNbPhases() const {return _nbPhases;}
	void setNbPhases(int nbPhases) { _nbPhases = nbPhases;}
	int getNbPhasesPesees() const {return _nbPhasesPesees;}	
	void setNbPhasesPesees(const int nb);
	bool getEnCoursDePeseeParArticle() const {return _enCoursDePeseeParArticle;}
	void setEnCoursDePeseeParArticle(bool enCoursDePeseeParArticle) { _enCoursDePeseeParArticle = enCoursDePeseeParArticle;}
	bool getPhaseBegin() const {return _phaseBegin;}
	void setPhaseBegin (const bool& b)	{_phaseBegin = b;}
	void sendX3_ChangePhase(); // pesée par matière : verrouillage du couple phase/composant de l'OF
	//bool acquisitionPhase();
// acces composants
	IlList* getComposantList_Art() const {return _composantList_Art;}
	int getNbComposants_Art() const {return _nbComposants_Art;}
	void setNbComposants_Art(int nbComposants) { _nbComposants_Art = nbComposants;}
	int getIndexComposant_Art(const AdxComposant* composant); // renvoie l'index precis du composant
	int getIndexComposant_Art(const char* composant);	// renvoie l'index du premier composant de meme libelle 
	AdxComposant* getComposant_Art(unsigned long index) const {
			AdxComposant* composant = (AdxComposant*)(*_composantList_Art)[index];
			return composant;}
	bool sendX3_GetMatMat(const char* composant); // SMO : STD-PR-OO1 : Pesee Matiere : pour recuperation liste des matieres
// acces matiere courante
	AdxComposant* getCurrentComposant() const {return _currentComposant;}
	void setCurrentComposantIndex(unsigned long index);
	int	getCurrentComposantIndex() const{return _currentComposantIndex;}	
	bool getComposantBegin() const {return _composantBegin;}
	void setComposantBegin (const bool& b)	{_composantBegin = b;}
	bool getComposantAlloue() const {return _composantAlloue;}
	void setComposantAlloue (const bool& b)	{_composantAlloue = b;}
// acces balances
	AdxBalance* getCurrentBalance() const {return _currentBalance;}
	IlList* getBalanceList() const {return _balanceList;}
	AdxBalance* getBalance(unsigned long index) const {
				AdxBalance* balance = (AdxBalance*)(*_balanceList)[index];
				return balance;}
	int getNbBalances() const {return _nbBalances;}
	int getNbBalancesAEtalonner() const {return _nbBalancesAEtalonner;}
	void setCurrentBalanceIndex(unsigned long index);
	void setNbBalances(int nbBalances) { _nbBalances = nbBalances;}
	void setNbBalancesAEtalonner(int nbBalancesAEtalonner)
		{ _nbBalancesAEtalonner = nbBalancesAEtalonner;}
// acces fiches ISM
	IlList* getFicheISMList() const {return _ficheISMList;}
	AdxFicheISM* getFicheISM(unsigned long index) const {
				AdxFicheISM* ficheISM = (AdxFicheISM*)(*_ficheISMList)[index];
				return ficheISM;}
	int getNbFichesISM() const {return _nbFichesISM;}
	void setNbFichesISM(int nbFichesISM) { _nbFichesISM = nbFichesISM;}
	AdxFicheISM* getCurrentFicheISM() const {return _currentFicheISM;}
// acces fiches ISM recipient
	IlList* getFicheISMRecipientList() const {return _ficheISMRecipientList;}
	AdxFicheISMRecipient* getFicheISMRecipient(unsigned long index) const {
				AdxFicheISMRecipient* ficheISMRecipient = 
					(AdxFicheISMRecipient*)(*_ficheISMRecipientList)[index];
				return ficheISMRecipient;}
	int getNbFichesISMRecipient() const {return _nbFichesISMRecipient;}
	void setNbFichesISMRecipient(int nbFichesISMRecipient)
		{ _nbFichesISMRecipient = nbFichesISMRecipient;}
// acces recipients
	IlList* getRecipientList() const {return _recipientList;}
	AdxRecipient* getRecipient(unsigned long index) const {
				AdxRecipient* recipient = (AdxRecipient*)(*_recipientList)[index];
				return recipient;}
	int getNbRecipients() const {return _nbRecipients;}
	void setNbRecipients(int nbRecipients) { _nbRecipients = nbRecipients;}
//acces lot
	IlList* getLotList() const {return _lotList;}
	void setLotList(IlList* lotList);
	bool compareLotList(IlList* lotList);
	AdxLot* getCurrentLot() const {return _currentLot;}
	int	getCurrentLotIndex() const{return _currentLotIndex;}
	void setCurrentLotIndex(unsigned long index);
	AdxLot* getLot(unsigned long index) const {
				AdxLot* lot = (AdxLot*)(*_lotList)[index];
				return lot;}
	int getNbLots() const {return _nbLots;}
	void setNbLots(int nbLots) { _nbLots = nbLots;}
	int getNbLotsPeses() const {return _nbLotsPeses;}	
	void setNbLotsPeses(const int nb);
	bool getLotBegin() const {return _lotBegin;}
	void setLotBegin (const bool& b)	{_lotBegin = b;}
	bool acquisitionLots(double	quantite);
	

// acces guide etalonnage
	IlList* getEtalonList() const {return _etalonList;}
	AdxEtalon* getCurrentEtalon() const {return _currentEtalon;}
	void setCurrentEtalonIndex(unsigned long index);
	int	getCurrentEtalonIndex() const{return _currentEtalonIndex;}
	AdxEtalon* getEtalon(unsigned long index) const {
				AdxEtalon* etalon = (AdxEtalon*)(*_etalonList)[index];
				return etalon;}
	int getNbEtalons() const {return _nbEtalons;}
	void setNbEtalons(int nbEtalons) { _nbEtalons = nbEtalons;}
	int getNbLignes() const {return _nbLignes;}
	void setNbLignes(int nbLignes) { _nbLignes = nbLignes;}
	int getNbLignesValidees() const {return _nbLignesValidees;}	
	void setNbLignesValidees(const int nb);
	bool getEtalonBegin() const {return _etalonBegin;}
	void setEtalonBegin (const bool& b)	{_etalonBegin = b;}
	bool getPeseeLancee() const {return _peseeLancee;}
	void setPeseeLancee (const bool& b)	{_peseeLancee = b;}
	// sr 02.12
	bool getOkToContinue() const {return _okToContinue;}
	void setOkToContinue (const bool& b)	{_okToContinue = b;}
// acces unites
	IlList* getUnitList() const {return _unitList;}
	void setUnitList(IlList* uniteList);
	int getNbUnits() const {return _nbUnits;}
	void setNbUnits(int nbUnits) { _nbUnits = nbUnits;}
// renvoie le poidsAConvertir exprime dans l'uniteDepart, converti dans l'unite d arrivee
	double convertir(double poidsAConvertir, const char* uniteDepart, const char* uniteArrivee);
// renvoie le poidsAConvertir exprime dans l'uniteDepart, converti dans l'unite d arrivee
//  sr 10.03 créé et utilisée uniquement pour le retour de tarage 
    double convertir2(double poidsAConvertir, const char* uniteDepart, const char* uniteArrivee);
// mm 12.09 Passage en majuscule des unités 
	char * majuscule(const char* unite);
// mm 09.10 Raz des Listes 
	void razListeFicheISM();
	void razListeOF();
	void razListePhase();
	void razListeComposant();


	bool loadData(  const char* PARfileName,		//parameters
					const char* MWGfileName,		//orders
					const char* PHAfileName,		//phases
					const char* MATfileName,		//matieres
					const char* SLEfileName,		//balances
					const char* HSHfileName,		//fiches ISM
					const char* CTNfileName,		//fiches ISM recipient
					const char* TCOfileName,		//unite
					const char* CGDfileName,		//guides etalonnage
					const char* UIDfileName			//X3-67237: file containing the user id (indicates pass or fail for credentials)
				   ); 
	bool loadLots( const char* LotfileName);
	void imprimeLots();
	void imprimeEtAlloueLots();
	void alloueLots();
	bool ReloadAll();
    void saveLots();
	int getIndexNumOF(const char* numOF);
	int getIndexPhase(const int phase);
	int getIndexLot(const char* lot);
	int getIndexLotParCuve(const char* cuve);
	int getIndexEtalon(const char* numEtalon);
	int getIndicateurProcedure() const {return _indicateurProcedure;}
	char*			getComposantProcedure()	const {return _composantProcedure;} // SMO : 28/07/2010
	AdxOrder*		getOFProcedure()		const {return _OFProcedure;}
	AdxPhase*		getPhaseProcedure()		const {return _phaseProcedure;}
	void setIndicateurProcedure(int i);
	void PositionneProcedurePhaseAttente();
	void PositionneProcedureOFAttente();
	void PositionneProcedureComposantAttente(); // SMO : 17/08/2010
	void lanceProcedureEnAttente();

	void sendX3_PeseePartielle();
	void sendX3_FinLot();
	void sendX3_FinComposant();
	void sendX3_FinComposant_Art();	// mm 10.10 : Fin composant en pesée par article
	void sendX3_FinPhase();
	void sendX3_FinOF();
	void sendX3_SoldeEmballage();
	void sendX3_MajEmballage(int wsens); // sens de la mise à jour : 1 en plus, 2 en moins
	void SendX3_ChangementOFNonPese(AdxOrder* order);
	void SendX3_InterruptionComposant();
	void SendX3_ChangementComposant();
	void SendX3_InterruptionPhase();
	void SendX3_InterruptionOF();
	void SendX3_Procedure(int i); // i = 1 ouv de Box; 2 = fin de phase; 3 = fin d'OF; 4 = pesee matiere
	bool SendX3_CheckCredentials(bool GetCred, bool ShowMsg);		//X3-67237: Have X3 prompt and validate the user id & password
	void SendX3_Reconciliation(); 
	void SendX3_Aide();
	void sendX3_Etalonnage(int sta);//sta = 1 fin d'etalonnage KO ; =2 fin OK
	void ouvreLigneEtalonnage();
	void saveLigneEtalonnage();
	void closeLigneEtalonnage();
	void savePesee(int fin);  //fin = 1 fin de phase; =2 fin OF; 0 sinon
	void sendX3_soldeMatiereSansQuantite();
	void sendX3_FinPhaseBis();
	void sendX3_FinOFBis();
	void SendX3_Refresh();   // sr 11.02 reactualisation des donnees
    void sendX3_AllocLot(double	quantite);
    void SendX3_ReloadAll(); // sr 03.04 réextraction allocs si pesée > prévu
	void SendX3_ConsultationStockDetaille();	// mm 04.10
	void SendX3_XtractInitial();	// mm 09.10
	void sendX3_InterruptionPeseeMulti();	// mm 09.12

	// SMO : STD-PR-OO1 : Pesee Matiere : 16/07/2010
	// pour sauvegarde des infos selectionnes lors de la pesee matiere,

	// accès aux données de la matière
	char*			getPseMatCurrentMat()							{return _pseMat_currentMat;}
	char*			getPseMatCurrentMatLib()						{return _pseMat_currentMatLib;}
	int				getPseMatCurrentMatIndexComposant()				{return	_pseMat_currentIndexComposant;}	
	void			setPseMatCurrentMatIndexComposant(int index)	{ _pseMat_currentIndexComposant = index; }
	void			setCurrentComposantIndexPseMat(const char* composant,const char* libComposant, int index);

	//mm 08.10
	bool			getPseMatMatiereBegin()const {return _pseMat_matiereBegin;}
	void			setPseMatMatiereBegin(const bool& b){_pseMat_matiereBegin = b;}
	
	// --------- 06.04 Unicode
	const char * getStringUnicode(AdxCsvLine* line, long index);	
	UINT getCodepage()
	{
		return _codepage;
	}
	char* getstringUTF8()
	{
		return _stringUTF8;
	}
	char* getstringMBS()
	{
		return _stringMBS;
	}
	// ----------


protected :
	
	// --------- 06.04 Unicode
	UINT						_codepage;		
	char*						_stringUTF8;
	char*						_stringMBS;
	// --------- 

	char*						_szCheminCsv1;
	char*						_szCheminCsv2;
	char*						_szCheminCsv3;
	char*						_szCheminCsv4;
	char*						_szCheminCsv5;
	char*						_szCheminCsv6;
	char*						_szCheminCsv7;
	char*						_szCheminCsv8;
	char*						_szCheminCsv9;
	char*						_szCheminCsv10;
	char*						_szCheminCsv11;
	char*						_szCheminCsv12;
	char*						_szCheminCsv13;
	char*						_szCheminCsv14;				//X3-67237 
	AdxInterface*				_interface;
// donnees
	char*						_language;
	AdxDate*					_dateJour;
	char*						_utilisateur;
	char*						_application;
	char*						_lieu;
	char*						_box;
	char*						_ouvertureBox;
	int							_ouvertureBoxOblig;				// 1: non; 2: oui; 3 deja fait
	char*						_videBoxFinOF;
	int							_videBoxFinOFOblig;
	char*						_videBoxFinPhase;
	int							_videBoxFinPhaseOblig;
	char*						_videBoxFinMatiere;				// SMO : STD-PR-OO1 : Pesee Matiere
	int							_videBoxFinMatiereOblig;		// SMO : STD-PR-OO1 : Pesee Matiere
	bool				        _attenteProcedureFinComposant;  // SMO : STD-PR-OO1 : Pesee Matiere
	bool				        _attenteProcedureFinOF;
	bool						_attenteProcedureFinPhase;
	char*						_peseePartielle;
	int							_peseePartielleCode;			// 1: interdite; 2: autorisee
	char*						_modifLigneStock;
	int							_modifLigneStockCode;
	char*						_recontroleArticle;
	int							_recontroleArticleCode;
	char*						_recontroleCuve;				// 1 : non ; 2 : cuve
	int							_recontroleCuveCode;
	char*						_prioriteAllocation;			// 1: OF ; 2 : box de pesée
	int							_prioriteAllocationCode;
	char*						_depotBox;
	char*						_emplacementBox;
	char*						_allocationAuto;				// 1: non; 2: oui;
	int							_allocationAutoCode;
	int							_longueurLot;
	int							_redressementNegatif;			// 1: non; 2: oui;
	int							_codeOFEnCoursPesee;
	char*						_libOFEnCoursPesee;
	int							_codeOFPeseBox;
	char*						_libOFPeseBox;
	int							_codeMatEnCoursPesee;
	char*						_libMatEnCoursPesee;
	int							_codeMatPese;
	char*						_libMatPese;
	int							_chargementListMat;				// mm 
	int							_applicationTolerance;			// 113445 mm 07.2016
	int							_exceedingTolerancePos;			// 116324 mm 08.2016
	//--------------------------------------------------------------------------------------------//
	// 103422 mm 01.2015 - Découpage du CAB et recontrôle
	int							_decoupageCAB;					
	char*						_libDecoupageCAB;
	int							_typeCAB;
	int							_suppBlanc;
	int							_numZoneArticle;
	char*						_separateurArt;
	int							_numZoneLot;
	char*						_separateurLot;
	int							_numZoneSlo;
	char*						_separateurSlo;
	int							_longueurArt;
	int							_debutArt;
	int							_longueurLot2;
	int							_debutLot;
	int							_longueurSlo;
	int							_debutSlo;
	//--------------------------------------------------------------------------------------------//
	IlList*						_orderList;
	int							_nbOrders;
// ordre choisi en pesee
	AdxOrder*					_currentOrder;
//position de l'ordre courant dans la liste (pour MAJ)
	unsigned long				_currentOrderIndex;
// indique si l ordre est commence de peser 0 non/1 oui
	bool						_orderBegin;

	IlList*						_phaseList;
	int							_nbPhases;
	int							_nbPhasesPesees;
// indique que la même pesée est déjà en cours sur un autre poste : 0 false/ 1 true - mm 05.11
	bool						_enCoursDePeseeParArticle;	
// phase choisie en pesee
	AdxPhase*					_currentPhase;
//position de la phase courante dans la liste (pour MAJ)
	unsigned long				_currentPhaseIndex;
// indique si la phase est commence de peser 0 non/1 oui
	bool						_phaseBegin;

	IlList*						_composantList_Art;
	int							_nbComposants_Art;
// matiere choisie en pesee
	AdxComposant*				_currentComposant;
//position de la matiere courante dans la liste de la phase courante(pour MAJ)
	unsigned long				_currentComposantIndex;
// indique si la matiere est commence de peser 0 non/1 oui
	bool						_composantBegin;
// indique si la matiere a ete allouee ou non
	bool						_composantAlloue;

	IlList*						_lotList;
	int							_nbLots;
	int							_nbLotsPeses;
// lot choisi en pesee
	AdxLot*						_currentLot;
//position du lot courant dans la liste (pour MAJ)
	unsigned long				_currentLotIndex;
// indique si le lot est commence de peser 0 non/1 oui
	bool						_lotBegin;

	IlList*						_balanceList;
	// balance choisie en pesee
	AdxBalance*					_currentBalance;
//position de la balance courante dans la liste (pour MAJ)
	unsigned long				_currentBalanceIndex;
	int							_nbBalancesAEtalonner;

	IlList*						_ficheISMList;
	int							_nbFichesISM;
	AdxFicheISM*				_currentFicheISM;

	IlList*						_ficheISMRecipientList;
	int							_nbFichesISMRecipient;

	IlList*						_recipientList;
	IlList*						_unitList;
	int							_nbUnits;
	
	int							_nbBalances;
	int							_nbRecipients;

	int							_indicateurProcedure;

	//AdxComposant*				_composantProcedure;	// SMO : 28/07/2010 : composant pour lequel il reste un vide de box a faire
	char *						_composantProcedure;	// mm 02.11 - déclenchement d'une procédure de vide de box
														//  au moment du changement matière
	AdxOrder*					_OFProcedure;			// ordre pour lequel il retse un vide de box a faire
	AdxPhase*					_phaseProcedure;		// phase pour laquelle il retse un vide de box a faire

	IlList*						_etalonList;
	int							_nbEtalons;
	int							_nbLignes;
	int							_nbLignesValidees;

// Etalon en cours
	AdxEtalon*					_currentEtalon;
//position de l'etalon courant dans la liste (pour MAJ)
	unsigned long				_currentEtalonIndex;
// indique si l etalonnage est commence 0 non/1 oui
	bool						_etalonBegin;
// La pesée a-t-elle été lancée ?
	bool						_peseeLancee;

	// SMO : STD-PR-OO1 : Pesee Matiere : 16/07/2010
	// ajout de variables pour sauvegerder des valeurs dans le cas pesee matiere 
	char*						_pseMat_currentMat;		// nom de la matiere
	char*						_pseMat_currentMatLib;	// nom de la matiere libelle
	int							_pseMat_currentIndexComposant ; // index du composant choisi dans la matrice de sélection des matières
	bool						_pseMat_matiereBegin;	// indique si on a commencé de peser la matière 0 non/1 oui
	bool						_okToContinue;			// indique si ValidationCB de AdxChoixOF est ok 0 non/1 oui

	//115769 mm 04.2016
	AdxOrder*					_lockedOrder;

//X3-67237: Added variables for user id/password validation
	int							_usrwei;						//X3-67237: User Weighing Validation Flag
	int							_boxpwd;						//X3-67237:
	int							_ewopwd;						//X3-67237:
	int							_phapwd;						//X3-67237:
	int							_matpwd;						//X3-67237:
	char*						_X3UserID;						//X3-67237: The "real" user id (from X3)
	int							_X3Ver;							//X3-67237: Holds the "version" of the DLL 

// fonctions

protected :
	
	// -------- 06.04 Unicode
	void setCodepage(UINT codepage)
	{
		_codepage = codepage;
	}
	void setstringUTF8(char* stringUTF8)
	{
		if( _stringUTF8 != NULL)
			delete [] _stringUTF8;
		_stringUTF8 = new char[ strlen( stringUTF8) +1];
		strcpy( _stringUTF8, stringUTF8);
	}
	void setstringMBS(char* stringMBS)
	{
		if( _stringMBS != NULL)
			delete [] _stringMBS;
		_stringMBS = new char[ strlen( stringMBS) +1];
		strcpy( _stringMBS, stringMBS);
	}
	// -------- 

	void init(AdxInterface* m_interface);


private :
	bool loadParameters( const char* ParamfileName);
	bool loadOrders( const char* OrderfileName);
	bool loadPhases( const char* PhasefileName);
	bool loadComposants( const char* MatierefileName, int lcode);
	bool loadBalances( const char* BalancefileName);
	bool loadFichesISM( const char* FicheISMfileName);
	bool loadFichesISMRecipient( const char* FicheISMRecipientfileName);
	bool loadUnits( const char* UnitfileName);
	bool loadEtalons( const char* EtalonfileName);
	bool loadUserID( const char* UIDfileName);				//X3-67237
};

#endif /*_ADXDATA_H_*/
