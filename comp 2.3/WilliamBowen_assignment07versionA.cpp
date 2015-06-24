/* Program by Silver Bowen
   COSC 1337 - summer 2015
   Status - Complete
   OS Ubuntu 14.04 LTS
   IDE Code::Blocks 13.12

   This program takes input from a user of
   package weights and dimensions and provides
   postal costs. */

#include <iostream>  // for cin/cout
#include <iomanip>   // for setw()
#include <string>    // for strings
#include <limits>    // to clear strings
using namespace std; // to use std functions w/out a prefix

/* Define constants. I made these all integers because
   the sample output was all integers (except shipping
   cost). I probably would have done floats otherwise. */
int MAX_WEIGHT = 50, // maximum weight in lbs
    MAX_INCHES = 36, // max length of any side
    MAX_GIRTH  = 60, // max smallest circumference
    T_SIZE     = 15; // size of array of objects

// Prototypes
class TableEntry;  // This class will hold table entries
void populate(TableEntry []);  // This will populate our array
void showPrompt(); // This will give our opening prompt
bool getTransaction(int&, int&, int&, int&); // This gets input from user
void showResult(int, string, int, float); // Prints transaction results
bool errorMessage(int&, int&, int&, int&);    // This checks for negative input
float getCost(int, TableEntry []); // This calculates the cost
bool getStatus(int&, int&, int&, int&);  // This determines accepted or rejected
void showTotals(int, int);  //This shows total accepted/rejected transactions


/* Class TableEntry holds one pair of weight/shipping
   charges per instantiated object. It will be used
   in an array of objects to make our shipping table. */
class TableEntry
{
    private:
    int weight;      // weight threshold in lbs
    double shipping; // shipping charge if <= weight

    public:  // all the functions are inline

    void setWeight(int w) // sets the weight
    {  weight = w;  }

    void setShipping(double s)  // sets the shipping
    {  shipping = s;  }

    int getWeight()          // gets the weight
    {  return weight;  }

    float getShipping()      // gets the shipping
    {  return shipping;  }

}; // end TableEntry class


int main()
{
     // Define variables
     int weight,  // holds package weight
         len1,    // these three hold the package dimensions
         len2,
         len3,
         trans = 0,   // counter that keeps track of current transaction number
         accepted = 0, // # of accepted packages
         rejected = 0; // # of rejected packages
     float cost;       // holds shipping cost
     string status;    // holds accepted/rejected status string


     TableEntry table[T_SIZE]; // This is our array of objects

     // set precision
     cout << fixed << setprecision(2);

     // Call functions
     populate(table);  // Put all the table data in our array
     showPrompt();        // Say hi to user

     /* This loop keeps going as long as getTransaction keeps
        returning true (ie, no -1 input for weight). */
     while (getTransaction(weight, len1, len2, len3)) // get input from user
     {
         /* Decide whether to continue or not. If an
            error message is displayed,we skip the rest
            of the processing and go back to the top. */
         if (!errorMessage(weight, len1, len2, len3))
         {
             trans++; // only iterates if no error

             if (getStatus(weight, len1, len2, len3)) // get the status
             {
                 status = "Accepted"; // if package is accepted,
                 accepted++;          // iterate accepted and get the cost.
                 cost = getCost(weight, table);
             }

             else
             {
                 status = "Rejected"; // if rejected, iterate rejected
                 rejected++;          // no need to get cost
             }

             // show the result of the transaction
             showResult(trans, status, weight, cost);
         }
     } // end while loop

     // show our final totals
     showTotals(accepted, rejected);

}  // end main


/* The populate function just calls setters
   on the TableEntry objects in the table
   array. Tedious stuff, I know. */
