# TD and TME 2 - Basic HTML

Aura Leirós García\
Feito con <3 em Galiza e Portugal

## Used functions ! 

#### TD

1. `tableau_en_table($array, $caption)` returns a string with an HTML table with a caption and two headers Name and Value, using elements stored in the $array.

2. `cherche_index_n($array, $n)` returns the index (indexing from 0) or false if the length of the array is smaller than n. 

3. `tableau_en_liste($array, $tag='ul')` returns an HTML list as a string either ordered or unordered depeding of $tag.

4. REGEX `RE_JOUR` No matching groups.

5. REGEX `RE_HEURE` Two matching groups, for the hour and the AM / PM

5. REGEX `RE_ENTETE` Two matching groups, name of the header and attribute(s) / value(s).

After a preg_match this is how it's going to be:

1. $res[0] : "Content-Type: text/html; charset=uft-8"
2. $res[1] : "Content-Type"
3. $res[2] : "text/html; charset=utf-8"

#### TP

1. `debut_html($title)` this function returns the start of an HTML code without the `</html>` closing tag

2. REGEX `RE_URL` match this groups `schema://site:port/chemin?query-string`

3. REGEX `RE_CHEMIN` match the chemin part.


## TD

### Exercice 1. affiche_tableau.php

This exercise is to make a first aproach to the array manipulations.

Including declarations, looping through them and using the system functions `ksort` `krsort` `asort` `arsort` and `array_shift`

~~~
<?php

$Candidats = array("Bob", "Alice", "Chris");

/* First case: for bucle */

$html = "<ul>";

for($i=0; $i < count($Candidats); $i++){
    $html .= "<li>" . $Candidats[i] . "</li>\n";
}

foreach($Candidats as $elem){
    $html .= "<li>" . $elem . "</li>\n";
}

while($Candidats){
    $html .= "<li>" . array_shift($Candidats) . "</li>\n";
}

$Scores =  array("Bob"=>300, "Alice"=>130, "Chris"=>30);

/* ----------------------------- */

$html = "<ol>"

foreach($Scores as $name => $points){
    $html .=  "<li>". $name . ":" . $points . "</li>";
}

$html .= "</ol>";

return $html;

?>
~~~

### Exercice 2. tableau_en_table.php

This is a key function that spawns a html table with the columns "Name" and "Value" using an array and a caption passed as a parameter.

There will be two headers for the table, one at the beginning and other one at the end. 
~~~
function tableau_en_table ($tab, $nom) {
    if (!$tab) return '';
    $chaine = "";
    foreach($tab as $k => $v) {
        $chaine .= "<tr>\n<td>$k</td>\n<td>$v</td>\n</tr>\n";
    }
    $th = "<tr>\n<th>Nom</th>\n<th>Valeur</th>\n</tr>\n";
    return "<table>\n<caption>$nom</caption>\n$th$chaine$th</table>\n";
}
~~~

~~~
function cherche_index_n($tab, $n){
    
    foreach($tab as $idx => $val){
        if (! --$n){
            return $idx;
        }
    }

    return false;
}
~~~

### Exercice 3. tableau_en_liste.php

This function will display all the elements of an array in form of an unordered or ordered list (unordered by default). 

Recursive function! Will transform the given array in one where every value is the value in a list-structure string.

~~~
function tableau_en_liste($tab, $tag="ul"){

    if (!is_array($data)){
        return $data;
    }

    if (count($data) == 1){
        return array_shift($data);
    }

    foreach($tab as $idx => $val) $data[$idx] = tableau_en_liste($val);
    return "<$type><li>" . join("</li>\n\t<li>, $data) . "</li></$type>\n";
}
~~~

### Exercice 4. re_jour.php

This is the first exercice of REGEX that will match a date YYYYMMDD in the range of 00000000 to 99991939 (it's supposed to allow some impossible dates)

~~~
<?php
define('RE_HEURE', "/^([01][0-9]|2[0-3])[0-5][0-9][0-5][0-9]([ap]m)?$/i");
?>
~~~

### Exercice 5. re_heure.php

Same as with re_jour in this case the REGEX is implemented with groups using parentheses and has an indicator for AM/PM

~~~
<?php
define('RE_HEURE', "/^([01][0-9]|2[0-3])[0-5][0-9][0-5][0-9]([ap]m)?$/i");
?>

/* Official solution but the question does not asks for the AM/PM distintion */
~~~

### Exercice 6. re_entete.php

Designed to match a header into groups, the first group is only the name of the header and then a single group with the attributes 

~~~
<?php 
define('RE_ENTETE', "/^([A-Z][A-Za-z]*(?:-[A-Z][A-Za-z]+)?):\s+(.*?)\s*$/");
?>
~~~

## TP

### Exercice 1. debut_html.php

This function creates the start of an HTML code, important, we still need to close the HTML tag!

~~~
<?php
function debut_html ($title) {
  return
    "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML Basic 1.1//EN'
        'http://www.w3.org/TR/xhtml-basic/xhtml-basic11.dtd'>\n" .
    "<html xmlns='http://www.w3.org/1999/xhtml' lang='fr'>\n" .
    "<head>\n" .
    "<meta http-equiv='Content-Type' content='text/html;charset=utf-8' />\n" .
    "<title>" . 
    $title .
    "</title>\n" .
    "</head>\n";
}
?>
~~~

### Exercice 2. metissage.php

This exercice is a simple PHP script that send the actual date in d M Y format using the debut_html function. This is a good example of alternating between PHP and HTML.


~~~
<?php
include 'debut_html.php';
echo debut_html("Date du jour");
?>

<body>
<h1><?php echo date("d M Y"); ?></h1>
</body></html>
~~~

### Exercice 3. informations.php

This will output the informations of the server contained in the $_SERVER array.

~~~
<?php
include 'debut_html.php';
include '../../TD/2/tableau_en_table.php';

echo debut_html("Informations sur le serveur");
echo tableau_en_table($_SERVER, 'Informations sur le serveur');
echo '</html>'
?>
~~~

### Exercice 4. re_url.php

This is a REGEX that will match in groups the schema, site, port, address and query-string like in this `schema://site:port/chemin?query-string` exemple.

~~~
define('RE_URL', "@^(?:(\w+)://)?([^/:]*)(?::(\d+))?(/[^?]*)[?]?(.*)$@");
~~~

### Exercice 5. re_chemin.php

This REGEX aims to get the repertoire, the name of the file and the extension.

For this exercise is good to remember that `*? and +?` try to get the shortest and without the `?` will be the most long one.

~~~
$nunix =  "][(){}<>|&;'\"";

define('RE_CHEMIN',
       "@^([^$nunix]*?)([^$nunix/]*?)(?:[.]([\d\w]+))?$@");
~~~