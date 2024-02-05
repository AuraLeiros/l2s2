## TD 1

Made by Aura Leirós García\
Galiza Ceive Poder Popular

### Exercice 1

- The first line is composed of the `!DOCTYPE` declaration that is used to specify the type and version of the HTML / XTML being used. We can use a simple html for html5 or indicate a specific rule conformity.

- `<head>` is used to specify the metadata and other non-visible information while `<body>` is the element rendered and displayed in the browser.

- the first `<meta>` is used to send the metadata, more specifically, the Content-type including the type of the file and the used encoding

- `<a>` is used to create links usually combined with href, an example of use `<a href="linkto.something">Text</a>`

- `<form>` is used to create an interactive form.

- `&` is used for special items (for example < is &lt)

### Exercise 2

~~~
#! /bin/sh

echo "Content-type: text/plain; charset=utf-8"
echo /* La ligne vide */
echo "$(date)"
~~~

### Exercice 3

~~~
#! /bin/sh

cat <<EOF > var_style.html

Content-type: text/html; charset=utf-8

<html>
  <head>
    <meta charset="utf-8">
    <title>Titre de la page</title>
    <style type="text/css">
      h1 {
        text-align: center;
      }
    </style>
  </head>

  <body>
    <div>
      <h1>Titre de la page</h1>
      <p>Phrase quelconque utilisant le nom du client (\$client) et le nom du serveur (\$serveur).</p>
    </div>
  </body>
</html>

EOF

NOTE: the code is partially correct, we need to use the $ to substitute for the given env variables
~~~

As we can see, the first line of code "cat's" the following lines until the EOF is found (note: we can use any other tag) saving them into the var_style.html