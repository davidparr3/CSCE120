#include "functions.h"
using std::cin, std::cout, std::endl, std::ostream, std::string;

#define INFO(X)  cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;
#define INFO_STRUCT(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " count = " << X.count << endl;

/**
 * ----- REQUIRED -----
 * Pushes number to top of stack. If stack is full, then resize stack's array.
 * @param   stack   Target stack.
 * @param   number  Number to push to stack.
 */
void push(Stack& stack, int number) {
  // TODO: implement push function for stack
  INFO_STRUCT(stack);
  INFO(number);
  
  
  if(stack.count == stack.capacity){
    //resize array
    int resizedcap = stack.capacity * 2;
    int* newstack = new int[resizedcap];
    for(int i = 0; i < stack.count; i++){
      newstack[i] = stack.numbers[i];
    }
    //clear memory and set edit stack
    delete[] stack.numbers;
    stack.numbers = newstack;
    stack.capacity = resizedcap;
    
  }
  //implement push
  stack.numbers[stack.count] = number;
  stack.count++;
  
}

/**
 * ----- REQUIRED -----
 * Pops number from top of stack. If stack is empty, return INT32_MAX.
 * @param   stack   Target stack.
 * @return          Value of popped number.
 */
int pop(Stack& stack) {
  // TODO: implement pop function for stack
  INFO_STRUCT(stack);
  
  //check for empty stack
  if(stack.count == 0){
    return INT32_MAX;
  }
  //get pop val
  int pop = stack.numbers[stack.count - 1];
  //resize stack
  stack.count--;

  return pop;
}

/**
 * ----- REQUIRED -----
 * Returns the number at top of stack without popping it. If stack is empty, return INT32_MAX.
 * @param   stack   Target statck.
 * @return          Number at top of stack.
 */
int peek(const Stack& stack) {
  // TODO: implement peek function for stack
  INFO_STRUCT(stack);
  //check if count is 0
   if(stack.count == 0){
    return INT32_MAX;
  }
  //get top val
  int peek = stack.numbers[stack.count - 1];
  return peek;
}
