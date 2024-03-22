#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
*
* double-linked, double-ended list with Iterator interface
* EECS 280 Project 4
*/

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert> //assert

template <typename T>
class List
{
  friend class Iterator;
  // OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  // EFFECTS: returns true if the list is empty
  bool empty() const
  {
    return first == nullptr;
  }

  // EFFECTS: returns the number of elements in this List
  // HINT: Traversing a list is really slow. Instead, keep track of the size
  // with a private member variable. That's how std::list does it.
  int size() const
  {
    return track;
  }

  // REQUIREMENTS: list is not empty
  // EFFECTS: Returns the first element in the list by reference
  T &front()
  {
    return first->datum;
  }

  // REQUIREMENTS: list is not empty
  // EFFECTS: Returns the last element in the list by reference
  T &back()
  {
    return last->datum;
  }

  // EFFECTS: inserts datum into the front of the list
  void push_front(const T &datum)
  {
    Node *newNode = new Node;
    newNode->datum = datum;
    newNode->prev = nullptr;
    if (empty())
    {
      first = last = newNode;
    }
    else
    {
      first->prev = newNode;
      newNode->next = first;
      first = newNode;
    }
    track++;
  }

  // EFFECTS: inserts datum into the back of the list
  void push_back(const T &datum)
  {
    Node *newNode = new Node;
    newNode->datum = datum;
    newNode->next = nullptr;
    if (empty())
    {
      first = last = newNode;
    }
    else
    {
      last->next = newNode;
      newNode->prev = last;
      last = newNode;
    }
    track++;
  }

  // REQUIREMENTS: list is not empty
  // MODIFIES: may invalidate list iterators
  // EFFECTS: removes the item at the front of the list
  void pop_front()
  {
    if (first == last)
    {
      //deletefirst;
      first = last = nullptr;
    }
    else
    {
      Node *nextFirst = first->next;
      //deletefirst;
      first = nextFirst;
      if (first){
      first->prev = nullptr;
      }
    }
    track--;
  }

  // REQUIREMENTS: list is not empty
  // MODIFIES: may invalidate list iterators
  // EFFECTS: removes the item at the back of the list
  void pop_back()
  {
    if (size() == 1)
    {
      delete last;
      first = last = nullptr;
    }
    else
    {
      Node *prevLast = last->prev;
      prevLast->next = nullptr;
      delete last;
      last = prevLast;
    }
    track--;
  }

