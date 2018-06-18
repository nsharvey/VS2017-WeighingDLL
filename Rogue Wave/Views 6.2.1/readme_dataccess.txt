		      Rogue Wave Views Data Access - Version 6.2.1

			       README File

Migration from previous releases
--------------------------------

   All known incompatibilities of this version of Rogue Wave Views Data Access
   with previous versions are described in the file "RELEASE_dataccess".
   Please read it if you have any problems compiling or running your old
   applications.


Requirements
------------

   Rogue Wave Views Data Access 2017 requires Rogue Wave Views 2017 and
   Rogue Wave DB Link 2017.

   In addition, depending on the database you intend to use, you
   will need the appropriate client support files (libraries) 
   provided by your database vendor.


   DBMS          VERSION          PRODUCT
   -----------------------------------------------------------------
   Oracle        11g, 12c         Oracle client
   -----------------------------------------------------------------
   Informix      5-11             SDK 3.5
   -----------------------------------------------------------------
   Sybase        12.x or 15.x     Open Client /C Developers Kit
   -----------------------------------------------------------------
   DB2           9.x, 10.x        DB2 Connect
   -----------------------------------------------------------------

Platforms
---------

   Rogue Wave Views Data Access is delivered with a set of libraries that are
   stored in a directory that depends on the type of machine you are using,
   the operating system it runs on, and the compiler you plan to use. To get
   the list of platforms, see the Views readme file.

Formats
-------

   The different formats are:

	stat_mta: static library in multi thread with static run-time
		  library using new IOStreams.
		 Flags: /GX /GR /MT (Multi Threaded).
                 Requires: Views   stat_mta libraries.
                           Db Link stat_mta libraries.
                           The dbms must be known at compile time.

	stat_mda: static library in multi thread with dynamic run-time
		  library using new IOStreams.
		 Flags: /GX /GR /MD (Multi Threaded  DLL).
                 Requires: Views   stat_mda libraries.
                           Db Link stat_mda libraries.
                           If the 'dblnkdyn.lib' library is used then the
                           dbms can be selected at run-time by loading
                           one or more of the dbms-specific DLLs found
                           in the Dbink lib/<system>/dll_mda directory.

	dll_mda: dynamic library in multi thread with dynamic run-time
		 library using new IOStreams.
		 Flags: /GX /GR /MD /DILVDLL (Multi Threaded DLL).
                 Requires: Views   dll_mda libraries.
                           Db Link dll_mda libraries.
                           If the 'dblnkdyn.lib' library is used then the
                           dbms can be selected at runtime.


Execution requirements
----------------------

   In this section, X.Y indicates the current version of Rogue Wave Views
   and Rogue Wave DB Link.

   You will need to define the following  environment variables 
   (adjusting their values to your installation requirements) :

   C:\> SET ILVHOME="C:\Program Files\Rogue Wave\Views X.Y"
   C:\> SET ILDHOME="C:\Program Files\Rogue Wave\DB Link X.Y"


   alternatively, you can add to the VIEWS.INI file :

   IlvHome=C:\Program Files\Rogue Wave\Views X.Y
   IldHome=C:\Program Files\Rogue Wave\DB Link X.Y


Compilation
-----------

   In this section, X.Y indicates the current version of Rogue Wave Views
   and Rogue Wave DB Link.

   The following variables should be defined in the environment :

   C:\> SET ILVHOME="C:\Program Files\Rogue Wave\Views X.Y"
   C:\> SET ILDHOME="C:\Program Files\Rogue Wave\DB Link X.Y"


   In addition, you need to define any DBMS-specific environment 
   variables.

   Assuming the database support files have been installed in
   directory C:\ :

   db2:
	C:\> SET DB2DIR=C:\DB2

   informix:
	C:\> SET INFORMIXDIR=C:\INFORMIX

   oracle:
	C:\> SET ORACLE_HOME=C:\ORACLE

   sybase:
	C:\> SET SYBASE=C:\SYBASE


