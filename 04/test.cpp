#include "serializer.h"

using namespace std;

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(a, b, c);
    }

    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};


int main(){

    Data x { 1, true, 2 };
	
	stringstream stream;
	
	Serializer serializer(stream);
	serializer.save(x);
		
	Data y { 0, false, 0 };
	
	Deserializer deserializer(stream);

    const Error err = deserializer.load(y);
    assert(err == Error::NoError);
    cout << "Test 1 successfully passed" << endl;  

    assert(x.a == y.a);
    cout << "Test 2 successfully passed" << endl; 

    assert(x.b == y.b);
    cout << "Test 3 successfully passed" << endl; 

    assert(x.c == y.c);
    cout << "Test 4 successfully passed" << endl; 

    return 0;
}