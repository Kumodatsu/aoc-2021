# Day 5 - Hydrothermal Venture with C++
You can find the description of the problem [here][1].

## About the solution
Everyone knows that even in modern times, it is crucially essential to squeeze
every tiny bit of performance we can out of our programs. But when optimizing
one's code, it is always a good idea to start with algorithmic optimizations
before moving on to micro optimizations. In other words, how can one improve the
worst-case complexity of the algorithm?

When I first saw the problem description, it looked to me like the most
straightforward solution would run in O(N) time complexity, where N is the
number of lines in the input. However, then it occured to me that since the
input is known it advance, it can be made to run in O(1) if we just do all the
calculations at compile-time and store the result, so that the program only has
to print that value when it is run. Of course, C++'s obsession with `constexpr`
and templates is just what we need.

## How to run
To build the program, you need to have g++ installed. Use the following command
to build, where `<PART>` is either `AOC_PART1` or `AOC_PART2` for Part 1 and
Part 2 respectively:

    g++ -std=c++20 -o out/Main -D <PART> src/main.cpp

Then run with the following command:

    out/Main

The solution is written to the standard output.

Since obviously the program is already incredibly fast (after all, it only
prints a number) one could afford optimizing the binary for size. Here are some
commands if you wish to try it out:

    g++ -std=c++20 -Os -fno-exceptions -ffunction-sections -fdata-sections -o out/Main -D <PART> src/main.cpp
    strip -s -R .comment -R .gnu.version --strip-unneeded out/Main

Again `<PART>` is either `AOC_PART1` or `AOC_PART2`. If you are on windows, you
may have to change the `out/Main` in the second command to `out/Main.exe`.

[1]: <https://adventofcode.com/2021/day/5>
