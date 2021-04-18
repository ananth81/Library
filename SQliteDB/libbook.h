#ifndef LIB_BOOK_H
#define LIB_BOOK_H
#include "book.h"


class libBook: public Book
{
  public:
    typedef  unsigned long serialNo; 
    libBook():mserialNo(0)
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
    serialNo& getMemberID(void) { return memberID;}
   
    void SetisReference(std::string ref)
    {  misReference=ref;}
    void setDateOfIssue(std::string doi) { mdoi=doi;}
    void setDateOfReturn(std::string dor) { mdor=dor;}
    void setMemberID(serialNo memID) { memberID=memID;}
   
    
    serialNo getSerialNo(void) { return mserialNo;}    
 private:
   std::string misReference;
   std::string mdoi;
   std::string mdor;
   serialNo mserialNo;
   serialNo memberID;
};








#endif
