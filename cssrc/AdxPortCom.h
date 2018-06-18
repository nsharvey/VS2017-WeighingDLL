// AdxPortCom.h
// ------------
// project : Adonix X3 Scales
// author : MC
// V130 : MC 2001.05.28
//--------------------------------------------------------------
//

#ifndef AdxPortCom_h
	#define AdxPortCom_h

//#include <ilviews/resource.h>
//#include <windows.h>
/*
typedef struct tagCOMMInfo
{
	HANDLE hDev,hMutex; 
	BOOL bConnected; // the port is open ?
	OVERLAPPED ovRead;
	HANDLE hThread;
	DWORD dwThreadID;
	HANDLE hThreadStat;
	DWORD dwThreadIDStat;
	HWND hWnd;
} COMMInfo, *LPTRCOMMInfo;

#define COMMDEV(x) x->hDev
#define HWNDDEV(x) x->hWnd
#define MUTEXINFO(x) x->hMutex
#define CONNECTED(x) x->bConnected
#define OV_READ(x) x->ovRead
#define THREAD(x) x->hThread
#define THREADID(x) x->dwThreadID
#define THREADSTAT(x) x->hThreadStat
#define THREADIDSTAT(x) x->dwThreadIDStat
#define MINPOS 0
#define MAXPOS 100
*/
class AdxPortCom
{

//----------------------------------------------------------
//		
// Properties
//
//protected:
public:

	LPTSTR		_lpszIOData;
	DWORD		_dwLength;
	HANDLE		_hPort; 
	HANDLE		_hMutex; 
	HANDLE		_hEventIO; 
	HANDLE		_hEventWatch; 
	HANDLE		_hEventThread; 
	BOOL		_bConnected; 
	HANDLE		_hThread;
	DWORD		_dwThreadID;
	HANDLE		_hThreadStat;
	DWORD		_dwThreadIDStat;
	int			_request;

	int			_baudRate;
	int			_parity;
	int			_stopBits;
	int			_byteSize;


//----------------------------------------------------------
//		
// CTOR - DTOR
//
public:

	virtual ~AdxPortCom();
	AdxPortCom(int baudRate,
			   int parity,
			   int stopBits,
			   int byteSize);
	

//----------------------------------------------------------
//		
// accessors & modifiers
//
public:

	bool InitPort (LPTSTR lpszPortName);
	DWORD Receive(LPSTR lpszIOData, int nbcRead );
	DWORD Send(LPSTR lpszIOData, int nbcWrite );

	DWORD ReadCommBlock( LPSTR lpszBlock, int nMaxLength );
	DWORD WriteCommBlock( LPSTR lpszBlock, int nMaxLength );
//	DWORD WaitForCommEvent(DWORD dwEventFlags);
	void Disconnect();
	
protected:


};

#endif /* AdxPortCom_h */
