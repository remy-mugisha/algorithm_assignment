#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;

// Making a node struct containing a data int and a pointer
// to another node
//our structure will contain an integer data and pointer
// knot is presenting node in this structure 
struct knot {
  int data;
  struct knot *next;
};

class LinkedList {
  //this is Head pointer
  knot * head;
  // this is TAIL pointer
  knot * tail;
  void updateTail() {
    // check a condition , if head is null set that the tail to null also
    if (head == NULL) {
      tail = NULL;
      return;
    }
    knot * temp = head;
    
    //  Else traverse till you reach to the last node
    while (temp -> next != NULL) {
      temp = temp -> next;
    }
    //  Assigning the last node to tail
    tail = temp;
    return;
  }

  public:
    // default constructor.lets Initializing head pointer
    LinkedList() {
      head = NULL;
      tail = NULL;
    }
  LinkedList(int size) {
    // Seed srand with random numbers
    srand(time(0));
    for (int i = 0; i < size; i++)
      // Add random numbers into our linked list
      insertAtBeginning(rand());
  }
  //This is Copy constructor
  LinkedList(const LinkedList & l1) {
    head = l1.head;
    tail = l1.tail;
  }
  // Desctructor
  ~LinkedList() {
    knot * current = head;
    while (current != 0) {
      knot * next = current -> next;
      delete current;
      current = next;
    }
    head = NULL;
  } 
  void operator = (const LinkedList & l) {
    head = l.head;
    tail = l.tail;
  }
  // Return the head of the linked list
  knot * getHead() {
    return head;
  }
  // Return tail of the linked list
  knot *getTail() {
    if (tail == NULL) 
       return NULL;
    return tail;
  }
  // inserting elements (At start of the list)
  void insertAtBeginning(int num) {
    // make a new node
    knot * new_node = new knot;
    new_node -> data = num;
    new_node -> next = NULL;

    // If list is empty, make the new node, the head
    if (head == NULL) head = new_node;

    // else, make the new_node the head and its next, the previous
    // head
    else {
      new_node -> next = head;
      head = new_node;
    }
    this -> updateTail();
  }

  // inserting elements (At the end of the list)
  void insertAtEnd(int num) {
    // make a new node
    knot * new_node = new knot;
    new_node -> data = num;
    new_node -> next = NULL;

    // If list is empty, make the new node, the head
    if (head == NULL) head = new_node;

    // else, make the new_node the head and its next, the previous
    // head
    else {
      tail -> next = new_node;
      tail = new_node;
    }
    //      this->printTail();
  }
  // loop over the list. return true if element found
  bool search(int num) {
    knot * temp = head;
    while (temp != NULL) {
      if (temp -> data == num) return true;
      temp = temp -> next;
    }
    return false;
  }

  void remove(int num) {
    // If the head is to be deleted
    if (head -> data == num) {
      delete head;
      head = head -> next;
      return;
    }

    // If there is only one element in the list
    if (head -> next == NULL) {
      // If the head is to be deleted. Assign null to the head
      if (head -> data == num) {
        delete head;
        head = NULL;
        return;
      }
      // else print, value not found
      cout << "Value not found!" << endl;
      return;
    }

    // Else loop over the list and search for the node to delete
    knot * temp = head;
    while (temp -> next != NULL) {
      // When node is found, delete the node and modify the pointers
      if (temp -> next -> data == num) {
        knot * temp_ptr = temp -> next -> next;
        delete temp -> next;
        temp -> next = temp_ptr;
        return;
      }
      temp = temp -> next;
    }
    // Else, the value is not in the list
    cout << "Value not found" << endl;
  }

  void display() {
    knot * temp = head;
    while (temp != NULL) {
      cout << temp -> data << " ";
      temp = temp -> next;
    }
    cout << endl;
  }

  /* the Function will be used to reverse the nodes in a linked list. */
  void reverse() {
    if (head == NULL) return;

    knot * prev = NULL, * current = NULL, * next = NULL;
    current = head;
    while (current != NULL) {
      next = current -> next;
      current -> next = prev;
      prev = current;
      current = next;
    }
    // now let the head point at the last node (previous)
    head = prev;
  }
  //This is Function
  void removeDuplicate() {
    this -> selectionSort();
    // temp pointing to head
    knot * temp = head;
    while (temp -> next != NULL && temp != NULL) {
      // Duplication detected 
      if (temp -> data == temp -> next -> data) {
        // TO remove any duplication
        temp -> next = temp -> next -> next;
      } else {
        // No Duplicate available
        temp = temp -> next;
      }
    }
  }

  void selectionSort() {
    knot * temp = head;

    // Traverse the List
    while (temp) {
     knot * min = temp;
     knot * r = temp -> next;

      //Here we are going to Traverse the unsorted sublist
      while (r) {
        if (min -> data > r -> data) min = r;
        r = r -> next;
      }

      // Swapping  Data
      int x = temp -> data;
      temp -> data = min -> data;
      min -> data = x;
      temp = temp -> next;
    }
  }
};

int main() {
  LinkedList l(4);
  LinkedList l2 = l;
  cout << "Displaying l2:";

  l2.display();
  cout << l2.getHead() -> data;
  // inserting elements in linked list
  l.insertAtBeginning(6);
  l.insertAtBeginning(9);
  l.insertAtBeginning(1);
  l.insertAtEnd(3);
  l.insertAtBeginning(7);
  l.insertAtBeginning(9);
  l.insertAtEnd(32);
  cout << "Current Linked List: ";
  l2.display();
  
  cout << "Deleting 1: ";
  l.remove(1);
  l.display();
  cout << "Reversed linked list \t";
  l.reverse();
  l.display();
  cout << "Deleting 13: ";
  l.remove(13);

  cout << "Searching for 7: ";
  cout << l.search(7) << endl;
  //  l.selectionSort();
  //  l.removeDuplicate();
  cout << "Displaying l:";
  l.display();
  l2 = l;
  cout << "Displaying l2:";
  l2.display();
  cout << l.getHead() -> data << endl;
  cout << "Searching for 13: ";
  cout << l.search(13) << endl;

}
