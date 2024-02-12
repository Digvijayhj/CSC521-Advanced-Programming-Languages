<?php

// Check if the file path is provided as a command-line argument.
if ($argc < 2) {
    echo "Please enter the file path of the C program as an argument.\n";
    exit(1);
}

$filePath = $argv[1];

// Main function to analyze the C program.
function analyzeCProgram($filePath) {
    try {
        // Read the content of the specified file.
        $data = file_get_contents($filePath);
        if ($data === false) {
            throw new Exception("Failed to read file: " . $filePath);
        }

        // Find invalid comments in the C program.
        $errors = findInvalidComments($data);

        $inMultiLineComment = false;
        $multiLineCommentStartLine = 0;
        $lines = explode("\n", $data);

        foreach ($lines as $index => $line) {
            // Check for the start of a multi-line comment.
            if (strpos($line, '/*') !== false) {
                if ($inMultiLineComment) {
                    $errors[] = "Nested multi-line comment starting at line " . ($index + 1);
                }
                $inMultiLineComment = true;
                $multiLineCommentStartLine = $index + 1;
            }
            // Check for the end of a multi-line comment.
            if (strpos($line, '*/') !== false) {
                if (!$inMultiLineComment) {
                    $errors[] = "Orphan end of multi-line comment at line " . ($index + 1);
                }
                $inMultiLineComment = false;
            }
        }

        // Check if a multi-line comment was left unclosed.
        if ($inMultiLineComment) {
            $errors[] = "Unclosed multi-line comment starting at line $multiLineCommentStartLine";
        }

        // Log all errors found in the analysis.
        foreach ($errors as $error) {
            echo $error . "\n";
        }

        // Remove all comments from the file content.
        $newData = preg_replace('/\/\/.*|\/\*[\s\S]*?\*\//m', "", $data);
        // Generate a new file path with a modified extension.
        $newFilePath = str_replace('.c', '_no_comments.c', $filePath);
        // Save the modified file content without comments.
        if (file_put_contents($newFilePath, $newData) === false) {
            throw new Exception("Failed to write file: " . $newFilePath);
        }
        echo "File saved without comments: $newFilePath\n";
    } catch (Exception $e) {
        echo "Error processing file: " . $e->getMessage() . "\n";
    }
}

// The enhanced function to find invalid single-line comments.
function findInvalidComments($code) {
    $errors = [];
    $lines = explode("\n", $code);
    $inMultiLineComment = false;

    foreach ($lines as $index => $line) {
        $trimmedLine = trim($line);

        // Detect the start and end of multi-line comments.
        if (strpos($trimmedLine, '/*') === 0) {
            $inMultiLineComment = true;
        }
        if (strpos($trimmedLine, '*/') !== false && $inMultiLineComment) {
            $inMultiLineComment = false;
            continue; // Skip further checks for this line.
        }

        // Check for invalid single-line comments outside of multi-line comments.
        if (!$inMultiLineComment) {
            if (preg_match('/^\/\s+(?![*\/])/', $trimmedLine)) {
                $errors[] = "Invalid single-line comment at line " . ($index + 1) . ": " . $line;
            } else if (preg_match('/^\/(?!\s+[*\/])/', $trimmedLine)) {
                $errors[] = "Invalid single-line comment at line " . ($index + 1) . ": " . $line;
            }
        }
    }

    return $errors;
}

// Execute the main function with the provided file path.
analyzeCProgram($filePath);

