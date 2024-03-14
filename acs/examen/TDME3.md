# TD and TME 3 - Forms

Aura Leirós García\
Feito con <3 em Galiza e Portugal

"Sendo galego non debo de ser máis que galeguista." -Castelao

## Used functions ! 

#### TD

1. `specialchars_en_table($array, $caption)` returns a table (str) like tableau_en_table (TD2) where the elements are sanitized to prevent errors or attacks.

2. `html_form($body, $method="get", $action="", $attr="")` Builds the outer structure of a form.

3. `saisie_fiable($array, $index, $exp='')` This function will check if a given $index in a given $array satifies an expression (Usually we will use one of the previously defined REGEX)

4. `tableau_pour_cocher($tab, $nom='choix', $mode=array())` Creates the body of a form that will use 

#### TP

1. `tableau_en_select ($options, $nom, $choix='')` this will return a string that contains a label and a select tag with different optgroups.

2. `trouver_sous_index ($array, $index)` this function returns the index of a 2D array if it's found or else an empty array.

3. `soumission_multiple($tab, $n)` this function creates a list to be placed inside a form with the aim or displaying only one element at the time.

## TD

### Exercice 1. specialchars_en_table.php

This function aims to create a table with the elements received from a person that sends a form, is esentially the same as `tableau_en_table` but designed to prevent problems and possible injection attacks.

~~~
include '../../TD/2/tableau_en_table.php';
include '../../TD/2/tableau_en_liste.php';

function specialchars_en_table($tab, $chaine){

    $r = array();

    foreach($tab as $key => $val){
        $r[htmlspecialchars($key, ENT_QUOTES)] = htmlspecialchars((is_array($val) ? join("\n", $val) : $val), ENT_QUOTES);
    }

    return tableau_en_table($r, $nom);
}
~~~

### Exercice 2. html_form.php

Builds the outer structure of a form. 

~~~
function html_form($body, $method="get", $action="", $attr=""){

    return "<form action='$action' method='$method' $attr><fieldset>\n" . $body . "\n</fieldset></form>\n"
}
~~~
### Exercice 3. form_urljour.php

This exercise uses the base that it's better that the script that issues and processes the form is the same (to be able to move the script for example). So uses an if-else control structure to do that.

~~~
<?php

if (isset($_POST['jour']) && isset($_POST['url'])){
    $body = specialchars_en_table($_POST, "Informations");
} else {

    $body = "<label for='jour'>jour</label> <input id='jour' name='jour' />\n" . "<label for='url'>Url</label><textarea id='url' name='url'></textarea>\n";

    $body = html_form($body . "<input type='submit'>");
}

echo $body

/* If we want to display all the web page is as easy as */
echo debut_html($titre),
    "<body><div><h1>$titre</h1>\n$body</div></body></html>\n";

?>
~~~


### Exercice 4. saisie_fiable.php

This exercice will first check if there's an element in the provided idx (if not returns 1) then check if either there's not regex or the regex matches (success, returns 0) else returns -1

This is to verify that every input is there and it's correct.

~~~
function saisie_fiable($array, $index, $exp=''){

    if (!isset($array[$index])) return 1;

    if (!$exp || (is_string($array[$index]) && preg_match($exp, $array[$index]))) return 0;

    return -1;
}
~~~

Remember `isset()` and `is_string` will be true if it's provided but it's empty, we should always check either with `empty()` or `!something`


### Exercice 5. form_htmlspecialchars.php

We're testing that the inputs are OK and if not re-sending the form with the previously received values (to facilitate the re-input) this will be made with 

1. For input adding a value attribute.
2. For textarea adding a text between the opening and the closing.


~~~
<?php
$url = saisie_fiable($_POST, 'url', RE_URL);
$jour = saisie_fiable($_POST, 'jour', RE_JOUR);
$titre = "Evénement";
$err = '';
if (!$url AND !$jour) {
    $body = specialchars_en_table($_POST, "Informations");
} else {
    if ($url < 0) $err = ' url';
    $url = ($url > 0) ? '' : htmlspecialchars($_POST['url']);
    if ($jour < 0) $err .= ' jour';
    $jour = ($jour > 0) ? '' : htmlspecialchars($_POST['jour']);
    if ($err) $titre = "Erreur $err $titre"; 
    $body = "<label for='jour'>Jour :</label>" .
          "<input id='jour' name='jour' value='$jour' />\n" .
          "<label for='url'>Url :</label>" .
          "<textarea id='url' name='url'>$url</textarea>\n";
    $body = html_form($body . "<input type='submit'>");
}

echo debut_html($titre),
    "<body><div><h1>$titre</h1>\n$body</div></body></html>\n";
?>
~~~

### Exercice 6. tables_pour_cocher.php

This exercice explains the use of the checkboxes in PHP forms, specially the `<input name='t[EXP]' type='checkbox' />` that creates a sub-array inside the $_GET or $_POST array with the ones selected, the index being the expression and the value the attribute `value` or `on` if it's missing.

For the label tags and id attributes, we use the name without the brackets.

In the case of the 'radio buttons' where only a choice it's possible where one and only one of the tags it's already selected using the `checked='checked'` attribute.

This function returns an array where every element is a string with a label and input tags.

~~~
<?
function tableau_pour_cocher($tab, $nom='choix', $mode=array())
{
    $res = array();
    if (is_array($mode)) {
        $type = 'checkbox';
    } else {
        $type = 'radio';
        $mode = array($mode => true);
    }
    foreach($tab as $k => $v) {
        $c = isset($mode[$k]) ? " checked='checked'" : '';
        $indice = ($type == 'radio') ? '' : "[$k]";
        $res[]= "<input id='$nom$k' value='$v' name='$nom$indice' type='$type'$c />"
              . "<label for='$nom$k'>$v</label>\n";
    }
    return $res;
}
?>
~~~

