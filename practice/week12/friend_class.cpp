#include <iostream>
using namespace std;

class A {
  public:
  friend class B; // B는 A의 프렌드가 된다.
  A(string s = "") : secret{s} { }
  private:
  string secret; // B는 여기에 접근할 수 있다.
};

class B {
  public:
  B() { }
  void print(A obj) {
    cout << obj.secret << endl;
  }
};

int main()
{
  A a("이것은 기밀 정보입니다.");
  B b;
  b.print(a);
  return 0;
}
// 프렌드 함수는 두 개의 객체를 비교할 때 많이 사용된다.(비대칭)