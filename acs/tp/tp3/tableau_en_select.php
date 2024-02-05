<?php

    function tableau_en_select($tab, $libelle, $predef=null){
        $html = '<label>' . htmlspecialchars($libelle, ENT_QUOTES) . '/label>'
        $html .= '<select name=' . htmlspecialchars($libelle, ENT_QUOTES) . ' id=' . htmlspecialchars($libelle, ENT_QUOTES) . '>';

        foreach($tab as $continent => $countries){
            $html .= '<optgroup label=' . htmlspecialchars($continent, ENT_QUOTES) . '>';

            foreach($countries as $country => $city){
                $isPredef = ($country == $predef) ? "selected" : "";
                $html .= '<option value="' . htmlspecialchars($country) . '" label="' . htmlspecialchars($country, ENT_QUOTES) . '" ' . $isPredef . '></option>';
            }

            $html .= '</optgroup>';
        }
        $html .= '</select>';

        return $html;
    }

?>