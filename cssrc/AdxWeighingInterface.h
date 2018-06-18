// AdxWeighingInterface.h
// ----------------------
// project : Adonix X3 Scales
// author : MC
// V130 : MC 2001.05.28
//--------------------------------------------------------------
//

#ifndef AdxWeighingInterface_h
	#define AdxWeighingInterface_h

//#include <ilviews/resource.h>

//#include <windows.h>
#include <stddef.h>
#include <string.h>
#include <fstream>								// 06.04 TRACE

using std::ifstream;							// 06.04 TRACE
using std::ofstream;							// 06.04 TRACE
using std::fstream;								// 06.04 TRACE



class AdxMeid5;
class AdxMeid7;
class AdxMepm;
class AdxSartorius;
class AdxMSICS;
class AdxMultiCom;
class AdxInterface;
class AdxBalance;
class AdxGadgetContainer;

enum WeighingOperation
{
	APL_R,
	APL_W,
	APL_C,
	BIP,
	D_KBD,
	E_KBD,
	ART_I,
	ART_S,
	CHG_P,
	CHG_U,
	CHG_U_M,
	PDS_I,
	PDS_IR,
	PDS_S,
	WAIT_MSG,
	UNITE_P,
	RAZ,
	RAZ_MANUELLE,
	TAR,
	TAR_MANUELLE,
	POIDSCONSIGNE,
	RAZ_TAR,
	DETAR,
	DETAR_MANUELLE,
	DSPL,
	RAZ_DSPL,
	PRT, 
	ID_A,
	ID_B,
	ID_C,
	ID_D,
	CONTROLE_QUITTANCE,
	SERIAL_NUM,
    LAST_OP,
};

enum WeighingOrder
{
	RAZ_M,
	RAZ_A,
	TAR_M,
	TAR_A,
	RAZ_TAR_M,
	RAZ_TAR_A,
	CONS_TAR_M,
	CONS_TAR_A,
	POIDS_IMDT,
	POIDS_STAB_M,
	POIDS_STAB_A,
	MSG1,
	DISPL,
	CTRL_BAL_PRA,
	BIPP,
	CHGT_UP_M,
	CHGT_UP_A,
	UNT_PDS,
	CLAV_BAL,
	CLAV_BAL_LOCK,			// sr 01.12 APCPRD-729
	CLAV_BAL_UNLOCK,		// sr 01.12 APCPRD-729
	SERIAL_NUMBER,			// Num�ro de s�rie

	CHGT_P,					// Changement de plateau
	LAST_ORD,               //la laisser en dernier
};

/******************************************
 *    liste crois�e des ordres de pes�e   *
 ******************************************/

static char msg_ord[LAST_ORD][20] =
{
	"ZERO MANUEL        ",
	"ZERO AUTO.         ",
	"TARAGE MANUEL      ",
	"TARAGE AUTO.       ",
	"RAZ TARAGE MANUEL  ",
	"RAZ TARAGE AUTO.   ",
	"PESAGE A 0 MANUEL  ",
	"PESAGE A 0 AUTO.   ",
	"POIDS IMMEDIAT     ",
	"POIDS STABLE MANUEL",
	"POIDS STABLE AUTO. ",
	"MESSAGE LIGNE  3   ",
	"MESSAGE AFFICHEUR  ",
	"CTRL BAL PRATIQUE  ",
	"BIP                ",
	"CHGT U.P. MANUEL   ",
	"CHGT U.P. AUTO.    ",
	"U.P ACTUEL         ",
	"CLAV. BALANCE 1/0  ",
	"CLAV. BAL LOCK     ",
	"CLAV. BAL UNLOCK   ",
	"SERIAL UMBER       ",
	"CHANGEMENT PLATEAU ",
};


enum DriverStatus
{
	OK,
	PORT,
	EMPTY,
	CCLOSE,
	PCLOSE,
	ERROR1,
	UNKNOWN1,
	UNKNOWN2,
	NO_RESPONSE,
	LOGISTIC_ERROR,
	TRANSMIT_ERROR,
	SYNTAX_ERROR,
	UNAVAILABLE,
	SURCHARGE_ERROR,
	SOUSCHARGE_ERROR,
	UNKNOWN_ANSWER,
	OVERFLOW1, 
	OVERFLOW2,
	DYNAMIQUE,
	TRONCATED_RESPONSE,
	UNIT_ERROR,
	BAD_PLATE,
	LAST_ERR,                           //la laisser en dernier
};

