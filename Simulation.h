#ifndef SIMULATION
#define SIMULATION

#include "Student.h"
#include "Window.h"

#include "Node.h"
#include "DLL.h"
#include "DLQueue.h"

#include "IndexOutOfBoundsException.h"
#include "ListEmptyException.h"
#include "FileNotFoundException.h"

#include <iostream>
#include <fstream>

using namespace std;

/* A class for calculating stats based on student wait times and window idle times as per assignment specs.
*/
class Simulation {

  public:
    int clock;

    Simulation(string fileName);

    void runSim();

  private:
    float mnswt; // mean student wait time
    int medswt; // median student wait time
    int lswt; // longest student wait time
    int tmpswt; // ten minutes plus student wait times
    float mwit; // mean window idle time
    int lwit; // longest window idle time
    int fmpwit; // five minutes plus window idle times

    DLQueue<Student*>* studentQ;
    DLQueue<Window*>* windowQ;

    DLL<Student*>* preStudents;
    DLL< pair<int, pair<Student*, Window*> > >* occupiedPairs; // (busy time, (student, window))
    DLL<Student*>* helpedStudents;

    void calcStats();
    void printStats();

};

#endif
