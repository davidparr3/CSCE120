#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	// TODO(student): print prompt for input
	// TODO(student): read the numbers from standard input
	// TODO(student): validate input (and reprompt on invalid input)
	bool valid = false;
	while (valid == false){
		cout << "Enter numbers 10 <= a <= b < 10000: ";
		int a = 0;
		int b = 0;
		cin >> a >> b;
		if(is_valid_range(a, b)){
			valid = true;
			count_valid_mv_numbers(a,b);
			break;
		}
		else{
			cout << "Invalid Input" << endl;
		}
	}
		
	// TODO(student): compute and display solution
	
	return 0;
}