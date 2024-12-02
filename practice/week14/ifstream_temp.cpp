#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  ifstream is("temp.txt");
  if (!is)
  {
    cerr << "파일 오픈에 실패하였습니다" << endl;
    exit(1);
  }

  int hour;
  double temperature;

  while (is >> hour >> temperature)
  { // 첫 번째 >> 더 이상 읽을 수 없을 때 or 읽기에 실패했을 때 false 반환
    cout << hour << "시: 온도 " << temperature << endl;
  }
  return 0;
}