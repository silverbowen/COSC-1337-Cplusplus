/* Program by Silver Bowen
   COSC 1337 - summer 2015
   Status - Complete
   OS Ubuntu 14.04 LTS
   IDE Code::Blocks 13.12

   This is a payroll program for Armadillo Automotive Group.
   It uses a C++ class called employee. Each employee's info
   is held in an Employee object, and all objects are held in
   a master array (that can handle up to 100 employees). Names
   etc. are held in C-char[]s rather than String objects.
   Input comes from files rather than the keyboard. */

#include <iostream>  // for cin/cout
#include <iomanip>   // for setw()
#include <limits>    // to clear char[]s
#include <fstream>   // for files
#include <cstring>   // for C-strings
using namespace std; // to use std functions w/out a prefix

class Employee
{
  private:
    int id;             // employee ID
    char name[21];      // employee name
    double hourlyPay;   // pay per hour
    int numDeps;        // number of dependents
    int type;           // employee type

  public:
    Employee( int initId=0, char initName[]="",
              double initHourlyPay=0.0,
              int initNumDeps=0, int initType=0 );  // Constructor

    bool set(int newId, char newName[], double newHourlyPay,
             int newNumDeps, int newType);

    /* Getters for all five member variables.
       Defined inline because they are short.*/
    int getID(){ return id; }
    // because C-strings are arrays, get name returns a char* pointer
    const char* getName() { return name; }
    double getHourlyPay() { return hourlyPay; }
    int getNumDeps() { return numDeps; }
    int getType() { return type; }

};

