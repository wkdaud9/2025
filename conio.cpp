#include "conio.h"
#include <termios.h>
#include <unistd.h>

char _getch() {
    struct termios oldt, newt;
    char ch;

    // 현재 터미널 설정 저장
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // 즉시 입력 받도록 설정 (non-canonical), 입력 에코도 끔
    newt.c_lflag &= ~(ICANON | ECHO);

    // 새 설정 적용
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // 키 1개 입력 받기
    read(STDIN_FILENO, &ch, 1);

    if (ch == 27) { // ESC가 눌린 경우
        // non-block 모드로 잠깐 변경
        struct termios temp = newt;
        temp.c_cc[VMIN] = 0;  // 읽을 문자가 없으면 바로 리턴
        temp.c_cc[VTIME] = 1; // 0.1초 대기
        tcsetattr(STDIN_FILENO, TCSANOW, &temp);

        char seq[2];
        int n = read(STDIN_FILENO, &seq[0], 1);
        if (n == 0) {
            // 추가 입력 없으면 진짜 ESC 키
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return 27;
        }
        read(STDIN_FILENO, &seq[1], 1);

        if (seq[0] == '[') {
            if (seq[1] == 'D') ch = 75; // ←
            else if (seq[1] == 'C') ch = 77; // →
            else if (seq[1] == 'A') ch = 72; // ↑
            else if (seq[1] == 'B') ch = 80; // ↓
        }
    }

    // 원래 설정 복원
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}