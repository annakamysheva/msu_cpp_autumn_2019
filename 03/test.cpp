#include "matrix.h"

using namespace std;
int main() {

	Matrix m1(3,3);
	Matrix m2(3,3);
	Matrix m3(3,3);

	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			m1[i][j] = 1;
			m2[i][j] = 1;
			m3[i][j] = 5;
		}
	}

    //Тест на присвоение 
    cout << m3[1][1]<<" => " << "Test 1 successfully pased" << endl;

    //Тест на равенство 
    assert(m1 == m2);
	cout << "Test 2 successfully pased" << endl;

    //Тест на неравенство
	assert(m2 != m3);
	cout << "Test 3 successfully pased" << endl;

    //Тест на умножение
	m1 *= 5;
	assert(m1 == m3);
	std::cout << "Test 4 successfully pased" << endl;

    //Тест на методы
	assert((m1.getRows() == 3) && (m1.getColumns() == 3));
	std::cout << "Test 5 successfully pased" << endl;

    //Тест на ошибку выхода за рамки матрицы
	m1[10][25] = 15;

	return 0;
}