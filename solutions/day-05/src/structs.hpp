#pragma once
#include <iostream>
#include <cstdint>
#include <array>

using Int = uint64_t;

struct Point {
    Int X, Y;
    constexpr Point() : X(0), Y(0) {}
    constexpr Point(Int x, Int y) : X(x), Y(y) {}
    constexpr bool operator == (Point p) { return X == p.X && Y == p.Y; }
    constexpr bool operator != (Point p) { return !(*this == p ); }
};

struct Line {
    Point A, B;
    constexpr Line() = default;
    constexpr Line(Point a, Point b) : A(a), B(b) { }

    constexpr bool ContainsPoint(Point p) {
        Int x_dir = A.X == B.X ? 0 : A.X < B.X ? 1 : -1;
        Int y_dir = A.Y == B.Y ? 0 : A.Y < B.Y ? 1 : -1;
        for (Point q = A; q != B; q.X += x_dir, q.Y += y_dir)
            if (q == p)
                return true;
        return p == B;
    }
};

inline std::ostream& operator << (std::ostream& stream, const Point& p) {
    return stream << "(" << p.X << ", " << p.Y << ")";
}

inline std::ostream& operator << (std::ostream& stream, const Line& line) {
    return stream << "{ " << line.A << " -> " << line.B << " }";
}
