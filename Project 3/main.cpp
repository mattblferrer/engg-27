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
 * Validates the filename by checking if the file exists. Returns the
 * valid filename as output.
*/
string validate_filename()
{
  // get initial filename from user
  string filename;
  cout << "Enter filename of Polynomial File Format file: ";
  getline(cin, filename);
  ifstream file(filename.c_str());  // open file

  // loop until valid filename or path entered
  while (true)  
  {
    if (file.is_open()) // check if file is open (valid file)
    {
      cout << "\nFile " << filename << " exists." << endl;
      file.close();
      return filename;
    }

    // if invalid filename, repeat input sequence
    cout << "\nThere was a problem opening the file." << endl;
    cout << "Enter filename of Polynomial File Format file: ";
    getline(cin, filename);
    file.close();
    file.open(filename.c_str());  // change name of file opened
  }
}

/**
 * Validates the file by checking if the file follows the Polynomial
 * File Format. If file is valid, the coefficients are added to the
 * "coefficients" vector. Returns true if the file is valid, else 
 * false
*/
bool extract_coefficients(string filename, 
  vector<double>& coefficients)
{
  ifstream file(filename.c_str());  // open file

  // check if first token (header) is "POLYNOMIAL"
  string line;
  string header; 
  getline(file, line);
  stringstream stream(line);
  stream >> header;

  if (header != "POLYNOMIAL")  // invalid header
  {
    cout << "Invalid Polynomial File Format header. Enter another";
    cout << " filename." << endl;
    return false;
  } 

  // check if second token (degree) is a valid integer
  int degree;
  getline(file, line);
  stream.str(line);
  stream.clear();

  if (!(stream >> degree))  // invalid degree
  {
    cout << degree;
    cout << "Invalid Polynomial File Format degree. Enter another";
    cout << " filename." << endl;
    return false;
  }

  cout << "File " << filename << " follows the Polynomial File ";
  cout << "Format." << endl;

  // TODO: read coefficients

  return true;
}

void determine_roots()
{

}

int main()
{
  cout << "Roots of Polynomials" << endl;
  cout << "Ferrer, Bernardo\n" << endl;

  vector<double> coefficients;
  string filename;
  filename = validate_filename();
  while (!extract_coefficients(filename, coefficients))
  {
    filename = validate_filename();
  }

  return 0;
}
