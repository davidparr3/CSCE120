#include <iostream>
#include <iomanip>
#include <cstring>
#include "rank_functions.h"

using std::cin, std::cout, std::endl;

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an array of doubles is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
	for (unsigned int i = 0; i < SIZE; i++)
	{
		ary[i] = 0.0;
	}
	
}

//-------------------------------------------------------
// Name: prep_unsigned_int_array
// PreCondition:  an array of unsigned ints is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
  for (unsigned int i = 0; i < SIZE; i++)
	{
		ary[i] = 0;
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  an array of strings is passed in
// PostCondition: each element in the array is set to "N/A"
//---------------------------------------------------------
void prep_string_array(char ary[][STRING_SIZE])
// making sure all values within the array are set to "N/A";
{
	for (unsigned int i = 0; i < SIZE; i++)
	{
		strcpy(ary[i], "N/A");
	}
}

//-------------------------------------------------------
// Name: trim
// PreCondition:  the cstring
// PostCondition: whitespace has been removed from beginning and end of string
//---------------------------------------------------------
void trim(char str[STRING_SIZE]) {
	int num = 0;
	int end = strlen(str) - 1;
	while (isspace((unsigned char)str[num])) 
	{
        num++;
	}
	while (isspace((unsigned char)str[end])) 
	{
        end--;
    }
	if (num > end) {
        str[0] = '\0'; 
        return;
	}
	str[end + 1] = '\0';
	if ((num > 0) || (end > 0)) 
	{
        memmove(str, str + num, end - num + 2);
	}
	
}

//-------------------------------------------------------
// Name: get_driver_data
// PreCondition:  the prepped parallel arrays
// PostCondition: all arrays contain data from standard in
//---------------------------------------------------------
bool get_driver_data(double timeArray[], char countryArray[][STRING_SIZE], 
		unsigned int numberArray[], char lastnameArray[][STRING_SIZE]) 
{
  	for (unsigned int i = 0; i < SIZE; i++)
  	{
		//get input
		cin >> timeArray[i] >> countryArray[i] >> numberArray[i];
		cin.ignore();
    	cin.getline(lastnameArray[i], STRING_SIZE);

		// validate time
		if (timeArray[i] < 1)
  		{
			return false;
  		}

		// validate country
		trim(countryArray[i]);
		if (strlen(countryArray[i]) != 3)
		{
			return false;
		}
		for (unsigned int j = 0; j < 3; j++)
		{
			if (!isalpha(countryArray[i][j]) || !isupper(countryArray[i][j]))
			{
				return false;
			}
		}

		// validate number
		if (numberArray[i] >= 100) 
		{
			return false;
		}

		//validate lastname
		trim(lastnameArray[i]);
		unsigned int lastnameLength = strlen(lastnameArray[i]);
		if (lastnameLength < 2)
		{
			return false;
		}
		
		for (unsigned int j = 0; j < lastnameLength - 1; j++)
		{
			if (!isalpha(lastnameArray[i][j]) && !isspace(lastnameArray[i][j]))
			{
				return false;
			}
		}
		
		
		
  	}
  
  return true; // set so it will compile
}

//-------------------------------------------------------
// Name: set_rankings
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void set_rankings(const double timeArray[], unsigned int rankArray[])
{
	for (unsigned int i = 0; i < SIZE; i++)
	{
		rankArray[i] = 1;
		for (unsigned int j = 0; j < SIZE; j++)
		{
			if (timeArray[i] > timeArray[j])
			{
				rankArray[i]++;
			}
			
		}
		
	}
	
}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays them along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const char countryArray[][STRING_SIZE],
		const char lastnameArray[][STRING_SIZE], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}