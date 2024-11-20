#include "user.h"

User::User() : hp(20), itemCnt(0) {}

// HP 감소
void User::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
}

// HP 증가
void User::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

// HP 반환
int User::GetHP() const {
    return hp;
}

// 아이템 추가
void User::AddItem() {
    itemCnt++;
}

// 아이템 개수 반환
int User::GetItemCnt() const {
    return itemCnt;
}

// 출력 연산자 중복 정의
std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "Current HP: " << user.GetHP() << ", Items Collected: " << user.GetItemCnt();
    return os;
}
