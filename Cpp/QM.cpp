#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Binary {
protected:
    vector<vector<int>> binaryArr;
public:
    Binary();
    vector<int> TenToBinary (int n);
};

Binary::Binary() {
    for (int i=0; i<=15; i++)
        binaryArr.push_back(TenToBinary(i));
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
    vector<int> binary;
    Implicants(vector<int> k, vector<int> b) : key(k) , binary(b){}
};

class QM : public Binary{
private:
    int inputArr[16];
    int mgIdx = 0;
    vector<int> epiTop; // EPI 도표에서 위엣 부분
    vector<vector<int>> epiTable; // EPI 도표
    vector<vector<Implicants>> groupOne;   // 분류된 숫자들(1의 갯수로)
    vector<vector<Implicants>> mergeGroup;    // 0: 2차 분류 , 1: PI, 2: hidden PI, 3: PI 총합, 4: EPI
    vector<vector<int>> epi;
    vector<vector<int>> hiddenEpi;

public:
    QM(){};
    void Manage();
    void InitVector();
    void InputOneZero();
    void CheckInput(int i);
    void GroupOnePrint();
    void KeyComp(vector<int> n1, vector<int> n2);
    void BinaryComp(Implicants n1, Implicants n2);
    void TwoMerge();
    void ThreeMerge();
    void RemoveDup();
    void ThreePrintArr(int n);
    void FindHidden();
    void MergePi();
    void InitPI();
    void SetPI();
    void ShowPI();
    void InitEPI();
    void ShowEPI();
    void AddEPI();
    void HiddenEPI();
    void DeletePI(int j);
    void ShowDeleteEPI();
    void LastPrint();

    ~QM(){};
};

void QM::Manage() {
    int n = 0;
    InitVector();
    InputOneZero();
    GroupOnePrint();
    TwoMerge();
    ThreePrintArr(n);
    ThreeMerge();
    RemoveDup();
    ThreePrintArr(n+1);
    FindHidden();
    MergePi();
    InitPI();
    SetPI();
    ShowPI();
    InitEPI();
    ShowEPI();
    HiddenEPI();
    ShowDeleteEPI();
    AddEPI();
    LastPrint();
}

void QM::InitVector() {
    for (int i=0; i<5; i++) {
        groupOne.push_back(vector<Implicants>());
    }
}

void QM::InputOneZero() {
    for (int i=0; i<16; i++) {
        cin >> inputArr[i];
        CheckInput(i);
    }
}

void QM::CheckInput(int i) {
    vector<int> key;
    vector<int> binary;
    int cnt;
    if (inputArr[i] == 1) {
        cnt = count(binaryArr[i].begin(), binaryArr[i].end(), 1);
        key.push_back(i);
        for (int a=0; a<4; a++) {
            binary.push_back(binaryArr[i][a]);
        }
        Implicants temp(key, binary);
        groupOne[cnt].push_back(temp);
    }
}

void QM::TwoMerge() {
    int start = 0;
    while (groupOne[start].empty()) start++;
    while (start<groupOne.size()) {
        if (!groupOne[start+1].empty()) {
            for (Implicants i : groupOne[start]) {
                for (Implicants j : groupOne[start+1]) {
                    KeyComp(i.key, j.key);
                }
            }
        }
        start++;
    }
}

void QM::ThreeMerge() {
    int start = 0;
    vector<Implicants>::iterator it;
    vector<Implicants>::iterator second;

    while (mergeGroup[start].empty()) start++;
    it = mergeGroup[start].begin();
    while (it!=mergeGroup[start].end()-1) {
        second = it+1;
        while (second != mergeGroup[start].end()-1) {
            BinaryComp(*it, *second);
            ++second;
        }
        ++it;
    }
}


