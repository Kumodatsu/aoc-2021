# Day 6 - Lanternfish with C#
You can find the description of the problem [here][1].

## About the solution
Unfortunately I didn't have much time today, so the solution is a rather boring
one. Nonetheless, if you want to get a result before the end of time, the trick
is to not model each fish as a single number that represents its internal timer
as the problem suggests, but rather the other way around: model each _timer_ as
the number of fish that currently have their timer at that value. Since only a
few timer values exist, one only has to store a few numbers and do some simple
addition and assignment. Another point to note is that the result for Part 2
overflows 32 bits, so `Int64` (or `long`) is needed here.

## How to run
To run the solution, you need to have the .NET 6 SDK installed. Use the
following command to run, where `<DAYS>` is the number of days to simulate (`80`
for Part 1, `256` for Part 2):

    cat input/input.txt | dotnet run <DAYS>

The solution is written to the standard output.

[1]: <https://adventofcode.com/2021/day/6>
