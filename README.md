<div align="center">

<img src="assets/Logo.png" alt="Athletic Assistant XR Logo" width="120"/>

# ⚡ ATHLETIC ASSISTANT XR

### *Fitness Automation System — Architected for the Future*

[![Language](https://img.shields.io/badge/Language-C%20(C11)-00599C?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey?style=for-the-badge)]()
[![Build](https://img.shields.io/badge/Build-Makefile-4CAF50?style=for-the-badge)]()
[![XR](https://img.shields.io/badge/XR-Ready-9C27B0?style=for-the-badge)]()

> *"Empowering human performance through modular automation and spatial computing readiness."*

</div>

---

## 🚀 Vision: Fitness Automation System XR

**Athletic Assistant XR** is more than a fitness tracker; it is a modular automation system built in **C**. It features a robust core for health metrics, a dynamic diet planning engine, and a dedicated **XR Abstraction Layer** designed for future integration with spatial computing platforms (OpenXR/WebXR).

---

## 🧩 Architectural Design

```mermaid
graph TD
    A[CLI Presentation Layer] --> B[Core Computation Engine]
    A --> C[Data & Session Layer]
    B --> D[XR Abstraction Layer]
    C --> E[(Session Logs / CSV)]
    D --> F[XR Telemetry / Stubs]
    
    subgraph Core Engine
        B1[BMI/BMR]
        B2[Weight Plan]
        B3[Stamina/VO2Max]
        B4[Diet Engine]
        B5[Exercise Planner]
    end
```

---

## ✨ Advanced Features

| Feature | Description |
|---------|------------|
| 🕶️ **XR Abstraction** | Architected with `xr_interface.h` for future AR/VR workout overlays. |
| 📊 **Session Persistence** | Automatic CSV logging of every session for long-term progress tracking. |
| 🧮 **Visual Metrics** | Real-time ASCII gauges for BMI and Stamina zones. |
| 🫀 **VO₂ Max Analysis** | Scientific approximation of aerobic capacity with age-group norms. |
| 🥗 **Nutrition Engine** | 30nd-item food database with precise macro-nutrient splitting. |
| 📅 **7-Day Scheduler** | Complete weekly workout programming with sets, reps, and recovery. |

---

## 👥 Project Team

| Name | Role |
|------|------|
| **Md Hassan** | Lead Developer |
| **Ayyan Eqbal** | Systems Architect |
| **Intekhab Ahmad** | Data Engineer |
| **Adeeeb Asif** | Documentation & QA |

---

## 🛠️ Getting Started

### Prerequisites
- GCC or any C11-compatible compiler
- `make`

### Installation & Build

```bash
# Standard Build
make

# Build with XR Telemetry Enabled
make xr

# Run the CLI system
make run
```

### 🖥️ Web Command Center XR
Launch the premium visual dashboard to track your trends:
```bash
cd dashboard
npm run dev
# Open http://localhost:3000
```

---

## 📚 Documentation

- 📖 [User Manual & Build Guide](docs/USAGE.md)
- 📐 [Scientific Algorithm Reference](docs/ALGORITHMS.md)
- 📦 [Original Project Specification](AthleticAssistantDocfile.pdf)

---

<div align="center">

**Athletic Assistant XR — Professional Series**  
*Precision Engineering for Human Potential*

</div>
