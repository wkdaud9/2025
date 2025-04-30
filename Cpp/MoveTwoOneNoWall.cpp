/*
 * 10칸 0을 모두 채우고 임의의 두개의 위치에 1을 두 개 두고, 좌우키를 누르면 움직임
 * 32번키를 치면 움직이는 권한이 상대방에게 넘어감
 * 왼쪽애가 먼저 움직이다가, 벽 밖으로는 나갈 수 없음
 */

#include <iostream>
#include <unistd.h>
#include "conio.h"

using namespace std;

class SPACE {
public:
    int b_map[10] = {0,};
    int x_one, x_two;
    char ky;

    void Nm_Bgin();
    void S_Print();
    void S_Left();
    void S_Right();
    void Key_Turn();
};

void SPACE::Nm_Bgin() {
    srand(time(NULL));
    x_one = rand() % 10;
    x_two = rand() % 10;

    if (x_one > x_two) {
        Key_Turn();
    }

    b_map[x_one] = 1;
    b_map[x_two] = 1;

    S_Print();
    ky = 0;
    while (ky != 'q') {
        ky = _getch();
        switch (ky) {
            case 32: Key_Turn();
            break;
            case 75: S_Left();
            break;
            case 77: S_Right();
            break;
        }
        system("clear");
        S_Print();
    }
}

void SPACE::Key_Turn() {
    int temp;
    temp = x_one;
    x_one = x_two;
    x_two = temp;
}

void SPACE::S_Left() {
    if (x_one -1 != x_two && x_two - 9 != x_one) {
        if (x_one != 0) {
            b_map[x_one--] = 0;
            b_map[x_one] = 1;
        }
        else if (x_one == 0) {
            b_map[x_one] = 0;
            b_map[x_one+=9] = 1;
        }
    }
    else if (x_one -1 == x_two) {
        if (x_two != 0) {
            b_map[x_two--] = 0;
            b_map[x_two] = 1;
            b_map[x_one--] = 0;
            b_map[x_one] = 1;
        }
        else if (x_two == 0) {
            b_map[x_two] = 0;
            b_map[x_two+=9] = 1;
            b_map[x_one--] = 0;
            b_map[x_one] = 1;
        }
    }
    else if (x_two - 9 == x_one) {
        b_map[--x_two] = 1;
        b_map[x_one] = 0;
        x_one = 9;
    }

}

void SPACE::S_Right() {
    if (x_one + 1 != x_two && x_two + 9 != x_one) {
        if (x_one != 9) {
            b_map[x_one++] = 0;
            b_map[x_one] = 1;
        }
        else if (x_one == 9) {
            b_map[x_one] = 0;
            b_map[x_one-=9] = 1;
        }
    }
    else if (x_one + 1 == x_two) {
        if (x_two != 9) {
            b_map[x_two++] = 0;
            b_map[x_two] = 1;
            b_map[x_one++] = 0;
            b_map[x_one] = 1;
        }
        else if (x_two == 9) {
            b_map[x_two] = 0;
            b_map[x_two-=9] = 1;
            b_map[x_one++] = 0;
            b_map[x_one] = 1;
        }
    }
    else if (x_two + 9 == x_one) {
        b_map[++x_two] = 1;
        b_map[x_one] = 0;
        x_one = 0;
    }

}

void SPACE::S_Print() {
    for (int a:b_map) {
        cout << a << " " ;
    }
    cout << endl;
}

int main() {
    SPACE s;
    s.Nm_Bgin();
    return 0;
}


