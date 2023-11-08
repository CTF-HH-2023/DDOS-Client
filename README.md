> ⚠️ This is a client for educational purpose, used for a scenarios during a ctf organized by 2 university. Our team will not support the usage outside of the CTF context.

# DDOS-Client
## A simple ddos client

To execute the code use this : 

-> apt-get install libcurl4-openssl-dev libssh-dev sshpass openssh-client

-> gcc -o ddos ddos.c -lcurl -lssh -lc

-> ./ddos

To use a file like a botnet respect this format : 

-> username;password;ip;port (don't forget to modify the directory of the file)



## How it's working ?

The ddos-client use CURL library to make a GET request with the custom user-agent. 
It sends to every (fake) compromised machine with set port and run it trought these machine. It's kind of a botnet.
