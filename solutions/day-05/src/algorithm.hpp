#pragma once
#include "structs.hpp"

template <size_t LineCount>
using LinesT = std::array<Line, LineCount>;

inline constexpr bool IsHorizontal(Line line) {
    return line.A.X == line.B.X || line.A.Y == line.B.Y;
}

template <size_t LineCount, LinesT<LineCount> Lines>
inline constexpr auto GetGridDiagonal() {
    Point tl, br;
    for (size_t i = 0; i < LineCount; i++) {
        Line line = Lines[i];
        if (line.A.X < tl.X) tl.X = line.A.X;
        if (line.A.Y < tl.Y) tl.Y = line.A.Y;
        if (line.A.X > br.X) br.X = line.A.X;
        if (line.A.Y > br.Y) br.Y = line.A.Y;
        if (line.B.X < tl.X) tl.X = line.B.X;
        if (line.B.Y < tl.Y) tl.Y = line.B.Y;
        if (line.B.X > br.X) br.X = line.B.X;
        if (line.B.Y > br.Y) br.Y = line.B.Y;
    }
    return Line(tl, br);
}

template <size_t LineCount, LinesT<LineCount> Lines>
struct Grid {
    static constexpr Int
        Width   = 1
                + GetGridDiagonal<LineCount, Lines>().B.X
                - GetGridDiagonal<LineCount, Lines>().A.X,
        Height  = 1
                + GetGridDiagonal<LineCount, Lines>().B.Y
                - GetGridDiagonal<LineCount, Lines>().A.Y,
        XOffset = GetGridDiagonal<LineCount, Lines>().A.X,
        YOffset = GetGridDiagonal<LineCount, Lines>().A.Y;
};

template <size_t LineCount, LinesT<LineCount> Lines>
inline constexpr Int GetResult(bool count_diagonals) {
    Int overlaps = 0;
    using G = Grid<LineCount, Lines>;

    Int grid[G::Height][G::Width];
    for (size_t y = 0; y < G::Height; y++)
        for (size_t x = 0; x < G::Width; x++)
            grid[y][x] = 0;

    for (size_t i = 0; i < LineCount; i++) {
        Line line = Lines[i];
        if (!count_diagonals && !IsHorizontal(line))
            continue;
        Point A = line.A, B = line.B;

        Int x_dir = A.X == B.X ? 0 : A.X < B.X ? 1 : -1;
        Int y_dir = A.Y == B.Y ? 0 : A.Y < B.Y ? 1 : -1;
        Int x, y;
        for (Point p = A; p != B; p.X += x_dir, p.Y += y_dir) {
            x = p.X + G::XOffset, y = p.Y + G::YOffset;
            grid[y][x]++;
            if (grid[y][x] == 2)
                overlaps++;
        }
        x = B.X + G::XOffset, y = B.Y + G::YOffset;
        grid[y][x]++;
        if (grid[y][x] == 2)
            overlaps++;    
    }

    return overlaps;
}
