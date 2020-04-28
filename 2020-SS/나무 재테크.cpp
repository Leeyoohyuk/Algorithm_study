#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int M;
int K;
int directorX[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int directorY[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

int map[11][11]; // ���� ���� ���
int A[11][11]; // �κ��� �߰��ϴ� ���
vector<int> tree[11][11]; // ���� ��ġ�� ������

// �Ʒ����� ���� ���� ����ü
struct Tree {
	int r;
	int c;
	int age;
};
vector<Tree> deathTrees; // ���� ���� ����
vector<Tree> age5; // ���̰� 5�� ����� ���� ����

void spring();
void summer();
void fall();
void winter();
int main() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] = 5;
			cin >> A[i][j];
		}
	}
	int x;
	int y;
	int z;
	for (int i = 1; i <= M; i++) {
		cin >> x >> y >> z;
		tree[x][y].push_back(z);
	}
	while (K--) {
		spring();
		summer();
		fall();
		winter();
	}
	int total = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			total += tree[i][j].size();
		}
	}
	cout << total;
}

void spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int deathtree = 0;
			for (int k = 0; k < tree[i][j].size(); k++){
				if (tree[i][j][k] <= map[i][j]) {
					map[i][j] -= tree[i][j][k]; // �� ��� ����
					tree[i][j][k]++; // ���� ���� ����
					
					if (tree[i][j][k] % 5 == 0) { // ���̰� 5�� ����� ����
						Tree tree5;
						tree5.r = i;
						tree5.c = j;
						tree5.age = tree[i][j][k];
						age5.push_back(tree5);
					}
				}
				else {
					deathtree++; // ���� ���� ���� ����
				}
			}
			for (int k = 0; k < deathtree; k++) { // ���� ���� ����
				Tree dtree;
				dtree.r = i;
				dtree.c = j;
				dtree.age = tree[i][j].back();
				deathTrees.push_back(dtree);
				tree[i][j].pop_back(); // ����ִ� �������� ����
			}
		}
	}
}

void summer() {
	for (int i = 0; i < deathTrees.size(); i++) {
		map[deathTrees[i].r][deathTrees[i].c] += (deathTrees[i].age / 2);
	}
	deathTrees.clear();
}

void fall() {
	for (int i = 0; i < age5.size(); i++) {
		for (int j = 0; j < 8; j++) {
			int nr = age5[i].r + directorX[j];
			int nc = age5[i].c + directorY[j];
			if (nr > 0 && nr <= N && nc > 0 && nc <= N) {
				tree[nr][nc].push_back(1);
			}
		}
	}
	age5.clear();
}

void winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] += A[i][j];
			sort(tree[i][j].begin(), tree[i][j].end());
		}
	}
}