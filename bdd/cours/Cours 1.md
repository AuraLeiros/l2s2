## Cours 1.

### Introduction: Why a database?

#### DBMS vs File system

The DBMS, also known as Database Management System is a software system used to store, retrieve and run queries on data.

A few of the advantages of this software are...

- Description, contraints and meta-data of data bases.
- Control of the redundancy of the data.
- Control of the integrity, automatization of the maintenance.
- More security of the data

#### 3-Level architecture

1. Views (accesible to users)\
1.1 The type of data that are able to see -> External scheme
2. Logical (accesible to the designer & programmer)\
2.1 What type of data is stocked -> Logical scheme
3. Physical (accesible to the designer & admin)\
3.1 How the data is stocked -> Physical scheme

There's independence between the levels...

- Physical independence: changing the physical scheme does not affect the logical scheme
- Logical independence: changing the logical scheme does not affect the external scheme.

### 1. So, how I build a database?

#### 3-Phases method

The IFI,

Identify --> Our real life needs\
Formalize --> Model our data\
Implant --> Building up our DB, query & updating methods\

I : Informal discussion that leads-up to technical documentation\
F : Translate this needs into links between them (Entity-Association model)\
I : Use machine-oriented languages like SQL

#### Two different models for two different needs

1. Entity-Association model

High-level description of data, defines links between the data.\
Used by the designer and the client

2. Relational model.

Logical representation of data, normally in a sheet setting.\
Used by the designer and the developer.

Therefore, our stepping stone will be learn how to design an Entity-Association model...

### 2. _Mãos à obra!_ How to design a Entity-Association Model

As we indicated before, we're going to divide the information into two different subsections

#### Analysis of our needs

At first we need to have an informal discussion with the involved stakeholders that identifies <u>objects</u> and the <u>links</u> between them, identify the operations and the possible updates that the project may have.

#### Conceptual scheme

~~~
Warning! /!\ The official LU2IN009 course this year (spring '24) uses as a study case an university database, with the following...

Needs

- Inscriptions to modules
- Affectation of tutors to students
- Planning of rooms

Objets to modelize

- Students
- Modules
- Tutors
- Rooms

Links & Restrictions

- Students will be enrolled in 1 or + modules for an academic year
- Courses are in a given room, with a starting and duration known

In the following documents I will be using the same examples, always in a code box and clearly marked as example, and will try to clarify all and not just copying the course!
~~~

 #### Definitions
 
1. `entities` --> real-world objects
    - Can be specific ('Anne DUPONT') or abstract ('the bank account of a client')

2. `associations` --> relations between entities
3. `attributes` --> properties that gives information about entities of the same class

    - Presents a property or a characteristic of an entity class
    - We can make sets with entities and associations
    - Has a nom and pre-defined values
    - Atomic (no multiple values)
    - A value at a time for every entity.

 ---

1. `entity class` --> set of entities that have the same properties.
    - `Student, Module, ... `

2. `association class` --> set of associations that relies entities of the same class.

--- 

1. `Identifiers` 

They're a sub-set of attributes of an entity class.

Useful to distinguish between two attributes from the same class, the identifier must be unique.

Every entity class must have an identifier, it can be either:

1. Natural, using different attributes of the class. `Ex. Name + Surname + City`
2. Artificial, a new "attribute", `Ex. Spanish DNI no.`

The identifiers depend as well of our needs.

We need to take care of the cardinality of the relationships

#### Transforming a n-ary association into an entity

There are a lot of reasons for wanting to do the transformation, these include simplifying the DB (in the case of complex relationships), more easy queries to the database, reduced redundance of information and easier scalability.

To do this we have to:

1. Create a new entity $E$ using the attributes without the identifier.
2. Give an identifier to $E$ (artificial if none of the E subsets can be chose as such)
3. Create an association $A{i}$ between every $E{i}$ and $E$ with 1:1 cardinality.

#### Reflexivity association

An entity can be associated to itself while maintaining different cardinalities!

#### Weak entities

A weak entity is an entity that can be identified by itself (usually because it doesn't have enough attributes).

They usually have an "identifier" called "discriminant attributes" but they need to be in the context of the strong entity.

The 1:1 cardinality is implicit.

The association with the strong entity can't have attributes.
 
### F.A.Q. Conception

1. Attribute or entity?

    Depends of the application needs.

2. Entity or association?

    General rule: All action that implicates two entities creates a new association.

3. Attribute of an association or of an entity?

    Depends on cardinality!
    - If 1:1 then they're equivalent
    - If n:m depends of the specific context and semantics.

4. Specialization?!

    Useful where a lot of objects share properties and have other priorities standard to them!

    It's usually done in the form of descendance and inheritance.

## And that's all folks! 