#ifndef NODE
#define NODE

#include <cstdlib>

using namespace std;

/* A generic node for a doubly linked list.
*/
template <class T>
class Node
{
  public:
    T data;
    Node* next;
    Node* prev;

    Node() {
      data = NULL;
      next = NULL;
      prev = NULL;
    }
    Node(T d) {
      data = d;
      next = NULL;
      prev = NULL;
    }

};

#endif
