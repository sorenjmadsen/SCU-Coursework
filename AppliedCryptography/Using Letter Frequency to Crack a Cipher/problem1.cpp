// Applied Cyptography: Dr. Houshmand
// Soren Madsen
// 12 April 2020
// Problem 1: Using letter frequency, crack the monoalphabetic substitution
// cipher.

#include <iostream>   // Provides cout
#include <vector>
using namespace std;

int main (int argc, char * argv[]){
  std::string ct = "ZJRJ AZJRJ VX F XARMCO ARFUVAVMC MQ XAMRI AJTTVCO FX F RJXNTA MQ AZVX GMXA WJMWTJ FRJ ARJGJCUMNX WNKTVP XWJFSJRX FCU AZJRJ VX FTGMXA CM HRVAAJC XWJJPZ";
  std::vector<int> letter_count(26,0);


  for (int i = 0; i < ct.length(); ++i){
    if (ct[i] == ' ') continue;               // Skip spaces

    // Increment each letter count with respect to A in ASCII
    ++letter_count[int(ct[i]) - int('A')];
  }
  std::cout << "Letter Frequencies" << std::endl;
  for (int i = 0; i < 26; ++i){
    std::cout << char(i + int('A')) << " " << letter_count[i] << std::endl;
  }

  // After some cryptanalysis, I found the following possible translations
  for (int i = 0; i < ct.length(); ++i){
    if (ct[i] == 'J')
      ct[i] = 'E';
    else if (ct[i] == 'A')
      ct[i] = 'T';
    else if (ct[i] == 'Z')
      ct[i] = 'H';
    else if (ct[i] == 'X')
      ct[i] = 'S';
    else if (ct[i] == 'V')
      ct[i] = 'I';
    else if (ct[i] == 'F')
      ct[i] = 'A';
    else if (ct[i] == 'M')
      ct[i] = 'O';
    else if (ct[i] == 'T')
      ct[i] = 'L';
    else if (ct[i] == 'G')
      ct[i] = 'M';
    else if (ct[i] == 'N')
      ct[i] = 'U';
    else if (ct[i] == 'C')
      ct[i] = 'N';
    else if (ct[i] == 'U')
      ct[i] = 'D';
    else if (ct[i] == 'O')
      ct[i] = 'G';
    else if (ct[i] == 'Q')
      ct[i] = 'F';
    else if (ct[i] == 'I')
      ct[i] = 'Y';
    else if (ct[i] == 'P')
      ct[i] = 'C';
    else if (ct[i] == 'S')
      ct[i] = 'K';

      // From here, I decrypted the rest by hand.

  }
  std::cout << ct << std::endl;

  return 0;
}
