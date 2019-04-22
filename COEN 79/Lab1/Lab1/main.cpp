//
//  main.cpp
//  Lab1
//
//  Created by Søren Madsen on 1/10/19.
//  Copyright © 2019 SCU. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "test.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int i = 1;
    int j = 2;
    
    i++;
    int k = i + j;
    
    std::cout << "k is " << k << std::endl;
    
    print_hello();
    
    // Just put it in the same folder as .cpp and it works perfectly
    std::string fileLoc = "/Users/sorenmadsen/Documents/Programs/COEN79/Lab1/Lab1/GettysburgAddress.txt";
    
    // Time to read
    std::ifstream input;
    input.open(fileLoc);
    
    if(!input) std::cerr << "File open error" << std::endl;
    
    std::string edit = "";
    std::string word = "";
    
    // Read it
    while(input >> word){
        // Is it a big word?
        if(word.length() >= 10){
            // Cool, let's make it better
            for(int i = 0; i < word.length(); i++){
                if(isalnum(word[i])) edit.push_back(toupper(word[i]));
            }
            // Print that word
            std::cout << edit << std::endl;
            edit = "";
        }
    }
    input.close();
    
    return 0;
}
