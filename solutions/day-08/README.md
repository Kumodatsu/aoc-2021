# Day 8 - Seven Segment Search with Haskell
You can find the description of the problem [here][1].

## About the solution
The solution provided here is another simple one with Haskell, but I intend to
make a more interesting solution later, when I have time. The current solution
uses set manipulation to make deductions about which signal patterns must
correspond to which digits.

## How to run
To run the solution, you need to have GHC installed. Run the following commands
to build the executable:

    mkdir out
    ghc -odir out -hidir out -o out/Main src/Main.hs

Run this command to run the solution, where `<PART>` is either `1` or `2` for
Part 1 and Part 2 respectively:

    cat input/input.txt | out/Main <PART>

The solution is written to the standard output.

[1]: <https://adventofcode.com/2021/day/8>
