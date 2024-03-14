# TD and TME 5 - CACHES

Aura Leirós García\
Feito con <3 em Galiza e Portugal

## Used functions ! 

#### TD
1. `function fournir_page ($r)` sends the equivalent of an HTTP answer.

2. `typer_cache ($headers)` returns the extension to cache.

3. `function limiter_cache ($headers)` returns true if the expiration is in the future or does not have expiration, else otherwise.

4. `memorises 



#### TP
1. 
2. 
3. 
4. 

## TD 

### Exercice 1. fournir_page.php

This exercice simulates being a HTTP server answering with a return code, headers and body.

~~~
<?php
function fournir_page ($r){
    list($status, $entetes, $page) = $r;
    header("HTTP/1.1 $status");
    foreach ($entetes as $nom => $valeurs)
        foreach($valeurs as $valeur)
            header("$nom: $valeur");
    echo $page;
}
?>
~~~

### Exercice 2. typer_cache.php

This exercise uses REGEX to find the extension of the filw within the Content-Type

~~~
define('RE_CONTENT_TYPE', ",/(\w+),");

function typer_cache ($headers)
{
    if (isset($headers['Content-Type'])
    AND preg_match(RE_CONTENT_TYPE, $headers['Content-Type'][0], $m))
      return $m[1];
    return 'html';
}
~~~

### Exercice 3. limiter_cache.php

This function returns true if there's not expiration or it's in the future, else false.

~~~
<?php
/// Si pas d'Expire ou Expire pas dans le futur, retourner True
function limiter_cache ($headers)
{
    if (!isset($headers['Expires'])) return true;
    return (strtotime($headers['Expires'][0]) < time()) ;
}
?>
~~~

### Exercice 4. memoriser_cache.php

Puts the files in the provided directory, true if ok, false if else.

~~~
<?php
function memoriser_cache ($dir, $nom, $entetes, $page)
{
    $f = "$dir/$nom" . ".http";
    $t = file_put_contents($f, serialize($entetes));
    if ($t)
        $f = "$dir/$nom" . "." . typer_cache($entetes);
        $t = file_put_contents($f, $page);
    return $t;
}
?>
~~~

### Exercice 5. trouver_cache.php

This function finds a cache and then checks that it's still unexpired then returns an array with this.

~~~
<?php
function trouver_cache ($dir, $nom)
{
    $f = "$dir/$nom" . '.http';
    if (!is_readable($f))
        return array();
    $h = unserialize(file_get_contents($f));
    if (!$h OR limiter_cache($h))
        return array();
    $f = "$dir/$nom" . '.' . typer_cache($h);
    if (!is_readable($f))
        return array();
    return array(200, $h, file_get_contents($f));
}
?>
~~~

### Exercice 6. utiliser_cache.php

~~~
<?php
include '../../TM/4/requeter_en_http.php';

function utiliser_cache ($url, $dir)
{
    $md5 = md5($url);
    $reponse = trouver_cache($dir, $md5);
    if (!$reponse) {
        $reponse = requeter_en_http($url);
        if (!($reponse[0] == 200)
              AND !limiter_cache($reponse[1])
              AND memoriser_cache($dir, $md5, $reponse[1], $reponse[2]))) {
            $md5 ='';
        }
    }
    fournir_page($reponse);
    return $md5;
}
?>
~~~

### Exercice 7. actualiser_cache.php

~~~
 <?php
function actualiser_cache ($tabCaches, $nom,  $dir, $max)
{
  $tabCaches[$nom] = time();
  if (count($tabCaches) > $max) {
      asort($tabCaches);
      $nom = key($tabCaches);
      $h = $dir . $nom . '.http';
      $t = $dir . $nom . '.' . typer_cache(unserialize(file_get_contents($h)));
      unlink($h);
      unlink($t);
      array_shift($tabCaches);
  }
  return $tabCaches;
}
?>
~~~

### Exerccie 8. cache_url

~~~
<?php
include 'actualiser_cache.php';
include 'fournir_page.php';
include 'limiter_cache.php';
include 'memoriser_cache.php';
include 'trouver_cache.php';
include 'typer_cache.php';
include 'utiliser_cache.php';

/// Constante indiquant le nombre maximum de cache
define('MAX_CACHES', 2);
/// Répertoire des caches
define('DIR_CACHE', '/tmp');
/// Fichier de la table des caches : md5 => date (en secondes depuis le 1/1/1970)
define('FILE_CACHE', '/tmp/caches');

$nom = empty($_GET['url']) ? '' : utiliser_cache($_GET['url'], DIR_CACHE);
if ($nom) {
    $tab = is_readable(FILE_CACHE) ? unserialize(file_get_contents(FILE_CACHE)) : array();
    $tab = actualiser_cache($tab, $nom, DIR_CACHE, MAX_CACHES);
    file_put_contents(FILE_CACHE, serialize($tab));
}
?>
~~~