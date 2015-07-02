/* Program by Silver Bowen
   COSC 1337 - summer 2015
   Status - Complete
   OS Ubuntu 14.04 LTS
   IDE Code::Blocks 13.12

   This program takes input from a user for
   the names and scores of a class. It then sorts
   the class in order of ascending score and
   calculates the average score for the class.
   Finally, it shows the results as a table.
   Pointer notation is used throughout (rather than
   array notation). A struct holds the paired data.*/

#include <iostream>  // for cin/cout
#include <iomanip>   // for setw()
#include <string>    // for strings
#include <limits>    // to clear strings
using namespace std; // to use std functions w/out a prefix

/* Define struct Student. */
struct Student
{
    string name;  // up to 30 characters, including spaces
    int score;    // integer value - between 0 -105, inclusive
};

/* Prototypes, in order of use. */
void getStudents(Student *, int); // gets info from user
void sortByScore(Student *, int); // sorts array of structs (ascending order)
float getAvg(Student *, int);     // calculates avg
void showTable(Student *, int, float); // displays formatted table

/* Main will do all the I/O as well as calling
   each function prototyped above, in order. */
int main()
{
    // Declare variables
    int totalStudents; // holds total number of students
    float avgScore;    // holds the calculated avg score
    Student *student;  // array to hold Student structs

    // Get total students
    cout << "This program will take the name and "
         << "score for any number of students,\n"
         << "sort them by score, calculate the average score,\n"
         << "and display the results as a formatted table.\n\n"
         << "Please enter the number of students (or 0 to quit): ";
    cin  >> totalStudents;

    // Error check for nonnegative number of students
    while (totalStudents < 0)
    {
        cout << "\nError! Please enter a non-negative "
             << "number of students (or 0 to quit): ";
        cin  >> totalStudents;
    }

    // If user hasn't quit
    if (totalStudents)
    {
        // Dynamically allocate memory for array
        student = new Student[totalStudents];

        // Call getStudents to get student names/scores
        getStudents(student, totalStudents);

        // Call sortByScore to sort the students by score
        sortByScore(student, totalStudents);

        // Call avgScore to compute/return the average score
        avgScore = getAvg(student, totalStudents);

        //Call showTable to display results
        showTable (student, totalStudents, avgScore);

        // Return allocated memory to heap
        delete [] student;

        // Set student to 0 to prevent errors
        student = 0;
    }

    // Return 0 for success
    return 0;

}  // end main

/* Function getStudents populates Student structs in array
   of structs student via user input. */
void getStudents(Student *student, int length)
{
    // Loop through array
    for (int i = 0; i < length; i++)
    {
        // Clear buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Get input - name
        cout << "\nEnter the name of student #" << i + 1 << ": ";
        getline(cin, (student + i)->name);

        // Validate input
        while (((student + i)->name).length() < 1
                     || ((student + i)->name.length() > 30))
        {
            cout << "\n-----Error!-----\nName must be from "
                 << "1 to 30 characters, including spaces.\n"
                 << "\nEnter the name of student #" << i + 1 << ": ";
            getline(cin, (student + i)->name);
        }

        // Get input - score
        cout << "Enter the score for student #" << i + 1 << ": ";
        cin  >> (student + i)->score;

        // Validate input
        while ((student + i)->score < 0
                 || (student + i)->score > 105)
        {
            cout << "\n-----Error!-----\nScore must be an integer "
                 << "from 0 to 105, inclusive.\n"
                 << "\nEnter the score for student #" << i + 1 << ": ";
            cin  >> (student + i)->score;
        }
    }  //end for loop
} // end getStudents function

/* Function sortByScore sorts the array by score, ascending. */
void sortByScore(Student *student, int totalStudents)
{
    // Declare variables
    Student temp;
    int swapJ;

    // Use selection sort to sort elements of array
    // First, get starting point of array
    for (int i = 0; i < totalStudents - 1; i++)
    {
        // Initialize variables
        temp = *(student + i);
        swapJ = i;

        // Check each index after starting point to see
        // if score value is smaller
        for (int j = i + 1; j < totalStudents; j++)
        {
            // if smaller, save the values & index
            if ((student + j)->score < temp.score)
            {
                temp = *(student + j);
                swapJ = j;
            }  // end if
        } // end inner loop

        // Swap out start index value for swapJ(lowest found) value
        // then swap temp value for start index value
        *(student + swapJ) = *(student + i);
        *(student + i) = temp;

    } // end outer loop
} // end sortByScore function;

/* avgScore computes and returns the class' average score */
float getAvg(Student *student, int totalStudents)
{
    // Initialize accumulator
    float total = 0;

    // Accumulate total
    for (int i = 0; i < totalStudents; i++)
        { total +=  (student + i)->score; }

    // Return average
    return total/totalStudents;

} // End getAvg function

/* showTable displays a nicely formatted table */
void showTable(Student *student, int totalStudents, float avgScore)
{
    // Header for the table, w/ formatting
    cout << "\n\n" << setw(30) << left << "Name" << "Score"
         << "\n-----------------------------------\n";

    // For loop prints names/scores
    for (int i = 0; i < totalStudents; i++)
    {
        cout << setw(30) << left << (student + i)->name
             << setw(5) << right << (student + i)->score << endl;
    }

    // I set precision to 1 and added a couple extra spaces
    // in the setw so avgScore's decimal would hang off the
    // end as per the example :)
    cout << "-----------------------------------\n"
         << setw(30) << left << "Average"
         << fixed << setprecision(1)
         << setw(7) << right << avgScore << endl;

}  // End showTable function
