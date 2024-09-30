#include <iostream>
#include <string>
using namespace std;

int main() {
    const int maxPeople = 5;
    string names[maxPeople];
    int ages[maxPeople];

    cout << maxPeople << "명의 회원 정보를 입력해주세요." << endl;
    int i = 0;

    while (i < maxPeople) {
        cout << "사람 " << i + 1 << "의 이름: ";
        cin >> names[i];
        cout << "사람 " << i + 1 << "의 나이: ";
        cin >> ages[i];
        ++i;
    }

    int menu;
    cout << "1. 가장 나이가 많은 사람 출력 2. 가장 나이가 적은 사람 출력 3. 종료\n";
    cin >> menu;

    switch(menu) {
        case 1: {
            int maxAge = ages[0];
            int j = 1;

            while (j < maxPeople) {
                if (ages[j] > maxAge) {
                    maxAge = ages[j];
                }
                ++j;
            }

            cout << "가장 나이가 많은 사람(들): ";
            j = 0;
            while (j < maxPeople) {
                if (ages[j] == maxAge) {
                    cout << names[j] << " (" << ages[j] << "세) ";
                }
                ++j;
            }
            cout << endl;
            break;
        }
        case 2: {
            int minAge = ages[0];
            int j = 1;

            while (j < maxPeople) {
                if (ages[j] < minAge) {
                    minAge = ages[j];
                }
                ++j;
            }

            cout << "가장 나이가 적은 사람(들): ";
            j = 0;
            while (j < maxPeople) {
                if (ages[j] == minAge) {
                    cout << names[j] << " (" << ages[j] << "세) ";
                }
                ++j;
            }
            cout << endl;
            break;
        }
        case 3:
            cout << "프로그램을 종료합니다." << endl;
            break;
        default:
            cout << "잘못된 선택입니다." << endl;
            break;
    }

    return 0;
}


