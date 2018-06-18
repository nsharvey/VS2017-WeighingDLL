// AdxMultiCom.cpp
// ---------------
// project : Adonix X3 Scales
// author : MC
// V130 : MC 2001.05.28
//--------------------------------------------------------------
//

#include "stdafx.h"
#include "AdxInterface.h"
#include "AdxMultiCom.h"
#include "AdxPortCom.h"
#include "AdxWeighingInterface.h"
#include "AdxMessage.h"
#include "AdxMeid5.h"
//#include "AdxMeid7.h"
//#include "AdxMepm.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>

//--------------------------------------------------------------
// Destructeur
//
AdxMultiCom::~AdxMultiCom()
{
	// Ferme et delete les ports

	for (long i=0; i<8; i++)
	{
		if (_portCom[i] != NULL)
			delete _portCom[i];
	}
}

//--------------------------------------------------------------
// Constructeur
//
AdxMultiCom::AdxMultiCom() :
	_nbLec		(0)
{
	// Initialise les ports à NULL

	for (long i=0; i<8; i++)
	{
		_portCom[i] = NULL;
	}

	// Initialise la zone de réception à blanc

	for (long i=0; i<256; i++)
	{
		_zoneLec[i] = ' ';
	}
}

//--------------------------------------------------------------
// Initialisation du multi-com
//
void AdxMultiCom::initMultiCom(AdxWeighingInterface* wi,
							   int* pPortFlag,
							   int* pBaudRate,
							   int* pParity,
							   int* pStopBits,
							   int* pByteSize)
{
	setWeighingInterface(wi);
	WeighingStatus sta_err = OK_STA;
	getWeighingInterface()->setWeighingStatus(sta_err);
	getWeighingInterface()->setResWeighingMessage(msg_status [sta_err]);

	// Configure et ouvre les ports

	for (long i = 0; i < 8; i++)
	{
		int portFlag = pPortFlag[i];
		if (portFlag > 0)
		{
			int baudRate = pBaudRate[i];
			int parity	 = pParity[i];
			int stopBits = pStopBits[i];
			int byteSize = pByteSize[i];
			_portCom[i] = new AdxPortCom(baudRate, parity, stopBits, byteSize);
			if (_portCom[i]->InitPort(pPortNames[i]))
				sta_err = OK_STA;
			else
			{
				sta_err = PORT_NOT_CORRECT;
//				getWeighingInterface()->setWeighingStatus(sta_err);
				char* message = new char[80];
				sprintf(message,"%s  %s",
					IlvGetMessage(getWeighingInterface()->getInterface()->getDisplay(),
									msg_status [sta_err]), pPortNames[i]); 
				getWeighingInterface()->setResWeighingMessage(message);

				getWeighingInterface()->getInterface()
					->getMessage()->setPanneauAppelant(NULL);
				getWeighingInterface()->getInterface()
					->envoieMessage(message,false);
				delete [] message;

				if (_portCom[i] != NULL)
				{
					delete _portCom[i];
					_portCom[i] = NULL;
				}

//				return;
			}
		}
	}
}

//--------------------------------------------------------------
// Traitement de l'appel
//
void AdxMultiCom::comOperationTreatment(int& port,
										ComOperation& ope,
										char* iodata,
										DriverStatus& sta,
										int& nbcMax)
{
	sta = OK;

	// Vérification port de communication

	if (_portCom[port-1] == NULL)
	{
		sta = PCLOSE;
		return;
	}

	double time1;
	double timediff;

	int i;
	int j;
	bool reception_en_cours;

	DWORD nbecr;
	DWORD nblec;
	DWORD liodata = 0;
	DWORD liodataMax = 1000;
	char* pZoneLec = _zoneLec;

	// traite l'appel
	switch (ope)
	{
		// envoi
		case SEND:
			for (liodata = 0; liodata < liodataMax; liodata++)
			{
				if ((strncmp(iodata+liodata,"\r",1) == 0))
					break;
			}
			liodata += 2; 
			nbecr = _portCom[port-1]->Send(iodata, liodata);
			if (nbecr != liodata)
			{
				sta = 	TRANSMIT_ERROR;
				return;
			}
			break;
		// réception
		case READ:
			j = 0;
			reception_en_cours = true;
			while (reception_en_cours)
			{
				nblec = 0;
				time1 = ((double) clock()) / CLOCKS_PER_SEC;
				while (nblec == 0)
				{
					nblec = _portCom[port-1]->Receive(pZoneLec, liodataMax);
					setNbLec(nblec);
					if (nblec <= 0)
					{
						timediff = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
//						if (timediff > ATTENTE_MAXI)    //teste time-out
						if (timediff > 0.5)    //teste time-out
						{
							sta = 	NO_RESPONSE;
							return;
						}
					}
				}

				for (i = 0; i < getNbLec(); i++)
				{
					switch (_zoneLec[i])
					{
					case NUL:
						if (j <= 0)
						{
							sta = TRONCATED_RESPONSE;
							return;
						}
						break;
					case LF:
					case CR:
						sta = OK;
						if (j <= 0)
							sta = EMPTY;
						reception_en_cours = false;
						return;
						break;
					case SYN:
					case ACK:
					case DEL:
						break;
					default:
						iodata[j] = _zoneLec[i];
						j++;
						if (j > nbcMax)
						{
							sta = OVERFLOW2;
							return;
						}
						break;
					}
				}
			}
			break;

		default:
			sta = 	UNKNOWN1;
			return;
	}
}
