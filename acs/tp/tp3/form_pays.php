<?php
    include "../debut_html.php"
    include "../tableau_en_select.php"

    function form_pays($tab){
        $html = debut_html("pays");
        $html .= '<form action="form_ville.php" method="POST">'
        $html .= '<fieldset>' . tableau_en_select($tab, "pays") . '</fieldset>'
        $html .= '<input type="submit"></input>'
    }
?>