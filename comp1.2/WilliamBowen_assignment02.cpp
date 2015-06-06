/* Program by Silver Bowen
   COSC 1337 - summer 2015
   Status - Complete

   This program helps balance a checkbook.
   The user  enters the initial balance,
   then any number of transactions. Each
   transaction is chosen from a menu. The program
   then prints a confirmation, a running balance,
   whether there is a service charge, and a service
   charge total. When prompted, it ends
   and gives a final total balance. */

#include <iostream>  // for cin/cout
#include <iomanip>   // for fixed/setprecision()
using namespace std; // to use std functions w/out a prefix

// declare constants
const float checkFee = .25;

int main()
{

    // declare variables
    double balance,            // balance accumulator
           changeAmount,       // amount added/subtracted
           serviceTotal = 0;   // total of fees
    char transaction = 'Z';    // selected menu item

    // opening splash tells user what program is for
    cout << "Checkbook Balance Program\n\n";

    // get opening balance
    cout << "Enter the beginning balance: ";
    cin  >> balance;
    cout << endl;

    // show menu
    cout << "Commands:\n"
         << "C - process a check\n"
         << "D - process a deposit\n"
         << "E - end the program\n\n";

    do
    {
        // get user choice
        cout << "Enter transaction type: ";
        cin  >> transaction;

        // error checking starts here
        if ((transaction == 'C') ||
            (transaction == 'c'))   // if it's a check, do this
        {
            // get transaction amount
            cout << "Enter transaction amount: ";
            cin  >> changeAmount;

            // error check transaction amount
            if (changeAmount <= 0)
                cout << "You must enter an amount greater than zero!\n";

            else
            {
                // confirmation message
                cout << "Processing check for $"
                     << fixed << setprecision(2)
                     << changeAmount << endl;

                // get new balance
                balance -= changeAmount;

                // show balance
                cout << "Balance: $"
                     << fixed << setprecision(2)
                     << balance << endl;

                // show service message
                cout << "Service charge: $.25 for a check\n";

                // compute charge
                serviceTotal += checkFee;

                // show total fees
                cout << "Total service charges: $"
                     << fixed << setprecision(2)
                     << serviceTotal << "\n\n";
            }
        }

        else if ((transaction == 'D') ||
                 (transaction == 'd'))    // if it's a deposit, do this
        {
            // get transaction amount
            cout << "Enter transaction amount: ";
            cin  >> changeAmount;

            // error check transaction amount
            if (changeAmount <= 0)
                cout << "Please enter an amount greater than zero.\n\n";

            else
            {
                // confirmation message
                cout << "Processing deposit for $"
                     << fixed << setprecision(2)
                     << changeAmount << endl;

                // get new balance
                balance += changeAmount;

                // show balance
                cout << "Balance: $"
                     << fixed << setprecision(2)
                     << balance << endl;

                // show total fees
                cout << "Total service charges: $"
                     << fixed << setprecision(2)
                     << serviceTotal << "\n\n";
            }
        }

        // if transaction error
        else if ((transaction != 'E') &&
                 (transaction != 'e'))   // if it's not a valid choice, do this
            cout << "You entered an invalid choice. Please enter C, D, or E.\n\n";
    }
    while ((transaction != 'E') &&
           (transaction != 'e'));   // if it's not end time, keep going

    // process end of month
    cout << "Processing end of month\n";

    // calculate final balance
    balance -= serviceTotal;

    // show final balance
    cout << "Final balance: $"
         << fixed << setprecision(2)
         << balance << endl;

    return 0;
}
