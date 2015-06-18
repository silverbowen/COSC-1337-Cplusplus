/* Program by Silver Bowen
   COSC 1337 - summer 2015
   Status - Complete
   OS Ubuntu 14.04 LTS
   IDE Code::Blocks 13.12

   This program includes a struct called employee that stores
   the employee's particulars. It uses an array of structs to
   hold the data for 4 employees. There are 2 Constructors, one
   accepts 4 arguments and the other accepts none. Both set the
   defaults to 0/null. A Timesheet Vector holds hours worked for
   each employee. The program includes validation for new.
   values inserted into the structs. Main gets input, calculates
   gross pay, tax, net pat, and total gross and net, then prints
   a report detailing the payroll for the week. */

#include <iostream>  // for cin/cout
#include <iomanip>   // for setw()
#include <string>    // for strings
#include <cctype>    // for toupper
#include <vector>    // for vectors
using namespace std; // to use std functions w/out a prefix

struct Employee
{
    int   id,     // between 1-4
        type;     // 0 or 1
    float  rate;  // must be positive
    string name;  // up to 20 chars, includes spaces

    Employee()         // constructor 1
    {
        id = type = 0; // variables set to defaults
        rate = 0.0;
        name =  "";
    }  // end constructor 1

    Employee(int i, int t,
             float r, string n ) // constructor 2
    {
        id   = i;   // variables set to arguments
        type = t;
        rate = r;
        name = n;
    }  // end constructor 2
}; // end struct definition


/* main will do IO, generate conglomerate data,
   do validation, and print out our report. */
int main()
{
    // define constants
    const int   TOTAL_EMPS = 4;
    const float TAX_RATE = .15;

    // define variables
    float   grossPay, // hours * rate
                 tax, // grossPay * TAX_RATE
              netPay; // grossPay - tax

    // define and initialize accumulators
    float totalGross = 0.0, // grossPay total for all employees
            totalNet = 0.0; // netPay total for all employees

    // define vector - default values 0.0
    /* (no good reason to make this a vector
        except for the practice.) */
    vector<float>timeSheet(TOTAL_EMPS, 0.0); // holds hrs worked

    // prototypes
    void prompt(int);  // display prompts

    void getID(int);   // get Employee input
    void getName(int);
    void getRate(int);
    void getType(int);

    void getTime(int); // get timeSheet input

    bool validID(int);      // validate Employee input
    bool validName(string);
    bool validRate(float);
    bool validType(int);

    bool validTime(float);  // validate timeSheet input

    // instantiate an array of structs
    Employee employee[TOTAL_EMPS];

    // for loop for input
    for (int n = 0; n < TOTAL_EMPS; n++)
    {
        prompt(n);
        getID(n);
        getName(n);
        getRate(n);
        getType(n);
        getTime(n);
    } // end for loop

    // prompt for input 2
    cout << "n\Enter timecard information for each employee:\n\n"

    // for loop for input 2
    for (int n = 0; n < TOTAL_EMPS; n++)
        { getTime(n); } // end for loop

   // prompt for report
   cout << "\nPayroll Report\n\n"
        << setw(4) << left << "ID"
        << setw(20) << "Name"
        << setw(8) << right << "Gross Pay"
        << "Tax" << "Net Pay\n";

    // set precision
    cout << fixed << setprecision(2);

    // print the report
    for (int n = 0; n < TO;TAL_EMPS; n++)
        {
            grossPay = timeSheet[n] * employee[n].rate;
            tax = grossPay * TAX_RATE;
            netPay = grossPay - tax;
            totalGross += grossPay;
            totalNet += netPay;

            cout << setw(4) << left << employee[n].id
                 << setw(20) << employee[n].name
                 << setw(8) << right << grossPay
                 << tax << netPay << endl;
        } // end for loop

    // print the totals
    cout << "Total Gross Pay $" << totalGross << endl;
    cout << "Total Net Pay   $" << totalNet << endl;


    // hold the screen until the user is done looking
    cout << "Press any key to continue . . .";
    cin.get();

} // end main

// prompt displays a helpful prompt
void prompt(int n)
{
    cout << "Enter information for employee "
         << n << endl;
} // end function

// getID gets an employee ID
void getID(int id)
{
    cout << "Employee id: ";
    cin >> id;
    while (!validID(id))
        cout <<
};   // get Employee input
    void getName(int);
    void getRate(int);
    void getType(int);

    void getTime(int); // get timeSheet input

    bool validID(int);      // validate Employee input
    bool validName(string);
    bool validRate(float);
    bool validType(int);

    bool validTime(float);  // validate timeSheet input
