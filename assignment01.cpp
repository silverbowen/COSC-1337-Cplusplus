/* Program by Silver Bowen
   COSC 1337 - summer 2015
   Status - Complete

   This program asks the user for two
   integers, then performs math operations
   on them and displays the results. */

// include iostream for input
// and iomanip for setw()
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    // Ask user for input.
    cout << "Enter two integers, separated by a space: ";

    // Variables declared.
    int num1, // stores 1st user input number
        num2; // stores 2nd user input number

    // Variables initialized via cin.
    cin >> num1 >> num2;

    // Spacer for tidiness.
    cout << endl;

    /* The rest of the program prints the
       various manipulations. I've tried to keep
       the formatting exactly as per the example. */

    // Sum - simply adds the numbers.
    cout << left << setw(10) << "Sum";
    cout <<"is " << (num1 + num2) << endl;
    cout << endl;

    // Product - simply multiplies them.
    cout << left << setw(10) << "Product";
    cout <<"is " << (num1 * num2) << endl;
    cout << endl;

    // Average - adds the numbers, then divides by two.
    // These are ints == any decimal places are truncated.
    cout << left << setw(10) << "Average";
    cout <<"is " << ((num1 + num2) / 2) << endl;
    cout << endl;

    // Quotient - divides the 2nd number by the 1st.
    // These are ints == any decimal places are truncated.
    cout << left << setw(10) << "Quotient";
    cout <<"is " << (num1 / num2) << endl;
    cout << endl;

    // Modulus - gets the remainder of the 1st number
    // divided by the 2nd number.
    cout << left << setw(10) << "Modulus";
    cout <<"is " << (num1 % num2) << endl;
    cout << endl;

    return 0;
}
