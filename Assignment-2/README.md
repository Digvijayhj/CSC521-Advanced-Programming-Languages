# Project Title: Calculator Language Parser and Scanner

## Description
This project contains a table-driven parser (`parser.c`) and a lexical scanner (`scanner.c`) for a simple calculator language. The parser uses a predictive parsing method, and the scanner tokenizes the input into meaningful symbols that the parser can understand.

## Installation
To run the programs, follow these steps:
1. Compile the source code using a C compiler, e.g., GCC: `gcc -o parser parser.c` and `gcc -o scanner scanner.c`
2. Run the parser and scanner with: `./parser <input_file>` and `./scanner <input_file>`.

## Test Programs
Our programs have been tested with five different test cases, covering various aspects of the calculator language syntax and semantics.

a) Program Correctness:
   - Both `parser.c` and `scanner.c` run correctly without any errors.
   - The parser successfully recognizes and handles all the grammatical structures of the calculator language.
   - The scanner accurately tokenizes different elements of the language, such as identifiers, literals, and operators.

b) Evidence of Testing:
   - Below are the screenshots from our tests that support our claim of the program's correctness.
   - **Add your screenshots here:**
     - ![Program 1 output](https://github.com/Digvijayhj/CSC521-Advanced-Programming-Languages/blob/master/Assignment-2/prog1%20output.jpeg?raw=true)
     - ![Program 2 output](https://github.com/Digvijayhj/CSC521-Advanced-Programming-Languages/blob/master/Assignment-2/prog2%20output.jpeg?raw=true)
     - ![Program 3 output](https://github.com/Digvijayhj/CSC521-Advanced-Programming-Languages/blob/master/Assignment-2/prog3%20output.jpeg?raw=true)
     - ![Program 4 output](https://github.com/Digvijayhj/CSC521-Advanced-Programming-Languages/blob/master/Assignment-2/prog4%20output.jpeg?raw=true)
     - ![Program 5 output](https://github.com/Digvijayhj/CSC521-Advanced-Programming-Languages/blob/master/Assignment-2/prog5%20output.jpeg?raw=true)

## Some known issues

- Comments handling: The scanner’s current implementation does not handle nested comments correctly. While most single-line and multi-line comments are processed appropriately, nested comments can lead to incorrect parsing or unrecognized token errors.

- Unicode support: Both the scanner and parser currently lack proper support for Unicode characters. This limits the use of non-ASCII characters in identifiers, literals, or comments within the calculator language.

## Contributions

### Digvijay
**Development Contribution**: Concentrated on optimizing the scanner's performance in `scanner.c`, ensuring it operated efficiently and accurately. This included refining the tokenization process and improving the scanner's ability to handle different types of input, such as varying identifiers and numerical values.

**Challenges and Solutions**:
- Encountered performance issues when the scanner processed large files or complex nested structures. Addressed these by optimizing the character reading loop and implementing a more efficient character buffer.
- Dealt with difficulties in correctly tokenizing similar-looking operators (e.g., ‘:’ vs. ‘:=’). Resolved by enhancing the finite state machine within the scanner to better differentiate between single and multi-character tokens.

### Jateen
**Development Contribution**: Led the development of the `parser.c` logic, focusing on implementing the predictive parsing algorithm. Ensured the parser could handle all constructs of the calculator language according to the provided grammar. Extended the parsing capabilities to include error recovery strategies, enabling the parser to continue after encountering non-critical syntax errors.

**Challenges and Solutions**:
- One of the main challenges was designing a comprehensive yet flexible parse table that accommodated all grammar rules without being overly complex. Overcame this by breaking down the grammar into smaller, more manageable components and testing each thoroughly before integration.
- Struggled with implementing an effective error recovery mechanism that wouldn’t halt the parser on minor errors. Solved this by introducing a 'synchronization' concept, allowing the parser to skip tokens until a pre-defined 'safe point' (like the end of a statement) was reached.


### Ashwini
**Development Contribution**: Focused on enhancing the error reporting mechanism within `scanner.c`. This involved refining the logic for identifying and distinguishing different types of lexical errors, such as misformatted literals and unrecognized symbols. 

**Challenges and Solutions**:
- Faced a significant challenge with identifying the end of multi-line comments and distinguishing them from nested comments. Resolved by implementing a counter for open comment tags and ensuring they matched close comment tags before considering the comment closed.
- Encountered issues with line numbers not accurately updating, especially after encountering comments or strings spanning multiple lines. Solved by refining the newline character detection logic and ensuring line counts updated correctly regardless of source.





