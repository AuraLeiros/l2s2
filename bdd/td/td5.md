# TD5 - BDD

This TD it's mainly to put in use the adquired knowledge about the JOIN, the lecture uses an old syntaxis (doing the JOIN in the WHERE clause) but we're going to use the dedicated JOIN clause.



1. French athletes (country name = 'France')

~~~
SELECT *
FROM Athlete AS a
JOIN Pays as p ON (a.codePays = p.codePays)
WHERE (p.nomP = 'France');
~~~

2. Events (sport, name of the event, category) ordered by sport, then by the name of the event in the inverse order of the dictionary.

~~~
SELECT t1.nomSp, t2.nomEp, t2.categorie
FROM Sport AS t1
JOIN Epreuve AS t2 ON (t1.sid = t2.sid)
ORDER BY t1.nomSp DESC, t2.nomEp DESC;
~~~

Note: I'm not 100% sure if I did correctly the part about the dictionary.

3. Athletes that participated in the french team.

~~~
SELECT *
FROM Athlete AS a
JOIN AthleteEquipe AS ae ON a.AID = ae.AID
JOIN Equipe as e ON ae.EQID = e.EQID
WHERE (e.codePays = 'FRA'); 
~~~

4. Events (sport, event, category) where teams participate

~~~
SELECT s.nomSp, e.nomEp, e.categorie
FROM Epreuve AS e
JOIN Sport AS s ON (s.SID = e.SID)
JOIN RangEquipe AS re ON (re.EPID = e.EPID)  
~~~

5. The country that won, in team, the gold medal in the 'Femmes' category of the event 'relais 4x6km' of the sport 'Biathlon'

~~~
SELECT p.nomP
FROM Pays AS p
JOIN RangEquipe AS re ON re.codePays = p.codePays
JOIN Epreuve AS ep ON ep.EPID = re.EPID
JOIN Sport AS sp ON ep.SID = sp.SID
WHERE re.rang = 1 AND ep.nomEp = 'relais 4x6km' AND ep.categorie = 'Femmes' AND sp.nomSp = 'Biathlon';
~~~

6. Athletes that participated in at least one individual event and at least team event.

~~~
todo
~~~

7. Homonymes (equal last names in 2+ athletes)

~~~
SELECT DISTINCT *
FROM Athlete AS a1
JOIN Athlete AS a2 ON a1.nomAth = a2.nomAth
WHERE (a1.AID != a2.AID);
~~~

8. Athletes that participated in at least two individual events.

~~~
SELECT DISTINCT a1.*
FROM Athlete AS a1
JOIN RangIndividuel AS r1 ON a1.AID = r1.AID
JOIN RangIndividuel AS r2 on a1.AID = r2.AID AND (r1.AID != r2.AID)
~~~

9.  Athletes that won a medal in an individual event and disqualified in another.

~~~
SELECT a1.*
FROM Athlete AS a1
JOIN RangIndividuel AS r1 ON (a1.aid = r1.aid)
JOIN RangIndividuel AS r2 ON (a1.aid = r2.aid) AND (r1.epid != r2.epid)
WHERE (r1.rang BETWEEN 1 AND 3) AND (r2.rang IS NULL) AND (r2.epid IS NOT NULL);
~~~


10. Athletes that won at least a medal in an individual event

~~~
SELECT DISTINCT a1.*
FROM Athlete AS a1
JOIN RangIndividuel AS r1 ON (a1.aid = r1.aid)
WHERE (r1.rang BETWEEN 1 AND 3)
~~~

11. Names of countries that only have one team

~~~
todo
~~~

### 12

~~~
todo
~~~
