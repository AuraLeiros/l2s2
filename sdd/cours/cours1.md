# Cours 1

Aura Leirós García\
València en Falles! <3

## Introduction: Abstracts

A data structure is the way of building an abstract data type, but a question arises, what is a abstraction and how achieve it?

### Abstraction

The broad concept of abstraction comes from the method of isolating some part of something and consider it independent.

We have two basic types of (human) abstraction.

1. Simplification: reduces the description of an object to have only the essential.

2. Generalization: starts with a particular thing and frames into a broader class of objects.

#### The abstract data type

An abstract data type is a mathematical specification of a set of objects and their applicable operations.

#### Applied Abstraction

In a broad and general definition, the abstraction in a CS setup is the art of identifying and synthesize common characteristics and uses of different elements to simplify them and ease their manipulation.

Using abstract data types help us to create useful and reusable code that is easy to understand without needing to know their memory representation or other technical information.

## Data Structures

A data structure is a representation in the memory of a computer of the objects built by an abstract type with the implementation of operations in this representation.

`Example: A bool is a data structure that is represented by 1 octet in C++ and 1 bit in Java`

As always in CS we need to consider a trade-off when declaring a new data structure, in this case between:

1. Spatial Complexity, measured in octets.
2. Temporal Complexity, how much time it takes measured in the no. of elementary operations. Is estimated counting the number of elementary operations.

### What is a program...

A program is a code composed of:

1. A finite set of variables (entry vars included)
2. A finite set of elementary operations.
3. A finite set of control structures.

A variable defines a simple type or a more elaborated structure.

An elementary operation is an operation that takes a known number of calls to the CPU (arithmetical, logical, etc.), like a = a + b.

### ...and what is an algorithm?

An algorithm is a program that solves a problem that satisfies the properties of termination and validity.

A problem is defined based in parameters (that take values in a given domain) and a question.

Properties:

1. Termination: finite number of elementary operations.

2. Validity: Solving the problem without depending in the entry values (i.e. for any set that satisfies the requirements).

## Complexity: Is my algorithm a complexity disaster?!

This section comes back to develop the concept of temporal complexity



