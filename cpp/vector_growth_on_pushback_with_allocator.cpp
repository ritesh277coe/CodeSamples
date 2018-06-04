#include <iostream>
#include <vector>

/*
  for custom allocator
*/
#include <map>
#include <set>
#include <stdlib.h>
#include <vector>
#include <memory>
#include <limits>

using namespace std;

template <class T>
class MyAlloc {
public:
  // type definitions
  typedef T        value_type;
  typedef T*       pointer;
  typedef const T* const_pointer;
  typedef T&       reference;
  typedef const T& const_reference;
  typedef std::size_t    size_type;
  typedef std::ptrdiff_t difference_type;

  // rebind allocator to type U
  template <class U>
  struct rebind {
    typedef MyAlloc<U> other;
  };

  // return address of values
  pointer address (reference value) const {
    return &value;
  }
  const_pointer address (const_reference value) const {
    return &value;
  }

  /* constructors and destructor
   * - nothing to do because the allocator has no state
   */
    MyAlloc() throw() {
  }
  MyAlloc(const MyAlloc&) throw() {
  }
  template <class U>
  MyAlloc (const MyAlloc<U>&) throw() {
  }
  ~MyAlloc() throw() {
  }

  // return maximum number of elements that can be allocated
  size_type max_size () const throw() {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
  }

  // allocate but don't initialize num elements of type T
  pointer allocate (size_type num, const void* = 0) {
    // print message and allocate memory with global new
    std::cerr << "allocate " << num << " element(s)"
	      << " of size " << sizeof(T) << std::endl;
    pointer ret = (pointer)(::operator new(num*sizeof(T)));
    std::cerr << " allocated at: " << (void*)ret << std::endl;
    return ret;
  }
  
   // initialize elements of allocated storage p with value value
  void construct (pointer p, const T& value) {
    // initialize memory with placement new
    new((void*)p)T(value);
  }

  // destroy elements of initialized storage p
  void destroy (pointer p) {
    // destroy objects by calling their destructor
    p->~T();
  }

  // deallocate storage p of deleted elements
  void deallocate (pointer p, size_type num) {
    // print message and deallocate memory with global delete
    std::cerr << "deallocate " << num << " element(s)"
	      << " of size " << sizeof(T)
	      << " at: " << (void*)p << std::endl;
    ::operator delete((void*)p);
  }
};

// return that all specializations of this allocator are interchangeable
template <class T1, class T2>
bool operator== (const MyAlloc<T1>&,
		 const MyAlloc<T2>&) throw() {
  return true;
}

template <class T1, class T2>
bool operator!= (const MyAlloc<T1>&,
		 const MyAlloc<T2>&) throw() {
  return false;
}

class A
{
public:
  static int c_;
  int m_;

  A() {
    c_++;
    m_= c_;
    //cout << "Inside constructor A " << c_ << " " << m_ << endl;
    cout << "Inside constructor A " << m_ << endl;
  }
  
  A(const A& a) {
    c_++;
    m_ = a.m_;
    //cout << "Inside copy constructor A " << c_ << " " << m_ << endl;
    cout << "Inside copy constructor A " << m_ << endl;
  }
  
  ~A() {
    c_--; 
    //cout << "Inside destructor A " << c_ << " " << m_ << endl;
    cout << "Inside destructor A " << m_ << endl;
  }

  A& operator=(const A& a)
  {
    cout << "Inside assignment" << endl;
  }

  bool operator== (const A& rhs) const
  {
    return this->m_ == rhs.m_;
  }

  bool operator< (const A& rhs) const
  {
    return !(this->m_ < rhs.m_);
  }

  bool operator> (const A& rhs) const
  {
    return !(*this < rhs);
  }

  bool operator!= (const A& rhs) const
  {
    return !(*this == rhs);
  }
};

int A::c_ = 0;

#define NUM 10

int main()
{
  A a[NUM]; //Will call constructor of A NUM times
  
  vector <A, MyAlloc<A> > vec; //Will call constructor of vector

  for (int i = 0; i < NUM; i++) {
    //if mem is not enough, alloc sizeof(A)*i*[2 or 1.5} factor. 
    //Call copy constructor of A to copy a[i] into vector. 
    //Copy all i-1 elements by calling there copy constructors. 
    //Then delete all i-1 elements by callin there destructors. Dealloc the old memory that was holding i-1 elements. 

    //Memory allocation pattern 1, 2, 3, 4, 8, 16, 32, 64, 128....

    //So for copying 5, 6, 7, 8, only copy constructor will be called, but for 9th element, All the above mentioned steps will be followed.
    //10, 11, 12, 13, 14, 15, 16 will only call copy constructor, and reallocation+moving of elemnets will ocuur at 17th insertion.
    vec.push_back( a[i]);
    cout << endl;
  }

  //Will call vector destructor
  //Will call constructor of A NUM times

  return 0;
}
