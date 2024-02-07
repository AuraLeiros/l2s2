<?php

    if ((!(isset($_POST["pays"]))) || (!(isset($_POST["item"])))) {
        header("HTTP/1.1 303");
        header("Location: form_pays.php");
    }

    trouver_sous_index($tab, $pays)





?>
