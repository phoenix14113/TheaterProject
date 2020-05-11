#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
#include "movieTheaterFunctions.h"

/* This program uses stored information from previous program uses to simulate
 * software at a theater. You can ask for statistics, purchase groups of
 * tickets, display that the theater looks like and which seats are taken, or
 * completely reset what the theater looks like. */

int main() {
  // for saving and calling from a file
  ifstream fin;
  ofstream fout;

  // for altering the theater chart array and the theater.txt file
  int userColumns;
  int userRows;
  vector<double> userPrice;

  // for storing information on each theater seat
  char theaterChart[500][500];
  fin.open("theater.txt");

  // find the number of rows and columns and the prices per row in the file
  if (fin.is_open()) {
    // stores the price of each row in the vector userPrice
    for (int i = 0; i >= 0; i++) {
      double tempPrice;
      fin >> tempPrice;
      if (!fin.fail()) {
        userPrice.push_back(tempPrice);
      } else {
        fin.clear();
        break;
      }
    }

    // stores what each row looks like from the file
    double fileInputErrorCheck;
    string fileInput;

    vector<string> eachRow;
    int fileLines = 0;
    while (!fin.eof()) {
      fin >> fileInput;
      eachRow.push_back(fileInput);
      ++fileLines;
    }
    // stores what the row and column sizes are of the file
    userColumns = fileInput.size();
    userRows = fileLines;
    // changes the vector of strings into a 2D array of characters of which
    // seats are taken
    for (int i = 0; i < eachRow.size(); i++) {
      string tempHolder = eachRow.at(i);
      for (int j = 0; j < tempHolder.size(); j++) {
        theaterChart[i][j] = tempHolder.at(j);
      }
    }
    fin.close();
  } else {
    /* collects user input for how big the theater 2D array should be and how
     * expensize each seat is */
    RowsAndColumnsAndPrice(theaterChart, userPrice, userRows, userColumns);
  }

  // This is so the menu constantly outputs after the menu after each switch
  do {
    int chooseFunction = DisplayMenu();
    switch (chooseFunction) {

    case 1:
      // displays what the theater looks like and which seats are already taken
      DisplayTheater(theaterChart, userRows, userColumns);
      break;
    case 2:
      // displays the statistics on how many seats are taken and available and
      // how much money the theater has made
      Statistics(theaterChart, userPrice, userRows, userColumns);
      break;
    case 3:
      // goes to the function that allows a user to purchase a seat
      purchaseASeat(theaterChart, userPrice, userRows, userColumns);
      break;
    case 4:
      // reset the file and create a new one
      RowsAndColumnsAndPrice(theaterChart, userPrice, userRows, userColumns);
      break;
    default:
      cout << "Not a valid option. Please choose again." << endl;
      break;
    }
  } while (true);
}
