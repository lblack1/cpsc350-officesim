# cpsc350-officesim
Office Sim (Assignment 4)

Lloyd Black
2295968
CPSC350, Section 2
Rene German

A program for running a simulation to keep predict student wait times and window idle times using a custom Doubly Linked List and Queue.

1. Source Files - main.cpp, Node.h, DLL.h, DLQueue.h, Student.h, Student.cpp, Window.h, Window.cpp, Simulation.h, Simulation.cpp, IndexOutOfBoundsException.h, IndexOutOfBoundsException.cpp, FileNotFoundException.h, FileNotFoundException.cpp, ListEmptyException.h, ListEmptyException.cpp

2. Issues - None found in the time I spent doing QA.

3. Resources - cplusplus.com/reference, stackoverflow, tutorialspoint, In-Class guided programming, and Data Structures and Algorithms in C (by Goodrich, Tamassia, and Mount).

4. Description of Program - Takes a file path as a command line argument. Reads that file for the number of windows to open, the clock ticks at which how many students arrive with what amount of time they'll take at a window, and runs a simulation with all the students and windows. Calculates wait and idle time averages and maximums, as well as wait and idle times exceeding a certain threshold, then prints the statistics to the console.

5. After compiling - ./OfficeSimA4.out [TEXT FILE TO READ]
