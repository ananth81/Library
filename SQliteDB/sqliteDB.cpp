#include "sqliteDB.h"
#include <iostream>
#include <stdio.h>


#define UNUSED_MEMBERID 0UL
                   //yyyy mm dd
#define UNUSED_DATE "0000/00/00"

std::vector<libBook> LibSQLiteDB::bookVec;

LibSQLiteDB::LibSQLiteDB():db(NULL)
{
   char *zErrMsg = 0;
   int rc = sqlite3_open(DATABASE_FILE, &db);

   if( rc ) {
      std::cout<< "Can't open database:" << sqlite3_errmsg(db) << std::endl;
      
   } 
   else {
       
       const char *sqlcommand = "CREATE TABLE  IF NOT EXISTS LIBRARYBOOKS (  \
                                             TITLE TEXT NOT NULL , \
                                             AUTHOR TEXT NOT NULL , \
                                             DOI TEXT, \
                                             DOR TEXT, \
                                             MEMBERID INT, \
                                             REFERENCE TEXT);";
                                             
       rc=sqlite3_exec(db,sqlcommand,&libBookcallback,0,&zErrMsg);
    
       if( rc != SQLITE_OK ){
            std::cout << "SQL error: %s\n" << zErrMsg;
            sqlite3_free(zErrMsg);
       } 
       
       sqlcommand = "CREATE TABLE  IF NOT EXISTS MEMBERS (  \
                                    NAME TEXT NOT NULL , \
                                    ADDRESS TEXT NOT NULL );";
                                             
       rc=sqlite3_exec(db,sqlcommand,&libBookcallback,0,&zErrMsg);
    
       if( rc != SQLITE_OK ){
            std::cout << "SQL error:" << zErrMsg;
            sqlite3_free(zErrMsg);
       } 
   }
}

int LibSQLiteDB::libBookcallback(void *data, int argc, char **argv, char **azColName)
{
   int i;
   libBook book;
   for(i = 0; i<argc; i++) {
      if(std::string(azColName[i]) == "TITLE")
       book.setTitle(std::string(argv[i]));
      if(std::string(azColName[i]) == "AUTHOR")
       book.setAuthor(std::string(argv[i]));
      if(std::string(azColName[i]) == "DOI")
       book.setDateOfIssue(std::string(argv[i])); 
      if(std::string(azColName[i]) == "DOR")
       book.setDateOfReturn(std::string(argv[i])); 
      if(std::string(azColName[i]) == "MEMBERID")
       book.setMemberID(argv[i]); 
      if(std::string(azColName[i]) == "REFERENCE") 
       book.SetisReference(std::string(argv[i]));
      if(std::string(azColName[i]) == "rowid") 
       book.setSerialNo(std::string(argv[i]));
      
   }
   bookVec.push_back(book);
   *(bool*)data=true;
   return 0;
}

int LibSQLiteDB::libMembercallback(void *data, int argc, char **argv, char **azColName)
{
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   *(bool*)data=true;
   return 0;
}


int LibSQLiteDB::AddMember(libMember& member)
{
   bool error = true;
   char *zErrMsg = NULL;
   char *sqlcommand =NULL;
   if(0 < asprintf(&sqlcommand,"INSERT INTO MEMBERS(NAME,ADDRESS) \
                   VALUES ('%s','%s');",member.getName().c_str(),member.getAddress().c_str()))
                  
   {
      int rc=sqlite3_exec(db,sqlcommand,&libMembercallback,0,&zErrMsg);
    
      if( rc != SQLITE_OK ){
            std::cout << "SQL error:" << zErrMsg;
            sqlite3_free(zErrMsg);
       } else {
            std::cout<<"Member Added successfully"<<std::endl;
            error=false;
       }
       free(sqlcommand);
   }
   return error;
}


int LibSQLiteDB::RemoveMember(libMember& member)
{
   bool error = true;
   char *zErrMsg = NULL;
   char *sqlcommand =NULL;
   if(0 < asprintf(&sqlcommand,"DELETE FROM MEMBERS WHERE rowid=%lu  ;",member.getMemberID()))
   {
      int rc=sqlite3_exec(db,sqlcommand,&libMembercallback,0,&zErrMsg);
    
      if( rc != SQLITE_OK ){
            std::cout << "SQL error:" << zErrMsg;
            sqlite3_free(zErrMsg);
       } else {
            error = false;
            std::cout<<"Member Removed successfully"<<std::endl;
       }
       free(sqlcommand);
   }
   return error;
}

