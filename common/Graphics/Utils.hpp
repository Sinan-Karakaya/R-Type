/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Utils
*/

#pragma once

#include <cstdint>

namespace RType::Graphics
{
    template <typename T>
    class Vector2
    {
    public:
        Vector2()
        {
            x = 0;
            y = 0;
        };

        Vector2(T x, T y)
        {
            this->x = x;
            this->y = y;
        };

        Vector2(const Vector2 &vector)
        {
            x = vector.x;
            y = vector.y;
        };

    public:
        T x;
        T y;
    };

    template <typename T>
    Vector2<T> &operator==(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    template <typename T>
    Vector2<T> &operator!=(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T>
    Vector2<T> &operator+(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    template <typename T>
    Vector2<T> &operator-(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return Vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    template <typename T>
    Vector2<T> &operator*(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return Vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
    }

    template <typename T>
    Vector2<T> &operator/(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return Vector2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
    }

    template <typename T>
    Vector2<T> &operator+=(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return lhs + rhs;
    }

    template <typename T>
    Vector2<T> &operator-=(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return lhs - rhs;
    }

    template <typename T>
    Vector2<T> &operator*=(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return lhs * rhs;
    }

    template <typename T>
    Vector2<T> &operator/=(const Vector2<T> &lhs, const Vector2<T> &rhs)
    {
        return lhs / rhs;
    }

    template <typename T>
    Vector2<T> &operator-(const Vector2<T> &vector)
    {
        return Vector2<T>(-vector.x, -vector.y);
    }

    template <typename T>
    Vector2<T> &operator*(const Vector2<T> &vector, T scalar)
    {
        return Vector2<T>(vector.x * scalar, vector.y * scalar);
    }

    template <typename T>
    Vector2<T> &operator*(T scalar, const Vector2<T> &vector)
    {
        return vector * scalar;
    }

    template <typename T>
    Vector2<T> &operator/(const Vector2<T> &vector, T scalar)
    {
        return Vector2<T>(vector.x / scalar, vector.y / scalar);
    }

    template <typename T>
    Vector2<T> &operator/=(const Vector2<T> &vector, T scalar)
    {
        return vector / scalar;
    }

    template <typename T>
    Vector2<T> &operator*=(const Vector2<T> &vector, T scalar)
    {
        return vector * scalar;
    }

    typedef Vector2<int> Vector2i;
    typedef Vector2<unsigned int> Vector2u;
    typedef Vector2<float> Vector2f;

    template <typename T>
    class Rect
    {
    public:
        Rect() {};

        Rect(T left, T top, T width, T height)
        {
            this->left = left;
            this->top = top;
            this->width = width;
            this->height = height;
        };

        Rect(const Rect &rect)
        {
            left = rect.left;
            top = rect.top;
            width = rect.width;
            height = rect.height;
        };

        bool contains(T x, T y) const { return x >= left && x < left + width && y >= top && y < top + height; };

        bool contains(const Vector2<T> &point) const { return contains(point.x, point.y); };

        bool intersects(const Rect<T> &rect) const
        {
            if (left < rect.left + rect.width && left + width > rect.left && top < rect.top + rect.height &&
                top + height > rect.top) {
                return true;
            }
            return false;
        };

        Vector2<T> getSize() const { return Vector2<T>(width, height); };

        Vector2<T> getPosition() const { return Vector2<T>(left, top); };

    public:
        T left;
        T top;
        T width;
        T height;
    };

    template <typename T>
    Rect<T> &operator==(const Rect<T> &lhs, const Rect<T> &rhs)
    {
        return lhs.left == rhs.left && lhs.top == rhs.top && lhs.width == rhs.width && lhs.height == rhs.height;
    }

    template <typename T>
    Rect<T> &operator!=(const Rect<T> &lhs, const Rect<T> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T>
    Rect<T> &operator+(const Rect<T> &lhs, const Rect<T> &rhs)
    {
        return Rect<T>(lhs.left + rhs.left, lhs.top + rhs.top, lhs.width + rhs.width, lhs.height + rhs.height);
    }

    template <typename T>
    Rect<T> &operator-(const Rect<T> &lhs, const Rect<T> &rhs)
    {
        return Rect<T>(lhs.left - rhs.left, lhs.top - rhs.top, lhs.width - rhs.width, lhs.height - rhs.height);
    }

    template <typename T>
    Rect<T> &operator*(const Rect<T> &lhs, const Rect<T> &rhs)
    {
        return Rect<T>(lhs.left * rhs.left, lhs.top * rhs.top, lhs.width * rhs.width, lhs.height * rhs.height);
    }

    template <typename T>
    Rect<T> &operator/(const Rect<T> &lhs, const Rect<T> &rhs)
    {
        return Rect<T>(lhs.left / rhs.left, lhs.top / rhs.top, lhs.width / rhs.width, lhs.height / rhs.height);
    }

    template <typename T>
    Rect<T> &operator+=(const Rect<T> &lhs, const Rect<T> &rhs)
    {
        return lhs + rhs;
    }

    template <typename T>
    Rect<T> &operator-=(const Rect<T> &lhs, const Rect<T> &rhs)
    {
        return lhs - rhs;
    }

    template <typename T>
    Rect<T> &operator*=(const Rect<T> &lhs, const Rect<T> &rhs)
    {
        return lhs * rhs;
    }

    template <typename T>
    Rect<T> &operator/=(const Rect<T> &lhs, const Rect<T> &rhs)
    {
        return lhs / rhs;
    }

    template <typename T>
    Rect<T> &operator-(const Rect<T> &rect)
    {
        return Rect<T>(-rect.left, -rect.top, -rect.width, -rect.height);
    }

    template <typename T>
    Rect<T> &operator*(const Rect<T> &rect, T scalar)
    {
        return Rect<T>(rect.left * scalar, rect.top * scalar, rect.width * scalar, rect.height * scalar);
    }

    template <typename T>
    Rect<T> &operator*(T scalar, const Rect<T> &rect)
    {
        return rect * scalar;
    }

    template <typename T>
    Rect<T> &operator/(const Rect<T> &rect, T scalar)
    {
        return Rect<T>(rect.left / scalar, rect.top / scalar, rect.width / scalar, rect.height / scalar);
    }

    template <typename T>
    Rect<T> &operator/=(const Rect<T> &rect, T scalar)
    {
        return rect / scalar;
    }

    template <typename T>
    Rect<T> &operator*=(const Rect<T> &rect, T scalar)
    {
        return rect * scalar;
    }

    typedef Rect<int> IntRect;
    typedef Rect<unsigned int> UintRect;
    typedef Rect<float> FloatRect;

    class Time
    {
    public:
        Time();

        virtual float asSeconds() const { return m_microseconds / 1000000.f; };

        virtual int32_t asMilliseconds() const { return m_microseconds / 1000; };

        virtual int64_t asMicroseconds() const { return m_microseconds; };

    private:
        int64_t m_microseconds;
    };

    class Clock
    {
    public:
        Clock();

        virtual Time getElapsedTime() const;
        virtual Time restart();
    };
} // namespace RType::Graphics
