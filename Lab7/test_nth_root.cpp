#include <iostream>
#include <cmath>
#include "./nth_root.h"

using std::cout, std::endl;

int main() {
    {   // MINIMUM REQUIREMENT (for this lab)
        // just call the function with various values of n and x
        try{
            nth_root(0, 1); //A
        }catch(std::domain_error&){
            cout << "Domain";
        }
        try{
            nth_root(2, -1); //B
        }catch(std::domain_error&){
            cout << "Domain";
        }
        try{
            nth_root(-1, 0); //C
        }catch(std::domain_error&){
            cout << "Domain";
        }
        try{
            nth_root(1,2); //D
        }catch(std::domain_error&){
            cout << "Domain";
        }
        try{
            nth_root(-1,2); //E
        }catch(std::domain_error&){
            cout << "Domain";
        }
        try{
            nth_root(-6, 1); //FG
        }catch(std::domain_error&){
            cout << "Domain";
        }
        try{
            nth_root(-5, 1); //H
        }catch(std::domain_error&){
            cout << "Domain";
        }
        
        nth_root(6, 1); //I
        nth_root(2, 1); //JLP
        try{
            nth_root(1, 0); //K
        }catch(std::domain_error&){
            cout << "Domain";
        }
        try{
            nth_root(3, -2); //M
        }catch(std::domain_error&){
            cout << "Domain";
        }
        
        nth_root(2, 3);
        nth_root(2, 1.5);

    }

    {   // TRY HARD
        // report the value
        double actual = nth_root(2, 1);
        std::cout << "nth_root(2, 1) = " << actual << std::endl;
    
    }

    {   // TRY HARDER
        // compare the actual value to the expected value
        double actual = nth_root(2, 1);
        double expected = 1;
        if (std::fabs(actual - expected) > 0.00005) {
            std::cout << "[FAIL] (n=2, x=1)" << std::endl;
            std::cout << "  expected nth_root(2, 1) to be " << expected << std::endl;
            std::cout << "  got " << actual << std::endl;
        } else {
            std::cout << "[PASS] (n=2, x=1)" << std::endl;
        }
    }
}
