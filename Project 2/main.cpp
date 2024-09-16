/**
 * main.cpp
 * 
 * BERNARDO, Jonathan
 * FERRER, Matt
 * 
 * Project 2 - Parabolic Fit
 * ENGG 27 - M
*/

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Validates the filename by checking if the file exists. Returns 
 * the filename as the output. 
*/
string validate_filename()
{
  string filename;
  cout << "Enter filename of coordinates file ";
  cout << "(Include the extension): ";
  getline(cin, filename);
  ifstream file(filename.c_str());  // open file

  while (true)  // loop until valid filename or path entered
  {
    if (file.is_open()) // check if file is open (valid file)
    {
      file.close();
      cout << "File " << filename << " successfully read." << endl;
      return filename;
    }

    // if invalid filename, repeat input sequence
    cout << "There was a problem opening the file." << endl;
    cout << "Enter filename of coordinates file ";
    cout << "(Include the extension): ";
    getline(cin, filename);
    file.close();
    file.open(filename.c_str());  // change name of file opened
  }
}

/**
 * Reads an xy format file and adds the x-coordinates and y-
 * coordinates to vectors x_i and y_i, respectively. 
 */
void read_xy_file(string filename, vector<double>& x_i, 
  vector<double>& y_i)
{
  int lines_read = 0;  // number of lines read in the file
  double x = 0;
  double y = 0;
  string line;

  ifstream xy_file(filename.c_str());  // open file
  while(getline(xy_file, line))  // extract x, y coordinates per line
  {
    stringstream stream(line);
    if (!(stream >> x))  // no x value found in line
    {
      cout << "No x-value found in line " << lines_read + 1 << 
        "." << endl;
      break;
    }
    if (!(stream >> y))  // no y value found in line
    {
      cout << "No y-value found in line " << lines_read + 1 << 
        "." << endl;
      break;
    }

    // if both x and y found
    x_i.push_back(x);
    y_i.push_back(y);
    lines_read++;
  }

  // information about number of points extracted
  cout << lines_read << " points extracted." << endl;
}

/**
 * This function sets up a representation of systems of equations
 * using the x-y data obtained from the x-y formatted file. The
 * solution is a parabola y = ax^2 + bx + c that best fits the data.
 */
double** system_of_equations(vector<double>& x_i, vector<double>& y_i)
{
  double** system = new double*[3];  // system of equations matrix
  double* x_sums = new double[5];  // sums of x^(index)
  double* xy_sums = new double[3];  // sums of x^(index) * y

  // initialize 2D system of equations array
  for (int i = 0; i < 3; i++)
  {
    system[i] = new double[4];  // ax^2 + bx + c = 0
  }

  // initialize x_sums and xy_sums
  for (int i = 0; i < 5; i++)
  {
    x_sums[i] = 0;
  }
  for (int i = 0; i < 3; i++)
  {
    xy_sums[i] = 0;
  }

  // get relevant sums of x powers and x powers multiplied by y
  for (int i = 0; i < x_i.size(); i++)
  {
    for (int power = 0; power < 5; power++)  // x^(index)
    {
      x_sums[power] += pow(x_i[i], power);
    }
    for (int power = 0; power < 3; power++)  // x^(index) * y
    {
      xy_sums[power] += pow(x_i[i], power) * y_i[i];
    }
  }

  // put coefficients and constants of system of equations in array
  for (int i = 0; i < 3; i++)
  {
    system[i][3] = xy_sums[i];  // constants of system of equations
    for (int j = 0; j < 3; j++)
    {
      system[i][j] = x_sums[i + (2 - j)];  // coefficients a, b, c
    }
  }

  return system;
}

/**
 * This function implements Gaussian elimination on a system of
 * equations. 
 */
// TODO: add Gauss elimination function

int main()
{
  // for parsing x-y coordinate file
  vector<double> x_i;  // x-coordinates
  vector<double> y_i;  // y-coordinates

  string filename = validate_filename();  // get filename from user
  read_xy_file(filename, x_i, y_i);  // read from xy file to vectors
  double** system = system_of_equations(x_i, y_i); 
  
  return 0;
}
