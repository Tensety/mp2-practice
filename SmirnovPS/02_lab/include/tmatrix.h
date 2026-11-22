// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0 || sz > MAX_VECTOR_SIZE)
            throw std::out_of_range("Vector size is out of range");
        pMem = new T[sz]();
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (sz == 0 || sz > MAX_VECTOR_SIZE)
            throw std::out_of_range("Vector size is out of range");
        if (arr == nullptr)
            throw std::invalid_argument("Expected pointer; got nullptr");

        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v) : sz(v.sz)
    {
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
    {
        v.pMem = nullptr;
        v.sz = 0;
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return *this;

        if (sz != v.sz) {
            T* tmp = new T[v.sz];
            std::copy(v.pMem, v.pMem + v.sz, tmp);
            delete[] pMem;
            pMem = tmp;
            sz = v.sz;
        }
        else
            std::copy(v.pMem, v.pMem + sz, pMem);

        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this == &v)
            return *this;
        delete[] pMem;
        pMem = v.pMem;
        sz = v.sz;
        v.pMem = nullptr;
        v.sz = 0;
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if (ind >= sz)
            throw std::exception("Index out of range");
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind >= sz)
            throw std::exception("Index out of range");
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz)
            throw std::exception("Index out of range");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw std::exception("Index out of range");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
            return false;

        for (int i = 0; i < sz; i++)
            if (pMem[i] != v.pMem[i])
                return false;

        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val) const
    {
        TDynamicVector res(*this);
        for (int i = 0; i < sz; i++)
            res.pMem[i] += val;
        return res;
    }
    TDynamicVector operator-(T val) const
    {
        return *this + val * (-1);
    }
    TDynamicVector operator*(T val) const
    {
        TDynamicVector res(*this);
        for (int i = 0; i < sz; i++)
            res.pMem[i] *= val;
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v) const
    {
        if (sz != v.sz)
            throw std::invalid_argument("Vectors are different sizes");
        TDynamicVector res(sz);
        for (int i = 0; i < sz; i++)
            res[i] = pMem[i] + v.pMem[i];
        return res;
    }
    TDynamicVector operator-(const TDynamicVector& v) const
    {
        return *this + v * (-1);
    }
    T operator*(const TDynamicVector& v) const
    {
        if (sz != v.sz)
            throw std::invalid_argument("Vectors are different sizes");
        T res = T();
        for (int i = 0; i < sz; i++)
            res += pMem[i] * v.pMem[i];
        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend std::istream& operator>>(std::istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }
    friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v)
    {
        ostr << "{";
        bool first = true;
        for (int i = 0; i < v.sz; i++)
            if (!first)
                ostr << ", " << v.pMem[i];
            else {
                ostr << v.pMem[i];
                first = false;
            }
        ostr << "}";
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz == 0 || sz > MAX_MATRIX_SIZE)
            throw std::out_of_range("Matrix size is out of range");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz - i);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::size;
    using TDynamicVector<TDynamicVector<T>>::at;

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz)
            return false;

        for (size_t i = 0; i < sz; i++)
            if (pMem[i] != m[i])
                return false;

        return true;
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return !(*this == m);
    }

    // матрично-скалярные операции
    TDynamicMatrix operator+(const T& val) const
    {
        TDynamicMatrix<T> res(*this);
        for (size_t i = 0; i < sz; i++)
            res[i] = res[i] + val;
        return res;
    }
    TDynamicMatrix operator-(const T& val) const
    {
        return *this + val * (-1);
    }
    TDynamicMatrix operator*(const T& val) const
    {
        TDynamicMatrix res(*this);
        for (size_t i = 0; i < sz; i++)
            res[i] = res[i] * val;
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
    {
        if (sz != v.size())
            throw std::invalid_argument("Vectors have different sizes");
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++)
            for (size_t j = 0; j < pMem[i].size(); j++)
                res[i] += pMem[i][j] * v[j + i];
        return res;
    }


    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m) const
    {
        if (sz != m.sz)
            throw std::invalid_argument("Matrixes are different sizes");
        TDynamicMatrix res(*this);
        for (size_t i = 0; i < sz; i++)
            res[i] = res[i] + m[i];
        return res;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m) const
    {
        if (sz != m.sz)
            throw std::invalid_argument("Matrixes are different sizes");
        return *this + m * (-1);
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m) const
    {
        if (sz != m.sz)
            throw std::invalid_argument("Matrixes are different sizes");
        TDynamicMatrix res(sz);

        for (size_t i = 0; i < sz; i++)
            for (size_t j = 0; j < pMem[i].size(); j++)
                for (size_t k = 0; k <= j; k++)
                    res[i][j] += pMem[i][k] * m.pMem[i + k][j - k];

        return res;
    }

    // ввод/вывод
    friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v[i];
        return istr;
    }
    friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            for (size_t j = 0; j < i; j++)
                ostr << "   ";
            ostr << v[i] << std::endl;
        }
        return ostr;
    }
};

#endif