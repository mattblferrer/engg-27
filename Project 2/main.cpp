/**
 * main.cpp
 * 
 * BERNARDO, Jonathan
 * FERRER, Matt
 * 
 * Project 2 - Parabolic Fit
 * ENGG 27 - M
*/

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
void read_xy_file(string filename, vector<int>& x_i, 
  vector<int>& y_i)
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
// TODO: add systems of equations function

/**
 * This function implements Gaussian elimination on a system of
 * equations. 
 */
// TODO: add Gauss elimination function

int main()
{
  // for parsing x-y coordinate file
  vector<int> x_i;  // x-coordinates
  vector<int> y_i;  // y-coordinates

  string filename = validate_filename();  // get filename from user
  read_xy_file(filename, x_i, y_i);  // read from xy file to vectors
  
  return 0;
}
