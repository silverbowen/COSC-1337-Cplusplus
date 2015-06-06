/* Program by Silver Bowen
   COSC 1337 - summer 2015
   Status - Complete
   OS Ubuntu 14.04 LTS
   IDE Code::Blocks 13.12

   This program helps balance a checkbook.
   The user enters the initial balance, then any number
   of transactions. Each transaction includes a letter
   choice and a transaction amount. The program
   then prints a confirmation, a running balance,
   whether there is a service charge, and a service
   charge total. When prompted, it ends
   and gives a final total balance. */

#include <iostream>  // for cin/cout
#include <iomanip>   // for fixed/setprecision()
using namespace std; // to use std functions w/out a prefix

// declare constants
const float CHECK_FEE = .25,
          LOW_BAL_FEE = 5.00,
          NEG_BAL_FEE = 25.00;

// prototype functions
float processCheck(float, float);
float processDeposit(float, float);
float totalFee(char, float, float);
void monthEnd(float, float);

int main()
{

    // declare variables
    double balance,            // balance accumulator
           changeAmount,       // amount added/subtracted
           serviceTotal = 0;   // total of fees
    char transaction = 'Z';    // selected menu item


    // opening splash -- uncomment if wanted
//    cout << "Checkbook Balance Program\n\n";

    // get opening balance
    cout << "Enter the beginning balance: ";
    cin  >> balance;
    cout << endl;

    // show menu -- uncomment if wanted
//    cout << "Commands:\n"
//         << "C + amount - process a check\n"
//         << "D + amount - process a deposit\n"
//         << "E - end the program\n\n";

    // set precision
    cout << fixed << setprecision(2);

    // if it's not end of month, keep going
    while ((transaction != 'E') && (transaction != 'e'))
    {
        // get user choice (no prompt or new line for amount)
        cout << "Enter a transaction: ";
        cin  >> transaction;

        // if user isn't quitting, get amount
        if ((transaction != 'E') && (transaction != 'e'))
        {
            // Putting this here lets a user just type "e" to
            // quit. It also serves to clear the buffer if
            // the transaction choice turns out invalid.
            cin >> changeAmount;

            // if it's not a valid choice, do this
            if ((transaction != 'E') && (transaction != 'e')
                && (transaction != 'D') && (transaction != 'd')
                && (transaction != 'C') && (transaction != 'c'))
                cout << "You entered an invalid transaction command.\n"
                    << "Please enter C, D, or E.\n\n";

            // error check transaction amount
            if (changeAmount <= 0)
                cout << "Please enter an amount greater than zero.\n\n";

            // if it's a check, do this
            else if ((transaction == 'C') || (transaction == 'c'))
            {
                // call the check processing function
                balance = processCheck(changeAmount, balance);
                // call the fee totaling function
                serviceTotal = totalFee(transaction, balance,
                                        serviceTotal);
            }

            // if it's a deposit, do this
            else if ((transaction == 'D') || (transaction == 'd'))
            {
                // call the deposit processing function
                balance = processDeposit(changeAmount, balance);
                // call the fee totaling function
                serviceTotal = totalFee(transaction, balance,
                                        serviceTotal);
            }
        } // end 'not quitting' if
    } // end while

    //call the end of month function
    monthEnd(balance, serviceTotal);

    return 0;
}

// this function processes a check and returns the new balance
float processCheck(float changeAmount, float balance)
{
        // confirmation message
        cout << "Processing check for $"
        << changeAmount << endl;

        // get new balance
        balance -= changeAmount;

        // show balance
        cout << "Balance: $" <<
        balance << endl;

        return balance;
}

// this function processes a deposit and returns the new balance
float processDeposit(float changeAmount, float balance)
{
        // confirmation message
        cout << "Processing deposit for $"
        << changeAmount << endl;

        // get new balance
        balance += changeAmount;

        // show balance
        cout << "Balance: $" <<
        balance << endl;

        return balance;
}

// this functions adds the new fees for a processed
// check or deposit to the running total
float totalFee(char transaction, float balance,
                 float serviceTotal)
{
    // declare flag variable, static so only initialized once
    bool static lowBalFlag = false;

    // if check, do this
    if ((transaction == 'C') || (transaction == 'c'))
    {
        // show service message
        cout << "Service charge: $" << CHECK_FEE
            << " for a check\n";

        // add check fee to serviceTotal
        serviceTotal += CHECK_FEE;

        // if processing a check results in
        // a negative balance, add fee
        if (balance < 0)
        {
            cout << "Service charge: $" << NEG_BAL_FEE
            << " balance below $0.00" << endl;
            serviceTotal += NEG_BAL_FEE;
        }
    }

    // the following applies to both checks and deposits
    // if low balance, add fee ONCE PER MONTH ONLY
    if ((balance < 800) && !(lowBalFlag))
    {
        cout << "Service charge: $" << LOW_BAL_FEE
            << " balance below $800.00" << endl;
        serviceTotal += LOW_BAL_FEE;
        lowBalFlag = true;
    }

    // show total fees
    cout << "Total service charges: $" <<
         serviceTotal << "\n\n";

    return serviceTotal;
}

// this functions displays the end of month statement
void monthEnd(float balance, float serviceTotal)
{
    // process end of month
    cout << "Processing end of month\n";

    // calculate final balance
    balance -= serviceTotal;

    // show final balance
    cout << "Final balance: $"
//         << fixed << setprecision(2)
         << balance << endl;
}
