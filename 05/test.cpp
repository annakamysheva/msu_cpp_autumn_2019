#include <iostream>
#include "bigint.h"

using namespace std;

int main()
{
    BigInt a = -9;
    cout << "Here's your bigInt - "<< a << ". And test 1 successfully passed" << endl;

    BigInt b = 2;
    cout << "Here's your bigInt - "<< b << ". And test 2 successfully passed" << endl;
    BigInt c = a + b;

    cout << "Here's your bigInt - "<< c << ". And i can summarize!" << endl;

    if(a < c)
		cout << "I can compare" << endl;
	  if(c <= b)
		cout << "And it works both ways" << endl;

    if(c == (b + a))
		cout << "Test 6 successfully passed" << endl;

    return 0;
}