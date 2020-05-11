#include "movieTheaterFunctions.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// definitions of global constants defining maximum size of the array
const int MAX_ROWS = 500;
const int MAX_COLUMNS = 500;

void RowsAndColumnsAndPrice(char theater[500][500], vector<double> &price,
                            int &rows, int &columns) {
  for (int i = 0; i < rows; i++) {
    price.pop_back();
  }
  /* clears the input and repeats the question everytime on invalid input is
   * given, with an accompanying error, and then after 3 valid and replaces the
   * values already stored with them.*/
  do {
    cout << "How many rows do you want in the theater? (must be less than "
            "500): ";
    cin >> rows;
    if (rows < MAX_ROWS && rows > 0 && !cin.fail()) {
      cout << "How many columns do you want in the theater? (must be less than "
              "500): ";
      cin >> columns;
      if (columns < MAX_COLUMNS && columns > 0 && !cin.fail()) {
        // finds price per row for as many rows as input by the user.
        for (int i = 0; i < rows; i++) {
          do {
            double tempPrice;
            cout << "How much do you want row " << i + 1 << " to cost?: $";
            cin >> tempPrice;
            if (tempPrice > 0 && !cin.fail() && price.size() < rows) {
              price.push_back(tempPrice);
              break;
            } else {
              cin.clear();
              cin.ignore(MAX_ROWS, '\n');
              cerr << "input a valid number" << endl;
            }
          } while (true);
        }
        break;
      } else {
        cin.clear();
        cin.ignore(MAX_ROWS, '\n');
        cerr << "input a valid number" << endl;
      }
    } else {
      cin.clear();
      cin.ignore(MAX_ROWS, '\n');
      cerr << "input a valid number" << endl;
    }
  } while (true);

  // write or rewrite the array of the seating chart
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      theater[i][j] = '#';
    }
  }
  // output price to theater.txt
  ofstream fout;
  fout.open("theater.txt");
  for (int i = 0; i < price.size(); i++) {
    fout << fixed << setprecision(2) << price.at(i) << endl;
  }
  // output theater layout to theater.txt
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      fout << '#';
    }
    if (i < rows - 1) {
      fout << endl;
    }
  }
  fout.close();
}

int DisplayMenu() {
  // when called displays the possible options and collects the user's choice
  int userChoice;
  cout << "============================================================="
       << endl;
  cout << "This is a list of the possible operations this program can do:"
       << endl;
  cout << "1) Display a seating chart." << endl;
  cout << "2) Statistics on seat sales." << endl;
  cout << "3) Buy or sell tickets." << endl;
  cout << "4) Reset the theater seating chart and seat price." << endl;
  cout << "Type the number next to your choice to select it: ";
  cin >> userChoice;
  return userChoice;
}

void DisplayTheater(char theater[500][500], int rows = 1, int columns = 1) {
  // prints the row that has the tens place on it
  cout << endl << endl << endl;
  cout << setw(18);
  for (int i = 1; i <= columns / 10; i++) {
    cout << i << setw(10);
  }
  // prints the row that has the ones place on it
  cout << endl << setw(9);
  int counter = 1;
  for (int i = 1; i <= columns; i++) {
    cout << counter;
    ++counter;
    if (counter == 10) {
      counter = 0;
    }
  }
  cout << endl;
  for (int i = 0; i < rows; i++) {
    // outputs the row number
    cout << "Row " << i + 1 << ":";
    if (i < 9) {
      cout << setw(3);
    } else if (i < 99) {
      cout << setw(2);
    } else {
      cout << setw(1);
    }
    // outputs if the seat is taken or not dependant on the array
    for (int j = 0; j < columns; j++) {
      cout << theater[i][j];
    }
    cout << endl;
  }
  cout << endl << endl;
  // used so that the menu doesn't re-open till something is entered
  string openMenu;
  cout << "Enter anything to re-open the menu. ";
  cin >> openMenu;
}

