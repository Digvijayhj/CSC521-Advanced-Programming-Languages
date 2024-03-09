#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ctype.h"

int lineNumber = 1; // Tracks the current line number for error reporting
char errorMessage[50] = "Invalid formatting. Verify your syntax";

int mStart; // Used to track the start of a multiline comment
typedef enum {read, write, id, literal, becomes, addOp, subOp, multOp, divOp, lparen, rparen, eof} token;

char tokenImage[100]; // Holds the image of the current token

FILE *fileSrc; // File pointer if input is from a file
char buffer[80]; // General purpose buffer (not used in this snippet)

// Sets the source of input, either a file or stdin
void setSource(FILE *src) {
    fileSrc = src;
}

// Sets a custom error message
void setError(const char* s) {
    strcpy(errorMessage, s);
}

// Retrieves the current error message
const char* getError() {
    return errorMessage;
}

// Reads the next character from the input source
int getNext() {
    char c;

    if (fileSrc == NULL)
        c = getchar(); // Reads from stdin if fileSrc is NULL
    else {
        c = fgetc(fileSrc); // Reads from file otherwise
        if (c == '\n') {
            ++lineNumber; // Increment line number on newline character
        }
    }
    return c;
}

// Returns the current line number, adjusting for reading past EOF
int getLine() {
    if(lineNumber==1) return 1;
    else return --lineNumber;
}

// The main function that scans input and returns tokens
token scan() {
    static int c = ' '; // Holds the current character, initialized to space
    int i = 0; // Index for building tokenImage
     
    // Skip whitespace
    while (isspace(c)) {
        c = getNext();
    }
    // Check for end of file
    if (c == EOF)
        return eof;
    // Handle identifiers and keywords
    if (isalpha(c)) {
        do {
            tokenImage[i++] = c;
            c = getNext();
        } while (isalpha(c) || isdigit(c) || c == '_');
        tokenImage[i] = '\0'; // Null-terminate the string
        // Return corresponding token
        if (!strcmp(tokenImage, "read")) return read;
        else if (!strcmp(tokenImage, "write")) return write;
        else return id;
    }
    // Handle numeric literals
    else if (isdigit(c)) {
        do {
            tokenImage[i++] = c;
            c = getNext();
        } while (isdigit(c));
        tokenImage[i] = '\0'; // Null-terminate the string
        return literal;
    } else switch (c) { // Handle other characters
        case ':': // Assignment operator
            if ((c = getNext()) != '=') {
                fprintf(stderr, "lexical error detected at line #%d\n", lineNumber);
                exit(1);
            } else {
                c = getNext();
                return becomes;
            }
        case '+': c = getNext(); return addOp;
        case '-': c = getNext(); return subOp;
        case '*': c = getNext(); return multOp;
        case '/': // Division operator or comment
            c = getNext();
            if (c == '/') { // Single line comment
                do {
                    c = getNext();
                }while(c != '\n');
                c = getNext();
                return scan(); // Recursively call scan to handle next token
            } else if (c == '*') { // Multi-line comment
                mStart = lineNumber; // Record start line of the comment
                do {
                    c = getNext();
                    if(c == '*') {
                        if ((c = getNext()) == '/') {
                            c = getNext();
                            return scan(); // Recursively call scan to handle next token
                        }
                    }
                }while(c != EOF);
                printf("lexical error:Invalid initiation of a multiline comment at line. #%d\n", mStart);
                exit(1);
            } else {
                return divOp; // Division operator
            }
        case '(': c = getNext(); return lparen;
        case ')': c = getNext(); return rparen;
        default:
            printf("lexical error detected at line #%d\n", lineNumber);
            exit(1);
    }
}