static char tab_err[LAST_ERR][25] = 
{
	"bien pass�              ",
	"port non d�fini         ",
	"buffer vide             ",
	"carte inactive          ",
	"port serie inactif      ",
	"erreur de syntaxe niv1  ",
	"ordre niv1 inconnu      ",
	"ordre I/O niv2 inconnu  ",
	"pas de r�ponse          ",
	"erreur logique          ",
	"erreur de transmission  ",
	"erreur de syntaxe       ",
	"valeur indisponible     ",
	"plateau en surcharge    ",
	"plateau en sous-charge  ",
	"r�ponse erron�e         ",
	"niv1 buffer overflow    ",
	"niv2 buffer overflow    ",
	"donn�e dynamique        ",
	"r�ponse incompl�te      ",
	"unit� non pr�vue        ",
	"mauvais plateau         ",
};

enum WeighingStatus
{ 
	OK_STA,
	CHG_PLATE,
	CHG_PDS_UNIT,
	RAZ_OP,
	TAR_OP,
	RAZ_TAR_OP,
	ERR_LOGISTIC,
	SUR_CHARGE,
	SOUS_CHARGE,
	DYNAMIC_PDS,
	DATA_UNAVAILABLE,
	UNIT_BAL_NOT_CORRECT,
	PILOT_NOT_PRESENT,
	PORT_NOT_CORRECT,
	PORT_NOT_OPENED,
	NO_RESP,
	ERR_SYNTAX,
	ERR_TRANSMIT,
	SHORT_MSG,
	UNKNOWN_MSG,
	BAD_PLATE_MSG,
	LAST_MSG,                           //la laisser en dernier
};

static char msg_status [LAST_MSG][25] =
{	
	"&PeseeEffectuee         ",
	"&ChangementPlateau      ",
	"&ChangementUnitePoids   ",
	"&RemiseAZeroEffectuee   ",
	"&TarageEffectue         ",
	"&TareEffacee            ",
	"&LogicError             ",
	"&Surcharge              ",
	"&Souscharge             ",
	"&PoidsDynamique         ",
	"&Indisponible           ",
	"&UniteBalanceNonPrevue  ",
	"&PiloteNonDefini        ",
	"&NoPortIncorrect        ",
	"&BalanceNonReliee       ",
	"&PasDeReponse           ",
	"&SyntaxError            ",
	"&TransmitError          ",
	"&MessageTronque         ",
	"&MessageInconnu         ",
	"&BadPlate               ",
};

//#define nbDrv = 3
// 12/08/08 Sartorius modifi�
// 26/08/08 MT SICS 
static char driverNames [6][4] = 
{
	"ID5",
	"ID7",
	"MPM",
	"SAR",
	"SAM",
	"SIC"
};

/* gbe 06/11/07 Il manquait une dimension au tableau 
 *              depassement de memoire*/
/*static int driverFlag [3] = {0, 0, 0};*/
// 12/08/08 Sartorius modifi�
// 26/08/08 MT SICS 
static int driverFlag [6] = {0, 0, 0, 0, 0,0};

static int portFlag [8] = {0, 0, 0, 0, 0, 0, 0, 0};
static int baudRate [8] = {0, 0, 0, 0, 0, 0, 0, 0};
static int parity [8]	= {0, 0, 0, 0, 0, 0, 0, 0};
static int stopBits [8] = {0, 0, 0, 0, 0, 0, 0, 0};
static int byteSize [8] = {0, 0, 0, 0, 0, 0, 0, 0};

class AdxWeighingInterface {

//----------------------------------------------------------
//		
// Properties
//
protected:

