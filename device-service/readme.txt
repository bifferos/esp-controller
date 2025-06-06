Server for a simple udp client app to talk to a service
and get a response.  This relies on socat to do the 
heavy lifting.  Receives a packet with a query, responds 
whether the given file exists or not.

$ make install

to install the service

This server will listen on ipv4 port 6060.  Check with
netstat -an | grep 6060


$ sudo ./test.py

Will run some tests against the service (run as root).
Just to spell out what is going on, see the tcpdump while it runs

$ sudo tcpdump -i any port 6060 -A
tcpdump: data link type LINUX_SLL2
tcpdump: verbose output suppressed, use -v[v]... for full protocol decode
listening on any, link-type LINUX_SLL2 (Linux cooked v2), snapshot length 262144 bytes
12:39:34.505534 lo    In  IP localhost.39378 > localhost.6060: UDP, length 8
E..$..@.@._................#testfile
12:39:34.507720 lo    In  IP localhost.6060 > localhost.39378: UDP, length 5
E..!..@.@._................ true

12:39:34.507840 lo    In  IP localhost.59671 > localhost.6060: UDP, length 8
E..$..@.@._................#testfile
12:39:34.509442 lo    In  IP localhost.6060 > localhost.59671: UDP, length 6
E.."..@.@._................!false


To use
======

The test.py client example mirrors what the esp will do.  We use udp here
because the ESP may want to do something else in the transmit-receive loop,
and we don't want to stall anywhere.
