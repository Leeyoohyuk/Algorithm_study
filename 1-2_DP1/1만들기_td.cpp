#include <iostream>
using namespace std;

int result = 1000;

void makeOne(int num, int cnt)
{
	if (num == 1) // num이 1까지 도달했을 경우 cnt를 result에 저장한다. 
	// 여러가지 가능값들에 의해 result가 계속 변한다
	{
		if (cnt < result)
			result = cnt;
		return;
	}
	if (cnt > result) // 기존보다 큰 카운트 값이 들어왔을 경우 무조건 함수종료
		// 깊이조절
	{
		return;
	}
	if (num % 3 == 0)
		makeOne(num / 3, cnt + 1);
	if (num % 2 == 0)
		makeOne(num / 2, cnt + 1);
	makeOne(num - 1, cnt + 1);

	return;
}

int main()
{
	int number;
	cin >> number;
	makeOne(number, 0);
	cout << result;
	return 0;
}