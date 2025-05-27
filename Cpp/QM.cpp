#include <iostream>
#include <vector>

using namespace std;

class Binary {
protected:
    vector<vector<int>> firstArr;
public:
    Binary();
    vector<int> TenToBinary (int n);
};

Binary::Binary() {
    for (int i=0; i<=15; i++)
        firstArr.push_back(TenToBinary(i));
}

vector<int> Binary::TenToBinary(int n) {
    vector<int> b(4);
    for (int i=3; i>=0; i--) {
        b[i] = n % 2;

        n /= 2;
    }
    return b;
}

class Implicants{
public:
    vector<int> key;
    vector<int> binary{4};
};

class QM : public Binary{
private:
    int inputArr[16];
    vector<vector<int>> secondArr{5};
    vector<Implicants> threeArr;

public:
    QM(){};
    void Manage();
    void InputOneZero();
    void CheckInput();
    int CountOne(vector<int> v);
    void SecondPrintArr();
    void Comp(int n1, int n2);
    void ThreePrintArr();
    ~QM(){};
};

void QM::Manage() {
    InputOneZero();
    CheckInput();
    SecondPrintArr();
    // 여기서부터 다시 짜기
    Comp();
    ThreePrintArr();
}

void QM::InputOneZero() {
    for (int i=0; i<16; i++)
        cin >> inputArr[i];
}

void QM::CheckInput() {
    int cnt;
    for (int i=0; i<16; i++) {
        if (inputArr[i] == 1) {
            cnt = CountOne(firstArr[i]);
            secondArr[cnt].push_back(i);
        }
    }
}

int QM::CountOne(vector<int> v) {
    int cnt = 0;
    for (int i=0; i<4; i++) {
        if (v[i] == 1) cnt++;
    }
    return cnt;
}

void QM::Comp(int n1, int n2) {
    Implicants im;
    vector<int> key;
    vector<int> binary;
    int cnt = 0;
    for (int i=0; i<4; i++) {
        if (firstArr[n1][i] != firstArr[n2][i]) cnt++;
    }
    if (cnt == 1) {
        key.push_back(n1);
        key.push_back(n2);
        for (int i=0; i<4; i++) {
            if (firstArr[n1][i] == firstArr[n2][i]) binary.push_back(firstArr[n1][i]);
            else binary.push_back(-1);
        }
        im.key = key;
        im.binary = binary;
        threeArr.push_back(im);
    }
}


void QM::SecondPrintArr() {
    int printCnt = 0;
    int idx = 0;

    cout << "        ABCD"<<endl;
    for (vector<int> i : secondArr) {
        printCnt = 0;
        if (!i.empty()) cout << idx;
        idx++;
        for (int j : i) {
            if (printCnt == 0) printCnt++;
            else cout << " ";
            cout <<"  (" << j << ") ";
            if (j < 10) cout << " ";
            for (int a=0; a<4; a++) {
                cout << firstArr[j][a];
            }
            cout << "   " << endl;
        }
        cout << endl;
    }
}

void QM::ThreePrintArr() {
    for (Implicants i : threeArr) {
        cout << "(";
        for (int k : i.key) {
            cout << k << ", ";
        }
        cout << ")  ";
        for (int v : i.binary) {
            cout << v;
        }
        cout << endl;
    }
}



int main() {
    QM q;
    q.Manage();
    return 0;
}