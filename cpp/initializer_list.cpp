#include <iostream>
#include <map>
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

class B
{
public:
  int x_;
  A a_;

  B(int a, A& obj):x_(a), a_(obj)
  {
    cout << "Inside B constructor" << endl;
  }
};

class C
{
public:
  int x_;
  A a_;

  C(int a, A& obj)
  {
    x_= (a);
    a_= (obj);
    cout << "Inside B constructor" << endl;
  }
};

int main()
{
  A a;
  cout << endl;

  B b(10, a); //This will only call copy constructor of A.
  cout << endl;

  C c(10, a);//This will only call constructor and assignment operator of A.
  cout << "done" << endl;
  
}