void populate(TableEntry t[])
{
     t[0].setWeight(1);       // All we're doing here is
     t[0].setShipping(1.50);  // setting the values for each
     t[1].setWeight(2);       // object in the array,
     t[1].setShipping(2.10);  // one by one.
     t[2].setWeight(3);
     t[2].setShipping(4.00);
     t[3].setWeight(5);
     t[3].setShipping(6.75); // I could have saved myself some
     t[4].setWeight(7);      // trouble if I'd made one setter
     t[4].setShipping(9.90); // method that set both values,
     t[5].setWeight(10);     // but by the time I thought of
     t[5].setShipping(14.95);// that I was already done.
     t[6].setWeight(13);
     t[6].setShipping(19.40);
     t[7].setWeight(16);
     t[7].setShipping(24.20);
     t[8].setWeight(20);
     t[8].setShipping(27.30);
     t[9].setWeight(25);
     t[9].setShipping(31.90);
     t[10].setWeight(30);
     t[10].setShipping(38.50);
     t[11].setWeight(35);
     t[11].setShipping(43.50);
     t[12].setWeight(40);
     t[12].setShipping(44.80);
     t[13].setWeight(45);
     t[13].setShipping(47.40);
     t[14].setWeight(50);
     t[14].setShipping(55.20);
}

/* The showPrompt function gives the user
   instructions on what to enter. */
void showPrompt()
{
    cout << "For each transaction, enter package weight and"
         << "3 dimensions.\nEnter -1 to quit.\n\n";

}  // end showPrompt function

/* The getTransaction function gets input from the user.
   It returns false when the user enters -1. */
bool getTransaction(int &weight, int &len1, int &len2, int &len3)
{
    // helpful prompt
    cout << "Enter package weight and 3 dimensions: ";

    // get weight
    cin >> weight; // get input

    // if weight is -1, immediately return false/kill the loop (in main)
    if (weight == -1)
        return false;

    cin >> len1 >> len2 >> len3; // get rest of input

    // clear the buffer after getting all 4 values, just in case
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // return true and keep going
    return true;

} // end getTransaction function

/* the getStatus function gets the status of a transaction
   and returns a bool to main true for accepted, false otherwise). */
bool getStatus(int &weight, int &len1, int &len2, int &len3)
{
     // initialize variables
     bool status = false;  // our bool
     int largest = len1;    // holding variable for largest current side

     // first check if we are over weight, if so, skip the rest
     if (weight <= MAX_WEIGHT)
     {
         if (len2 > largest)  // check against largest
             largest = len2;
         if (len3 > largest)  // and again
             largest = len3;

         // this if clause determines whether we are over girth
         if (2 * (len1 +len2 + len3 - largest) <= MAX_GIRTH)
             status = true;  // if not, true
     }  // end if

     // return status
     return status;

} // end getStatus function

/* getCost takes an int from our holding array for transaction input
   and our entire array of objects and calculates shipping cost. It isn't
   ever called if the transaction was rejected. */
float getCost(int weight, TableEntry table[])
{
     // handy for loop, iterate through object array
     for (int i = 0; i < T_SIZE; i++)
     {
         /* check if weight <= current TableEntry object's weight.
            If so, we know we are in the right category. */
          if (weight <= table[i].getWeight())
             return table[i].getShipping();
     } // end for loop

} // end getCost function

/* errorMessage prints an error message if needed.
   It also returns a bool that serves as a flag for whether
   to continue processing the input or whether to restart. */
bool errorMessage(int &weight, int &len1, int &len2, int &len3)
{
     bool error = false; // variable to hold return value

     // throw error message if non positive input
     if (weight < 0 || len1 < 0 || len2 < 0 || len3 < 0)
     {
          cout << "\nError - package weight and dimensions must be "
               << "larger than 0\nPlease re-enter transaction\n\n";

          // set bool
          error = true;
     }

     // return bool
     return error;

}  // end errorMessage function

/* showResult takes all the values we've calculated and displays
   them for the user. */
void showResult(int trans, string status, int weight, float cost)
{
     cout << "\nTransaction :"
          << setw(11) << trans
          << "\nStatus      :"
          << setw(11) << status
          << "\nWeight      :"
          << setw(11) << weight
          << "\nCost        :";

     // decide whether to show a cost or show a -
     if (status == "Accepted")
         cout << setw(11) << cost << "\n\n";
     else
         cout << setw(11) << "-" << "\n\n";

}  // end showResult function

/* showTotals takes the accumulators we've been running and
   prints them out, so the user knows how many packages were
   accepted and rejected. */

void showTotals(int accepted, int rejected)
{
    cout << "\nNumber of accepted packages: "
         << accepted << endl
         << "Number of rejected packages: "
         << rejected << endl;

} // end showTotals function
