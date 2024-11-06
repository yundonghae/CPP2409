#ifndef USER_H
#define USER_H

class User {
private:
    int hp;

public:
    User(); // 생성자
    void DecreaseHP(int dec_hp); // HP 감소 함수
    void IncreaseHP(int inc_hp); // HP 증가 함수
    int GetHP() const; // 현재 HP 반환
};

#endif