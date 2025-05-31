#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "conio.h"

using namespace std;

class Binary {  // 0~15 Binary 저장 클래스
protected:
    vector<vector<int>> binaryArr; // 인덱스 0~15까지 사이즈 4 int형 vector로 Binary 저장
public:
    Binary();
    vector<int> TenToBinary(int n);
};

Binary::Binary() {
    for (int i = 0; i <= 15; i++)
        binaryArr.push_back(TenToBinary(i));
}

vector<int> Binary::TenToBinary(int n) {    // 0 ~ 15, Binary 찾는 함수
    vector<int> b(4);
    for (int i = 3; i >= 0; i--) {
        b[i] = n % 2;
        n /= 2;
    }
    return b;
}

class Implicants {  // merge 작업 후 key, binary 저장위한 클래스(key가 여러개일 상황 대비, vector로 선언)
public:
    vector<int> key, binary;
    Implicants(vector<int> k, vector<int> b) : key(k), binary(b) {}
};

class QM : public Binary {  // 퀸 맥클러스키 전반적인 코드 진행 클래스
private:
    int inputArr[16];   // 처음에 받은 0과 1 값 저장 변수
    int mgIdx = 0;      // mergeGroup 상태 체크 변수
    vector<int> epiTop; // 도표 윗부분
    vector<vector<int>> piTable, epi, hiddenEpi; // EPI 도표(X만 표시, O로 표시, erase 작업 후)
    vector<vector<Implicants>> groupOne;   // 분류된 숫자들(1의 갯수로)
    vector<vector<Implicants>> mergeGroup;    // [0]: 하나만 다른면 그룹핑 , [1]: Prime Implicants, [2]: hidden PI, [3]: PI 총합, [4]: EPI

public:
    QM() {};    // 상속받은 Binary 생성자 호출위한 기본 생성자
    void Manage();  // 코드 전체적인 진행 관리
    void InitVector();
    void InputOneZero();
    void CheckInput(int i); // input 들어온 값들 1의 개수 체크 및 그룹핑
    void TwoMerge();
    void KeyComp(vector<int> n1, vector<int> n2);   // TwoMerge에서 받은 그룹 비교 및 merge 담당
    void SelfMerge(int n);  // 입력 값이 1개 or 2개 일 때 처리 위한 함수
    void ThreeMerge();
    void BinaryComp(Implicants n1, Implicants n2);  // ThreeMerge에서 받은 그룹 비교 및 merge 담당
    void RemoveDup();
    void FindHidden();
    void MergePi();
    void InitPITable();
    void SetPITable();
    void InitEPITable();
    void AddEPI();
    void DeletePI();
    void DeleteCol(int j);
    void AddHiddenEPI();

    void Screen(int n); // 출력관리 함수
    void GroupOnePrint();   // 1의 개수 그룹 프린트 함수
    void ThreePrintArr(int n);  // mergeGroup[0], mergeGroup[1] 출력
    void ShowPITable();     // PITable 출력(X만 있는 테이블)
    void ShowEPITable();    // EPITable 출력(O표시 된 테이블)
    void ShowDeleteEPI();   // DeleteEPI 출력(EPI 빼고 삭제 된 테이블)
    void LastPrint();       // 마지막 수식 출력
    ~QM() {};
};

void QM::Manage() {
    int screenNum = 0;
    vector<vector<Implicants>>::iterator it;
    vector<Implicants>::iterator i;

    InitVector();   // 1의 개수로 분류된 숫자 저장할 vector(groupOne) 초기화
    InputOneZero(); // 입력 받는 함수

    TwoMerge(); // groupOne토대로 binary 하나만 다르면 mergeGroup[0]에 저장하는 함수 *Key 2개
    if (mergeGroup[0].size() < 1) {
        for (it = groupOne.begin(); it != groupOne.end(); ++it){
            if (!it->empty()) {
                for (int a : it->begin()->key){
                    SelfMerge(a);
                }
            }
        }
        screenNum = 1;
    }

    ThreeMerge(); // mergeGroup[0]을 토대로 binary 하나만 다르면 mergeGroup[1]에 저장하는 함수 *Key 4개
    if ((mergeGroup[0].size() > 0) && (mergeGroup[1].size() < 1)) {
        mergeGroup[3] = mergeGroup[0];
        screenNum = 2;
    }

    if ((mergeGroup[0].size() > 0) && (mergeGroup[1].size() > 0)) {
        RemoveDup();    // mergeGroup[1]에서 중복된 값이 있으면 제거
        FindHidden();   // mergeGroup[1]에 겹치지 않는 값을 mergeGroup[0]에서 찾아, mergeGroup[2]에 저장
        MergePi();      // mergeGroup[1]과 mergeGroup[2]를 합쳐서 mergeGroup[3]에 저장
    }

    InitPITable(); // epiTop을 inputArr 활용해서 초기화, epiTop과 mergeGroup[3]을 활용해 piTable 생성
    SetPITable();  // piTable에 -1로 x 표시, 나머지는 0
    InitEPITable(); // 열에 혼자 있는 애들 체크해서 -2로 O표시
    AddEPI(); // O표시 되어있는 epi mergeGroup[4]에 저장
    DeletePI(); // 수평선 -1 찾아서 해당 열 -3으로 만들기(erase 작업),
    AddHiddenEPI(); // hiddenEPI, mergeGroup[4]에 저장
    Screen(screenNum);    // 출력 함수 호출
}

