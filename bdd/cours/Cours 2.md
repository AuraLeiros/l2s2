## Cours 1.

Aura Leirós García
Licence Informatique - Sorbonne Université

### Introduction: The relational model

This model is made using the definition and manipulation of relations, structuring the data with them.

We define transformation rules from the E/A model to the relational one.

### Keys

#### Primary and candidate keys

We need to define the use of keys. Every relation must have at least one key and at least one candidate key (and every attribute must be !NULL).

- The primary key can be included in the set of candidate keys

To determine the keys we need to see the restrictions.

#### Foreign key

Subset of attributes where the value comes from _candidate keys_ from the same or other table.

Allowed values: Existing values or NULL

A foreign key can be part of the primary / candidate key of a relation.

### Schema

#### Schema of a relation

Name of the relation + list of the attributes with their domaines + Keys and integrity restrictions.

#### Instance of a relationship

N-uplets of a spreadsheet. i.e. all n-uplets where an n-uplet is a line.

#### Schema of a database

All the schemas of the relationships that are part of the DB

### Notations

#### Schema of a DB

`S = {R1, R2, ..., Rn} where Ri is a relationship schema`


