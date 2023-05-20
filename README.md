# BasicCompare
![pretty command line text](https://github.com/CoalNova/BasicCompare/blob/main/ast/sc.png?raw=true)
A basic comparitive analysis of C, C++, Rust, Zig, Python, and Java.
---



### Overview

The goal of this project was to test operational time performance for each language using as like operations as possible. Though per-lang optimizations could be performed, the systems-level languages allow for inline assembly. That means this would get real nasty, real quick. The implementation is meant to be a naive, or at least a beginner's basic approach to the problem.

The operations are:
 - using a struct to contain a billable user account
 - propogated by a language provided random number generator
 - over a provided (100 default) number of iterations
 - propagate a resizeable heap-based account collection of provided operation size (100 default)
 - iterate over the list and perform a billing based on account balance (actual values don't matter)
 - perform the iteration loop operation number of times
 - clear list/free memory

Although variations obviously change between languages, those operations are performed in much the same manner across. The languages are compiled using optimizations where available. C/C++ uses -O2, Rust uses --release, and Zig uses ReleaseFast. Programs will print to command line the total time of execution. As well as the maximum, minimum, and average per-iteration times.

---
### Useage


The provided Makefile should build on any machine that has Make/Clang, Rust/Cargo, Zig, and Java. Python .py file to be run via CLI `$ python ./python/main.py`. Each program allows for up to two numeric arguments, with the first assigning operations, and the second iterations.

---
### Timings

Raw output on an admittedly cheap laptop running 100 operations over 1000 iterations are as follows:

| Language | Execution Time (s) | Max (ns) | Min (ns) | Avg (ns) | C Ratio |
|-|-|-|-|-|-|
| C | 0.335615 | 455000 | 296000 | 335181 | 1.00 |
| C++ | 0.348636 | 477918 | 306957 | 348245 | 0.96 |
| Rust | 0.229681174 | 368683 | 201749 | 229564 | 1.46 |
| Zig | 0.10153 | 541197 | 75332 | 95047 | 3.30 |
| Python | 14.77727734 | 33754451 | 12984472 | 14775610 | 0.02 |
| Java | 0.263353044 | 7772037 | 130966 | 240370 | 1.27 |

\**note: Python timed via interpreter, your times may vary. Please speak to your doctor or a licensed medical professional before attempting Java. Not to be confused with financial advice. Offer void in Utah.*
