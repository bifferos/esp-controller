.PHONY: build run clean


BINARY_NAME := esp-controller-ui
INSTALL_DIR := /usr/local/bin
SERVICE_FILE := esp-controller-ui.service
SYSTEMD_DIR := /etc/systemd/system
TEMPLATE_SRC_DIR := templates
TEMPLATE_DST_DIR := /usr/share/esp-controller-ui/templates


install: build install-templates
	sudo cp $(BINARY_NAME) $(INSTALL_DIR)/
	sudo cp $(SERVICE_FILE) $(SYSTEMD_DIR)/
	sudo chmod 644 $(SYSTEMD_DIR)/$(SERVICE_FILE)
	sudo systemctl daemon-reexec
	sudo systemctl enable --now $(BINARY_NAME).service
	@echo "Installed and started $(BINARY_NAME).service"


uninstall: uninstall-templates
	sudo systemctl disable --now $(BINARY_NAME).service
	sudo rm -f $(INSTALL_DIR)/$(BINARY_NAME)
	sudo rm -f $(SYSTEMD_DIR)/$(SERVICE_FILE)
	sudo systemctl daemon-reexec
	@echo "Uninstalled $(BINARY_NAME).service"



install-templates:
	@echo "Installing templates to $(TEMPLATE_DST_DIR)"
	sudo install -d $(TEMPLATE_DST_DIR)
	sudo install -m 644 $(TEMPLATE_SRC_DIR)/* $(TEMPLATE_DST_DIR)


uninstall-templates:
	@echo "Removing installed templates from $(TEMPLATE_DST_DIR)"
	sudo rm -rf $(TEMPLATE_DST_DIR)
	

build:
	go build -o $(BINARY_NAME) main.go
		