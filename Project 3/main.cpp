/**
 * main.cpp
 * 
 * BERNARDO, Jonathan
 * FERRER, Matt
 * 
 * Project 3 - Roots of Polynomials
 * ENGG 27 - M
*/

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Reads a Polynomial File Format file and adds the coefficients
 * of the polynomial to the double vector "coefficients".
 */
void extract_coefficients(vector<double>& coefficients)
{
  // get initial filename from user
  string filename;
  cout << "Enter filename of Polynomial File Format file ";
  cout << "(Include the extension): ";
  getline(cin, filename);
  ifstream file(filename.c_str());  // open file

  // loop until valid filename or path entered
  while (true)  
  {
    if (file.is_open()) // check if file is open (valid file)
    {
      cout << "\nFile " << filename << " successfully read." << endl;
      break;
    }

    // if invalid filename, repeat input sequence
    cout << "\nThere was a problem opening the file." << endl;
    cout << "Enter filename of coordinates file ";
    cout << "(Include the extension): ";
    getline(cin, filename);
    file.close();
    file.open(filename.c_str());  // change name of file opened
  }

  // read coefficients from file
  // TODO: read coefficients
}

void determine_roots()
{

}



int main()
{
  vector<double> coefficients;
  extract_coefficients(coefficients);  // stores in coefficients

  cout << "Roots of Polynomials" << endl;
  cout << "Ferrer, Bernardo\n" << endl;

  return 0;
}
