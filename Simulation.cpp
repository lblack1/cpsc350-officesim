#include "Simulation.h"
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
#include <utility>

using namespace std;

/* The constructor. Initializes all Queues and lists, and creates appropriate number of windows and students according to file.
* @param string fileName: the path of the file to be opened and read, in the format of the assignment specs (assuming you want the program to accomplish its task)
*/
Simulation::Simulation(string fileName) {

  int clock = 0;

  studentQ = new DLQueue<Student*>();
  windowQ = new DLQueue<Window*>();

  preStudents = new DLL<Student*>();
  occupiedPairs = new DLL< pair<int, pair<Student*, Window*> > >();
  helpedStudents = new DLL<Student*>();

  ifstream inFile;
  inFile.open(fileName);
  if (!inFile) {
    throw FileNotFoundException();
  }

  string temp;
  getline(inFile, temp);
  int itemp = stoi(temp);
  if (itemp < 1) {
    throw invalid_argument("All numbers must be greater than 0.");
  }
  for (int i = 0; i < itemp; ++i) {
    windowQ->insert(new Window());
  }

  while (getline(inFile, temp)) { // next clock tick of students
    if (temp == "") {
      continue;
    } else {
      int arrTime = stoi(temp);
      if (arrTime < 0) {
        throw invalid_argument("All numbers must be greater than 0.");
      }
      getline(inFile, temp);
      itemp = stoi(temp); // number of students arriving at next tick
      if (itemp < 0) {
        throw invalid_argument("All numbers must be greater than 0.");
      }
      for (int i = 0; i < itemp; ++i) {
        getline(inFile, temp);
        if (stoi(temp) < 0) {
          throw invalid_argument("All numbers must be greater than 0.");
        }
        preStudents->insertRear(new Student(arrTime, stoi(temp)));
      }
    }
  }

  inFile.close();

}

/* Runs the simulation appropriately. Students placed in queue at their arrival time, idle and wait times updated at each clock tick,
* runs until no students are left in queue or yet to arrive. Then prints the staistics of the simulation.
*/
void Simulation::runSim() {

  while (!studentQ->isEmpty() || !preStudents->isEmpty()) {

    for (int i = 0; i < preStudents->getCount(); ++i) { // New students show up
      Student* stu = preStudents->findAtIndex(i)->data;
      if (stu->arrivalTime == clock) {
        studentQ->insert(stu);
        preStudents->removeFirst(stu);
        i--;
      }
    }

    while (!windowQ->isEmpty() && !studentQ->isEmpty()) {
      Student* tempStu = studentQ->remove();
      occupiedPairs->insertFront(pair<int, pair<Student*, Window*>>(tempStu->busyTime, pair<Student*, Window*>(tempStu, windowQ->remove())));
    }

    for (int i = 0; i < windowQ->size(); ++i) {
      windowQ->list->findAtIndex(i)->data->idleTime++;
    }

    for (int i = 0; i < studentQ->size(); ++i) {
      studentQ->list->findAtIndex(i)->data->waitTime++;
    }

    for (int i = 0; i < occupiedPairs->getCount(); ++i) {
      int temp = --get<0>(occupiedPairs->findAtIndex(i)->data);
      if (temp == 0) {
        pair<Student*, Window*> tempPair = get<1>(occupiedPairs->removeAt(i));
        windowQ->insert(get<1>(tempPair));
        helpedStudents->insertRear(get<0>(tempPair));
        i--;
      }
    }

    clock++;
  }
  while (!occupiedPairs->isEmpty()) {
    helpedStudents->insertRear(get<0>(get<1>(occupiedPairs->peekFront())));
    windowQ->insert(get<1>(get<1>(occupiedPairs->removeFront())));
  }
  printStats();
}

/* Calculates mean student wait time, longest student wait time, median student wait time, number of student wait times longer than 10 minutes,
* mean window idle time, longest window idle time, and number of windows idle for longer than 5 minutes.
*/
void Simulation::calcStats() {
  lswt = 0;
  for (int i = 0; i < helpedStudents->getCount(); ++i) {
    int temp = helpedStudents->findAtIndex(i)->data->waitTime;
    mnswt += (float)temp;
    lswt = (temp > lswt) ? temp : lswt;
    tmpswt += (temp > 9) ? 1 : 0;
  }
  mnswt /= (float)helpedStudents->getCount();


  DLL<Student*>* sortedByWaitTime = new DLL<Student*>();
  int tempCounter = 0;
  while (!helpedStudents->isEmpty()) {
    for (int i = 0; i < helpedStudents->getCount(); ++i) {
      if (helpedStudents->findAtIndex(i)->data->waitTime == tempCounter) {
        sortedByWaitTime->insertRear(helpedStudents->removeAt(i--));
      }
    }
    tempCounter++;
  }
  medswt = sortedByWaitTime->findAtIndex(sortedByWaitTime->getCount()/2)->data->waitTime;

  lwit = 0;
  for (int i = 0; i < windowQ->size(); ++i) {
    int temp = windowQ->list->findAtIndex(i)->data->idleTime;
    mwit += (float)temp;
    lwit = (temp > lwit) ? temp : lwit;
    fmpwit += (temp > 4) ? 1 : 0;
  }
  mwit /= (float)windowQ->size();

}

/* Calls calcStats() then prints the stats to cout.
*/
void Simulation::printStats() {
  calcStats();
  cout << endl << "Mean Student Wait Time: " << mnswt << " minutes" << endl;
  cout << "Median Student Wait Time: " << medswt << " minutes" << endl;
  cout << "Longest Student Wait Time: " << lswt << " minutes" << endl;
  cout << "Students with Wait Times Greater than 10 Minutes: " << tmpswt << endl;
  cout << "Mean Window Idle Time: " << mwit << " minutes" << endl;
  cout << "Longest Window Idle Time: " << lwit << " minutes" << endl;
  cout << "Windows with Idle Times Greater than 5 Minutes: " << fmpwit << endl << endl;
}
