#pragma once
#include <cmath>

namespace quadtree
{

template<typename T>
class Vector2
{
public:
    T x;
    T y;

    constexpr Vector2<T>(T X = 0, T Y = 0) noexcept : x(X), y(Y)
    {

    }

    constexpr Vector2<T>& operator+=(const Vector2<T>& other) noexcept
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr Vector2<T>& operator-=(const Vector2<T>& other) noexcept
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    constexpr Vector2<T>& operator/=(T t) noexcept
    {
        x /= t;
        y /= t;
        return *this;
    }

    constexpr Vector2<T>& operator*=(T t) noexcept
    {
        x *= t;
        y *= t;
        return *this;
    }

    constexpr T obtenerX() const noexcept
    {
        return x;
    }

    constexpr T obtenerY() const noexcept
    {
        return y;
    }

    constexpr T modulo() noexcept
    {
        return sqrt(x * x + y * y);
    }

    constexpr void normalizar() noexcept
    {
        T modulo = sqrt(x * x + y * y);
        if (modulo == 0) return;
        this->x /= modulo;
        this->y /= modulo;
    }

    constexpr T calcularDistancia(const Vector2<T>& otro) const noexcept
    {   
        return (*this - otro).modulo();
    }
};

template<typename T>
constexpr Vector2<T> operator+(Vector2<T> lhs, const Vector2<T>& rhs) noexcept
{
    lhs += rhs;
    return lhs;
}

template<typename T>
constexpr Vector2<T> operator-(Vector2<T> lhs, const Vector2<T>& rhs) noexcept
{
    lhs -= rhs;
    return lhs;
}

template<typename T>
constexpr Vector2<T> operator/(Vector2<T> vec, T t) noexcept
{
    vec /= t;
    return vec;
}

template<typename T>
constexpr Vector2<T> operator*(Vector2<T> vec, T t) noexcept
{
    vec *= t;
    return vec;
}

}
