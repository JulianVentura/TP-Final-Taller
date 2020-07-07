#pragma once
#ifndef __BOX_H__
#define __BOX_H__

#include "Vector2.h"
#include <nlohmann/json.hpp>
// Por conveniencia
using json = nlohmann::json;


namespace quadtree
{
template<typename T>
class Box
{
private:
    T left;
    T top;
    T width; // Must be positive
    T height; // Must be positive
public:
    constexpr Box(T Left = 0, T Top = 0, T Width = 0, T Height = 0) noexcept :
        left(Left), top(Top), width(Width), height(Height)
    {

    }

    constexpr Box(const Vector2<T>& position, const Vector2<T>& size) noexcept :
        left(position.x), top(position.y), width(size.x), height(size.y)
    {

    }

    constexpr T getRight() const noexcept
    {
        return left + width;
    }

    constexpr T getBottom() const noexcept
    {
        return top + height;
    }

    constexpr Vector2<T> getTopLeft() const noexcept
    {
        return Vector2<T>(left, top);
    }

    constexpr Vector2<T> getCenter() const noexcept
    {
        return Vector2<T>(left + width / 2, top + height / 2);
    }

    constexpr Vector2<T> getSize() const noexcept
    {
        return Vector2<T>(width, height);
    }

    constexpr bool contains(const Box<T>& box) const noexcept
    {
        return left <= box.left && box.getRight() <= getRight() &&
            top <= box.top && box.getBottom() <= getBottom();
    }

    constexpr bool intersects(const Box<T>& box) const noexcept
    {
        return !(left >= box.getRight() || getRight() <= box.left ||
            top >= box.getBottom() || getBottom() <= box.top);
    }
    
    Box<T>(const Box<T> &&otro) : 
    Box(otro.left, otro.top, otro.width, otro.height){}

    Box<T>(const Box<T> &otro) : 
    Box(otro.left, otro.top, otro.width, otro.height){}
    
    constexpr T obtenerX() const noexcept { return left; } 
    constexpr T obtenerY() const noexcept { return top; }
    constexpr T obtenerAncho() const noexcept { return width; }
    constexpr T obtenerAlto() const noexcept { return height; }

    constexpr void set(T x, T y, T width, T height){
        this->left = x;
        this->top = y;
        this->width = width;
        this->height = height;
    }

    Box<T>& operator=(Box<T> &otro){
        top     = otro.top;
        left    = otro.left;
        width   = otro.width;
        height  = otro.height;
        return *this;
    }

    Box<T>& operator=(Box<T> &&otro){
        top     = otro.top;
        left    = otro.left;
        width   = otro.width;
        height  = otro.height;
        return *this;
    }
};
}

#endif