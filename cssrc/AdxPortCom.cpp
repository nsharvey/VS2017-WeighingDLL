// AdxPortCom.cpp
// --------------
// project : Adonix X3 Scales
// author : MC
// V130 : MC 2001.05.28
//--------------------------------------------------------------
//

#include "stdafx.h"
#include "AdxPortCom.h"
#include "AdxMultiCom.h"
#include "AdxWeighingInterface.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
//#include <windows.h>
//#include <afx.h>


//--------------------------------------------------------------
// Traitement de surveillance
//
static DWORD CommWatchProc(AdxPortCom* port)
{
	int nMaxLength = 256;
	int nbcWrite;

	SetEvent(port->_hEventThread);
	// Creation d'un mutex sans propriétaire initial.
	if(port->_hMutex == NULL)
	{
		HANDLE hMutex;
		// On ne nomme plus le mutex pour en  avoir un différent pour toutes les créations			
		hMutex = CreateMutex( NULL,                       // pas d'attributs de sécurité
							  TRUE,                       // appartient au thread
							  NULL);		  // nom du mutex
		if (hMutex == NULL) 
		{
 			port->Disconnect();	
			return FALSE ;
		}
		port->_hMutex	= hMutex;
	}
	while (port->_bConnected)
	{
		DWORD dwWaitResult;				
		dwWaitResult = WaitForSingleObject(port->_hEventWatch,INFINITE);
		switch (dwWaitResult)
		{
		case WAIT_OBJECT_0:
			{
				DWORD dwWaitResultMutex;				
				dwWaitResultMutex = WaitForSingleObject(port->_hMutex,INFINITE);
				if(dwWaitResultMutex == WAIT_OBJECT_0)
				{
					switch (port->_request)
					{
					case 0:
						break;
					case 1:
						port->_dwLength = 0 ;
						port->_dwLength = port->ReadCommBlock(port->_lpszIOData,nMaxLength);
						break;
					case 2:
						nbcWrite = port->_dwLength;
						port->_dwLength = port->WriteCommBlock(port->_lpszIOData,nbcWrite);
					default:
						break;
					}
					ReleaseMutex(port->_hMutex);
				}
				break;
			}
		default:
			{
			// autre erreur
			}
		}

		ResetEvent(port->_hEventWatch);
		SetEvent(port->_hEventIO);
	}
	return TRUE;
}
/*
//--------------------------------------------------------------
// Analyse statut
//
static DWORD CommStatProc(AdxPortCom* port)
{
	DWORD	dwEvent;
	char	szEvent[30];
	char	szBuffer[100];
	DWORD   dwStoredFlags;
	
	dwStoredFlags = EV_BREAK | EV_CTS | EV_DSR | EV_ERR | EV_RING |\
				  EV_RLSD | EV_RXCHAR | EV_RXFLAG | EV_TXEMPTY ;

	SetEvent(port->_hEventThread);
	
	while (port->_bConnected)
	{
		if (dwEvent = port->WaitForCommEvent(dwStoredFlags))
		{
			switch(dwEvent)
			{
			case EV_BREAK:
				wsprintf(szEvent,"Break");
				break;
			case EV_CTS:
				wsprintf(szEvent,"Clear to Send");
				break;
			case EV_DSR:
				wsprintf(szEvent,"Data Set Ready");
				break;
			case EV_ERR:
				wsprintf(szEvent,"Error occurred");
				break;
			case EV_RING:
				wsprintf(szEvent,"Ring Detected");
				break;
			case EV_RLSD:
				wsprintf(szEvent,"Receive Line signal detect");
				break;
			case EV_RXCHAR:
				wsprintf(szEvent,"Character was receided");
				break;
			case EV_RXFLAG:
				wsprintf(szEvent,"Event character was received");
				break;
			case EV_TXEMPTY:
				wsprintf(szEvent,"Last character was received");
				break;
			default:
				wsprintf(szEvent,"Unknown event");
			}//Switch
			wsprintf( szBuffer, "Event on COM1 : %s",szEvent) ;
		}
		else
			wsprintf( szBuffer, "No Event on COM1") ;

//		cout <<szBuffer<<endl;
	}
	return TRUE  ;
}
*/
//--------------------------------------------------------------
// Destructeur : fermeture du port
//
AdxPortCom::~AdxPortCom()
{
	Disconnect();
}

