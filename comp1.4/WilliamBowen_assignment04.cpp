/* Program by Silver Bowen
   COSC 1337 - summer 2015
   Status - Complete
   OS Ubuntu 14.04 LTS
   IDE Code::Blocks 13.12

   This program includes a class called Date that stores
   the day, month, and year as private integers. The constructor
   sets the values to 1 - 1 - 2001. It has a setter and getter
   function for the class. The setter includes validation.
   The class has three print member functions and a month
   name string function. Main includes a driver to test the class. */

#include <iostream>  // for cin/cout
#include <cctype>    // for toupper
using namespace std; // to use std functions w/out a prefix

class Date
{
    private:    // member variables set to private
    int month,
        day,
        year;

    public:
    Date()               // constructor
    {
        month = day = 1; // initializes member variables
        year = 2001;
    }

    bool setDate(int, int, int);  //
    void printDate1();            //
    void printDate2();            // prototypes
    void printDate3();            //
    string getMonthName(int);        //

    int getMonth()    //
    { return month;   //
    }                 //
    int getDay()      // inline functions
    { return day;     //
    }                 //
    int getYear()     //
    { return year;    //
    }                 //
};   // end class definition

// this function sets the values in tardis and also does error
// checking. It returns true if the values have
// been changed and false if they have not been changed.
bool Date::setDate( int m, int d, int y)
{
    bool valid = true; // declare and initialize a bool

    // this if does error checking on the values and
    // changes them if everything is copacetic
    if (m > 0 && m <= 12
        && d > 0 && d <= 31
        && y >= 1950 && y <= 2020)
        {
            month = m;
            day = d;
            year = y;
        }
    // if the values are invalid, change valid to false
    else
        valid = false;
    return valid;
}

// this function prints the values in tardis
// in the format day/month/year ie 1/1/2001
void Date::printDate1()
{
    cout << "The current date is: "
         << month << "/" << day
         << "/" << year << endl;
}

// this function prints the values in tardis
// in the format month day, year ie January 1, 2001
void Date::printDate2()
{
    cout << "The current date is: "
         << getMonthName(month) << " "
         << day << ", " << year << endl;
}

// this function prints the values in tardis
// in the format day month year ie 1 January 2001
void Date::printDate3()
{
    cout << "The current date is: "
         << day << " " << getMonthName(month)
         << " " << year << endl;
}

// this function takes the month number
// as an argument1 and returns the month string
string Date::getMonthName(int m)
{
    switch(m)
    {
        case 1:  return "January";
        case 2:  return "February";
        case 3:  return "March";
        case 4:  return "April";
        case 5:  return "May";
        case 6:  return "June";
        case 7:  return "July";
        case 8:  return "August";
        case 9:  return "September";
        case 10: return "October";
        case 11: return "November";
        case 12: return "December";
    }
}

// main is a driver that can be used to
// test the date class by instantiating
// a Date object named tardis and fiddling
// around with it
int main()
{
    // declarations
    char notQuit = 'Y'; // controls Main's while loop
    Date tardis;        // bigger on the inside

    // prototypes
    void expectations();
    char getAnswer();
    void changeValues(Date&);  // important - passed by reference
    void testValues(Date);    // all the functions used in Main
    int getinMonth();
    int getinDay();
    int getinYear();

    // welcome message
    cout << "Main() is a driver that allows you to "
         << "test the Date class.\nI've instantiated "
         << "a Date object named tardis.\nIt's default "
         << "values are day: 1, month: 1, year: 2001.\n";

    // set expectations
    expectations();

    // start while loop
    while (toupper(notQuit) == 'Y')
    {
        // get okay to proceed
        cout << "\nWould you like to enter some values?\n"
             << "Y will let you change the values in tardis, and\n"
             << "any other letter will leave them in place: ";

        // if yes, we'll change some values
        if (toupper(getAnswer()) == 'Y')
          changeValues(tardis);

        // test time
        cout << "\nWould you like to test the changes (or lack thereof)?\n"
             << "Enter Y for yes or any other letter for no: ";
        // if yes, we'll do some tests (using the print functions of Date)
        if (toupper(getAnswer()) == 'Y')
            testValues(tardis);

        // check if we should continue
        cout << "\nWould you like to continue?\n"
             << "Enter Y for yes or any other letter to quit: ";
        cin  >> notQuit;

    } // end while

    cout << "Goodbye!";  // friendly goodbye
    return 0;
} // end main

// this function just prints the expectations for valid input
void expectations()
{
  cout << "\nReminders: valid months are between 1 and 12, inclusive\n"
  << "           valid days are between 1 and 30, inclusive\n"
  << "           valid years are between 1950 and 202, inclusive\n\n"
  << "Also, your input isn't checked until all of it is entered!!\n";
}

// this function lets the tester input a month value
int getinMonth()
{
    int inM;
    cout << "\nPlease enter a month: ";
    cin >> inM;
    return inM;
}

// this function lets the tester input a day value
int getinDay()
{
    int inD;
    cout << "\nPlease enter a day: ";
    cin >> inD;
    return inD;
}

// this function lets the tester input a year value
int getinYear()
{
    int inY;
    cout << "\nPlease enter a year: ";
    cin >> inY;
    return inY;
}

// this functions gets a simple yes or
// anything else answer and returns a char
char getAnswer()
{
    char a;
    cin >> a;
    return a;
}

// this function lets the tester change the values
// in the object named tardis.
void changeValues(Date& tardis)  // important - passed by reference
{
    char retry;
    // this loop let's the user do input and/or retry
    do
    {
        // nested functions let me skip declaring some variables
        if (tardis.setDate(getinMonth(), getinDay(),
                  getinYear()) == true)
        {
            cout << "Okay, the values in tardis have been set.\n";
            retry = 'N';  // if retry isn't set to N here: infinite loop
        }

        // if values are invalid
        else
        {
            cout << "\nSorry, one of your values was invalid.\n"
                 << "The values in tardis have not been changed.\n\n"
                 << "Would you like to see the valid values again?\n"
                 << "Enter Y for yes or any other letter for no: ";

            // ask if user wants to see the rules again
            if (toupper(getAnswer()) == 'Y')
                expectations();

            // ask if user wants to re-enter the values
            cout << "\nWould you like to retry entering some values?\n"
                 << "Y will let you change the values, and\n"
                 << "any other letter will leave them in place: ";
            retry = getAnswer();
        }
    } while (toupper(retry) == 'Y');
}

// this function lets the tester test the 3 inputted values
// by showing what tardis's variables are set to, using
// tardis's three different print functions
void testValues(Date tardis)
{
    int choice;

    // menu let's user choose print function
    cout << "\n1) print the current date as month/day/year\n"
         << "2) print the current date as month day, year\n"
         << "3) print the current date as day month year\n"
         << "4) exit testing\n"
         << "-----------------------\n";

    do // do/while loop let's user repeat test as needed
    {
        cout << "\nChoose 1, 2, 3, or 4: ";
        cin >> choice;
        cout << endl;

        // switch actually calls function selected
        switch (choice)
        {
            case 1: tardis.printDate1();
                    break;
            case 2: tardis.printDate2();
                    break;
            case 3: tardis.printDate3();
                    break;
            case 4: cout << "Leaving test menu.\n"
                         << "------------------\n";
                    break;
            // error checking
            default: cout << "You didn't enter a valid choice.\n";
                     break;
        }
    } while (choice != 4); // end while loop
} // end function
