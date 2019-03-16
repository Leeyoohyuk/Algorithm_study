#include <stdio.h>
#include <algorithm>
using namespace std;

int main()
{
	int size;
	long long max;
	scanf_s("%d", &size);
	long long *cardarr = new long long[size+1];
	for (int i = 1; i <= size; i++)
	{
		scanf_s("%lld", &cardarr[i]);
	}
	sort(cardarr + 1, cardarr + size +1);
	int cnt = 1;
	int maxcnt = 1;
	max = cardarr[1];
	for (int i = 2; i <= size; i++)
	{
		if (cardarr[i] == cardarr[i - 1])
		{
			cnt++;
		}
		else // ������ ���� �ٲ� ���
		{
			if (cnt > maxcnt) // ���� maxcnt ������ cnt�� Ŭ ��
			{
				maxcnt = cnt; // cnt�� maxcnt�� �ϰ�
				max = cardarr[i - 1]; // max�� ���� ī��ѹ���
			}
			cnt = 1;
		}
		if (i == size)
		{
			if (cnt > maxcnt) // ���� maxcnt ������ cnt�� Ŭ ��
			{
				maxcnt = cnt; // cnt�� maxcnt�� �ϰ�
				max = cardarr[i - 1]; // max�� ���� ī��ѹ���
			}
		}
	}
	printf("%lld", max);
	return 0;
}