//--------------------------------------------------------------
// Constructeur
//
AdxPortCom::AdxPortCom(int baudRate,
					   int parity,
					   int stopBits,
					   int byteSize) :
	_lpszIOData					(NULL),
	_dwLength					(0),
	_hPort						(NULL), 
	_hMutex						(NULL), 
	_hEventIO					(NULL), 
	_hEventWatch				(NULL), 
	_hEventThread				(NULL), 
	_bConnected					(FALSE),
	_hThread					(NULL),
	_dwThreadID					(0),
	_hThreadStat				(NULL),
	_dwThreadIDStat				(0),
	_request					(0)
{
//	cout <<"construction AdxPortCom"<<endl;
	_baudRate = baudRate;
	_parity = parity;
	_stopBits = stopBits;
	_byteSize = byteSize;
}
//--------------------------------------------------------------
// Ouverture du port
//
bool AdxPortCom::InitPort (LPTSTR lpszPortName)
{
	HANDLE 			hPort,
					hThread,
					hEvent;
	DWORD			dwError,
					dwThreadID;
	DCB				PortDCB;
	COMMTIMEOUTS	CommTimeouts;

	hPort = CreateFile (lpszPortName,
                        GENERIC_READ|GENERIC_WRITE ,
                        NULL,
                        NULL,
                        OPEN_EXISTING,
                        FILE_FLAG_OVERLAPPED,
						NULL);


	if (!hPort || hPort==INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	PortDCB.DCBlength = sizeof (DCB);

	GetCommState (hPort, &PortDCB);

	PortDCB.BaudRate = _baudRate;				// vitesse
	PortDCB.fBinary = TRUE;						// mode binaire
	PortDCB.fParity = TRUE;						// controle parité
	PortDCB.fOutxCtsFlow = FALSE;				// controle CTS flux de sortie
	PortDCB.fOutxDsrFlow = FALSE;				// controle DSR flux de sortie
// llc 05.02.03 sur ID5 apparemment c'est mieux de mettre ENABLE ...
//  1. il faut conditionner suivant driver (si ID5 alors ENABLE, si ID7 alors DISABLE)
//	2. cela va-t-il fonctionner avec toutes les ID5 ?
//	PortDCB.fDtrControl = DTR_CONTROL_DISABLE;	// controle DTR flux 
	PortDCB.fDtrControl = DTR_CONTROL_ENABLE;	// controle DTR flux 


	PortDCB.fDsrSensitivity = FALSE;			// sensibilité DSR
	PortDCB.fTXContinueOnXoff = FALSE;			// XOFF continue tx
	PortDCB.fOutX = FALSE;						// XON/XOFF flux de sortie
	//PortDCB.fOutX = TRUE;						// XON/XOFF flux de sortie
	PortDCB.fInX = FALSE;						// XON/XOFF flux d'entrée
	//PortDCB.fInX = TRUE;						// XON/XOFF flux d'entrée
	PortDCB.fErrorChar = TRUE;					// Remplacement error
	PortDCB.fNull = FALSE;						// suppression NULL
	PortDCB.fRtsControl = RTS_CONTROL_DISABLE;	// controle RTS flux
	PortDCB.fAbortOnError = FALSE;				// abort lecture/ecriture sur error
	PortDCB.ByteSize = _byteSize;				// nb de bits/byte 4-8
	switch (_parity)							// parité 0-4 (aucune,impaire, paire, ...)
	{
		case 0:
			PortDCB.Parity = NOPARITY;
			break;
		case 1:
			PortDCB.Parity = ODDPARITY;
			break;
		case 2:
			PortDCB.Parity = EVENPARITY;
			break;
		case 3:
			PortDCB.Parity = MARKPARITY;
			break;
		case 4:
			PortDCB.Parity = SPACEPARITY;
			break;
	}
	switch (_stopBits)							// 1, 1,5, 2
	{
		case 1:
			PortDCB.StopBits = ONESTOPBIT;
			break;
		case 2:
			PortDCB.StopBits = TWOSTOPBITS;
			break;
	}
	PortDCB.XonChar = 0x0011;					// 
	PortDCB.XoffChar = 0x0013;					// 
	PortDCB.ErrorChar = 0x20;					// 
	PortDCB.EofChar = 0x0a;						// 

	if (!SetCommState (hPort, &PortDCB))
	{
		dwError = GetLastError();
		return FALSE;
	}

	GetCommTimeouts (hPort, &CommTimeouts);

	CommTimeouts.ReadIntervalTimeout			= 5 ;
	CommTimeouts.ReadTotalTimeoutMultiplier		= 1 ;
	CommTimeouts.ReadTotalTimeoutConstant		= 1000 ;
	CommTimeouts.WriteTotalTimeoutMultiplier	= 1 ;
	CommTimeouts.WriteTotalTimeoutConstant		= 1000 ;

	if (!SetCommTimeouts (hPort, &CommTimeouts))
	{
		dwError = GetLastError();
		return FALSE;
	}

	_hPort = hPort;

	_bConnected = TRUE;
	_dwThreadID = 0;
	_hThread	= NULL;

	// Creation d'un "event" pour suivre les operations d'I/O

	hEvent  = CreateEvent(NULL,		// "LPSecurity" ignoré pour Win9X
						  TRUE,		// restauration manuelle
						  FALSE,	// état initial "nonsignaled"
						  NULL);	// pas de nom
	if (!hEvent)
	{
		Disconnect();	
		return FALSE;
	}

	_hEventIO = hEvent;

	// Creation d'un "event" pour suivre le thread de surveillance

	hEvent  = CreateEvent(NULL,		// "LPSecurity" ignoré pour Win9X
						  TRUE,		// restauration manuelle
						  FALSE,	// état initial "nonsignaled"
						  NULL);	// pas de nom
	if (!hEvent)
	{
		Disconnect();	
		return FALSE;
	}

	_hEventWatch = hEvent;

	// Creation d'un "event" pour attendre le départ du Thread secondaire

	hEvent  = CreateEvent(NULL,		// "LPSecurity" ignoré pour Win9X
						  TRUE,		// restauration manuelle
						  FALSE,	// état initial "nonsignaled"
						  NULL);	// pas de nom
	if (!hEvent)
	{
		Disconnect();	
		return FALSE;
	}

	_hEventThread = hEvent;

	// Creation d'un Thread secondaire pour surveiller un "event"
	
	if (!(hThread = CreateThread(NULL, // attributs de sécurité
							     0,
							     (LPTHREAD_START_ROUTINE) CommWatchProc,
							     (AdxPortCom*) this,
							     0,
								 &dwThreadID
							    )))
	{
		Disconnect();	
		return FALSE;
	}
	else
	{
		_dwThreadID = dwThreadID ;
		_hThread = hThread ;
//		SetThreadPriority(_hThread, THREAD_PRIORITY_HIGHEST);
		hThread = NULL;
		dwThreadID = 0;
	}

	// Attente départ du Thread secondaire

	DWORD dwWaitResult;				
	dwWaitResult = WaitForSingleObject(_hEventThread,10000);
	switch (dwWaitResult)				//switch de principe
	{
	case WAIT_OBJECT_0:
		{
			break;
		}
	case WAIT_TIMEOUT:
		{
			break;
		}
	default:
		{
		// autre erreur
		}
	}

	if(_hEventThread != NULL)
	{
		CloseHandle(_hEventThread);
		_hEventThread = NULL;
	}
/*
	// Creation d'un "event" pour attente départ du troisième thread

	hEvent  = CreateEvent(NULL,		// "LPSecurity" ignoré pour Win9X
						  TRUE,		// restauration manuelle
						  FALSE,	// état initial "nonsignaled"
						  NULL);	// pas de nom
	if (!hEvent)
	{
		Disconnect();	
		return FALSE;
	}

	_hEventThread = hEvent;

	// Creation d'un troisième Thread pour surveiller un "status" 

	if (!(hThread = CreateThread(NULL, // SECURITY ATTRIBUTES
								 0,
								 (LPTHREAD_START_ROUTINE) CommStatProc,
								 (AdxPortCom*) this,
								 0,
							 	 &dwThreadID
								)))
	{
		Disconnect();	
		return FALSE;
	}
	else
	{
		_dwThreadIDStat = dwThreadID ;
		_hThreadStat = hThread ;
//		SetThreadPriority(_hThreadStat, THREAD_PRIORITY_ABOVE_NORMAL);
		hThread = NULL;
		dwThreadID = 0;
	}

	// Attente départ du troisième Thread 

	dwWaitResult = WaitForSingleObject(_hEventThread,10000);
	switch (dwWaitResult)
	{
	case WAIT_OBJECT_0:
		{
			break;
		}
	case WAIT_TIMEOUT:
		{
			break;
		}
	default:
		{
		// autre erreur 
		}
	}

	if(_hEventThread != NULL)
	{
		CloseHandle(_hEventThread);
		_hEventThread = NULL;
	}

*/
	return TRUE;
}
  
//--------------------------------------------------------------
// Demande de lecture
//
DWORD AdxPortCom::Receive(LPSTR lpszIOData, int nbcRead )
{
	// 18/08/08 gestion mutex
	bool continu = TRUE;

//gbe pour debug
//MessageBox(NULL,"poser point d'arret 1","test",MB_OK);
	_lpszIOData = lpszIOData;
	_request = 1;
	if (!ResetEvent(_hEventIO))
	{
		return 0;
	}

	if (!SetEvent(_hEventWatch))
	{
		return 0;
	}

	DWORD dwWaitResult;				
	dwWaitResult = WaitForSingleObject(_hEventIO,10000);
	switch (dwWaitResult)
	{
	case WAIT_OBJECT_0:
		{
			break;
		}
	case WAIT_TIMEOUT:
		{
			break;
		}
	default:
		{
		// autre erreur
			_dwLength = 0 ;
		}
	}

	if (!ResetEvent(_hEventIO))
	{
		return 0;
	}

	nbcRead = _dwLength;
	return _dwLength;
}
  
//--------------------------------------------------------------
// Demande d'écriture
//
DWORD AdxPortCom::Send(LPSTR lpszIOData, int nbcWrite )
{
	// 18/08/08 gestion mutex
	bool continu = TRUE;

	_lpszIOData = lpszIOData;
	_dwLength = nbcWrite;
	_request = 2;
	if (!ResetEvent(_hEventIO))
	{
		return 0;
	}

	if (!SetEvent(_hEventWatch))
	{
		return 0;
	}

	DWORD dwWaitResult;				
	dwWaitResult = WaitForSingleObject(_hEventIO,10000);
	switch (dwWaitResult)
	{
	case WAIT_OBJECT_0:
		{
			break;
		}
	case WAIT_TIMEOUT:
		{
			break;
		}
	default:
		{
		// autre erreur
			_dwLength = 0 ;
		}
	}

	if (!ResetEvent(_hEventIO))
	{
		return 0;
	}

	return _dwLength;
}
  
//--------------------------------------------------------------
// Lecture bloc
//
DWORD AdxPortCom::ReadCommBlock(LPSTR lpszBlock, int nMaxLength )
{
	BOOL       fReadStat ;
	BOOL	   fWaitingOnRead;
	COMSTAT    ComStat ;
	DWORD      dwErrorFlags;
	DWORD      dwLength = 0;
	DWORD	   dwRes = 0;
	HANDLE	   hEvent;	
	OVERLAPPED osReader = {0};
	bool continu = TRUE; // 18/08/08 gestion mutex

	if (_hPort == NULL)
		return 0 ;

	// essaie seulement de lire le nombre de bytes dans la queue
	ClearCommError( _hPort, &dwErrorFlags, &ComStat ) ;
	if (nMaxLength > 0)
	{
		hEvent  = CreateEvent(NULL,		// "LPSecurity" ignoré pour Win9X
							  TRUE,		// restauration manuelle
							  FALSE,	// état initial "nonsignaled"
							  NULL);	// pas de nom
		if (!hEvent)
		    return 0;

		osReader.hEvent = hEvent;

//		fReadStat = ReadFile( _hPort, lpszBlock,
//							nMaxLength, &dwLength, &osReader ) ;
		fReadStat = ReadFile( _hPort, lpszBlock,
							nMaxLength, &dwLength, &osReader ) ;
		if (!fReadStat)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				fWaitingOnRead = TRUE;
				while (fWaitingOnRead)
				{
//					dwRes = WaitForSingleObject(osReader.hEvent,1000);
					dwRes = WaitForSingleObject(osReader.hEvent,500);
					switch(dwRes)
					{
					case WAIT_OBJECT_0:
						{
							if (!GetOverlappedResult( _hPort,&osReader, &dwLength, FALSE))
								// une erreur s'est produite, essaie de la récupérer
								ClearCommError( _hPort, &dwErrorFlags, &ComStat ) ;
							fWaitingOnRead = FALSE;
							break;
						}
					case WAIT_TIMEOUT:
						{
							continue;
							break;
						}
					default:
						{
						// autre erreur
							dwLength = 0 ;
							ClearCommError( _hPort, &dwErrorFlags, &ComStat ) ;
							fWaitingOnRead = FALSE;
						}
					}
				}  // fin du while
			}
		}	  
		CloseHandle(hEvent);
	}
	return dwLength;
}

