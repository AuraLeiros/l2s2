<?php
    function trouver_sous_index($tab, $pays){
        return isset($tab[$pays]) ? $tab[$pays] : array();
    }
?>