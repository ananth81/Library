#ifndef SQLITEDB_H
#define SQLITEDB_H

#include <vector>
#include <sqlite3.h> 
#include "libbook.h"
#include "libmember.h"

#define DATABASE_FILE "SQlite.db"

class LibSQLiteDB {
    public:
      LibSQLiteDB();
      virtual ~LibSQLiteDB();

     int AddMember(libMember& );
     int RemoveMember(libMember&);
     int AddNewBook(libBook&);
     int RemoveBook(libBook&);
     std::vector<libBook>&  QueryBookAvailability(libBook&);
     std::vector<libMember>& getMemberList(void);
     int IssueBook(libBook&,libMember&);
     int ReturnBook(libBook& , libMember&);
    private:
      sqlite3 *db;
   static int libBookcallback(void *data, int argc, char **argv, char **azColName);
   static int libMembercallback(void *data, int argc, char **argv, char **azColName); 
   static std::vector<libBook> bookVec;
   static std::vector<libMember> memberVec;
   

};
















#endif
