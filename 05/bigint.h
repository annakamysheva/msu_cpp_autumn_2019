#include <iostream>
#pragma once


class BigInt {
	size_t size;
	bool sign;
	uint16_t *data;
	BigInt(const size_t n, const bool s, uint16_t *l): size(n), sign(s), data(l) {}

public:
	BigInt();
	BigInt(const BigInt& val);
	BigInt(const int64_t& val);
	BigInt(BigInt&& val);

	BigInt& operator=(BigInt&& val);
	BigInt& operator=(const BigInt& val);
	BigInt operator-() const;


	BigInt operator+(const BigInt&  val) const;
	BigInt operator-( const BigInt& val) const;
	bool operator==( const BigInt& val) const;
	bool operator!=( const BigInt& val) const;
	bool operator<(const BigInt& val) const;
	bool operator<=(const BigInt& val) const;
	bool operator>(const BigInt& val) const;
	bool operator>=( const BigInt& val) const;
	bool cmp_abs(const BigInt& n1, const BigInt& n2) const;
	friend std::ostream& operator<<( std::ostream&, const BigInt& );
	~BigInt();
};