void QM::Screen(int n) {
    char key = 0;
    int print = 0, low=0, high;

    if (n == 0) high = 5;
    else if (n == 1) high = 3;
    else if (n == 2) high = 4;

    while (key != 27) {
        if (key == 77) { // Left
            if (print < high) print++;
        }
        else if (key == 75) { // Right
            if (low < print) print--;
        }

        system("clear");

        if (n == 0) {
            if (print == 0) GroupOnePrint();
            else if (print == 1) ThreePrintArr(0);
            else if (print == 2) ThreePrintArr(1);
            else if (print == 3) ShowPITable();
            else if (print == 4) ShowEPITable();
            else if (print == 5) ShowDeleteEPI();
        }
        else if (n == 1) {
            if (print == 0) GroupOnePrint();
            else if (print == 1) ShowPITable();
            else if (print == 2) ShowEPITable();
            else if (print == 3) ShowDeleteEPI();
        }
        else if (n == 2) {
            if (print == 0) GroupOnePrint();
            else if (print == 1) ThreePrintArr(0);
            else if (print == 2) ShowPITable();
            else if (print == 3) ShowEPITable();
            else if (print == 4) ShowDeleteEPI();
        }
        key = _getch();
    }
}

void QM::InitVector() {
    for (int i = 0; i < 5; i++) {
        groupOne.push_back(vector<Implicants>());
        mergeGroup.push_back(vector<Implicants>());
    }
}

void QM::InputOneZero() {
    for (int i = 0; i < 16; i++) {
        cout << "(" << setw(2) << i << ") ";
        for (int b : binaryArr[i]) {
            cout << b;
        }
        cout << ": ";
        cin >> inputArr[i];
        CheckInput(i);
    }
}

