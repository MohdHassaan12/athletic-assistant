# ─────────────────────────────────────────────────────────────────
# Makefile — Athletic Assistant: Fitness Automation System XR
# ─────────────────────────────────────────────────────────────────
# Usage:
#   make          → standard CLI build
#   make xr       → build with XR stub telemetry visible
#   make run      → build + run (CLI)
#   make logs     → create logs directory
#   make clean    → remove compiled artifacts
# ─────────────────────────────────────────────────────────────────

CC       = gcc
CFLAGS   = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS  = -lm
SRC_DIR  = src
BIN_DIR  = bin
LOG_DIR  = logs
TARGET   = $(BIN_DIR)/athletic_assistant_xr

SRCS = $(SRC_DIR)/main.c            \
       $(SRC_DIR)/bmi_bmr.c         \
       $(SRC_DIR)/weight_plan.c     \
       $(SRC_DIR)/stamina.c         \
       $(SRC_DIR)/diet_plan.c       \
       $(SRC_DIR)/exercise_plan.c   \
       $(SRC_DIR)/xr_interface.c    \
       $(SRC_DIR)/data_logger.c

HEADERS = include/athletic_assistant.h \
          include/xr_interface.h       \
          include/data_logger.h

.PHONY: all xr run logs clean

all: logs $(BIN_DIR) $(TARGET)

xr: CFLAGS += -DXR_ENABLED
xr: all
	@echo "  XR stubs active — watch logs/xr_telemetry.log"

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

logs:
	mkdir -p $(LOG_DIR)

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(TARGET)
	@echo ""
	@echo "  ✓ Build successful → $(TARGET)"
	@echo "  Run with: make run"
	@echo ""

run: all
	@echo ""
	@echo "  ─── Starting Athletic Assistant XR ───"
	@echo ""
	./$(TARGET)

clean:
	rm -rf $(BIN_DIR)
	@echo "  ✓ Cleaned build artifacts."
