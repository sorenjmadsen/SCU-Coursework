# include <iostream>

using namespace std;



int main()
{
	string token;
	int c = cin.get();

	// Main loop getting characters
	while (!cin.eof()) {
		token.clear();

		// Ignore white space
		if (isspace(c))
			c = cin.get();

		// Integer
		else if (isdigit(c)) {
			token += c;
			c = cin.get();
			while (isdigit(c)){
				token += c;
			}
			cout << "int:" << token << endl;
		}


	}
}
