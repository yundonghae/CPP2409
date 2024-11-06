#include "user.h"

User::User() : hp(20) {} // 생성자에서 hp를 20으로 초기화

void User::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
    if (hp < 0) hp = 0; // hp가 0 이하로 내려가지 않도록 조정
}

void User::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

int User::GetHP() const {
    return hp;
}