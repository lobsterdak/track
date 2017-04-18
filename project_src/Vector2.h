#pragma once
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>


class Vector_2
{
public:
    double x, y;
    Vector_2()
    {}
    Vector_2(double a, double b);
    Vector_2(int a, int b);
    ~Vector_2() {}
    Vector_2& operator+=(const Vector_2& other);
    Vector_2& operator-=(const Vector_2& other);
    Vector_2 operator-() const;
    double operator*(const Vector_2 other) const;
    double operator^(const Vector_2 other) const;
    double len() const;
    Vector_2 unit_vector() const;
    Vector_2 normal() const;
    Vector_2 rotate(double degree);
    Vector_2 getRotate(double degree) const;
};

std::istream&  operator >> (std::istream& stream, Vector_2& v);
std::ostream&  operator<<(std::ostream& stream, const Vector_2& v);
Vector_2 operator*(double c, const Vector_2& v);
Vector_2 operator*(const Vector_2& v, double c);
Vector_2 operator+(const Vector_2& first, const Vector_2& second);
Vector_2 operator-(const Vector_2& first, const Vector_2& second);
Vector_2 operator/(const Vector_2& v, double c);
