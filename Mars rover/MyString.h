//Implement this header file
# ifndef _MYSTRING_H_
# define _MYSTRING_H_
# include <iostream>
# include <fstream>
using std::cin, std::cout, std::endl, std::ifstream, std::istream;

class MyString {
    private:
        unsigned int privSize;
        unsigned int privCapacity;
        char* ary;
    
    public:
        //Constructors
            //Default
            MyString();
            //copy
            MyString(const MyString& str);
            //from C-String
            MyString(const char* s);
        
        //Destructor
            ~MyString();

        //Resize
            void resize (size_t n);

        //Capacity
            size_t capacity() const;

        //Size
            size_t size() const;

        //Length
            size_t length() const;

        //Data
            const char* data() const;

        //Empty
            bool empty() const;

        //Front
            const char& front() const;

        //At
            const char& at (size_t pos) const;
            
        //Clear
            void clear();

        //Operator <<
            friend std::ostream& operator<< (std::ostream& os, const MyString& str);

        //Operator =
            MyString& operator= (const MyString& str);

        //Operator +=
            MyString& operator+= (const MyString& str);

        //Find
            int find (const MyString& str, size_t pos = 0) const noexcept;

        //Operator ==
            friend bool operator== (const MyString& lhs, const MyString& rhs) noexcept;

        //Operator +
            friend MyString operator+ (const MyString& lhs, const MyString& rhs);
    
};



# endif