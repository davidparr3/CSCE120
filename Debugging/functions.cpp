#include <iostream>
#include <string>
#include <sstream>
#include "functions.h"
#include <climits>

using std::cout, std::cin, std::endl, std::string;
 
bool SumIsEven(int a, int b) {
  if((a+b)%2)
  {
    return false;
  }
  else
  {
    return true;
  }
}

int Largest(int a, int b, int c) {
  if (a >= b && a >= c)
   {
    return a;
   }
  if (b >= a && b >= c)
  {
    return b;
  }
   
  return c;
}

unsigned int BoxesNeeded(int apples) {
  int boxes = 1;
  if (apples <= 0)
    {
    boxes = 0;
    }
  while(apples > 20)
    {
    boxes++;
    apples -= 20;
    }
  return boxes;
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
  if ((A_correct > A_total || B_correct > B_total)
      || A_correct < 0 || A_total < 0 || B_correct < 0 || B_total < 0)

  {
    throw std::invalid_argument("Invalid Argument");
  }

  if (static_cast<double>(A_correct) / A_total > static_cast<double>(B_correct) / B_total)
  {
    return true;
  }
  
  return false;
}

bool GoodDinner(int pizzas, bool is_weekend) {
  if (is_weekend && !(pizzas >= 10)) {
    return false;
  }
  if (!is_weekend && (!(pizzas >= 10) || !(pizzas <= 20))) {
    return false;
  }

  return true;
}

long long SumBetween(long long low, long long high) {
long long value = 0;
  if (low > high)
  {
    throw std::invalid_argument("Invalid Argument");
  }

  

  for (long long n = low; n < high + 1; n++) {
    if (value == LLONG_MAX || value == LLONG_MIN)
      {
      return value;
      }
   
    if ((n > 0 && value > LLONG_MAX - n) || (n < 0 && value < LLONG_MIN - n))
      {
      throw std::overflow_error("");
      }
  
    
    value += n;
  }
  return value;
}

long long Product(long long a, long long b) {
  if (a == 0 || b == 0)
  {
    return 0;
  }
  
  if((a > 0 && b > 0 && a > LLONG_MAX / b)
    ||  (a > 0 && b < 0 && b < LLONG_MIN / a)
    ||  (a < 0 && b > 0 && a < LLONG_MIN / b)
    ||  (a < 0 && b < 0 && a < LLONG_MAX / b)
    
  ){
    throw std::overflow_error("");
    }

  return a*b;
}