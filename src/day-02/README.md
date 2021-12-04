# Day 2 - Dive! with Haskell
You can find the description of the problem [here][1].

## About the solution
Programming in Haskell is like playing with Lego. Except the bricks are
functions and the studs are types.

The input gets shoved into the Lego tower:

```haskell
show . mul . foldl move start . map tup . map words . lines
```

The `lines` brick takes the input (with `String`-shaped studs) and splits into
lines (`[String]`). This fits onto the next brick `map words`, which has
`[String]`-shaped studs and splits each line into words. In the case of this
problem, there are always two words per line: a direction and a number. The
`map tup`-brick converts these to a tuple, fitting onto `[(String, Int)]`-shaped
studs such as those on top of the next brick `foldl move start`. The output is
the final position (with `(Int, Int, Int)` studs) which is clicked onto `mul`
and finally `show`, which multiply the horizontal position and depth and turns
the result into a `String`.

Yes, I know the Lego analogy is rather disappointing, but hey - maybe comparing
functional programming to colorful toys will make it look more appealing.

## How to run
To run the solution, you need to have GHC installed. Run the following commands
to build the executable:

    mkdir out
    ghc -odir out -hidir out -o out/Main Main.hs

Run this command to run the solution, where `<PART>` is either `1` or `2` for
Part 1 and Part 2 respectively:

    cat input.txt | out/Main <PART>

The solution is written to the standard output.

[1]: <https://adventofcode.com/2021/day/2>
