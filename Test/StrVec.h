#pragma once
#include<string>
#include<memory>
using namespace std;

class StrVec
{
public:
	StrVec() :elements(nullptr), first_free(nullptr), cap(nullptr) {};
	StrVec(const StrVec&);
	StrVec(StrVec&& s) noexcept;
	StrVec& operator=(const StrVec&);
	StrVec& operator=(StrVec&& rhs) noexcept;
	StrVec& operator=(std::initializer_list<string>);
	std::string& operator[](std::size_t n) { return elements[n]; }
	const std::string& operator[](std::size_t n) const { return elements[n]; }
	~StrVec();
	void push_back(const std::string&s);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	std::string* begin() const { return elements; }
	std::string* end() const { return first_free; }
	static std::allocator<std::string> alloc;  //分配元素
	void chk_n_alloc() {
		if (size() == capacity()) {
			reallocate();
		}
	}
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void free();                    // 销毁元素并释放内存
	void reallocate();              // 获得更多内存并拷贝已有元素
	std::string *elements;          // 指向数组首元素的指针
	std::string *first_free;        // 指向数组第一个空闲元素的指针
	std::string *cap;               // 指向数组尾后位置的指针
};



