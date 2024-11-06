#include <vector>
#include <iostream>
using namespace std;

int main(void) {
  vector<int> v;
  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
  }

  cout << "현재의 v = ";
  for (auto& e : v)
    cout << e << " ";
  cout << endl;

  cout << "삭제 요소 = ";
  // 벡처가 공백이 될 때까지 pop_back() 호출
  while (v.empty() != true) {
    cout << v.back() << " ";
    v.pop_back();
  }
  cout << endl;
  return 0;
}