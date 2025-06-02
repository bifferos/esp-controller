.PHONY: build run clean run install uninstall install-templates


BINARY_NAME := esp-controller-ui
INSTALL_DIR := /usr/local/bin
SERVICE_FILE := esp-controller-ui.service
SYSTEMD_DIR := /etc/systemd/system

# Web templates go here, e.g. index.html
TEMPLATE_SRC_DIR := templates
TEMPLATE_DST_DIR := /usr/share/esp-controller-ui/templates

# Static files like favicon.ico
STATIC_SRC_DIR := static
STATIC_DST_DIR := /usr/share/esp-controller-ui/static

# Tokens will be generated on-the-fly
TOKEN_SRC_DIR := tokens
TOKEN_DST_DIR := /var/lib/esp-controller/tokens


run: build
	./$(BINARY_NAME) -config ./config.json


install: build
	sudo install -m 755 $(BINARY_NAME) $(INSTALL_DIR)/
	sudo install -d $(TEMPLATE_DST_DIR)
	sudo install -m 644 $(TEMPLATE_SRC_DIR)/* $(TEMPLATE_DST_DIR)
	sudo install -d $(STATIC_DST_DIR)
	sudo install -m 644 $(STATIC_SRC_DIR)/* $(STATIC_DST_DIR)
	sudo install -d $(TOKEN_DST_DIR)
	sudo install -m 644 $(SERVICE_FILE) $(SYSTEMD_DIR)/
	sudo systemctl daemon-reexec
	sudo systemctl enable --now $(BINARY_NAME).service
	@echo "Installed and started $(BINARY_NAME).service"


uninstall:
	sudo systemctl disable --now $(BINARY_NAME).service
	sudo rm -f $(INSTALL_DIR)/$(BINARY_NAME)
	sudo rm -rf $(TEMPLATE_DST_DIR)
	sudo rm -rf $(STATIC_DST_DIR)
	sudo rm -f $(SYSTEMD_DIR)/$(SERVICE_FILE)
	sudo systemctl daemon-reexec
	@echo "Uninstalled $(BINARY_NAME)"
	

build:
	go build -o $(BINARY_NAME) main.go


clean:
	rm -f $(BINARY_NAME) *~

