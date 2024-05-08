# Cours 4 - SDD

Non-Linear Data Structures

Aura Leirós García

# Linear Data Structures  

A data aggregation structure is considered linear if there exists a first and last element and at least a *next* function that allows iteration through its elements. The complexity in their algorithms is determined by the number of elements in the structure.

Examples of linear structures are the array, a list (stack and queue), hashing tables, etc...

# Non-Linear Data Structures

## Binary trees 

We're going to do a small recap of binary trees and its types.

This non-linear structure can be defined recursively as follows:

A binary tree is either empty (a null pointer in C) or is composed of a single node, where the left and right pointers each point to a binary tree.

---

*Alternative. Sorbonne's recursive definition:*

A tree data structure it's a recursive organization of a set of elements using a partition $\{x\} \times \prod_i K_i$ where every $K_i$ has a tree structure. 

- {x} is the root
- trees of only an element are called leaves.
---

A binary tree can be of various types, we're going to define 4 essential ones:

1. Rooted binary tree

This type has a root node and every node has at most two childrens.

2. Full binary tree

This is a tree where every node has either 0 or 2 childrens.

4. Complete binary tree

Type of tree that is full in every level except possibly the last, if it's completely full including the last we call it *perfect* if not, *nearly complete* 

## Heap

A heap (in french, *tas*) is a tree-based, non-linear data structure that satisfies the heap property, *parents have a higher priority key than any of their children*.

It must be a complete or nearly complete binary tree, there are two types of heaps.

1. max-heap: where the key of every node is greater than their childs.

2. min-heap: where the key of every node is smaller than their childs.

## Graphs

A graph is a mathematical structure used to represent relationships between elements through nodes and edges, they don't have any rules, so they are called the *wild west of node-based structures*

A brief glossary on the elements of a graph:

1. Nodes: Elements of the graph, sometimes also called *vertex*.

2. Edges: Connections between nodes, it's called *directed* if goes in only one direction or *undirected* otherwise.

3. Path: Sequence of edges to take from a path to another, we call *path length* the number of nodes on a path.

4. Neighbor: Two nodes connected directly by an edge.

---
*Sorbonne's formal definition:*

A structure in the form of a graph represents a set of elements and their pair relationship within that set.

---

Some remarks:

1. In a graph there's not a first and last element.

2. The complexity of an algorithm depends of the number of nodes, the number of paths, the diameter (the longest path possible).

## UML: Aggregation and Composition

Because of the uneficiency of markdown with images, please refer to the slides for this part of the course.

An aggregation and a composition it's a non-symetrical relationship between an element A and B that indicates a strong relationship between them (including a belonging)

- A composition (filled diamond) indicates us that an element B needs one of type A, an aggregation it's more flexible.

- A composition indicates as well the exclusivity of the type A, it can be shared.

### Implementation of an aggregation in C

In the case of aggregations, there's a weak connection between the two elements and it's common to use pointers to establish the relationship.

```C
typedef struct {
    int vitesse;
} processeur;

typedef struct {
    float prix;
    processeur* proc;
} ordi;

/* Creation */ 

ordi* cree_ordinateur (float prix, processeur* p){
    ordi* o = malloc(sizeof(ordi));
    o->prix = prix;
    o->proc = p;
}

/* Use */

if (o != NULL) {
    if (o->proc != NULL){
        o->proc->vitesse = 1;
    }
} 

/* Deletion */

free(o);
free(p);
```

As we can see, the processeur exists separately, it's passed as an argument to the function, free'd separately, etc.

### Implementation of a composition in C

1. External composition

In this case we use pointers to contain an element inside of the other and we use a delegation pattern, this is, evaluating a member of one object in the context of another.

```C
typedef struct {
    int vitesse;
} processeur;

typedef struct {
    float prix;
    processeur* proc;
} ordi;

/* Creation */
ordi* cree_ordinateur(float prix, int vitesse) {
    ordi* o = malloc(sizeof(ordi));
    processeur* p = malloc(sizeof(processeur));
    o->prix = prix;
    o->proc = p;
    p->vitesse = vitesse;
    return o;
}

/* Use */ 
if (o != NULL) {
    o->proc->vitesse = 1;
}

/* Deletion */ 
free(o->p);
free(o);
```

In this case, we can clearly see that processor is always in the context of a computer, even if it's technically a separated element.

2. Internal Composition

In internal compositions we're going to do some modifications to the internal distribution.

```C
typedef struct {
    int vitesse;
} processeur;

typedef struct {
    float prix;
    struct processeur proc;
} ordi;

/* Creation */

ordi* cree_ordinateur(float prix, int vitesse) {
    ordi* o = malloc(sizeof(ordi));
    o->prix = prix;
    o->proc.vitesse = vitesse;
}

/* Use */
if (o != NULL){
    o->proc.vitesse = 1;
}

/* Deletion */
free(o);
```

We don't actually need to allocate memory to processeur because it's a static structure completely dependant of the ordi element!

### Choosing a structure

As always in CS, there's a trade-off between the three main features.

|                     | Aggregation | External Comp. | Internal Comp. |   |   |   |   |   |   |
|---------------------|-------------|----------------|----------------|---|---|---|---|---|---|
| Flexibility         |  ++         | ++             | +              |   |   |   |   |   |   |
| Anti-bug            | -           | +              |  ++            |   |   |   |   |   |   |
| Easy of development | ++          | ++             | -



### Two-ways reference

There are times when two elements that have a relationship may need to access each other. To accomplish this we can set up a pointer to the other in both structures.

### Multiple reference

In cases where multiple A elements are associated with a single B element, we can set-up a pointer array and store there the A elements.

## Back to non-linear structures

We're going to introduce a new concept, the *recursive aggregation / composition* that is a relationship within an entity itself, not necessarily a direct one.


### Applied to binary trees

1. Binary trees

A binary tree can be represented by a data structure that has two relations of recursive aggregation, `left` and `right`. It's an aggregation because we need to consider the scenarios where either or both of these may not exist.

~~~C
typedef struct s_nodeB {
    int content;

    struct s_nodeB* child_left;
    struct s_nodeB* child_right;
} binary_node;
~~~

2. n-ary tree v1

A n-ary tree is a data structure that can accomodate an indefinite number of child per node, therefore this structure uses multiple references to establish a recursive aggregation relationship.

~~~C
typedef struct s_nodeN {
    int content;

    struct s_nodeN** childs;
} nary_nodel;
~~~

3. n-ary tree v2

In the case of v1, there isn't a relationship that facilitates accessing the parent node (i.e. navigating upwards).

~~~C
typedef struct s_nodeN {
    int content;

    struct s_nodeN* father;
    struct s_nodeN** childs;
}
~~~

### Applied to graphes

A directed graph is defined by nodes where each node can have an undetermined number of parent and child nodes. This means that are also an undertemined number of in and out edges.

1. v1

Similar to the n-ary tree v2

~~~C
typedef struct s_nodeG{
    int content;

    struct s_nodeG** parents;
    struct s_nodeG** childs
}
~~~









## Bibliography

- http://cslibrary.stanford.edu/110/BinaryTrees.html

- https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1206/lectures/graphs/