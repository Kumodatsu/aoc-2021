# Day 1 - Dive! with Haskell
You can find the description of the problem [here][1].

## How to run
To run the solution, you need to have GHC installed. Run the following
commands to build the executable:

    mkdir out
    ghc -odir out -hidir out -o out/Main Main.hs

Run this command to run the solution if you're using bash or cmd:

    out/Main < input.txt

If you're using Powershell, use this command to run instead:

    Get-Content input.txt | out/Main

The solution is written to the standard output.

[1]: <https://adventofcode.com/2021/day/2>
