# Cours 3 - SDD

This lecture starts with the question, how can we easily find data associated with a key?\

Considering that...

1. We don't know the number of elements.
2. We need a fast access to the elements.
3. The keys don't need to be sorted.

## Direct method

We have the good 'ol method of using arrays, where we associate every piece of data to an (usually) int index.

This method has different problems...

- When the universe of keys, $U \ne \set{0,\ 1,\ ... , \ M-1}$ (the index does not have that structure)
- $|U|$ it's too big and the array is too big to be saved in the memory
- Different elements have the same key

The solution to this it's using elements from the...

## Hashing tables

Formal defition:

*Table that instead of stocking the element of key $k$ at the index $k$ of the table, stocks it at the index $h(k)$, where $h$ it's a hashing function $U \mapsto \{0,1,...,m-1)$*

The core idea after this is to create an on-the-fly key to store the data using pre-defined hashing algorithms, at the moment of searching something at the hashing table, we would use the hashing function to our input and then search with directly (friendly reminder, $O(1)$)

The main problem that we may have is when selecting our $h(k)$ function, it needs to be that...

- The calculations to hash the input must be fast (and efficient).
- $h$ must try to evade collisions (where two unrelationated elements get the same index).

Unfortunately, even with the best hashing algorithm, collisions are inevitable, so we need to prepare solutions for when this happens, using either resolution by chaining or by open addresing.

### Finding a good hashing function

A good hashing function it's the one that it's calculated fast, usually $O(1)$.

The usual hashing functions transforms the key $k$ in an int using a function $f: \ \mapsto \mathbb{N}$ and then maps the number between $[0, m-1]$ with a $g$ function, $h(k) = g \circ f(k)$

Different proposals

1. Using divisions: $g(x) = x \div m$ chosing a m that it's not near of a power of two
2. Using multiplication $g(x) = \lfloor m(x\Alpha - \lfloor x\Alpha \rfloor)\rfloor$ where m it's not critical, Knuth proposes to use $\phi$, the golden number.


### Load factor of a hashing table

Before continuing with the two types of resolution, is essential to understand the concep of load factor, calculated with the formula:

$\alpha = \dfrac{n}{m} $ where $n$ is the number of elements in the hash table and $m$ the total cells in the table.

A low load factor is a sign of underutilization, where collisions are less likely which improves accessing times at the tradeoff of likely being overusing memory ressources, at the other hand, a high load factor signals overusing and therefore more collisions, this can be more memory efficient but calcultions time and complexity overall will augment drastically. 

There's not an easy or equilibrated solution, it depends of our problem and implementation.

*Hypothesis: Simple Uniform Hashing, every case of the table has an equal probability of receiving an element drawed randomly.*




## Hashing: Resolution by chaining

The principle of this method is that every element of the table is a linked list, in the case of collision this element is added to the linked list in that case.

### Complexity

Hypothesis: the calculation of the hashing function $h(k)$ is in $O(1)$ and that minimaze at maximum the collisions.

Remark: All the complexity analysis depends of the load factor $\alpha$

1. For the insertion of an element

First of all the calculation of the hashed index, $h(k)$, is $O(1)$ and we do an insertion (at the first element) that is also $O(1)$ so we have that the insertion is $O(1)$.

2. For the suppresion

In the case of having a reference to the element and is a double linked list, $O(1)$, this is we only need to update the previous and next pointers.

3. Searching for an element

In the worst case scenario that all the elements of the table are in the same linked list, the complexity will be in $\Theta(n)$ as we need to iterate through that list.

4. Searching an element that is not in the table

Under the hypohesis of the Simple Uniform Hashing, the search of an element that it's not in the table it's $\Theta(1 + \alpha)$ 

This can be explained as the result of the complexity of computing the hash and access to the case, $\Theta(1)$ and that the length of an average chained list with a decent hashing function is proportional to $\alpha$ and therefore the complexity of iterating through it will be $\Theta(\alpha)$

5. Searching of an element that is in the table

Again under the hypthesis of the Simple Uniform Hashing, the search of an element that is in the table is $\Theta(1 + \alpha)$.

The explanation is kind of similar as the point 4, but a bit more complicated, let's start with the fact that the hypothesis of the SUH implies that the mean length of the lists after inserting $(i-1)$ elements  is $\dfrac{i-1}{m}$ (supposing elements are inserted at the end), almost equal to the load factor as before.

Therefore the mean of number of elements that we're going to examinate during the search of the ith element is equal to $ 1 + \dfrac{i-1}{m}$, this takes to $\dfrac{1}{n} \sum_{i=1}^{n} (1 + \dfrac{i-1}{m}) = 1 + \dfrac{\alpha}{2} - \dfrac{1}{2m}$

We can wrap it up saying that the average time ($\Theta$) is the sum for all linked lists of the average time of searching an i element in such linked list divided by the total number of entries in the hash table. That is $\Theta(1 + \alpha)$.

Note for the reader: This is the 17th slide of the attached lecture.


### Conclusion

If the number of cases of the table it's at least proportional to the number of elements to stock, $\alpha = n / m = O(m) / m = O(1)$


| Operation                  | Complexity  | 
|----------------------------|-------------|
| Add an element             | $O(1)$      |   
| Remove (double)            | $O(1)$      |   
| Remove (single)            | $O(n)$      |    
| Search                     | $\Theta(n)$ |   
 

## Hashing: Open Addresing

The resolution using linked lists can be very memory intensive so we can try to skip in using pointers to stock directly the elements in the table and not in linked lists.

Advantage: Uses less space that resolution by chaining, we can use bigger tables, the problem is how we solve the collisions.

The principle usually lies in scanning the table until finding an empty case to stock the element, the way of scanning will depend of the element's key.

Hypothesis. Uniform Hashing, every key has an equal chance of having any of the $m!$ permutations of $\{0, ..., m-1\}$ as sequence of scans

In practic that hypothesis is never verified, we only have approximations.

### Hashing functions

1. Linear probing

Tries to place the key in the closest empty cell, usually provides good performance because the CPU's tendence to access the same set of memory addresses but it's more sensible to the quality of the hashing function and can form clusters of filled cases making the scan take long.

2. Quadratic probing

This works taking the result of a function and applying to it a quadratic polynomial until  an empty case is found, the problem originates when 2 keys $k_1, k_2, \; h'(k_1) = h'(k_2)$ will have the sequence of scans.

There's a third hash function more performant that approaches the hypothesis of the uniform hashing, the *double hashing*.


## Bloom filters

A bloom filter is an space-efficient probabilistic data structure that is used to test if an element is part of a set, this kind of structure can't have false negatives but false positives are possible.

Note to the reader: We will skip this part of the lecture because at least this year is more like a general culture thing, but I highly recommend to read about this.

## BONUS: Universal hashing

Universal hashing is a way of coding hashing tables with the main objective of evitate attacks to our data where a pirate uses keys having the same hashed value.

This is accomplished selecting our hashing function independently of the keys every execution of the program.

Note to the reader: As in the bloom filters, we're going to skip this part, but it's highly recommended to see the lecture, a video or some information about this type of hashing.

## Conclusions

First of all, we will prioritize using resolution by chaining.

Then we have the practical applications of this type of data structures, data integrity over files downloaded from the net, proof of works, blockchains, etc.
