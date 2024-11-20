#include <iostream>
#include <string>
using namespace std;

class Person {
  string name; // 기본적으로 private
  protected:
  string address;

  public:
  void SetName(string name){ this->name = name; }
};

class Student : public Person {
  public:
  void SetAddress(string add) {
    address = add;
  }
  string GetAddress() {
    return address;
  }
};

int main() {
  Student obj;
  obj.SetName("미수");
  obj.SetAddress("서울시 종로구 1번지");
  cout << obj.GetAddress() << endl;
  return 0;
}
