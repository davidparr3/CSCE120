//Implement this source file
# include <iostream>
# include <fstream>
# include "Rover.h"
# include "MyString.h"
using std::cin, std::cout, std::endl, std::ifstream, std::istream;

//Constructors
//Default
MyString::MyString() : privSize(0), privCapacity(privSize + 1), ary(new char[privCapacity]) {}

//copy
MyString::MyString(const MyString& str) : privSize(str.privSize), privCapacity(str.privSize + 1), ary(new char[privCapacity]) {
    //leave one for null
    for (size_t i = 0; i < privSize + 1; i++) {
        ary[i] = str.ary[i];
    }
}
            

//from C-String
MyString::MyString(const char* s) : privSize(0), privCapacity(0), ary(nullptr) {
    //set Size
        int j = 0;
        while(s[j] != '\0'){
            j++;
            privSize++;
        }

        privCapacity = privSize + 1;
        ary = new char[privCapacity];
        for(size_t k = 0; k < privSize; k++){
            ary[k] = s[k];
        }

     ary[privSize] = '\0';   
    
}
        
//Destructor
MyString::~MyString(){
    //delete ary from heap
    delete[] ary;
}

//Resize
void MyString::resize (size_t n){
                size_t oldSize = privSize;
                char* newAry = new char[privCapacity];
                for(size_t i = 0; i < privCapacity; i++){
                    newAry[i] = ary[i];
                }
                delete[] ary;

                //n less than orig
                if(n < oldSize){
                    privSize = n;
                    ary = new char[n + 1];
                    for(size_t i = 0; i < n; i++){
                        ary[i] = newAry[i];
                    }
                }
                
                //n greater than orig
                if(n > oldSize){
                    privSize = oldSize;
                    privCapacity = n;
                    ary = new char[privCapacity];
                    for(size_t i = 0; i < oldSize; i++){
                        ary[i] = newAry[i];
                    }
                }
                delete[] newAry;
            }

//Capacity
size_t MyString::capacity() const{
    //get capacity
    return privCapacity;
}

//Size
size_t MyString::size() const{
    //get size
    return privSize;
}

//Length
size_t MyString::length() const{
    // set length = to num of chars
    return privSize;
}
        
//Data
const char* MyString::data() const{
    //return individual elems
    return ary;
}

//Empty
bool MyString::empty() const{
    //check if char 0 is null
    if(privSize == 0){
        return true;
    }
    return false;
}

//Front
const char& MyString::front() const{
    //return first char
    return ary[0];
}

//At
const char& MyString::at(size_t pos) const{
    //bounds check
    if((pos >= privSize) || (privSize == 0)){
        throw std::out_of_range("");
    }
    return ary[pos];
}
            
//Clear
void MyString::clear(){
    //wipe string
    privSize = 0;
    privCapacity = 0;
    ary[0] = '\0';
}
        
//Operator <<
std::ostream& operator<< (std::ostream& os, const MyString& str){
    os << str.data();
    return os;
}

//Operator =
MyString& MyString::operator= (const MyString& str){
    if (this != &str) {
        delete[] ary;
        privSize = str.privSize;
        privCapacity = str.privSize + 1;
        //allocate new memory
        ary = new char[privCapacity];
        //copy
        for (size_t i = 0; i < privSize + 1; i++) {
            ary[i] = str.ary[i];
        }
    }

        return *this;                
}

//Operator +=
MyString& MyString::operator+= (const MyString& str){
    size_t oldSize = privSize;
    size_t strSize = str.privSize;
    privSize = strSize + oldSize;
    privCapacity = strSize + oldSize + 1;

    char* newAry = new char[privCapacity];
    for(size_t i = 0; i < oldSize; i++){
        newAry[i] = ary[i];
    }

    for(size_t i = 0; i < strSize + 1; i++){
        newAry[oldSize + i] = str.ary[i];
    }

   //
    delete[] ary;
    ary = newAry;

    return *this;     
}

//Find
int MyString::find(const MyString& str, size_t pos) const noexcept {
                //starting index
                size_t start = 0;
                if(pos){
                    start = pos;
                }

                //validate params
                if((pos > privSize) || (str.privSize > (privSize - start))){
                    return -1;
                }

                //find opp
                for(size_t i = start; i < privSize; i++){
                    if(ary[i] == str.ary[0]){
                        bool inStr = true;
                        for(size_t j = 0; j < str.privSize; j++){
                            if(ary[j + i] != str.ary[j]){
                                inStr = false;
                                break;
                            }
                            if((j == str.privSize - 1) && inStr){
                                return i;
                            }
                        }
                    }
                }

                return -1;
            }

//Operator ==
bool operator== (const MyString& lhs, const MyString& rhs) noexcept{
    //check length
    if(lhs.size() != rhs.size()){
        return false;
    }

    const char* lhsAry = lhs.data();
    const char* rhsAry = rhs.data();
    //check vals
    for(size_t i = 0; i < rhs.size(); i++){
        if(lhsAry[i] != rhsAry[i]){
            return false;
        }
    }
    
    return true;
}

//Operator +
MyString operator+ (const MyString& lhs, const MyString& rhs){
    size_t lhsSize = lhs.privSize;
    size_t rhsSize = rhs.privSize;
    size_t privSize = lhsSize + rhsSize;
    size_t privCapacity = privSize + 1;

    char* newAry = new char[privCapacity];
    for(size_t i = 0; i < lhsSize; i++){
        newAry[i] = lhs.ary[i];
    }

    for(size_t i = 0; i < rhsSize + 1; i++){
        newAry[lhsSize + i] = rhs.ary[i];
    }

    //build new string
    MyString newString(newAry);

   //clear memory
    delete[] lhs.ary;
    delete[] rhs.ary;
    

    return newString; 
}