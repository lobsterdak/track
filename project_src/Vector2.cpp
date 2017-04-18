#include "Vector2.h"
#include <math.h>

Vector_2::Vector_2(double a, double b) :
    x(a), y(b)
{}

Vector_2::Vector_2(int a, int b) :
    x(a), y(b)
{}

std::ostream& operator << (std::ostream& stream, const Vector_2& v)
{
    stream << v.x << " " << v.y;
    return stream;
}

std::istream& operator >> (std::istream & stream, Vector_2 & v)
{
    stream >> v.x >> v.y;
    return stream;
}

Vector_2 operator*(double c, const Vector_2& v)
{
    return v * c;
}

Vector_2 operator*(const Vector_2& v, double c)
{
    return Vector_2(c * v.x, c * v.y);
}

Vector_2 operator+(const Vector_2& first, const Vector_2& second)
{
    return Vector_2(first.x + second.x, first.y + second.y);
}

Vector_2 operator-(const Vector_2& first, const Vector_2& second)
{
    return Vector_2(first.x - second.x, first.y - second.y);
}

double Vector_2::len() const
{
    return (sqrt(x * x + y * y));
}

Vector_2 Vector_2::unit_vector() const
{
    return Vector_2(x, y) / len();
}

Vector_2 Vector_2::normal() const
{
    return Vector_2(-y, x);
}

Vector_2 Vector_2::operator-() const
{
    return Vector_2(-x, -y);
}

Vector_2& Vector_2::operator+=(const Vector_2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector_2& Vector_2::operator-=(const Vector_2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

double Vector_2::operator*(const Vector_2 other) const
{
    return (x * other.x + y * other.y);
}

double Vector_2::operator^(const Vector_2 other) const
{
    return (x * other.y - y * other.x);
}

Vector_2 operator/(const Vector_2& v, double c)
{
    return Vector_2(v.x / c, v.y / c);
}

Vector_2 Vector_2::getRotate(double degree) const
{
    return Vector_2(x, y).rotate(degree);
}

Vector_2 Vector_2::rotate(double degree)
{
    double rad = degree / 180 * M_PI;
    double xtmp = x;
    x = x * cos(rad) - y * sin(rad);
    y = xtmp * sin(rad) + y * cos(rad);
    return *this;
}