void QM::KeyComp(vector<int> n1, vector<int> n2) {
    vector<int> key;
    vector<int> binary;
    int cnt = 0;
    for (int i=0; i<4; i++) {
        if (binaryArr[n1[0]][i] != binaryArr[n2[0]][i]) cnt++;
    }
    if (cnt == 1) {
        key.push_back(n1[0]);
        key.push_back(n2[0]);
        for (int i=0; i<4; i++) {
            if (binaryArr[n1[0]][i] == binaryArr[n2[0]][i]) binary.push_back(binaryArr[n1[0]][i]);
            else binary.push_back(-1);
        }
        Implicants im(key, binary);
        mergeGroup.push_back(vector<Implicants>());
        mergeGroup[mgIdx].push_back(im);
    }
}

void QM::BinaryComp(Implicants n1, Implicants n2) {
    vector<int> key;
    vector<int> binary;
    int cnt = 0;
    mgIdx = 1;

    for (int a=0; a<4; a++) {
        if (n1.binary[a] != n2.binary[a]) cnt++;
    }

    if (cnt == 1) {
        for (int i : n1.key)
            key.push_back(i);
        for (int i : n2.key)
            key.push_back(i);
        for (int b=0; b<4; b++) {
            if (n1.binary[b] == n2.binary[b]) binary.push_back(n1.binary[b]);
            else binary.push_back(-1);
        }
        Implicants im(key, binary);
        mergeGroup.push_back(vector<Implicants>());
        mergeGroup[mgIdx].push_back(im);
    }
}

void QM::RemoveDup() {
    vector<Implicants>::iterator it;
    vector<Implicants>::iterator second;
    it = mergeGroup[1].begin();

    while (it != mergeGroup[1].end()) {
        sort(it->key.begin(), it->key.end());
        ++it;
    }

    it = mergeGroup[1].begin();
    while (it != mergeGroup[1].end()) {
        second = it+1;
        while (second != mergeGroup[1].end()) {
            if (it->key == second->key) {
                second = mergeGroup[1].erase(second);
            }
            else ++second;
        }
        ++it;
    }
}

void QM::FindHidden() {
    int cnt = 0;
    vector<Implicants>::iterator it = mergeGroup[0].begin();
    vector<Implicants>::iterator second;
    vector<int> key;
    vector<int> binary;
    mgIdx = 2;

    while (it != mergeGroup[0].end()) {
        key.clear();
        binary.clear();
        cnt = 0;
        second = mergeGroup[1].begin();
        while (second != mergeGroup[1].end()) {
            if (includes(second->key.begin(), second->key.end(), it->key.begin(), it->key.end()))
                cnt++;
            ++second;
        }
        if (cnt == 0) {
            for (int i : it->key) {
                key.push_back(i);
            }
            for (int b : it->binary) {
                binary.push_back(b);
            }
            Implicants im(key, binary);
            mergeGroup.push_back(vector<Implicants>());
            mergeGroup[mgIdx].push_back(im);
        }
        ++it;
    }
}

void QM::MergePi() {
    vector<int> key;
    vector<int> binary;
    vector<Implicants>::iterator it;
    mgIdx = 3;

    for (int i=1; i<=2; i++) {
        it = mergeGroup[i].begin();
        while (it != mergeGroup[i].end()) {
            key.clear();
            binary.clear();
            for (const int & k : it->key) {
                key.push_back(k);
            }
            for (const int & b : it->binary) {
                binary.push_back(b);
            }
            Implicants im(key, binary);
            mergeGroup.push_back(vector<Implicants>());
            mergeGroup[mgIdx].push_back(im);
            ++it;
        }
    }
}

void QM::GroupOnePrint() {
    int printCnt = 0;
    int idx = 0;

    cout << "        ABCD"<<endl;
    for (vector<Implicants> &i : groupOne) {
        printCnt = 0;
        if (!i.empty()) cout << idx;
        idx++;
        for (Implicants &j : i) {
            for (int &k : j.key) {
                if (printCnt == 0) printCnt++;
                else cout << " ";
                cout <<"  (" << k << ") ";
                if (k < 10) cout << " ";
                for (int & a : j.binary) {
                    cout << a;
                }
            }
            cout << "   " << endl;
        }
        if (!i.empty()) cout << endl;
    }
}

