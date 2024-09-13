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

int main()
{
  // for parsing x-y coordinate file
  vector<int> x_i;  // x-coordinates
  vector<int> y_i;  // y-coordinates
  double x = 0;
  double y = 0;
  string filename = validate_filename();  // get filename from user
  ifstream xy_file(filename.c_str());

  while(xy_file.good())  // extract x, y coordinates per line
  {
    xy_file >> x;
    xy_file >> y;
    x_i.push_back(x);
    y_i.push_back(y);
  }
  
  return 0;
}
