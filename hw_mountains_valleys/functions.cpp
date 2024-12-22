#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range
	if ((a >= 10) and ((b >= a) and (b < 10000)))
	{
		return true;
	}
	
	return false;
}

char classify_mv_range_type(int number) {
	std::string numstr = std::to_string(number);
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	bool mountain = true;
	bool valley = true;
	int count = numstr.size();
	int i = 0;
	if (count == 2){
		if (int(numstr[i]) < int(numstr[i+1])){
			return 'M';
		}	
		if (int(numstr[i]) > int(numstr[i+1])){
			return 'V';
		}	
		return 'N';
	}

	if ((count == 4) or (count == 6) or (count == 8) or (count == 10)){
		for (int i = 1; i < count-1; i+=2){
		if (!(numstr[i - 1] < numstr[i] && numstr[i] > numstr[i + 1] && numstr[i + 1] < numstr[i + 2])) {
			mountain = false;
			break;
		}
	}

	
		for (int i = 1; i < count-1; i+=2){
			if (!(numstr[i - 1] > numstr[i] && numstr[i] < numstr[i + 1] && numstr[i+1] > numstr[i+2])) {
				valley = false;
				break;
			}
		}
		if (mountain){
			return 'M';
		}
	
		if (valley){
			return 'V';
		}
		return 'N';
	}
	

	for (int i = 1; i < count-1; i+=2){
		if (!(numstr[i - 1] < numstr[i] && numstr[i] > numstr[i + 1])) {
			mountain = false;
			break;
		}
	}

	
	for (int i = 1; i < count-1; i+=2){
		if (!(numstr[i - 1] > numstr[i] && numstr[i] < numstr[i + 1])) {
			valley = false;
			break;
		}
	}

	if (mountain){
		return 'M';
	}
	
	if (valley){
		return 'V';
	}
	return 'N';
	

	
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	int i = a;
	int M = 0;
	int V = 0;
	while (i != b+1){
		if (classify_mv_range_type(i) == 'M'){
			M += 1;
		}
		else if (classify_mv_range_type(i) == 'V'){
			V += 1;
		}
		i += 1;
	}
	cout << "There are " << M << " mountain ranges and " << V << " valley ranges between " << a << " and " << b << "." << endl;
}