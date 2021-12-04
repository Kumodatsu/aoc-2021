# Day 4 - Giant Squid with C#
You can find the description of the problem [here][1].

## About the solution
Functional programming is very hip nowadays, yet languages such as Haskell still
frighten many programmers with their functors and monads. A common approach
therefore is to simply apply as many concepts from functional programming as
possible in mainly object oriented languages, but giving them different names
such as fluent interfaces and LINQ. C# is an optimal language for writing
beautiful fluent interfaces and oneliners. With just a few fancy combinators,
here defined in `FancyFluencyFacilitation.cs`, both parts of this day's problem
can be solved in a single line. Granted, it is a very long line and I've split
it up into multiple lines for readability, but I can assure you the entire thing
contains no braces and only a single semicolon at the end. If you ask me, that
still counts as a oneliner.

## How to run
To run the solution, you need to have the .NET 6 SDK installed. Use the
following command to run, where `<PART>` is either `1` or `2` for Part 1 and
Part 2 respectively:

    cat input.txt | dotnet run <PART>

The solution is written to the standard output.

[1]: <https://adventofcode.com/2021/day/4>
