#include <iostream>
using namespace std;
// Ʋ�� ���
//int main()
//{
//	int input;
//	cin >> input;
//	int zerosum = 0;
//	int lastnumber = 1; // 0�̾ƴ� ���ڸ��� �����ϴ� ����
//	for (int i = 1; i <= input; i++)// ��ǲ ���丮�� ������
//	{
//		lastnumber = lastnumber * i;
//		cout << lastnumber << endl;
//		while (true)
//		{
//			if (lastnumber % 10 == 0) // 10���� ������ ���
//			{
//				lastnumber = lastnumber / 10; // lastnumber�� 10���� �����ش�
//				zerosum++; // 0�� ���� �Ѱ� �߰�
//			}
//			else
//			{
//				lastnumber = lastnumber % 10; // lastnumber�� 0�̾ƴ� ���� ���� ��� while ����
//				break;
//			}
//		}
//	}
//	cout << zerosum << endl;
//	return 0;
//}
int main()
{
	int input;
	int two = 0, five = 0;
	cin >> input;

	for (int i = 2; i <= input; i *= 2)
	{
		two += input / i;
	}
	for (int i = 5; i <= input; i *= 5)
	{
		five += input / i;
	}
	cout << ((two < five) ? two : five);
	return 0;
}
