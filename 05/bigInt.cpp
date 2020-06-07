#include "bigint.h"
#include <iostream>
#include<cmath>

BigInt::BigInt()
{
    size = 1;
    data = new uint16_t[size];
	data[0] = '0';
    sign = true;
}

BigInt::BigInt(const int64_t& val)
{
	sign = (val >= 0) ? true : false;
	uint64_t new_num = (sign) ? val : (-1) * val;
	uint64_t num = new_num;
	size = 0;
	data = nullptr;
	while (num != 0)
	{
		num /= 10;
		size++;
	}
	data = new uint16_t[size];
	for (size_t i = 0; i < size; i++)
	{
		data[size - i - 1] = new_num / pow(10, size - i - 1);
		new_num -= data[size - i - 1] * pow(10, size - i - 1);
	}
	if (size == 0)
	{
		size = 1;
		data = new uint16_t[size];
		data[0] = static_cast<uint16_t>(0);
	}
}

BigInt::BigInt(const BigInt& val): size(val.size), sign(val.sign)
{
	data = new uint16_t[size];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = val.data[i];
	}

	std::copy(val.data, val.data + size, data);
}

BigInt::BigInt(BigInt&& val): data(val.data),size(val.size),sign(val.sign)
{
	val.data = nullptr;
	val.size = 0;
	val.sign = 1;
}

BigInt::~BigInt(){

	delete[] data;
}

std::ostream& operator<<(std::ostream& out, const BigInt& val){
    if (!val.sign) out << '-';
    for (int i = val.size-1; i >=0; i--) {
		out << val.data[val.size - i - 1];;
	}
    return out;
}

BigInt& BigInt::operator=(const BigInt& val)
{
  if (this == &val){return *this;}
  uint16_t* new_data = new uint16_t[val.size];
  for (uint16_t i = 0; i < val.size; i++)
	{
		new_data[i] = val.data[i];
	}
  delete [] data;
  data = new_data;
  size = val.size;
  sign = val.sign;
  std::copy(val.data, val.data + size, data);
  return *this;
}

BigInt& BigInt::operator=(BigInt&& val)
{
	if (this == &val){return *this;}
	delete[] data;
	data = nullptr;
	size = val.size;
	sign = val.sign;
	data = val.data;
	val.data = nullptr;
	val.sign = 0;
	val.size = 0;
	return *this;
}

bool BigInt::operator>(const BigInt& val) const
{
    if (sign!=val.sign)
    {
        if (val.sign){return false;}
        return true;
    }
    for (int i = (size >= val.size ) ? size : val.size; i > 0; i-- )
    {
        if((( i > size) ? 0 : data[i]) < ((i > val.size) ? 0 : val.data[i]))
            return !sign;
    }
    return sign;
}

bool BigInt::operator==(const BigInt& val) const
{
	if (size != val.size || sign != val.sign){return false;}
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] != val.data[i])
		{
			return false;
		}
	}
	return true;
}

bool BigInt::operator!=(const BigInt& val) const
{
	if (*this == val)
	{
		return false;
	}
	return true;
}

bool BigInt::operator<(const BigInt& val) const
{
	return !(*this == val || *this > val);
}


bool BigInt::operator>=(const BigInt& val) const
{
	return !(*this < val);
}

bool BigInt::operator<=(const BigInt& val) const
{
	return !(*this > val);
}


BigInt BigInt::operator-() const
{
    BigInt c=*this;
    if (c.sign)
    {
        c.sign=false;
    }
    else
    {
        c.sign=true;
    }
    return c;
}

bool BigInt::cmp_abs(const BigInt& n1, const BigInt& n2) const
{
	bool ans;
	if (n1.size != n2.size)
	{
		ans = n1.size < n2.size;
	}
	else
	{
		int a = std::memcmp(n1.data, n2.data, n1.size);
		ans = (a < 0);
	}
	return ans;
}


BigInt BigInt::operator+(const BigInt& val) const
{
	size_t new_len = std::max(size, val.size);
	bool new_sign = sign;
	uint16_t* new_num = nullptr;

	if (sign == val.sign)
	{
		if (size < val.size)
		{
			return val + (*this);
		}
		size_t i = size; 
		size_t j = val.size;
		size_t k = new_len;
		uint8_t plus = 0;
		uint8_t sum = 0;
		uint8_t* s = new uint8_t[new_len];
		while (i != 0)
		{
			i--;
			j--;
			k--;
			if (j >= 0)
			{
				sum = data[i] + val.data[j];
			}
			if (plus != 0)
			{
				sum += plus;
				plus = 0;
			}
			if (sum >= 10)
			{
				plus++;
				sum %= 10;
			}
			s[k] = sum;
			sum = 0;
		}
		if (plus != 0)
		{
			new_len++;
			new_num = new uint16_t[new_len];
			new_num[0] = plus;
			std::memcpy(new_num + 1, s, new_len - 1);
		}
		else
		{
			new_num = new uint16_t[new_len];
			std::memcpy(new_num, s, new_len);
		}
		delete[] s;
		return BigInt(new_len, new_sign, new_num);
	}
	else
	{
		
		if(cmp_abs(*this, val))
		{
			return (val + *this);
		}
		else
		{
			// len >= n.len
			size_t i = size;
			size_t j = val.size;
			size_t k = new_len;
			uint8_t minus = 0;
			uint8_t raz = 0;
			uint8_t* r = new uint8_t[new_len];
			while (i != 0)
			{
				i--;
				j--;
				k--;
				if (j >= 0)
				{
					raz = data[i] - val.data[j];
				}
				if (minus != 0)
				{
					raz -= minus;
					minus = 0;
				}
				if (raz < 0)
				{
					minus++;
					raz = std::abs(raz);
				}
				r[k] = raz;
				raz = 0;
			}
			new_num = new uint16_t[new_len];
			std::memcpy(new_num, r, new_len);
			delete[] r;
			return BigInt(new_len, new_sign, new_num);
		}
	}
}

// BigInt BigInt::operator+(const BigInt& val) const {
//         if (sign != val.sign) {
//             if (sign)
//                 return -val;
//             else 
//                 return val-(-(*this));
//         }
        
//         const BigInt* first = this;
//         const BigInt* second = &val;
        
//         if (this -> size < val.size) {
//             first = &val;
//             second = this;
//         }
        
//         BigInt result(*first);
        
//         uint16_t* a = result.data;
//         uint16_t* b = second->data;
//         unsigned c, over = 0;
//         size_t a_left = result.size;
//         size_t b_left = second->size;
        
//         while (a_left and b_left) {
//             c = *a - '0' + *b - '0' + over;
//             over = c / 10;
//             c %= 10;
                
//             *a = c + '0';
                
//             a++;
//             b++;
                
//             a_left--;
//             b_left--;
//         }
            
//         while (a_left) {
//             c = *a - '0' + over;
//             over = c / 10;
//             c %= 10;
                
//             *a = c + '0'; 
//             a++;
//             a_left--;
//         }
            
//         if (over) {
//             result.size++;
            
//             *a = over + '0';
//         }
        
//         return result;
        
//     }

BigInt BigInt::operator-(const BigInt& val) const
{
    return *this+(-val);
}