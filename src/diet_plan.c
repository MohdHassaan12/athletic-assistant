/*
 * diet_plan.c — Fitness Automation System XR
 * ─────────────────────────────────────────────────────────────────
 * Dynamic Diet Planning Engine.
 *
 * Food database: 30 items (expanded from 17).
 * BMI-driven meal plans: Breakfast, Snack, Lunch, Dinner.
 * Outputs full macro summary and daily nutrition table.
 */

#include <stdio.h>
#include "../include/athletic_assistant.h"

/* ── Expanded Food Database (30 items) ───────────────────────────── */
static const Food foods[FOOD_DB_SIZE] = {
 /* idx  Name                                     Cal   Fat  Vit  Pro  Carb */
 /* 00 */ { "Oatmeal (1 cup cooked)",              300,   5,  10,   5,   58 },
 /* 01 */ { "Whole-wheat toast (2 slices)",        200,   2,   5,   7,   36 },
 /* 02 */ { "Greek yogurt with berries",           150,   2,   8,  12,   18 },
 /* 03 */ { "Salad with grilled chicken",          300,  10,  15,  28,   12 },
 /* 04 */ { "Tomato soup with salad",              220,   5,  12,   8,   28 },
 /* 05 */ { "Whole-grain sandwich (turkey)",       370,   9,   8,  22,   40 },
 /* 06 */ { "Baked salmon + roasted veg",          420,  16,  14,  36,   18 },
 /* 07 */ { "Chicken stir-fry + brown rice",       460,  10,  12,  32,   50 },
 /* 08 */ { "Lentil soup (2 cups)",                310,   4,  11,  18,   48 },
 /* 09 */ { "Apple",                                95,   0,  10,   0,   25 },
 /* 10 */ { "Banana",                              105,   0,   6,   1,   27 },
 /* 11 */ { "Orange",                               62,   0,  53,   1,   15 },
 /* 12 */ { "Grapefruit (half)",                    52,   0,  38,   1,   13 },
 /* 13 */ { "Mixed berries (1 cup)",                70,   0,  20,   1,   17 },
 /* 14 */ { "Peanut butter (2 tbsp)",              190,  16,   0,   8,    6 },
 /* 15 */ { "Boiled eggs (2)",                     155,  10,   4,  13,    1 },
 /* 16 */ { "Grilled chicken breast (150g)",       250,   5,   0,  46,    0 },
 /* 17 */ { "Quinoa bowl (1 cup)",                 220,   3,   6,   8,   39 },
 /* 18 */ { "Avocado toast",                       280,  15,   5,   6,   28 },
 /* 19 */ { "Cottage cheese (1 cup)",              180,   5,   4,  26,    7 },
 /* 20 */ { "Protein smoothie (whey + banana)",    280,   3,   8,  25,   35 },
 /* 21 */ { "Sweet potato (medium, baked)",        130,   0,  18,   3,   30 },
 /* 22 */ { "Steamed broccoli + tofu",             200,   6,  25,  14,   14 },
 /* 23 */ { "Mixed nuts (30g)",                    180,  16,   2,   5,    6 },
 /* 24 */ { "Whole-milk paneer (100g)",            265,  20,   0,  18,    3 },
 /* 25 */ { "Tuna salad (canned tuna + veg)",      240,   5,   8,  32,   10 },
 /* 26 */ { "Chana masala (1 bowl)",               280,   7,  10,  15,   40 },
 /* 27 */ { "Dal tadka + brown rice",              340,   6,   9,  14,   56 },
 /* 28 */ { "Overnight oats with chia",            320,   9,   8,  11,   48 },
 /* 29 */ { "Grilled fish (tilapia, 150g)",        200,   4,   0,  38,    0 },
};

/* ── Section printer ─────────────────────────────────────────────── */
static void meal_section(const char *icon_title, int *idx, int count)
{
    printf("\n  " BOLD "%s" RESET "\n", icon_title);
    for (int i = 0; i < count; i++) {
        int f = idx[i];
        printf("   • %-38s " CYAN "%3d kcal" RESET "  |  P:%dg C:%dg F:%dg\n",
               foods[f].name, foods[f].calories,
               foods[f].protein, foods[f].carbohydrates, foods[f].fat);
    }
}

