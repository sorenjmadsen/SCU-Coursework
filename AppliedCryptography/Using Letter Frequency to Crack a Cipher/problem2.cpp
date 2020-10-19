// Applied Cyptography: Dr. Houshmand
// Soren Madsen
// 12 April 2020
// Problem 2: Write a program to perform encryption/decryption using the
// Vigenere cipher.
// Usage: ./problem2 <-d to decrypt, -e to encrypt> <cipher/plain text> <keyword>
// NOTE: Please use uppercase letters! It is structure around the class cases
// of denoiting letters A->Z as integers of 0->25.

#include <iostream>   // Provides cout
using namespace std;

void handle_error(){
  std::cerr << "Usage: ./problem2 <-d to decrypt, -e to encrypt> <cipher/plain text> <keyword> <-u or -l for case>" << std::endl;
}

int main (int argc, char * argv[]){
  bool encrypt;
  bool uppercase;

  // Check argument count
  if (argc != 5){
    handle_error();
    return -1;
  }

  if (argv[1][1] == 'e')
    encrypt = true;
  else if (argv[1][1] == 'd')
    encrypt = false;
  else {
    handle_error();
    return -1;
  }
  if (argv[4][1] == 'u')
    uppercase = true;
  else if (argv[4][1] == 'l')
    uppercase = false;
  else {
    std::cout << argv[4] << endl;
    handle_error();
    return -1;
  }

  string text(argv[2]);
  string keyword(argv[3]);
  int keylen = keyword.length();

  string other(text);

  int start((uppercase ? 'A' : 'a'));
  if (encrypt)
    for (int i = 0; i < text.length(); ++i)
      other[i] = char((((int(text[i]) - start) + (int(keyword[(i % keylen)]) - start)) % 26) + start);
  else
    for (int i = 0; i < text.length(); ++i){
      int ascii = (((int(text[i]) - start) - (int(keyword[(i % keylen)]) - start)) % 26) + start;
      other[i] = char((ascii - start < 0) ? ascii + 26 : ascii);
    }

  std::cout << "The " << (encrypt ? "encryption" : "decryption") << " is: " << std::endl;
  std::cout << other << std::endl;

  return 0;
}
