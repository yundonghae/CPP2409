#include <iostream>
#include <fstream> // 파일 스트림을 위한 헤더
using namespace std;

int main()
{
  ifstream is{"numbers.txt"};
  if (!is)
  {
    cerr << "파일 오픈에 실패하였습니다" << endl;
  }
  int number;
  while (is)
  {
    is >> number;
    cout << number << " ";
  }
  cout << endl;
  return 0;
}