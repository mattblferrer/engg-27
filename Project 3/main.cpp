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
#include <complex>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Validates the filename by checking if the file exists. Returns the
 * valid filename as output.
*/
string validate_input_filename()
{
  // get initial filename from user
  string filename;
  cout << "\nEnter filename of Polynomial File Format file: ";
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
bool extract_coefficients(string filename, int& degree,
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
    cout << "\nInvalid Polynomial File Format header. Enter another";
    cout << " filename." << endl;
    return false;
  } 

  // check if second token (degree) is a valid integer
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

  // checking if following tokens are valid coefficients
  double c;
  for (int i = 0; i <= degree; i++)
  {
    getline(file, line);
    stream.str(line);
    stream.clear();
    if (!(stream >> c))
    {
      cout << "Invalid Polynomial File Format coefficient. Enter"; 
      cout << "another filename." << endl;
      return false;
    }
    coefficients.push_back(c);
  }

  // valid polynomial file format
  cout << "File " << filename << " follows the Polynomial File ";
  cout << "Format." << endl;
  return true;
}

/**
 * Gets the number of iterations from the user and checks that it 
 * is valid.
*/
int validate_iterations()
{
  string input;
  int iterations;
  cout << "\nEnter number of iterations: ";
  stringstream stream;

  while (true)  // loop until valid input
  {
    getline(cin, input);
    stream.str(input);
    stream.clear();
    if (!(stream >> iterations))
    {
      cout << "\nInvalid input. Please enter a valid number: ";
    }
    else 
      if (iterations < 1)
      {
        cout << "\nInvalid input. Please enter iterations ";
        cout << "above 0: ";
      } 
      else
        if (stream >> input)
        {
          cout << "\nInvalid input. Please enter a valid number: ";
        }
        else 
          break;
  }
  
  cout << "Valid number of iterations." << endl;
  return iterations;
}

/**
 * Solves for the roots of the polynomial using the Durand-Kerner
 * method. 
*/
complex<double>* determine_roots(int& degree, 
  vector<double>& coefficients, int& iterations)
{
  complex<double>* roots = new complex<double>[degree];
  complex<double>* W = new complex<double>[degree];
  complex<double> base(0.4, 0.9); // arbitrary starting point
  
  // first iteration x_i (0)
  for(int i = 0; i < degree; i++)
  {
    roots[i] = pow(base, i);
  }

  // loop iterations
  for (int k = 0; k < iterations; k++)
  {
    // Weierstrass correction
    for (int i = 0; i < degree; i++) // ith root
    {
      W[i] = 1;
      complex<double> p_i(0, 0);
      for (int j = 0; j < degree; j++)  // denominator
      {
        if (i == j)
        {
          continue;
        }
        W[i] *= roots[i] - roots[j]; 
      }

      for (int j = 0; j <= degree; j++) // numerator
      {
        p_i += coefficients[j] * pow(roots[i], j); // compute terms
      }
      W[i] = p_i / W[i];
    }
    
    // next iteration x_i (k + 1) from x_i (k)
    for (int i = 0; i < degree; i++)
    {
      roots[i] -= W[i];
    }
  }  
  
  return roots;
}

/**
 * Evaluates the polynomial for each root in roots[i] and returns
 * the value of the polynomial as a complex number. 
*/
complex<double>* evaluate_polynomial(int& degree, 
  vector<double>& coefficients, complex<double>* roots)
{
  complex<double>* eval = new complex<double>[degree];
  
  for (int i = 0; i < degree; i++)
  {
    for (int j = 0; j <= degree; j++) // per term
    {
      eval[i] += coefficients[j] * pow(roots[i], j);
    }
  }

  return eval;
}

