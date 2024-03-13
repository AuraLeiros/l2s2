Aura Leirós García
TD 1 - A.C.S.

### Exercise 1.

- The first line it's a declaration to inform the browser what type or document we're sending, in HTML < HTML5 it needs to have the DTD referenced.

- The tags `<head>` and `<body>` are the start of the metadata and the text, respectively.

- The first `<meta>` is always to send the charset encoding (usually "UTF-8")

- The `<a>` tag is an hypertextual link.

- `<form>` is used to enclose a formulary

- It's to designate special characteres in html.

### Exercise 2.

HTTP is a request-reponse protocol we usually need to send something along the lines of:

~~~
METHOD URI HTTP_VERSION

HEADERS

BODY
~~~

In this case we're only asked to send a header with a body, so we're going to write:

~~~
#! /bin/bash

echo "Content-Type: text/plain; charset="utf-8"
echo
echo $(date)
~~~  

### Exercise 3.

For this exercise we can use the CAT<<EOF
~~~
#! /bin/bash

cat<<EOF
Content-Type: text/html; charset="utf-8"

<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html" charset="utf-8" />
    	<title>Server and Client TD1</title>
        <style>
        h1 {
            text-align:center
        }
        </style>
    </head>
    <body>
        <div>
            <h1>Server and Client TD1</h1>
            $HTTP_USER_AGENT and $SERVER_SOFTWARE
        </div>
    </body>
</html>    
~~~

Rappel: `<div>` is a section, `<h1>` is header.


#### Exercice 4.

~~~
#! /bin/bash

cat<<EOF
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html" charset="utf-8" />
    	<title>Server and Client TD1</title>
        <style>
            tr:nth-child(2n) {
                background:#edf3fe
            }
        </style>
    </head>

    <body>
        <table>
            <caption>Table des variables!</caption>
            <tr>
                <th>Noms des variables></th>
                <th>Valeurs des variables</th>
            </tr>
            <tr>
                /* We can add a <th> here to create a header for the row */
                <td>A</td>
                <td>B</td>
            </tr>
            <tr>
                <td>A</td>
                <td>B</td>
            </tr>
            <tr>
                <td>A</td>
                <td>B</td>
            </tr>
            <tr>
                <td>A</td>
                <td>B</td>
            </tr>
            <tr>
                <td>A</td>
                <td>B</td>
            </tr>
            <tr>
                <td>A</td>
                <td>B</td>
            </tr>
            <tr>
                <td>A</td>
                <td>B</td>
            </tr>
        </table>
    </body>
</html>
EOF
~~~

### Exercice 5.

~~~
#! /bin/bash

cat<<EOF
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html" charset="utf-8" />
    	<title>Table multiplication</title>
        <style>
            tr:nth-child(2n) {
                background:#edf3fe
            }
        </style>
    </head>
    <body>
        <table>
            <caption> table de multiplication  </caption>
            <tr>
                <th>x</th>
                <th>2x</th>
            </tr>
EOF
while [ $i -lt 10 ]; do
    echo "<tr><td>$i</td><td>$((2 * i))</td></tr>"
    ((i++))
done
echo '</table></body></html>
~~~

### Exercise 6.

We just need to reformulate to get a single column with a `<th>` cutting it

### Exercise 7.

~~~
#!/bin/sh

cat <<EOF
Content-Type: text/html; charset=utf-8

<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <title>Tables de multiplication par 2</title>
  <style type='text/css'>tr:nth-child(2n) {background:beige;}</style>
</head>
<body>
  <table>
    <caption>Table de multiplication par 2 sur 2 colonnes</caption>
    <tr><th>x</th><th>2x</th></tr>
    <tr><td style='text-align:center' colspan='2'>0</td></tr>
EOF

i=1
while [ $i -lt 10 ]
do
  echo "<tr><td>$i</td><td>$(($i*2))</td></tr>"
  i=$((i+1))
done

echo '</table>
</body>
</html>'

~~~

### Exercise 8.

The same as exercise 6 but with rows.
