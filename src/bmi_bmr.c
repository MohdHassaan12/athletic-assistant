/*
 * bmi_bmr.c — Fitness Automation System XR
 * ─────────────────────────────────────────────────────────────────
 * BMI & BMR computation with visual ASCII gauge and XR metric push.
 *
 * Formulas:
 *   BMI  = weight(kg) / [height(m)]²
 *   BMR Male   = 66 + (13.75 × W) + (5 × H_cm) - (6.75 × A)
 *   BMR Female = 655 + (9.56 × W) + (1.85 × H_cm) - (4.68 × A)
 */

#include <stdio.h>
#include <string.h>
#include "../include/athletic_assistant.h"

/* ── Calculations ────────────────────────────────────────────────── */

float calculate_bmi(float weight_kg, float height_m)
{
    return weight_kg / (height_m * height_m);
}

float calculate_bmr(int gender, float weight_kg, float height_cm, int age)
{
    if (gender == 1)
        return 66.0f + (13.75f * weight_kg) + (5.0f * height_cm) - (6.75f * age);
    return 655.0f + (9.56f * weight_kg) + (1.85f * height_cm) - (4.68f * age);
}

const char *bmi_category_str(float bmi)
{
    if (bmi < BMI_UNDERWEIGHT)  return "Underweight";
    if (bmi <= BMI_HEALTHY_MAX) return "Healthy Weight";
    if (bmi <= BMI_OVERWEIGHT)  return "Overweight";
    if (bmi <= BMI_OBESE_I)     return "Obese Class I";
    if (bmi <= BMI_OBESE_II)    return "Obese Class II";
    return "Obese Class III";
}

/* ── ASCII BMI Gauge ─────────────────────────────────────────────── */
/*
 * Renders a colour-coded horizontal bar over the BMI scale 10 – 45.
 * Each character ≈ 1 BMI unit in a 35-wide gauge.
 */
static void render_bmi_gauge(float bmi)
{
    const int WIDTH = 35;
    const float MIN_BMI = 10.0f, MAX_BMI = 45.0f;

    /* Zone boundaries as bar positions */
    int z1 = (int)((18.5f - MIN_BMI) / (MAX_BMI - MIN_BMI) * WIDTH); /* underweight end */
    int z2 = (int)((25.0f - MIN_BMI) / (MAX_BMI - MIN_BMI) * WIDTH); /* healthy end */
    int z3 = (int)((30.0f - MIN_BMI) / (MAX_BMI - MIN_BMI) * WIDTH); /* overweight end */
    int pos = (int)((bmi  - MIN_BMI) / (MAX_BMI - MIN_BMI) * WIDTH);
    if (pos < 0) pos = 0;
    if (pos > WIDTH - 1) pos = WIDTH - 1;

    printf("  BMI Scale  [10 ──────────────────────────── 45]\n");
    printf("             ");
    for (int i = 0; i < WIDTH; i++) {
        if (i == pos) {
            printf(BOLD WHITE "▲" RESET);
        } else if (i < z1) {
            printf(CYAN "─" RESET);
        } else if (i < z2) {
            printf(GREEN "─" RESET);
        } else if (i < z3) {
            printf(YELLOW "─" RESET);
        } else {
            printf(RED "─" RESET);
        }
    }
    printf("\n");
    printf("             ");
    for (int i = 0; i < WIDTH; i++) printf(" ");
    printf("\n");

    printf("  Zones:     " CYAN "■ Under" RESET " | " GREEN "■ Healthy" RESET
           " | " YELLOW "■ Over" RESET " | " RED "■ Obese" RESET "\n");
}

