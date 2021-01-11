# include <iostream>
# include <set>

using namespace std;


string keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
std::set<std::string> keywordSet(keywords, keywords + 32);

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

		// Integer: one or more digits
		else if (isdigit(c)) {
			token += c;
			c = cin.get();
			while (isdigit(c)){
				token += c;
                c = cin.get();
			}
			cout << "int:" << token << endl;
            continue;
		}

        // Strings: enclosed by double quotes, no newlines or quotes without slashes
        else if (c == '\"'){
            token += c;
            c = cin.get();

            int end = 0;
            while(end != 1){
                if (c == '\\'){
                    token += c;
                    c = cin.get();
                    token += c;
                    c = cin.get();
                    continue;
                }
                else if (c == '\"')
                    end = 1;
                else if (c == '\n')
                    cerr << "Unexpected newline while parsing string" << endl;
                token += c;
                c = cin.get();
            }
            cout << "string:" << token << endl;
            continue;
        }

        // Identifiers + Keywords
        else if (isalnum(c) || c == '_'){
            token += c;
            c = cin.get();
            while(isalnum(c) || c == '_'){
                token += c;
                c = cin.get();
            }
            cout << ((keywordSet.count(token) > 0) ? "keyword:" : "identifier:") << token << endl;
            continue;
        }
        else {
            token += c;
            char nextChar = cin.get();
            switch(c){
                case '=':
                    // Equals Comparison
                    if (nextChar == '='){
                        token += nextChar;
                    }
                    break;
                case '|':
                    // Logical Or
                    if (nextChar == '|'){
                        token += nextChar;
                    }
                    break;
                case '&':
                    // Logical And
                    if (nextChar == '&'){
                        token += nextChar;
                    }
                    break;
                case '!':
                    // Not Equals Comparison
                    if (nextChar == '='){
                        token += nextChar;
                    }
                    break;
                case '<':
                    // Less Than Equals Comparison
                    if (nextChar == '='){
                        token += nextChar;
                    }
                    break;
                case '>':
                    // Greater Than Equals Comparison
                    if (nextChar == '='){
                        token += nextChar;
                    }
                    break;
                case '+':
                    // Increment
                    if (nextChar == '+'){
                        token += nextChar;
                    }
                    break;
                case '-':
                    // Decrement
                    if (nextChar == '-'){
                        token += nextChar;
                    }
                    // Pointer to Member
                    else if (nextChar == '>'){
                        token += nextChar;
                    }
                    break;
                case '*':
                    // Multiplication
                    break;
                case '/':
                    // Comment
                    if (nextChar == '*'){
                        bool end = false;
                        while (!cin.eof() && !end){
                            // Look for end of comment
                            if (c == '*' && cin.peek() == '/'){
                                token += c;
                                token += cin.get();
                                end = true;
                            }
                            c = cin.get();
                        }
                        if (!end)
                            cerr << "Comment started but not finished" << endl;
                        continue;
                    }
                    else {
                        // Division
                    }
                    break;
                case '%':
                    // Modulo
                    break;
                case '.':
                    // Structure reference
                    break;
                case '(':
                    // Open Paren
                    break;
                case ')':
                    // Close Paren
                    break;
                case '[':
                    // Open Bracket
                    break;
                case ']':
                    // Close Bracket
                    break;
                case '{':
                    // Open Brace
                    break;
                case '}':
                    // Close Brace
                    break;
                case ';':
                    // Semicolon
                    break;
                case ':':
                    // Colon
                    break;
                case ',':
                    // Comma
                    break;
                default:
                    cerr << "Invalid token" << endl;
                    c = nextChar;
                    continue;
            }
            cout << "operator:" << token << endl;
            if (token.length() > 1)
                c = cin.get();
            else 
                c = nextChar;
        }
	}
}
