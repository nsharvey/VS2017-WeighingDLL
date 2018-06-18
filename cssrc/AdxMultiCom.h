// AdxMultiCom.h
// -------------
// project : Adonix X3 Scales
// author : MC
// V130 : MC 2001.05.28
//--------------------------------------------------------------
//

#ifndef AdxMultiCom_h
	#define AdxMultiCom_h

//#include <ilviews/resource.h>
//#include <windows.h>

class AdxWeighingInterface;
class AdxPortCom;

#define ATTENTE_MAXI   1 			   //delai d'attente maxi d'une
                                       // demande de réponse

enum ComOperation
{
	OPEN,
	OPT,
	SPEED,
	SEND,
	READ,
	RESET_BUF,
	STATUS,
	CLOSE 
};

enum ComStatus{
	COM_OK
};

static char* pPortNames [] = 
{
	"COM1:",
	"COM2:",
	"COM3:",
	"COM4:",
	"COM5:",
	"COM6:",
	"COM7:",
	"COM8:",
};

class AdxMultiCom
{

//----------------------------------------------------------
//		
// Properties
//
protected:

	// nb caractères traités par appelant
	int _nbCar;
	// nb caractères lus
	DWORD _nbLec;
	// zone reception
	char _zoneLec[1000];
	// Weighing interface
	AdxWeighingInterface* _weighingInterface;

public:

	// table des ports com
	AdxPortCom* _portCom[8];

//----------------------------------------------------------
//		
// CTOR - DTOR
//
public:

	virtual ~AdxMultiCom();
	AdxMultiCom();
	

//----------------------------------------------------------
//		
// accessors & modifiers
//
public:

	void comOperationTreatment(int& port,
							   enum ComOperation& ope,
							   char* iodata,
							   enum DriverStatus& sta,
							   int& nbcMax);

	int getNbLec() const {
		return _nbLec;
	}

//protected:

	void setNbLec( const DWORD& value) {
		_nbLec = value;
	}

	AdxWeighingInterface*  getWeighingInterface()
	{
		return _weighingInterface;
	}

	void setWeighingInterface(AdxWeighingInterface* weighingInterface)
	{
		_weighingInterface = weighingInterface;
	}

	void initMultiCom(AdxWeighingInterface* wi,
					  int* pPortFlag,
					  int* pBaudRate,
					  int* pParity,
					  int* pStopBits,
					  int* pByteSize);
};

#endif /* AdxMultiCom_h */
