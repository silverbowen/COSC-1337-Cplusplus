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
#include <limits>    // to clear strings
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
        name = "";
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


/* main will call IO functions, generate conglomerate
   data, and print out our report. */
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

    // instantiate an array of structs
    Employee employee[TOTAL_EMPS];

    // prototypes
    void prompt(int);  // display prompts

    int getID();   // get Employee input
    string getName();
    float getRate();
    int getType();

    float getTime(string); // get timeSheet input

    bool validID(int);      // validate Employee input
    bool validName(string);
    bool validRate(float);
    bool validType(int);

    bool validTime(float);  // validate timeSheet input

    // for loop for input
    for (int n = 0; n < TOTAL_EMPS; n++)
    {
        prompt(n);
        employee[n].id = getID();
        employee[n].name = getName();
        employee[n].rate = getRate();
        employee[n].type = getType();
        cout << endl;
    } // end for loop

    // prompt for input 2
    cout << "Enter timecard information for each employee:\n\n";

    // for loop for input 2
    for (int n = 0; n < TOTAL_EMPS; n++)
        { timeSheet[n] = getTime(employee[n].name); } // end for loop

   // prompt for report
   cout << "\nPayroll Report\n\n"
        << setw(4) << left << "ID"
        << setw(20) << "Name"
        << setw(9) << right << "Gross Pay"
        << setw(8) << right << "Tax"
        << setw(9) << right << "Net Pay"
        << "\n\n";

    // set precision
    cout << fixed << setprecision(2);

    // print the report
    for (int n = 0; n < TOTAL_EMPS; n++)
        {
            grossPay = timeSheet[n] * employee[n].rate;
            tax = grossPay * TAX_RATE;
            netPay = grossPay - tax;
            totalGross += grossPay;
            totalNet += netPay;

            cout << setw(4) << left << employee[n].id
                 << setw(20) << employee[n].name
                 << setw(9) << right << grossPay
                 << setw(8) << right << tax
                 << setw(9) << right << netPay << endl;
        } // end for loop

    // print the totals
    cout << "\nTotal Gross Pay $ " << totalGross << endl;
    cout << "Total Net Pay   $ " << totalNet << endl;


    // hold the screen until the user is done looking
    cout << "\nPress ENTER to continue . . .";

    // cin.ignore(...) clears buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

} // end main

// prompt displays a helpful prompt
void prompt(int n)
{
    cout << "Enter information for employee "
         << (n + 1) << endl;
} // end function

/* this block of functions returns boolean values to the
functions in the get block, validating the values input there.
Logically, these should be defined after the get block,
but then I would have to declare prototypes inside each get() for
the corresponding validate(). Hence the flip-flop. */

// validID validates id input
bool validID(int checkID)
{
    if (checkID > 0)
        return true;
    else
        return false;
} // end function

// validName validates name input
bool validName(string checkName)
{
    /* I wrote a for loop here because it bugs me that
    C++ doesn't have an "in range (...)" function like
    Python. It's maybe a tad overkill here though. */
    for (int i = 1; i <= 20; i++)
        if (checkName.length() == i) // checks lengths 1 through 20
            return true;  // and returns true if found
    return false; // or else returns false
} // end function

// validRate validates rate input
bool validRate(float checkRate)
{
    if (checkRate > 0)
        return true;
    else
        return false;
} // end function

// validType validates type input
bool validType(int checkType)
{
    // same as for loop note in validName
    for (int i = 0; i < 2; i++)
        if (checkType == i)
            return true; // return true if ==
    return false;  // otherwise return false after if ends
} // end function

// validTime validates time input
bool validTime(float checkTime)
{
    if (checkTime > 0)
        return true;
    else
        return false;
} // end function

/* This block of code is functions that return values
to main. These functions also call validation functions. */

// getID gets an employee ID
int getID()
{
    // local variable
    int tempID = 0;

    // get input
    cout << "Employee ID: ";
    cin  >> tempID;

    //validate input
    while (!validID(tempID))
    {
        cout << "Please enter a positive (greater than 0) value!\n";
        cout << "Employee ID: ";
        cin  >> tempID;
    }  //end while loop

    return tempID;
} // end function

// getName gets an employee name
string getName()
{
    // local variable
    string tempName = "";

    // get input
    cout << "Employee name: ";
    // cin.ignore(...) clears buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, tempName);

    //validate input
    while (!validName(tempName))
    {
        cout << "Please enter a name of 20 characters or less!\n";
        cout << "Employee name: ";
        getline(cin, tempName);
    }  //end while loop

    return tempName;
} // end function

// getRate gets an employee rate
float getRate()
{
    // local variable
    float tempRate = 0.0;

    // get input
    cout << "Pay rate: ";
    cin  >> tempRate;

    //validate input
    while (!validRate(tempRate))
    {
        cout << "Please enter a positive (greater than 0) value!\n";
        cout << "Pay rate: ";
        cin  >> tempRate;
    }  //end while loop

    return tempRate;
} // end function

// getType gets an employee type
int getType()
{
    // local variable
    int tempType = 0;

    // get input
    cout << "Type: ";
    cin  >> tempType;

    //validate input
    while (!validType(tempType))
    {
        cout << "Please enter either 0 for union or 1 for management!\n";
        cout << "Type: ";
        cin  >> tempType;
    }  //end while loop

    return tempType;
} // end function

// getTime gets an employee rate
float getTime(string empName)
{
    // local variable
    float tempTime = 0.0;

    // get input
    cout << "Hours worked for "
         << empName << ": ";
    cin  >> tempTime;

    //validate input
    while (!validTime(tempTime))
    {
        cout << "Please enter a non-negative (0 or larger) value!\n";
        cout << "Hours worked for "
             << empName << ": ";
        cin  >> tempTime;
    }  //end while loop

    return tempTime;
} // end function

// end of program
