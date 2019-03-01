#include <iostream>
#include <algorithm>
using namespace std;
int cache[100001][3] = { 0 };
int arr[2][100001] = { 0 };
void InitArr(int sticknum) {
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j <= sticknum; j++) {
			int input;
			cin >> input;
			arr[i][j] = input;
		}
	}
}
int Cal_Max(int count) {

	cache[1][0] = 0;
	cache[1][1] = arr[0][1];
	cache[1][2] = arr[1][1];

	for (int i = 2; i <= count; i++) {
		cache[i][0] = max(cache[i - 1][0], max(cache[i - 1][1], cache[i -1][2])); // �ش翭 �������
		cache[i][1] = max(cache[i - 1][0], cache[i - 1][2]) + arr[0][i]; 
		// �ش翭 1�ప�� ���ϴ� ��� -> ������ 2�� ���� �����ϴ� ĳ�� or �ƹ��͵� �������� ���� ĳ�� �� �ִ밪�� ���Ѵ�
		cache[i][2] = max(cache[i - 1][0], cache[i - 1][1]) + arr[1][i];
		// �ش翭 2�ప�� ���ϴ� ��� -> ������ 1�� ���� �����ϴ� ĳ�� or �ƹ��͵� �������� ���� ĳ�� �� �ִٰ��� ���Ѵ�
	}
	// ����� ���� 3������ �д� ����x, 1�� ����, 2�� ����
	return max(cache[count][0], max(cache[count][1], cache[count][2])); // ����� ĳ�� �� �ִ밪 ����
}
int main() {
	int testNum;
	cin >> testNum;
	for (int i = 0; i < testNum; i++) {
		int stickNum;
		cin >> stickNum;
		InitArr(stickNum);
		cout << Cal_Max(stickNum) << endl;
	}
}
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
	int d[2][100001], a[2][100001]; // DP�� ĳ�� d�� �� ��ƼĿ�� a
	d[0][0] = d[1][0] = 0;
	int i, j, n, t; // for���� i,j �� ����Ƚ�� t, ���� n
	cin >> t;
	while (t-- > 0)
	{
		cin >> n;
		for (i = 0; i <= 1; i++)
			for (j = 1; j <= n; j++)
				cin >> a[i][j];
		d[0][1] = a[0][1];
		d[1][1] = a[1][1];
		for (i = 2; i <= n; i++)
		{
			// 1���� �밢��or 2���� �밢�� + �ش翭 ��ƼĿ ��
			d[0][i] = max(d[1][i - 1], d[1][i - 2]) + a[0][i]; // 1�� ������ �����ϴ°�� 
			d[1][i] = max(d[0][i - 1], d[0][i - 2]) + a[1][i]; // 1�� �Ʒ����� �����ϴ°��
		}
		cout << max(d[0][n], d[1][n]) << endl;
	}
	return 0;
}