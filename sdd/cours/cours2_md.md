# Cours 2

Aura Leirós García\
Caralho!

## Matrices

A matrix is set of elements that are accesible using a index, usually in one or two dimensions.

### C implementation

1. 1D-Matrix: a simple C array.

Is statically allocated using `int my_matrix[SIZE];` and dinamically with `int* my_matrix = malloc(sizeof(int) * SIZE);`

2. 2D-Matrix: an array of arrays.

Is statically allocated using `int my_matrix[ROWS][COLUMNS];` and dinamically with `int** m = (int **) malloc (2* sizeof(int*));` and a loop to initializate every element inside. In both cases the type will be an `int**` (pointer-to-pointer)

Remember that for any `malloc()` that wee do we need to have the corresponding `free()` when we no longer want to use it or in case of an error, a loop (or nested loops) will be needed to do this.

#### Complexity of operations with matrices

1. Acces a known index in an array: $O(1)$.

2. Find a element in an array and return the index: $O(n)$ (or $O(log(n))$ if the array is ordered and we use a dichotomic search).

3. Delete a element with a known index $O(n)$ because we need to move all the cases to maintain the order.

4. If we know the case then is $O(1)$, if we need to search for the case then it will be $O(n)$.

## Lists

Abstract data type that can be defined by a finite series of elements $(x_1, ..., x_n)$ the list is empty if $n = 0$. We pass from the case $x_i$ to the $x_{i+1}$ with a function `succesor`, a non-empty list has two extremes, `head` and `tail`.

### C implementation

We can use a unidimensional C array but if we don't have index or it's ordered, we try not to use contiguous memory because it consummes a lot of place in the memory, we use instead linked lists.

## Linked Lists

Data structure defined by a set of cells, there's always going to be a cell that points to another element of the list (usually the next element), we can differenciate into singly linked lists and double linked lists, the former having only a ``succesor`` cell and the latter having both `predecessor` and `sucessor`

Example:

~~~
typedef struct list {
    char* name;
    int something;
    struct list* predecessor; /* Points to the element that is before, NULL if is the first */
    struct list* succesor; /* Points to the next element, NULL if it's the last */
} List

/* Access to an element */
List* myList = malloc(sizeof(List));

myList->name = "whatever"
~~~

The `->` automatically access the elements and de-references it if it's a pointer.

Friendly reminder that we're declaring a `struct list` and later creating an alias using the `typedef` that's why there's the `list` and `List`.

Note to the reader: We're omitting in this resume the common operations with linked lists, they're in the poly and they're kind of common sense.

### Complexity of operations with linked lists

1. Accesing an element: $O(1)$ if it's the first element, $O(n)$ otherwise.

2. Delete an element: $O(n)$ because we have to search in the list (therefore the $O(n)$) and then a simple $O(1)$ to update the pointer.

3. Insertion of an element: $O(1)$ in the head and $O(n)$ at the end.

## Queues

A queue is an abstract data type that represents a set of homogeneous data using the FIFO (First In, First Out) principle.

In C they're implemented using double linked lists.

### Complexity of operations with queues

All the operations, usually, create_queue, is_empty, in_queue and de_queue, are $O(1)$.

## Stacks

Abstract data type represented by a set of homogeneus data using the LIFO (Last In, First Out) principle

In C they're implemented using single arrays or singly linked lists, the difference between the two implementations is about the memory reservation.

### Complexity of operatiosn with stacks

As in the queues, the usual functions, create_pile, is_empty, in_stack, de_stack are $O(1)$

## Execution Pile

DO NOT MISTAKE with stacks.

When we call a function, a memory zone is automatically reserved for the call. This zone contains variables declared within the function, as well as those passed as parameters, this zone is not cleared until we arrive to either the `return` statement or the closing curly brace. If inside or function $f$ we call a function $g$ the memory zone of $f$ will stay during the execution of $g$.

As we saw in the OCaml UE, the function calls are stored in the stack until ending, which can cause memory errors if there are many calls in between, especially in the case of recursive functions. That's why it is preferable to use tail recursion.