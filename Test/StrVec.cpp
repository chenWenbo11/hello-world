#include "StrVec.h"

void StrVec::push_back(const string& s) {
	chk_n_alloc(); //确保有空间容纳新元素
	alloc.construct(first_free++, s);
}

pair<string*, string*>
StrVec::alloc_n_copy(const string* b, const string* e) {
	// 分配空间保存给定范围中的元素
	auto data = alloc.allocate(e - b);
	// 初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
	return { data, uninitialized_copy(b,e,data) };
}

void StrVec::free() {
	// 不能传递给deallocate一个空指针，如果elements为0，函数什么也不做
	if (elements) {
		//逆序销毁旧元素
		for (auto p = first_free; p != elements;) {
			alloc.destroy(--p);
		}
		alloc.deallocate(elements, cap - elements);
	}
}

StrVec::StrVec(const StrVec& s) {
	// 调用 alloc_n_copy分配空间以容纳与s中一样的元素
	auto newData = alloc_n_copy(s.begin(), s.end());
	elements = newData.first;
	first_free = cap = newData.second;
}

StrVec& StrVec::operator=(std::initializer_list<string> il) {
	// alloc_n_copy分配内存空间并从给定范围内拷贝元素
	auto data = alloc_n_copy(il.begin(), il.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

StrVec::StrVec(StrVec&& s) noexcept :elements(s.elements), first_free(s.first_free), cap(s.cap){ // 移动操作不应抛出任何异常
	// 成员初始化器接管s中的资源
	// 令s进入这样的状态——对其运行析构函数是安全的
	s.elements = s.first_free = s.cap = nullptr;
}


StrVec::~StrVec() {
	free();
}

StrVec& StrVec::operator=(const StrVec& rhs) {
	// 调用alloc_n_copy分配内存，大小与rhs中元素占用空间一样多
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

StrVec & StrVec::operator=(StrVec &&rhs) noexcept{
	// 直接检测自赋值
	if (this != &rhs) {
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

void StrVec::reallocate() {
	// 我们将分配当前大小两倍的内存空间
	auto newCapacity = size() ? 2 * size() : 1;
	// 分配新内存
	auto newData = alloc.allocate(newCapacity);
	// 将数据从旧数据移动到新数据
	auto dest = newData;      // 指向新数组中下一个空闲位置
	auto elem = elements;     // 指向旧数组中下一个元素
	for (size_t i = 0; i < size() ;i++)
	{
		alloc.construct(dest++, std::move(*elem++));
	}
	free(); // 一旦我们移动完元素就释放就内存空间，更新我们的数据结构，执行新元素
	elements = newData;
	first_free = dest;
	cap = elements + newCapacity;
}
