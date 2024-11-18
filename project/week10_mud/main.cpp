#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "user.h"

using namespace std;

const int mapX = 5;
const int mapY = 5;

// 사용자 정의 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY);
void displayMap(int map[][mapX], int user_x, int user_y);
bool checkGoal(int map[][mapX], int user_x, int user_y);
void currentStatus(User& user);
bool CheckUser(User& user);

// 문자열의 앞뒤 공백 제거 함수
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// 메인 함수
int main() {
    srand(time(0)); // 랜덤 시드 초기화

    // 0은 빈 공간, 2는 적, 3은 포션, 4는 목적지
    int map[mapY][mapX] = { {0, 0, 2, 0, 4},
                            {0, 0, 0, 2, 0},
                            {0, 0, 0, 0, 0},
                            {0, 2, 3, 0, 0},
                            {3, 0, 0, 0, 2} };

    // (0,1), (1,0)에 랜덤하게 검 또는 갑옷 배치
    if (rand() % 2 == 0) {
        map[0][1] = 1; // (0,1)에 검 배치
        map[1][0] = 5; // (1,0)에 갑옷 배치
    } else {
        map[0][1] = 5; // (0,1)에 갑옷 배치
        map[1][0] = 1; // (1,0)에 검 배치
    }

    // 유저 객체 생성
    User user;
    int user_x = 0; // 가로 번호
    int user_y = 0; // 세로 번호

    // 게임 시작
    while (true) { // 사용자에게 계속 입력받기 위해 무한 루프
        // 현재 체력 상태 출력
        currentStatus(user);

        // 사용자의 입력을 저장할 변수
        string user_input = "";

        cout << "Enter a command (up, down, left, right, map, exit, info): ";
        getline(cin, user_input);

        // 입력값을 소문자로 변환하고 앞뒤 공백 제거
        transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);
        user_input = trim(user_input);

        if (user_input == "up") {
            // 위로 한 칸 올라가기
            user_y -= 1;
            bool inMap = checkXY(user_x, mapX, user_y, mapY);
            if (!inMap) {
                cout << "You went out of the map. Moving back." << endl;
                user_y += 1;
            } else {
                cout << "Moving up." << endl;
            }
        } else if (user_input == "down") {
            // 아래로 한 칸 내려가기
            user_y += 1;
            bool inMap = checkXY(user_x, mapX, user_y, mapY);
            if (!inMap) {
                cout << "You went out of the map. Moving back." << endl;
                user_y -= 1;
            } else {
                cout << "Moving down." << endl;
            }
        } else if (user_input == "left") {
            // 왼쪽으로 이동하기
            user_x -= 1;
            bool inMap = checkXY(user_x, mapX, user_y, mapY);
            if (!inMap) {
                cout << "You went out of the map. Moving back." << endl;
                user_x += 1;
            } else {
                cout << "Moving left." << endl;
            }
        } else if (user_input == "right") {
            // 오른쪽으로 이동하기
            user_x += 1;
            bool inMap = checkXY(user_x, mapX, user_y, mapY);
            if (!inMap) {
                cout << "You went out of the map. Moving back." << endl;
                user_x -= 1;
            } else {
                cout << "Moving right." << endl;
            }
        } else if (user_input == "map") {
            // 지도 보여주기 함수 호출
            displayMap(map, user_x, user_y);
            continue; // 지도를 볼 때는 체력 감소 없음
        } else if (user_input == "exit") {
            cout << "Exiting the game." << endl;
            break;
        } else if (user_input == "info") {
            cout << user << endl;
            continue; // 정보 출력 시 체력 감소 없음
        } else {
            cout << "Invalid input." << endl;
            continue;
        }

        // 이동 시 체력 감소
        user.DecreaseHP(1);
        if (CheckUser(user) == false) {
            cout << "HP has reached 0. You have failed. Exiting the game." << endl;
            break;
        }

        // 현재 위치 상태 출력
        int currentState = map[user_y][user_x];
        switch (currentState) {
            case 1:
                cout << "There is a sword here!" << endl;
                user.AddItem();
                break;
            case 2:
                user.DecreaseHP(2);
                cout << "There is an enemy here! A battle occurs, and HP decreases by 2." << endl;
                break;
            case 3:
                user.IncreaseHP(2);
                cout << "There is a potion here! HP increases by 2." << endl;
                user.AddItem();
                break;
            case 4:
                cout << "You have reached the destination! Congratulations!" << endl;
                cout << "Exiting the game." << endl;
                return 0;
            case 5:
                cout << "There is armor here!" << endl;
                user.AddItem();
                break;
        }

        // HP가 0 이하로 감소했는지 확인
        if (CheckUser(user) == false) {
            cout << "HP has reached 0. You have failed. Exiting the game." << endl;
            break;
        }

        // 지도 출력
        displayMap(map, user_x, user_y);
    }

    return 0;
}

// 지도와 사용자 위치 출력하는 함수
void displayMap(int map[][mapX], int user_x, int user_y) {
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            if (i == user_y && j == user_x) {
                cout << " USER |"; // 양 옆 1칸 공백
            } else {
                int posState = map[i][j];
                switch (posState) {
                    case 0:
                        cout << "      |"; // 6칸 공백
                        break;
                    case 1:
                        cout << " SWORD|"; // 양 옆 1칸 공백
                        break;
                    case 2:
                        cout << " ENEMY|"; // 양 옆 1칸 공백
                        break;
                    case 3:
                        cout << "POTION|"; // 양 옆 1칸 공백
                        break;
                    case 4:
                        cout << "GOAL  |"; // 양 옆 1칸 공백
                        break;
                    case 5:
                        cout << "ARMOR |"; // 양 옆 1칸 공백
                        break;
                }
            }
        }
        cout << endl;
    }
}

// 현재 체력 상태를 출력하는 함수
void currentStatus(User& user) {
    cout << "Current HP: " << user.GetHP() << endl;
}

// 유효한 좌표인지 확인하는 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY) {
    return user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY;
}

// 목적지에 도착했는지 확인하는 함수
bool checkGoal(int map[][mapX], int user_x, int user_y) {
    return map[user_y][user_x] == 4;
}

// 유저의 HP를 확인하는 함수
bool CheckUser(User& user) {
    return user.GetHP() > 0;
}
