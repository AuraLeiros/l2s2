# Cours 5 - SDD

Aura Leirós García

## Preface

Before starting I would like to revisit the main concept of this course: the *data type*. 

Defined as a classification of data that specifies the possibles values, the operations that can be performed on it and the way it is stored in memory, it's composed of two elements:

1. Abstract Data Type

An Abstract Data Type (ADT) is a mathematical model for data, defined by its behavior from a user's perspective, this is, the potential values that the data can hold and the operations that can be performed on it, abstracting away from implementation details.

ADT's are strictly theoretical concepts, analogous to the algebraic structures, which are caracterized for having a domain, a collection of operations and a set of constraints to satisfy.

2. Data Structure

Low-level, concrete implementation of the ADT's focusing on how data is organized in memory, with the main focus in improving efficiency.

## Introduction

This lecture focuses on introducing the Priority Queue ADT and comparing its implemention using arrays and heaps.

At the end of the course, we will continue with binary trees and begin to work with recursive functions involving them.

## Priority queues

How can we easily find the minimum element of a dataset?

A priority queue is an abstract data type in which every element is assigned a *priority* (key) that determines the order in which elements are served. Elements with higher priority are given precedence and in case of equal priorities, the FI-FO scheme is followed.

The priority queue can be implemented using different structures.

---
*Sorbonne's formal definition:

A priority queue is an abstract data type that operates over a set of elements that satisfies a complete order.

---

### Base operations

Given a set of elements $F$ and an element $x$.

The basic operations of a priority queue are:
e
1. Insert an element $\rightarrow$ `insert(F, x)`

2. Return the element of F with the largest / smallest key $\rightarrow$ `max(F)` / `min(F)`

3. Return and remove from F the element with the largest / smallest key $\rightarrow$ `extract_max(F)` / `extract_min(F)`

## Implementation

### Using arrays and linked lists.

The structure we're using
~~~C
typedef struct cell {
    int priority;
    /* ... */
    struct cell* next;
} s_cell;
~~~
And a sample function to get the minimum from an element `l`.
~~~C
s_cell* minimum(s_cell* l){

    s_cell* argmin = l;
    int min = argmin->priority;

    while (l != NULL) {
        if (l->priority < min){
            argmin = l;
            min = argmin->priority;
        }
        l = l->next;
    }

    return argmin;
}
~~~

After doing the calculus, we'll see that the complexity table is as follows

| Data Structure            | `insert(F, x)` | `min(F)` | `extract_min(F)`       |
|---------------------------|-----------|----------|--------------|
| Array         | $\Theta(1)$      | $\Theta(n)$      | $\Theta(min(F)) + \Theta(n)$ |
| Linked List    | $\Theta(1)$       | $\Theta(n)$    |$\Theta(min(F)) + \Theta(1)$  |
| Sorted Array | $\Theta(n)$       | $\Theta(1)$     | $\Theta(1)$          |
| Sorted Linked List | $\Theta(n)$      | $\Theta(1)$     | $\Theta(1)$        |

It's not necesary to memorize the table, but it's very important to take the time to think why this complexities.

As we're focused in finding the most interesting function complexity-wise 

## Implementation of Priority Queues

### Using lists

We're trying to see if it's viable to implement a priority queue using lists, either unordered simple arrays and linked lists or ordered ones.

The answer is no, in the former the search for `min(F)` / `max(F)` would have a complexity of $\Theta(n)$ and in the latter inserting a new element will have a $\Theta(n)$ complexity.

Therefore, we can't efficiently use lists, let's try with heaps!

### Using heaps

#### 1. Heap as a tree

A heap is an ordered, nearly complete binary tree, all the nodes other than the root have more priority than their parents.

In this lecture we're going to restrict the heap to a left-leaning binary tree, this is, a nearly complete binary tree where the elements in the last level are strictly inserted left to right.

The complexity of this type of heap will be $\lfloor log_2(n) \rfloor$

We see that we can assign an index `i` to every element in the heap, with some interesting properties!

- `i(root) = 1`
- `i(father) = floor(i(fils) / 2)`
- `i(left_child) = 2 * i(father)`
- `i(right_child) = 2 * i(father) + 1`

This are independent of the type of heap we're using.

#### 2. Using an array

This implementation uses the index properties that we talked in the tree implement

This implementation has the inconvinience of having a maximum capacity, it also has to start from the case 1 (i.e. we will never use `t.tab[0]`)

~~~C
#define CAPACITE_MAX 100

typedef struct heap {
    int n;
    int tab[CAPACITE_MAX + 1];
} myHeap;
~~~






## Cours 5 - Cont

## Heap

### Implementation using arrays

As we're using left-leaning binary trees we can assign an index to every element following the left-to-right schema, and we discover some interesting properties.

- `i(root) = 1`
- `i(left_child) = 2 * i(father)`
- `i(right_child) = (2 * i(father)) + 1`
- `i(father) = floor(i(child) / 2)`

This allows us to classify all the nodes into an array, only needing the index of every element.

This functions are independent of the type of heap we're using.

~~~C
#define CAPACITE_MAX 100

typedef struct heap {
    int n;
    int tab[CAPACITE_MAX + 1];
} Heap;
~~~

To preserve the heap properties we can't use the index 0.

/* Insert here the different C functions to manipualte a heap using array and linked lists */

## Preserve coherence

The process of rearranging elements in a heap to satisfy its property is called heapify. There are two essential functions, bubble up and bubble down nodes.

First we're going to define an `exchange(Tas* t, int i, int j)` that changes the place of two elements in a heap, similar to linked lists.

~~~C
void exchange(Tas* t, int i, int j){
    int tmp = t->tab[i];
    t->tab[i] = t->tab[j];
    t->tab[j] = tmp;
    return;
}
~~~

Now, we're going to define a recursive function that bubbles up a node until the root is attained or until is bigger than its parent. This function is going to have a $\Theta(log_2(n))$ complexity.

~~~C
void mount(Tas* t, int i){

    if (!hasFather(i)) {
        return;
    }

    int fatherNode = father(i);

    if (t->tab[fatherNode] > t->tabl[i]){
        exchange(t, i, fatherNode)
        mount(t, fatherNode);
    }

}
~~~

