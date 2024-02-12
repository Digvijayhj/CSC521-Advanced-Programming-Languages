/*
    Program to find Square Root Of s number
 */

#include <stdio.h>

double sqrtRecursive(double n, double guess) {
    if ((guess * guess - n) < 0.00001) { // Tolerance for approximate square root
        return guess;
    } else {
        return sqrtRecursive(n, (n / guess + guess) / 2); // Refine the guess
    }
}

/ *
  This is invalid single or multiline comment

 */

int main() {
    double number;
    /
    printf("Enter a non-negative number: ");
    scanf("%lf", &number);
    scanf("%lf", &number); */

    /* hi There/  */

    if (number < 0) {
        printf("Invalid input: Please enter a non-negative number.\n");
    } else {
        double squareRoot = sqrtRecursive(number, 1.0); /*Initial guess of 1.0*/
        printf("The square root of %.2lf is approximately %.2lf\n", number, squareRoot);
    }
/*
  This is invalid multiline comment

 * /
    return 0;
}

/*
 *  I'm Valid
 */
*/

void function()
/*{

}

