## Megaguide of HTML & PHP

### HTML tags

- Called in french: balises

- `label=` : data to be displayed
- `value=` : data to be sent to the server

### Forms

`fieldset` is used to put together related elements in a form.
Example of a form: 

~~~
<form action="php script processing" method="POST or GET">
    <fieldset>
        <legend> Title </legend>
        <label for="dropdown">Text to display with the button:</label>
        <select name="name to be used by the server" id="id to match with a <label>" >
            <optgroup label="the label">
                <option value="the value to be sent to the server" label="the label to be displayed"></option>
                ...
            </optgroup>
    </fieldset>
~~~
#### Select tag

We use the following open/closing tags `<select name=a_name id=an_id>` `</select>` with options in between

then we have the possibility to do `optgroup` to create a new group with the following structure

Important! The presence of the `selected` attribute is sufficient to be selected like in the following example:\

`<option value="caralho" selected>caralho</option>`

Any following ocurrences of options with the `selected` attribute will be ignored.


### HTTP REQUESTS

#### Difference between POST and GET requests in HTML FORMS

GET requests are sent in a visible query-string format via URI
Example of a POST request:


- Disadvantages of POST:
    - Not possible to bookmark or caching it
    - Undefined behavior when dealing with browser navigation
    - Not as efficient as GET.
    - Potential danger if not well-defined as they can allow to modify data in the server


