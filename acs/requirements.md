## Requirements

This page will be updated with every TME to indicate the  elements to install in a local machine (not Sorbonne's owned machines) to properly do the TMEs.

All the provided guidelines are for a Debian system running in a WSL2 environment.


### TME 1

- Install apache2 webserver
`sudo apt install apache2`

Every time that a terminal session is started apache2 must be started as well, we can do that with the command `sudo service apache2 start` but I recommend to create an alias

OPTIONAL: We can get the "local" IP of the distro with `ip addr show eth0 | grep inet | awk '{ print $2; }' | sed 's/\/.*$//'` so we're able to use native firefox, I recommend to create an alias.

If not we need, to install firefox in debian we're going to use the `sudo apt-get install firefox-esr` command