Important Note for Db Link Users
--------------------------------

       The 'dblink.lib'(dll) is now replaced by :

            *) dbkernel.lib + dblnkst.lib in static mode
            *) dbkernel.lib(dll)+ dblnkdyn.lib(dll) in dynamic mode.


Db Link requirements (not using the dynamic loader)
--------------------

       The following library formats can be used :

                stat_mta
                stat_mda
                dll_mda

   The following steps must be taken in order to include support for 
   database access into your applications :

   1- The type of database used must be known at compile time.

   2- The source file containing the main() function should include
      the following code:

      #include <ilviews/dataccess/dbms/session.h>
      #include <ildblink/dblink.h>
               
      static IldDbms* ILVCALLBACK
      CustomNewDbms (const char* dbms, const char* params) {
        return IldNewDbms(dbms, params);
      }

      int main() {
                  IliSQLSession::SetNewDbmsFunction(CustomNewDbms);
                  ...
      }

   3- When this file is compiled, one or more of the following macro
      symbols should be defined :

                  ILDDB2
                  ILDINFORMIX
                  ILDORACLE
                  ILDSYBASE
                  ILDODBC
                  ILDOLEDB

      This can be done either by adding a line such as :

             #define ILDORACLE

      at the beginning of the source file, or better, by providing
      the C++ compiler an option such as :

                  /D "ILDORACLE"

   4- The application should be linked with one or more of the following
      Db Link libraries :

             dbdb2.lib           (DB2 9.x, 10.x)
             dbdb29x.lib         (DB2 9.x, 10.x)
             dbinf9.lib          (Informix 5-11)
             dbora.lib           (Oracle 11g, 12c)
             ctsyb.lib           (Sybase Ct-Library)
             dbodbc.lib          (ODBC)
             dboledb.lib         (OleDb)

   5- The application should be linked with any required database
      libraries. These libraries are described in the files found in

             lib/makefiles/<system>/<dbms>.mak

      <dbms> is one of :

         db2                 (DB2 9.x, 10.x)
         db29x               (DB2 9.x, 10.x)
         oracle              (Oracle 11g, 12c)
         informix            (Informix 5-11)
         sybase              (Sybase Ct-Library)
         odbc                (ODBC)
         oledb               (Oledb)

   6- The application should be linked with 'dbkernel.lib' and 'dblnkst.lib'.


Db Link requirements (using the dynamic loader)
--------------------

   The following formats can be used with the Db Link dynamic loader
   which let you defer the choice of database systems until runtime :

                stat_mda
                dll_mda

   In that case the following steps must be taken:

   1- The source file containing the main() function should include
      the following code:

               #define ILDALL
               #include <ilviews/dataccess/dbms/session.h>

   2- The application should be linked with the following
      Db Link libraries :

               dbkernel.lib
               dblnkdyn.lib

   3- At runtime, the following DLL must be reachable through
      the PATH environment variable :

               dbkernel.dll
               dblnkdyn.dll

      In addition one or more of the following DLLs must also 
      be on the PATH :

               dbdb2.dll           (DB2 9.x, 10.x)
               dbdb29x.dll         (DB2 9.x, 10.x)
               dbinf9.dll          (Informix 5-11)
               dbora.dll           (Oracle 11g, 12c)
               ctsyb.dll           (Sybase Ct-Library)
               dbodbc.dll          (ODBC)
               dboledb.dll         (OleDb)


       Care must be taken to ensure that the correct library
       format for Db Link is selected according to the
       Data Access library format used as stated in the 'Library Formats'
       section (i.e., do not mix Data Access dll_mda with Db Link stat_sta
       for instance.)

   4- The application should be linked with 'dbkernel.dll' and 'dblnkdyn.dll'.


SQL Trace
---------

   If you intend to trace SQL statements, you need to define
   the following variable in the 'VIEWS.INI' file :

   TTY=true
   Warnings=true
