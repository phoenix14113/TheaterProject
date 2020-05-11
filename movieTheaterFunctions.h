#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
extern const int MAX_ROWS;
extern const int MAX_COLUMNS;

/* precondition: rows amd columns values must be less than 500 and greater than
   zero and price is greater than zero.
   postcondition: returns the values the user input into their respective
   variables in the equation*/
void RowsAndColumnsAndPrice(char theater[500][500], vector<double> &price,
                            int &rows, int &columns);

/* postcondition: outputs the user interface and the number of the choice the
 * user input. */
int DisplayMenu();

/* postcondition: outputs the array entered in with numbers marking row and
 * column and then asks if the user would like to see the menu again. */
void DisplayTheater(char theater[500][500], int rows, int columns);

// postcondition: changes an index in the input array to the taken symbol '*'
void purchaseASeat(char theater[500][500], vector<double> price, int rows,
                   int columns);

/* postcondition: outputs the selected seat or seats and changes their
 * respective symbol in the array to the purchased symbol */
void Statistics(char theater[500][500], vector<double> price, int rows,
                int columns);