void QM::ThreePrintArr(int n) {
    int countPrint = 0;
    string space = "";
    int back;
    for (Implicants i: mergeGroup[n]) {
        space = "";
        cout << "(";
        countPrint = 0;
        back=0;
        for (int k : i.key) {
            back = k;
            cout << k;
            if (countPrint < 1) {
                cout << ",";
                countPrint++;
            }
            else if (countPrint < 3 && n == 1) {
                cout << ",";
                countPrint++;
            }
            if (back < 10) space+=" ";
        }
        cout << ")  " << space;
        for (int v : i.binary) {
            if (v == -1) cout << "-";
            else cout << v;
        }
        cout << endl;
    }
    cout << endl;
}

void QM::InitPI() {
    vector<Implicants>::iterator it = mergeGroup[3].begin();

    while (it != mergeGroup[3].end()) {
        for (int k : it->key) {
            epiTop.push_back(k);
        }
        ++it;
    }

    sort(epiTop.begin(), epiTop.end());
    epiTop.erase(unique(epiTop.begin(), epiTop.end()), epiTop.end());
    epiTable.resize(mergeGroup[3].size(), vector<int>(epiTop.size()));
}


void QM::SetPI() {
    int xdx = 0;
    vector<int>::iterator ydx;
    vector<Implicants>::iterator it = mergeGroup[3].begin();

    while (it != mergeGroup[3].end()) {
        for (int k : it->key) {
            ydx = find(epiTop.begin(), epiTop.end(), k);
            if (ydx != epiTop.end()) {
                epiTable[xdx][distance(epiTop.begin(),ydx)] = -1;
            }
        }
        ++it;
        ++xdx;
    }
}

void QM::ShowPI() {
    int print = 0;
    int idx = 0;
    int back;
    string space = "";

    cout << setw(15) << " ";
    for (int i : epiTop) cout << setw(3) << i;
    cout << endl;

    for (Implicants im : mergeGroup[3]) {
        space = "";
        print = 0;
        cout << "(";
        for (int k : im.key) {
            cout << left << k;
            back = k;
            if (print < im.key.size()-1) {
                cout << ", ";
                print++;
            }
            if (back < 10) space += " ";
        }
        if (im.key.size() == 4) space+=" ";
        if (im.key.size() == 2) space+="         ";
        cout << ")";
        cout << space;
        for (int i : epiTable[idx]) {
            if (i == -1) cout << setw(3) << "X";
            else cout << setw(3) << "  ";
        }
        cout << endl;
        idx++;
    }
    cout << endl;
}

void QM::InitEPI() {
    int idx=0, jdx=0;
    int cnt = 0;
    epi.assign(epiTable.size(), vector<int>(epiTable.size()));
    copy(epiTable.begin(), epiTable.end(), epi.begin());

    for (int j=0; j<epiTop.size(); j++) {
        cnt = 0;
        idx =0;
        jdx = 0;
        for (int i=0; i<epi.size(); i++) {
            if (epi[i][j] == -1) {
                cnt++;
                idx = i;
                jdx = j;
            }
        }
        if (cnt == 1) {
            epi[idx][jdx] = -2;
        }
    }
}

void QM::ShowEPI() {
    int print = 0;
    int idx = 0;
    int back;
    string space = "";

    cout << setw(17) << " ";
    for (int i : epiTop) cout << setw(3) << i;
    cout << endl;

    for (Implicants im : mergeGroup[3]) {
        space = "";
        print = 0;
        cout << "(";
        for (int k : im.key) {
            cout << left << k;
            back = k;
            if (print < im.key.size()-1) {
                cout << ", ";
                print++;
            }
            if (back < 10) space += " ";
        }
        if (im.key.size() == 4) space+=" ";
        if (im.key.size() == 2) space+="         ";
        cout << ")";
        cout << space;
        for (int i : epi[idx]) {
            if (i == -1) cout << setw(3) << "X";
            else if (i == -2) cout << setw(3) << "O";
            else cout << setw(3) << "  ";
        }
        cout << endl;
        idx++;
    }
    cout << endl;
}

