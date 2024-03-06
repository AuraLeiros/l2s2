#### Introduction

HTTP does not have a lot of revisions and it's a stateless protocol.

#### Structure of an HTTP request

1. A line with 3 pieces of information (with a space as separator)
    - Name of the request 
    - Address of the ressource (changing spaces for a +, no # allowed)
    - `[OPTIONAL]` name and version of the protocol.
2. Headers with a structure similar to `Nom : value`
3. Body of the request

We are going to mostly use (in the context of this course) `GET, POST, HEAD`

We can group all the requests by what they do. 

1. asking of the client `(If-Modified-Since, Range)`
2. Client capabilities `(Accept-Charset, Accept-Encoding, Accept-Language, Accept)`
3. `Connexion` to send multiple requests
4. `Host` precision to a server
5. `Authorization` sends name and password of an user if asked by the server.
6. `User-agent`
7. `Referer`

Example of a minimal request : `GET /`
Example of a request with a header : 
~~~
GET / HTTP/1.1
Host: www.licence.ufr-info-p6.jussieu.fr
Accept-Language: fr
~~~

#### Structure of an HTTP answer

1. A ligne of status starting with 3 numbers
2. Headers `Name: value`
3. Body

##### Most common status

1. 200 OK
2. 301 Moved Permanently
3. 303 See Other
4. 400 Bad Request
5. 403 Forbidden
6. 404 Not Found

##### Most common headers

1. Content-Type
2. Content-Length
3. Content-Language
4. Content-Location
5. Last-Modified

#### Modes of HTTP connections

- HTTP 0.9 had the particularly that the connection was closed just after the answer was sent
- HTTP 1.0 added persistent connections with headers `Connexion: Keep-Alive` useful to separate a Content-Length header.
- HTTP 1.1 Makes the persistence by default unless a `Connexion: Close` header is sent.

#### Cache-related headers

HTTP servers send headers related to the expiration of the page (and only yhe page, no associated CSS / images / etc)

1. `Expire: n` gives the expiration of the webpage
2. `Cache-control` followed by the values comma separated, `max-age=n` , `immutable`, `must-revalidate`
3. `Vary: cookie`

#### Send of a request to a client

If the client is calling an script, the address at the server ends at the first ? following there indicates the arguments of the executable (indeed, in a query string way)

Query-string structure : `nom1=value&nom2=value..."

With certain restrictions relating to the use of & and = that must be used with %ascii 

The server stores all of this in two system variables, `REQUEST_URI` and `QUERY_STRING`, the first one has all the address and the second one only the query string.

#### Application to forms

We envoy a form using either POST or GET as explained in Cours 1 and Cours 2.

To access the values we have the global variables $_GET and $_POST initialized with the query-string and input flux respectively.

The input tags of type file send files, they store them in the array $_FILES with the arguments size, error, name (not allowed to use), and tmp_name

#### Header function

We have a header function THAT MUST BE SENT BEFORE ANY OTHER FUNCTION

