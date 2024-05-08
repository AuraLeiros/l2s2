# Cours 4

Aura Leirós García\
Os bos e xenerosos a nosa voz entenden.

24 Marzo 2024


## SQL Introduction

SQL is an interrogation language for relational databases developed by IBM in the '80s. Is considered a declarative language based in the relational calculus of tuples.

The roles of SQL are to define and modify the schema of a database, manipulate the data and interrogate the data.

### SQL Simplified Syntaxis

~~~
SELECT column1, column2, ...
FROM MyTable
[WHERE condition];
~~~

This code is an example of a basic SQL snippet that returns the specified columns from the table 'MyTable' the third line is an optional argument. 

Remember that terms column and attribute are almost always used interchangeably, where column makes reference to the more physical concept and attribute more to the conceptual model.

1. SQL allows us to create 'variables' with the name of the columns and the tables, we can do it with or without the `AS` keyword, there's not practical difference but it's recommended for clarity purpouses. This is called 'Column aliasing' and 'Table aliasing'.

~~~
/* Column Aliasing */

SELECT column1 AS c1, column2 AS c2
FROM mytable

/* Table Aliasing */

SELECT v1.column1, v2.column2
FROM A AS v1, S AS v2
~~~

2. We can as well prefix a column with the name of the table like `SELECT myTable.column1`

3. To select all the columns in a table, we use `Select *`

4. We can use the `DISTINCT` keyword to get all the values in a column without repeated elements

~~~
SELECT DISTINCT col1
From myTable
~~~

5. SQL allows to do arithmetic operations with the attributes in the `SELECT` for example `SELECT Col1-Col2` or `SELECT Col1 * 2`

6. We have the possibility of returning a string using `''`, the concatenator operator is usually `||` but can be `+` depending of the DB.

~~~
SELECT 'First name: ' || FirstName
FROM myTable
~~~

## Where: The Predicates

This section is dedicated to explain the use of the third element in our SQL request, the optional WHERE.

### Simple predicates

The simple predicates are made using of mathematical connectors, Expression1 $\Theta$ Expresssion2 where $\Theta \in \{\lt, \le, =, \neq, \gt, \ge \}$

Some examples are `R.Name = 'J. Doe'`, `(S.Age + 30) >= 90` or `R.A = S.B`

### Composed predicates

Composed predicates are formed by combining simple predicates using logical connectors, namely AND, OR, and NOT.

### Specific operators.

1. `IN` to filter concrete attributes, it's a shorthand for multiple OR operators.

~~~
SELECT * 
FROM Customes
WHERE Country in (Mexico, Argentina, Portugal);
~~~

2. `BETWEEN`to select elements in a range.

~~~
SELECT *
FROM Products
WHERE Price BETWEEN 10 AND 20;
~~~

3. `LIKE` is used to search an specific pattern in a column, using `%` for any string (included the empty string) and `_` for only one char.

~~~
/* Customers that start with the letter 'a' */ 

SELECT *
FROM Customers
WHERE CustomerName LIKE 'a%'; 
~~~

### NULL Values

The value of certain variables can be unknown or nonsensical. In these cases, we refer to these values as NULL.

NULL it's not a value but an absence of value, can't be operated (in case of doing operations the result is going to be NULL) or compared (in which case the result is going to be UNKNOWN)

### ORDER BY

In the `ORDER BY` clause we can specify:

1. Names of columns
2. Expressions with the names of columns.
3. Numbers of positions in the SELECT clause.

We can specify the sorting order as either `ASC` (ascending, with NULL values at the end) or `DESC` (descending, with NULL values at the beginning) after the column name. This allows us to define multiple sorting criteria, if there are elements that are equal according to the first sorting condition, they will be further sorted based on the second condition, and so forth.


## Set Operators

We can do set operations in the SELECT statement, for that we have three avaliable operators, UNION, INTERSECT and MINUS.

To be able to do the operations we have to respect two rules, the number and order of columns must be the same and the data types must be compatibles (i.e. same schema in the two requests).

Remark: The use of this operators deletes all the duplicates, if we want to avoid this we can use the keyword `ALL` after the operator.

## Time

### Functions to parse the date

We have functions for a lot of tasks, the problem is that they're different from a DBMS to other, we're going to use H2

1. PARSEDATETIME('string', 'format')

The separators are chosen by the user and the format will use the following syntax (attention to the upper/lower case!!)

- y: year
- M: month
- d: day

- H: hour
- m: minute
- s: second

2. DATE 'string'

Uses the format of the system by default.

3. FORMATDATETIME('date', 'format')

Returns the pased date in the specified format, for example FORMATDATETIME(CURRENT_DATE, 'dd-MM-yyyy')

### Get actual date

We can either use the EXTRACT (composant FROM date) or the following functions (more easy):

