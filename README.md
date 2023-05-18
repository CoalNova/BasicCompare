# BasicCompare
A basic comparitive analysis of C, C++, Rust, and Zig.
---
![pretty command line text](https://github.com/CoalNova/BasicCompare/blob/main/ast/sc.png?raw=true)

The goal of this project was to test operational time performance for each language using as like operations as possible. Though per-lang optimizations could be performed, all of the languages allow for inline assembly, meaning this would get real nasty, real quick. The implementation is meant to be a naive, or at least a beginner's basic approach to the problem.

The operations are:
 - using a struct to contain a billable user account
 - filled with a language provided random number generator
 - over a provided (100 default) number of iterations
 - propagate a resizeable heap-based account collection of provided operation size (100 default)
 - iterate over the list and perform a billing based on account balance (actual values don't matter)
 - perform the iteration loop operation number of times
 - clear list/free memory

Although variations obviously change between languages, those operations are performed in much the same manner across. The languages are compiled using optimizations, with C/C++ using -O2, Rust using --release, and Zig using ReleaseFast. Programs will print to command line the total time of execution. As well as the minimum, maximum, and average iteration times.

The provided Makefile should build on any machine that has Make/Clang, Rust/Cargo, and Zig.

Each program allows for up to two numeric arguments, with the first being operations, and the second being iterations.
