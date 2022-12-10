#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#pragma once

struct Vector2D
{
    int x = 0;
    int y = 0;
    Vector2D() = default;
    Vector2D(int x, int y);
    void move(char direction);
    bool isTouching(const Vector2D& other) const;
    bool isDiagonalTo(const Vector2D& other) const;
};

#endif