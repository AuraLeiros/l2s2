### TD4 ACS

Ex 1.1
~~~
function requeter_en_pop($sock, $s){
    if( !fputs($sock, trim($s) . "\r\n")){
        return false
    }
    $r=fgets($sock)

    return preg_match('/^+ok(.*)/', $r, $n)?$n[1]:false;
}
~~~

Quand ça va pas, ça marche pas, il faut absolument controler que fputs repond quelque chose et la reponse commence par +ok quelque chose

Ex.1.2

~~~
function ouvrir_session_pop($add, $id, $password, $port=110){
    $socket = fsockopen($add, $port, $err_num, $err_mess, 5);

    if (!$socket){
        return $err_mess
    }

    $send_user = requeter_en_pop($socket, "USER");
    $send_pass = requeter_en_pop($socket, "PASS");

    if (!($send_user) || (!($send_pass))){
        return "Erreur dans user ou pass";
    } 

    return $socket;
}

SOLUTION:

function ouvrir_session_pop($s, $u, $p, $port=110){

    $sock = fsockopen($s, $port, $e, $n, 5);

    if(!$socket){
        return "Erreur de connexion $e, $n"
    }

    fgets($sock); //lire le bonjour
    if (!requeter_on_pop($sock, "USER $u")){
        return "utilisateur inconnu
    }

    if again avec le pass {
        return "pass incorrect"
    }
    return $sock
}

Mais ou menos o mesmo

~~~

Ex 1.3

Déconnexion

function fermer_session_pop($socket){
    if (!$socket){
        exit();
    }
    requete_en_pop($socket, "QUIT");
    @fclose($socket);
}

function lire_message_pop($socket){
    while((r)trim(fgets($sock) != "." )){
        

    }
}