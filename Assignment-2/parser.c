/*
 * Table-Driven Parser for 'Calculator'
 *
 * @author: Jateen Joharapurkar
 * @author: Ashwini Sudheer Kumar
 * @author: Digvijay Hethur Jagadeesha
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    read, write, id, literal, becomes,
    addOp, subOp, multOp, divOp, lparen, rparen, eof
} token;

char *names[] = {"read", "write", "id", "literal", "becomes",
                "add", "sub", "mult", "div", "lparen", "rparen", "eof"};

static token inputToken;

// Symbols in the language
typedef enum {
    program, stmt_list, stmt, expr, term_tail, term,
    factor, factor_tail, mult_op, add_op,
    $$, eps, identifier, assignment, input, output, plus,
    minus, star, slash, lpar, rpar, number
} symbol;

// Symbol Names
char *symbolNames[] = {"program", "stmt_list", "stmt", "expr",
                     "term_tail", "term", "factor", "factor_tail",
                     "mult_op", "add_op", "$$", "epsilon", "id",
                     ":=", "read", "write", "+", "-", "*", "/",
                     "(", ")", "number"};
// Terminals 
symbol terminals[] = {slash, star, minus, plus,
                      number, identifier, lpar, rpar, eps,
                      assignment, input, output, $$};
// Non-terminals
symbol nonTerminals[] = {program, stmt_list, stmt,
                         expr, term_tail, term, factor,
                         factor_tail, add_op, mult_op};

static symbol expSymbol;
static bool done;

struct table_item
{
    int action;
    symbol production[4];
};

// Parse table
#define EMPTY {1, }
#define EPSILON {0, {eps}}
#define NON_EMPTY(action) {0, action}

// Define actions for easier readability
#define ACTION_PROGRAM {stmt_list, $$}
#define ACTION_STMT_LIST {stmt, stmt_list}
#define ACTION_STMT_ASSIGNMENT {identifier, assignment, expr}
#define ACTION_STMT_INPUT {input, identifier}
#define ACTION_STMT_OUTPUT {output, expr}
#define ACTION_EXPR {term, term_tail}
#define ACTION_TERM {factor, factor_tail}
#define ACTION_TERM_TAIL_ADD {add_op, term, term_tail}
#define ACTION_FACTOR_TAIL_MULT {mult_op, factor, factor_tail}
#define ACTION_FACTOR_IDENTIFIER {identifier}
#define ACTION_FACTOR_NUMBER {number}
#define ACTION_FACTOR_EXPRESSION {lpar, expr, rpar}
#define ACTION_ADD_OP_PLUS {plus}
#define ACTION_ADD_OP_MINUS {minus}
#define ACTION_MULT_OP_STAR {star}
#define ACTION_MULT_OP_SLASH {slash}

// Macro for rows in the parsing table
#define ROW_PROGRAM NON_EMPTY(ACTION_PROGRAM), EMPTY, NON_EMPTY(ACTION_PROGRAM), NON_EMPTY(ACTION_PROGRAM), EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, NON_EMPTY(ACTION_PROGRAM)
#define ROW_STMT_LIST NON_EMPTY(ACTION_STMT_LIST), EMPTY, NON_EMPTY(ACTION_STMT_LIST), NON_EMPTY(ACTION_STMT_LIST), EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EPSILON
#define ROW_STMT NON_EMPTY(ACTION_STMT_ASSIGNMENT), EMPTY, NON_EMPTY(ACTION_STMT_INPUT), NON_EMPTY(ACTION_STMT_OUTPUT), EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY
#define ROW_EXPR NON_EMPTY(ACTION_EXPR), NON_EMPTY(ACTION_EXPR), EMPTY, EMPTY, EMPTY, NON_EMPTY(ACTION_EXPR), EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY
#define ROW_TERM_TAIL EPSILON, EMPTY, EPSILON, EPSILON, EMPTY, EMPTY, EPSILON, NON_EMPTY(ACTION_TERM_TAIL_ADD), NON_EMPTY(ACTION_TERM_TAIL_ADD), EMPTY, EMPTY, EPSILON
#define ROW_TERM NON_EMPTY(ACTION_TERM), NON_EMPTY(ACTION_TERM), EMPTY, EMPTY, EMPTY, NON_EMPTY(ACTION_TERM), EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY
#define ROW_FACTOR_TAIL EPSILON, EMPTY, EPSILON, EPSILON, EMPTY, EMPTY, EPSILON, EPSILON, EPSILON, NON_EMPTY(ACTION_FACTOR_TAIL_MULT), NON_EMPTY(ACTION_FACTOR_TAIL_MULT), EPSILON
#define ROW_FACTOR NON_EMPTY(ACTION_FACTOR_IDENTIFIER), NON_EMPTY(ACTION_FACTOR_NUMBER), EMPTY, EMPTY, EMPTY, NON_EMPTY(ACTION_FACTOR_EXPRESSION), EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY
#define ROW_ADD_OP EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, NON_EMPTY(ACTION_ADD_OP_PLUS), NON_EMPTY(ACTION_ADD_OP_MINUS), EMPTY, EMPTY, EMPTY
#define ROW_MULT_OP EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, NON_EMPTY(ACTION_MULT_OP_STAR), NON_EMPTY(ACTION_MULT_OP_SLASH), EMPTY

// Parsing table structure using macros
struct table_item parseTable[sizeof(nonTerminals) / sizeof(*nonTerminals)][sizeof(names)/sizeof(*names)] = {
        {ROW_PROGRAM},    // program
        {ROW_STMT_LIST},  // stmt_list
        {ROW_STMT},       // stmt
        {ROW_EXPR},       // expr
        {ROW_TERM_TAIL},  // term_tail
        {ROW_TERM},       // term
        {ROW_FACTOR_TAIL},// factor_tail
        {ROW_FACTOR},     // factor
        {ROW_ADD_OP},     // add_op
        {ROW_MULT_OP},    // mult_op
};

void matchSuccess();

void matchFail();

// For the row index of the parse table
int getNonTerminalIndex(symbol s) {
    if (s == program) {
        return 0;
    } else if (s == stmt_list) {
        return 1;
    } else if (s == stmt) {
        return 2;
    } else if (s == expr) {
        return 3;
    } else if (s == term_tail) {
        return 4;
    } else if (s == term) {
        return 5;
    } else if (s == factor_tail) {
        return 6;
    } else if (s == factor) {
        return 7;
    } else if (s == add_op) {
        return 8;
    } else if (s == mult_op) {
        return 9;
    } else {
        return -1;
    }
}

// get column index into the parse table
int tokenInd(token t) {
    if (t == id) {
        return 0;
    } else if (t == literal) {
        return 1;
    } else if (t == read) {
        return 2;
    } else if (t == write) {
        return 3;
    } else if (t == becomes) {
        return 4;
    } else if (t == lparen) {
        return 5;
    } else if (t == rparen) {
        return 6;
    } else if (t == addOp) {
        return 7;
    } else if (t == subOp) {
        return 8;
    } else if (t == multOp) {
        return 9;
    } else if (t == divOp) {
        return 10;
    } else if (t == eof) {
        return 11;
    } else {
        return -1;
    }
}

void error(const char* msg) {
    printf("syntax error - %s\n\n", msg);
    exit(EXIT_FAILURE);
}

// Parse Stack
symbol parseStack[128];
int topOfStack = 0;

int isTerminal(symbol s) {
    for (int i = 0; i < (sizeof(terminals) / sizeof(*terminals)); i++)
    {
        if (terminals[i] == s)
        {
            return 1;  // Found the symbol in terminals
        }
    }

    return 0; // Symbol not found in terminals
}

void match() {
    // Print the current token from the input and the top symbol from the parse stack
    printf("Current token in input: %s\t|\tCurrent top of the stack: %s\n", names[inputToken], symbolNames[expSymbol]);

    // Check if the expected symbol (on the stack) is an epsilon production
    if (expSymbol == eps) {
        // An epsilon production, reduce the stack without consuming an input token
        topOfStack--;
        return;
    } else if (inputToken == read) {
        if (expSymbol == input) {
            matchSuccess();
        } else {
            matchFail();
        }
    } else if (inputToken == write) {
        if (expSymbol == output) {
            matchSuccess();
        } else {
            matchFail();
        }
    } else if (inputToken == id) {
        if (expSymbol == identifier) {
            matchSuccess();
        } else {
            matchFail();
        }
    } else if (inputToken == literal) {
        if (expSymbol == number) {
            matchSuccess();
        } else {
            matchFail();
        }
    } else if (inputToken == becomes) {
        if (expSymbol == assignment) {
            matchSuccess();
        } else {
            matchFail();
        }
    } else if (inputToken == addOp) {
        if (expSymbol == plus) {
            matchSuccess();
        } else {
            matchFail();
        }
    } else if (inputToken == subOp) {
        if (expSymbol == minus) {
            matchSuccess();
        } else {
            matchFail();
        }
    } else if (inputToken == multOp) {
        if (expSymbol == star) {
            matchSuccess();
        } else {
            matchFail();
        }
    } else if (inputToken == divOp) {
        if (expSymbol == slash) {
            matchSuccess();
        } else {
            matchFail();
        }
    } else if (inputToken == lparen) {
        if (expSymbol == lpar) {
            matchSuccess();
        } else {
            matchFail();
        }
    } else if (inputToken == rparen) {
        if (expSymbol == rpar) {
            matchSuccess();
        } else {
            matchFail();
        }
    } else if (inputToken == eof) {
        if (expSymbol == $$) {
            matchSuccess();
        } else {
            matchFail();
        }
    } else {
        // Handles the cases where the input token is unrecognized
        error("Error: Unrecognized input token.");
    }
}

void matchSuccess() {
    printf("\tMATCH\n");
    topOfStack--;
    inputToken = scan();
}

void matchFail() {
    error("Match Fail");
}


int main(int argc, char *argv[])
{
    FILE *src;
    char fileName[32];

    int nonTerminalIndex;
    int tokenIndex;
    struct table_item item;

    // program name was passed in as a command-line argument
    if (argc > 1)
    {
        strcat(fileName, argv[1]);
        printf("Initiating file opening: %s\n\n\n", fileName);
        src = fopen(fileName, "r");

        // failed to open the file
        if (src == NULL)
        {
            perror("An error occurred while attempting to open the file.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
        src = NULL;

    setSource(src);

    // initialize parse stack
    parseStack[topOfStack] = program;
    inputToken = scan();

    do
    {
        expSymbol = parseStack[topOfStack];
        printf("\nPresent anticipated symbol: %s\n", symbolNames[expSymbol]);
        printf("Current input token: %s\n\n", names[inputToken]);

        // Determine if the symbol at the top of the stack is a terminal
        if (isTerminal(expSymbol))
        {
            // Process matching terminal symbols
            match();

            // Check for end of input
            if (expSymbol == $$) // Assuming $$ represents end of input symbol
            {
                printf("Parsing completed successfully, no lexical or syntactical errors detected.");
                done = true;
            }
        }
        else // If symbol is non-terminal
        {
            // Retrieve indexes for parsing table
            nonTerminalIndex = getNonTerminalIndex(expSymbol);
            tokenIndex = tokenInd(inputToken);

            if (nonTerminalIndex >= 0 && tokenIndex >= 0)
            {
                // check the parse table
                item = parseTable[nonTerminalIndex][tokenIndex];

                if (item.action == 1)
                {
                    // check the parse table for syntax error found
                    error("Syntax error: Incompatible input token and top of the stack.\n");
                }
                else
                {
                    // Push production to the stack in the reverse order
                    for (int i = 3; i >= 0; i--)
                    {
                        if (item.production[i] != NULL)
                        {
                            // Add symbol to the parsing stack
                            printf("\tAdding to the parse stack.: %s\n", symbolNames[item.production[i]]);
                            parseStack[topOfStack] = item.production[i];
                            if (i != 0)
                                topOfStack++;
                        }
                    }
                }
                // Print current status of the parse stack
                printf("parse stack: \n");
                for (int i = topOfStack; i >= 0; i--)
                {
                    printf("\t(%d): %s\n", i, symbolNames[parseStack[i]]);
                }
                printf("\n\n");
            }
        }
    } while (!done);

    // Close the source file
    if (src != NULL)
        fclose(src);

    return (0);
}
