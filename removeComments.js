const fs = require('fs');
const readline = require('readline');

// Create a readline interface for input/output in the console.
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

// Prompt the user to enter the file path of a C program.
rl.question('Please enter the file path of the C program: ', function(filePath) {
    analyzeCProgram(filePath).then(() => rl.close());
});

async function analyzeCProgram(filePath) {
    try {
        // Read the content of the specified file asynchronously.
        const data = await fs.promises.readFile(filePath, 'utf8');

        // Find invalid comments in the C program.
        const errors = findInvalidComments(data);

        let inMultiLineComment = false;
        let multiLineCommentStartLine = 0;

        const lines = data.split('\n');
        lines.forEach((line, index) => {
            // Check for the start of a multi-line comment.
            if (line.includes('/*')) {
                if (inMultiLineComment) {
                    errors.push(`Nested multi-line comment starting at line ${index + 1}`);
                }
                inMultiLineComment = true;
                multiLineCommentStartLine = index + 1;
            }
            // Check for the end of a multi-line comment.
            if (line.includes('*/')) {
                if (!inMultiLineComment) {
                    errors.push(`Orphan end of multi-line comment at line ${index + 1}`);
                }
                inMultiLineComment = false;
            }
        });

        // Check if a multi-line comment was left unclosed.
        if (inMultiLineComment) {
            errors.push(`Unclosed multi-line comment starting at line ${multiLineCommentStartLine}`);
        }

        // Log all errors found in the analysis.
        errors.forEach(error => console.log(error));

        // Remove all comments from the file content.
        const newData = data.replace(/\/\/.*|\/\*[\s\S]*?\*\//gm, "");
        // Generate a new file path with a modified extension.
        const newFilePath = filePath.replace('.c', '_no_comments.c');
        // Save the modified file content without comments.
        await fs.promises.writeFile(newFilePath, newData); // Corrected variable name here
        console.log(`File saved without comments: ${newFilePath}`);
    } catch (err) {
        console.error("Error processing file:", err);
    }
}

function findInvalidComments(code) {
    const errors = [];
    const lines = code.split('\n');
    let inMultiLineComment = false;

    lines.forEach((line, index) => {
        const trimmedLine = line.trim();

        // Detect the start and end of multi-line comments.
        if (trimmedLine.startsWith('/*')) {
            inMultiLineComment = true;
        }
        if (trimmedLine.indexOf('*/') !== -1 && inMultiLineComment) {
            inMultiLineComment = false;
            return; // Skip further checks for this line.
        }

        // Check for invalid single-line comments outside of multi-line comments.
        if (!inMultiLineComment) {
            // Regex explanation:
            // /^\/\s+(?![*\/])/ checks for a single forward slash followed by whitespace, not followed by another slash or asterisk.
            if (/^\/\s+(?![*\/])/.test(trimmedLine)) {
                errors.push(`Invalid single-line comment at line ${index + 1}: ${line}`);
            }
            // /^\/(?!\s+[*\/])/ checks for a forward slash not followed by whitespace leading to another slash or asterisk.
            else if (/^\/(?!\s+[*\/])/.test(trimmedLine)) {
                errors.push(`Invalid single-line comment at line ${index + 1}: ${line}`);
            }
        }
    });

    return errors;
}