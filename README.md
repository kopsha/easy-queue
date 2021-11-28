# easy-queue for ansi c

A simple and fast static ring buffer implementation in ANSI C

## Interesting stats

* ![build passed](https://img.shields.io/badge/build-passed-brightgreen)
* ![code coverage](https://img.shields.io/badge/code%20coverage-100%25-brightgreen)
* ![branch coverage](https://img.shields.io/badge/branch%20coverage-100%25-brightgreen)


## why a static queue, you ask...

Static implementations are really fast, portable (if you're not bothered
by compiling) and safe.

Any ANSI C implementation cannot be super generic to cover each possible
use case, but hopefully its simplicity allows you to easily customize it
to your own needs.

For example it would worth to parametrize the type of the underlying
type. For the moment, I have considered a _byte_ as it is the most
versatile in embedded systems.

The only thing you need to do before using it is to define the `QUEUE_SIZE`
which, unfortunately will be used for all further queues. That is a small
price to pay for the speed of using static implementations.

Maybe the next thing for our fellow ANSI C coders is some smart, minimalistic
C templating mechanics, using some external tool. I guess it's going to
be _Python_, since it is already supported by so many platforms.


## overview

This whole project, is a bit overkill, but it was necessary when I decided
to ensure it is tested with *100% code and branch coverage*, as safety is
most critical in embedded systems.

Yet, the whole test code in [main_tests.cpp](./main_tests.cpp), implemented
using Google Test Framework provides a great collection of all use cases.
And since all code and branches are covered, you can be sure nothing is
missed inthere.
The tests are actually C++ code, because Google Test Framework requires it,
but rest assured, the queue library is fully ANSI C compliant.


## single header implementation

The actual queue implementation lives in a single header file
[easy_queue.h](./include/easy_queue.h). Copy it and use it at will.

## basic example

I have provided also a C client application example at [main.c](./main.c).
