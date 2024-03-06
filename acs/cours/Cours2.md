### Introduction

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

##### Built-in PHP functions for arrays

- count($array) : number of elements into an array.
- is_array($var) : test if the variable is an array
- array_shift($array) : returns the first element and then takes it out of the array, array_unshift adds one.
- array_pop($array) : the same that array_shift.
- join($glue, $array) : returns an string composed of the elements of an array.


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

PHP has a lot of inspiration from C, we found terniary structures, and structures like `try {instr1} catch (e) {instr2}`

Most important the `foreach(array as idx => val) { /* */ }

#### Built-in PHP functions for strings

Very useful for security with requests !!

- strlen
- substr($string, $start, $length) : cuts a string
- trim() : returns a trimmed string.
- intval() : returns the first elements of a chain if they're integers.
- is_numeric : tests if a string is a number
- strpos($string, $substring) : sends the position where the substring starts.


#### Inputs

Very import to use the htmlspecialchars($chars, ENT_QUOTES) so quotes are being properly converted to an HTML format.

This prevents injections attacks!


### Rational Expressions (A.K.A. REGEX)

Two very frequent options

i : do not make a distinction between uppercase and lowercase.\
s : makes that the /n is assimilated to an space.\
m : multiline match

`^` : start of the string `(or line if m option)`\
`$` : end of the string `(or line if m option)`\
`.` : wildcard\
`[...]` : any of the characters inside the brackets.\

- `[^...]` : aby character but the ones inside the brackets.\

#### Generic characters in the RegExp

- \d : any numerical character\
- \D : all but numerical characters\
- \w : any alphanumerical character\
- \W : any but alphanumerical characters\
- \s : any separator\
- \S : any but a separator\
- \ : to 'neutralize' any character.
 
 #### Iteration with RegExps

-  `{n,m}`\
- `?` : equivalent to `{0,1}`\
- `*` : equivalent to `{0,}`\
- `+` : equivalent to `{1,}`\
- `|` : or one or another `m1 | m2`

It's important to take into account the two modes of iteration, greedy (by default) and ungreedy (that we need to use with a +)

We can capture things using parentheses and referencing it later with \1, \2, \3, etc.

#### preg_match function

Function that returns true or false and stores all ocurrences of an applied RegEx to a string and saves into an array.

Use : `preg_match($regex, $string [, $res])` \

`$res` will be an array, that will contain in `$res[0]` the complete matched text, further elements in the array will contain the matched text by groups.

#### Alternatives to preg_match

- `preg_match_all($regex, $string, $res [, $flags])`

This function returns the number of matches. We need to know two important flags 

`PREG_PATTERN_ORDER` that makes an array of arrays, $res[0] will contain the full matches, $res[n] with the strings matched by the n parenthesis in the regex.

`PREG_SET_ORDER` that orders the results so that every match is in the n case.

- `preg_replace($regex, $replace, T)` 

This function replaces all the matches of the regex with the replace string, remember that we can use \0 and \1, T is the code to modify.




 