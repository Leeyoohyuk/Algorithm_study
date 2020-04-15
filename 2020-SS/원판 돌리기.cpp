#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int totalCircle;
int number;
bool findSame = false;
int mx[4]= { 1, 0, 0, -1 };
int my[4] = { 0, -1, 1, 0};
vector<vector<int>> wholeCircle;
void rotate(int circleNum, int direction, int step);
void DFS(bool **visit, int i, int j, bool recursiveChecker);
int main() {
	int rotation;
	cin >> totalCircle >> number >> rotation;

	// �ʱ� ���� �հ� ������ ����
	int total = 0;
	int currentElement = totalCircle * number;

	for (int i = 0; i < totalCircle; i++) {
		vector<int> eachCircle;
		for (int j = 0; j < number; j++) {
			int input;
			cin >> input;
			eachCircle.push_back(input);
			total += input;
		}
		wholeCircle.push_back(eachCircle);
	}

	// �� ȸ�� Ƚ����ŭ �ݺ�
	for (int i = 0; i < rotation; i++) {
		int baseNumber;
		int direction;
		int step;
		cin >> baseNumber >> direction >> step;

		// base number�� �� ���� ������ ���� �������� ����
		int targetCount = totalCircle / baseNumber;
		for (int j = 1; j <= targetCount; j++) {
			// �� ������ ȸ����Ų��
			rotate(j * baseNumber -1, direction, step);
		}

		// visit �ʱ�ȭ
		bool** visit = new bool*[totalCircle];
		for (int j = 0; j < totalCircle; j++) {
			visit[j] = new bool[number];
			for (int k = 0; k < number; k++) {
				visit[j][k] = false;
			}
		}

		// ���� DFS ���࿡�� Same�� �ִ°��� �˻��ϴ� ����
		findSame = false;
		for (int j = 0; j < totalCircle; j++)
		{
			for (int k = 0; k < number; k++)
			{
				if (!visit[j][k] && wholeCircle[j][k]) {
					DFS(visit, j, k, false);
				}
			}
		}
		
		// 0 division protection
		if (currentElement == 0) {
			total = 0;
			break;
		}
		float avg = (float)total / currentElement;
		total = 0;
		currentElement = 0;
		if (findSame) { // ��������� �ִٸ� �׳� ���� ����
			for (vector<vector<int>>::iterator iter = wholeCircle.begin(); iter != wholeCircle.end(); iter++) {
				for (vector<int>::iterator iter2 = iter->begin(); iter2 != iter->end(); iter2++) {
					if (*iter2 != 0) {
						total += *iter2;
						currentElement++;
					}
				}
			}
		}
		else { // ��������� ��ã�Ҵٸ� �� ���Ұ� ����
			for (vector<vector<int>>::iterator iter = wholeCircle.begin(); iter != wholeCircle.end(); iter++) {
				for (vector<int>::iterator iter2 = iter->begin(); iter2 != iter->end(); iter2++) {
					if (*iter2 != 0) {
						if (*iter2 > avg) {
							*iter2 = *iter2-1;
						}
						else if (*iter2 < avg) {
							*iter2 = *iter2+1;
						}
						total += *iter2;
						currentElement++;
					}
				}
			}
		}
	}
	cout << total;
}

// ���� ȸ��
void rotate(int circleNum, int direction, int step) {
	int size = wholeCircle[circleNum].size();
	int *arr = new int[size];
	if (direction == 0) { // �ð����
		for (int i = 0; i < size; i++) {
			int nextpos = (i + step) % size;
			arr[nextpos] = wholeCircle[circleNum][i];
		}
	}
	else { // �ݽð����
		step = size - step;
		for (int i = 0; i < size; i++) {
			int nextpos = (i + step) % size;
			arr[nextpos] = wholeCircle[circleNum][i];
		}
	}

	// ȸ�� ������ ���� -> ȸ�� ���� ���� ������� ����
	wholeCircle[circleNum].clear();
	for (int i = 0; i < size; i++) {
		wholeCircle[circleNum].push_back(arr[i]);
	}
}

// DFS
void DFS(bool **visit, int x, int y, bool recursiveChecker) {
	visit[x][y] = true; // �湮 ǥ��
	for (int run = 0; run < 4; run++) {
		int nx = x + mx[run];
		int ny = y + my[run];
		if (ny == number) ny = 0;
		else if (ny < 0) ny = number - 1;
		if (nx == totalCircle) {
			continue;
		}
		if (nx == -1) {
			continue;
		}
		if ((wholeCircle[nx][ny] == wholeCircle[x][y]) && !visit[nx][ny] && wholeCircle[nx][ny]) {
			recursiveChecker = true;
			DFS(visit, nx, ny, recursiveChecker);
		}
	}
	// ���� �Լ��� ���ȣ���̶��?
	if (recursiveChecker) {
		findSame = true; // �̹� DFS���� �����ϰ� ���� ���� ã�Ҵٴ� ������ �����Ѵ�
		wholeCircle[x][y] = 0; // ���ȣ���� ���� �� ���� ���ڸ� ���� (����0�� X�� ����)
	}
}