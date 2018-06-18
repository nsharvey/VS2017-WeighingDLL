	              Rogue Wave Views version 6.2.1

			tools/socket README File

Rogue Wave Views module to use INET sockets.

Abstract class IlvSocket:
-------------------------

class IlvSocket
{
public:
    IlvInt       readBytes(char* buffer, IlvUInt maxToRead);
    IlvBoolean   readNBytes(char*, IlvUInt count);
    IlvInt       writeBytes(const char* buffer, IlvUInt maxToWrite);
    int          getSocket();
    IlvBoolean   isBad();
    IlvBoolean   writeMessage(const char* message, int length=0);
    char*        readMessage(IlvUInt& count);
    virtual void error(int);
};

   readBytes reads at most 'maxToRead' bytes in string buffer
	and returns the number of bytes found.
	
   readNBytes reads exactly 'count' bytes.

   writeBytes writes at most 'maxToWrite' bytes

   getSocket returns the unix file descriptor

   isBad returns IlvTrue if it is a bad socket

   writeMessage writes the length and the string

   readMessage reads a length then a string of this length.

Asynchronus reading:
-------------------

    typedef void (*IlvSocketReader)(IlvSocket*,IlvAny arg);
    void IlvSocket::setCallback(IlvSocketReader reader,IlvAny arg=0);
    virtual void IlvSocket::manageInput();
    void IlvRegisterSocket(IlvSocket*,IlvDisplay*);
    void IlvUnRegisterSocket(IlvSocket*,IlvDisplay*);

The server side :
-----------------

class IlvServerSocket : public IlvSocket
{
public:
    IlvServerSocket(IlvDisplay* display, unsigned short,
		    IlvSocketReader r = 0,IlvAny a = 0);
// For Unix platforms only.
    IlvServerSocket(IlvDisplay* display, char* path,
		    IlvSocketReader r = 0,IlvAny a = 0);

    IlvDisplay*              getDisplay();
    virtual IlvAcceptSocket* make(int fd);
    virtual void             read (IlvAcceptSocket*);
    virtual void             manageInput();
};


The client side :
-----------------

class IlvClientSocket : public IlvSocket
{
public:
    IlvClientSocket(unsigned short port, char* host = 0,
		    IlvSocketReader r = 0, IlvAny a = 0);
// For Unix platforms only.
    IlvClientSocket(char* path,
		    IlvSocketReader r = 0, IlvAny a = 0);
};

Testing:
--------
You can compile two test programs:
	testsrvr
	testclnt

You should run testsrvr in background or on another computer, then run
testclnt (with an optional argument indicating the name of the computer
where the program testsrvr is running) and check the communication
messages.
