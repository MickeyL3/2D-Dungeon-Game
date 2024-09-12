#pragma once
#ifndef TVECTOR2D_H
#define TVECTOR2D_H
#include <cmath>
#include "olcPixelGameEngine.h"

template<typename T>
class TVector2D 
{
public:
    T X, Y;

    TVector2D(T x = 0, T y = 0) : X(x), Y(y) {}

    TVector2D<T> operator+(const TVector2D<T>& other) const 
    {
        return TVector2D<T>(X + other.X, Y + other.Y);
    }

    TVector2D<T>& operator+=(const TVector2D<T>& other) 
    {
        X += other.X;
        Y += other.Y;
        return *this;
    }

    TVector2D<T> operator*(T scalar) const 
    {
        return TVector2D<T>(X * scalar, Y * scalar);
    }


    TVector2D<T>& operator*=(T scalar) 
    {
        X *= scalar;
        Y *= scalar;
        return *this;
    }

    bool operator==(const TVector2D<T>& other) const 
    {
        return X == other.X && Y == other.Y;
    }

    TVector2D<T> operator-(const TVector2D<T>& other) const 
    {
        return TVector2D<T>(X - other.X, Y - other.Y);
    }

    TVector2D<float> Normalize() const 
    {
        float length = Length();
        if (length > 0) 
        {
            return TVector2D<float>(X / length, Y / length);
        }
        return TVector2D<float>(0, 0);
    }

    float Length() const 
    {
        return std::sqrt(X * X + Y * Y);
    }

    TVector2D<T> operator/(T scalar) const 
    {
        return TVector2D<T>(X / scalar, Y / scalar);

    }

    static olc::vi2d ToOlcVi2d(const TVector2D<int>& vec) 
    {
        return olc::vi2d(vec.X, vec.Y);
    }
};
#endif