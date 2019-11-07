#ifndef STUDENT
#define STUDENT

#include <iostream>

using namespace std;

/* A basic student class for keeping track of wait time, along with a couple other housekeeping members. Might as well be a struct.
*/
class Student {

  public:
    int waitTime;
    int arrivalTime;
    int busyTime;

    Student(int arrTime, int busTime);

};

#endif