	// Weighing operation
	WeighingOperation _weighingOperation;
	// Weighing operation result
	WeighingOperation _weighingReturnOp;
	// Weighing order
	WeighingOrder _weighingOrder;
	// Weighing status
	WeighingStatus _weighingStatus;
	// Driver status
	DriverStatus _driverStatus;
	// Weight
	double _weight;
	// Total Weight
	double _totWeight;
	// intermediate net weight result
 	double _resWeight;
	// Net weight result
	double _resNetWeight;
	// Gross weight result
	double _totResNetWeight;
	// Gross weight result
	double _resGrossWeight;
	// Tare
	double _tare;
	// Tare en unit� de poids balance
	double _tareUnitBal;
	// Tare result
	double _resTare;
	// Weighing short message
	char* _weighingShortMessage;
	// Weighing message
	char* _weighingMessage;
	// Weighing message result
	char* _resWeighingMessage;
	// Weight unit
	char* _weightUnit;
	// Weight unit result
	char* _resWeightUnit;
	// Balance
	AdxBalance* _balance;
	// Scale Number
	int _scaleNumber;
	// Message waiting time
	int _msgWaitingTime;
	// Multi Com
	AdxMultiCom* _multiCom;
	// Driver Meid5
	AdxMeid5* _meid5;
	// Driver Meid7
	AdxMeid7* _meid7;
	// Driver Mepm 3000
	AdxMepm* _mepm;
	// Driver Sartorius
	AdxSartorius* _sartorius;
	// 12/08/08 Driver Sartorius modifi�
	AdxSartorius* _sartoriusMod;
	// 26/08/08 MT SICS 
	AdxMSICS* _MSICS;
	// 09/09/11 Pesee multi-article 
	bool  _matiere1Pesee;	//false - aucune mati�re pesee
							//true - 1ere matiere pesee

	AdxInterface* _interface;

	AdxGadgetContainer*	_panneauAppelant;
	// GBE 16/09/08 Possibilit� de ne plus avoir de bouble pour arr�ter la pes�e
	HANDLE	 _hMutexStopPesee;	// Mutex pour la synchronization Indicateur de fin de pes�e
	bool     _bStopPesee;		// Indicateur de fin de pes�e
	HANDLE	 _hMutexCancel;		// Mutex pour la synchronization Indicateur d'annulation
	bool     _bCancel;			// Indicateur d'annulation
	HANDLE	 _hMutexValid;		// Mutex pour la synchronization Indicateur de validation
	bool     _bValid;			// Indicateur de validation
	HANDLE	 _hMutexComm;		// Mutex pour la synchronization des communications

public:

	int _weighingFlag;
/*
	HANDLE 	_hThread;

	DWORD _dwThreadID;

	HANDLE 	_hEventWeighing;

	bool _bActive;
*/
//----------------------------------------------------------
//		
// CTOR - DTOR
//
public:

	virtual ~AdxWeighingInterface();
	AdxWeighingInterface(AdxInterface* interf);
	

//----------------------------------------------------------
//		
// accessors & modifiers
//
public:
	void setStopPesee(bool value)
	{
		DWORD dwWaitResult;
		dwWaitResult = WaitForSingleObject(_hMutexStopPesee,INFINITE);
		if(dwWaitResult == WAIT_OBJECT_0)
		{
			_bStopPesee = value;
		}
		ReleaseMutex(_hMutexStopPesee);
	}
	bool getStopPesee()
	{
		DWORD dwWaitResult;
		bool  bRetour = false;
		dwWaitResult = WaitForSingleObject(_hMutexStopPesee,INFINITE);
		if(dwWaitResult == WAIT_OBJECT_0)
		{
			bRetour = _bStopPesee;
		}
		ReleaseMutex(_hMutexStopPesee);
		return (bRetour);
	}

	void setCancel(bool value);
	bool getCancel()
	{
		DWORD dwWaitResult;
		bool  bRetour = false;
		dwWaitResult = WaitForSingleObject(_hMutexCancel,INFINITE);
		if(dwWaitResult == WAIT_OBJECT_0)
		{
			bRetour = _bCancel;
		}
		ReleaseMutex(_hMutexCancel);
		return (bRetour);
	}