(Today's date is March 24th 2024, Sunday)

1. YEAR(current_date) -> 2024
2. MONTH(current_date) -> 3
3. DAY_OF_MONTH(current_date) -> 24
4. DAY_OF_WEEK(current_date) -> 1
5. DAYNAME(current_date) -> Sunday
6. WEEK(current_date) -> (no. of the current week of the year)

Remember that this date follows LIBERTY AND DEMOCRACY conventions (pun intended, is U.S. Time Notation) so the week starts in Sunday huh.

### Manipulation of the date

1. Add a number of days/weeks/months/years

`DATEADD(datetimeField, addIntLong, dateAndTime)`

2. Difference between two dates

`DATEDIFF(datetimeField, endDate, startDate)`

The ``datetimeField`` is the parameter to specify the units (days, years, etc.), if the `endDate` is before the `startDate` the result will be a negative number.

# End of this cours!

## Exercices done through the lecture.

Considering the following database schema:

~~~
Emp (Eno, Ename, Title, City)
Project(Pno, Pname, Budget, City)
Pay(Title, Salary)
Works(Eno, Pno, Resp, Dur)
~~~

### Page 8.

1. The name of all employees.

~~~
SELECT Ename
FROM Emp
~~~

2. The name and budget of all the projects.

~~~
SELECT Pname, Budget
FROM Project
~~~

### Page 10.

1. All the informations about employees.

~~~
SELECT *
FROM Emp
~~~

2. All the cities where employees live.

~~~
SELECT City
FROM Emp
~~~

3. The set of cities where employees live.

The difference here is that they ask us for the set, so we can't have repeated elements, therefore we need to use the DISTINCT keyword.

~~~
SELECT DISTINCT City
FROM Emp
~~~

### Page 12.

1. Monthly salary for every title (considering that `Salary` is for one year)

~~~
SELECT Emp.Title, (Emp.Salary / 12)
FROM Emp
~~~

2. All the cities where employes lives.

~~~
SELECT Emp.City
FROM Emp
~~~

3. Name and budget of the projects.

~~~
SELECT Project.Pname, Project.Budget
FROM Project
~~~

### Page 16.

1. Professions that earn more than €50,000 per year?

~~~
SELECT Pay.Title
FROM Pay
WHERE (Pay.Salary >= 50000)
~~~

2. Numbers of project managers for over 17 months?

~~~
/* We don't know how Resp is structurated nor if Dur is in months, so we're assuming */

SELECT Works.Eno
FROM Works
WHERE (Works.Resp = 'MANAGER') AND (Works.Dur > 17) 
~~~

### Page 18.

1. Name of the projects in Paris, Lyon or Nantes?

~~~
SELECT Project.Pname
FROM Project
WHERE Project.City IN ('Paris', 'Lyon', 'Nantes');
~~~

To do it without the IN we need to use three ORs with Project.City = 'NameOfTheCity'.

2. Name of the projects with a budget ranging from 5M to 10M of EUR?

~~~
SELECT Project.Pname
FROM Project
WHERE Project.Budget BETWEEN 50000000 AND 10000000;
~~~

To do it without the BETWEEN we need to use (Project.Budget >= 50000000) AND (Project.Budget <= 10000000)

### Page 19.

1. Name of the employees starting with 'C'?

~~~
SELECT Emp.Ename
FROM Emp
WHERE Emp.Ename LIKE 'C%'
~~~

2. Names of the employees whose second digit is a 5?

~~~
SELECT Emp.Ename
FROM Emp
WHERE Emp.Eno LIKE '_5%';
~~~

3. Name of the employees that live in a city with two names

~~~
SELECT Emp.Ename
FROM Emp
WHERE Emp.City LIKE '% %' OR Emp.City LIKE '%-%'
~~~

### Page 22.

1. Names, budgets, and cities of projects with budgets greater than 250,000 euros, ordering the result by descending order of budget and then by name in ascending alphanumeric order.

~~~
SELECT prj.Pname, prj.Budget, prj.City
FROM Project AS prj
WHERE (prj.Budget > 250000)
ORDER BY prj.Budget DESC, prj.Pname ASC;
~~~ 

### Page 24.

1. Names, total budgets (adding 20% VAT), and cities of the projects, ordering the result by descending order of total budget (including VAT).

~~~
SELECT prj.Pname, (prj.Budget * 1.20) AS budgetVAT, prj.City
FROM Projects as prj
ORDER BY budgetVAT DESC;
~~~

2. Names, budgets and cities of the projects sorting the result by decreasing order of budget TTC.

~~~
SELECT prj.Pname, Prj.Budget, prj.City
FROM Projects as prj
ORDER BY (prj.Budget * 1.20) DESC;
~~~

### Page 27. (Union)

1. Names of the cities where employees live or where projects are located?

`SELECT Emp.City FROM Emp UNION SELECT prj.City FROM Project AS prj`

### Page 28. (Intersection)

1. Names of the cities where employees live and where projects are located?

`SELECT Emp.City FROM Emp INTERSECT SELECT prj.City FROM Project AS prj`

### Page 29. (Minus)

2. Names of the cities where employees live but where no project is located?

`SELECT Emp.City FROM Emp MINUS SELECT prj.City FROM Project AS prj`