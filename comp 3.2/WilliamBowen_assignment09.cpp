/* Program by Silver Bowen
   COSC 1337 - summer 2015
   Status - Complete
   OS Ubuntu 14.04 LTS
   IDE Code::Blocks 13.12

   This is a payroll program for Armadillo Automotive Group.
   It uses a C++ class called employee. Each employee's info
   is held in an Employee object, and all objects are held in
   a master array. A second class called Pay holds employee
   pay info. All input comes from files rather than the keyboard. */

#include <iostream>  // for cin/cout
#include <iomanip>   // for setw()
#include <string>    // for strings
#include <limits>    // to clear strings
#include <fstream>    // for files
using namespace std; // to use std functions w/out a prefix

// Prototypes


class Employee
{
  private:
    int id;             // employee ID
    string name;        // employee name
    double hourlyPay;   // pay per hour
    int numDeps;        // number of dependents
    int type;           // employee type

  public:
    Employee( int initId=0, string initName="",
              double initHourlyPay=0.0,
              int initNumDeps=0, int initType=0 );  // Constructor

    bool set(int newId, string newName, double newHourlyPay,
             int newNumDeps, int newType);

    /* Getters for all five member variables.
       Defined inline because they are short.*/
    int getID(){ return id; }
    string getName() { return name; }
    double getHourlyPay() { return hourlyPay; }
    int getNumDeps() { return numDeps; }
    int getType() { return type; }

};

int main()
{
    // Define constants
    const int TOTAL_EMPS = 6,
               INSURANCE = 20;
    const float TAX_RATE = .15;

    // Define variables
    int     insurance;   // INSURANCE * numDeps
    float hoursWorked,   // hours worked
             grossPay,   // reg pay + overtime
                  tax,   // grossPay * TAX_RATE
               netPay;   // grossPay - tax - insurance

    // Define and initialize holding variables
    int id;             // employee ID
    string name;        // employee name
    double hourlyPay;   // pay per hour
    int numDeps;        // number of dependents
    int type;           // employee type

    // Define and initialize accumulators
    float totalGross = 0.0, // grossPay total for all employees
            totalNet = 0.0; // netPay total for all employees
    int transactions = 0;   // total transactions processed

    // Instantiate an array of objects
    Employee employee[6];

    // Open master file
    ifstream inFile("master9.txt");

    // Call set function to populate objects using for loop
    for (int i = 0; i < TOTAL_EMPS; i++)
    {
        // Read each variable from file
        inFile >> id;
        inFile.ignore();
        getline(inFile, name, '#');
        inFile >> hourlyPay >> numDeps >> type;

        // Use setter to write variables to object
        employee[i].set(id, name, hourlyPay, numDeps, type);
    }

    // Close inFile
    inFile.close();

    // Open transaction file
    ifstream inFile2("trans9.txt");

    // Open report file
    ofstream outFile("report9.txt");

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

    // read data, process, and write to report using for loop
    for (int i = 0; i < TOTAL_EMPS; i++)
    {
        // Get variable values from inFile2
        inFile2 >> id;
        inFile2 >> hoursWorked;

        // Validate employee object id - if 0 it's invalid = error
        if (!employee[i].getID())
            cout << "Entry #" << i+1 << " in employee master file "
                 << "-- invalid employee data!\n";

        // Validate hours worked - if < 0 = error
        else if (hoursWorked < 0.0)
            cout << "Entry #" << i+1 << " employee #"
                 << id << " in transaction file -- invalid hours worked!\n";

        // If object and transaction are valid - write to report
        else
        {
            /* Determine overtime - not eligible
               if hours > 40 or type = union (0). */
            if (hoursWorked <= 40 || employee[i].getType())
                grossPay = hoursWorked * employee[i].getHourlyPay();

            // otherwise eligible
            else
                grossPay = (40 * employee[i].getHourlyPay()) +
                     ((hoursWorked - 40) * employee[i].getHourlyPay() * 1.5);

            // Calculate tax, insurance, and net pay
            tax = grossPay * TAX_RATE;
            insurance = employee[i].getNumDeps() * INSURANCE;
            netPay = grossPay - tax - insurance;

            // Write everything to report
            outFile << fixed << setprecision(2)
                    << setw(2)  << id << " "
                    << setw(20) << left << employee[i].getName()
                    << setw(10) << right << grossPay
                    << setw(10) << tax
                    << setw(12) << insurance
                    << setw(10) << netPay << endl;

            // Accumulate and iterate
            totalGross += grossPay;
            totalNet += netPay;
            transactions++;

        } // End else
    } // End for

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

} // End main

Employee::Employee( int initId, string initName,
                    double initHourlyPay,
                    int initNumDeps, int initType )
{
  bool status = set( initId, initName, initHourlyPay,
                     initNumDeps, initType );

  if ( !status )
  {
    id = 0;
    name = "";
    hourlyPay = 0.0;
    numDeps = 0;
    type = 0;
  }
}

bool Employee::set( int newId, string newName, double newHourlyPay,
                                 int newNumDeps, int newType )
{
  bool status = false;

  if ( newId > 0 && newHourlyPay > 0 && newNumDeps >= 0 &&
       newType >= 0 && newType <= 1 )
  {
    status = true;
    id = newId;
    name = newName;
    hourlyPay = newHourlyPay;
    numDeps = newNumDeps;
    type = newType;
  }
  return status;
}
