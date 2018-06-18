// AdxInterface.h
// --------------
// project : Adonix X3 Optimisation
// author : ILOG SCM Consulting 1999.12.08
// V124 : MC 2000.07.07
//--------------------------------------------------------------
//

#if !defined _ADXINTERFACE_H_
#define _ADXINTERFACE_H_

#include <Ilviews/Macros.h>
#include <Ilviews/Ilv.h>
#include <ilviews/gadgets/stdialog.h>
#include <ilog/list.h>
#include <ilviews/bitmaps/png.h>				// v5
#include <ilviews/bitmaps/jpg.h>				// v5
#include <atlstr.h>
#include <fstream>								// 06.04 TRACE

using std::ifstream;							// 06.04 TRACE
using std::ofstream;							// 06.04 TRACE
using std::fstream;								// 06.04 TRACE

class IlvDisplay;
class AdxGadgetContainer;
class AdxSelection_OF;
class AdxSelection_Phase;
class AdxSelection_MWF;
class AdxSelection_LOT;
class AdxSelection_Balance;
class AdxSelection_Recipient;
class AdxSelection_EtalonLigne;
class AdxAccueil;
class AdxChoix_OF;
class AdxChoix_Balance;
class AdxPesee_Etalon;
class AdxClavier_Tactile;
class AdxPesee_OF;
class AdxPhrase_Secu;
class AdxRecontrole_OF;
class AdxMessage;
class AdxWeighingInterface;
//class AdxBalanceRow;

class AdxData;
//class AdxOrder;


class AdxInterface  {
  // CTOR - DTOR
public:
	virtual ~AdxInterface();
	AdxInterface(){init();};

//--------------------------------------------------------------
// accessors & modifiers
public:
	IlvDisplay*  getDisplay() const {return  _display;}
	void setDisplay(IlvDisplay* display) { _display = display;}
	AdxAccueil*  getAccueil() const {return  _accueil;}
	AdxChoix_OF*  getChoix_OF() const {return  _choix_OF;}
	AdxChoix_Balance*  getChoix_Balance() const {return  _choix_Balance;}
	AdxPesee_Etalon*  getPesee_Etalon() const {return  _pesee_Etalon;}
	AdxClavier_Tactile*  getClavier_Tactile() const {return  _clavier_Tactile;}
	AdxSelection_OF* getSelection_OF() const {return _selection_OF;}
	AdxSelection_Phase* getSelection_Phase() const {return _selection_Phase;}
	AdxSelection_MWF* getSelection_MWF() const {return _selection_MWF;}
	AdxSelection_LOT* getSelection_LOT() const {return _selection_LOT;}
	AdxSelection_Balance* getSelection_Balance() const {return _selection_Balance;}
	AdxSelection_EtalonLigne* getSelection_EtalonLigne() const {return _selection_Ligne;}
	AdxSelection_Recipient* getSelection_Recipient() const {return _selection_Recipient;}
	AdxPesee_OF* getPesee_OF() const {return _pesee_OF;}
	AdxPhrase_Secu* getPhrase_Secu() const {return _phrase_Secu;}
	AdxRecontrole_OF* getRecontrole_OF() const {return _recontrole_OF;}
	AdxMessage* getMessage() const {return _message;}
	void setMessage(AdxMessage* message) { _message = message;}
	bool envoieMessage(CString mess, bool OUINON);
	AdxWeighingInterface* getWeighingInterface() const {return _weighingInterface;}
	char* getStructX3 (void) const {return _pStructX3;}
	char* getPathX3 (void) const {return _pszPathX3;}
	char* getPathCACHE (void) const {return _pszPathCACHE;}
	char* getAppName (void) const {return _appName;}
	IlvAny getInstance (void) const {return _instance;}
	AdxData*  getDonnees() const {return  _donnees;}
	IlvFont* getFont() const { return	_font;}
	void setFonctionEnCours(const int value) {_fonctionEnCours = value;}
	int getFonctionEnCours (){ return _fonctionEnCours;}
	void setPeseeEnCuve(const bool b) {_peseeEnCuve = b;}
	bool getPeseeEnCuve(){ return _peseeEnCuve;}
	void setTraceMode(const int value) {_traceMode = value;}		// 06.04 TRACE
	int getTraceMode (){ return _traceMode;}						// 06.04 TRACE
	void setMsgMode(const int value) {_msgMode = value;}		    // 12.04 MESSAGE
	int getMsgMode (){ return _msgMode;}						    // 12.04 MESSAGE
	void setScaMsgMode(const int value) {_scaMsgMode = value;}		// sr 01.12 APCPRD-511
	int getScaMsgMode (){ return _scaMsgMode;}						// sr 01.12 APCPRD-511
	void setClearBuffer(const bool value) {_ClearBuffer = value;}		// sr 01.12 APCPRD-511
	bool getClearBuffer (){ return _ClearBuffer;}						// sr 01.12 APCPRD-511

