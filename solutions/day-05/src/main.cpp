#include <iostream>
#include "structs.hpp"
#include "parsing.hpp"
#include "algorithm.hpp"
#include "source.hpp"

static constexpr bool CountDiagonals =
    #if !(defined(AOC_PART1) ^ defined(AOC_PART2))
    false
    #error "AOC_PART1 or AOC_PART2 must be defined, but not both"
    #elif defined(AOC_PART1)
    false
    #else
    true
    #endif
    ;
static constexpr size_t LineCount = GetLineCount(src);
static constexpr auto   VentLines = GetLines<LineCount>(src);
static constexpr Int    Result    = GetResult<LineCount, VentLines>(CountDiagonals);

// This is only here so Result can be passed as a template parameter;
// this means that if the code compiles, we can be certain that Result has been
// computed at compile-time.
template <Int X> Int ID = X;

int main() {
    std::cout << ID<Result> << std::endl;
    return 0;
}
