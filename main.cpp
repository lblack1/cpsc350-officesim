#include "Simulation.h"
#include "Student.h"
#include "Window.h"

#include "DLQueue.h"
#include "DLL.h"
#include "Node.h"

#include "ListEmptyException.h"
#include "IndexOutOfBoundsException.h"
#include "FileNotFoundException.h"


#include <iostream>
#include <fstream>

using namespace std;

/* Takes the first command line argument as a file name and runs a simulation per the assignment specifications.
*/
int main(int argc, char** argv) {

  string fileName = argv[1];

  try {
    Simulation* sim = new Simulation(fileName);
    sim->runSim();
  } catch (FileNotFoundException e){
    cout << "No file with the path \"" << fileName << "\" was found. Please check inputted path and try again." << endl;
  } catch (invalid_argument e) {
    if (e.what() == "stoi") {
      cout << "Invalid file format." << endl;
    }
    cout << e.what() << endl;
  }

}
