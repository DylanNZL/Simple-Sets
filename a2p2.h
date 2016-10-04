#ifndef A2P2_H
#define A2P2_H
#include <exception>
#include <iostream>
using namespace std;
//========part a-Comments here:
/*
 *  Assignment 2 Part One for 159.234
 *  Dylan Cross - 15219491
 */
//========part b-author's details
void info() {
    std::cout << "***************************" << std::endl;
    std::cout << "* Assignment 2 - Part Two *" << std::endl;
    std::cout << "* Dylan Cross    15219491 *" << std::endl;
    std::cout << "*       159.234 OOP       *" << std::endl;
    std::cout << "***************************" << std::endl;
    std::cout << std::endl;
}
//========part c-exception classes:

class RemoveFromEmpty : exception {
public:
    RemoveFromEmpty() {
      mMessage = "Empty set exception thrown";
    }
    ~RemoveFromEmpty() _NOEXCEPT {}
    const char* what() const _NOEXCEPT {
       return "Empty set exception thrown";
    }

private:
    string mMessage;
};

class NonExistingElem : exception {
public:
// to be thrown  when the element to be removed is not found in the set
    NonExistingElem() {
      mMessage = "Element doesn't exist excpetion thrown";
    }
    ~NonExistingElem() _NOEXCEPT {}
    const char* what() const _NOEXCEPT {
      return "Element doesn't exist excpetion thrown";
    }
private:
    string mMessage;
};
//========part d-Set class template
template <typename EType>
class Set {
public:
//constructors
    Set( );
    Set( const Set & rhs );
    Set( Set && rhs );
//destructor
    ~Set( );
//operators overloaded
    Set & operator=( const Set & rhs );
    Set & operator=( Set && rhs );
    Set operator+( const Set & rhs ) const; //set union
    Set operator*( const Set & rhs ) const; //set intersection
//methods
    bool isElement( const EType & x ) const;
    bool isEmpty( ) const;
    int getSize( ) const;
//display on out all elements in the set between {..}
    void print( ostream & out = cout ) const;
    void setToEmptySet( );
//methods to work with individual elements of a set
    void insert( const EType & x );
    void remove( const EType & x );
private:
    struct Node{// type of the elements of the set
      EType mData;
      Node *mNext;
      Node( const EType & d = EType( ), Node *n = nullptr ) : mData( d ), mNext( n ) { }
    };
    Node *mFirst;
    int mSize;   // to have an efficient getSize().
};

//Write the definitions of all Set function members here:
//======== part e-the output operator:
/* Constructor for emtpy set */
template <typename EType>
Set<EType>::Set( ) {
  mFirst = nullptr;
  mSize = 0;
}

/* Copy Constructor */
template <typename EType>
Set<EType>::Set( const Set<EType> & rhs ) {

}

/* Move Constructor */
template <typename EType>
Set<EType>::Set( Set<EType> && rhs ) {
  setToEmptySet();
  mFirst = rhs.mFirst;
  rhs.mFirst = nullptr;
  mSize = rhs.mSize;
  rhs.mSize = 0;
}

/* Destructor */
template <typename EType>
Set<EType>::~Set( ) {
  Node *ptr = mFirst;
  while (ptr != nullptr) {
    ptr->mData = NULL;
    Node *next = ptr->mNext;
    ptr->mNext = nullptr;
    ptr = next;
  }
}

/* Copy Assignement Operator */
template <typename EType>
Set<EType> & Set<EType>::operator=( const Set<EType> & rhs) {

}

/* Move Assignement Operator */
template <typename EType>
Set<EType> & Set<EType>::operator=( Set<EType> && rhs) {

}

/* Union */
template <typename EType>
Set<EType> Set<EType>::operator+( const Set<EType> & rhs ) const{
 std::cout << rhs.mFirst << " " << mFirst << endl;
}

/* intersection */
template <typename EType>
Set<EType> Set<EType>::operator*( const Set<EType> & rhs ) const{

}

/* Print Function
 * Prints out the set objects value
 */
template <typename EType>
void Set<EType>::print( ostream & out ) const {
  cout << "{ ";
  Node *ptr = mFirst;
  while (ptr != nullptr) {
    cout << ptr->mData << ' ';
    ptr = ptr->mNext;
  }
  cout << '}';
}

/* Is element method
 * Checks if x is already in the set.
 */
template <typename EType>
bool Set<EType>::isElement( const EType & x ) const {
  Node *ptr = mFirst;
  while (ptr != nullptr) {
    if (ptr->mData == x) {
      return true;
    }
    ptr = ptr->mNext;
  }
  return false;
}
/* Is Empty method
 * Checks if a set is empty or not
 */
template <typename EType>
bool Set<EType>::isEmpty( ) const {
  if (mSize == 0) {
    return true;
  }
  return false;
}
/* Get Size method
 * Returns the mSize data member of Set.
 */
template <typename EType>
int Set<EType>::getSize( ) const {
  return mSize;
}
/* Set to empty Function
 * Takes a Set and sets it to an empty set
 */
template <typename EType>
void Set<EType>::setToEmptySet() {
  Node *ptr = mFirst;
  mFirst = nullptr;
  while (ptr != nullptr) {
    Node *next = ptr->mNext;
    ptr->mData = NULL;
    ptr->mNext = nullptr;
    ptr = next;
  }
  mSize = 0;
}

/* Insert Function */
template <typename EType>
void Set<EType>::insert( const EType & x ) {
  if (isElement(x)) {
    // Exception?
  } else {
    Node* node = new Node(x, mFirst);
    mFirst = node;
    mSize++;
  }
}

/* Remove Function
 * Takes in a value and a set and removes that value from the set.
 * If the function is called on an empty array it will throw a RemoveFromEmpty exception
 * If nothing is deleted the function will throw a NonExistingElem exception
 * Otherwise the node that has that value is removed from the list and the preceding
 *      Nodes mNext pointer is changed to the deleted nodes mNext.
 */
template <typename EType>
void Set<EType>::remove( const EType & x ) {
  Node *ptr = mFirst;
  bool deleted = false;
  if (mSize == 0) {
    throw new RemoveFromEmpty();
  } else if (ptr->mData == x) {
    // delete ptr
    mFirst = ptr->mNext;
    //ptr->mData = NULL;
    ptr = nullptr;
    deleted = true;
    mSize--;
  } else {
    Node *nextPtr = ptr->mNext;
    while (nextPtr != nullptr) {
      if (nextPtr->mData == x) {
        // delete nextPtr
        Node *next = nextPtr->mNext;
        ptr->mNext = next;
        //nextPtr->mData = NULL;
        nextPtr->mNext = nullptr;
        deleted = true;
        mSize--;
        break;
      } else {
        // Move to next Node.
        ptr = ptr->mNext;
        nextPtr = nextPtr->mNext;
      }
    }
    if (!deleted) {
      throw new NonExistingElem();
    }
  }
}

/* Output operator that redirects to the print function in the Set class */
template <typename EType>
ostream & operator<< (ostream &out, const Set<EType> &set) {
  set.print(out);
  return out;
}
#endif
