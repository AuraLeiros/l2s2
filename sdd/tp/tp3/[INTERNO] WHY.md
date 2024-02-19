En el main vamos a utilizar fgets en vez de scanf porque fgets permite introducir en parámetro el tamanho por lo tanto es inmune a fallos

Ex1.3

Dnas la function enregistrer_biblio on a deux implementations possibles celui proposé qui est plus longue ou une que seulement itere through et fais un fprintf, malgre que notre application soit pas avec des donnes tres largues on a choisi cette implmenetiton car ca nous permet d'avoir une gestion propre de la memoire et des erreurs et la diference dans la complexite c'est negligeable


Ex1.6 

ultimo exercicio, imos asumir de que dous libros non poden ter o mesmo número de enregistrement



cambiados los return por exit, "handed gracefully"


la fonction 2.2 peut avoir des collisions, characters non suportees (asume ascii, etc)

A cambiar no entreesortieH e no outro é que son do tipo size_t e polo tanto non poden ser -1