#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define USER_FILE "user.txt"

typedef struct {
    int keyId;
    char userId[50];
    char password[20];
    char name[50];
    char address[50];
    int birth;
    int lc;
} User;

// 함수 선언
void Manage();
void Menu();
void Login();
void AddUser();
void onExit();
int isValidEmail(const char* email);

int main() {
    atexit(onExit);
    Manage();
    return 0;
}

// 시스템 메뉴
void Manage() {
    int choice;
    while (1) {
        Menu();
        scanf("%d", &choice);
        while (getchar() != '\n');  // 버퍼 비우기

        switch (choice) {
            case 1: Login(); break;
            //case 2: AddUser(); break;
            case 0:
                printf("프로그램 종료!\n");
                exit(0);
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}

// 메뉴 출력
void Menu() {
    printf("\n< 시스템 소프트웨어 >\n");
    printf("1. 로그인\n");
    printf("2. 사용자 추가\n");
    printf("0. 종료\n");
    printf("선택: ");
}

// 로그인 기능
void Login() {
    char id[50];
    char pw[20];
    User u;

    printf("로그인 화면 입니다.\n");
    printf("사용자 id와 password를 입력하세요.\n");
    printf("id: ");
    fgets(id, sizeof(id), stdin);

    printf("pass: ");
    fgets(pw, sizeof(pw), stdin);
}


void AddUser() {
    char id[50];
    char pass[20];
    char uname[50];
    char uaddress[50];
    int ubirth, cnt, lastId = 0;
    User u;
    FILE * fp;

    printf("사용자 추가 화면입니다.");

    while (1) {
        printf("userid: ");
        fgets(id, sizeof(id), stdin);
        fp = fopen(USER_FILE, "rb");
        if (fp != NULL) {
            cnt = 0;
            while (fread(&u, sizeof(User), 1, fp)) {
                if (strcmp(u.userId, id) == 0) {
                    cnt = 1;
                }
            }
            if (cnt) {
                printf("이미 있는 사용자 입니다.");
            }
            else {
                printf("새로운 사용자 id를 만듭니다.");
                fclose(fp);
                break;
            }
        }
    }

    fp = fopen(USER_FILE, "ab");
    if (fp == NULL) {
        perror("파일 열기 실패");
        return;
    }





}
// 프로그램 종료 핸들러
void onExit() {
    printf("\n<Exit handle을 사용해 다음 프린트>\n");
    printf("---------------------------------------------\n");
    printf("\"서지현\"이 구현한\n시스템소프트웨어 데모 시스템을 이용해 주셔서 감사합니다.\n");
    printf("---------------------------------------------\n");
}