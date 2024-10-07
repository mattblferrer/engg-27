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
      cout << "\nFile " << filename << " successfully read." << endl;
      return filename;
    }

    // if invalid filename, repeat input sequence
    cout << "\nThere was a problem opening the file." << endl;
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
      cout << "\nNo x-value found in line " << lines_read + 1 << 
        "." << endl;
      break;
    }
    if (!(stream >> y))  // no y value found in line
    {
      cout << "\nNo y-value found in line " << lines_read + 1 << 
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
 * equations defined by a 2D matrix system. It returns a double array
 * which represents the coefficients of the solution. 
 */
double** gaussian_elimination(double** system, int max_row, 
                              int max_column)
{
  int row = 0;  // row of current pivot
  int column = 0;  // column of current 

  // convert matrix to row-echelon form
  while ((row < max_row) && (column < max_column))
  {
    // find pivot for current column
    int pivot = 0;
    double max_leading = 0;  // maximum leading coefficient in row
    for (int i = row; i < max_row; i++)
    {
      double leading = abs(system[i][column]);
      if (leading > max_leading) 
      {
        max_leading = leading;
        pivot = i;
      }
    }

    // check if need to pivot
    if (system[pivot][column] == 0)  // no need to pivot if leading 0
    {
      column++;
      continue;
    }

    // swap pivot row with current row
    double* temp = system[pivot];
    system[pivot] = system[row];
    system[row] = temp;

    // eliminate from all rows below pivot row
    for (int i = row + 1; i < max_row; i++)
    {
      double elim = system[i][column] / system[row][column];
      system[i][column] = 0;
      for (int j = column + 1; j < max_column; j++)
      {
        system[i][j] -= system[row][j] * elim;
      }
    }
    row++;
    column++;
  }

  // perform back substitution on row-echelon matrix 
  for (int i = max_row - 1; i >= 0; i--)
  {
    // express each row in terms of unknown variable in row
    system[i][max_column - 1] /= system[i][i];
    system[i][i] = 1;
    for (int j = i + 1; j < max_column - 1; j++)
    {
      system[i][j] = 0;
    }

    if (i == 0)  // if first row, no need to back substitute
    {
      continue;
    }

    // substitute on row above
    for (int j = i; j < max_column - 1; j++)
    {
      double subst = system[j][max_column - 1] * system[i - 1][j];
      system[i - 1][max_column - 1] -= subst;
      system[i - 1][j] = 0;
    }
  }

  return system;
}

/**
 * This function prints the equation of the best-fit parabola to
 * the given points. 
 */
void format_parabola(double** coordinates)
{
  // print out coefficients of parabola
  cout << "\nThe equation of the best-fit parabola is: " << endl;
  cout << coordinates[0][3] << "x^2";
  if (coordinates[1][3] < 0)  // negative x coefficient
  {
    cout << " - " << abs(coordinates[1][3]) << "x";
  }
  else if (coordinates[1][3] > 0)  // positive x coefficient
  {
    cout << " + " << coordinates[1][3] << "x";
  }
  if (coordinates[2][3] < 0)  // negative constant
  {
    cout << " - " << abs(coordinates[2][3]);
  }
  else if (coordinates[2][3] > 0)  // positive constant
  {
    cout << " + " << coordinates[2][3];
  }
}

int main()
{
  // for parsing x-y coordinate file
  vector<double> x_i;  // x-coordinates
  vector<double> y_i;  // y-coordinates

  cout << "Parabolic Fit" << endl;
  cout << "Ferrer, Bernardo\n" << endl;

  string filename = validate_filename();  // get filename from user
  read_xy_file(filename, x_i, y_i);  // read from xy file to vectors
  double** system = system_of_equations(x_i, y_i);  
  double** coordinates = gaussian_elimination(system, 3, 4);
  format_parabola(coordinates);

  return 0;
}
