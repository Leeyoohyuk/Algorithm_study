#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main()
{
	stack<char> st;
	int pipe = 0; // ���� �������� �� (�߸��� ���)
	int piece = 0; // ���� ������ ������ ����
	char before; // ���� ��ȣ ��� ����
	
	string s;
	cin >> s;
	for (int i = 0; i < s.size(); i++)
	{
		st.push(s[i]);
	}

	for (int j = 0; j < s.size(); j++)
	{
		if (st.top() == ')')
		{
			pipe++;
			before = st.top();
			st.pop();
		}
		else
		{
			if (before == ')') {
				pipe--;
				for (int k = 0; k < pipe; k++)
				{
					piece++;
				}
			}
			else {
				piece++;
				pipe--;
			}
			before = st.top();
			st.pop();
		}
	}
	cout << piece;
	return 0;
}