	void setValid(bool value);
	bool getValid()
	{
		DWORD dwWaitResult;
		bool  bRetour = false;
		dwWaitResult = WaitForSingleObject(_hMutexValid,INFINITE);
		if(dwWaitResult == WAIT_OBJECT_0)
		{
			bRetour = _bValid;
		}
		ReleaseMutex(_hMutexValid);
		return (bRetour);
	}

	void weighingOrderTreatment(bool bCheckPlate=true);
	void manualMode(bool bCheckPlate);
//	void automaticMode(void);
	void sendMsgScales(void);
	void EmissionReception(WeighingOperation ope,
						   AdxBalance* balance,
						   bool bCheckPlate);
	void getResponseScales(int nbWait,bool bCheckPlate);
	void editionMessage();
	void finPesee();
	bool finPeseePartielle();
	void connectionTest(AdxBalance* balance, bool bAppel);
	void initEcranBalance(AdxBalance* balance);
	void delay(int milliSec);
	bool controlePoids(double poidsPese);
	bool controlePoidsInf();
	bool controlePoidsSup();
	WeighingStatus statusEvents(void);
	WeighingStatus opeEvents(void);
	void setPanneauAppelant(AdxGadgetContainer* container) {_panneauAppelant = container;}
	AdxGadgetContainer* getPanneauAppelant() {return _panneauAppelant;}
	// 61152 mm 01.10
	void afChLower(char *plChValueES);
	void afChUpper(char *plChValueES);
	void afChRTrim (char * lChValeurES);
	void afChLTrim (char * lChValeurES);

	WeighingOperation getWeighingOperation() const
	{
		return _weighingOperation;
	}

	WeighingOperation getWeighingReturnOp() const
	{
		return _weighingReturnOp;
	}

	WeighingOrder getWeighingOrder() const
	{
		return _weighingOrder;
	}

	WeighingStatus getWeighingStatus() const
	{
		return _weighingStatus;
	}

	DriverStatus getDriverStatus() const
	{
		return _driverStatus;
	}

	double getWeight() const
	{
		return _weight;
	}

	double getResWeight() const
	{
		return _resWeight;
	}

    double getTotWeight() const
	{
		return _totWeight;
	}

	double getResNetWeight() const
	{
		return _resNetWeight;
	}

	double getTotResNetWeight() const
	{
		return _totResNetWeight;
	}

	double getResGrossWeight() const
	{
		return _resGrossWeight;
	}

	double getTare() const 
	{
		return _tare;
	}

	double getTareUnitBal() const 
	{
		return _tareUnitBal;
	}

	double getResTare() const 
	{
		return _resTare;
	}

	char* getWeighingShortMessage() const 
	{
		return _weighingShortMessage;
	}

	char* getWeighingMessage() const 
	{
		return _weighingMessage;
	}

	char* getResWeighingMessage() const 
	{
		return _resWeighingMessage;
	}

	char* getWeightUnit() const 
	{
		return _weightUnit;
	}

	char* getResWeightUnit() const 
	{
		return _resWeightUnit;
	}

	AdxBalance* getBalance() const
	{
		return _balance;
	}

	int getScaleNumber() const
	{
		return _scaleNumber;
	}

	int getMsgWaitingTime() const
	{
		return _msgWaitingTime;
	}

	AdxMultiCom* getMultiCom() const
	{
		return _multiCom;
	}

	AdxMeid5* getMeid5() const
	{
		return _meid5;
	}

	AdxMeid7* getMeid7() const
	{
		return _meid7;
	}

	AdxMepm* getMepm() const
	{
		return _mepm;
	}

	AdxSartorius* getSartorius() const
	{
		return _sartorius;
	}
	// 12/08/08 Sartorius modifi�
	AdxSartorius* getSartoriusMod() const
	{
		return _sartoriusMod;
	}

	// 26/08/08 MT SICS 
	AdxMSICS* getMSICS() const
	{
		return _MSICS;
	}

	AdxInterface* getInterface() const
	{
		return _interface;
	}
	// 09/09/11 mm - Pes�e multi-article
	bool getMatiere1Pesee() const
	{
		return _matiere1Pesee;
	}

