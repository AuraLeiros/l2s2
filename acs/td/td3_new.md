Aura Leirós García\
TD 3 - A.C.S.\

### Exercice 1.
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

### Exercice 2.
~~~
function html_form($body, $method="get", $action="", $attr=""){

    return "<form action='$action' method='$method' $attr><fieldset>\n" . $body . "\n</fieldset></form>\n"
}
~~~

### Exercice 3.

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

### Exercice 4.

~~~
function saisie_fiable($tab, $chaine, $exp=''){

    if (!isset($tab[$chaine])) return 1;

    if (!$exp || (is_string($tab[$chaine]) && preg_match($exp, $tab[$chaine]))) return 0;

    return -1;
}
~~~

Remember isset will be true if it's provided but it's empty, we should check either with ``empty()``, `is_string` or `!something`

### Exercice 5.

~~~
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

### Exercice 6.

To do this exercise we need to take into account how the checkbox works if we assign an array `[EXPRESSION]` to the name element then a subarray will be created inside the GET or POST array.

~~~
<?php 

/// $tab est un tableau indice (alpha-)numeriquement
/// $nom est le nom souhaité pour la saisie
/// $mode est:
///  - soit un des indices de $tab, et on veut alors un choix unique;
///  - soit un tableau dont les indices forment un sous-ensemble de ceux de $tab
///  qui indiquent les cases à cocher d'avance

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

### Exercice 7

~~~
<?php

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