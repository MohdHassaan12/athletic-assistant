# Athletic Assistant XR — Scientific Algorithm Reference

This document details the mathematical models and physiological heuristics implemented in the **Fitness Automation System XR**.

---

## 1. Body Mass Index (BMI) & Visual Zones

```
BMI = weight (kg) / [height (m)]²
```

The system maps this value to a relative scale (10–45) for visual representation in the CLI and XR HUD.

| Range | Classification | Health Risk |
|-------|----------------|-------------|
| < 18.5 | Underweight | High (Malnutrition) |
| 18.5–24.9 | Healthy | Low |
| 25.0–29.9 | Overweight | Moderate |
| 30.0–34.9 | Obese (I) | High |
| 35.0–39.9 | Obese (II) | Very High |
| ≥ 40.0 | Obese (III) | Extreme |

---

## 2. Basal Metabolic Rate (BMR)

Calculated using the **Harris-Benedict Equation (Revised)**.

- **Male:** `66.5 + (13.75 × W) + (5.003 × H) - (6.775 × A)`
- **Female:** `655.1 + (9.563 × W) + (1.850 × H) - (4.676 × A)`

*`W`=kg, `H`=cm, `A`=years.*

---

## 3. Aerobic Capacity (VO₂ Max)

The system provides a **VO₂ max approximation** inferred from 1 km run performance and anthropometric data:

```
VO2max ≈ 100.5 - (0.7 × time_min) - (0.08 × age)
```

*Note: In XR-enabled mode, this is designed to be replaced by a 12-minute Cooper Test or real-time HR sensor integration.*

---

## 4. Stamina Index

A proprietary metric designed for the **Athletic Assistant** to capture specific run-time performance:

```
Stamina = 0.8 × (220 − age) + 0.2 × (weight / time_min) − 3
```

---

## 5. Nutritional Macro-Splitting

The **Diet Planning Engine** follows the **Acceptable Macronutrient Distribution Ranges (AMDR)**:

| Nutrient | Energy Density | Target Distribution |
|----------|----------------|---------------------|
| **Carbohydrates** | 4 kcal/g | 50% of TDEE |
| **Proteins** | 4 kcal/g | 20% of TDEE |
| **Fats** | 9 kcal/g | 30% of TDEE |

*TDEE (Total Daily Energy Expenditure) is computed as `BMR × 1.375` (Lightly Active baseline).*

---

## 6. Target Heart Rate (THR) for XR Coaching

Calculated for the Exercise Recommendation module:

- **Intensity 1 (Beginner):** `50–60% of (220 - age)`
- **Intensity 2 (Intermediate):** `60–75% of (220 - age)`
- **Intensity 3 (Advanced/HIIT):** `75–90% of (220 - age)`

---

## 7. Weight Roadmap

```
Weeks to Target = |Target Weight - Current Weight| / Weekly Rate
```

*Daily Caloric Target for Roadmap:*
```
Plan Calories = (Target Weight × 25) + ((Age - 30) × 5)
```
