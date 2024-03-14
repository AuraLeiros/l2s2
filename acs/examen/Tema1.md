# Cours 1

Aura Leirós García\
Feito con <3 em Galiza e Portugal

## Cours

- All the tags must follow the structure `<name></name>` with the exception of the ones that are always empty like `<title />` 

&nbsp;

With the introduction of HTML4 there were revolutionary changes to the HTML structure, including the ìntroduction of the `<label>` tag to improve accesibility and CSS to change the style without changing the body of the code.

### `<a>` and `<img>` tags


A `<a>` tag is used to provide a link to other webpages, and have some kind of restrictions, these have to be clearly differentiated meaning that they can't touch one another and the anchor text must be clearly different for screenreaders.

`<a href='$link'> Anchor text </a>`

The `<img>` is used to display images. They need to have an alt attribute.

`<img src='$link' alt='This is the explanation'/>`

### The HTML structure

A HTML snnipet is composed of 5 fundamental parts.

1. `<html lang='fr-fr'> </html>` tags

Is important to specify the language due to accesibility reasons.

2. DOCTYPE

That will be 'HTML' in case of HTML5 and older and the DTD in previous versions, DTD will be further explained in following courses an example of HTTP 4.1:

~~~
/* HTML 4.1 */
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
~~~    


3. `<head>` tag.

That will contain a `<meta>` tag that is used to send metadata, the bare minimum is `<meta charset='UTF-8'>`, but we will consider that is `<meta http-equiv="Content-Type" content="text/html;>` a `<title>Title</title>` tag and a `<link>` that is used to set things like the CSS or the webpage's icon, an example can be `<link rel="stylesheet" href="styles.css"/>`

4.  `<body></body>` tags

That will contain the body of the page.

5. `<script></script> and <noscript>content</noscript>` tags

The first will be used to execute javascript code in the page, the second one is to display a message for users with disabled javascript.


A "complete" example of how a HTML webpage looks like:

~~~
<!DOCTYPE HTML>

<html lang='fr-fr'>

    <head>
        <meta content="">

        <title> /* Page title to index the webpage */ </title>
        <link href=' /* address of the ressource */ rel='/* relationship */ >

        /* OPTIONAL : */
        <base href=/* web address */ > 
        <style></style>
    </head>

    <body>
    </body>

    <script></script>
    <noscript>/* Alt content to users with disabled scripts */</noscript>

</html>
~~~

### HTML tables

HTML disposes of tables to display information in a fashioned way, these is an example of how a table looks like.

~~~
<table>

  <caption>Employee Information</caption>

  <thead>
    <tr>
      <th>Employee ID</th>
      <th>Name</th>
      <th>Department</th>
    </tr>
  </thead>

  <tbody>
    <tr>
      <td>001</td>
      <td>John Doe</td>
      <td>Marketing</td>
    </tr>
    <tr>
      <td>002</td>
      <td>Jane Smith</td>
      <td>Finance</td>
    </tr>
  </tbody>

</table>
~~~

There are multiple things that are kind of optional, specifically the `<thead>` and `<tbody>` that is used to reagrupate the information but is a good developement practice.

Tables are structured using rows, `<tr>` stands for table row and `<td>` for table data (i.e. cell). We need to include a caption for accesibility purposes and it's a good practice to put it at the beginning.

### HTML forms

An HTML form stands for the primary way of communication between an user and the server-side, the opening tag it's composed of 4 primary attributes.

1. `id` and `name`
2. `action` that specifies which script is supposed to be sent the form, if empty it will be the sending one.
3. `method` that will be `get` or `post` that will be talking later.

Later we found a `<fieldset>` tag to reagrupate options together, and inside the inputs. 

It's very important that we use the `<label>` tag for every element inside the fieldset, it is associated with the id rather than the name.

~~~
<form action="/submit" method="post">
  <label for="username">Username:</label>
  <input type="text" id="username" name="username"><br>
</form>
~~~