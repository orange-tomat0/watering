PROJECT_ROOT := $(shell powershell -Command "(Get-Location).Path")

#Basic Configration
SRC_DIR := $(PROJECT_ROOT)\source
DEBUG_BUILD_DIR := $(PROJECT_ROOT)\build
TMP := $(PROJECT_ROOT)\tmp\build
LIB := $(SRC_DIR)\libraries
CONF := arduino-cli.yaml
FQBN := m5stack:esp32:m5stack_cores3
COMPILE_SETTINGS := compile_commands.json

#Source and Binary Names
SRC_PATH := .\source\main\main.ino
SOFT_BIN := main.ino.bin

#Serial Device Auto-Detection
SERIAL_DEV ?= COM3

all: debug

.PHONY: prepare_dirs
prepare_dirs:
	@if not exist "$(DEBUG_BUILD_DIR)" mkdir "$(DEBUG_BUILD_DIR)"
	@if not exist "$(PROJECT_ROOT)\tmp" mkdir "$(PROJECT_ROOT)\tmp"
	@if not exist "$(PROJECT_ROOT)\tmp\build" mkdir "$(PROJECT_ROOT)\tmp\build"
	@if not exist "$(PROJECT_ROOT)\tmp\cache" mkdir "$(PROJECT_ROOT)\tmp\cache"
	@if not exist "$(PROJECT_ROOT)\tmp\downloads" mkdir "$(PROJECT_ROOT)\tmp\downloads"
	@if not exist "$(PROJECT_ROOT)\external" mkdir "$(PROJECT_ROOT)\external"
	@if not exist "$(PROJECT_ROOT)\external\boards" mkdir "$(PROJECT_ROOT)\external\boards"
	@if not exist "$(PROJECT_ROOT)\external\libraries" mkdir "$(PROJECT_ROOT)\external\libraries"
	@if not exist "$(SRC_DIR)\libraries" mkdir "$(SRC_DIR)\libraries"
	@echo [OK] I have confirmed the required directories.

first-setup: prepare_dirs
	arduino-cli --config-file $(CONF) core update-index
	arduino-cli --config-file $(CONF) core install m5stack:esp32
	arduino-cli --config-file $(CONF) lib install "M5CoreS3"

debug: prepare_dirs
	arduino-cli --config-file $(CONF) compile --libraries $(LIB) --build-path $(TMP) --output-dir $(DEBUG_BUILD_DIR) --fqbn $(FQBN) $(SRC_PATH)

upload: prepare_dirs
	arduino-cli --config-file $(CONF) upload -b $(FQBN) -p $(SERIAL_DEV) -i $(DEBUG_BUILD_DIR)\$(SOFT_BIN)

check-root:
	@echo PROJECT_ROOT = $(PROJECT_ROOT)
