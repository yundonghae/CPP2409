#ifndef USER_H
#define USER_H

#include <iostream>

class User {
private:
    int hp;
    int itemCnt;

public:
    User(); // 생성자
    void DecreaseHP(int dec_hp); // HP 감소
    void IncreaseHP(int inc_hp); // HP 증가
    int GetHP() const; // HP 반환
    void AddItem(); // 아이템 추가
    int GetItemCnt() const; // 아이템 개수 반환

    // 출력 연산자 중복 정의
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};

#endif
