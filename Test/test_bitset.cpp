#include<iostream>
#include<stdlib.h>
#include<string>
#include<tuple>
#include<vector>
#include<list>
#include<bitset>


using namespace std;

int main() {

	bitset<32> bitvec(1U);                // 32λ�� ��λΪ1�� ʣ��λλ0
	bool is_set = bitvec.any();           // true, ��Ϊ��1λ��λ
	bool is_ant_set = bitvec.none();
	bool all_set = bitvec.all();
	size_t onBits = bitvec.count();
	size_t sz = bitvec.size();
	bitvec.flip();                       // ��תbitvec�е�����λ
	bitvec.reset();
	bitvec.set();
	cout << bitvec << endl;
	

	system("pause");
	return 0;
}