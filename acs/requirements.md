## Requirements

This page will be updated with every TME to indicate the  elements to install in a local machine (not Sorbonne's owned machines) to properly do the TMEs.

All the provided guidelines are for a Debian system running in a WSL2 environment.


### TME 1

First, we need to install the apache2 webserver
`sudo apt install apache2`

Every time that a terminal session is started apache2 must be started as well, we can do that with the command `sudo service apache2 start` but I recommend to create an alias

OPTIONAL: We can get the "local" IP of the distro with `ip addr show eth0 | grep inet | awk '{ print $2; }' | sed 's/\/.*$//'` so we're able to use native firefox, I recommend to create an alias as well.

If we don't want to use the native browser, we need to install one (in this case, firefox) in debian we can use the `sudo apt-get install firefox-esr` command

We check that accessing either with the IP or with `localhost` the apache2 welcome page appears.

For easier access we're going to create a `public_html` folder in our user folder

We create the folder and then do `chmod 755 ~/public_html
` to assign permissions. 

With a text editor we add

~~~
<Directory /home/your_username/public_html>
    Options Indexes FollowSymLinks
    AllowOverride None
    Require all granted
</Directory>
~~~

into the `/etc/apache2/apache2.conf` then we restart to apply the changes `sudo service apache2 restart`

If errors occur we need to check the permissions.

