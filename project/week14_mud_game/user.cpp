#include "user.h"

// Magician 클래스 구현
Magician::Magician() : hp(15), itemCnt(0) {}

void Magician::DecreaseHP(int dec_hp)
{
    hp -= dec_hp;
}

void Magician::IncreaseHP(int inc_hp)
{
    hp += inc_hp;
}

int Magician::GetHP() const
{
    return hp;
}

void Magician::AddItem()
{
    itemCnt++;
}

int Magician::GetItemCnt() const
{
    return itemCnt;
}

void Magician::doAttack() const
{
    std::cout << "Using magic!" << std::endl;
}

// Warrior 클래스 구현
Warrior::Warrior() : hp(25), itemCnt(0) {}

void Warrior::DecreaseHP(int dec_hp)
{
    hp -= dec_hp;
}

void Warrior::IncreaseHP(int inc_hp)
{
    hp += inc_hp;
}

int Warrior::GetHP() const
{
    return hp;
}

void Warrior::AddItem()
{
    itemCnt++;
}

int Warrior::GetItemCnt() const
{
    return itemCnt;
}

void Warrior::doAttack() const
{
    std::cout << "Using a slash attack!" << std::endl;
}
