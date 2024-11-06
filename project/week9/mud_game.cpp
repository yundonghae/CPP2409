#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int mapX = 5;
const int mapY = 5;

// 사용자 정의 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY);
void displayMap(int map[][mapX], int user_x, int user_y);
bool checkGoal(int map[][mapX], int user_x, int user_y);
void currentStatus(int hp);

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

    // 유저의 위치를 저장할 변수
    int user_x = 0; // 가로 번호
    int user_y = 0; // 세로 번호
    int hp = 20; // 유저의 체력

    // 게임 시작
    while (true) { // 사용자에게 계속 입력받기 위해 무한 루프
        // 현재 체력 상태 출력
        currentStatus(hp);

        // 사용자의 입력을 저장할 변수
        string user_input = "";

        cout << "명령어를 입력하세요 (상,하,좌,우,지도,종료): ";
        cin >> user_input;

        if (user_input == "상") {
			// 위로 한 칸 올라가기
			user_y -= 1;
			bool inMap = checkXY(user_x, mapX, user_y, mapY);
			if (inMap == false) {
				cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
				user_y += 1;
			}
			else {
				cout << "위로 한 칸 올라갑니다." << endl;
				displayMap(map, user_x, user_y);
			}
		}
		else if (user_input == "하") {
			// TODO: 아래로 한 칸 내려가기
			user_y += 1;
			bool inMap = checkXY(user_x, mapX, user_y, mapY);
			if (inMap == false) {
				cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
				user_y -= 1;
			}
			else {
				cout << "위로 한 칸 내려갑니다." << endl;
				displayMap(map, user_x, user_y);
			}
		}
		else if (user_input == "좌") {
			// TODO: 왼쪽으로 이동하기
			user_x -= 1;
			bool inMap = checkXY(user_x, mapX, user_y, mapY);

			if (inMap == false) {
				cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
				user_x += 1;
			}
			else {
				cout << "왼쪽으로 이동합니다." << endl;
				displayMap(map, user_x, user_y);
			}
		}
		else if (user_input == "우") {
			// TODO: 오른쪽으로 이동하기
			user_x += 1;
			bool inMap = checkXY(user_x, mapX, user_y, mapY);
			if (inMap == false) {
				cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
				user_x -= 1;
			}
			else {
				cout << "오른쪽으로 이동합니다." << endl;
				displayMap(map, user_x, user_y);
			}
		}
		else if (user_input == "지도") {
			// TODO: 지도 보여주기 함수 호출
			displayMap(map, user_x, user_y);
            continue; // 지도를 볼 때는 체력 감소 없음
		}
		else if (user_input == "종료") {
			cout << "종료합니다.";
			break;
		}
		else {
			cout << "잘못된 입력입니다." << endl;
			continue;
		}


        // 이동 시 체력 감소
        hp -= 1;
        if (hp <= 0) {
            cout << "HP가 0이 되어 실패하였습니다. 게임을 종료합니다." << endl;
            break;
        }


        // 현재 위치 상태 출력
        int currentState = map[user_y][user_x];
        switch (currentState) {
            case 1:
                cout << "검이 있습니다!" << endl;
                break;
            case 2:
                hp -= 2;
                cout << "적이 있습니다! 전투가 발생하여 HP가 2 감소합니다." << endl;
                break;
            case 3:
                cout << "포션이 있습니다!" << endl;
                break;
            case 4:
                cout << "목적지에 도착했습니다! 축하합니다!" << endl;
                cout << "게임을 종료합니다." << endl;
                return 0;
            case 5:
                cout << "갑옷이 있습니다!" << endl;
                break;
        }

        // HP가 0 이하로 감소했는지 확인
        if (hp <= 0) {
            cout << "HP가 0이 되어 실패하였습니다. 게임을 종료합니다." << endl;
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
                cout << " USER |"; // 양 옆 1칸 공백
            } else {
                int posState = map[i][j];
                switch (posState) {
                    case 0:
                        cout << "      |"; // 6칸 공백
                        break;
                    case 1:
                        cout << "  검  |"; // 양 옆 2칸 공백
                        break;
                    case 2:
                        cout << "  적  |"; // 양 옆 2칸 공백
                        break;
                    case 3:
                        cout << " 포션 |"; // 양 옆 1칸 공백
                        break;
                    case 4:
                        cout << "목적지|";
                        break;
                    case 5:
                        cout << " 갑옷 |"; // 양 옆 1칸 공백
                        break;
                }
            }
        }
        cout << endl;
        cout << " -------------------------------- " << endl;
    }
}

// 이동하려는 곳이 유효한 좌표인지 체크하는 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY) {
	bool checkFlag = false;
	if (user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY) {
		checkFlag = true;
	}
	return checkFlag;
}

// 유저의 위치가 목적지인지 체크하는 함수
bool checkGoal(int map[][mapX], int user_x, int user_y) {
	// 목적지 도착하면
	if (map[user_y][user_x] == 4) {
		return true;
	}
	return false;
}

// 현재 상태를 출력하는 함수
void currentStatus(int hp) {
    cout << "현재 HP: " << hp << endl;
}