void QM::CheckInput(int i) {
    int cnt;
    vector<int> key, binary;

    if (inputArr[i] == 1) {
        cnt = count(binaryArr[i].begin(), binaryArr[i].end(), 1);
        key.push_back(i);
        for (int a = 0; a < 4; a++) {
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

void QM::SelfMerge(int n) {
    vector<int> key;
    key.push_back(n);
    Implicants im(key, binaryArr[n]);
    mergeGroup[3].push_back(im);
}

void QM::ThreeMerge() {
    int start = 0;
    vector<Implicants>::iterator it, second;

    for (it = mergeGroup[start].begin(); it!=mergeGroup[start].end(); ++it) {
        for (second = it+1; second != mergeGroup[start].end(); ++second) {
            BinaryComp(*it, *second);
        }
    }
}

void QM::KeyComp(vector<int> n1, vector<int> n2) {
    vector<int> key, binary;
    int cnt = 0;

    for (int i = 0; i < 4; i++) {
        if (binaryArr[n1[0]][i] != binaryArr[n2[0]][i]) cnt++;
    }
    if (cnt == 1) {
        key.push_back(n1[0]);
        key.push_back(n2[0]);
        for (int i = 0; i < 4; i++) {
            if (binaryArr[n1[0]][i] == binaryArr[n2[0]][i]) binary.push_back(binaryArr[n1[0]][i]);
            else binary.push_back(-1);
        }
        Implicants im(key, binary);
        mergeGroup[mgIdx].push_back(im);
    }
}

void QM::BinaryComp(Implicants n1, Implicants n2) {
    vector<int> key, binary;
    int cnt = 0;
    mgIdx = 1;

    for (int a = 0; a < 4; a++)
        if (n1.binary[a] != n2.binary[a]) cnt++;

    if (cnt == 1) {
        for (int i : n1.key)
            key.push_back(i);
        for (int i : n2.key)
            key.push_back(i);
        for (int b = 0; b < 4; b++) {
            if (n1.binary[b] == n2.binary[b]) binary.push_back(n1.binary[b]);
            else binary.push_back(-1);
        }
        Implicants im(key, binary);
        mergeGroup[mgIdx].push_back(im);
    }
}

void QM::RemoveDup() {
    vector<Implicants>::iterator it, second;

    for (it = mergeGroup[1].begin(); it != mergeGroup[1].end(); ++it) {
        sort(it->key.begin(), it->key.end());
    }

    for (it = mergeGroup[1].begin(); it != mergeGroup[1].end(); ++it) {
        second = it + 1;
        while (second != mergeGroup[1].end()) {
            if (it->key == second->key) second = mergeGroup[1].erase(second);
            else ++second;
        }
    }
}

void QM::FindHidden() {
    int cnt = 0;
    vector<Implicants>::iterator it, second;
    vector<int> key, binary;
    mgIdx = 2;

    for (it = mergeGroup[0].begin(); it != mergeGroup[0].end(); ++it) {
        cnt = 0;
        key.clear();
        binary.clear();
        for (second = mergeGroup[1].begin(); second != mergeGroup[1].end(); ++second) {
            if (includes(second->key.begin(), second->key.end(), it->key.begin(), it->key.end())) cnt++;
        }

        if (cnt == 0) {
            for (int i : it->key) {
                key.push_back(i);
            }
            for (int b : it->binary) {
                binary.push_back(b);
            }
            Implicants im(key, binary);
            mergeGroup[mgIdx].push_back(im);
        }
    }
}

void QM::MergePi() {
    vector<int> key, binary;
    vector<Implicants>::iterator it;
    mgIdx = 3;

    for (int i = 1; i <= 2; i++) {
        it = mergeGroup[i].begin();
        while (it != mergeGroup[i].end()) {
            key.clear();
            binary.clear();
            for (const int& k : it->key) {
                key.push_back(k);
            }
            for (const int& b : it->binary) {
                binary.push_back(b);
            }
            Implicants im(key, binary);
            mergeGroup[mgIdx].push_back(im);
            ++it;
        }
    }
}

void QM::GroupOnePrint() {
    int printCnt = 0, idx = 0;

    cout << right;
    cout << setw(12) << "ABCD" << endl;
    for (vector<Implicants>& i : groupOne) {
        printCnt = 0;
        if (!i.empty()) cout << idx;
        idx++;
        for (Implicants& j : i) {
            for (int& k : j.key) {
                if (printCnt == 0) printCnt++;
                else cout << " ";
                cout << "  (" << k << ") ";
                if (k < 10) cout << " ";
                for (int& a : j.binary) {
                    cout << a;
                }
            }
            cout << "   " << endl;
        }
        if (!i.empty()) cout << endl;
    }
}

void QM::ThreePrintArr(int n) {
    int countPrint = 0, back;
    string space;

    for (Implicants i : mergeGroup[n]) {
        space = "";
        cout << "(";
        countPrint = 0;
        back = 0;
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
            if (back < 10) space += " ";
        }
        cout << ")  " << space;
        for (int v : i.binary) {
            if (v == -1) cout << "-";
            else cout << v;
        }
        cout << endl;
    }
}

void QM::InitPITable() {
    vector<Implicants>::iterator it;

    for (int i=0; i<16; i++) {
        if (inputArr[i]) epiTop.push_back(i);
    }

    sort(epiTop.begin(), epiTop.end());
    piTable.assign(mergeGroup[3].size(), vector<int>(epiTop.size()));
}

void QM::SetPITable() {
    int xdx = 0;
    vector<int>::iterator ydx;
    vector<Implicants>::iterator it;

    for (it = mergeGroup[3].begin(); it != mergeGroup[3].end(); ++it) {
        for (int k : it->key) {
            ydx = find(epiTop.begin(), epiTop.end(), k);
            if (ydx != epiTop.end()) {
                piTable[xdx][distance(epiTop.begin(), ydx)] = -1;
            }
        }
        ++xdx;
    }
}

void QM::ShowPITable() {
    int print = 0, idx = 0, back;
    string space = "";
    string under = "┌";

    cout << left;
    cout << setw(18) << " ";
    for (int i : epiTop) {
        cout << setw(3) << i;
        under += "───";
    }
    cout << endl;
    cout << setw(16) << " ";
    cout << under;
    cout << endl;

    for (Implicants im : mergeGroup[3]) {
        space = "";
        print = 0;
        cout << "(";
        for (int k : im.key) {
            cout << left << k;
            back = k;
            if (print < im.key.size() - 1) {
                cout << ", ";
                print++;
            }
            if (back < 10) space += " ";
        }
        if (im.key.size() == 2) space += "        ";
        if (im.key.size() == 1) space += "            ";
        cout << ")";
        cout << space;
        cout << "│ ";
        for (int i : piTable[idx]) {
            if (i == -1) cout << setw(3) << "X";
            else cout << setw(3) << "  ";
        }
        cout << endl;
        idx++;
    }
}

void QM::InitEPITable() {
    int idx = 0, jdx = 0, cnt=0;
    epi.assign(piTable.size(), vector<int>(piTable.size()));
    copy(piTable.begin(), piTable.end(), epi.begin());

    for (int j = 0; j < epiTop.size(); j++) {
        cnt = idx = jdx = 0;
        for (int i = 0; i < epi.size(); i++) {
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

void QM::ShowEPITable() {
    int print = 0, idx = 0, back;
    string space;
    string under = "┌";

    cout << setw(18) << " ";
    for (int i : epiTop) {
        cout << setw(3) << i;
        under += "───";
    }
    cout << endl;
    cout << setw(16) << " ";
    cout << under;
    cout << endl;

    for (Implicants im : mergeGroup[3]) {
        space = "";
        print = 0;
        cout << "(";
        for (int k : im.key) {
            cout << left << k;
            back = k;
            if (print < im.key.size() - 1) {
                cout << ", ";
                print++;
            }
            if (back < 10) space += " ";
        }
        if (im.key.size() == 2) space += "        ";
        if (im.key.size() == 1) space += "            ";
        cout << ")";
        cout << space;
        cout << "│ ";
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
    int print = 0, idx = 0, back;
    string space;
    string under = "┌";

    cout << setw(18) << " ";
    for (int i : epiTop) {
        cout << setw(3) << i;
        under += "───";
    }
    cout << endl;
    cout << setw(16) << " ";
    cout << under;
    cout << endl;

    for (Implicants im : mergeGroup[3]) {
        space = "";
        print = 0;
        cout << "(";
        for (int k : im.key) {
            cout << left << k;
            back = k;
            if (print < im.key.size() - 1) {
                cout << ", ";
                print++;
            }
            if (back < 10) space += " ";
        }
        if (im.key.size() == 2) space += "        ";
        if (im.key.size() == 1) space += "            ";
        cout << ")";
        cout << space;
        cout << "│ ";
        for (int i : hiddenEpi[idx]) {
            if (i == -1) cout << setw(3) << "X";
            else if (i == -2) cout << setw(3) << "O";
            else cout << setw(3) << "  ";
        }
        cout << endl;
        idx++;
    }
    cout << endl;
    LastPrint();
}

void QM::AddEPI() {
    mgIdx = 4;
    vector<int> key, binary;
    vector<Implicants>::iterator it = mergeGroup[3].begin();

    mergeGroup.push_back(vector<Implicants>());

    for (vector<int> i : epi) {
        if (find(i.begin(), i.end(), -2) != i.end()) {
            key = it->key;
            binary = it->binary;
            Implicants im(key, binary);
            mergeGroup[mgIdx].push_back(im);
        }
        ++it;
    }
}

void QM::DeletePI() {
    mgIdx = 4;

    hiddenEpi.assign(epi.size(), vector<int>(epi.size()));
    copy(epi.begin(), epi.end(), hiddenEpi.begin());

    for (int i = 0; i < epi.size(); i++) {
        if (find(hiddenEpi[i].begin(), hiddenEpi[i].end(), -2) != hiddenEpi[i].end()) {
            for (int j = 0; j < epiTop.size(); j++) {
                if (hiddenEpi[i][j] == -1) DeleteCol(j);
            }
        }
    }
}

void QM::AddHiddenEPI() {
    int cnt;
    vector<int> key, binary;
    vector<Implicants>::iterator it = mergeGroup[3].begin();

    mergeGroup.push_back(vector<Implicants>());

    for (int i = 0; i < epi.size(); i++) {
        cnt = 0;
        for (int j = 0; j < epiTop.size(); j++) {
            if (hiddenEpi[i][j] == -1) cnt++;
        }
        if (cnt == it->key.size()) {
            key = it->key;
            binary = it->binary;
            Implicants im(key, binary);
            mergeGroup[mgIdx].push_back(im);
        }
        ++it;
    }
}

void QM::DeleteCol(int j) {      // j행, 열에 있는 값들 삭제
    for (int i = 0; i < epi.size(); i++)
        if (hiddenEpi[i][j] == -1) hiddenEpi[i][j] = -3;
}

void QM::LastPrint() {
    int idx = 0, plus = 0;
    string f = "F = ";

    for (Implicants im : mergeGroup[4]) {
        idx = 0;
        for (int b : im.binary) {
            if (idx == 0) {
                if (b == 1) f += "A";
                else if (b == 0) f += "A'";
            }
            else if (idx == 1) {
                if (b == 1) f += "B";
                else if (b == 0) f += "B'";
            }
            else if (idx == 2) {
                if (b == 1) f += "C";
                else if (b == 0) f += "C'";
            }
            else if (idx == 3) {
                if (b == 1) f += "D";
                else if (b == 0) f += "D'";
            }
            idx++;
        }
        if (plus < mergeGroup[4].size() - 1) {
            f += " + ";
            plus++;
        }
    }
    cout << f << endl;
}

int main() {
    QM q;
    q.Manage();
    while (1) {}
    return 0;
}