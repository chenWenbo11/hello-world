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
	static std::allocator<std::string> alloc;  //����Ԫ��
	void chk_n_alloc() {
		if (size() == capacity()) {
			reallocate();
		}
	}
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void free();                    // ����Ԫ�ز��ͷ��ڴ�
	void reallocate();              // ��ø����ڴ沢��������Ԫ��
	std::string *elements;          // ָ��������Ԫ�ص�ָ��
	std::string *first_free;        // ָ�������һ������Ԫ�ص�ָ��
	std::string *cap;               // ָ������β��λ�õ�ָ��
};



