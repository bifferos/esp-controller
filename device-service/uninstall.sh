#!/bin/bash
set -e

./stop.sh

# Paths to unit file
SERVICE_FILE="esp-controller.service"

# Destination for systemd unit file
SYSTEMD_DIR="/etc/systemd/system"

# Copy unit file
sudo cp "$SERVICE_FILE" "$SYSTEMD_DIR/"

sudo rm -f "$SYSTEMD_DIR/$SERVICE_FILE"

# Reload systemd to forget the removed units
sudo systemctl daemon-reload

# Remove installed script and data directory
sudo rm -f /usr/local/bin/esp-controller-check.sh

echo "Uninstallation complete. esp-controller has been removed."

