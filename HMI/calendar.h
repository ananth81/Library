class Calendar {
  public :
    Calendar(int year , int month , int day):m_year(year),
                                             m_month(month),
                                             m_day(day)
                                             {
                                             }
  
   std::string getFutureDate(int days)
   {
      std::stringstream Date;
      int months[]={-1,31,28,31,30,31,30,31,31,30,31,30,31};
      int y=m_year,m=m_month,d=m_day;
      
      while(days)
      {
        months[2]=(isLeapYear(y))?29:28;
        if(days <= (months[m] - d)) {
            d+=days;
            days=0;
        }
        else {
          days-= months[m]-d;
          m++;
          d=0;
          if(m > 12)
          {
            m=1;
            y++;
          }
             
        }
     }
     Date << y<<"/"<<m<<"/"<<d;
     return(Date.str());
   }
   
   private:
   bool isLeapYear(int y)
   {
       if ((y%4) ==0)
       {
          if((y%400) == 0)
            return true;
          else if( (y%100) ==0)
            return false;
          else
            return true;
       }
       else 
         return false;
       
   }
   int m_year;
   int m_month;
   int m_day;
                                             
};
