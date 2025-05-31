Installation
============

create /etc/esp-controller/filelist.txt with a list of 
files, one per line matching the names of the files under
/var/lib/esp-controller that you want created/read by the
UI.

Make sure /var/lib/esp-controller exists, and is writable by
your program

$ make install

Will attempt to copy the files somewhere sensible and setup
a systemd service for the UI.

PLEASE INSPECT ALL SOURCES BEFORE RUNNING!


 