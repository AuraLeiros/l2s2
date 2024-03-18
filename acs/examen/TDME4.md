# TD and TME 4 - POP

Aura Leirós García\
Feito con <3 em Galiza e Portugal

## Used functions ! 

#### TD

1. `requeter_en_pop($sock, $req)` returns the answer of the server, if error, false.

2. `ouvrir_session_pop ($server, $user, $pass, $port=110)` opens a POP session and returns the socket.

3. `fermer_session_pop($sock)` Closes the session without returning anything.

4. `lire_message_pop($sock)` reads a message sent by the POP server.

5. `function lire_entetes ($sock)` this function reads all the headers of a POP answer and stores it in an array.

6. `choisir_message_pop($sock, $criteres)` this function selects all the messages that satisfy given criteria.

7. `presenter_message_pop($sock, $criteres)` Displays an HTML web page with the messages in the socket that satisfy the given criteria.

#### TP

1. `http_args ($serveur='', $entetes=array(), $version='')` this function returns the start of an HTTP request.

2. REGEX `RE_HTTP_STATUS` that matches the HTTP version no. and the return code.

3. `requeter_en_php($url, $req='GET', $version='1.1', $entetes=array())`

## TD

### Exercice 1. requeter_en_pop.php

This function sends a request to a POP server and reads the answer. 

~~~
<?php
function requeter_en_pop($sock, $req) {
    if (!fputs($sock, trim($req) . "\r\n")) return false;
    $reponse = fgets($sock);
    return preg_match("@^\+OK(.*)@",$reponse, $m) ? $m[1] : false;
}
?>
~~~

### Exercice 2. ouvrir_session_pop.php

Opens a POP session sending the USER and the PASS and returns the open socket.

~~~
function ouvrir_session_pop ($server, $user, $pass, $port=110)
{
    $sock = @fsockopen($server, $port, $errno, $errstr, 5);
    if ($sock == false){
        return "Erreur de connexion au serveur POP [$errno] : $errstr\n";
    } else {
        /// Chercher le message de bienvenue du serveur
        $reponse = fgets($sock);
        /// Envoi de la requete USER et contrôle
        if (requeter_en_pop($sock,"USER $user") === false)
            return "USER $user inconnu\n";
        /// Envoi de la requete PASS et contrôle
        if (requeter_en_pop($sock,"PASS $pass") === false)
            return "PASS incorrect\n";
        /// L'utilisateur est reconnu
        /// on retourne le descripteur
        return $sock;
    }
}
?>
~~~


### Exercice 3. fermer_session_pop.php

This closes the connection with the server sending a QUIT request and frees the socket.

~~~
function fermer_session_pop($sock){
  requeter_en_pop($sock, "QUIT");
  @fclose($sock);
}
?> 
~~~

### Exercice 4. lire_message_pop.php

This function sends the body of a message sended by the POP server

~~~
 <?php
function lire_message_pop($sock){
    $message = '';
    /// ici rtrim serait plus juste
    while (trim($ligne = fgets($sock)) != '.') {
        $message .= $ligne;
    }
    return $message;
}
?>
~~~


### Exercice 5. lire_entetes.php

This function returns an array with all the headers in the POP server answer.

~~~
<?php
include __DIR__ . '/../../TD/2/re_entete.php';

function lire_entetes ($sock){
  $cle = '';
  $entetes = array();
  while (trim($ligne = fgets($sock))) {
      if (preg_match(RE_ENTETE, $ligne, $r)){
          $cle = $r[1];
          if (!isset($entetes[$cle])){
              $entetes[$cle] = array($r[2]);
          } else {
              $entetes[$cle][] = $r[2];
          }              
      } else {
          $entetes[$cle][count($entetes[$cle])-1] .= $ligne;
      }
  }
  return $entetes;
}
?>
~~~
### Exercice 6. choisir_message_pop.php

This function recovers in an array all the messages in a socket that satisfies having a determinated header.

~~~
<?php
include 'requeter_en_pop.php';
include 'lire_entetes.php';
include 'lire_message_pop.php';

function choisir_message_pop($sock, $criteres){
    $n = intval(requeter_en_pop($sock, "STAT"));
    $res = array();
    for (;$n;--$n) {
        requeter_en_pop($sock,"RETR $n");
        $entetes = lire_entetes($sock);
        $message = lire_message_pop($sock);
        $ok = true;
        foreach ($criteres as $nom => $val) {
            if (!isset($entetes[$nom]) OR ($entetes[$nom][0] != $val)) {
                $ok = false;
                break;
            }
        }
        if ($ok) {
            $res[] = array($n, $entetes, $message);
        }
    }
    return $res;
}
?>
~~~

