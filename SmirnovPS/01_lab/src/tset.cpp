// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0 || Elem >= MaxPower)
        throw("Incorrect elem");

    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw("Incorrect elem");

    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw("Incorrect elem");

    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

const TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this == &s)
        return *this;

    MaxPower = s.MaxPower;
    BitField = s.BitField;

    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower)
        return 0;

    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int mxPower;

    mxPower = max(MaxPower, s.MaxPower);
    TSet result(mxPower);

    for (int i = 0; i < mxPower; i++)
        if ((i < MaxPower && BitField.GetBit(i)) || (i < s.MaxPower && s.BitField.GetBit(i)))
            result.BitField.SetBit(i);

    return result;  
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet result(*this);
    result.InsElem(Elem);
    return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet result(*this);
    result.DelElem(Elem);
    return result;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    int minPower;

    minPower = min(MaxPower, s.MaxPower);
    TSet result(minPower);

    for (int i = 0; i < minPower; i++)
        if (BitField.GetBit(i) && s.BitField.GetBit(i))
            result.BitField.SetBit(i);

    return result;
}

TSet TSet::operator~(void) // дополнение
{
    TSet result(*this);
    result.BitField = ~BitField;

    return result;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{   
    int n;
    istr >> n;

    for (int i = 0; i < n; i++) {
        int elem;
        istr >> elem;
        s.InsElem(elem);
    }

    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{   
    for (int i = 0; i < s.MaxPower; i++)
        if (s.BitField.GetBit(i))
            ostr << i << " ";

    return ostr;
}
