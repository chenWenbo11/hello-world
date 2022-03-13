#pragma once
#include<string>

class Quote
{
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price):bookNo(book),price(sales_price){}
	std::string isbn() const { return bookNo; }
	// 返回给定数量的书籍的销售总额
	// 派生类负责改写并使用不同的折扣计算方法
	virtual double net_price(std::size_t n) const; 
	virtual ~Quote() = default;
private:
	std::string bookNo;
protected:
	double price = 0.0; 
};

double Quote::net_price(std::size_t n) const {
	return n * price;
}

class Disc_quote :public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string& book, double price, std::size_t qty, double disc): 
		Quote(book, price),
		quantity(qty),discount(disc){}
	double net_price(std::size_t) const = 0;
private:
	std::size_t quantity = 0;   // 折扣适用的购买量
	double discount = 0.0;      // 表示折扣的小数值
};

class Bulk_quote :public Disc_quote {
public :
	Bulk_quote() = default;
	Bulk_quote(const std::string& book, double p, std::size_t qty, double disc):
		Disc_quote(book,p,qty,disc){}
	double net_price(std::size_t) const override;
};

