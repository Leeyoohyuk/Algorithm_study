#include <vector>
#include <iostream>
using namespace std;

// ���͸� ���ȭ ���� �� ��,��,��,�ϴ� ����������
int directorX[4] = { 0, 0, -1, 1 };
int directorY[4] = { 1, -1 , 0, 0 };
int N, K;

// �ϳ��� ��Ŀ (��) ����ü, ��ġ�� ������ ��������
struct marker {
	pair<int, int> pos;
	int direction;
};

// ���� ĥ���� �ִ� ����
vector<vector<int>> map;

// ��Ŀ���� ���¸� �迭�� ����
vector<marker> markers;

int gameStart(vector<vector<vector<int>>> &markerMap);
int findLevel(int nowX, int nowY, int id, vector<vector<vector<int>>> &markerMap);
void move(int nowX, int nowY, int num, int newX, int newY, int level, vector<vector<vector<int>>> &markerMap, int color);
bool checkEnd(vector<vector<vector<int>>> &markerMap);

int main() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		vector<int> row;
		for (int j = 0; j < N; j++) {
			int mapElem;
			cin >> mapElem;
			row.push_back(mapElem);
		}
		map.push_back(row);
	}
	vector<vector<vector<int>>> markerMap(N, vector<vector<int>>(N, vector<int>(0)));
	for (int i = 0; i < K; i++) {
		int X;
		int Y;
		int direction;
		marker newMarker;
		cin >> X >> Y >> direction;
		newMarker.direction = direction - 1;
		newMarker.pos = make_pair(X - 1, Y - 1);

		markers.push_back(newMarker);
		// ��Ŀ���� ���� ĥ���� �ִ� map�� ũ��� �����ϴ�.
		// �� ���ڴ� � ��Ŀ���� �ö� �ִ����� ��Ÿ����
		// ��Ŀ(��)�� �� K���̱� ������ i�� �� �� ��Ŀ�� �����ϴ� ��ȣ�̴�.
		markerMap[X - 1][Y - 1].push_back(i);
	}

	// ���� ����
	cout << gameStart(markerMap);
	return 0;
}

int gameStart(vector<vector<vector<int>>> &markerMap) {
	int i = 1;
	while (i <= 1000) {
		// 1ȸ�� ��Ŀ ������ŭ ���� ���� ����
		for (int num = 0; num < K; num++) {

			int direction = markers[num].direction;

			int nowX = markers[num].pos.first;
			int nowY = markers[num].pos.second;
			int newX = nowX + directorX[direction];
			int newY = nowY + directorY[direction];
			int level = findLevel(nowX, nowY, num, markerMap);
	
			// ���� ����� ��� color = 2 �� �����ϰ� ������
			if (newX < 0 || newY >= N ||  newX >= N || newY < 0) {
				move(nowX, nowY, num, newX, newY, level, markerMap, 2);
			} // �������� �̵��� ��ġ color ��� ���۽�Ų��
			else {
				move(nowX, nowY, num, newX, newY, level, markerMap, map[newX][newY]);
			} 
			// ���� ������ ���������� ������ �������� �˻��Ѵ�
			if (checkEnd(markerMap)) {
				return i;
			}
		}
		i++;
	}

	return -1;
}

// ���� ��Ŀ�ʿ��� �ش� ��Ŀ�� ���̸� ã�´� (���°�� ���������ִ°�?)
int findLevel(int nowX, int nowY, int id, vector<vector<vector<int>>> &markerMap) {
	for (int i = 0; i < markerMap[nowX][nowY].size(); i++) {
		if (markerMap[nowX][nowY][i] == id) {
			return i;
		}
	}
}

void move(int nowX, int nowY, int curMarker, int newX, int newY, int level, vector<vector<vector<int>>> &markerMap, int color) {
	int removeCount = 0;
	if (color == 0) { // 0�� ��� �Ϲݵ��� ����
		for (level; level < markerMap[nowX][nowY].size(); level++) { // ��Ŀ�ʿ��� �ű���� ��Ŀ�� level �̻��� ��Ŀ�� �� �ű��
			// ��Ŀ���� ���ο� ��ġ�� push_back���� ���� ��Ŀ ��ȣ �߰�
			int id = markerMap[nowX][nowY][level];
			markerMap[newX][newY].push_back(id);
			// ���� ��Ŀ ����ü ��ġ ����
			markers[id].pos.first = newX;
			markers[id].pos.second = newY;

			// ��Ŀ���� ���� ��ġ���� ���� ��Ŀ ���� ī��Ʈ
			removeCount++;
		} 
		// ��Ŀ���� ���� ��ġ���� pop_back���� ���� ��Ŀ�� ����
		for (int i = 0; i < removeCount; i++) {
			markerMap[nowX][nowY].pop_back();
		}

	}
	else if (color == 1) { // 0�� ���������� ��Ŀ�� �ڿ������� ������ �ű� (������ ����)
		for (int i = markerMap[nowX][nowY].size() - 1; i >= level; i--) {
			int id = markerMap[nowX][nowY][i];
			markerMap[newX][newY].push_back(id);
			markers[id].pos.first = newX;
			markers[id].pos.second = newY;
			removeCount++;
		}
		for (int i = 0; i < removeCount; i++) {
			markerMap[nowX][nowY].pop_back();
		}
	}
	else if (color == 2) { // 2�� ���� ���� ��Ŀ�� ������ ��ȯ�Ѵ�
		if (markers[curMarker].direction == 0 || markers[curMarker].direction == 2)
			markers[curMarker].direction++;
		else {
			markers[curMarker].direction--;
		}
		// ��ȯ�� ������ �̿��Ͽ� ���ο� ��ġ ���
		newX = nowX + directorX[markers[curMarker].direction];
		newY = nowY + directorY[markers[curMarker].direction];

		// ��ġ�� �ʿ��� ������� üũ
		if (!(newX < 0 || newY >= N || newX >= N || newY < 0)) {
			// �ȹ���ٸ� ��ȭ ��ġ�� color�� 2�� �ƴ��� üũ (2�̸� ���۾��� ����)
			if(map[newX][newY] != 2)
				move(nowX, nowY, curMarker, newX, newY, level, markerMap, map[newX][newY]);
		}
	}
}

bool checkEnd(vector<vector<vector<int>>> &markerMap) {
	for (marker elem : markers) {
		if (markerMap[elem.pos.first][elem.pos.second].size() >= 4)
			return true;
	}
	return false;
}