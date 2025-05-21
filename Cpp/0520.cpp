#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "conio.h"
#include <unistd.h>

using namespace std;

class CLA {
protected:
    int map[8][8] =
        {
        {1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1},
        };
    int sx, sy;
    char ch;
public:
    void Manage();
    void MakeUser();
    void Walk();
    void Up();
    void Down();
    void Left();
    void Right();
    void MakeWall();
    void DrawMap();
};

void CLA::Manage() {
    MakeUser();
    DrawMap();
    Walk();
}

void CLA::MakeUser() {
    srand(time(NULL));

    sx = (rand()%6) + 1;
    sy = (rand()%6) + 1;
    map[sy][sx] = 2;
}

void CLA::Walk() {
    ch = 0;
    while (ch!='q') {
        ch = _getch();
        switch (ch) {
            case 72: Up(); break;
            case 80: Down(); break;
            case 75: Left(); break;
            case 77: Right(); break;
            case 32: MakeWall(); break;
        }
        system("clear");
        DrawMap();
    }
}

void CLA::Up() {
    --sy;
    if (sy == 0) sy = 1;
    else {
        if (map[sy+1][sx] != 1) map[sy+1][sx] = 0;
        if (map[sy][sx]!=1) map[sy][sx] = 2;
    }
}

void CLA::Down() {
    ++sy;
    if (sy == 7) sy = 6;
    else {
        if (map[sy-1][sx] != 1) map[sy-1][sx] = 0;
        if (map[sy][sx] != 1) map[sy][sx] = 2;
    }
}

void CLA::Left() {
    --sx;
    if (sx == 0) sx = 1;
    else {
        if (map[sy][sx+1]!=1) map[sy][sx+1] = 0;
        if (map[sy][sx]!=1) map[sy][sx] = 2;
    }
}

void CLA::Right() {
    ++sx;
    if (sx == 7) sx = 6;
    else {
        if (map[sy][sx-1]!=1) map[sy][sx-1] = 0;
        if (map[sy][sx]!=1) map[sy][sx] = 2;
    }
}

void CLA::MakeWall() {
    map[sy][sx] = 1;
}


void CLA::DrawMap() {
    int a, b;
    for (a=0; a<8; a++) {
        for (b=0; b<8; b++) {
            if (map[a][b] == 0) {
                cout << " ";
            }
            if (map[a][b] == 1) {
                cout <<  "#";
            }
            if (map[a][b] == 2) {
                cout <<  "#";
            }
            if (map[a][b] == 3) {
                cout << "⭐";
            }
        }
        cout << endl;
    }
}

class Move:public CLA {
public:
    void Move_Manage();
    void RandomWalk();
};

void Move::Move_Manage() {
    Manage();
    RandomWalk();
}

void Move::RandomWalk() {
    int r;

    while (1) {
        r = rand() % 4;
        if (r == 0) {   // 위로 이동
            if (map[sy-1][sx] == 0 && sy > 0) {
                map[sy--][sx] = 0;
                map[sy][sx] = 3;
            }
        }
        else if (r == 1) {  // 아래로 이동
            if (map[sy+1][sx] == 0 && sy < 7) {
                map[sy++][sx] = 0;
                map[sy][sx] = 3;
            }
        }
        else if (r == 2) {  // 왼쪽으로 이동
            if (map[sy][sx-1] == 0 && sx > 0) {
                map[sy][sx--] = 0;
                map[sy][sx] = 3;
            }

        }
        else if (r == 3) {  // 오른쪽으로 이동
            if (map[sy][sx+1] == 0 && sx < 7) {
                map[sy][sx++] = 0;
                map[sy][sx] = 3;
            }
        }
        usleep(300000);
        system("clear");
        CLA::DrawMap();
    }
}


int main() {
    Move nm;
    nm.Move_Manage();
    return 0;
}