### Exercice 7. form_index_checkbox.php

~~~
<?php 
include '../../TM/2/debut_html.php';
include '../../TD/2/tableau_en_liste.php';
include 'html_form.php';
include 'tableau_pour_cocher.php';

$villes = array('Paris', 'Lyon', 'Marseille'); // pour essai
if (!isset($_GET['choix']) OR !is_array($_GET['choix'])) {
    $titre = "Possibilités";
    $body = tableau_en_liste(tableau_pour_cocher($villes, 'choix'));
    $body = html_form($body . "<input type='submit' />");
} else {
    $titre = "Choix effectués";
    $final = array();
    // Ne pas faire confiance aux valeurs transmises, repartir des index
    foreach ($_GET['choix'] as $n => $v) $final[] = $villes[$n];
    $body = tableau_en_liste($final);
}
echo debut_html($titre),
    "<body><div><h1>$titre</h1>\n$body</div></body></html>\n";
?> 
~~~


## TP

### Exercice 1. tableau_en_select.php

The objective is building a `<select>` tag to choose a country that will have sub-groups declared with `<otpgroup label="Group1">` (similar to fieldsets, used to group related options together)

~~~
<?php
/// Cette fonction a été concue en ecrivant ses lignes dans cet ordre:
/// 1 2 3 4 6 8 9 10 7 11 12 5 13 14 15 16 17
function tableau_en_select ($options, $nom, $choix='')
{
    $sel = "\n\t<option></option>";
    foreach ($options as $titre => $listes) {
        $groupes = '';
        foreach($listes as $indice => $valeur) {
            $c = ($indice == $choix) ? " selected='selected'" : "";
            $desc = is_string($valeur) ? $valeur : $indice;
            $groupes .= "\n\t<option value='$indice'$c>$desc</option>";
        }
        if (count($options) == 1) {
            $sel .= $groupes;
        } else {
            $t = htmlspecialchars($titre, ENT_QUOTES);
            $sel .= "\n\t<optgroup label='$t'>$groupes</optgroup>";
        }
    }
    return "<label for='$nom'>$nom</label>\n"
        .  "<select id='$nom' name='$nom'>$sel</select>\n";
}
~~~

### Exercice 2. form_pays.php

This script just sends a form with the countries.

~~~
<?php
include '../../TD/3/html_form.php';
include '../2/debut_html.php';
include 'destinations.php';
include 'tableau_en_select.php';

$titre = "Pays";
$body = tableau_en_select($destinations, 'pays');
$body = html_form($body . "<input type='submit' />", 'post', 'form_ville.php');
echo debut_html($titre), "<body><div><h1>$titre</h1>\n$body</div></body></html>\n";
?>
~~~


### Exercice 3. trouver_sous_index.php

This function returns an array with the destinations and pricing in the passed country (i.e. the passed index) and an empty array if does not exist.

~~~
<?php
function trouver_sous_index ($t, $index)
{
    foreach ($t as $v) {
        if (isset($v[$index])) {
            return $v[$index];
        }
    }
    return array();
}
?>
~~~

### Exercice 4. soummision_multiple.php

This function aims to create a selector that allows to only display a city and change it through

~~~
function soumission_multiple ($villes, $n)
{
  if (($n <= 0) OR ($n > count($villes))) $n = 1;
  if ($n > 1)
    $p = "<input type='submit' name='item' value='" . ($n-1) . "' />\n";
  else $p = '';
  if ($n < count($villes))
    $s = "<input type='submit' name='item' value='" . ($n+1) . "' />\n";
  else $s = '';
  $destination = cherche_index_n($villes, $n);
  $prix = $destination ? $villes[$destination] : "?";
  $v = htmlspecialchars($destination, ENT_QUOTES);
  $choix = "<input type='submit' name='item' value='$v' />$prix €";
  return "<ul><li>$p</li>\n<li>$choix</li>\n<li>$s</li></ul>";
  /// ou bien: tableau_en_liste(array($p, $choix, $s)
}
?>
~~~

### Exercice 5. form_ville.php

Wrapping-up the TME searching finishing a PHP script that is readily-usable to search a city inside the array and display the pricing.

This combines hidden inputs, modularity of PHP while using forms and etc.

~~~
<?php
include '../../TD/3/html_form.php';
include '../../TD/2/tableau_en_table.php'; // pour cherche_index_n n > 0
include '../2/debut_html.php';
include 'trouver_sous_index.php';
include 'soumission_multiple.php';
include 'destinations.php';

$item = isset($_POST['item']) ? $_POST['item'] : 1;
$pays = isset($_POST['pays']) ? $_POST['pays'] : '';
$villes = trouver_sous_index($destinations, $pays);
if (!$villes) {
    header("HTTP/1.1 303");
    header("Location: form_pays.php");
} else {
    $titre = "Votre voyage";
    if (is_numeric($item)) {
        $pays = htmlspecialchars($pays, ENT_QUOTES);
        $hidden = "<input type='hidden' name='pays' value='$pays' />";
        $body = html_form(soumission_multiple($villes, $item) . $hidden, 'post');
    } else {
        if (isset($villes[$item]))
            $body = "Bon séjour à $item pour " . $villes[$item] . "€.";
        else $body = "Ville inconnue";
    }
    echo debut_html($titre),
        "<body><div><h1>$titre</h1>\n$body</div></body></html>\n";
}
?>
~~~