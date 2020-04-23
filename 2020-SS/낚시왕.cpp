#include <iostream>
#include <vector>
using namespace std;

struct shark {
	int r;
	int c;
	int s; // �ӷ�
	int d; // ���� - ���Ͽ���
	int z; // ũ��
};
int directorX[5] = { 0, -1, 1, 0, 0 };
int directorY[5] = { 0, 0, 0, 1, -1 };

bool map[101][101]; // ��� ���� ǥ��
shark sharkmap[101][101]; // ��� ����
int R;
int C;
int sharks;
int point = 0;

void fishing();
void sharkmoving();
int main() {
	fill(&map[0][0], &map[100][101], false);
	cin >> R >> C >> sharks;
	int r;
	int c;
	int s;
	int d;
	int z;
	for (int i = 0; i < sharks; i++) {
		cin >> r >> c >> s >> d >> z;
		shark one;
		one.r = r;
		one.c = c;
		one.s = s;
		one.d = d;
		one.z = z;

		map[r][c] = true;
		sharkmap[r][c] = one;
	}
	fishing();
	cout << point;
}

void fishing() {
	for (int i = 1; i <= C; i++) {
		for (int j = 1; j <= R; j++) {
			if (map[j][i]) { // �� ������?
				point += sharkmap[j][i].z;
				map[j][i] = false;
				sharkmap[j][i].z = 0; // �� ������ ��Ÿ��
				break; // ��� ���� ������.
			}
		}
		// ��� �̵�
		sharkmoving();
	}
}

void sharkmoving() {
	vector<shark> aftermove;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (map[i][j]) { // �� �ִ� ���
				shark temp = sharkmap[i][j];
				temp.r = temp.r + (temp.s % ((R - 1) * 2)) * directorX[temp.d];
				temp.c = temp.c + (temp.s % ((C - 1) * 2)) * directorY[temp.d];
				while (temp.r > R || temp.r < 1 || temp.c > C || temp.c < 1) {
					if (temp.r > R) {
						temp.r = R - (temp.r - R);
						temp.d = 1;
					}
					else if (temp.r < 1) {
						temp.r = 1 + (1 - temp.r);
						temp.d = 2;
					}

					if (temp.c > C) {
						temp.c = C - (temp.c - C);
						temp.d = 4;
					}
					else if (temp.c < 1) {
						temp.c = 1 + (1 - temp.c);
						temp.d = 3;
					}
				}
				map[i][j] = false;
				aftermove.push_back(temp); // �̵��� ���� ��� ��ġ, ���� ���� ���
			}
		}
	}
	// ��� ���ġ
	fill(&map[0][0], &map[100][101], false);
	for (int i = 0; i < aftermove.size(); i++) {
		int x = aftermove[i].r;
		int y = aftermove[i].c;
		// ���ο� ��ġ�� �� ���� ��� map, sharkmap ����
		if (map[x][y] == true) {
			if (sharkmap[x][y].z < aftermove[i].z) {
				sharkmap[x][y] = aftermove[i];
			}
		}
		else {
			map[x][y] = true;
			sharkmap[x][y] = aftermove[i];
		}
	}
}