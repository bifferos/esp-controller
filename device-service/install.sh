#!/bin/bash

#
# Install script for esp-contolller, a simple control mechanism for an ESP-01.
#

set -e

# Paths to unit file
SERVICE_FILE="esp-controller.service"

# Destination for systemd unit file
SYSTEMD_DIR="/etc/systemd/system"

# Copy unit file
sudo cp "$SERVICE_FILE" "$SYSTEMD_DIR/"

# Set permissions
sudo chmod 644 "$SYSTEMD_DIR/$SERVICE_FILE"

# Setup program
sudo cp esp-controller-check.sh /usr/local/bin/.
sudo chmod 755 /usr/local/bin/esp-controller-check.sh

# Reload systemd to recognize new units
sudo systemctl daemon-reload

# Enable and start the socket (service will be started on demand)
sudo systemctl enable --now esp-controller.service

echo "Installation complete. esp-control is active."