/* ── Macro summary table ─────────────────────────────────────────── */
static void print_macro_table(float kcal)
{
    float protein = (0.20f * kcal) / 4.0f;
    float carbs   = (0.50f * kcal) / 4.0f;
    float fat     = (0.30f * kcal) / 9.0f;

    printf("\n  " BOLD "Daily Macro Targets:" RESET "\n");
    printf("  ┌──────────────────┬────────────┬──────────────┐\n");
    printf("  │ Macro            │  Calories  │    Grams     │\n");
    printf("  ├──────────────────┼────────────┼──────────────┤\n");
    printf("  │ Protein (20%%)   │ %8.0f   │ %9.0f g  │\n", 0.20f * kcal, protein);
    printf("  │ Carbohydrates    │ %8.0f   │ %9.0f g  │\n", 0.50f * kcal, carbs);
    printf("  │ Fat (30%%)       │ %8.0f   │ %9.0f g  │\n", 0.30f * kcal, fat);
    printf("  ├──────────────────┼────────────┼──────────────┤\n");
    printf("  │ " BOLD "Total" RESET "            │ " CYAN "%8.0f" RESET "   │ " DIM "see above" RESET "     │\n", kcal);
    printf("  └──────────────────┴────────────┴──────────────┘\n");
}

/* ── BMI-specific meal plans ─────────────────────────────────────── */
static void plan_underweight(void)
{
    printf("  " BOLD "Goal:" RESET " " CYAN "Caloric Surplus — Weight Gain" RESET
           " (High protein, high healthy fats)\n");
    int b[] = {28, 14, 20};         meal_section("🌅 Breakfast:", b, 3);
    int s[] = {23, 10};             meal_section("🍎 Snack:",     s, 2);
    int l[] = {7,  16, 21};         meal_section("☀️  Lunch:",    l, 3);
    int d[] = {6,  24, 17};         meal_section("🌙 Dinner:",    d, 3);
}

static void plan_healthy(void)
{
    printf("  " BOLD "Goal:" RESET " " GREEN "Balanced Maintenance" RESET
           " (Varied, nutrient-dense)\n");
    int b[] = {0,  2,  15};         meal_section("🌅 Breakfast:", b, 3);
    int s[] = {9,  19};             meal_section("🍎 Snack:",     s, 2);
    int l[] = {3,  17, 4};          meal_section("☀️  Lunch:",    l, 3);
    int d[] = {29, 22, 8};          meal_section("🌙 Dinner:",    d, 3);
}

static void plan_overweight(void)
{
    printf("  " BOLD "Goal:" RESET " " YELLOW "Caloric Deficit — Fat Loss" RESET
           " (High protein, low carb, high fibre)\n");
    int b[] = {18, 2};              meal_section("🌅 Breakfast:", b, 2);
    int s[] = {11, 19};             meal_section("🍎 Snack:",     s, 2);
    int l[] = {25, 4};              meal_section("☀️  Lunch:",    l, 2);
    int d[] = {6,  22};             meal_section("🌙 Dinner:",    d, 2);
}

/* ── Public API ──────────────────────────────────────────────────── */
void display_diet_plan(const UserProfile *user)
{
    SECTION("PERSONALISED DIET PLAN");

    printf("  BMI  : " CYAN "%.2f" RESET "  (%s)\n", user->bmi, bmi_category_str(user->bmi));
    printf("  BMR  : " CYAN "%.0f kcal/day" RESET "\n\n", user->bmr);

    float tdee = user->bmr * 1.375f;   /* lightly active */
    float plan_kcal;

    if (user->bmi < BMI_UNDERWEIGHT) {
        plan_kcal = tdee + 450.0f;
        plan_underweight();
    } else if (user->bmi <= BMI_HEALTHY_MAX) {
        plan_kcal = tdee;
        plan_healthy();
    } else {
        plan_kcal = tdee - 500.0f;
        if (plan_kcal < 1200.0f) plan_kcal = 1200.0f;
        plan_overweight();
    }

    HR();
    print_macro_table(plan_kcal);

    printf("\n  " BOLD "General Guidelines:" RESET "\n"
           "   • Drink 2.5 – 3 L of water daily; more on training days.\n"
           "   • Eat slowly — allow 20 min for satiety signals.\n"
           "   • Minimise ultra-processed foods and sugary beverages.\n"
           "   • Prep meals in advance to stay consistent.\n");

    printf("\n  " DIM "XR Layer : diet plan metrics ready for holographic food-coach overlay.\n" RESET);
}
