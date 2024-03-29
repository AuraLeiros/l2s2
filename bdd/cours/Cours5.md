# Cours 5

Aura Leirós García
O povo é quem mais ordea!

25 Marzo 2024

## Complex Requests 

### Cartesian Product

As we can remember, the cartesian product is a mathematical concept is a multiplication of sets $A \cdot B$ that returns a set of all the ordered tuples  $(a, b)$ where $a \in A$ and $b \in B$, of course these is not limited to only two sets.

In SQL this concept helps us to bring together rows from 2+ tables based on a related column between them.

The reason why we care about this is because usually we will need to draw from more than one table, then we will use a `FROM tab1, tab2, ...` and the resulting operation it will be called a join! That result starts by forming the cartesian products of the tables and is followed by the application of the remaining clauses (WHERE, etc.), which reduces or facilitates the search.

### Joins

Join conditions are used to match up related tuples from the two tables (usually using the common row that we talked about before), these allows to select the tuples in the cartesian product table that actually makes sense.

1. A tuple of T1 will appear in the result of the join if it joins at least with one tuple of T2.

2. Usually, the join allows to 'pass' through the association of a E/A scheme.

3. If there's an attribute with the same name in the two tables we need to aliase it (it's a good practice to do it always tho).

4. If there are K tables in the FROM, there will be usually k-1 join conditions.

### Particular case of joins: self join

A self join is the method of joining a table with itself and it's useful in cases where we want to select informations that are in the same table. Noawadays it's not very used.

To do this we need to respect some conditions:

1. Mandatory aliasing of tables at the FROM.

2. All the atributes must be prefixed with the alias.

Also it's a good advice to make attention when making the join statement.

## Nested Querys

Another way of doing complex requests are doing nested querys in the WHERE clause with the following schema:

~~~
SELECT ...
FROM ...
WHERE [OPERAND] OPERATOR (
    SELECT ...
    FROM ...
    WHERE ...
);
~~~

We have three possible nestings

1. $(A_1, ... , A_n)$ [NOT] IN `<sub-query>` -> set inclusion
2. [NOT] EXISTS <sub-query> -> existence or inexistence

This returns TRUE or FALSE and for every row in the outer query evaluates the inner request, if >= 1 rows are returned by the inner request then it's true and adds the current row to the result.

It's usually used a SELECT 1 inside the inner query so it's more efficient. 


3. $(A_1, ... , A_n)$ `<comp> [ALL | ANY] <sub-query>` -> comparing with a quantifier, ANY by default

Conditions:

1. The internal query it's made for the first time and saved into the RAM (or the HDD if it's big)

2. The inner query does not use the tables of the external request (but can reference them).

3. The n-uplets returned by the internal request must be of the same format that the ones in the where (same number and type of attributes)

4. The SELECT of the external requests only returns attributes that belong to the tables in the (external) FROM.





# End of this lecture!

## Exercices done through the lecture.

Considering the following schema: 

Emp (Eno, Ename, Title, City) Project(Pno, Pname, Budget, City)
Pay(Title, Salary) Works(Eno, Pno, Resp, Dur)

### Page 8.

1. Names and salary of employees?

~~~
SELECT Emp.Ename, Pay.Salary
FROM Emp, Pay
WHERE (Emp.Title = Pay.Title)
~~~

2. Names and titles of employees that works a project in Paris?

~~~
SELECT Emp.Ename, Emp.Title
FROM Emp, Projects, Works
WHERE (Emp.Eno = Works.Eno) AND (Works.Pno = Project.Pno) AND (Project.City = 'Paris');
~~~

### Page 9.

1. Numbers and names of the projects where the employee number 10 has worked

~~~
SELECT p.Pno, p.Pname
FROM Project AS p, Emp, Works AS w
WHERE (Emp.Eno = 10) AND (Emp.Eno = w.Eno) AND (w.Pno = p.Pno)
~~~

2. Number and title of employees that are working in projects at Paris?

~~~
SELECT Emp.Eno, Emp.Title
FROM Project AS p, Emp, Works AS w
WHERE (p.City = 'Paris') AND (Emp.Eno = w.Eno) AND (w.Pno = p.Pno);
~~~

### Page 17.

1. Names of the employees that lives in cities where there are projects with a budget of less than 50

~~~
SELECT Emp.Ename
FROM Emp
WHERE Emp.City IN (
    SELECT p.City
    FROM Project AS p
    WHERE(p.Budget < 50)
);
~~~

For the NOT suffit of adding it before the IN.


### Missing exercises, TBD

