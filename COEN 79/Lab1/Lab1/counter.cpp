//
//  counter.cpp
//  Lab1
//
//  Created by Søren Madsen on 1/10/19.
//  Copyright © 2019 SCU. All rights reserved.
//
#include <iostream>
#include <ctype.h>

int main(int argc, const char * argv[]){
	std::string input;
	int alNum = 0, n = 0;
	// Do you have a string?
	std::cout << "String?" << std::endl;
	// We got that string
	std::getline(std::cin, input);

	for(int i = 0; i < input.length(); i++){
		// Is the character a space?
		if(input[i] == ' ') continue;
		// Nah, is it alphanumeric?
		else if(isalnum(input[i])) 	alNum++;
		// Nah
		else					n++;
	}

	// Let them know what we thought of the string
	std::cout << "\"" << input << "\" has " << alNum << " alphanumeric characters and " << n << " non-alphanumeric characters." << std::endl;
	return 0;
}