#include<iostream>
#include<stdlib.h>
#include<string>
#include<tuple>
#include<vector>
#include<list>


using namespace std;

int main_tuple() {

	tuple<size_t, size_t, size_t> threeD;
	tuple<string, vector<double>, int, list<int>> someVal("constants", { 3.14, 2.718 }, 42, { 0, 1, 2, 3, 4, 5 });

	// ��ʾ��꽻�׼�¼��tuple�� ������ ISBN��������ÿ����ļ۸�
	auto item = make_tuple("0-999-78345-X", 3, 20.00);
	auto book = get<0>(item);
	auto cnt = get<1>(item);
	auto price = get<2>(item) / cnt;
	get<2>(item) *= 0.8;

	typedef decltype(item) trans;  // trans��item������
	// ����trans���Ͷ����г�Ա������
	size_t sz = tuple_size<trans>::value;
	// cnt��������item�еĵڶ�����Ա��ͬ
	//tuple_element<1, trans>::type cnt = get<1>(item);

	system("pause");
	return 0;
}