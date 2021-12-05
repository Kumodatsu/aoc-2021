#pragma once
#include <string_view>
#include "structs.hpp"

static constexpr Int ParseInt(std::string_view str, Int radix = 10) {
    Int n = 0;
    Int r = 1;
    for (Int i = str.size(); i > 0; i--) {
        char c = str.at(i - 1);
        n += (c - '0') * r;
        r *= radix;
    }
    return n;
}

static constexpr Line ParseLine(std::string_view line) {
    size_t
        ax_beg = 0,
        ax_end = line.find(','),
        ay_beg = ax_end + 1,
        ay_end = line.find(" -> "),
        bx_beg = ay_end + 4,
        bx_end = line.find(',', bx_beg),
        by_beg = bx_end + 1,
        by_end = line.size();
    Int
        ax = ParseInt(line.substr(ax_beg, ax_end - ax_beg)),
        ay = ParseInt(line.substr(ay_beg, ay_end - ay_beg)),
        bx = ParseInt(line.substr(bx_beg, bx_end - bx_beg)),
        by = ParseInt(line.substr(by_beg, by_end - by_beg));
    return Line(Point(ax, ay), Point(bx, by));
}

static constexpr size_t GetLineCount(std::string_view str) {
    size_t n = 0;
    for (size_t i = 0; i < str.size(); i++)
        if (str.at(i) == '\n')
            n++;
    return n;
}

template <size_t LineCount>
static constexpr std::array<Line, LineCount> GetLines(std::string_view str) {
    std::array<Line, LineCount> lines;
    size_t offset = 0;
    for (size_t i = 0; i < LineCount; i++) {
        size_t end = str.find('\n', offset);
        std::string_view substr = str.substr(offset, end - offset);
        Line line = ParseLine(substr);
        lines[i] = line;
        offset = end + 1;
    }
    return lines;
}
