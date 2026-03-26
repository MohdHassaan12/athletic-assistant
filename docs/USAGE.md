# Athletic Assistant XR — User Manual & Build Guide

## 🛠️ System Requirements

- **Compiler:** GCC (recommended) or Clang.
- **Standards:** C11 or higher.
- **Build Tool:** GNU Make.
- **Platform:** Works on macOS, Linux, and Windows (via WSL or MinGW).

---

## ⚙️ Build Instructions

The project uses a structured `Makefile` for multi-file compilation.

### 1. Standard Build
Compiles all core modules and the XR abstraction layer in **Stub Mode**.
```bash
make
```

### 2. XR Telemetry Build
Enables the `-DXR_ENABLED` flag. This allows you to monitor the XR abstraction layer calls in `logs/xr_telemetry.log` during a terminal session.
```bash
make xr
```

### 3. Cleanup
Removes all compiled binaries and object files.
```bash
make clean
```

---

## 🚀 Running the System

After building, launch the executable:
```bash
make run
```

---

## 📂 Project Organization

- **`src/`**: All C source files (Modular architecture).
- **`include/`**: Header files (`athletic_assistant.h`, `xr_interface.h`).
- **`bin/`**: Target directory for compiled binaries.
- **`docs/`**: Scientific algorithms and usage manuals.
- **`logs/`**: CSV session logs and XR telemetry data.
- **`assets/`**: Media and branding assets.

---

## 📊 Data & Persistence

The system automatically persists your fitness data:

1. **`logs/fitness_sessions.log`**: A CSV file containing every session's metrics (Timestamp, BMI, BMR, Stamina, XR Mode).
2. **`logs/xr_telemetry.log`**: A trace of all calls to the XR abstraction layer (viewable in real-time if `make xr` was used).

You can view your history within the app by selecting the **`[h] Session History`** option in the main menu.

---

## 🛡️ Future XR Integration

To integrate a real XR SDK (like OpenXR):
1. Locate `src/xr_interface.c`.
2. Replace the `xr_log()` stubs with your hardware-specific SDK calls.
3. Link the necessary libraries in the `Makefile`.

---

*Precision Engineered by the Athletic Assistant Team.*
