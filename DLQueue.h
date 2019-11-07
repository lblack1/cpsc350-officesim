#ifndef DL_QUEUE
#define DL_QUEUE

#include "DLL.h"
#include "Node.h"
#include "ListEmptyException.h"
#include "IndexOutOfBoundsException.h"
#include <iostream>

using namespace std;

/* A generic Doubly Linked List-based Queue class.
*/
template <class T>
class DLQueue {

  public:
    DLL<T>* list;

    /* Default constructor. Initializes an empty queue.
    */
    DLQueue() {
      list = new DLL<T>();
    }

    /* Destructor. Empties queue and deletes List.
    */
    ~DLQueue() {
      while (!isEmpty()) {
        remove();
      }
      delete list;
    }

    /* Enqueues specified data.
    * @param T d: datum to be enqueued.
    */
    void insert(T d) {
      list->insertRear(d);
    }
    /* Dequeues first datum in list. Throws ListEmptyException if list is empty.
    * @return T: datum at front of list.
    */
    T remove() {
      return list->removeFront();
    }
    /* Shows first datum in list. Throws ListEmptyException if list is empty.
    * @return T: datum at front of list.
    */
    T peek() {
      return list->peekFront();
    }

    /* Indicates if queue is empty.
    * @return bool: true if empty, false otherwise.
    */
    bool isEmpty() {
      return (size() == 0);
    }
    /* Returns number of elements if queue.
    * @return int: number of elements in queue.
    */
    int size() {
      return list->getCount();
    }

};

#endif
