/* Program by Silver Bowen
   COSC 1337 - summer 2015
   Status - Complete
   OS Ubuntu 14.04 LTS
   IDE Code::Blocks 13.12

   This program creates a two-dimensional array (3 x 7) to
   store the amount of food eaten by three different monkeys
   over the course of a week. It takes input for each monkey,
   then displays a nicely-formatted report on the data. The
   report shows a table of amounts eaten, plus average food eaten
   by all monkeys, least by any, and most by any. */

#include <iostream>  // for cin/cout
#include <iomanip>   // for setw()
#include <string>    // for strings
#include <limits>    // to clear strings
using namespace std; // to use std functions w/out a prefix

// define constants
const int NUM_MONKEYS = 3,
            DAYS_WEEK = 7;

// prototypes
string dayName(int);
void getWeeklyFood(float[][DAYS_WEEK], int);
void showWeeklyFood(float[][DAYS_WEEK], int);
float getAvg(float[][DAYS_WEEK], int);
void showAvg(float);
float getMost(float[][DAYS_WEEK], int);
void showMost(float);
float getLeast(float[][DAYS_WEEK], int);
void showLeast(float);

int main()
{
    // declare variables
    float  avg,
          most,
         least;

    // define 2D array
    float monkeyArray[NUM_MONKEYS][DAYS_WEEK];

    // call functions
    getWeeklyFood(monkeyArray, NUM_MONKEYS);    // get food
    showWeeklyFood(monkeyArray, NUM_MONKEYS);   // show table
    avg = getAvg(monkeyArray, NUM_MONKEYS);     // get avg
    showAvg(avg);                               // show avg
    most = getMost(monkeyArray, NUM_MONKEYS);   // get most
    showMost(most);                             // show most
    least = getLeast(monkeyArray, NUM_MONKEYS); // get least
    showLeast(least);                           // show least

    return 0;

} // end main

// dayName converts an int to an abbreviated day name
string dayName(int j)
{
    switch (j)
    {
        case 0 : return "Sun";
        case 1 : return "Mon";
        case 2 : return "Tue";
        case 3 : return "Wed";
        case 4 : return "Thu";
        case 5 : return "Fri";
        case 6 : return "Sat";
    } // end switch
} // end dayName function

// getWeeklyFood gets the food for NUM_MONKEYS monkeys
void getWeeklyFood(float monkeyArray[][DAYS_WEEK], int NUM_MONKEYS)
{
    // loop through array
    for (int i = 0; i < NUM_MONKEYS; i++)
    {
        for (int j = 0; j < DAYS_WEEK; j++)
        {
            // get the food eaten
            cout << "Enter pounds of food eaten by monkey "
                 << i+1 << " on " << dayName(j) << ": ";
            cin  >> monkeyArray[i][j];
            while (monkeyArray[i][j] <= 0)
            {
                cout << "Error: Please enter a non-negative amount!\n"
                     << "Enter pounds of food eaten by monkey "
                     << i+1 << " on " << dayName(j) << ": ";
                cin  >> monkeyArray[i][j];
            }

        } // end inner loop

        cout << endl; // spacer
    }  // end outer loop

    cout << "\n\n";  // spacer
} // end getWeeklyFood function

// showWeeklyFood shows a table of the weekly food eaten
void showWeeklyFood(float monkeyArray[][DAYS_WEEK], int NUM_MONKEYS)
{
    // set precision
    cout << fixed << setprecision(2)  // and print table header
         << "Pounds of Food Eaten by Monkey and Day of Week\n\n"
         << "Monkey" << setw(7) << dayName(0) << setw(7) << dayName(1)
         << setw(7) << dayName(2) << setw(7) << dayName(3)
         << setw(7) << dayName(4) << setw(7) << dayName(5)
         << setw(7) << dayName(6) << "\n\n";

    // loop through array
    for (int i = 0; i < NUM_MONKEYS; i++)
    {
        // show current monkey
        cout << setw(6) << right << i+1;

        for (int j = 0; j < DAYS_WEEK; j++)
        {
            // show food eaten
            cout << setw(7) << right << monkeyArray[i][j];

        } // end inner loop

    cout << endl; // spacer
    } // end outer loop

    cout << "\n\n";  // spacer
} // end showWeeklyFood function

// getAvg returns the avg food eaten
float getAvg(float monkeyArray[][DAYS_WEEK], int NUM_MONKEYS)
{
    // define and initialize accumulator
    float totalFood = 0.0;

    // loop through array
    for (int i = 0; i < NUM_MONKEYS; i++)
    {
        for (int j = 0; j < DAYS_WEEK; j++)
        {
            // accumulate total
            totalFood += monkeyArray[i][j];

        } // end inner loop
    } // end outer loop

    // calculate return average
    return totalFood/(NUM_MONKEYS*DAYS_WEEK);

} // end getAvg function

// showAvg shows the average food eaten by all monkeys
void showAvg(float avg)
{
    // display average
    cout << "The average food eaten per day by all monkeys  :"
         << setw(8) << right << avg << " pounds\n";

} // end showAvg function

// getLeast gets the least amount of food eaten
float getLeast(float monkeyArray[][DAYS_WEEK], int NUM_MONKEYS)
{
    // initialize leastFood
    float least = monkeyArray[0][0];

    // loop through array
    for (int i = 0; i < NUM_MONKEYS; i++)
    {
        for (int j = 0; j < DAYS_WEEK; j++)
        {
            // accumulate total
            if (monkeyArray[i][j] < least)
                least = monkeyArray[i][j];

        } // end inner loop
    } // end outer loop

    // return least
    return least;

} // end getLeast function

// showLeast shows the least food eaten by any monkey
void showLeast(float least)
{
    // display least
    cout << "The least amount of food eaten by any monkey   :"
         << setw(8) << right << least
         << " pounds\n";

} // end showLeast function

// showMost shows the most food eaten by any monkey
float getMost(float monkeyArray[][DAYS_WEEK],int NUM_MONKEYS)
{
    // initialize mostFood
    float most = monkeyArray[0][0];

    // loop through array
    for (int i = 0; i < NUM_MONKEYS; i++)
    {
        for (int j = 0; j < DAYS_WEEK; j++)
        {
            // accumulate total
            if (monkeyArray[i][j] > most)
                most = monkeyArray[i][j];

        } // end inner loop
    } // end outer loop

    // return most
    return  most;

} // end getMost function

// showMost shows the most food eaten by any monkey
void showMost(float most)
{
    // display most
    cout << "The largest amount of food eaten by any monkey :"
         << setw(8) << right << most
         << " pounds\n";

} // end showMost function
