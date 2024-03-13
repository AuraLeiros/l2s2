Aura Leirós García\
TD 2 - A.C.S.\

### Exercice 1.

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

### Exercice 2.
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

    return $false;
}

~~~

### Exercice 3.


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

### Exercice 4.

~~~
<?php
define("RE_JOUR", "/^\d{4}[0-1][0-9][0-3]$/");
?>
~~~

### Exercice 5.

~~~
<?php

define("RE_HEURE", "/^(0[0-9]|1[0-9]|2[0-3])([0-5][0-9]){2}$/");

/* Alternative */

define('RE_HEURE', "/^([01][0-9]|2[0-3])[0-5][0-9][0-5][0-9]([ap]m)?$/i");

?>
~~~


### Exercice 6. 

``define('RE_ENTETE', "/^([A-Z][A-Za-z]*(?:-[A-Z][A-Za-z]+)?):\s+(.*?)\s*$/");``