	int getWeighingFlag() const
	{
		return _weighingFlag;
	}

	void setWeighingFlag( const int& value)
	{
		_weighingFlag = value;
	}

	void setBalance( AdxBalance* balance)
	{
		_balance = balance;
	}

//protected:

	void setWeighingOperation( WeighingOperation operation)
	{
		_weighingOperation = operation;
	}

	void setWeighingReturnOp( WeighingOperation operation)
	{
		_weighingReturnOp = operation;
	}

	void setWeighingOrder( WeighingOrder order)
	{
		_weighingOrder = order;
	}

	void setWeighingStatus( WeighingStatus status)
	{
		_weighingStatus = status;
	}

	void setDriverStatus( DriverStatus status)
	{
		_driverStatus = status;
	}

	void setWeight( const double& value)
	{
		_weight = value;
	}
  	void setTotWeight( const double& value)
	{
		_totWeight = value;
	}


	void setResWeight( const double& value)
	{
		_resWeight = value;
	}
 	void setTotResWeight( const double& value)
	{
		_totResNetWeight = value;
	}


	void setResNetWeight( const double& value)
	{
		_resNetWeight = value;
	}

	void setResGrossWeight( const double& value)
	{
		_resGrossWeight = value;
	}

	void setTare( const double& value)
	{
		_tare = value;
	}

	void setTareUnitBal( const double& value)
	{
		_tareUnitBal = value;
	}

	void setResTare( const double& value)
	{
		_resTare = value;
	}

	void setWeighingShortMessage( const char* str)
	{
		if( _weighingShortMessage != NULL)
		{
			delete [] _weighingShortMessage;
		}
		_weighingShortMessage = new char[ strlen( str) +1];
		strcpy( _weighingShortMessage, str);
	}

	void setWeighingMessage( const char* str)
	{
		if( _weighingMessage != NULL)
		{
			delete [] _weighingMessage;
		}
		_weighingMessage = new char[ strlen( str) +1];
		strcpy( _weighingMessage, str);
	}

	void setResWeighingMessage( const char* str)
	{
		if( _resWeighingMessage != NULL)
		{
			delete [] _resWeighingMessage;
		}
		_resWeighingMessage = new char[ strlen( str) +1];
		strcpy( _resWeighingMessage, str);
	}

	void setWeightUnit( const char* str)
	{
		if( _weightUnit != NULL)
		{
			delete [] _weightUnit;
		}
		_weightUnit = new char[ strlen( str) +1];
		strcpy( _weightUnit, str);
	}

	void setResWeightUnit( const char* str)
	{
		if( _resWeightUnit != NULL)
		{
			delete [] _resWeightUnit;
		}
		_resWeightUnit = new char[ strlen( str) +1];
		strcpy( _resWeightUnit, str);
	}

	void setScaleNumber( const int& value)
	{
		_scaleNumber = value;
	}

	void setMsgWaitingTime( const int& value)
	{
		_msgWaitingTime = value;
	}

	void setMultiCom( AdxMultiCom* multiCom)
	{
		_multiCom = multiCom;
	}

	void setMeid5( AdxMeid5* meid5)
	{
		_meid5 = meid5;
	}

	void setMeid7( AdxMeid7* meid7)
	{
		_meid7 = meid7;
	}

	void setMepm( AdxMepm* mepm)
	{
		_mepm = mepm;
	}

	void setSartorius( AdxSartorius* sartorius)
	{
		_sartorius = sartorius;
	}

	// 12/08/08 Sartorius modifi�
	void setSartoriusMod( AdxSartorius* sartorius)
	{
		_sartoriusMod = sartorius;
	}

	// 26/08/08 MT SICS 
	void setMSICS( AdxMSICS* MSICS)
	{
		_MSICS = MSICS;
	}

	void setInterface( AdxInterface* interf)
	{
		_interface = interf;
	}

	bool initWeighingInterface();
	void weighingOrder();

	//09/09/11 mm - Pes�e multi-article
	void setMatiere1Pesee( bool _mat1Pesee)
	{
		 _matiere1Pesee = _mat1Pesee;
	}
};

#endif /* AdxWeighingInterface_h */
