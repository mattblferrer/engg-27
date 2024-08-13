/**
 * main.cpp
 * 
 * BERNARDO, Jonathan
 * FERRER, Matt
 * 
 * ENGG 27 - M
*/

#include <cmath>
#include <iostream> 

using namespace std;

/**
 * Returns the maximum value that can be stored in a double.
*/
double maximum()
{
  double result = 1.0;
  double inf_test = 1.0;  // to test if infinite
  bool isInfinite = false;

  // find largest bit (rough magnitude) of maximum value by iteration
  while(!isInfinite)
  {
    result = inf_test;
    inf_test = result * 2;
    
    if(isinf(inf_test))  // if largest bit found
    {
      isInfinite = true;
    }
  }

  // test smaller powers of 2 until maximum value is found
  double power_of_two = result / 2;
  inf_test = result;  // reset infinite test variable

  while(power_of_two != 0)
  {
    result = inf_test;
    inf_test = result + power_of_two;

    if(isinf(inf_test))
    {
      inf_test = result;  // reset infinite test variable
      power_of_two = power_of_two / 2;  // move to next power of 2
    }
    else if(result == inf_test)  // if equal, then lost precision
    {
      return result;
    }
  }
}

/**
 * Returns the minimum value that can be stored in a double.
*/
double minimum()
{
  double result = 1.0;

  return result;
}

int main()
{
  cout << maximum() << endl;

  return 0;
}
