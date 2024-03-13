### Useful PHP Functions

#### Arrays

1. Using index

- `ksort($array)` - sorts in ascending order
- `krsort($array)` - sorts in descending order

2. Using value

- `asort($array)` - sorts in ascending order
- `arsort($array)` - sorts in descending order

Either numerically or alphabetically.

asort will maintain the original index (even if it's implicit) so usually for loops are affected.



### Checking equality

In PHP there are two types of equality checking, either

- `==` that checks only if the value is the same.
- `===` that checks that the value and the type are the same.

### Loops and conditionals 

#### Behaviour by type

- An integer will evaluate to `true` for every non-zero value, including negative numbers.

- A `$string` as condition if the string is not empty it will evaluate to `true` else to false.


### Useful pre-defined functions

- `intval()` returns the first integers found in a string, until it found a non-numerical character (that said if the first element is a non-numerical the return will be 0)

