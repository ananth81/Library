#ifndef LIB_MEMBER_H
#define LIB_MEMBER_H
#include <string>

class libMember {
    public:
    libMember(){}
    libMember(std::string name , std::string address , std::string ID):mName(name),
                                                                    mAddress(address),
                                                                    mId(ID)
    {}
    std::string& getName() { return mName;}
    std::string& getAddress() { return mAddress;}
    std::string getMemberID(){ return mId;}
    
    void setName(std::string name) { mName=name;}
    void setAddress(std::string address) { mAddress=address;}
    void setMemberID(std::string ID){ mId=ID;}
    
    private:
      std::string mName;
      std::string mAddress;
      std::string mId;
   
    

};

#endif
