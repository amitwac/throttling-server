# Throttling-server
Throttling server limits or sets a fixed quota on number of requests from users, sent per second.
At startup, the server should be given a configuration file, having registered users and their
respective quota in below format
>
> user1:100
>
> Example config file is available in the repository: servers/users.config

* The server runs on port 8090, so make sure this port is free.


# Pre-Requsites
To build and run throttling server, below packages should be installed on the machine:
>
>$ cmake --version
>
> cmake version 2.8.12.2
>
>$ g++ --version
>
> g++ (GCC) 4.8.5 20150623 (Red Hat 4.8.5-44
>

# Code walk-through
1. Throttle server implementation is in direcotry: server
2. Code to send requests to throttling server is in directory: client

# Build
1. Build throttling server
    >
    >$ cd server
    >
    >$ make clean
    >
    >$ make all
    >
2. Build client
   >
   >$ cd client
   >
   >$ make clean
   >
   >$ make all
   >


# Run throttling server and send requests to it
1. Run throttling server
<pre>
$ cd server
$ ./throttleserver
USAGE: throttleserver 'user-quota-config-file'
$ ./throttleserver '/path/to/user.config/file'
</pre>
2. Send request to the throttling server
 <pre>
 $ cd client
 $ ./generaterequest
 USAGE: generaterequest username request-count
 $ ./generaterequest Don 100
 </pre>


# Sample response from throttling server
<pre>
Send 15 requests from User Mary, whose quota has been set to '5':
<pre>
$ ./generaterequest Marry 15
Marry
Allow
Marry
Allow
Marry
Allow
Marry
Marry
Allow
Marry
Deny
Marry
Deny
Marry
Deny
Marry
Deny
Marry
Deny
Marry
Deny
Marry
Allow
Marry
Allow
Marry
Allow
Marry
Allow
</pre>
