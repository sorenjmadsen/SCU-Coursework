//
//  random.cpp
//  Random
//
//  Created by Søren Madsen on 1/17/19.
//  Copyright © 2019 SCU. All rights reserved.
//

#include "random.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2 {
    rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus)
    {
        this->seed = seed;
        this->multiplier = multiplier;
        this->increment = increment;
        this->modulus = modulus;
    }
    
    // MODIFICATION MEMBER FUNCTIONS
    void rand_gen::set_seed(int new_seed)
    {
        seed = new_seed;
    }
    int rand_gen::next(){
        seed = (multiplier * seed + increment) % modulus;
        return seed;
    }
    
    // CONSTANT MEMBER FUNCTIONS
    void rand_gen::print_info()
    {
        cout << "Seed: " << seed << endl;
        cout << "Multiplier: " << multiplier << endl;
        cout << "Increment: " << increment << endl;
        cout << "Modulus: " << modulus << endl;
    }
    
    //int seed;
   // int multiplier;
    //int increment;
    //int modulus;
}
