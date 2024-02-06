<?php

include("tableau_en_table.php");

function soumission_multiple($tab, $n){

    $idx = (($n >= 1) && ($n <= count($tab))) ? $n : 1;
    $html = "<ul>";
    
    /* First element */
    if ($idx == 1){
        $html .= '<li></li>';
    } else {
        $html .= '<li><input type="submit" value="' . htmlspecialchars($tab[($idx - 1)], ENT_QUOTES) . '"></input></li>';
    }

    /* Second element */
    $ville = cherche_index_n($tab, $n);
    $html .= '<li><input type="submit" value="' . htmlspecialchars($ville, ENT_QUOTES) . '"></li>';

    /* Third element */
    if ($n >= count($tab)) {
        $html .= '<li></li>';
    } else {
        $html .= '<li><input type="submit" value="' . htmlspecialchars($tab[($n + 1)], ENT_QUOTES) . '"></input></li>';
    }
    $html .= '</ul>';

    return $html;
}

?>
