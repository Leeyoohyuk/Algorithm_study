#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int map[51][51];
vector<pair<int, int>> chicken;
vector<pair<int, int>> house;
int minimum = 999999;

int dist(pair<int, int> houseloc, pair<int, int> chickloc);
int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 2) {
                chicken.push_back(make_pair(i, j));
            }
            else if (map[i][j] == 1) {
                house.push_back(make_pair(i, j));
            }
        }
    }
    int chickensize = chicken.size();
    int housesize = house.size();

    // ���� ����
    vector<int> comb;
    for (int i = 0; i < chickensize - M; i++) {
        comb.push_back(0);
    }
    for (int i = 0; i < M; i++) {
        comb.push_back(1);
    }
    do {
        int subtotal = 0;
        vector<int> dists; // �� ������ ���� ����� ġŲ������ �Ÿ�
        for (int i = 0; i < housesize; i++) {
            dists.push_back(999999);
        }
        for (int i = 0; i < chickensize; i++) {
            if (comb[i] == 1) { // ���� ���տ��� ���õ� ġŲ���� ���
                for (int j = 0; j < housesize; j++) {
                    dists[j] = min(dists[j], (dist(house[j], chicken[i]))); // �Ÿ�����Ͽ� �ּҰ����� ����
                }
            }
        }
        for (int i = 0; i < housesize; i++) {
            subtotal += dists[i];
        }
        minimum = min(minimum, subtotal);
    } while (next_permutation(comb.begin(), comb.end()));

    cout << minimum;

    return 0;
}

int dist(pair<int, int> houseloc, pair<int, int> chickloc) {
    return abs(houseloc.first - chickloc.first) + abs(houseloc.second - chickloc.second);
}