  // MODIFIES: may invalidate list iterators
  // EFFECTS: removes all items from the list
  void clear()
  {
    while (!empty())
    {
      Node* temp = first;
      first = first->next;
      delete temp;
    }
    last = nullptr;
    track = 0;
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. To user
  // of the class must be able to create, copy, assign, and destroy Lists.
  List() : track(0), first(nullptr), last(nullptr){};

  List(const List<T> &other) : track(0), first(nullptr), last(nullptr)
  {
    copy_all(other);
  }

  ~List()
  {
    clear();
  }

  List<T> &operator=(const List<T> &other)
  {
    if (this != &other)
    {
      clear();
      copy_all(other);
    }
    return *this;
  }

// begin and end access private variables from List
// we need to add friend so that this operator has access as well
friend bool operator==(const List<T>& lhs, const List<T>& rhs) {
    if (lhs.size() != rhs.size()) {
    return false;
  }

  auto it1 = lhs.begin();
  auto it2 = rhs.begin();
  while (it1 != lhs.end()) {
    if (*it1 != *it2) {
  return false;
  }
  ++it1;
  ++it2;
  }
  return true;
}

private:
  // to private type
  int track;

  struct Node
  {
    Node *next;
    Node *prev;
    T datum;
  };

  // REQUIREMENTS: list is empty
  // EFFECTS: copies all nodes from other to this
  void copy_all(const List<T> &other)
  {
    clear();
    for (Node *p = other.first; p != nullptr; p = p->next)
    {
      push_back(p->datum);
    }
  }

  Node *first; // points to first Node in list, or nullptr if list is empty
  Node *last; // points to last Node in list, or nullptr if list is empty

public:
  /////////////////////////////////////////
  class Iterator
  {
    // OVERVIEW: Iterator interface to List

    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. To user
    // of the class must be able to copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    // iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    // compare equal
    // - two iterators to different locations in the same list must
    // compare unequal
    // - comparing iterators obtained from different lists results in
    // undefined behavior
    // - Your implementation can handle this however you like, but
    // don't assume any particular behavior in your test cases --
    // comparing iterators from different lists essentially
    // violates the REQUIRES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.

  public:
    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is either dereferenceable or an end Iterator
    // EFFECTS: moves this Iterator to point to the previous element
    // and returns a reference to this Iterator
    Iterator &operator--()
    { // prefix -- (eg --it)
      assert(list_ptr);
      if (node_ptr)
      {
        node_ptr = node_ptr->prev;
      }
      else
      { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is either dereferenceable or an end Iterator
    // EFFECTS: moves this Iterator to point to the previous element
    // and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/)
    { // postfix -- (eg it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    // member variable f, then it->f accesses f on the
    // underlying T element.
    T *operator->() const
    {
      return &operator*();
    }

    // post
    Iterator &operator++()
    {
      if (node_ptr)
      {
        node_ptr = node_ptr->next;
      }
      return *this;
    }

    // changes object index but return original
    Iterator operator++(int /*postfix*/)
    {
      Iterator copy = *this;
      if (node_ptr)
      {
        node_ptr = node_ptr->next;
      }
      return copy;
    }

    T &operator*() const
    {
      return node_ptr->datum;
    }

    Iterator() : list_ptr(nullptr), node_ptr(nullptr) {}

    Iterator(const Iterator &other) :
    list_ptr(other.list_ptr), node_ptr(other.node_ptr) {} // here

    Iterator &operator=(const Iterator &other)
    {
      //changed this -> *this
      if (*this != other)
      {
        list_ptr = other.list_ptr;
        node_ptr = other.node_ptr;
      }
      return *this;
    }

    bool operator==(const Iterator &other) const
    {
      return list_ptr == other.list_ptr && node_ptr == other.node_ptr;
    }

    bool operator!=(const Iterator &other) const
    {
      return !(*this == other);
    }

  private:
    const List *list_ptr; // pointer to the List associated with this Iterator
    Node *node_ptr; // current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend List;
    // friend Iterator begin();
    // friend Iterator end();

    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np) : list_ptr(lp), node_ptr(np) {}

  }; // List::Iterator
  /////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const
  {
    return Iterator(this, first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const
  {
    return Iterator(this, last->next);
  }

  // REQUIRES: i is a valid, dereferenceable iterator associated with this list
  // MODIFIES: may invalidate other list iterators
  // EFFECTS: Removes a single element from the list container.
  // Returns An iterator pointing to the element that followed the
  // element erased by the function call
  Iterator erase(Iterator i){

    Node* current = i.node_ptr;
    Iterator next(this, current->next);

    //return end if current is null
    if(!current){
      return next;
    }
    
    // if the previous of current exists
    if (current->prev){
      // the previous's next is the currents next
      current->prev->next = current->next;
    }
    else { // if the previous of current doesnt exist
      // the current's next is the start
      first = current->next;
    }
    
    if (current->next){
      current->next->prev = current->prev;
    }
    else {
      last = current->prev;
    }

    delete current;
    track--;

    return next;

  }

  // REQUIRES: i is a valid iterator associated with this list
  // EFFECTS: Inserts datum before the element at the specified position.
  // Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum){

    Node * current = i.node_ptr;
    
    // check if it's being inserted into the end
    if(!current){
      push_back(datum);
      return Iterator(this, last);
    }

    Node* newNode = new Node;
    newNode->datum = datum;
    newNode->prev = current->prev;
    newNode->next = current;

    // check if node isn't first in list
    if(current->prev){
      current->prev->next = newNode;
    }
    else {
      first = newNode;
    }

    current->prev = newNode;

    track++;
    return Iterator(this, newNode);
  }

}; // List

/////////////////////////////////////////////////// ///////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed. Do add the public member functions for
// Iterator.

//Do not remove this. Write all your code above this line.
#endif 