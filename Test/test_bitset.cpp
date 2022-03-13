#include<iostream>
#include<stdlib.h>
#include<string>
#include<tuple>
#include<vector>
#include<list>
#include<bitset>


using namespace std;

int main() {

	bitset<32> bitvec(1U);                // 32位； 低位为1， 剩余位位0
	bool is_set = bitvec.any();           // true, 因为有1位置位
	bool is_ant_set = bitvec.none();
	bool all_set = bitvec.all();
	size_t onBits = bitvec.count();
	size_t sz = bitvec.size();
	bitvec.flip();                       // 翻转bitvec中的所有位
	bitvec.reset();
	bitvec.set();
	cout << bitvec << endl;
	

	system("pause");
	return 0;
}