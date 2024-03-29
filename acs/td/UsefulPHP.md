Aura Leirós García\
Made with <3 in Portugal and Galiza\
A.C.S. 23-24


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




### Structure of common HTML tags

`<a href='link'>Cliquez ici</a>`\
`<img src='link' alt='description'>`

### Functions from TD / TME

#### TD/TME 2

`debut_html($title)` returns the start of an HTML code we need to close the tags (body, h1, html, ...).



`phpinfo()` takes optional flags and returns a page with the requested data.

`RE_URL` regex that filters and url using:
1. Schema
2. Server
3. Port
4. Address of the ressource 
5. Query-String

`preg_match($pattern, $subject, $res)` $res is an array if more than one group is matched.

`array_shift($array)` returns the first value and deletes it from the array

`count($array)` - Returns the number of elements in the array

`tableau_en_table($array, $caption)` Creates an HTML table with two columns "Name" and "Value"

`cherche_index_n($tab, $n)` return String | False returns the n-th element of an array, `false` if count($array) < n

`tableau_en_liste($data, $type='ul')`takes as a parameter an array $data and returns a HTML table that it's in a list form (ul or ol)


`RE_JOUR` `RE_HEURE` `RE_ENTETE` all contained in the respective .php file, the last one allows to verify that is a request and to decompose it.

After a preg_match this is how it's going to be:

1. $res[0] : "Content-Type: text/html; charset=uft-8"
2. $res[1] : "Content-Type"
3. $res[2] : "text/html; charset=utf-8"


#### TD/TME 3

`htmlspecialchars($input, ENT_QUOTES (for the chauvinistic language))`

`specialchars_en_table` Same function as tableau_en_table but securizing it with the precedent function.

`html_form($corps, $method='get', $action="", $att="")`builds the form tag without adding a submit!

`saisie_fiable($tab, $index, $re="")` takes in argument an array that will use POST or GET a string and a REGEX and returns:
1. Tests if tab has an element $index if not returns 1
2. If !$re or the REGEX is matched then return 0
3. Else returns -1

##### form_htmlspecialchars.php

`tableau_pour_cocher($tab, $nom='choix', $mode='array()')` takes an array and an optional name and returns an array with a choice selector. It will allow for multiple if is_array($mode) (checkbox) or single (radio)

`tableau_en_select($options, $name, $choix="")` takes an array of 3 dimensions (name is for name and id, $choix selected='selected') and return a HTML fragment of a selections array. (¡To verify!)

`trouver_sous_index($tab, $index)` Checks that $index is a subindex of the array $tab (a 3D array)

`soumissions_multiples($tab, $n)` allows to check a city.

`header($string)` sends a header !

#### TD/TME4 Requeter en POP

Avaliable functions

`requeter_en_pop($sock, $req)` function that sends a request and reads the answer, returns false if the request fails or the answer does not start by +OK.

`fgets($sock)` allows to read the answer from a sock stream.

`fputs($socket)` allows to send a request through the socket.

`fsockopen($server, $port, $errno, $errstr)` opens a socket

`fclose($socket)` closes a socket.

`fermer_session_pop($socket)`sends a QUIT request to the server to close the session.

`lire_message_pop($socket)` reads the body of the POP server answer

`lire_entetes($socket)` reads the headers and returns an array with them (and sub-arrays in case of multiple values), the index are the headers names.

`choisir_message_pop($socket, $criteres)` $criteres is an array of headers, the function will search all the messages and return an array with all the ones that coincides with the criteria.

`presenter_message_pop($socket, $criteria)` displays all the elements that are within the scope of choisir_message_pop

--- 

`http_args ($serveur='', $entetes=array(), $version='')` returns a request with different elements depending of the HTTP version

`requeter_en_http ($url, $req='GET', $version='1.1', $entetes=array())` This function returns an array composed of the return code an array with the headers in the server answer and the body.

#### TD/TME5

`list($a, $b, $c) = array()` allows to decompose an array and store the VALUES in some variables.

`fournir_page($r)` a cache system returns a code in 3 numbers,, the headers and the document. This function returns the headers + echo page. (a verifier!)

`type_cache($headers)` returns the type of Content-Type found in an array of headers

`limiter_cache($headers)` returns true if theres not expiration or the document expires in the future, false if it's already expired

`time()`

`serialize($array)` transforms an array into an string

`unserialize($text)` the inverse of serialize

`memoriser_cache($dir, $nom, $entetes, $page)` creates the files needed to store a page. returns true if the two files are created.

`file_put_contents` This function is identical to calling fopen(), fwrite() and fclose() successively to write data to a file.

`trouver_cache($dir, $nom)` tries to locate a page with that name and returns an array with it, empty array if it's not found.

`utiliser_cache ($url, $dir)`

`actualiser_cache ($tabCaches, $nom,  $dir, $max)`






