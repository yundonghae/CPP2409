#include <iostream>
#include <fstream> // 파일스트림을 위한 헤더
using namespace std;

int main()
{ // 파일의 출력 스트림 생성 및 초기화
  ofstream os{"numbers.txt"};
  if (!os)
  {
    cerr << "파일 오픈에 실패하였습니다" << endl;
    exit(1);
  }
  for (int i = 0; i < 100; i++)
    os << i << " "; // 파일에 데이터 출력
  return 0;
}