//--------------------------------------------------------------
// Ecriture bloc
//
DWORD AdxPortCom::WriteCommBlock( LPSTR lpszBlock, int nMaxLength )
{
	BOOL       fWriteStat ;
	BOOL	   fWaitingOnWrite;
	COMSTAT    ComStat ;
	DWORD      dwErrorFlags;
	DWORD      dwLength = 0;
	DWORD	   dwRes = 0;
	HANDLE	   hEvent;	
	OVERLAPPED osWriter = {0};
	bool continu = TRUE; // 18/08/08 gestion mutex

	if (_hPort == NULL)
		return 0 ;

	ClearCommError( _hPort, &dwErrorFlags, &ComStat ) ;
	if (nMaxLength > 0)
	{
		hEvent  = CreateEvent(NULL,		// "LPSecurity" ignoré pour Win9X
						      TRUE,		// restauration manuelle
							  FALSE,	// état initial "nonsignaled"
							  NULL);	// pas de nom
		if (!hEvent)
		  return 0;

		osWriter.hEvent = hEvent;

//		fWriteStat = WriteFile( _hPort, lpszBlock,
//							nMaxLength, &dwLength, &osWriter ) ;
//gbe pour debug
//MessageBox(NULL,"poser point d'arret 4","test",MB_OK);
		fWriteStat = WriteFile( _hPort, lpszBlock,
							nMaxLength, &dwLength, &osWriter ) ;

		if (!fWriteStat)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				fWaitingOnWrite = TRUE;
				while (fWaitingOnWrite)
				{
					dwRes = WaitForSingleObject(osWriter.hEvent,500);
					switch(dwRes)
					{
					case WAIT_OBJECT_0:
						{
							if (!GetOverlappedResult( _hPort,&osWriter,
													  &dwLength, FALSE))
								// une erreur s'est produite, essaie de reprendre
								ClearCommError( _hPort, &dwErrorFlags,
												&ComStat ) ;
							fWaitingOnWrite = FALSE;
							break;
						}
					case WAIT_TIMEOUT:
						{
							continue;
							break;
						}
					default:
						{
						// autre erreur
							dwLength = 0 ;
							ClearCommError( _hPort, &dwErrorFlags, &ComStat ) ;
							fWaitingOnWrite = FALSE;
						}
					}
				} // fin du while
			}
		}

		CloseHandle(hEvent);
	}
	return dwLength;
}
/*
//--------------------------------------------------------------
// Attente évènement
//
DWORD AdxPortCom::WaitForCommEvent(DWORD dwEventFlags)
{

	DWORD      dwRes = 0;
	DWORD      dwResWait = 0;
	DWORD      dwCommEvent = 0;
	DWORD      dwErrorFlags;
	BOOL       fWaitingOnStat = FALSE;
	COMSTAT    ComStat ;
	OVERLAPPED osStatus = {0};

	if (!SetCommMask(_hPort,
					 dwEventFlags))	  // error setting communications mask; abort
	{
//		cout<<"setCommMask"<<endl;
		return 0;
	}

	osStatus.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (osStatus.hEvent == NULL)	  // error creating event; abort
	{
//		cout <<"osStatus.hEvent == NULL"<<endl;
		return 0;
	}
	
	// Lance un controle du "status event" si ce n'est déjà fait.

	if (!WaitCommEvent(_hPort, &dwCommEvent, &osStatus)) 
	{
		if (GetLastError() == ERROR_IO_PENDING)
		   fWaitingOnStat = TRUE;
		else
		{
		   // erreur dans WaitCommEvent; plante
			ClearCommError( _hPort, &dwErrorFlags, &ComStat ) ;
			dwRes=0;
		}
	}
	else
		// WaitCommEvent retourné immediatement.
		// Traite le status event convenablement.

		fWaitingOnStat = FALSE;
	
//	cout<<"fWaitingOnStat = "<<fWaitingOnStat<<endl;

	// Teste overlapped operation.
	while(fWaitingOnStat) 
	{
		// Attend un petit moment qu'un évènement se produise.
		dwResWait = WaitForSingleObject(osStatus.hEvent, 500);
//		cout<<"fWaitingOnStat = "<<fWaitingOnStat<<" "<<dwResWait<<endl;
		switch(dwResWait)
		{
		// L'évènement s'est produit.
		case WAIT_OBJECT_0: 
			if (!GetOverlappedResult(_hPort, &osStatus, &dwRes, FALSE))
				// Une erreur s'est produite dans l'"overlapped operation";
				// appelle GetLastError pour trouver ce que c'était
				// et plante si c'était une erreur fatale.
				ClearCommError( _hPort, &dwErrorFlags, &ComStat ) ;
			else
				// le "status event" est chargé dans l'"event flag"
				// specifié dans l'appel au "WaitCommEvent" d'origine.
				// Traite le "status event" convenablement.
				// Positionne "fWaitingOnStat flag" pour indiquer qu'un nouveau
				 // "WaitCommEvent" est attendu.
				fWaitingOnStat = FALSE;
			break;

		case WAIT_TIMEOUT:
			 // L'operation n'est pas encore terminée. "fWaitingOnStatusHandle flag" 
			 // n'est pas modifié.
			 // et il ne faut pas lancer un WaitCommEvent tant que le précédent
			 // n'est pas terminé
			 //
			continue;
			break;                       

		default:
			 // Erreur dans le "WaitForSingleObject"; Plante
			 // Cela indique un problème dans la structure OVERLAPPED de l'"event handle".
			dwCommEvent = 0;
			fWaitingOnStat = FALSE;
		}//Switch
	}//While
	CloseHandle(osStatus.hEvent);
	return dwCommEvent;
}
*/
//--------------------------------------------------------------
// Deconnexion
//
void AdxPortCom::Disconnect()
{
	if (_bConnected)
	{
		if(_hMutex != NULL)
		{
//			delete _hMutex;
			// 18/08/08 Gestion Mutex
			CloseHandle(_hMutex);
		}
			
		// Libère les threads de travail
		if(_hThread != NULL)
		{
			TerminateThread(_hThread,0);
	//		WaitForSingleObject(_hThread,10000);
			CloseHandle(_hThread);
			_dwThreadID = 0;
			_hThread = NULL;
//			delete _hThread;
		}

		if(_hThreadStat != NULL)
		{
			TerminateThread(_hThreadStat, 0);
//			WaitForSingleObject(_hThreadStat, 10000);
			CloseHandle(_hThreadStat);
			_dwThreadIDStat = 0;
			_hThreadStat = NULL;
//			delete _hThreadStat;
		}

		if(_hEventIO != NULL)
		{
			CloseHandle(_hEventIO);
			_hEventIO = NULL;
//			delete _hEventIO;
		}

		if(_hEventWatch != NULL)
		{
			CloseHandle(_hEventWatch);
			_hEventWatch = NULL;
//			delete _hEventWatch;
		}

		if(_lpszIOData != NULL)
		{
			_lpszIOData = NULL;
			delete _lpszIOData;
		}

		_bConnected = FALSE;
	}

	CloseHandle(_hPort);
	return ;
}



