#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
  int i = 0;
  while (str[i] != '\0')
  {
    i++;
  }
  
  // returns the length of the string including zero (0)
  return i;
}

unsigned int find(char str[], char character) {
  int i = 0;
  while (str[i] != '\0')
  {
    if (str[i] == character)
    {
      return i;
    }
    i++;
  }
  // returns 
  //  - the index of the first occurence of character in str
  //  - the size if the character is not found
  return i;
}

bool equalStr(char str1[], char str2[]) {
  int i = 0;
  while ((str1[i] != '\0') and (str2[i] != '\0'))
  {
    if (str1[i] != str2[i])
    {
      return false;
    }
  i++;
  }
  // returns true if they are equal and false if they are not
  return true;
}