//
//  pattern.cpp
//  Lab1
//
//  Created by Søren Madsen on 1/10/19.
//  Copyright © 2019 SCU. All rights reserved.
//

#include <iostream>
#include <iomanip>

int main(int argc, const char * argv[]){
	std::string seq = "0123456789";
	int winsize = 10;

	// Reverse, reverse!
	std::string rev(seq);
	std::reverse(rev.begin(), rev.end());

	std::cout << seq << std::endl;

	// Make that staircase
	for(int rotation = 0; rotation < 4; rotation++){
		std::cout << std::setw(++winsize);
		std::cout << rev;
		std::cout << std::setw(++winsize);
		std::cout << "";
		std::cout << seq << std::endl;
	}

	// Last one
	std::cout << std::setw(++winsize);
	std::cout << rev << std::endl;

	return 0;
}