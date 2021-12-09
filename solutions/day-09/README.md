# Day 9 - Smoke Basin with Java
You can find the description of the problem [here][1].

## About the solution
I've solved today's problem using Java. In the supremely object-oriented spirit
of Java, I've done my best to squish as many design patterns as possible into
the code to ensure the flexibility and extensibility of this program that will
likely never change at all. However, to balance this out, I've used exceptions
to determine the control flow of the program where convenient.

## How to run
To run the solution, you need to have a Java JDK and runtime installed. Run the
following commands to build the program:

    mkdir out
    cd src
    javac -classpath . com/github/kumodatsu/*.java
    jar -cmvf META-INF/MANIFEST.mf ../out/Main.jar com/github/kumodatsu/*.class
    cd ..

Run this command to run the program, where `<PART>` is either `1` or `2` for
Part 1 and Part 2 respectively:

    cat input/input.txt | java -jar out/Main.jar <PART>

The solution is written to the standard output.

[1]: <https://adventofcode.com/2021/day/9>
