# AwesomePHP

Aura Leirós García\
Feito con <3 em Galiza e Portugal

### Useful PHP Functions

#### Include

To include elements in a PHP file we can either... 

1. Add points until get to our desired directory...

`include '../2/something.php';`

2. If we want to include all the directory.

`include __DIR__ . 'pathtodir';`

We need to take into account that when we include a file, this will be efectively replaced in that exact part of the script so we need to be cautious with variables.

#### Arrays

1. Using index

- `ksort($array)` - sorts in ascending order
- `krsort($array)` - sorts in descending order

2. Using value

- `asort($array)` - sorts in ascending order
- `arsort($array)` - sorts in descending order

Either numerically or alphabetically.

/!\ asort will maintain the original index (even if it's implicit) so usually for loops are affected.

The function `array_shift($array)` will remove the first element of an array and return it, respectively `array_unshift($array, $elem)` that appends the element to the head of the array.

- `$array[]` - Adds an element to the end of an array

#### Success and Fail

If a function returns `0` it's usually expected behavior, `1 or -1` is not.

#### Checking equality

In PHP there are two types of equality checking, either

- `==` that checks only if the value is the same.
- `===` that checks that the value and the type are the same.

#### Loops and conditionals 

#### Behaviour by type

- An integer will evaluate to `true` for every non-zero value, including negative numbers.

- A `$string` as condition if the string is not empty it will evaluate to `true` else to `false`.


### Useful pre-defined functions

- `intval()` returns the first integers found in a string, until it found a non-numerical character (that said if the first element is a non-numerical the return will be 0).

- `count($array)` will return the length of the array.

- `join($glue, $array)` returns a string with all the elements of the array using the $glue as separator.

- `date("d M Y")` returns the actual date.

- `phpinfo()` takes optional flags and returns a page with the requested data.

- `preg_match($pattern, $subject, $res)` $res is an array if more than one group is matched.

- `fgets($sock)` allows to read the answer from a sock stream.

- `fputs($socket)` allows to send a request through the socket.

- `fsockopen($server, $port, $errno, $errstr)` opens a socket

- `fclose($socket)` closes a socket

- `serialize() and unserialize()` converts an array of headers into a string and the inverse.


## HTML

### Accesibility


- Use of the <label> tag in forms like in this example:

~~~
/* 1 */

<label>
  Do you like peas?
  <input type="checkbox" name="peas" />
</label>

/* 2 */

<label for="username">Enter your username:</label>
<input id="username" name="username" type="text" />
<label for="username">Forgot your username?</label>
~~~

In the 2nd the for is associated with the `id` parameter, in most of the cases this tag is used only within forms and can't be used when the input has a value='hidden'.

### Structure of common HTML tags

`<a href='link'>Cliquez ici</a>`\
`<img src='link' alt='description'>`