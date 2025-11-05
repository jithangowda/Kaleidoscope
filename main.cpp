/*Compiler for custom language
 *Language structure as below

 # Compute the x'th finonacci series
 def fib(x)
    if x < 3 then
        1
    else fib(x-1) + fib(x-2)

# This expression will compute the 40th number.
fib(40)

*/


#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>

//---------LEXER------------------------------------------------------//
//-------------------------------------------------------------------//

enum Token {
    tok_eof = -1,

    // commands
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5,
};

static std::string IdentifierString;
static double NumberValue;

// gettok function to get the next token
static int gettok() {
    static int lastChar = ' ';

    // skip white spaces
    while (isspace(lastChar)) {
        lastChar = getchar();
    }

    // Identifier [a-zA-Z][a-zA-Z0-9]*
    if (isalpha(lastChar)) {
        IdentifierString = lastChar;
        while (isalnum(lastChar = getchar())) {
            IdentifierString += lastChar;
        }

        if (IdentifierString == "def") { return tok_def; }
        if (IdentifierString == "extern") { return tok_extern; }

        return tok_identifier;
    }

    /*
    // Number [0-9]+
    if (isdigit(lastChar) || lastChar == '.') {
        std::string numStr;

        do {
            numStr += lastChar;
            lastChar = getchar();
        } while (isdigit(lastChar) || lastChar == '.');

        NumberValue = strtod(numStr.c_str(), nullptr);

        return tok_number;

    }
    */

    // Number [0-9]+ or [0-9]+.[0-9]+   my version
    if (isdigit(lastChar) || lastChar == '.') {
        std::string numStr;
        int dotCount{0};

        do {
            if (lastChar == '.') {
                dotCount++;
                if (dotCount > 1) {
                    break;
                }
            }
            numStr += lastChar;
            lastChar = getchar();
        } while (isdigit(lastChar) || lastChar == '.');

        NumberValue = strtod(numStr.c_str(), nullptr);
        return tok_number;
    }

    // Ignore comments starting with #
    if (lastChar == '#') {
        do {
            lastChar = getchar();
        } while (lastChar != EOF && lastChar == '\n' && lastChar == '\r');

        if (lastChar != EOF) { return gettok(); }
    }

    // return EOF
    if (lastChar == EOF) { return tok_eof; }

    // return the char if not any of the above
    int thisChar = lastChar;
    lastChar = getchar();
    return thisChar;
}


//---------ABSTRACT SYNTAX TREE---------------------------------------//
//-------------------------------------------------------------------//