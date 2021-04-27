#ifndef BOOK_H
#define BOOK_H
#include <string>
class Book {
  public:
    Book() {}
    Book(std::string Title ,
         std::string Author
         ):mTitle(Title),
           mAuthor(Author)

    {
    }
    std::string& getTitle()
    { return mTitle;}

    std::string& getAuthor()
    { return mAuthor;}

    void setTitle(std::string title)
    {  mTitle=title;}

    void setAuthor(std::string author)
    {mAuthor=author;}

    private:
    std::string mTitle;
    std::string mAuthor;

};


#endif
