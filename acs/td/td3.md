## TD 3

Made by Aura Leirós García\
Galiza Ceive Poder Popular

### Exercice 1


~~~
fonction specialchars_en_table($tab, $s){
	if (!$tab) return "";
	$r = ""
	$head = "<tr><th>index</th><th>value</th></tr>\n"
	foreach($tab as $k => $v){
		$r .= "<tr><td>htmlspecialchars($k, ENT_QUOTES)</td><td>htmlspecialchars($V, ENT_QUOTES)</td></tr>"
	}
	
	return "<table><caption>htmlspecialchars($s, ENT_QUOTES)</caption> $h $r </table>"
}
~~~

### Exercice 3

~~~
<?php
    if (isset($_POST['jour']) && isset($_POST['url'])){
        specialchar_en_table($_POST, 'saisies')
    } else {
        <label for='jour'>'jour</label>
        <input name='jour'/>
        <label for='url></label>
        <textarea name='url'> </textarea>
    }

    echo html_form($args, 'POST')
?>
~~~

### Exercice 4

~~~
<?php

function saisie_fiable($tab, $str, $exp=""){
    if (!isset($tab[$str])) {
        return 1;
    } else if ($exp && !preg_match($exp, $tab[$str])) {
        return -1;
    }

    return 0;
}

?>
~~~

### Exercice 5

1. controler avec if saisie_fiable
~~~
<?php

    $j=saisiefiable($_POST, 'jour', RE_JOUR);
    $v=saisiefiable($_POST, 'val', RE_URL);

    if (!$j && !$v){
        $corps=specialchar_entable($POST, 'saisies');
    } else {
        if ($j==-1) || ($u==-1) $title='ERREUR ALGO'
        $ji = ($j==1):
        htmlspecialchar($_POST['jour']);
        $ui=($u==1)?:
        htmlspecialchar($_POST['url'])
        $corps= '<label for='jour'></label><textarea nano(nao)='url' id='url>$ui</textarea><input title='sibis'/>
    }
?>
~~~

1. C'est bon d'ajouter balises et faire des changements.