void purchaseASeat(char theater[500][500], vector<double> price, int rows = 1,
                   int columns = 1) {

  // variabes for user choices
  int purchaseRow;
  int purchaseColumn;
  int groupSize;
  char checkUser;
  double groupCost = 0;
  vector<int> groupRows;
  vector<int> groupColumns;

  // find how many people are in a group, errors repeat loop
  do {
    cout << "How many people are in the group? ";
    cin >> groupSize;
    if (!cin.fail()) {
      break;
    } else {
      cin.clear();
      cin.ignore(100, '\n');
      cerr << "That is not a valid number. Try again." << endl;
      continue;
    }
  } while (true);
  for (int i = 0; i < groupSize; i++) {

    /* asks for which seat you want by asking for row and column. If you enter a
     * column that doesn't exist it outputs an error and then asks all the
     * questions again. if that seat is already assigned with the taken symbol
     * it outputs an error and starts over. */
    do {
      cout << "Which row would you like to purchase your seat from?: ";
      cin >> purchaseRow;
      if (purchaseRow > 0 && purchaseRow <= rows) {
        cout << "Which column would you like to purchase your seat from?: ";
        cin >> purchaseColumn;
        if (purchaseColumn <= 0 || purchaseColumn > columns) {
          cerr << "That column does not exist. Please pick another one."
               << endl;
          continue;
        }
      } else {
        cerr << "That row does not exist. Please pick another one." << endl;
        continue;
      }
      if (theater[purchaseRow - 1][purchaseColumn - 1] == '*') {
        cerr << "This seat has already been taken. Please choose another."
             << endl;
        continue;
      } else {
        groupColumns.push_back(purchaseColumn);
        groupRows.push_back(purchaseRow);
        break;
      }

    } while (true);
  }

  // asks if the user really wants to buy all of the selected seats
  if (groupColumns.size() == 1) {
    cout << "Do you wish to puchase the seat at";
  } else {
    cout << "Do you wish to puchase the seats at";
  }
  // used to output the selected seats
  for (int i = 0; i < groupColumns.size(); i++) {
    if (i < groupColumns.size() - 1) {
      cout << " row " << groupRows.at(i) << " column " << groupColumns.at(i)
           << ",";
    } else {
      cout << " row " << groupRows.at(i) << " column " << groupColumns.at(i)
           << "?";
    }
  }
  cout << " It will cost $" << setprecision(4);
  // finds the total cost of all seats ready to be purchased.
  for (int i = 0; i < groupRows.size(); i++) {
    groupCost = groupCost + price.at(groupRows.at(i) - 1);
  }
  cout << fixed << setprecision(2) << groupCost << '.' << endl;
  cout << "(type 'y' to continue with your purchase and anything else to "
          "return to the "
          "menu): ";
  cin >> checkUser;
  if (checkUser == 'y') {
    // changes theater at the user indicated row and column to be taken.
    for (int i = 0; i < groupColumns.size(); i++) {
      theater[groupRows.at(i) - 1][groupColumns.at(i) - 1] = '*';
    }
    cout << "Purchase has been completed." << endl;

    ofstream fout;
    fout.open("theater.txt");
    // output prices to file theater.txt
    for (int i = 0; i < price.size(); i++) {
      fout << fixed << setprecision(4) << price.at(i) << endl;
    }
    // output theater layout to file theater.txt
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        fout << theater[i][j];
      }
      if (i < rows - 1) {
        fout << endl;
      }
    }
    fout.close();
  }
}

void Statistics(char theater[500][500], vector<double> price, int rows = 1,
                int columns = 1) {

  cout << endl << endl;

  int totalSeats = rows * columns;

  // find the number of *'s in the array input and assign it to seatsSold
  int seatsSold = 0;
  double revenue = 0;
  for (int i = 0; i < rows; i++) {
    int seatsSoldInRow = 0;
    for (int j = 0; j < columns; j++) {
      if (theater[i][j] == '*') {
        ++seatsSold;
        ++seatsSoldInRow;
      }
    }
    revenue = revenue + seatsSoldInRow * price.at(i);
  }
  int seatsLeft = totalSeats - seatsSold;

  // outputs for all collected information.

  cout << "The total number of seats in the theater is " << totalSeats << '.'
       << endl;
  cout << "There are " << rows << " rows and " << columns << " columns."
       << endl;
  // used to output proper grammer for only 1 seat or many seats
  if (seatsSold != 1) {
    cout << seatsSold << " seats have been sold and " << seatsLeft
         << " are still available." << endl;
  } else {
    cout << seatsSold << " seat has been sold and " << seatsLeft
         << " are still available." << endl;
  }

  cout << "The total revenue made by the theater is $" << fixed
       << setprecision(2) << revenue << endl
       << endl;

  // only goes back to the menu when the user asks for it
  char backToMenu;
  cout << "Enter anything to return to the menu. ";
  cin >> backToMenu;
}