	void setSequenceAppelante(const int value) {_sequenceAppelante = value;}
	int getSequenceAppelante (){ return _sequenceAppelante;}
	void setPanneauAppelant(AdxGadgetContainer* container) {_panneauAppelant = container;}
	AdxGadgetContainer* getPanneauAppelant() {return _panneauAppelant;}
	//Evolution Graphique PNG
	// Ajout de l'image de fond pour toutes les fenêtres
	IlvBitmap* LoadBackgroundBitmap(IlvDisplay* Display,AdxGadgetContainer* wnd);



	// API
	void AdxOpenTrace ();											// 06.04 TRACE
	void AdxCloseTrace ();											// 06.04 TRACE
	void AdxWriteTrace (char* message);								// 06.04 TRACE
	void showWindow(IlvSystemView parent, IlvRect* bbox);
//	void showWindow(IlvSystemView parent, const IlvRect& bbox);
	void showAccueilWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
//	void showAccueilWindow(IlvSystemView parent, const IlvRect& bbox,
//			   IlvBoolean visible);
	void showChoix_OFWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showChoix_BalanceWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showPesee_EtalonWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showClavier_TactileWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showSelection_OFWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showSelection_PhaseWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showSelection_MWFWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showSelection_LOTWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showSelection_BalanceWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showSelection_RecipientWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showSelection_EtalonLigneWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showPesee_OFWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showPhrase_SecuWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showRecontrole_OFWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);
	void showMessageWindow(IlvSystemView parent, IlvRect* bbox,
			   IlvBoolean visible);


	bool lectureDictionnaire(bool appel);
	void notify();

	static IlvAny      DllInstance;

	IlvBoolean initInterface( IlvAny,
							const char* appName,
							const char* language,
							const char* pszPathX3,
							const char* pszPathIni,
							const char* pszPathCSV, // GBE 10.08 pour générer la trace au bon endroit (vista)
							const char* szPathCACHE,
							const char* pStructX3);

	IlvBoolean completeInitInterface( IlvAny,
									const char* appName,
									const char* language,
									const char* pszPathX3,
									const char* pStructX3);
	void closeAllWindows();
	

protected :
// donnees
	IlvDisplay*					_display;
	AdxAccueil*					_accueil;
	AdxChoix_OF*				_choix_OF;
	AdxChoix_Balance*			_choix_Balance;
	AdxPesee_Etalon*			_pesee_Etalon;
	AdxClavier_Tactile*			_clavier_Tactile;
	AdxSelection_OF*			_selection_OF;
	AdxSelection_Phase*			_selection_Phase;
	AdxSelection_MWF*			_selection_MWF;
	AdxSelection_LOT*			_selection_LOT;
	AdxSelection_Balance*		_selection_Balance;
	AdxSelection_Recipient*		_selection_Recipient;
	AdxSelection_EtalonLigne*	_selection_Ligne;
	AdxPesee_OF*				_pesee_OF;
	AdxPhrase_Secu*				_phrase_Secu;
	AdxRecontrole_OF*			_recontrole_OF;
	AdxMessage*					_message;
	AdxWeighingInterface*		_weighingInterface;
	char*						_pStructX3;
	char*						_pszPathX3;
	char*						_pszPathIni;
	char*						_pszPathCSV;
	char*                       _pszPathCACHE;
	char*						_appName;
	IlvAny						_instance;
	AdxData*					_donnees;
	IlvFont*					_font;
	int							_fonctionEnCours;
	// 1 pesee par OF
	// 2 pesee par Article
	// 3 pesee en fabrication
	bool						_peseeEnCuve;
public:
	int							_sequenceAppelante;
	AdxGadgetContainer*			_panneauAppelant;
	IlvInt						_traceMode;				// 06.04 TRACE
	ofstream					_traceFile;				// 06.04 TRACE
	IlvInt						_msgMode;				// 12.04 MESSAGE
	IlvInt						_scaMsgMode;			// 01.12 APCPRd-511
	bool						_ClearBuffer;			// GBE 04/10/2013 Clear du buffer au connectionTest
// fonctions
	void init();

};

#endif /*_ADXINTERFACE_H_*/
