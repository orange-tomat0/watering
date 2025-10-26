PROJECT_ROOT := $(shell cd $(dir $(realpath $(firstword $(MAKEFILE_LIST)))) && cd /d %CD%)

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

first-setup:
	arduino-cli --config-file $(CONF) core update-index
	arduino-cli --config-file $(CONF) core install m5stack:esp32
	arduino-cli --config-file $(CONF) lib install "M5CoreS3"

debug:
	arduino-cli --config-file $(CONF) compile --libraries $(LIB) --build-path $(TMP) --output-dir $(DEBUG_BUILD_DIR) --fqbn $(FQBN) $(SRC_PATH)

upload:
	arduino-cli --config-file $(CONF) upload -b $(FQBN) -p $(SERIAL_DEV) -i $(DEBUG_BUILD_DIR)\$(SOFT_BIN)
