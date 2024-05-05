
# ArrayMemoryLayout

## Overview
This Java program explores the impact of memory layouts on page faults when accessing two-dimensional arrays in a simulated paged memory system. The project demonstrates the differences in page faults between row-major and column-major memory layouts using the Least Recently Used (LRU) cache replacement algorithm.

## How to Compile and Run
1. **Compilation**: To compile the program, navigate to the directory containing `ArrayMemoryLayout.java` and run the following command:
   ```bash
   javac ArrayMemoryLayout.java
   ```
2. **Execution**: To run the compiled program, use:
   ```bash
   java ArrayMemoryLayout
   ```
   Follow the on-screen prompts to enter the number of frames in physical memory.

## Program Functionality
- **Inputs**: User is prompted to enter the number of frames in physical memory.
- **Outputs**: The program calculates and displays the number of page faults for both row-major and column-major order array initializations based on the user input.

## Contributions
- **Digvijay**: Implemented the LRU cache mechanism and integrated it into the main program.
- **Jateen**: Handled user input and output formatting, ensuring clear and understandable interactions.
- **Ashwini**: Conducted initial tests and debugged the program to ensure correct calculation of page faults.

## Program Correctness
The program has been thoroughly tested and works correctly under various conditions. It handles different inputs for the number of frames, including boundary cases like zero or negative numbers. The page fault calculations match expected theoretical outcomes as discussed in class.

## Detailed Analysis of Results
- **Row-major Order**: This layout minimizes page faults effectively. As elements are stored consecutively, accessing an element in the same row likely hits the same or a recently used page, thus exploiting spatial locality.
- **Column-major Order**: This approach incurs significantly more page faults. Since accessing elements column by column jumps across entire rows, each access is likely to require a new page, especially with limited frames, leading to frequent cache misses.

## Screenshots
Please refer to the attached screenshots demonstrating the program execution for various inputs:
1. Screenshot1.png - Execution with 3 frames.
2. Screenshot2.png - Execution with 5 frames.
3. Screenshot3.png - Execution with 10 frames.
4. Screenshot4.png - Execution with 20 frames.
5. Screenshot5.png - Error handling for invalid input.
