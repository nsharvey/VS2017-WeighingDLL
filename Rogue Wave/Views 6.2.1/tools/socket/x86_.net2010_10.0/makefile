# --------------------------------------------------------------------------
#
#   Makefile for the 'socket' Rogue Wave Views Tools
#
# --------------------------------------------------------------------------
#   platform: x86_.net2010_10.0
#   format:   dll_mda
# --------------------------------------------------------------------------

ROOTDIR      = ..

VIEWSDIR     = $(ROOTDIR)\..\..
VIEWSINCDIR  = $(VIEWSDIR)\include
VIEWSLIBDIR  = $(VIEWSDIR)\lib\$(SYSTEM)\$(FORMAT)
VIEWSRESDIR  = $(VIEWSDIR)\data\res

SOCKETDIR    = $(VIEWSDIR)\tools\socket
SOCKETINCDIR = $(SOCKETDIR)
SOCKETLIBDIR = $(SOCKETDIR)\$(SYSTEM)

SYSTEM       = x86_.net2010_10.0
FORMAT       = dll_mda

CCC          = cl
COMPILERFLAGS= /c /DWIN32 /DIL_DLL /MD /nologo /W3 /EHsc /GR /D_CRT_SECURE_NO_DEPRECATE
LD           = link
LDFLAGS      = $(LDDBGFLAGS) /NOLOGO /SUBSYSTEM:WINDOWS /MACHINE:I386 /INCREMENTAL:NO	
AR           = link $(LDDBGFLAGS) /INCREMENTAL:NO /NOLOGO /SUBSYSTEM:WINDOWS /DLL $(ARFLAGS) /MACHINE:I386 /VERSION:6.2
OUTPUTFILE   = -Fo
RC           = rc
RCFLAGS      = /c1252 /I"$(VIEWSDIR)\data\res" $(RCDEFINES)
SYSLIBS      = winspool.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib shell32.lib advapi32.lib wsock32.lib imm32.lib
RANLIB       = 
SHLIBEXT     = 
SHLIBEXTFLAGS= 

# Debug options:
DEBUG        = 0
LDDEBUG      = 0
!if $(DEBUG)
DEBUGFLAGS   = /Zi /Od 
OPTIMFLAGS   = $(DEBUGFLAGS) 
LDDEBUG      = 1
RCDEFINES    = /d_DEBUG
!else
DEBUGFLAGS   =  
RCDEFINES    = /dNDEBUG
OPTIMFLAGS   = /Gs /O1
!endif
!if $(LDDEBUG)
LDDBGFLAGS   = /debug /DEBUGTYPE:CV /PDB:$*.pdb
ARFLAGS   = /debug /DEBUGTYPE:CV
!else
LDDBGFLAGS   = 
ARFLAGS   = 
!endif

CCFLAGSSYS   = $(DEBUGFLAGS) $(COMPILERFLAGS)
CCVIEWSFLAGS = -DILVNODEFAULTLOOK
CCFLAGS      = $(OPTIMFLAGS) $(COMPILERFLAGS) $(CCVIEWSFLAGS)
ALLSYSLIBS   = $(ADDLIBS) $(BIDILIBS) $(SYSLIBS)

LIBEXT       = .lib



# --------------------------------------------------------------------------
PROGRAMS     = testsrvr testclnt

SOCKETLIB    = ilvsock.lib

all: $(SOCKETLIB) $(PROGRAMS)

# --------------------------------------------------------------------------
ilvsock$(LIBEXT) ilvsock.dll: socket.obj server.obj client.obj "$(VIEWSLIBDIR)\winviews$(LIBEXT)" "$(VIEWSLIBDIR)\ilog$(LIBEXT)"
	-@IF EXIST ilvsock$(LIBEXT) DEL ilvsock$(LIBEXT)
	$(AR) /LIBPATH:"$(VIEWSLIBDIR)" winviews$(LIBEXT) ilog$(LIBEXT) $(ALLSYSLIBS) /OUT:ilvsock.dll /IMPLIB:ilvsock$(LIBEXT) @<<
socket.obj
server.obj
client.obj
<<

socket.obj: "$(ROOTDIR)\src\socket.cpp"
	-@IF EXIST socket.obj DEL socket.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)" $(CCFLAGS) $(ROOTDIR)\src\socket.cpp

client.obj: "$(ROOTDIR)\src\client.cpp"
	-@IF EXIST client.obj DEL client.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)" $(CCFLAGS) $(ROOTDIR)\src\client.cpp

server.obj: "$(ROOTDIR)\src\server.cpp"
	-@IF EXIST server.obj DEL server.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)" $(CCFLAGS) $(ROOTDIR)\src\server.cpp

###########################################################################
### tests
###########################################################################
# --------------------------------------------------------------------------
testsrvr: testsrvr.exe
testsrvr.exe: server.obj socket.obj testsrvr.obj viewsico.res
	-@IF EXIST testsrvr.exe DEL testsrvr.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ testsrvr.obj server.obj socket.obj ilvmain.obj viewsico.res

testsrvr.obj: "$(ROOTDIR)\src\testsrvr.cpp"
	-@IF EXIST testsrvr.obj DEL testsrvr.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)" $(CCFLAGS) $(ROOTDIR)\src\testsrvr.cpp

TESTCLNTOBJ  = socket client
# --------------------------------------------------------------------------
testclnt: testclnt.exe
testclnt.exe: socket.obj client.obj testclnt.obj viewsico.res
	-@IF EXIST testclnt.exe DEL testclnt.exe
	$(LD) $(LDFLAGS) /LIBPATH:"$(VIEWSLIBDIR)" views.lib winviews.lib ilog.lib $(VIEWSSYSLIBS) $(USERSYSLIBS) $(ALLSYSLIBS) -OUT:$@ testclnt.obj socket.obj client.obj ilvmain.obj viewsico.res

testclnt.obj: "$(ROOTDIR)\src\testclnt.cpp"
	-@IF EXIST testclnt.obj DEL testclnt.obj
	$(CCC) $(OUTPUTFILE)$@ /I"$(VIEWSINCDIR)" /I"$(ROOTDIR)" $(CCFLAGS) $(ROOTDIR)\src\testclnt.cpp

# --------------------------------------------------------------------------
clean1:
	@ECHO Cleaning...
	-@IF EXIST socket.obj DEL socket.obj
	-@IF EXIST client.obj DEL client.obj
	-@IF EXIST server.obj DEL server.obj
	-@IF EXIST testsrvr.obj DEL testsrvr.obj
	-@IF EXIST testclnt.obj DEL testclnt.obj
	-@IF EXIST testsrvr.exe DEL testsrvr.exe
	-@IF EXIST testclnt.exe DEL testclnt.exe

# --------------------------------------------------------------------------
viewsico.res: "$(VIEWSRESDIR)\viewsico.rc"
	$(RC) $(RCFLAGS) /I"$(VIEWSRESDIR)" -r -foviewsico.res "$(VIEWSRESDIR)\viewsico.rc"


# --------------------------------------------------------------------------
clean: clean1
	-@IF EXIST *.ncb DEL *.ncb
	-@IF EXIST *.pdb DEL *.pdb
	-@IF EXIST *.ilk DEL *.ilk
	-@IF EXIST *.idb DEL *.idb
	-@IF EXIST *.plg DEL *.plg
	-@IF EXIST *.map DEL *.map
	-@IF EXIST *.res DEL *.res
	-@IF EXIST *.bak DEL *.bak
	-@IF EXIST *.lnk DEL *.lnk

