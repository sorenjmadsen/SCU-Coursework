// FILE: rand_gen.h
// CLASS PROVIDED: rand_gen
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//   (a class to generate pseudorandom numbers)
//   This class is part of the namespace coen79_2C
//
// CONSTRUCTOR for the rand_gen class:
//   rand_gen( );
//     Postcondition: The object has been initialized, and is ready to generate pseudorandom numbers.
//
// PUBLIC MODIFICATION member functions for the rand_gen class:
//  void set_seed(int newSeed)
//    Postcondition: the number new_seed is the new seed
//  int next()
//    Postcondition: The return value is the next random integer, and the return value is set as the new seed
//
// PUBLIC CONSTANT member functions for the rand_gen class:
//  void print_info()
//    Postcondition: Prints the values of the private member variables



#ifndef RAND_NUM_GEN_H
#define RAND_NUM_GEN_H

#include <iostream>
#include <cassert>

using namespace std;

namespace coen79_lab2
{
    
    class rand_gen
    {
    public:
        // CONSTRUCTOR
        rand_gen(int seed = 1, int multiplier = 1, int increment = 1, int modulus = 1);
        
        // MODIFICATION MEMBER FUNCTIONS
        void set_seed(int new_seed);
        int next();
        
        // CONSTANT MEMBER FUNCTIONS
        void print_info();
        
    private:
        int seed;
        int multiplier;
        int increment;
        int modulus;
    };
}


#endif
