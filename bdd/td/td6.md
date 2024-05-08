# TD6 - BDD


### 1.

1. Athletes that participated in at least one individual event and at least one team event.

~~~
SELECT DISTINCT a1.*
FROM Athlete AS a1
WHERE a1.AID = ANY (
    SELECT r1.AID
    FROM RangIndividuel AS ri
    WHERE a1.AID = r1.AID 
) AND a1.AID = ANY (
    SELECT ae.AID
    FROM AthletesEquipe AS ae
    JOIN RangEquipe AS re ON ae.EQID = re.EQID
)

TBC
~~~


### 2.

1. Countries with at least one athlete

~~~
SELECT p.nomP
FROM Pays AS p
WHERE EXISTS (
    SELECT 1
    FROM Athlete AS a
    WHERE (a.codePays = p.codePays)
)
~~~

2. Countries with exactly one athlete

~~~
Select p.nomP
FROM Pays AS p
WHERE EXISTS (
    SELECT 1
    FROM Athlete AS a1
    WHERE p.codePays = a1.codePays
) AND NOT EXISTS (
    SELECT 1
    FROM Athlete AS a2
    JOIN a2 ON p.codePays = a2.codePays AND (a1.AID != a2.AID)
)
~~~

### 3.

1. Athletes that were never disqualified at individual events.

~~~
SELECT a1.*
FROM Athletes AS a1
WHERE NOT EXISTS (
    SELECT *
    FROM RangIndividuel AS ri
    WHERE (r1.AID = a1.AID) AND r1.rang IS NULL
);
~~~

2. 