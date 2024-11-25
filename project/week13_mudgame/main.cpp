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
void currentStatus(User &user);
bool CheckUser(User &user);
string trim(const string &str);

// 메인 함수
int main()
{
    srand(time(0));

    // 맵 구성
    int map[mapY][mapX] = {{0, 0, 2, 0, 4},
                           {0, 0, 0, 2, 0},
                           {0, 0, 0, 0, 0},
                           {0, 2, 3, 0, 0},
                           {3, 0, 0, 0, 2}};

    // (0,1), (1,0)에 랜덤하게 검 또는 갑옷 배치
    if (rand() % 2 == 0)
    {
        map[0][1] = 1;
        map[1][0] = 5;
    }
    else
    {
        map[0][1] = 5;
        map[1][0] = 1;
    }

    // 유저 생성
    User *currentUser = nullptr;
    string choice;

    cout << "Choose your class (Magician/Warrior): ";
    getline(cin, choice);
    transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
    choice = trim(choice);

    if (choice == "magician")
    {
        currentUser = new Magician();
    }
    else if (choice == "warrior")
    {
        currentUser = new Warrior();
    }
    else
    {
        cout << "Invalid class choice. Exiting the game." << endl;
        return 1;
    }

    // 초기 위치
    int user_x = 0;
    int user_y = 0;

    // 게임 시작
    while (true)
    {
        currentStatus(*currentUser);

        string user_input;
        cout << "Enter a command (up, down, left, right, map, exit, attack): ";
        getline(cin, user_input);

        transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);
        user_input = trim(user_input);

        if (user_input == "attack")
        {
            currentUser->doAttack();
            continue;
        }
        else if (user_input == "up")
        {
            user_y -= 1;
            if (!checkXY(user_x, mapX, user_y, mapY))
            {
                cout << "You went out of the map. Moving back." << endl;
                user_y += 1;
            }
        }
        else if (user_input == "down")
        {
            user_y += 1;
            if (!checkXY(user_x, mapX, user_y, mapY))
            {
                cout << "You went out of the map. Moving back." << endl;
                user_y -= 1;
            }
        }
        else if (user_input == "left")
        {
            user_x -= 1;
            if (!checkXY(user_x, mapX, user_y, mapY))
            {
                cout << "You went out of the map. Moving back." << endl;
                user_x += 1;
            }
        }
        else if (user_input == "right")
        {
            user_x += 1;
            if (!checkXY(user_x, mapX, user_y, mapY))
            {
                cout << "You went out of the map. Moving back." << endl;
                user_x -= 1;
            }
        }
        else if (user_input == "map")
        {
            displayMap(map, user_x, user_y);
            continue;
        }
        else if (user_input == "exit")
        {
            cout << "Exiting the game." << endl;
            break;
        }
        else
        {
            cout << "Invalid input." << endl;
            continue;
        }

        currentUser->DecreaseHP(1);
        if (CheckUser(*currentUser) == false)
        {
            cout << "HP has reached 0. Game over!" << endl;
            break;
        }

        int currentState = map[user_y][user_x];
        switch (currentState)
        {
        case 1:
            cout << "Found a sword!" << endl;
            currentUser->AddItem();
            break;
        case 2:
            currentUser->DecreaseHP(2);
            cout << "Encountered an enemy! HP decreases by 2." << endl;
            break;
        case 3:
            currentUser->IncreaseHP(2);
            cout << "Found a potion! HP increases by 2." << endl;
            currentUser->AddItem();
            break;
        case 4:
            cout << "You reached the goal! Congratulations!" << endl;
            delete currentUser;
            return 0;
        case 5:
            cout << "Found armor!" << endl;
            currentUser->AddItem();
            break;
        }

        if (CheckUser(*currentUser) == false)
        {
            cout << "HP has reached 0. Game over!" << endl;
            break;
        }

        displayMap(map, user_x, user_y);
    }

    delete currentUser;
    return 0;
}

string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void displayMap(int map[][mapX], int user_x, int user_y)
{
    for (int i = 0; i < mapY; i++)
    {
        for (int j = 0; j < mapX; j++)
        {
            if (i == user_y && j == user_x)
            {
                cout << "USER  |";
            }
            else
            {
                switch (map[i][j])
                {
                case 0:
                    cout << "      |";
                    break;
                case 1:
                    cout << " SWORD|";
                    break;
                case 2:
                    cout << " ENEMY|";
                    break;
                case 3:
                    cout << "POTION|";
                    break;
                case 4:
                    cout << "GOAL  |";
                    break;
                case 5:
                    cout << "ARMOR |";
                    break;
                }
            }
        }
        cout << endl;
    }
}

bool checkXY(int user_x, int mapX, int user_y, int mapY)
{
    return user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY;
}

void currentStatus(User &user)
{
    cout << user << endl;
}

bool CheckUser(User &user)
{
    return user.GetHP() > 0;
}
