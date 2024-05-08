# TD4 - BDD

Aura Leirós García
21218034

Friendly reminder that these aren't official solutions.

## Exercice 1.

1. French athletes 

~~~
SELECT *
FROM ATHLETE AS t1
WHERE t1.PAYS = 'France';
~~~

In this case we will match only exact ocurrencies of 'France', in case that we need to put it all in a common format, like for example all in underscore, we can use the `LOWER()` function.

~~~
SELECT *
FROM ATHLETE AS t1
WHERE LOWER(t1.PAYS) = LOWER('France');
~~~

2. DOB of 'Denis TEN'

~~~
SELECT t1.DateNaissance
FROM ATHLETE AS t1
WHERE(LOWER(t1.NOM) = LOWER('TEN')) AND (LOWER(t1.PRENOM) = LOWER('Denis'));
~~~

3. Competitions (Sport, Competition) where Therese JOHAUG won a medal along with the ranking that she got.

Information: To won a medal the rank must be 1, 2 or 3.

~~~
SELECT t1.SPORT, t1.EPREUVE, t1.RANG
FROM RangEpreuve AS t1
WHERE (t1.nomAth = JOHAUG) AND (t1.prenomAth = Therese) AND (t1.rang IN (1, 2, 3));
~~~

We can use as well `BETWEEN 1 AND 3` for the rank.

4. Nationality of the athlets Kamil STOCH and Suk-Hee SHIM.

~~~
(SELECT t1.nom, t1.prenom, t1.pays
FROM ATHLETE AS t1
WHERE (t1.nom = 'SHIM') AND (t1.prenom = 'Suk-Hee'))
UNION
(SELECT t1.nom, t1.prenom, t1.pays
FROM ATHLETE AS t1
WHERE (t1.nom = 'STOCH') AND (t1.prenom = 'Kamil'));
~~~

5. All the sports in the olympic games.

~~~
SELECT DISTINCT t1.sport
FROM RangEpreuve AS t1
~~~

6. The name of the athletes from Scandinavia (In french: Danemark, Finlande, Norvège, Suède, Islande) ordered by last name then by first name.

~~~
SELECT t1.nom
FROM ATHLETE AS t1
WHERE (t1.pays IN ('Danemark', 'Finlande', 'Norvège', 'Suède', 'Islande'))
ORDER BY t1.nom, t1.prenom;
~~~

7. The name of sports that have the string 'ski'

In this case we need to use the LIKE operator and the lower to do a case-insensitive search.

~~~
SELECT t1.sport
FROM RangEpreuve AS t1
WHERE (LOWER(t1.sport) LIKE '%ski%');
~~~

8. The athletes (last name, first name) whose DOB is not provided.

~~~
SELECT t1.nom, t1.prenom
FROM ATHLETE AS t1
WHERE t1.DateNaissance IS NULL;
~~~

9. Athletes that participated in the '10km' competition of 'Ski de fond' without being disqualified (rang unknown), ordered by rank.

As it's not specified, we're going to take as 'Athlete' all the columns of the table ATHLETE, this means that we have to use methods outside the scope of this TD (in this case we can use either nested requests or JOIN syntaxis)

À FAIRE

10. Events (sport, event, and category) that took place after February 21, 2014.

As it's not clear from the dateDebut column that all the elements follow the same notation, we could do an OR just in case, but this time we're leaving it like this for the sake of simplification. 

~~~
SELECT t1.sport, t1.epreuve, t1.categorie
FROM RangEpreuve AS t1
WHERE PARSEDATETIME(t1.dateFin, 'dd-MM-yyyy') > PARSEDATETIME('21-02-2024', 'dd-MM-yyyy');
~~~

11. The events (sport, event, and category) that lasted between 2 and 4 days, along with their exact duration.

~~~
SELECT t1.sport, t1.epreuve, t1.categorie, DATEDIFF('day', t1.dateFin, t1.dateDebut) AS duration
FROM RangEpreuve AS t1
WHERE DATEDIFF('day', t1.dateFin, t1.dateDebut) BETWEEN 2 AND 4;
~~~

12. Events (sport, event and category) where the final was in a weekend.

This is a bit hard to understand at first, but SQL automatically calculates the day of the week for a given, complete date with the function DAYOFWEEK('DATE'). 7 is saturday and 1 is sunday.

~~~
SELECT t1.sport, t1.epreuve, t1.category
FROM RangEpreuve AS t1
WHERE DAYOFWEEK(t1.dateFin) IN (1, 7);
~~~

13. Athletes (last, first name) that are women and french.

~~~
SELECT t1.nom, t1.prenom
FROM ATHLETE AS t1
WHERE (t1.nom, t1.prenom) IN (
        SELECT t2.nomAth, t2.prenomAth
        FROM RangEpreuve AS t2
        WHERE t2.categorie = 'Femmes'
    ) AND (t1.pays = 'France');
~~~

14. Athletes (last, first name) that have today less than 25 years and won a medal

Remember: medal = rank BETWEEN 1 and 3.

This exercise depends of the date of execution.

~~~
SELECT t1.nom, t1.prenom
FROM ATHLETE AS t1
WHERE (t1.nom, t1.prenom) IN (
        SELECT t2.nomAth, t2.prenomAth
        FROM RangeEpreuve AS t2
        WHERE (t2.rank IS NOT NULL) AND (t2.rank BETWEEN 1 AND 3)
    ) AND (DATEDIFF('year', CURRENT_DATE, t1.DateNaissance) < 25);
~~~

15. Athletes (last, first name) that had their birthday the day of the end of the event where they were participating.

~~~
SELECT t1.nom, t1.prenom
FROM ATHLETE AS t1, EpreuveRang AS t2
WHERE (t1.nom = t2.nomAth) AND (t1.prenom = t2.prenomAth) AND (MONTH(t1.dateNaissance) = MONTH(t2.dateFin)) AND (DAY(t1.dateNaissance) = DAY(t2.dateFin));
~~~

16. French athletes (last, first name) that won a medal

SELECT t1.nom, t1.prenom
FROM ATHLETE as t1
WHERE (t1.nom, t1.prenom) IN (
        SELECT (t2.nomAth, prenomAth)
        FROM RangEpreuves as t2
        WHERE (t2.rank IS NOT NULL) AND (t2.rank BETWEEN 1 AND 3)
    ) AND (LOWER(t1.pays) = LOWER('France'));

17. Sports that does not have feminine competitions

~~~
SELECT t1.sport
FROM RangEpreuves as t1
MINUS
SELECT t2.sport
FROM RangEpreuves as t2
WHERE t2.category='Femmes'
~~~

Correct, it's possible to use also a NOT EXISTS clause but out of the scope of this TD

# End of this TD!