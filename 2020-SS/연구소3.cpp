#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N = 0;
int M = 0;

// ������ ����
int lab[51][51];
// ���� ����
int infection[51][51];
// ���̷��� ��ġ
vector<pair<int, int> > virus;
// for BFS
queue<pair<int, int> > que;
int least = 100000;
bool flag = false;
// �����¿�
int directorX[4] = { -1, 1, 0, 0 };
int directorY[4] = { 0, 0, -1, 1 };

void BFS(int space);
void infectionInit();
int main() {
    int space = 0;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> lab[i][j];
            if (lab[i][j] == 2) {
                virus.push_back(make_pair(i, j));
            }
            else if (lab[i][j] == 0) {
                space++;
            }
        }
    }

    int virusSpace = virus.size();
    // ���̷��� Ȱ�� ��ġ ������ ���� ����: visrusSize �� M�� ����
    vector<int> selection;
    for (int i = 1; i <= virusSpace - M; i++) {
        selection.push_back(0);
    }
    for (int i = 1; i <= M; i++) {
        selection.push_back(1);
    }

    // ��� ���տ����� ����
    do {
        infectionInit(); // �������� �ʱ�ȭ
        for (int i = 0; i < selection.size(); i++) {
            if (selection[i] == 1) {
                que.push(make_pair(virus[i].first, virus[i].second));
                infection[virus[i].first][ virus[i].second] = -3;
            }
        }
        BFS(space);
    } while (next_permutation(selection.begin(), selection.end()));

    if (flag) {
        cout << least;
    }
    else {
        cout << -1;
    }

    return 0;
}

void infectionInit() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (lab[i][j] == 0) { // ����� 
                infection[i][j] = 0;
            }
            else if (lab[i][j] == 1){ // �� ��ġ�� -1
                infection[i][j] = -1;
            }
            else { // ���̷��� ��ġ
                infection[i][j] = -2;
            }
        }
    }
}

void BFS(int space) {
    int maximum = 0;
    while (!que.empty()) {
        pair<int, int> location = que.front();
        int X = location.first;
        int Y = location.second;
        que.pop();
        for (int i = 0; i < 4; i++) {
            int nX = X + directorX[i];
            int nY = Y + directorY[i];
            if (space <= 0) {
                break;
            }
            if (nX >= 1 && nX <= N && nY >= 1 && nY <= N) {
                // ���ο� ��ġ�� �� ���� or ���̷��� ��ġ�� ��� ����
                if (infection[nX][nY] == 0 || infection[nX][nY] == -2) {
                    if (infection[nX][nY] == 0) {
                        space--;
                    }
                    // ���� ��ġ�� ���̷��� ������ ���
                    if (infection[X][Y] == -3) {
                        infection[nX][nY] = 1; // ������ġ�� �ð��� 1�� ����
                    }
                    else { // ���� ��ġ�� ���̷��� ���������� ���
                        infection[nX][nY] = infection[X][Y] + 1;
                    }
                    que.push(make_pair(nX, nY));
                }
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            maximum = max(infection[i][j], maximum);
            if (infection[i][j] == 0) { // ������Ű�� ����ĭ�� ������ ���з� �ٷ� ����
                return;
            }
        }
    }
    flag = true;
    least = min(least, maximum);
}