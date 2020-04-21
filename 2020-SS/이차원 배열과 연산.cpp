#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int r;
int c;
int k;
int row = 3;
int col = 3;
vector<pair<int, int>> realPair; // ������׷� �� ��ȿ pair ����
int map[101][101]; // ���� �ʱ�ȭ 0���� �Ǿ� ����
int histogram[101]; // ������׷� �ľ�

int calculate();
void calculateR();
void calculateC();

int main() {
	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> map[i][j];
		}
	}
	cout << calculate();
	return 0;
}

int calculate() {
	int time = 0;
	do {
		if (row >= r && col >= c) { // ����
			if (map[r][c] == k) {
				return time;
			}
		}
		time++;
		if (row >= col) {
			calculateR();
		}
		else {
			calculateC();
		}
	} while (time <= 100);
	return -1;
}

// R ���
void calculateR() {
	int maximum = 0;
	for (int i = 1; i <= row; i++) {
		realPair.clear(); // realPair �ʱ�ȭ
		fill(histogram, histogram + 101, 0); // histogram �ʱ�ȭ

		for (int j = 1; j <= col; j++) {
			histogram[map[i][j]]++; // �ε��� = �ش� ��, ���� = ���� Ƚ��
			// ** �߿�! map�� 0�� ���� histogram�� ������ ������ ������ ����
			map[i][j] = 0; // ���� �� �ش� �ڸ� �������
		}
		for (int j = 1; j <= 100; j++) {
			if (histogram[j] != 0) { // ������׷� 0�� �ƴ� ��� (1ȸ�� ���� ����)
				realPair.push_back(make_pair(histogram[j], j)); // realPair�� ��´�
			}
		}
		// realPair�� �ε��� ����, �ε��� ������ �������
		// sort �� ���� ������ ������ ����, ������ ��� �ε��� ���� �� ����
		sort(realPair.begin(), realPair.end());

		// �� ������ ����(�ε���)�� �ִ°�?
		int pairSize = realPair.size();
		int localMax = 0; // ���� ���� ����
		// �ε���, �ε��� ���� ������ map�� �ٽ� ����
		for (int j = 0; j < pairSize; j++) {
			map[i][++localMax] = realPair[j].second;
			map[i][++localMax] = realPair[j].first;
		}
		maximum = max(localMax, maximum); // �� ���� ����ϸ� ���� �� ���� �̴´�.
	}
	col = maximum; // �ִ뿭 ����
}

void calculateC() {
	int maximum = 0;
	for (int i = 1; i <= col; i++) {
		realPair.clear();
		fill(histogram, histogram + 101, 0);
		for (int j = 1; j <= row; j++) {
			histogram[map[j][i]]++;
			map[j][i] = 0;
		}
		for (int j = 1; j <= 100; j++) {
			if (histogram[j] != 0) {
				realPair.push_back(make_pair(histogram[j], j));
			}
		}
		sort(realPair.begin(), realPair.end());

		int pairSize = realPair.size();
		int localMax = 0;
		for (int j = 0; j < pairSize; j++) {
			map[++localMax][i] = realPair[j].second;
			map[++localMax][i] = realPair[j].first;
		}
		maximum = max(localMax, maximum);
	}
	row = maximum;
}