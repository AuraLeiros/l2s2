## TD 3


### Exo 1.

#### 1.1

It's an association (key, value) where key = fingerprint and value = personal file of the person, a hash table seems like a good alternative.

#### 1.2

The hash function is applicated over the keys and returns the position of the elements in the table. Because of the table is an array of size <= 10^5 the hashing function returns a value MOD 10^5

#### 1.3

If one of the elements is 0 all it's going to be 0 and therefore we're going to fill a lot the 0 case. 

Rappel: The interesting about hashing tables is the possibility of dividing information.

The entered integers are [0,99], all the vectors containing a 0 will be stocked in the same case (case 0)

To lower the percentage of collision we can contournate this porblem adding a unit to every unit of the vector before doing the product which makes.
~~~
int g (x1, x2, ..., xn) {
    (int (x1+1)*(x2+1)... (xn+1)) % 1000
}
~~~

#### 1.4

With the given hashing function all the lines return the same value (a collision). É uma questão trampa pois não existe uma funçao boa pra este problema, we have to treat the collisions (next exercise)

### Exo 2.

La chiffre des unités dans nequel base c'est toujours la base

~~~
            g(f(n)) (hex)       decimal
01  le              E              14
02  cours           8               3
03  appelé          3               ...
04  structures      ...
05  de 
06  données
07  est
08  absolument
09  génial
10  j'adore
11  faire
12  ses
13  TD/TME
~~~

In every base, if we have an operation that is `number % base` we will get the last element at the right.

`n % (b^0) + (n - (n % b^0)) % b^1 + ...`

 #### Exo 2.2

 On rapelle que le probing h(k,i) consiste à inserer d'abord en h(k,0) puis en cas d'échéc en h(k,1) puis h(k,2) ...

 Dans le table suivante 

 - " x->y" se traduit par "x suivi de y dans la liste chaînée.

 -" Cx => Cy" represente l'operation tentative de placement de l'élement en case Cx puis tentarive en case Cy (probing)

premier mot -> cas 14 (E = 14 decimal)
deuxieme mot -> cas 08
troisieme mot- >cas 03
...
sixieme mot -> cas 08 qui n'est pas vide on le place aprés le 02 (liste chainée tel que 02 -> 06)

for the linear probing, we start puting and thn doing hops every time we enconter a filled case.



To respond the question, we consider that in the lineaire 28 and the quadratique 22 (hops)

Pour le probing linéaire, le nombre de tentatives d'insertion moyenne est 28/13 pour le probing quadriatique on a 22/13 du coup quadratique.

complexite d'arbre (log(n))

### Exo 3.

#### 3.1

The first 3 functions are linear.

1. `Identity function`, it's going to return the key
2. `10-times function`, returns 10 times the key
3. `2-times function`, returns 2 times the key
4. `Condition + Recursivity function`

#### 3.2

Le but c'est d'avoir le minimum de collision et que la table soit uniformement rempli.

f1 > f2

f3 2 est un diviseur de 10 donc on va avoir la moitie de cases 

La meilleur choix est f4. En effet, si on utilise f1, la fonction de hachage est f1=x mod 10. Par consequent la fonction ne tient compte que les dernieres chiffres de la lé. ce n'est donc pas une bonne function puisque elle ne donera pas tous les infos de la clé.

La fonction f2 est pire puisqu'aucun chiffre de la clé n'est pas pris en compte (on obtient 0 pour tout le monde)

La foncition f3 n'est pas géniale car elle multiplie les cles par un divisieur de la taille de la table, autrement dit, une case sur 2 de la table de háchage sera inutilise. 

La fonction à utiliser est f4 car celle-ci de par sa multiplication par 8 tient comple de tous les chiffres de la clé.
