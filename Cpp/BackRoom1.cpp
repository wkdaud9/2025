#include <iostream>
#include "conio.h"

using namespace std;

class BACK {
private:
    int r_nm; // 현실 값
    int b_nm; // 이동 객체의 값
    int nm_x; // 이동 객체의 위치
    char ky; // 이동 입력 키

public:
    void Start();
    void Print();
    void Left();
    void Right();
};

void BACK::Start() {
    r_nm = 1;
    nm_x = 0;
    b_nm = 1;
    Print();
    ky = 0;
    while (ky != 'q') {
        ky = _getch();
        switch (ky) {
            case 75: Left(); break;
            case 77: Right(); break;
        }
        system("clear");
        Print();
    }
}

void BACK::Left() {
    r_nm = 0;
    if (nm_x < 0) {
        b_nm -= 1;
        nm_x -= 1;
        if (b_nm == 0) {
            b_nm = -1;
        }
    }
    else if (nm_x > 0) {
        nm_x -= 1;
        if (b_nm == 0) {
            b_nm = -1;
        }
    }
    else if (nm_x == 0) {
        b_nm -= 1;
        nm_x -= 1;
        if (b_nm == 0) {
            b_nm = -1;
        }
    }
    if (nm_x == 0) {
        r_nm = b_nm;
    }
}


void BACK::Right() {
    r_nm = 0;
    if (nm_x > 0) {
        b_nm += 1;
        nm_x += 1;
        if (b_nm == 0) {
            b_nm = 1;
        }
    }
    else if (nm_x < 0) {
        nm_x += 1;
        if (b_nm == 0) {
            b_nm = 1;
        }
    }
    else if (nm_x == 0) {
        b_nm += 1;
        nm_x += 1;
        if (b_nm == 0) {
            b_nm = 1;
        }
    }
    if (nm_x == 0) {
        r_nm = b_nm;
    }
}

void BACK::Print() {
    cout << r_nm << endl;
    cout << "[" << nm_x <<  "]" << endl;
    cout << b_nm << endl;
}

int main() {
    BACK bac;
    bac.Start();
    return 0;
}