/* ── BMI Classification advice ───────────────────────────────────── */
static void print_bmi_advice(float bmi)
{
    printf("\n  " BOLD "Category : " RESET);
    if (bmi < BMI_UNDERWEIGHT) {
        printf(CYAN BOLD "Underweight" RESET "\n");
        printf("  " DIM "Increase caloric intake with nutrient-dense foods.\n"
               "  Focus on strength training to build lean muscle mass." RESET "\n");
    } else if (bmi <= BMI_HEALTHY_MAX) {
        printf(GREEN BOLD "Healthy Weight" RESET "\n");
        printf("  " DIM "Excellent! Maintain your current habits.\n"
               "  Keep exercising regularly and eating a balanced diet." RESET "\n");
    } else if (bmi <= BMI_OVERWEIGHT) {
        printf(YELLOW BOLD "Overweight" RESET "\n");
        printf("  " DIM "Aim for a moderate caloric deficit (300–500 kcal/day).\n"
               "  Prioritise cardio and reduce ultra-processed foods." RESET "\n");
    } else if (bmi <= BMI_OBESE_I) {
        printf(RED BOLD "Obese — Class I" RESET "\n");
        printf("  " DIM "Consult a healthcare professional for a structured plan.\n"
               "  Start with low-impact cardio (swimming, cycling)." RESET "\n");
    } else if (bmi <= BMI_OBESE_II) {
        printf(RED BOLD "Obese — Class II" RESET "\n");
        printf("  " DIM "Medical supervision strongly recommended.\n"
               "  Focus on sustainable lifestyle changes, not crash diets." RESET "\n");
    } else {
        printf(RED BOLD "Obese — Class III" RESET "\n");
        printf("  " DIM "Please consult a doctor immediately.\n"
               "  A multidisciplinary weight-management programme is essential." RESET "\n");
    }
}

/* ── Public entry point ──────────────────────────────────────────── */

void display_bmi_bmr(UserProfile *user, XRSession *xr)
{
    SECTION("BMI & BMR RESULTS");

    printf("  %-15s : " BOLD "%s" RESET "\n",       "Name",   user->name);
    printf("  %-15s : %d yrs  |  %s\n", "Age / Gender", user->age,
           user->gender == 1 ? "Male" : "Female");
    printf("  %-15s : %.1f cm  (%.3f m)\n", "Height",
           user->height_cm, user->height_m);
    printf("  %-15s : %.2f kg\n\n", "Weight", user->weight);

    HR();
    printf("\n  " BOLD "Body Mass Index (BMI)" RESET "\n");
    printf("  Computed  : " CYAN BOLD "%.2f kg/m²" RESET "\n\n", user->bmi);
    render_bmi_gauge(user->bmi);
    print_bmi_advice(user->bmi);

    HR();
    printf("\n  " BOLD "Basal Metabolic Rate (BMR)" RESET "\n");
    printf("  Computed  : " CYAN BOLD "%.2f kcal/day" RESET "\n", user->bmr);
    printf("  " DIM "(Harris-Benedict equation — calories burned at complete rest)" RESET "\n\n");

    /* Estimated active calorie needs */
    printf("  " BOLD "Daily Calorie Needs by Activity Level:" RESET "\n");
    printf("  %-25s → " CYAN "%.0f kcal" RESET "\n", "Sedentary",         user->bmr * 1.2f);
    printf("  %-25s → " CYAN "%.0f kcal" RESET "\n", "Lightly active",    user->bmr * 1.375f);
    printf("  %-25s → " CYAN "%.0f kcal" RESET "\n", "Moderately active", user->bmr * 1.55f);
    printf("  %-25s → " CYAN "%.0f kcal" RESET "\n", "Very active",       user->bmr * 1.725f);
    printf("  %-25s → " CYAN "%.0f kcal" RESET "\n", "Athlete",           user->bmr * 1.9f);

    /* Send to XR layer */
    if (xr) {
        XRFitnessMetrics m;
        m.bmi = user->bmi;
        m.bmr = user->bmr;
        m.stamina_score = user->stamina_score;
        m.recommended_calories = user->bmr * 1.375f;
        strncpy(m.bmi_category,  bmi_category_str(user->bmi), 31);
        strncpy(m.exercise_type, "BMI/BMR Display", 63);
        xr_send_metrics(xr, &m);
        xr_render_overlay(xr, "BMI", "see HUD panel");
    }

    printf("\n  " DIM "XR Layer : metrics pushed to " XR_STATUS_STR RESET "\n");
}
