<?php

    include 'destinations.php';

    $saisiePays = htmlspecialchars($_POST['pays'], ENT_QUOTES); 
    $saisieItem = htmlspecialchars($_POST['item'], ENT_QUOTES);
    $ville = trouver_sous_index($destinations, $saisiePays);
    $html = '<head><title>Bon Voyage!</title></head>';

    if (!$ville) {
        header("HTTP/1.1 303");
        header("Location: form_pays.php");
        exit();
    } else if (!(is_numeric($saisieItem))){
        foreach($ville as $x => $y){
            if ($x == $saisieItem){
                $html .='<body>' . $x . ' ' . $y . '</body>';
            }
        }
        echo $html;
    } else {
        $html .= '<body>' . soumission_multiple($ville, $saisieItem);
        $html .= '<input type="hidden" name="pays" value="' . $saisiePays . '"></input></body>';
        echo $html;
    }

    exit();
?>
