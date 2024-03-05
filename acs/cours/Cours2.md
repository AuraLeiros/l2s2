Programs executed by a web server are wrote in an execution language and they make a new text written in another language, usually, html.

PHP was during a long time the only language interpreted and not compiled which makes to have a great advantage in portability, maintenance  and security, losing in the trade-off the efficiency. 

### PHP Basics

#### Constants

For PHP any symbol that starts with a letter and it's not a reserved word is a constant, this can be redefined with the `define(constant, newValue)` function.

#### Lists

`list($var1, $var2, ...)`
`$var[] = value`

#### Implicit conversion of types

`false` = `''`, `0`, `0.0`, empty array.

To compare we use `===` that checks the type, ``==`` only checks the value.

#### Data types

Classical data types, `int, float, string, true, false, array`

An `array` is initialized with the `array()` function and can have two different structures depending if it's numerical or associate

~~~
$myNumArray = array('que', 'caralho', 'contas');

$myAsocArray = array('hello' => 12, ...);
~~~


#### Functions

~~~
function foo ($1, $2, $3, $4=40){
    ...
}
~~~

The variables declared inside the function are local and temporal, except the ones that are declared global or static.


#### PHP Classes

A class puts together variables and functions to obfuscate them at a global level and avoid nomenclature conflicts.

We can initialize the variables thanks to the __construct function, we can access the elements using `instance->function() and instance->variable` we can substitute instance with `$this`

#### PHP Control structures

PHP has a lot of inspiration from C, we found terniary structures, 