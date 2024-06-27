#pragma once
#include <string>
#include <cassert>
#include <cmath>

using std::string, std::to_string;

template <typename T>
constexpr bool is_numeric = false;
template <>
constexpr bool is_numeric<int> = true;
template <>
constexpr bool is_numeric<long> = true;
template <>
constexpr bool is_numeric<float> = true;
template <>
constexpr bool is_numeric<double> = true;
template <>
constexpr bool is_numeric<short> = true;

template <typename T>
class Complex
{
private:
    // Assuming a complex number is of the form: a+bi
    T a;
    T b;

public:
    Complex(T real, T imaginary) : a(real), b(imaginary)
    {
        static_assert(is_numeric<T>, "T must be a numeric type"); // Will fail at compile time if T is not a numeric type
    }

    string get_data() const
    {
        return to_string(this->a) + " + " + to_string(this->b) + "i";
    }

    T getReal() const
    {
        return this->a;
    }

    T getImaginary() const
    {
        return this->b;
    }

    bool operator==(const Complex &other) const
    {
        return this->getReal() == other.getReal() && this->getImaginary() == other.getImaginary();
    }
    bool operator!=(const Complex &other) const
    {
        return !(*this == other);
    }
    friend bool operator>(const Complex &me, const Complex &other)
    {
        return sqrt(pow(me.getReal(), 2) + pow(me.getImaginary(), 2)) > sqrt(pow(other.getReal(), 2) + pow(other.getImaginary(), 2));
    }

    friend bool operator<(const Complex &me, const Complex &other)
    {
        return sqrt(pow(me.getReal(), 2) + pow(me.getImaginary(), 2)) < sqrt(pow(other.getReal(), 2) + pow(other.getImaginary(), 2));
    }

    friend std::ostream &operator<<(std::ostream &os, const Complex<T> &complex)
    {
        os << complex.get_data();
        return os;
    }
};