int LibSQLiteDB::AddNewBook(libBook& book)
{
   bool error = true;
   char *zErrMsg = NULL;
   char *sqlcommand =NULL;
   if(0 < asprintf(&sqlcommand,"INSERT INTO LIBRARYBOOKS(TITLE,AUTHOR,REFERENCE,MEMBERID,DOI,DOR) \
                   VALUES ('%s','%s','%s',%lu,'%s','%s');",book.getTitle().c_str()
                                            ,book.getAuthor().c_str()
                                            ,book.isReference().c_str()
                                            ,UNUSED_MEMBERID
                                            ,NULL_DATE
                                            ,NULL_DATE))
                  
   {
      int rc=sqlite3_exec(db,sqlcommand,&libBookcallback,0,&zErrMsg);
    
      if( rc != SQLITE_OK ){
            std::cout << "SQL error:" << zErrMsg;
            sqlite3_free(zErrMsg);
       } else {
           
            error = false;
            std::cout<<"Added New Book successfully"<<std::endl;
       }
       free(sqlcommand);
   }
   return error;
}

int LibSQLiteDB::RemoveBook(libBook& book)
{
   bool error = true;
   char *zErrMsg = NULL;
   char *sqlcommand =NULL;
   if(0 < asprintf(&sqlcommand,"DELETE FROM LIBRARYBOOKS WHERE rowid = %s ;",book.getSerialNo().c_str()))
   {
      int rc=sqlite3_exec(db,sqlcommand,&libBookcallback,0,&zErrMsg);
    
      if( rc != SQLITE_OK ){
            std::cout << "SQL error:" << zErrMsg;
            sqlite3_free(zErrMsg);
       } else {
            error = false;
            std::cout<<"Removed Book successfully"<<std::endl;
       }
       free(sqlcommand);
   }
   return error;
}

std::vector<libBook>& LibSQLiteDB::QueryBookAvailability(libBook& book)
{
   bool rowFound;
   bool error=true;
   char *zErrMsg = NULL;
   char *sqlcommand =NULL;
   if(0 < asprintf(&sqlcommand,"SELECT rowid,* FROM LIBRARYBOOKS \
                  WHERE TITLE='%s' AND AUTHOR='%s' AND MEMBERID = %lu ;",
                  book.getTitle().c_str(),
                  book.getAuthor().c_str(),
                  UNUSED_MEMBERID))
   {
      bookVec.clear();
      int rc=sqlite3_exec(db,sqlcommand,&libBookcallback,&rowFound,&zErrMsg);
    
      if( rc != SQLITE_OK ){
            std::cout << "SQL error:" << zErrMsg;
            sqlite3_free(zErrMsg);
       } else {
            error = false;
            std::cout<<"Queried Book successfully"<<std::endl;
       }
       free(sqlcommand);
   }
   return bookVec;
}

int LibSQLiteDB::IssueBook(libBook& libbook,libMember& member)
{
   bool error=true;
   char *zErrMsg = NULL;
   char *sqlcommand =NULL;
   if(0 < asprintf(&sqlcommand,"UPDATE LIBRARYBOOKS \
                                SET MEMBERID = %lu \
                                WHERE rowid = %s ;",member.getMemberID(),libbook.getSerialNo().c_str()))
   {
      int rc=sqlite3_exec(db,sqlcommand,&libBookcallback,0,&zErrMsg);
    
      if( rc != SQLITE_OK ){
            std::cout << "SQL error:" << zErrMsg;
            sqlite3_free(zErrMsg);
       } else {
            error = false;
            std::cout<<"Issued Book successfully"<<std::endl;
       }
       free(sqlcommand);
   }
   return error;
}

int LibSQLiteDB::ReturnBook(libBook& libbook, libMember& member)
{
   bool error=true;
   char *zErrMsg = NULL;
   char *sqlcommand =NULL;
   if(0 < asprintf(&sqlcommand,"UPDATE LIBRARYBOOKS \
                                SET MEMBERID = %lu \
                                WHERE rowid = %s ;",UNUSED_MEMBERID,libbook.getSerialNo().c_str()))
   {
      int rc=sqlite3_exec(db,sqlcommand,&libBookcallback,0,&zErrMsg);
    
      if( rc != SQLITE_OK ){
            std::cout << "SQL error:" << zErrMsg;
            sqlite3_free(zErrMsg);
       } else {
            error = false;
            std::cout<<"Returned Book successfully"<<std::endl;
       }
       free(sqlcommand);
   }
   return error;

}


LibSQLiteDB::~LibSQLiteDB()
{
    if(db)
    {
      sqlite3_close(db);
      std::cout<<"Closed DB Successfully"<<std::endl;
    }
}
