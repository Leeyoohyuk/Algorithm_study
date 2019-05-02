#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
using namespace std;

vector<int> per(20);
int check[21] = { 0 };
long long int number = 1;

long long int Factorial(long long int n);
void prob1(int size);
void prob2(int size);
int main()
{
	int size, cmd;
	scanf_s("%d", &size);
	scanf_s("%d", &cmd);
	switch (cmd)
	{
	case 1:
		prob1(size);
		break;
	case 2:
		prob2(size);
		break;
	default:
		break;
	}

	return 0;
}

void prob1(int size)
{
	scanf_s("%lld", &number); // ã����� ���� �Է�
	for (int i = 0; i < size; i++)
	{
		long long int Fact = Factorial(size - i - 1); // �� �׿��� ���� �� �ִ� ���丮�� size 20�̸�, ù���� 19!
		long long int prefix; 
		prefix = number / Fact; 
		// prefix�� �־��� ������ ���丮�� ���� �� �� ������ ����
		number = number % Fact; // �������� ����
		if (number == 0)
		{
			// �������� ���� ���� ���丮��� ������ ������ �����
			// �� ��� number��, prefix�� ���� ó���� ������Ѵ�
			// ex) Fact=4! �� ��� prefix�� number 1~24�� ���� 0�̾���� �׷��� �� ���꿡���� 24���� 1�̳���
			// number�� ������, �� ������������ 0���� ���ŵǴµ� �׷��� �Ǹ� Ʋ��
			number += Fact; 
			prefix--;
		}
		int count = 0;
		for (int j = 1; j <= size; j++)
		{
			if (check[j] != 1)
				count++;
			if (count == prefix + 1)
			{
				per[i] = j;
				check[j] = 1;
				break;
			}
		}
		printf("%d ", per[i]);
	}
}

void prob2(int size)
{
	for (int i = 0; i < size; i++)
	{
		scanf_s("%d", &per[i]);
		int count = 0;
		check[per[i]] = 1;
		for (int j = 1; j < per[i]; j++)
		{
			if (check[j] != 1)
				count++;
		}
		number = number + count * Factorial(size - i - 1);
	}
	printf("%lld", number);
}

long long int Factorial(long long int n) {

	long long int result = 1;

	for (int i = 1; i <= n; ++i)
		result *= i;

	return result;
}