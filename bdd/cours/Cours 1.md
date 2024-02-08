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
I : Use machine-oriented languages like SQL\

#### Two different models for two different needs

1. Entity-Association model

High-level description of data, defines links between the data.\
Used by the designer and the client

2. Relational model.

Logical representation of data, normally in a sheet setting.\
Used by the designer and the developer.

Therefore, our stepping stone will be learn how to design an Entity-Association model...
 
### 2. _Mãos à obra!_ How to design a Entity-Association Model


