#include<iostream>
#include<stdlib.h>
#include<cstdlib>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<map>

using namespace std;

void error_msg(initializer_list<string> il) {
	for (auto beg = il.begin(); beg != il.end(); ++beg) {
		cout << *beg << " ";
	}
	cout << endl;
}

void elimDups(vector<string>& words) {
	sort(words.begin(), words.end());
	auto endUnique = unique(words.begin(), words.end());
	words.erase(endUnique, words.end());
}

bool check_size(const string& s, string::size_type sz) {
	return s.size() >= sz;
}


void biggeies(vector<string>& words, vector<string>::size_type sz) {
	elimDups(words);
	stable_sort(words.begin(), words.end(),
		[](const string& a, const string& b)->bool
			{return a.size() < b.size(); });
	auto wc = find_if(words.begin(), words.end(), [sz](const string& a) {return a.size() >= sz; });
	auto count = words.end() - wc;
	cout << count << endl;
	//for_each(wc, words.end(), [](const string& s) {cout << s << " "; });
	for_each(wc, words.end(), bind(check_size, std::placeholders::_1, sz));
	cout << endl;
}

// 普通函数
int add(int i, int j) {
	return i + j;
}
// lambda，其产生一个未命名的函数对象类
auto mod = [](int i, int j) {return i % j; };
// 函数对象类
struct divide {
	int operator()(int denominator, int divisor) {
		return denominator / divisor;
	}
};


void testFunction() {
	// 构建从运算符到函数指针的映射关系，其中函数接受两个int、返回一个int
	/*   
	*   	map<string, int(*)(int, int)> binops;
	*       binops.insert({ "+",add });
	*/

	function<int(int, int)> f1 = add;    //函数指针
	function<int(int, int)> f2 = divide();
	function<int(int, int)> f3 = [](int i, int j) { return i * j; };

	cout << f1(4, 2) << endl;
	cout << f2(4, 2) << endl;
	cout << f3(4, 2) << endl;

	map<string, function<int(int, int)>> binops = { 
		{"+",add}, 
		{"-",std::minus<int>()},
		{"/",divide()},
		{"*",[](int i, int j) {return i * j; }},
		{"%",mod}};

}

template <typename T>
int compare(const T& v1, const T& v2) {
	if (v1 < v2) {
		return -1;
	}
	if (v2 < v1) {
		return 1;
	}
	return 0;
}

template<typename T> class Blob {
public:
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;
	// 构造函数
	Blob();
	Blob(std::initializer_list<T> il);
	// Blob中的元素数目
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	// 添加和删除元素
	void push_back(const T& t) { data->push_back(t); }
	// 移动版本
	void push_back(T&& t) { data->push_back(std::move(t)); }
	void pop_back();
	// 元素访问
	T& back();
	T& operator[](size_type i);
private:
	std::shared_ptr<std::vector<T>> data;
	// 若data[i]无效，则抛出msg
	//void check < size_type i, const std::string& msg) const;
};

int main_16() {
	
	string s;
	cin >> s;
	cout << s << endl;
	
	for (auto &c : s) {
		c = toupper(c);
	}

	vector<string> words{ "abc","abc","acdcdde","defsgega","shbals","vector"};

	biggeies(words , 5);

	cout << s << endl;

	system("pause");
	return 0;
}