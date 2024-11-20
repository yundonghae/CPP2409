#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
protected:
    int hp;
    int itemCnt;

public:
    User(); // 생성자
    virtual ~User() = default; // 소멸자

    void DecreaseHP(int dec_hp); // HP 감소
    void IncreaseHP(int inc_hp); // HP 증가
    int GetHP() const; // HP 반환
    void AddItem(); // 아이템 추가
    int GetItemCnt() const; // 아이템 개수 반환

    virtual void doAttack() const; // 공격 동작(가상 함수)

    // 출력 연산자 중복 정의
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};

// Magician 클래스
class Magician : public User {
public:
    Magician(); // 생성자
    void doAttack() const override; // 공격 동작 재정의
};

// Warrior 클래스
class Warrior : public User {
public:
    Warrior(); // 생성자
    void doAttack() const override; // 공격 동작 재정의
};

#endif
