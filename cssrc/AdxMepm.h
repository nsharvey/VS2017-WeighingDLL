// AdxMepm.h
// ---------
// project : Adonix X3 Scales
// author : MC
// V130 : MC 2001.05.28
//--------------------------------------------------------------
//

#ifndef AdxMepm_h
	#define AdxMepm_h

class AdxWeighingInterface;

/*************************************************
*     constantes generales                       *
*************************************************/
#define MAXC         256               //nombre maxi d'�l�ments de la chaine
                                       // d'entr�e aval
#define DOWN_BUF_SIZ 40                //nombre maxi d'�l�ments de la chaine
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
#define ACK      0x06                  //accuse de r�ponse positive
#define LF       0x0a
#define CR       0x0d
#define SYN      0x16
#define DEL      0x127

/*************************************************
*              JEU D'INSTRUCTIONS                *
*************************************************/
// reponses d'erreurs possibles survenues en retour d'une op�ration de pesage

#define ERROR2      'E'
#define LOGISTIC    'L'
#define SYNTAX      'S'
#define TRANSMIT    'T'
#define SURCHARGE   '+'
#define SOUSCHARGE  '-'

// requetes de pesage

#define APPLICATION 'A'
#define PLATEAU     'A'
#define KEYP_A      'A'
#define OP_ACTION   'A'
#define BASE	    'B'
#define PC_ACTION   'B'
#define KEYP_B      'B'
#define KEYP_C      'C'
#define KEYP_D      'D'
#define DISPLAY     'D'
#define DYNAMIC     'D'
#define IMMEDIAT    'I'
#define INCORRECT   'I'
#define KEY_PAC     'K'
#define KBD         'R'
#define REPEAT      'R'
#define LECTURE     'R'
#define NET         'S'
/*
#define SENDX       'S'
*/
#define SOUND       'S'
#define CHANGE      'S'
#define TARE        'T'
#define ART_M       'T'
#define UNIT_POIDS  'U'
#define WRITE       'W'
#define ARTICLE     'X'
#define REMISEAZERO 'Z'
#define DISABLE     '0'
#define ENABLE      '1'

// accuses de manipulation

#define MANUEL      'A'
#define AUTO        'B'

#define MSGLEN       20                //nombre d'elements visualisables
                                       // sur l'afficheur PM 3000

class AdxMepm {

//----------------------------------------------------------
//		
// Properties
//
protected:

	// Weighing interface
	AdxWeighingInterface* _weighingInterface;

//----------------------------------------------------------
//		
// CTOR - DTOR
//
public:

	virtual ~AdxMepm() {};
	AdxMepm() {};
	

//----------------------------------------------------------
//		
// accessors & modifiers
//
public:
	void weighingTreatment(AdxWeighingInterface* wi,
						   enum WeighingOperation& opi,
						   int& porid,
						   enum WeighingOperation& opo,
						   enum DriverStatus& sto);
	void transaction(void);
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

};

#endif /* AdxMepm_h */