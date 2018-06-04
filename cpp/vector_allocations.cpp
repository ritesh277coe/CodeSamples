//Compile with: g++ -ggdb -O0 vector_growth_on_pushback.cpp -o v
#include <iostream>
#include <vector>

using namespace std;

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
  
  vector <A> vec; //Will call constructor of vector

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
