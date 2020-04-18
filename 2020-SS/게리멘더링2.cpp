#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int least = 100000;
int N;
int map[21][21];
int electionArea[21][21] = { 0 };
int area[5] = { 0 };
void checkBoundaryLength(int x, int y);
void checkArea5Boundary(int x, int y, int d1, int d2);
void checkArea5();
void checkAreas(int x, int y, int d1, int d2);
int calculate();
vector<int> edges;
int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	
	// map�� �»� -> ���� ������ x, y ����
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			checkBoundaryLength(i, j);
		}
	}

	cout << least;
	return 0;
}

// ������ x, y�� ���� ������ ��輱 �� d1, d2�� ã�´�
void checkBoundaryLength(int x, int y) {
	for (int d1 = 1; d1 < N - 1; d1++) {
		for (int d2 = 1; d2 < N - 1; d2++) {
			if ((x + d1 + d2) <= N && (1 <= (y - d1)) && (y + d2) <= N) {
				checkArea5Boundary(x, y, d1, d2);
			}
		}
	}
}

// ���ǿ� �´� d1, d2�κ��� ���ű� 5���� ���� ��踦 ��´�
void checkArea5Boundary(int x, int y, int d1, int d2) {
	edges.push_back(x); // top X
	edges.push_back(x + d1 + d2); // bottom

	electionArea[x][y] = 5;
	for (int i = 1; i <= d1; i++) { 
		electionArea[x + i][y - i] = 5;
	}
	for (int i = 1; i <= d2; i++) {
		electionArea[x + i][y + i] = 5;
	}
	for (int i = 0; i <= d2; i++) {
		electionArea[x + d1 + i][y - d1 + i] = 5;
	}
	for (int i = 0; i <= d1; i++) {
		electionArea[x + d2 + i][y + d2 - i] = 5;
	}

	checkArea5();
	checkAreas(x, y, d1, d2);
	least = min(least, calculate());

	edges.clear(); // ��� ������ �ʱ�ȭ
	fill(&electionArea[0][0], &electionArea[20][21], 0); // ���ű� ���� �ʱ�ȭ
}

// 5�� ���� ��� ���� ���ű��� 5�� ���ű��� �����Ѵ�
void checkArea5() {
	for (int i = 1; i <= N; i++) {
		bool flag = false;
		for (int j = 1; j <= N; j++) {
			if (i > edges[0] && i < edges[1]) {
				if (electionArea[i][j] == 5) {
					flag = !flag;
				}
			}
			if (flag) { // �÷��� ���� ��� 5�� �ٲ�
				electionArea[i][j] = 5;
			} // �÷��׸� ã�ƺ���.
		}
	}
}

void checkAreas(int x, int y, int d1, int d2) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (electionArea[i][j] != 5) {
				if (i < x + d1 && j <= y) {
					electionArea[i][j] = 1;
				}
				else if (i <= x + d2 && j > y) {
					electionArea[i][j] = 2;
				}
				else if (i >= x + d1 && j < y - d1 + d2) {
					electionArea[i][j] = 3;
				}
				else if (i > x + d2 && j >= y - d1 + d2) {
					electionArea[i][j] = 4;
				}
			}
		}
	}
}

int calculate() {
	vector<int> num(5, 0);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			num[electionArea[i][j]-1] += map[i][j];
		}
	}
	int maximum = 0;
	int minimum = 100000;
	for (int people : num) {
		if (maximum < people) {
			maximum = people;
		}
		if (minimum > people) {
			minimum = people;
		}
	}

	return maximum - minimum;
}