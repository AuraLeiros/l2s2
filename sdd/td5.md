### Exercice 1.

#### 1.1

Un arbre est une structure de données permettant de manipuler un ensemble de elements quelconque. Il est aracterisé par un element racine, des elements intermediaires et des feuilles. Ces elements sont appeles des noeuds de l'arbre. Un arbre est dit 

- Binaire : si chaque noeud posede au plus 2 fils.
complet si tous les niveaux sauf le dernier sont remplis.
tassé a gauche si les feuilles sont stockées de gauche à droite/

un tas es un ensemble d'elements auxquels sont associes des cles (des entiers en practique) structuré en 1 arbre binarire complet tassé a gauche et tel que tout noeud possede 1 dcle plus grande que cella de son pere

#### 1.2

swap est une fonction qui change la valeur, on doit echanger 

#### 1.3

En supprimant les arbres de plus petit cle on obtient l'abre

            
On met le plus bas element a droite comme racine et on fait un swap pour garantiser la propriete d'ordonne

Le plus petit élément est à la racine. Pour garder la structure de tas. Pour garder la structure de tas, en commence par remplacer le dernier élément du tas (noeud le + a droite du niveau le + bas).

Puis on fait des swaps à partir de la racine (vers le bas) tanta que nécessaire pour retrouver la propiété sur ;es c;és (swap avec le min des fils)

#### 1.4

On peut pas savoir si le dernier niveau va etre rempli, donc, on aura une double inegalité.
h = 1; 2 <= n <= 1+2
h = 2; 4 <= n <= 1+2+4
...
h   ; 2^n <= n <= sum(2^i) depuis i=0 jusqu'à h = 2^(h+1)-1

Une suite geometrique. q c'est le terme.

#### 1.5

L'inverse de l'exercice 1.4,

D'une part 2^h <= n est egal  h * log2(2) <= log2(n) est egal a h <= logs(n)

D'autre part: n <= 2^h+1 -1 equiv n+1 <= 2^h+1 
equiv log2(n+1) <= (h+1)log2(2)
equiv log (n+1) - 1 <= h

on a: log2(n+1) -1 <= h <= log2(n)
on h est un entier

Donc, on peut prendre la partie entiere sup de l'elémenent à gauche, et la parte arriére inf de l'élément à droite
floor_sup(log2(n+1) - 1) <= h <= floor_inf(log2(n));

Nous allons montrer que log2(n) - log2(n+1)+1 < 1


log2(n) - log2(n+1) + 1 < 1 equiv log2(n) - log2(n+1)<0 equiv log2(n/n+1) < 0 equiv n / n-1 (car log es 1) equiv n < n-1

On a donc forcemenet  : floor_sup(log2(n+1)-1) = floor_inf(log2(n)) = h en particulier h = floor_inf(log2(n))

/!\ Suite geomatrique et logaritmes hyper importants pour preuves de complexité et trouver hauteurs.

#### 1.6

O(log2(n)) dans le pire cas (le element a inserer est le plus pétit et donc on doit faire un swap), la meme chose dans le pire de cas dans la supression de l'élément de plus petite clé.

of.

En rajoutant un élément ayant 1 clé + petite que tous les éléments du tas, nous serons obligés de faire le swap d'éléments avant que la nouvelle feuille remplace la racine. Sachant que h = floor_sup(log2(n)) ceci correspond au cout le + éléve par 1 insertion. L'insertión est donc en O(log2(n)). Pour la suprresions des minimum on retrouve la meme complexite car dans lea pire des cas, on devra faire h swaps de la racine voir meme feuille.

### Exo 2.

#### Exo 2.1

#### Exo 2.2

Encore une fois, la hauteur changera selon 

h = log3(n) ou log3(2n-1)

Et non, c'est la meme complexité

En procedant comme dans l'exo précedent, on peut montrer que pour un n donné, la hauteur h vérifie h = floor_inf(log3(2n-1)) (exercise maison : preuve)

Donc, le cout d'insertion est en O(log3(n)).

L'utilisation d'un tas terniaire ne permet donc pas d'ameliorer le cout d'insertion (cas O(log2(n))) = O(log2(n))

#### Exo 2.3

Soit le numéro d'un noeud quelconque

-num (fg) = 3xi-1
num(fn) = 3xi
num(f11) = 3xi+1
num(per) = round(3/i)

round correspond à l'arrondi à l'entier le + proche

Un stockage efficace en memoire d'un tas de n éléments peut se faire avec un tablau, l'arbre étant complet, et les elements tiennent necesairement dans n cases sucessives indices de 1 [à] n (ou de 0 a n-1)
L'arces au noued i est donc inmediat et ne presippose pas de parcourir d'autres noeurds comme ce serait le cas dans une liste chainee les relations entre numeros permettant en autre un acces ainmediat aux noeuds fils ou pere s'ils existent