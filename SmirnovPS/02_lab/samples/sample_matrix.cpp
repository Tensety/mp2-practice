// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
#include <locale>
#include <stdexcept>

using namespace std;

int main()
{
    try
    {
        cout << "=== TESTING DYNAMIC VECTOR ===" << endl;

        TDynamicVector<int> v1(3);
        TDynamicVector<int> v2(3);

        for (size_t i = 0; i < 3; i++) {
            v1[i] = (i + 1);
            v2[i] = (i + 1) * 10;
        }

        cout << "Vector v1: " << v1 << endl;
        cout << "Vector v2: " << v2 << endl;
        cout << "v1 + v2: " << (v1 + v2) << endl;
        cout << "v1 * 5: " << (v1 * 5) << endl;

        int product = v1 * v2;
        cout << "v1 * v2 (product): " << product << endl;

        cout << "\n=== TESTING TRIANGULAR MATRIX ===" << endl;

        TDynamicMatrix<int> tr1(3);
        TDynamicMatrix<int> tr2(3);

        int counter = 1;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = i; j < 3; j++) {
                tr1[i][j - i] = counter++;
                tr2[i][j - i] = 1;
            }
        };

        // cout << tr1[2][2] << endl;

        cout << "Matrix tr1:" << endl << tr1 << endl;
        cout << "Matrix tr2:" << endl << tr2 << endl;

        TDynamicMatrix<int> tr3 = tr1 + tr2;
        cout << "Matrix tr3 = tr1 + tr2:" << endl << tr3 << endl;

        TDynamicMatrix<int> tr4 = tr1 * 10;
        cout << "Matrix tr4 = tr1 * 10:" << endl << tr4 << endl;

        TDynamicMatrix<int> tr_mult = tr1 * tr1;
        cout << "Matrix tr1 * tr1 (Matrix multiplication):" << endl << tr_mult << endl;

    }
    catch (const std::exception& e)
    {
        cerr << "Error occurred: " << e.what() << endl;
    }

    return 0;
}
//---------------------------------------------------------------------------

