#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <stdexcept>
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

// 맵 파일 읽기 함수
void readMapFromFile(const string &filename, int map[][mapX])
{
  ifstream infile(filename);
  if (!infile) // 예외 1: 파일이 존재하지 않거나 열리지 않을 때
  {
    throw runtime_error("Failed to open the map file.");
  }

  for (int i = 0; i < mapY; ++i)
  {
    for (int j = 0; j < mapX; ++j)
    {
      if (!(infile >> map[i][j])) // 예외 2: 파일 형식이 잘못된 경우
      {
        throw runtime_error("Invalid map format in file.");
      }
    }
  }
  infile.close();
}

// 메인 함수
int main()
{
  srand(time(0));

  // 맵 구성
  int map[mapY][mapX];
  try
  {
    // 예외 1, 2를 처리: 파일이 열리지 않거나 잘못된 형식일 경우 catch로 이동
    readMapFromFile("map.txt", map);
  }
  catch (const exception &e)
  {
    cerr << "Error: " << e.what() << endl;
    return 1; // 프로그램 종료
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

    try
    {
      // 예외 3: HP 감소 로직에서 음수 값 방지를 위한 예외 처리
      currentUser->DecreaseHP(1);
    }
    catch (const exception &e)
    {
      cerr << "Error: " << e.what() << endl;
      cout << "Game over due to critical error." << endl;
      break;
    }

    if (!CheckUser(*currentUser))
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
      try
      {
        // 예외 3: 적과 조우하여 HP가 음수가 될 가능성 처리
        currentUser->DecreaseHP(2);
      }
      catch (const exception &e)
      {
        cerr << "Error: " << e.what() << endl;
        cout << "Game over due to critical error." << endl;
        break;
      }
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

    if (!CheckUser(*currentUser))
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
