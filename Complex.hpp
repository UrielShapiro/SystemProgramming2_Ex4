/**
 * Name: Uriel Shapiro
 * ID: 9745
 */
#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <string>
#include <cassert>
#include <cmath>
#include <iomanip>              // For std::fixed, std::setprecision


using std::string;

template <typename T>
string formatValue(T value)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(1) << value;
    return out.str();
}

/*
    @brief: These functions will be used to check if a parameter given to the Complex class is a numeric type
*/
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
    // Assuming a complex number is of the form: a + bi
    T a;
    T b;

public:

    /*
        @brief: Constructor for the Complex class, will fail at compile time if T is not a numeric type
    */
    Complex(T real, T imaginary) : a(real), b(imaginary)
    {
        static_assert(is_numeric<T>, "Complex parameters must be of numeric type"); // Will fail at compile time if T is not a numeric type
    }

    string get_data() const
    {
        return formatValue(this->a) + " + " + formatValue(this->b) + "i";
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

    // Check which is more distant from the origin (0,0)
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
#endif