### Exercice 7. presenter_message_pop.php

This makes a webpage that displays all the messages filtered with the last functions

~~~
<?php
include '../../TM/2/debut_html.php';
include '../3/specialchars_en_table.php';
include 'choisir_message_pop.php';
include 'ouvrir_session_pop.php';
include 'fermer_session_pop.php';

function presenter_message_pop ($sock, $criteres)
{
    $rep = choisir_message_pop($sock, $criteres);
    $res = '';
    foreach ($rep as list($n, $entetes, $corps))
    {
        $res .= "<fieldset>"
             . specialchars_en_table($entetes, "Mail $n")
             . "<div>"
             . preg_replace("@\n@s", "<br />\n", htmlspecialchars($corps))
             . "</div></fieldset>\n";
    }
    return debut_html("Mails")
        . "<body>"
        . tableau_en_table($criteres, "criteres")
        . "<div>" . count($rep) . " messages trouvés " . "</div>"
        . $res
        . "</body></html>"; 
  }

/// Test
$sock = ouvrir_session_pop('127.0.0.1', 'moi', '123456789', 2110);
if (is_string($sock))
    echo $sock;
else {
    echo presenter_message_pop($sock,
            array("From" => "maman@ici.fr", "Subject" => "Noel"));
    fermer_session_pop($sock);
}
//*/
?>
~~~

## TP

### Exercice 1. telnet.txt

~~~
Le document renvoyé est de type HTML. 
C'est le même que celui renvoyé lorsqu'on écrit
http://127.0.0.1
dans la barre de navigation.

Le code de retour est 301, indiquant une redirection. 
Celle-ci est indiquée dans l'en-tête Location.
Elle est due au fait que l'URL donnée ne se termine pas par /
mais indique pourtant  un répertoire, non un fichier.

Lorsqu'on demande l'URL indiquée par l'en-tête Location
on obtient la liste des entrées de son répertoire public_html.
Le navigateur a donc immédiatement opéré la redirection.
~~~

### Exercice 2. http_args.php

This function returns the headers of an HTTP request.

~~~
function http_args ($serveur='', $entetes=array(), $version=''){
    if ($version < 1)
        return "\r\n";
    if ($version > 1) $entetes[]= "Host: $serveur";
    return "HTTP/$version\r\n" . join("\r\n", $entetes) . "\r\n\r\n";
}
/*/
echo http_args('localhost', array('Content-Type: image/png'), 1.1);
//*/
?>
~~~


### Exercice 3. re_http_status.php

RE_HTTP_STATUS matchs the HTTP version number and the return code.

~~~
define('RE_HTTP_STATUS', '@^(?:HTTP/(\S*)\s+)?(\d+)@');
~~~

### Exercice 4.

~~~
<?php
include '../../TD/4/lire_entetes.php';
include __DIR__ . '/../../TM/2/re_url.php';
include 're_http_status.php';
include 'http_args.php';
       
function requeter_en_http ($url, $req='GET', $version='1.1', $entetes=array())
{
    if (!preg_match(RE_URL, $url, $r) OR (!$r[1]))
        return array(400, array(), "Mauvaise URL: $url");
    list($tout, $schema, $serveur, $port, $ressource,) = $r;
    if (!$port) $port = 80;
    $sock = fsockopen($serveur,$port);
    if (!$sock)
        return array(500 , array(), "$serveur:$port injoignable");
    else {
        $args = http_args($serveur, $entetes, $version);
        if (!fputs($sock, "$req $url $args"))
            return array(500 , array(), "$serveur:$port injoignable");
        $rep = fgets($sock);
        $entetes = (preg_match(RE_HTTP_STATUS, $rep, $m) AND $m[1] >= 1)
                 ? lire_entetes($sock) : array();
        $page='';
        while ( !feof($sock) ) $page .= fgets($sock);
        return array(isset($m) ? $m[2] : 200, $entetes, $page);
    }
}
~~~

### Exercice 5. form_unique_input.php

~~~
<?php
include '../../TM/2/debut_html.php';
include '../../TD/3/html_form.php';
include '../../TD/3/specialchars_en_table.php';
include 'requeter_en_http.php';
$titre = "Visualisation des en-têtes";
if (!isset( $_GET['url'])) {
    $body = "<label for='url'>URL</label> <input id='url' name='url' size='99'/>";
    $body = html_form($body);
} else {
    list($status, $entetes,) = requeter_en_http($_GET['url'], 'HEAD', '1.0');
    $t = htmlspecialchars($_GET['url']) . " status $status";
    $body = specialchars_en_table($entetes, $t);
}
echo debut_html($titre), "<body>$body</body></html>\n";
?>
~~~
