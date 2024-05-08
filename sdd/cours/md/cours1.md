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

### Temporal complexity.

This section focus in the concept of complexity.

We usually try to measure complexity using the best scenario, when we do only the minimum of elementary operations, and the worst case, when we do the maximum.

### Temporal complexity.

The main goal will be to get the tightest bound possible.

Considering that: 

- $T(n)$ represents either the time or space that a function takes as $n$ changes.

- $g(n)$ the function that upper bounds.

Before continuing, we need to do a brief recall of the asymptotism defintion, a matematical concept that describes the behavior of a function as one of its variables approachs a certain value or infinity, without necesarily reaching it.

#### Definition of the Landau notation $O$

$O$ also known as "Big O notation" is used to describe the upper bound (i.e. worst case scenario) of the growth rate of a function.

- Formal definition of $O$: $T(n)$ is in $O(g(n))$ if it exists $n_0 \in \mathbb{N}$ and $c \in \mathbb{R}, \; c \gt 0$ that $\forall n \ge n_0, \;  T(n) \le c \cdot g(n)$

This can be explained in a more informal language, we consider $T(n)$ (the function that represents the growth of time or space that a function takes) and we can claim that it's in the set of functions upper bounded by $g(n)$ (displayed as $O(g(n)))$, if and only if, for every value of $n$ equal or bigger than the original $n (n_0)$ $T(n)$ is equal or smaller than the bounding function times a positive real constant $c$. 

This constant is important because it allows $g(n)$ to be bounding without modifying the growth rate that is what are we actually focused on.

#### Definition of the Landau notation $\Omega$

$\Omega$ is the Landau's notation used to describe the lower bound (best case scenario).

Formal definition of $\Omega$: $T(n)$ is in $\Omega(g(n))$ if and only if exists a $n_0 \in \mathbb{N}$ and a positive $c \in \mathbb{R}$ that $\forall n \gt n_0$ that satisfies $c \; \cdot g(n) \le T(n)$

This is similar to the definition of $O$ but in this case we are looking for the lower bound, the best case scenario. $\Omega$ is the first bounding function that is smaller than $T(n)$

#### Definition of the Landau notation $\Theta$

$\Theta$ is the Landau's notation used to describe a function that works as both a lower bound and upper bound (playing with the constant)

- Formal definition of $\Theta$: $T(n) \in \Theta(g(n))$ if and only if exists a  $n_0 \in \mathbb{N}$ and two positive $c_1, c_2 \in \mathbb{R}$ that $\forall n \ge n_0, c_1 \cdot g(n) \le T(n) \le c_2 \cdot g(n)$

#### Why is this important?

When we do operations to data the choice of data structures has a big impact in the number of elementary operations that we have to do and therefore the time we need to executate a program.

### Spatial complexity.

The spatial complexity of an algorithm is an estimation of the memory space that it uses during the execution.

There's usually a trade-off between temporal and spatial complexity.

## Modular Programming

Modularity is the concept of dividing our program into multiple and independent parts in different files.

This understanding is highly beneficial as it allows for improved code comprehension, reusability, and facilitates the stages of code development.

### Modules in C

In C a module is composed of an `.h` file that describes the structures, gives the declaration of functions and includes libraries, this file has to have the following structure:

~~~
#ifndef FILE_H
#define FILE_H

/* CODE */

#endif
~~~

These are called guards and are used to prevent the double-inclusion, forbidden in C.

The `.c` files includes the code of the declared functions.

### Compilation

We can either do a separated compilation to get our `.o` files and then join them into an executable, but its not recommended, instead, we can use a `make` file that will do the compilation of things that had changed with a simple command!

For more information, please go back to the first semester C UE or either search the internet, there are YT videos that explains this fairly well!

# Esto es todo amigos!

## Bibliography

- https://www.youtube.com/watch?v=0oDAlMwTrLo Very useful to understand the different notations in growth analysis.