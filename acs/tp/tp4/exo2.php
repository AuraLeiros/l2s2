<?php

function http_args($serverName = " ", $tab = array(), $httpVer = " ") {
    $ans = " ";
    if ($httpVer == " "){
        $httpVer = 0;
    } else {
        $httpVer = (double)$httpVer;
    }

    if ($httpVer < 1) {
        $ans .= "\r\n";
        return $ans;
    } else if ($httpVer == 1.0) {
        $ans .= "HTTP/1.0\r\n";
        $ans .= implode("\r\n", $tab);
        $ans .= "\r\n";
        return $ans;
    } else {
        $ans .= "HTTP/" . (string)$httpVer . "\r\n";
        $ans .= "Host " . $serverName . "\r\n";
        $ans .= implode("\r\n", $tab);
        $ans .= 
        
    }


?>
