/*
 * weight_plan.c — Fitness Automation System XR
 * ─────────────────────────────────────────────────────────────────
 * Weight Gain/Loss Planning Engine.
 *
 * Generates a week-by-week timeline with daily caloric targets and
 * phased milestones to reach the user's target weight.
 */

#include <stdio.h>
#include <math.h>
#include "../include/athletic_assistant.h"

#define MAX_MILESTONE_WEEKS 12   /* milestones shown in the plan table */

static void print_week_table(float start, float target, float rate, int weeks, int gaining)
{
    printf("\n  " BOLD "Week-by-Week Milestones:" RESET "\n");
    printf("  ┌──────┬────────────────┬────────────────┐\n");
    printf("  │ Week │ Target Weight  │  Progress      │\n");
    printf("  ├──────┼────────────────┼────────────────┤\n");

    int step = (weeks > MAX_MILESTONE_WEEKS) ? (weeks / MAX_MILESTONE_WEEKS) : 1;
    if (step < 1) step = 1;

    for (int w = step; w <= weeks; w += step) {
        float wk_weight = gaining
            ? (start + rate * w)
            : (start - rate * w);

        float pct = (gaining)
            ? ((wk_weight - start) / (target - start)) * 100.0f
            : ((start - wk_weight) / (start - target)) * 100.0f;
        if (pct > 100.0f) pct = 100.0f;

        printf("  │ %4d │ " CYAN "%10.2f kg" RESET "   │ [", w, wk_weight);
        int filled = (int)(pct / 5.0f);       /* 20-char bar ÷ 5 = 20 slots */
        for (int i = 0; i < 20; i++)
            printf("%s", i < filled ? "█" : "░");
        printf("] " CYAN "%5.1f%%" RESET " │\n", pct);
    }
    /* Always show "final" row */
    printf("  │ %4d │ " GREEN "%10.2f kg" RESET "   │ [████████████████████]  DONE │\n",
           weeks, target);
    printf("  └──────┴────────────────┴────────────────┘\n");
}

void display_weight_plan(const UserProfile *user)
{
    float target_weight, rate, daily_calories;
    int   weeks;

    SECTION("WEIGHT MANAGEMENT PLAN");
    printf("  Current Weight  : " CYAN BOLD "%.2f kg" RESET "\n\n", user->weight);
    printf("  Enter your target weight (kg): ");
    scanf("%f", &target_weight);

    if (target_weight <= 0) {
        printf(RED "\n  [!] Invalid weight.\n" RESET);
        return;
    }

    if (fabsf(target_weight - user->weight) < 0.1f) {
        printf(GREEN "\n  ✓ You are already at your target weight!\n" RESET);
        return;
    }

    int gaining = (target_weight > user->weight);
    printf("  Enter desired weight %s per week (kg): ", gaining ? "gain" : "loss");
    scanf("%f", &rate);

    if (rate <= 0) { printf(RED "\n  [!] Invalid rate.\n" RESET); return; }

    float delta = gaining ? (target_weight - user->weight) : (user->weight - target_weight);
    weeks = (int)ceilf(delta / rate);
    daily_calories = (target_weight * 25.0f) + ((user->age - 30) * 5.0f);

    HR();
    printf("\n  " BOLD "%s" RESET "\n", gaining ? "▲  Weight Gain Programme" : "▼  Weight Loss Programme");
    printf("  Current Weight  : %.2f kg\n", user->weight);
    printf("  Target Weight   : " CYAN "%.2f kg" RESET "\n", target_weight);
    printf("  Rate per week   : %.2f kg\n", rate);
    printf("  Duration        : " BOLD CYAN "%d weeks" RESET " (~%.1f months)\n",
           weeks, weeks / 4.3f);
    printf("  Daily Calories  : " BOLD CYAN "%.0f kcal" RESET "\n\n", daily_calories);

    /* Safety advice */
    if (!gaining && rate > 1.0f)
        printf("  " YELLOW "⚠  Losing more than 1 kg/week risks muscle loss.\n"
               "     Consider a rate of 0.5 – 0.75 kg/week for best results.\n" RESET "\n");
    if (gaining && rate > 0.5f)
        printf("  " YELLOW "⚠  Gaining more than 0.5 kg/week may increase fat gain.\n"
               "     Consider 0.25 – 0.5 kg/week if building lean muscle.\n" RESET "\n");

    print_week_table(user->weight, target_weight, rate, weeks, gaining);

    HR();
    printf("\n  " BOLD "Key Strategies:" RESET "\n");
    if (gaining) {
        printf("   • Caloric surplus of 300 – 500 kcal above TDEE\n"
               "   • Protein: 1.6 – 2.2 g per kg of bodyweight\n"
               "   • Compound lifts 3 – 4 × / week (progressive overload)\n"
               "   • Sleep 7 – 9 hrs for optimal anabolic hormone production\n");
    } else {
        printf("   • Caloric deficit of 300 – 500 kcal below TDEE\n"
               "   • Keep protein high (1.6 g/kg) to preserve muscle\n"
               "   • Cardio 3 – 4 × / week, resistance training 2 × / week\n"
               "   • Weigh yourself weekly (same time, morning, fasted)\n");
    }
}
