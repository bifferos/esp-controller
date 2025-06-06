.PHONY: clean install uninstall

SCRIPT_NAME := esp-controller-check.sh
INSTALL_DIR := /usr/local/bin

UNIT_FILE := "esp-controller.service"

# Destination for systemd unit file
SYSTEMD_DIR := "/etc/systemd/system"


install:
	sudo install -m 755 $(SCRIPT_NAME) $(INSTALL_DIR)/
	sudo install -m 644 $(UNIT_FILE) $(SYSTEMD_DIR)/
	sudo systemctl daemon-reload
	sudo systemctl enable --now $(UNIT_FILE)
	@echo "Installed and started $(UNIT_FILE)"
	
	
uninstall:
	sudo systemctl disable --now $(UNIT_FILE)
	sudo rm -f $(INSTALL_DIR)/$(SCRIPT_NAME)
	sudo rm -f $(SYSTEMD_DIR)/$(UNIT_FILE)
	sudo systemctl daemon-reload
	@echo "Removed $(UNIT_FILE)"

	
clean:
	rm -f *~
