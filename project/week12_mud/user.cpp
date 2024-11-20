#include "user.h"

// User 클래스 구현
User::User() : hp(20), itemCnt(0) {}

void User::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
}

void User::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

int User::GetHP() const {
    return hp;
}

void User::AddItem() {
    itemCnt++;
}

int User::GetItemCnt() const {
    return itemCnt;
}

void User::doAttack() const {
    std::cout << "Attacking!" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "Current HP: " << user.GetHP() << ", Items Collected: " << user.GetItemCnt();
    return os;
}

// Magician 클래스 구현
Magician::Magician() {
    hp = 15; // 마법사는 기본 HP가 낮음
}

void Magician::doAttack() const {
    std::cout << "Using magic!" << std::endl;
}

// Warrior 클래스 구현
Warrior::Warrior() {
    hp = 25; // 전사는 기본 HP가 높음
}

void Warrior::doAttack() const {
    std::cout << "Using a slash attack!" << std::endl;
}
