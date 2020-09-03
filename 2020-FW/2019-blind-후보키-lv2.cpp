#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
vector<string> combination;
int column = 0;

//string ���Լ� ���̷� ���� �������ϰ� ������ ū������� �����Ѵ�
bool compare(string a, string b) {
    if (a.length() != b.length()) {
        return a.length() < b.length();
    }
    return a < b;
}

//��� ������ ����� �Լ�
void makeComb() {
    for (int i = 0; i < column; i++) {
        vector<int> selector;
        for (int j = 0; j < i; j++) {
            selector.push_back(0);
        }
        for (int j = 0; j < column - i; j++) {
            selector.push_back(1);
        }
        do {
            string temp = "";
            for (int j = 0; j < column; j++) {
                if (selector[j] == 1) {
                    temp += to_string(j);
                }
            }
            combination.push_back(temp);
        } while (next_permutation(selector.begin(), selector.end()));
    }
}

//���տ����� �ĺ�Ű ���� ���� Ȯ��
bool subset(vector<vector<string>> relation, string combination) {
    set<string> keySet;
    for (int i = 0; i < relation.size(); i++) {
        string key = "";
        for (int j = 0; j < combination.length(); j++) {
            int colNumber = combination[j] - '0';
            key += relation[i][colNumber];
        }
        keySet.insert(key);
    }
    if (keySet.size() != relation.size()) {
        return false;
    }
    return true;
}

int solution(vector<vector<string>> relation) {
    int answer = 0;
    column = relation[0].size();
    makeComb();
    sort(combination.begin(), combination.end(), compare);
    
    // ���ռ���ŭ �ݺ�
    for (int i = 0; i < combination.size(); i++) {
        if (subset(relation, combination[i])) {
            string temp = combination[i];
            //�ĺ�Ű������ ��ġ�� ���� ����
            for (int j = combination.size() - 1; j >= i; j--) { // j~i�����ΰ� ���α��� �����ϱ� ����
                bool check = true;
                for (auto t : temp) { // Ű�� ���� attribute�� �ϳ��� ������ ������ check false 
                    if (combination[j].find(t) == string::npos) {
                        check = false;
                        break;
                    }
                }
                if (check) { // Ű�� ���� ��� attribute�� �߰ߵ� ��� ���տ��� ����
                    combination.erase(combination.begin() + j);
                }
            }
            i--;
            answer++;
        }
    }
    return answer;
}