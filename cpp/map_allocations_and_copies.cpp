#include <iostream>
#include <map>

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

class B
{
public:
  static int c_;
  int m_;


  B() {
    c_++;
    m_= c_;
    //cout << "Inside constructor B " << c_ << " " << m_ << endl;
    cout << "Inside constructor B " << m_ << endl;
  }
  
  B(const B& a) {
    c_++;
    m_ = a.m_;
    //cout << "Inside copy constructor B " << c_ << " " << m_ << endl;
    cout << "Inside copy constructor B " << m_ << endl;
  }
  
  ~B() {
    c_--; 
    //cout << "Inside destructor B " << c_ << " " << m_ << endl;
    cout << "Inside destructor B " << m_ << endl;
  }

  B& operator=(const B& a)
  {
    cout << "Inside assignment" << endl;
  }

  bool operator== (const B& rhs) const
  {
    return this->m_ == rhs.m_;
  }

  bool operator< (const B& rhs) const
  {
    return !(this->m_ < rhs.m_);
  }

  bool operator> (const B& rhs) const
  {
    return !(*this < rhs);
  }

  bool operator!= (const B& rhs) const
  {
    return !(*this == rhs);
  }
};

int A::c_ = 0;
int B::c_ = 0;

#define NUM 10

struct MyCmp
{
  MyCmp()
  {
    cout << "Inside default MyComp constructor\n";
  }

  bool operator() (const A& lhs, const A&rhs)
  {
    return (lhs > rhs);
  }
};

int main()
{
  /*
    STL code typedefs helpful while reading the stl map code
    typedef _Key                                          key_type;
    typedef _Tp                                           mapped_type;
    typedef std::pair<const _Key, _Tp>                    value_type; /This is important as key type is the Ky class, but value type is not the mapped type, but pair of key, value, and that is why map[] operator return  "return (*__i).second;"
    typedef _Compare                                      key_compare;
    typedef _Alloc                                        allocator_type;
  */

  A a1[NUM];
  B b1[NUM];
  
  A a9 = a1[9];
  A a8 = a1[8];
  B b9 = b1[9];
  B b8 = b1[8];
  
  cout << "*********************\n";
  map <A, B, MyCmp, MyAlloc< pair<A, B> > > m;
  m[a8] = b8;
  cout << "*********************\n";
  m[a9] = b9;
  cout << "*********************\n";
  cout << "DONE !!"<< endl;

}
