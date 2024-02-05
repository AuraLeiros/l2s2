## TD 2

Made by Aura Leirós García\
Galiza Ceive Poder Popular

### Exercice 1

~~~
$Candidats = array('Bob', 'Alice', 'Chris');

echo '<ul>'

foreach($Candidats as $v){
    echo "<li>", $v, "<\li>\n"
}

echo "<\ul>\n"

~~~

OU

~~~
while ($Candidat){
    echo "<li>", array_shift($Candidats), "<\li>\n"
}
~~~

OU

~~~

for ($i=0; $i<count($Candidat); ++$i){
    echo "<li>", $Canadidats[$i], "<\li>\n"
}

~~~



#### 1.3
~~~

$scores = array('Alice' => 130, 'Bob' => 300, 'Chris' => 30);
asort($scores)

foreach($scores as $k => $1){
    echo "<li>", $k, ':', $v, "<\li>\n"
}
~~~

### Exercice 2.

~~~
function tableau_en_table(array $idx, string $str){

    if (!$t) return ";$r=''"
    foreach($t as $k => $v){
        $r = "<tr><td>$k<\td><td>$v<\td><\tr>\n"
    }
    $h = "<tr><th>algo<\th><th>valeur<\th><\tr>"
}
~~~

### Exercice 3

~~~

function tableau_en_liste($data, $type=ul){
    if (!is_array($t)) {t, 
        return "$data"
    } else if (!$data) {
        return "";
    }

    if (count($data)==1) return array_shift($data);


    foreach($data as $k => $v){
        $data[$k]=tableau_en_table($v)
    }

    return "<type><li>"w
}

~~~

### Exercice 4

~~~
define('RE_JOUR', "/^[0-9]{4}[0-1][0-3][0-9]$/")
~~~

### Exercice 5

~~~
define('RE_HEURE', "/^[A-Z][A-Z a-z]*(-[A-Z][A-Z a-z]*)*:\s+(!*)\s$/")
~~~

important les regexp!!!
!*