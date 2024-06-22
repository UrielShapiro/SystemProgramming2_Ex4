#include "Complex.hpp"
using std::to_string;

Complex::Complex(float real, float imaginary) : a(real), b(imaginary) {}

string Complex::get_data()
{
    return to_string(a) + " + " + to_string(b) + "i";
}

float Complex::getReal() const
{
    return this->a;
}
float Complex::getImaginary() const
{
    return this->b;
}

bool Complex::operator==(const Complex &other) const
{
    return this->getReal() == other.getReal() && this->getImaginary() == other.getImaginary();
}

bool Complex::operator!=(const Complex &other) const
{
    return !(*this == other);
}
