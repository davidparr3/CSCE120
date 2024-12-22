/******************************************************************************

File: main.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Updates
Author: J. Michael Moore & Paul Taele
Author: J. Michael Moore

Input information format
<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
32.7 USA 12 Moore
36.5 RUS 35 Polsley
45.8 ENG 73 Teale
52.34 CHN 14 Nemec
76.45 ITY 23 Lupoli     

*******************************************************************************/

#include <iostream>
#include <cstring>
#include "rank_functions.h"

using std::cin; using std::cout; using std::endl;

int main()
{
    // TODO: create arrays needed
	double times[SIZE]; 
    char countries[SIZE][STRING_SIZE]; 
    unsigned int numbers[SIZE]; 
    char lastnames[SIZE][STRING_SIZE]; 
    unsigned int ranks[SIZE];

    // TOTO: prep all arrays
    prep_double_array(times); 
    prep_unsigned_int_array(numbers); 
    prep_string_array(countries); 
    prep_string_array(lastnames);
	
    // TODO: load the driver's data into the array
   
    // if unable to load runner data
    //   1) output "Bad input" to standard out
    //   2) exit program by returning 1
    //<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
  
    if (!get_driver_data(times, countries, numbers, lastnames))
        {
            cout << "Bad input";
            return 1;
        }
    // TODO: determine ranking, notice the rank array receives the results
    set_rankings(times, ranks);

    // TODO: Output results
    print_results(times, countries, lastnames, ranks);
    // this is not required in C++ but many people still explitly add it
    return 0; 
}

