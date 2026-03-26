/*
 * athletic_assistant.h
 * ─────────────────────────────────────────────────────────────────
 * Central header — Athletic Assistant: Fitness Automation System XR
 *
 * Includes all shared data structures, constants, and function
 * prototypes for the modular fitness engine.
 *
 * Project: Athletic Assistant — Fitness Automation System XR
 * Team   : Ayyan Eqbal, Intekhab Ahmad, Md Hassan, Adeeeb Asif
 */

#ifndef ATHLETIC_ASSISTANT_H
#define ATHLETIC_ASSISTANT_H

#include "xr_interface.h"
#include "data_logger.h"

/* ─────────────────────────────────────────────────────────────────
   ANSI Styling Macros
   ───────────────────────────────────────────────────────────────── */
#define BOLD       "\033[1m"
#define DIM        "\033[2m"
#define UNDERLINE  "\033[4m"
#define RESET      "\033[0m"
#define GREEN      "\033[32m"
#define CYAN       "\033[36m"
#define YELLOW     "\033[33m"
#define RED        "\033[31m"
#define MAGENTA    "\033[35m"
#define BLUE       "\033[34m"
#define WHITE      "\033[97m"
#define BG_DARK    "\033[40m"

/* ─────────────────────────────────────────────────────────────────
   Constants
   ───────────────────────────────────────────────────────────────── */
#define FOOD_DB_SIZE      30
#define APP_NAME          "Athletic Assistant XR"
#define APP_VERSION       "2.0.0"
#define APP_SUBTITLE      "Fitness Automation System XR"

/* BMI classification thresholds */
#define BMI_UNDERWEIGHT    18.5f
#define BMI_HEALTHY_MAX    24.9f
#define BMI_OVERWEIGHT     29.9f
#define BMI_OBESE_I        34.9f
#define BMI_OBESE_II       39.9f

/* ─────────────────────────────────────────────────────────────────
   Data Structures
   ───────────────────────────────────────────────────────────────── */

/**
 * Food — nutritional data for a single food item.
 *        All quantities per standard serving.
 */
typedef struct {
    const char *name;
    int calories;        /* kcal */
    int fat;             /* grams */
    int vitamins;        /* relative index */
    int protein;         /* grams */
    int carbohydrates;   /* grams */
} Food;

/**
 * UserProfile — all data collected at session startup.
 * BMI and BMR are derived once and reused throughout.
 */
typedef struct {
    char  name[50];
    int   gender;         /* 1 = Male, 2 = Female               */
    int   age;            /* years                              */
    float height_cm;      /* centimetres                        */
    float height_m;       /* metres (derived: height_cm / 100)  */
    float weight;         /* kilograms                          */
    float bmi;            /* kg / m²                            */
    float bmr;            /* kcal / day (Harris-Benedict)        */
    float stamina_score;  /* filled after stamina test, else 0  */
    float rec_calories;   /* recommended daily kcal             */
    XRSession xr;         /* active XR session for this user    */
} UserProfile;

/* ─────────────────────────────────────────────────────────────────
   Utility Macros
   ───────────────────────────────────────────────────────────────── */

/** Print a horizontal rule */
#define HR() printf("  ─────────────────────────────────────────\n")

/** Print a section header box */
#define SECTION(title) \
    printf("\n  ┌─────────────────────────────────────────┐\n"); \
    printf("  │  " BOLD UNDERLINE "%-39s" RESET "  │\n", (title));  \
    printf("  └─────────────────────────────────────────┘\n\n")

/** Render a simple ASCII progress bar (value 0–100, width chars wide) */
#define PROGRESS_BAR(value, width) do { \
    int _filled = (int)((value) * (width) / 100.0f); \
    printf("  [" GREEN); \
    for (int _i = 0; _i < (width); _i++) \
        printf("%s", (_i < _filled) ? "█" : DIM "░" RESET); \
    printf(RESET "] %5.1f%%\n", (float)(value)); \
} while (0)

/* ─────────────────────────────────────────────────────────────────
   Function Prototypes
   ───────────────────────────────────────────────────────────────── */

/* bmi_bmr.c */
float calculate_bmi(float weight_kg, float height_m);
float calculate_bmr(int gender, float weight_kg, float height_cm, int age);
void  display_bmi_bmr(UserProfile *user, XRSession *xr);
const char *bmi_category_str(float bmi);

/* weight_plan.c */
void display_weight_plan(const UserProfile *user);

/* stamina.c */
void display_stamina(UserProfile *user);

/* diet_plan.c */
void display_diet_plan(const UserProfile *user);

/* exercise_plan.c */
void recommend_exercise(int age, float bmi, int fitness_level);
void display_exercise_plan(const UserProfile *user);

#endif /* ATHLETIC_ASSISTANT_H */
