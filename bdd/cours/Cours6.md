# Cours 6 - Nested Queries

Aura Leirós García

As nações são todas mistérios.\
Cada uma é todo o mundo a sós.\
    - Fernando Pessoa

## ALL / ANY

At the 5th lecture we've introduced the concept of nested sub-queries, and more particularly the ALL / ANY that we will now proceed to explore further.

1. WHERE $(A_1, ... , A_n) \Theta$ `[ALL | ANY] <sub-query>`

Where $\Theta \in \{\lt, \le, =, \neq, \gt, \ge \}$, ALL ($\forall$) and ANY ($\exists$).

The condition is true for all the n-uplets / at least one n-uplet of the inner query. This is very powerful and allows us to create an 'enhanced' IN.

1. The inner request is done at first.

2. The n-uplets returned by the inner request must be of the same format that the n-uplet before the ANY/ALL

3. The SELECT of the external requests can only return (and retrieve) attributes that belong to tables specified in the FROM.

## Joins vs Nesting

A join can usually be rewrote with the help of nesting.

1. With IN, ANY or EXISTS if the conditions of the join are equalities.

2. With ANY or EXISTS if at least one is an unequality.

A JOIN can only be rewritten with a nesting query if and only if the attributes that are in the SELECT belong to the tables that we want to put in the sub-query.

The notion of totality (all, no one, never, more than all, less than all, etc.) is a difference of sets, this can't be done only with the join and needs at least a MINUS and joins at the two requests.

We can play with the NOT IN, ALL, NOT EXISTS for thee exclusions, in the case of more than, less than, etc. with an ALL or a NOT EXISTS.