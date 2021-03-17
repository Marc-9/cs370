README
======

This package includes the following files.

|-- Coordinator.c [This is the driver program which will be used as the program to take input and fork to Checker]
|-- Coordinator.h [Header file declaring the function exposed from Coordinator]
|-- Checker.c [This program is loaded into a process from exec with the divisor and dividend, and checks for divisibility]
|-- Checker.h [Header file declaring the function exposed from Checker]
|-- README.txt [This file]

To compile:
    make all

To run:
    ./coordinator <dividend> <divisor> <dividend> <dividend> <dividend>

For example;
    ./coordinator 1 2 3 4 5
