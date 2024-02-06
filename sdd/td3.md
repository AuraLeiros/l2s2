## TD 3


### Exo 1.

#### 1.1

It's an association (key, value) where key = fingerprint and value = personal file of the person, a hash table seems like a good alternative.

#### 1.2

The hash function is applicated over the keys and returns the position of the elements in the table. Because of the table is an array of size <= 10^5 the hashing function returns a value MOD 10^5

#### 1.3

If one of the elements is 0 all it's going to be 0 and therefore we're going to fill a lot the 0 case. 

Rappel: The interesting about hashing tables is the possibility of dividing information.

The entered integers are [0,99], all the vectors containing a 0 will be stocked in the same case (case 0)

To lower the percentage of collision we can contournate this porblem adding a unit to every unit of the vector before doing the product which makes.
~~~
int g (x1, x2, ..., xn) {
    (int (x1+1)*(x2+1)... (xn+1)) % 1000
}
~~~

#### 1.4

With the given hashing function all the lines return the same value (a collision). É uma questão trampa pois não existe uma funçao boa pra este problema, we have to treat the collisions (next exercise)

### Exo 2.

La chiffre des unités dans nequel base c'est toujours la base

~~~
            g(f(n)) (hex)       decimal
01  le              E              14
02  cours           8               3
03  appelé          3               ...
04  structures      ...
05  de 
06  données
07  est
08  absolument
09  génial
10  j'adore
11  faire
12  ses
13  TD/TME
~~~

In every base, if we have an operation that is `number % base` we will get the last element at the right.

`n % (b^0) + (n - (n % b^0)) % b^1 + ...`




