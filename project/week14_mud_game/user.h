#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User
{
public:
    virtual ~User() = default; // 소멸자

    virtual void DecreaseHP(int dec_hp) = 0; // HP 감소
    virtual void IncreaseHP(int inc_hp) = 0; // HP 증가
    virtual int GetHP() const = 0;           // HP 반환
    virtual void AddItem() = 0;              // 아이템 추가
    virtual int GetItemCnt() const = 0;      // 아이템 개수 반환

    virtual void doAttack() const = 0; // 공격 동작

    // 출력 연산자 중복 정의
    friend std::ostream &operator<<(std::ostream &os, const User &user)
    {
        os << "Current HP: " << user.GetHP() << ", Items Collected: " << user.GetItemCnt();
        return os;
    }
};

// Magician 클래스
class Magician : public User
{
private:
    int hp;
    int itemCnt;

public:
    Magician();                           // 생성자
    void DecreaseHP(int dec_hp) override; // HP 감소
    void IncreaseHP(int inc_hp) override; // HP 증가
    int GetHP() const override;           // HP 반환
    void AddItem() override;              // 아이템 추가
    int GetItemCnt() const override;      // 아이템 개수 반환
    void doAttack() const override;       // 공격 동작
};

// Warrior 클래스
class Warrior : public User
{
private:
    int hp;
    int itemCnt;

public:
    Warrior();                            // 생성자
    void DecreaseHP(int dec_hp) override; // HP 감소
    void IncreaseHP(int inc_hp) override; // HP 증가
    int GetHP() const override;           // HP 반환
    void AddItem() override;              // 아이템 추가
    int GetItemCnt() const override;      // 아이템 개수 반환
    void doAttack() const override;       // 공격 동작
};

#endif