/**
 * Prints the roots of the polynomial and the value of the 
 * polynomial both to an output file and to the console. 
*/
void print_roots(string filename, int& degree, 
  complex<double>* roots, complex<double>* eval)
{
  ofstream file(filename.c_str());  // open file
  file << setprecision(15);

  // print roots to file
  for (int i = 0; i < degree; i++)
  {  
    if (imag(roots[i]) == 0)
    {
      file << "f(" << real(roots[i]);
    }
    else
      if (imag(roots[i]) < 0)
      {
        file << "f(";
        file << real(roots[i]) << " - ";
        file << abs(imag(roots[i])) << "i";
      }
      else 
        if (imag(roots[i]) > 0)
        {
          file << "f(";
          file << real(roots[i]) << " + " << imag(roots[i]) << "i";
        }

    file << ") = ";

    if (imag(eval[i]) == 0)
    {
      file << real(eval[i]) << endl;
    }
    else
      if (imag(eval[i]) < 0)
      {
        file << real(eval[i]) << " - " << imag(eval[i]);
        file << "i" << endl;
      }
      else
        if (imag(eval[i]) > 0)
        {
          file << real(eval[i]) << " + " << imag(eval[i]);
          file << "i" << endl;
        }
  }

  // print roots to console
  cout << "\nRoots of Polynomial:" << endl;
  if (degree <= 20)
  {
    for (int i = 0; i < degree; i++)
    {  
      if (imag(roots[i]) == 0)
      {
        cout << "f(" << real(roots[i]);
      }
      else
        if (imag(roots[i]) < 0)
        {
          cout << "f(";
          cout << real(roots[i]) << " - ";
          cout << abs(imag(roots[i])) << "i";
        }
        else 
          if (imag(roots[i]) > 0)
          {
            cout << "f(";
            cout << real(roots[i]) << " + " << imag(roots[i]) << "i";
          }
      
      cout << ") = ";

      if (imag(eval[i]) == 0)
      {
        cout << real(eval[i]) << endl;
      }
      else
        if (imag(eval[i]) < 0)
        {
          cout << real(eval[i]) << " - " << imag(eval[i]);
          cout << "i" << endl;
        }
        else
          if (imag(eval[i]) > 0)
          {
            cout << real(eval[i]) << " + " << imag(eval[i]);
            cout << "i" << endl;
          }
    }
  }
  else
  {
    cout << "\nPolynomial has too many roots";
    cout << "to print to console." << endl;
  }
}

/**
 * Validates the output filename. This function does not require
 * a filename with an extension. 
*/
string validate_output_filename()
{
  string filename;
  cout << "\nEnter filename of output file: ";
  getline(cin, filename);
  return filename;
}

/**
 * Prints menu options to the console
*/
int menu()
{
  int choice;
  string input;
  stringstream stream;

  while (true)
  {
    cout << "\n1. Find roots of polynomial" << endl;
    cout << "2. Display instructions" << endl;
    cout << "3. Quit" << endl;
    cout << "Enter menu: ";
    
    getline(cin, input);
    stream.str(input);
    stream.clear();
    
    if (!(stream >> choice))
    {
      cout << "\nInvalid input. Please enter a valid number." << endl;
    }
    else
      if (choice > 3 || choice < 1)
      {
        cout << "\nInvalid input. Please enter a number from 1-3." << endl;
      }
      else
        if (stream >> input)
        {
          cout << "\nInvalid input. Please enter a valid number." << endl;
        }
        else
          break;
  }
  return choice;
}

void instructions()
{
  cout << "\nThis program solves for the roots of a polynomial.";
  cout << "\nEnter a file with that contains the following format:";
  cout << "\n\nPOLYNOMIAL optional comments" << endl;
  cout << "n optional comments" << endl;
  cout << "a_0 optional comments" << endl;
  cout << "a_1 optional comments" << endl;
  cout << "." << endl << "." << endl << "." << endl ;
  cout << "a_{n-1} optional comments" << endl;
  cout << "a_n optional comments" << endl;
  cout << "optional comments" << endl;
  cout << "\nNOTES" << endl;
  cout << "The first line must be the string 'POLYNOMIAL'";
  cout << "in uppercase." << endl;
  cout << "The second line must be the";
  cout << " degree of the polynomial." << endl;
  cout << "The subsequent lines must be valid";
  cout << " floating point numbers" << endl;
  cout << "These subsequent lines represent the coefficients";
  cout << " of the unspecified variable in increasing powers.";

  cout << "\nPress enter to continue...";
  string temp;
  getline(cin, temp);
}

int main()
{
  cout << "Roots of Polynomials" << endl;
  cout << "Ferrer, Bernardo" << endl;

  vector<double> coefficients;
  string filename;
  int degree;
  int iterations;
  cout << setprecision(15);

  while(true)
  {
    int choice = menu(); 

    if (choice == 1)
    {
      filename = validate_input_filename();
      while (!extract_coefficients(filename, degree, coefficients))
      {
        filename = validate_input_filename();
      }

      iterations = validate_iterations();
      complex<double>* roots = determine_roots(degree, coefficients, iterations);
      complex<double>* eval = evaluate_polynomial(degree, coefficients, roots);
      filename = validate_output_filename();
      print_roots(filename, degree, roots, eval);
    }
    else
      if (choice == 2)
      {
        instructions();
      }
      else
        if (choice == 3)
        {
          cout << "\nExiting program." << endl;
          return 0;
        }
  }
}
