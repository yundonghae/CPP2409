#include <iostream>
using namespace std;

int main() {
    int a, b, c, largest;

    cout << "3개의 정수를 입력하시오: ";
    cin >> a >> b >> c;

    if (a != b && a != c && b != c) {
        if (a > b && a > c)
            largest = a;
        else if (b > a && b > c)
            largest = b;
        else
            largest = c;
        
        cout << "가장 큰 정수는 " << largest << endl;
    } else {
        cout << "서로 다른 정수를 입력하시오." << endl;
    }

    return 0;
}
