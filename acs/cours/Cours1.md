## Cours 1 - A.C.S.

### Introduction - L'architecure client-serveur

Programme client <-> requête avec protocole de communication <-> Programme serveur

- Balisage avec ordre d'attributs indiférant.

Les <> délimitent le nom d'une balise.

- HTML4 

Introduction de la balise label et l'attribut title (sur toutes les balises) pour ajouter d'accésibilité.

- Apparitition de CSS, utilises avec les balises link ou style dans l'en-tete pour pouvoir changer le style sans changer corps.


- Toute balise ouvrante doit etre ferme `<nom></nom>` à exception des balises qui sont toujours vides comme `<title />`

Pour qu'une page soit considere accesible entre autres, les hyperliens doivent avoir des libelles differentes (uniquement si leurs attributes href sont differents), etre separes pour au moins un caractère, (deux balises a ne doivent pas se toucher), l'atttribut alt d'une balise img.

Un document HTML est compossé de :

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

    <body></body>

    <script></script>
    <noscript>/* Alt content to users with disabled scripts */</noscript>

</html>

~~~


Les tables HTML

~~~
 <table>
  <tr>
    <th>Company</th>
    <th>Contact</th>
    <th>Country</th>
  </tr>
  <tr>
    <td>Alfreds Futterkiste</td>
    <td>Maria Anders</td>
    <td>Germany</td>
  </tr>
  <tr>
    <td>Centro comercial Moctezuma</td>
    <td>Francisco Chang</td>
    <td>Mexico</td>
  </tr>
</table> 
~~~

No bloc-tags

- a : allows to visit other pages, href, hreflang
- img : no-content, display src (mandatory), alt (mandatory)
- form : fundamental for client-server communication.

HTML forms

A form is sended only if it has a name attribute and does not have a `disabled` attribute.

Every input tag is surrounded by a `<div></div>` element

Every asking has to have an associated `<label for="something">Somethig:</label> `tag

Use the `<fieldset><legend></legend></fieldset>` to put together in a block some of all input tags.

Input tags

- textarea : input box, `rows` and `cols`
- select : sub-tags with `<option value="something1">Something1</option>`
- optgroup : to have >= 7 `option` sub-tags
- input : very versatile, `value`,  `type`, `name`.

Where and how to send to a server!

We can use a `input` tag with `type="submit"` we have to make attention to not send a name and to be responsive with the different languages cause if we have a `name` attribute the value will depend of the language.

We can also use a `button` tag associated to an script.

The `<form> ` tag has three attributes that specify the sending methods...

- action : if it's empty the browser will take the address that sended the form

- accept-charset : optional, specifies the coding.

- method : either post (the number of octets will be saved at CONTENT_LENGTH) or get (that will save the query string into the QUERY_STRING environment variable)

When a server receives a request from a client, the answer has to come back specifying the type of the content that is sending, with the bare minimum being `Content-type: text/html; charset=utf-8 + empty line`

