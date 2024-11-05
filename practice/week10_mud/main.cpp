//한글 입력이 인식되지 않는 오류가 있어 영어로 변경함
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "user.h" // User 클래스 포함

using namespace std;

const int mapX = 5;
const int mapY = 5;

// 사용자 정의 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY);
void displayMap(int map[][mapX], int user_x, int user_y);
bool checkGoal(int map[][mapX], int user_x, int user_y);
void currentStatus(const User &user); // User 객체의 체력 상태를 출력

// 메인 함수
int main() {
    srand(time(0)); // 랜덤 시드 초기화

    int map[mapY][mapX] = { {0, 0, 2, 0, 4},
                            {0, 0, 0, 2, 0},
                            {0, 0, 0, 0, 0},
                            {0, 2, 3, 0, 0},
                            {3, 0, 0, 0, 2} };

    if (rand() % 2 == 0) {
        map[0][1] = 1;
        map[1][0] = 5;
    } else {
        map[0][1] = 5;
        map[1][0] = 1;
    }

    int user_x = 0;
    int user_y = 0;
    User user; // User 객체 생성

    while (true) {
        currentStatus(user); // 현재 체력 상태 출력

        string user_input = "";
        cout << "Enter command (up, down, left, right, map, exit): ";
        cin >> user_input;

        if (user_input == "up") {
            user_y -= 1;
            if (!checkXY(user_x, mapX, user_y, mapY)) {
                cout << "Out of bounds. Returning to previous position." << endl;
                user_y += 1;
            } else {
                cout << "Moving up." << endl;
                displayMap(map, user_x, user_y);
            }
        } else if (user_input == "down") {
            user_y += 1;
            if (!checkXY(user_x, mapX, user_y, mapY)) {
                cout << "Out of bounds. Returning to previous position." << endl;
                user_y -= 1;
            } else {
                cout << "Moving down." << endl;
                displayMap(map, user_x, user_y);
            }
        } else if (user_input == "left") {
            user_x -= 1;
            if (!checkXY(user_x, mapX, user_y, mapY)) {
                cout << "Out of bounds. Returning to previous position." << endl;
                user_x += 1;
            } else {
                cout << "Moving left." << endl;
                displayMap(map, user_x, user_y);
            }
        } else if (user_input == "right") {
            user_x += 1;
            if (!checkXY(user_x, mapX, user_y, mapY)) {
                cout << "Out of bounds. Returning to previous position." << endl;
                user_x -= 1;
            } else {
                cout << "Moving right." << endl;
                displayMap(map, user_x, user_y);
            }
        } else if (user_input == "map") {
            displayMap(map, user_x, user_y);
            continue;
        } else if (user_input == "exit") {
            cout << "Exiting the game." << endl;
            break;
        } else {
            cout << "Invalid input." << endl;
            continue;
        }

        user.DecreaseHP(1);
        if (user.GetHP() <= 0) {
            cout << "HP has reached 0. Game Over." << endl;
            break;
        }

        int currentState = map[user_y][user_x];
        switch (currentState) {
            case 1:
                cout << "You found a sword!" << endl;
                break;
            case 2:
                user.DecreaseHP(2);
                cout << "You encountered an enemy! HP decreased by 2." << endl;
                break;
            case 3:
                user.IncreaseHP(2);
                cout << "You found a potion! HP increased by 2." << endl;
                break;
            case 4:
                cout << "You reached the destination! Congratulations!" << endl;
                cout << "Exiting the game." << endl;
                return 0;
            case 5:
                cout << "You found an armor!" << endl;
                break;
        }

        if (user.GetHP() <= 0) {
            cout << "HP has reached 0. Game Over." << endl;
            break;
        }
    }

    return 0;
}

// 지도와 사용자 위치 출력하는 함수
void displayMap(int map[][mapX], int user_x, int user_y) {
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            if (i == user_y && j == user_x) {
                cout << " USER |";
            } else {
                int posState = map[i][j];
                switch (posState) {
                    case 0: cout << "      |"; break;
                    case 1: cout << " Sword |"; break;
                    case 2: cout << " Enemy |"; break;
                    case 3: cout << " Potion|"; break;
                    case 4: cout << " Goal  |"; break;
                    case 5: cout << " Armor |"; break;
                }
            }
        }
        cout << endl;
        cout << " -------------------------------- " << endl;
    }
}

// 이동하려는 곳이 유효한 좌표인지 체크하는 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY) {
   return (user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY);
}

// 유저의 현재 상태 출력하는 함수
void currentStatus(const User &user) {
    cout << "Current HP: " << user.GetHP() << endl;
}