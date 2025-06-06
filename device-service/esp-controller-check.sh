#!/bin/sh
# Read the filename from stdin (UDP packet)
read -r filename

# Check if the file exists in /var/lib/switchboard
if [ -n "$filename" ] && [ -e "/var/lib/switchboard/$filename" ]; then
  echo "true"
else
  echo "false"
fi
