#ifndef LIB_BOOK_H
#define LIB_BOOK_H
#include "book.h"

#define NULL_DATE "0000/00/00"
class libBook: public Book
{
  public:

    libBook()
    {
    }
    libBook(std::string Title ,
             std::string Author ,
             std::string isReference,
             std::string doi,
             std::string dor):Book(Title,Author),
                              misReference(isReference),
                              mdoi(doi),
                              mdor(dor)
     {}

    std::string& isReference(void)
    { return misReference;}
    std::string& getDateOfIssue(void) { return mdoi;}
    std::string& getDateOfReturn(void) { return mdor;}
    std::string& getMemberID(void) { return memberID;}
    std::string& getSerialNo(void) { return mserialNo;}
    std::string& getMemberName(void) { return memberName;}
    void SetisReference(std::string ref) {  misReference=ref;}
    void setDateOfIssue(std::string doi) { mdoi=doi;}
    void setDateOfReturn(std::string dor) { mdor=dor;}
    void setMemberID(std::string memID) { memberID=memID;}
    void setSerialNo(std::string Serial) { mserialNo = Serial;}
    void setMemberName(std::string Name) { memberName = Name;}



 private:
   std::string misReference;
   std::string mdoi;
   std::string mdor;
   std::string mserialNo;
   std::string memberID;
   std::string memberName;
};








#endif