void QM::ShowDeleteEPI() {
    int print = 0;
    int idx = 0;
    int back;
    string space = "";

    cout << setw(17) << " ";
    for (int i : epiTop) cout << setw(3) << i;
    cout << endl;

    for (Implicants im : mergeGroup[3]) {
        space = "";
        print = 0;
        cout << "(";
        for (int k : im.key) {
            cout << left << k;
            back = k;
            if (print < im.key.size()-1) {
                cout << ", ";
                print++;
            }
            if (back < 10) space += " ";
        }
        if (im.key.size() == 4) space+=" ";
        if (im.key.size() == 2) space+="         ";
        cout << ")";
        cout << space;
        for (int i : hiddenEpi[idx]) {
            if (i == -1) cout << setw(3) << "X";
            else if (i == -2) cout << setw(3) << "O";
            else cout << setw(3) << "  ";
        }
        cout << endl;
        idx++;
    }
}

void QM::AddEPI() {
    int idx = 0;
    mgIdx = 4;
    vector<int> key;
    vector<int> binary;
    vector<Implicants>::iterator it;
    it = mergeGroup[3].begin();


    for (vector<int> i : epi) {
        if (find(i.begin(), i.end(), -2) != i.end()) {
            key = it->key;
            binary = it->binary;
            mergeGroup.push_back(vector<Implicants>());
            Implicants im(key, binary);
            mergeGroup[mgIdx].push_back(im);
        }
        ++it;
    }
}

void QM::HiddenEPI() {
    mgIdx = 4;
    int cnt = 0;
    vector<int> key;
    vector<int> binary;
    vector<Implicants>::iterator it;
    it = mergeGroup[3].begin();

    hiddenEpi.assign(epi.size(), vector<int>(epi.size()));
    copy(epi.begin(), epi.end(), hiddenEpi.begin());

    for (int i=0; i<epi.size(); i++) {
        if (find(hiddenEpi[i].begin(), hiddenEpi[i].end(), -2) != hiddenEpi[i].end()) {
            for (int j=0; j<epiTop.size(); j++) {
                if (hiddenEpi[i][j] == -1) {
                    DeletePI(j);
                }

            }
        }
    }

    for (int i=0; i<epi.size(); i++) {
        cnt = 0;
        for (int j=0; j<epiTop.size(); j++) {
            if (hiddenEpi[i][j] == -1) cnt++;
        }
        if (cnt == it->key.size()) {
            key = it->key;
            binary = it->binary;
            mergeGroup.push_back(vector<Implicants>());
            Implicants im(key, binary);
            mergeGroup[mgIdx].push_back(im);
        }
        ++it;
    }
}

void QM::DeletePI(int j) {
    for (int i=0; i<epi.size(); i++) {
        if (hiddenEpi[i][j] == -1) hiddenEpi[i][j] = -3;
    }
}

void QM::LastPrint() {
    int idx = 0;
    int plus = 0;
    string f = "F = ";

    for (Implicants im : mergeGroup[4]) {
        idx = 0;
        for (int b : im.binary) {
            if (idx == 0) {
                if (b == 1) f+= "A";
                else if (b == 0) f += "A'";
            }
            else if (idx == 1) {
                if (b == 1) f+= "B";
                else if (b == 0) f += "B'";
            }
            else if (idx == 2) {
                if (b == 1) f+= "C";
                else if (b == 0) f += "C'";
            }
            else if (idx == 3) {
                if (b == 1) f+= "D";
                else if (b == 0) f += "D'";
            }
            idx++;
        }
        if (plus < mergeGroup[4].size()-1) {
            f+= " + ";
            plus++;
        }
    }
    cout << f << endl;
    cout << endl;
}


int main() {
    QM q;
    q.Manage();
    return 0;
}