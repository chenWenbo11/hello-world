#include "StrVec.h"

void StrVec::push_back(const string& s) {
	chk_n_alloc(); //ȷ���пռ�������Ԫ��
	alloc.construct(first_free++, s);
}

pair<string*, string*>
StrVec::alloc_n_copy(const string* b, const string* e) {
	// ����ռ䱣�������Χ�е�Ԫ��
	auto data = alloc.allocate(e - b);
	// ��ʼ��������һ��pair����pair��data��uninitialized_copy�ķ���ֵ����
	return { data, uninitialized_copy(b,e,data) };
}

void StrVec::free() {
	// ���ܴ��ݸ�deallocateһ����ָ�룬���elementsΪ0������ʲôҲ����
	if (elements) {
		//�������پ�Ԫ��
		for (auto p = first_free; p != elements;) {
			alloc.destroy(--p);
		}
		alloc.deallocate(elements, cap - elements);
	}
}

StrVec::StrVec(const StrVec& s) {
	// ���� alloc_n_copy����ռ���������s��һ����Ԫ��
	auto newData = alloc_n_copy(s.begin(), s.end());
	elements = newData.first;
	first_free = cap = newData.second;
}

StrVec& StrVec::operator=(std::initializer_list<string> il) {
	// alloc_n_copy�����ڴ�ռ䲢�Ӹ�����Χ�ڿ���Ԫ��
	auto data = alloc_n_copy(il.begin(), il.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

StrVec::StrVec(StrVec&& s) noexcept :elements(s.elements), first_free(s.first_free), cap(s.cap){ // �ƶ�������Ӧ�׳��κ��쳣
	// ��Ա��ʼ�����ӹ�s�е���Դ
	// ��s����������״̬���������������������ǰ�ȫ��
	s.elements = s.first_free = s.cap = nullptr;
}


StrVec::~StrVec() {
	free();
}

StrVec& StrVec::operator=(const StrVec& rhs) {
	// ����alloc_n_copy�����ڴ棬��С��rhs��Ԫ��ռ�ÿռ�һ����
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

StrVec & StrVec::operator=(StrVec &&rhs) noexcept{
	// ֱ�Ӽ���Ը�ֵ
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
	// ���ǽ����䵱ǰ��С�������ڴ�ռ�
	auto newCapacity = size() ? 2 * size() : 1;
	// �������ڴ�
	auto newData = alloc.allocate(newCapacity);
	// �����ݴӾ������ƶ���������
	auto dest = newData;      // ָ������������һ������λ��
	auto elem = elements;     // ָ�����������һ��Ԫ��
	for (size_t i = 0; i < size() ;i++)
	{
		alloc.construct(dest++, std::move(*elem++));
	}
	free(); // һ�������ƶ���Ԫ�ؾ��ͷž��ڴ�ռ䣬�������ǵ����ݽṹ��ִ����Ԫ��
	elements = newData;
	first_free = dest;
	cap = elements + newCapacity;
}
