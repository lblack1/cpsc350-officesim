#include "Student.h"
#include <iostream>

using namespace std;

/* The constructor. Sets members as specified.
* @param int arrTime: the time at which a student will be placed in the waiting queue.
* @param int busTime: the amount of time a student will take at a window once removed from the waiting queue.
*/
Student::Student(int arrTime, int busTime) {
  arrivalTime = arrTime;
  busyTime = busTime;
  waitTime = 0;
}
