#ifndef LIB_MEMBER_H
#define LIB_MEMBER_H
#include <string>

class libMember {
    public:
    typedef unsigned long MemberID; 
    libMember(std::string name , std::string address , MemberID ID):mName(name),
                                                                    mAddress(address),
                                                                    mId(ID)
    {}
    std::string& getName() { return mName;}
    std::string& getAddress() { return mAddress;}
    MemberID& getMemberID(){ return mId;}
    
    private:
      std::string mName;
      std::string mAddress;
      MemberID mId;
   
    

};

#endif