int main()
{
    // Define constants
    const int MAX_EMPLOYEES = 100,  // max # of employees
                  INSURANCE = 20;   // the cost of insurance
    const float    TAX_RATE = .15;  // the tax rate

    // Define variables
    int     insurance;   // INSURANCE * numDeps
    float hoursWorked,   // hours worked
             grossPay,   // reg pay + overtime
                  tax,   // grossPay * TAX_RATE
               netPay;   // grossPay - tax - insurance
    bool         flag;   // flag for id search loop

    // Define and initialize holding variables
    int id;             // employee ID
    char name[21];        // employee name
    double hourlyPay;   // pay per hour
    int numDeps;        // number of dependents
    int type;           // employee type

    // Define and initialize accumulators
    float totalGross = 0.0, // grossPay total for all employees
            totalNet = 0.0; // netPay total for all employees
    int transactions = 0;   // total transactions processed

    // Instantiate an array of objects
    Employee employee[MAX_EMPLOYEES];

    // Open master file
    ifstream inFile("master10.txt");

    // If file not found
    if (!inFile)
    {
       cout << "Can not open item file \"master10.txt\"" << endl;
       return 1;
    }

    /* This for loop iterates through the Employee object array, reading
       values from the Master File and assigning them to Employee objects. */
    for (int i = 0; i < MAX_EMPLOYEES; i++)
    {
        /* Read each variable from inFile, checking for end-of-file
           via read-error method. */
        if (inFile >> id)
        {
            // Ignore whitespace before calling getline
            inFile.ignore();

            /* Call getline to get name. As noted in the assignment page,
               this raises an error and causes further ifstream operations
               to fail. We could accomplish the same thing by calling
               get rather than getline, but I chose a different method. */
            inFile.getline(name, 21);

            // Clear error bit, so ifstream operations can resume :)
            inFile.clear();

            // Continue reading values
            inFile >> hourlyPay >> numDeps >> type;

            // Ignore last character (sex) and newline character
            inFile.ignore(2);

            // Use setter to write variables to object
            employee[i].set(id, name, hourlyPay, numDeps, type);
        }

        // end  the loop when we're at the end of file (saves on processing)
        else
             i = MAX_EMPLOYEES;
    } // end populate Employees for loop

    // Close inFile
    inFile.close();

    // Open transaction file
    ifstream inFile2("trans10.txt");

    // Open report file
    ofstream outFile("report10.txt");

    // Write report header to file
    outFile << fixed << setprecision(2)
                     << setw(2)  << "ID"  << " "
                     << setw(20) << left  << "Employee Name"
                     << setw(10) << right << "Gross Pay"
                     << setw(10) << "Tax"
                     << setw(12) << "Insurance"
                     << setw(10) << "Net Pay" << endl;
     outFile << "----------------------------------------------"
             << "-------------------" << endl;

    /* This for loop iterates through the transaction file. For each entry,
       the following if/else and for loops read data, process the data, then
       either call error messages or write to the report. */
    for (int i = 0; i < MAX_EMPLOYEES; i++)
    {
        /* Read each variable from inFile2, checking for end-of-file
           via read-error method. */
        if (inFile2 >> id)
        {
            // read hours worked
            inFile2 >> hoursWorked;

            /* This for loop searches the Employee objects array for
               a corresponding employee ID. Note that the new index is j. */
            for (int j = 0; j < MAX_EMPLOYEES; j++)
            {
                // If getID() equals the extracted id:
                if (employee[j].getID() == id)
                {
                    /* Set flag. If this isn't set to true during this loop,
                       an 'employee not found' error will be raised. */
                    flag = true;


                    /* Validate the employee object ID. If it is 0 then invalid
                       data was entered during object creation. If so, print
                       an error message and skip further calculations. */
                    if (!employee[j].getID())
                        cout << "Entry #" << i+1 << " in employee master file "
                             << "-- invalid employee data!\n";

                    /* Validate hours the worked. If they are less than 0,
                       print an error message and skip further calculations. */
                    else if (hoursWorked < 0.0)
                        cout << "Entry #" << i+1 << " in transaction file --"
                             << " employee ID " << id
                             << " -- invalid hours worked!\n";

                    /* If the object and transaction are valid, do needed
                      calculations, then write to report. */
                    else
                    {
                        /* Determine overtime. Employees are eligible if hours
                           worked is over 40 and their type is 0 (union). Here
                           we actually check if type is false (not positive). */
                        if (hoursWorked > 40 && !(employee[j].getType()))
                            grossPay = (40 * employee[j].getHourlyPay())
                                       + ((hoursWorked - 40)
                                          * employee[j].getHourlyPay()
                                          * 1.5);

                        // Else employee is ineligible for overtime
                        else
                            grossPay = hoursWorked
                            * employee[j].getHourlyPay();

                        // Calculate tax, insurance, and net pay
                        tax = grossPay * TAX_RATE;
                        insurance = employee[j].getNumDeps() * INSURANCE;
                        netPay = grossPay - tax - insurance;

                        // Write everything to report
                        outFile << fixed << setprecision(2)
                                << setw(2)  << id << " "
                                << setw(20) << left << employee[j].getName()
                                << setw(10) << right << grossPay
                                << setw(10) << tax
                                << setw(12) << insurance
                                << setw(10) << netPay << endl;

                        // Accumulate and iterate totals
                        totalGross += grossPay;
                        totalNet += netPay;
                        transactions++;

                    } // End if else - determine overtime
                } // end if else - validate hours worked
            } // end for - search array for ID

            // if employee not found
            if (flag == false)
                cout << "Entry #" << i << " in transaction file -- "
                     << "employee ID " << id
                     << " -- not found in Master File!\n";

            // reset flag
            flag = false;

        } // end if - variables from infile2
    } // End for loop - reads data

        // close transaction file
        inFile2.close();

        // Write totals to report
        outFile << setw(23) << "Total gross pay: "
                << setw(10) << totalGross
                << setw(22) << "Total net pay: "
                << setw(10) << totalNet << endl;

        // Close report
        outFile.close();

        // Print transactions successfully processed
        cout << "Total transactions processed: " << transactions << endl;

        // Return success!
        return 0;

} // End main

/* This is the constructor for the Employee class. It calls set and uses the
   returned value to determine if all the parameters are valid. If not, it
   sets everything to 0 or "", so we can print a suitable error message
   in main as needed. */
Employee::Employee(int initId, char initName[], double initHourlyPay,
                   int initNumDeps, int initType)
{
  // Call set and check for boolean return type
  bool status = set(initId, initName, initHourlyPay,
                    initNumDeps, initType);

  // If false was returned
  if (!status)
  {
    id = 0;
    // Because we are using an array pointer, strcpy is needed to set name
    strcpy(name, "");
    hourlyPay = 0.0;
    numDeps = 0;
    type = 0;
  }
} // End Employee::Constructor

/* The set member function does validation. If invalid data is sent, it
   skips setting the data and returns false. */
bool Employee::set(int newId, char newName[], double newHourlyPay,
                   int newNumDeps, int newType)
{
  // Initialize status to false
  bool status = false;

  // If data is valid, perform set operation
  if (newId > 0 && newHourlyPay > 0 && newNumDeps >= 0 &&
      newType >= 0 && newType <= 1)
  {
    status = true;
    id = newId;
    // Again using strcpy
    strcpy(name, newName);
    hourlyPay = newHourlyPay;
    numDeps = newNumDeps;
    type = newType;
  }
  // return bollean value
  return status;
} // End Employee::set member function
