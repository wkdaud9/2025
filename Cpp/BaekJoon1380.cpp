#include <iostream>


using namespace std;

class CLA {
private:
    static int sina;
    string who;
    int n;
    string * str;
    int * arr;
public:
    void manage();
    void init();
    void plusSina();
    void input(string s, int idx);
    void input(int num);
    int comp();
    void print();
};

void CLA::init() {
    cin >> n;
    str = new string[n+1];
    arr = new int[n+1];
    for (int i=1; i<=n; i++) {
        str[i] = " ";
        arr[i] = 0;
    }
}

void CLA::manage() {
    string s;
    char a;
    int num;
    while (1) {
        init();
        if (n == 0) break;
        cin.ignore();
        for (int i=1; i<=n; i++) {
            getline(cin, s);
            input(s, i);
        }
        for (int i=1; i<=n*2-1; i++) {
            cin >> num >> a;
            input(num);
        }
        who = str[comp()];
        print();
        sina++;
    }
    delete[] str;
    delete[] arr;
}

void CLA::input(int num) {
    arr[num]++;
}

void CLA::input(string s, int idx) {
    str[idx] = s;
}

int CLA::comp() {
    for (int i=1; i<=n; i++) {
        if (arr[i] == 1) return i;
    }
    return 0;
}
void CLA::print() {
    cout << sina << " " << who << endl;
}

int CLA::sina = 1;

int main() {
    CLA c;
    c.manage();
    return 0;
}