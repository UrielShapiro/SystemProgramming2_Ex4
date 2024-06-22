#include <string>

using std::string;

class Complex
{
private:
    // Assuming a complex number is of the form: a+bi
    float a;
    float b;

public:
    Complex(float real, float imaginary);
    string get_data();

    float getReal() const;
    float getImaginary() const;

    bool operator==(const Complex &other) const;
    bool operator!=(const Complex &other) const;
};