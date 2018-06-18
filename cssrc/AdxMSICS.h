// AdxMSICS.h
// ----------
// project : Sage X3 Scales
// author : gbe
//--------------------------------------------------------------
//

#ifndef AdxMSICS_h
	#define AdxMSICS_h

class AdxWeighingInterface;

/*************************************************
*     constantes generales                       *
*************************************************/
#define MAXC         256               //nombre maxi d'éléments de la chaine
                                       // d'entrée aval
#define DOWN_BUF_SIZ 40                //nombre maxi d'éléments de la chaine
                                       // de sortie aval

#define OFFSET_NAME 0x02da

#define ATTENTE_UNITAIRE 5             //delai d'attente maxi entre deux caracteres
                                       // a lire depuis le buffer
#define NB_MAX_RETRY     2             //nombre de repetition maximum d'une demande
                                       // de lecture d'un element

/*************************************************
*     constantes ASCII du protocole              *
*************************************************/
#define NUL      0x00
#define ACK      0x06                  //accuse de réponse positive
#define LF       0x0a
#define CR       0x0d
#define SYN      0x16
#define DEL      0x127

/*************************************************
*              JEU D'INSTRUCTIONS                *
*************************************************/
// reponses d'erreurs possibles survenues en retour d'une opération de pesage

// Erreurs 
#define SYNTAXERROR		"ES"
#define TRANSMISSION_ERROR	"ET"
#define LOGICAL_ERROR		"EL"

#define ERROR2      'E'
#define LOGISTIC    'L'
#define SYNTAX      'S'
#define TRANSMIT    'T'
#define SURCHARGE   '+'
#define SOUSCHARGE  '-'
#define NOTEXECUTE  'I'

// requetes de pesage

#define APPLICATION 'A'
#define PLATEAU     'A'
#define KEYP_A      'A'
#define OP_ACTION   'A'
#define PC_ACTION   'B'
#define KEYP_B      'B'
#define KEYP_C      'C'
#define KEYP_D      'D'
#define DISPLAY     'D'
#define RAZDISPLAY  "DW"
#define DYNAMIC     'D'
#define IMMEDIAT    'I'
#define STABLE      'S'
#define INCORRECT   'I'
#define KEY_PAC     'K'
#define LOCKK       "K 2"
#define UNLOCKK     "K 4"
#define KEYONLY     "K 3"
#define REPEAT      'R'
#define LECTURE     'R'
#define NET         'S'
/*
#define SENDX       'S'
*/
#define SOUND       'S'
#define CHANGE      'S'
#define TARE        'T'
#define SETTARE     "TA"
#define ASKTARE     "TA"
#define RAZTARE     "TAC"
#define ART_M       'T'
#define UNIT_POIDS  'U'
#define WRITE       'W'
#define ARTICLE     'X'
#define REMISEAZERO 'Z'
#define DISABLE     '0'
#define ENABLE      '1'
#define KEYTAR      '3'
#define KEYRAZ      '2'
#define WRITEPROG	"AW"

// Longueur de la chaine décrivant le poids 
#define WEIGHTLENGTH 10

// accuses de manipulation

#define MANUEL      'A'
#define AUTO        'B'

#define MSGLEN       20                //nombre d'elements visualisables
                                       // sur l'afficheur ID7

class AdxMSICS {

//----------------------------------------------------------
//		
// Properties
//
protected:

	// Weighing interface
	AdxWeighingInterface* _weighingInterface;
	bool _keyState; // états du clavier débloqué par défaut
	bool _keyOnly; // Quand on appuie sur une touche on envoie simplement le code
				   // on ne fait aucune action

//----------------------------------------------------------
//		
// CTOR - DTOR
//
public:

	virtual ~AdxMSICS() {};
	AdxMSICS() 
	{
		_keyState = true;
		_keyOnly = false;
	};
	

//----------------------------------------------------------
//		
// accessors & modifiers
//
public:
	void weighingTreatment(AdxWeighingInterface* wi,
						   enum WeighingOperation& opi,
						   int& porid,
						   enum WeighingOperation& opo,
						   enum DriverStatus& sto,
						   bool bCheckPlate);
	void transaction(void);
//	void readchar(void);
	void emissionMsg(void);
	void receptionMsg(void);
	void callMultiCom(int pornum, enum ComOperation comOp, char* iodata);
	void decodeResponse(void);
	void transcodeUnite(char* unit);
	bool controleUnite(char* unit);
	void delay(int milliSec);

	AdxWeighingInterface*  getWeighingInterface()
	{
		return _weighingInterface;
	}

	void setWeighingInterface(AdxWeighingInterface* weighingInterface)
	{
		_weighingInterface = weighingInterface;
	}
	bool IsCorrect(char* Data);
	bool extractWheight(char*  Data,		   // Trame à contôler
						short  CommandLength,  // Longueur de la commande
						double* Weight,        // Poids
						char*  Unit);          // Unité

};

#endif /* AdxMSICS_h */