#!/bin/sh
# Read the filename from stdin (UDP packet)
read -r filename

# Check if the file exists in /var/lib/esp-controller
if [ -n "$filename" ] && [ -e "/var/lib/esp-controller/$filename" ]; then
  echo "true"
else
  echo "false"
fi
