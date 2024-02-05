<?php
    function trouver_sous_index($tab, $pays){
        return isset($pays, $tab) ? $tab[$pays] : array();
    }
?>