# Day 1 - Sonar Sweep with AWK
You can find the description of the problem [here][1].

## About the solution
[AWK][2] is a programming language specifically intended for text processing and
data extraction. AWK programs are structured in terms of condition-action pairs,
where each line of the input that satisfies the condition triggers the
corresponding action.

AWK's design allows the input to be read very concisely, with no need for any
kind of manual parsing; one can simply execute an action for every number in the
input, and then print the result in the end. The entire solution (in `main.awk`)
comprises only 4 lines. That being said, half of these lines contain several
instructions, but all of them are still no longer than 80 characters (which is
helped by the very non-descriptive single letter variable names, in the spirit
of AWK's compactness).

However, the two parts of the problem can be decomposed into two subproblems,
and since breaking up a solution into smaller solutions is generally favorable
for both comprehension and reusability, let's start with these two subproblems.

`part-1.awk` solves Part 1 of the problem, by simply iterating over each row in
the input while continuously keeping track of the value of the previous row, and
counting how many times the current row's value is greater than the previous
row's value. Since the first row should not be counted as an increase, the
variable `p` (which represents the value of the previous row) is initialized to
infinity, ensuring that it will always be greater than the first row. However,
AWK doesn't allow one to directly use infinity as a value. One could just use a
Very Big Number instead, but that is AWKward and blegh. Fortunately, one can
still use infinity  by using `-log(0)`. Of course, normally in mathematics the
log of 0 is undefined. But this isn't maths, this is computer science; we make
our own rules. In AWK, `log(0)` evaluates to negative infinity, and so `-log(0)`
evaluates to positive infinity. To be fair, the log of `x` does tend to negative
infinity as `x` approaches 0 in conventional maths, but I digress.

`part-2.awk` solves the Part 2 of the problem, using a value `w` which
represents the size of the sliding window. The window starts by covering the
first `w` values, which is implemented by starting at row `w` and then iterating
over the rest of the rows, summing the last `w` values up to that row. Each sum
is then printed to the output, resulting in a list of all the sums of `w`
consecutive rows in the input. The output can then be piped into `part-1.awk` to
once again find the number of increases in this list, solving the problem.

`main.awk` squishes both scripts into one. Part 1 is actually the same as Part
2; the sliding window size just happens to be 1 in that case. This means
`main.awk` can be used for both parts by specifying a window size of either 1 or
3.

## How to run
To run the solution, you need to have GNU Awk installed. Run the following
command for the solution to Part 1:

    gawk -f src/part-1.awk input/input.txt

Run the following command for the solution to Part 2:

    gawk -f src/part-2.awk -v w=3 input/input.txt | gawk -f src/part-1.awk

The solution is written to the standard output.

You can also use the `main.awk` script for both parts of the solution, using
`w=1` for Part 1 and `w=3` for Part 2:

    gawk -f src/main.awk -v w=1 input/input.txt
    gawk -f src/main.awk -v w=3 input/input.txt

[1]: <https://adventofcode.com/2021/day/1>
[2]: <https://en.wikipedia.org/wiki/AWK>
