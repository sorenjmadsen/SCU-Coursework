// Applied Cyptography: Dr. Houshmand
// Soren Madsen
// 12 April 2020
// Problem 3: Solve for the given ciphertext given it's a Vigenere cipher. Calcuates
// the letter frequencies of a given column given a possible key length.
// Usage: ./problem3 <path to ciphertext> <key length> <column>

#include <iostream>   // Provides cout
#include <fstream>
#include <vector>
using namespace std;

int main (int argc, char * argv[]){

  int keylen = atoi(argv[2]);
  int col = atoi(argv[3]);

  int start('a');
  std::vector<int> letter_count(26,0);

  ifstream ct;
  ct.open(argv[1], ios::in);
  char ch;

  for (int i = 0; i < col && !ct.eof(); ++i)
    ct.get(ch);

  while (true){
    ct.get(ch);
    if(ct.eof()) break;
    ++letter_count[int(ch) - start];
    for (int i = 0; i < (keylen - 1) && !ct.eof(); ++i)
      ct.get(ch);
  }
  std::cout << "Letter Frequencies" << std::endl;
  int total = 0;
  for (int i = 0; i < 26; ++i){
    std::cout << char(i + start) << " " << letter_count[i] << std::endl;
    total += letter_count[i];
  }
  std::cout << total << endl;

  return 0;
}
