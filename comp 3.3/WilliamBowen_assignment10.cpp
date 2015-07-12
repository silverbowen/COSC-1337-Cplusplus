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

    // Call set function to populate objects using for loop
    for (int i = 0; i < MAX_EMPLOYEES; i++)
    {
        // Read each variable from file - while no read error
        if (inFile >> id)
        {
            cout << "id read " << id << "\n";
            inFile.ignore();
            inFile.getline(name, 21);
            cout << "name read " << name << "\n";
            if (!(inFile >> hourlyPay))
                cout << "Failed!";
            inFile >> numDeps >> type;
            cout << "h n t read " << hourlyPay << " " << numDeps << " " << type << "\n";
            inFile.ignore(2);

            // Use setter to write variables to object
            employee[i].set(id, name, hourlyPay, numDeps, type);
        }

        // end loop if end of file
        else
             i = MAX_EMPLOYEES;
    } // end for loop

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

    // read data, process, and write to report using for loop
    for (int i = 0; i < MAX_EMPLOYEES; i++)
    {
        // Get variable values from inFile2 - if no read error
        if (inFile2 >> id)
        {
            inFile2 >> hoursWorked;

            // search employee array for employee id
            for (int j = 0; j < MAX_EMPLOYEES; j++)
            {
                // when found
                if (employee[j].getID() == id)
                {
                    // set flag
                    flag = true;


                    // Validate employee object id - if 0 it's invalid = error
                    if (!employee[j].getID())
                        cout << "Entry #" << i+1 << " in employee master file "
                             << "-- invalid employee data!\n";

                    // Validate hours worked - if < 0 = error
                    else if (hoursWorked < 0.0)
                        cout << "Entry #" << i+1 << " employee #"
                             << id << " in transaction file --"
                             << " invalid hours worked!\n";

                    // If object and transaction are valid - write to report
                    else
                    {
                        /* Determine overtime - not eligible
                           if hours > 40 or type = union (0). */
                        if (hoursWorked <= 40 || employee[i].getType())
                            grossPay = hoursWorked
                            * employee[i].getHourlyPay();

                        // otherwise eligible
                        else
                            grossPay = (40 * employee[i].getHourlyPay())
                                       + ((hoursWorked - 40)
                                          * employee[i].getHourlyPay()
                                          * 1.5);

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

                    } // End if else - determine overtime
                } // end if else - validate hours worked
            } // end for - search array for ID

            // if employee not found
            if (flag == false)
                cout << "Employee ID " << id << " not found in Master File!\n";

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

Employee::Employee(int initId, char initName[],
                   double initHourlyPay,
                   int initNumDeps, int initType)
{
  bool status = set(initId, initName, initHourlyPay,
                    initNumDeps, initType);

  if (!status)
  {
    id = 0;
    strcpy(name, "");
    hourlyPay = 0.0;
    numDeps = 0;
    type = 0;
  }
}

bool Employee::set(int newId, char newName[], double newHourlyPay,
                   int newNumDeps, int newType)
{
  bool status = false;

  if (newId > 0 && newHourlyPay > 0 && newNumDeps >= 0 &&
      newType >= 0 && newType <= 1)
  {
    status = true;
    id = newId;
    strcpy(name, newName);
    hourlyPay = newHourlyPay;
    numDeps = newNumDeps;
    type = newType;
  }
  return status;
}
