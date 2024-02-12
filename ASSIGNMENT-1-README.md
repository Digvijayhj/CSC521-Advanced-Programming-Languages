
# Invalid Comment Identification and  Comment Removal Using JavaScript and PHP

## Overview

Contains two command-line tools designed for removing comments from C program files. One is written in PHP, and the other in JavaScript. Both programs analyze the C program file for single-line and multi-line comments, report any found errors in comment usage, and create a new file with all valid comments removed.

## Status

Both the PHP and JavaScript programs are fully operational and have been tested successfully. ✅

## Installation and Execution

### PHP Program

#### Prerequisites

- PHP installed on your machine. Tested with PHP 8.3.2 but should work with any versions.

#### Running the Program

1. Open a terminal.
2. Navigate to the directory containing the `remove-comments.php` script.
3. Execute the script by running the following command, replacing `PATH_TO_YOUR_C_FILE` with the path to the C program file you wish to analyze:

```bash
php remove-comments.php PATH_TO_YOUR_C_FILE
```

### JavaScript Program

#### Prerequisites

- Node.js installed on your machine. Tested with Node.js 14.x but should be compatible with newer versions.
- WebStorm IDE or any other JavaScript IDE (optional, for development purposes).

#### Running the Program in WebStorm IDE

1. Open WebStorm IDE.
2. Open the project directory containing the `removeComments.js` script.
3. Locate the `removeComments.js` file in the Project Explorer.
4. Right-click on the file and select `Run 'removeComments.js'` to execute the script.
5. Follow the prompts in the IDE's integrated terminal to enter the file path of the C program you wish to analyze.

## Screenshots

Below are screenshots showing the successful execution of both programs:

### Screenshots

Below are screenshots showing the successful execution of both programs:

### Screenshots

Below are screenshots showing the successful execution of both programs:

#### PHP Program Execution

- **Command Line Execution:** ![PHP Program Execution](https://raw.githubusercontent.com/Digvijayhj/CSC521-Advanced-Programming-Languages/master/PHP.png)

#### JavaScript Program Execution

- **Execution Result:** ![JavaScript Program Execution](https://raw.githubusercontent.com/Digvijayhj/CSC521-Advanced-Programming-Languages/master/JS.png)

## Conclusion

These programs provide an efficient way to clean C program files by removing comments and identifying potential issues with comment usage.