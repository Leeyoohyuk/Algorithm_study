#include <iostream>
#include <list>
#include <string>
using namespace std;

int main()
{
	list<char> li; // ���ڿ��� ��� ���� ����Ʈ

	string word; // ó�� �Է¹޴� ����
	int cnt = 0; // ��ɾ� ����
	cin >> word;
	cin >> cnt;

	char command, ch; // Ŀ�ǵ�� P��ɾ ���Ǵ� ĳ����
	
	for (int i = 0; i < word.size(); i++)
	{
		li.push_back(word[i]); // ����Ʈ�� ���ڿ� ����
	}

	list<char>::iterator iter; // ���ͷ����� ����
	iter = li.end(); // ���ͷ����ʹ� ������ ��

	for (int i = 0; i < cnt; i++)
	{
		cin >> command;
		switch (command)
		{
		case 'L':
			if (iter == li.begin()) // iter �� ó���̸� ����X
				break;
			else {
				iter--; // �ƴϸ� Ŀ�� �̵�
				break;
			}
		case 'D':
			if (iter == li.end()) // iter �� ���̸� ����X
				break;
			else {
				iter++; // �ƴϸ� Ŀ�� �̵�
				break;
			}
		case 'B': // ���ͷ����� �ٽ� Ȯ��
			if (iter == li.begin()) // iter �� ó���̸� ����X
				break;
			else {
				iter--;
				iter = li.erase(iter); // iter�� ����Ű�� �� ����
				break;
			}
		case 'P':
			cin >> ch;
			li.insert(iter, ch);
			break;
		default:
			break;
		}
	}

	for (iter = li.begin(); iter != li.end(); iter++)
	{
		cout << *iter;
	}
	return 0;
}