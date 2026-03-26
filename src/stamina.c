/*
 * stamina.c — Fitness Automation System XR
 * ─────────────────────────────────────────────────────────────────
 * Stamina test with VO₂ max approximation and age-group norms.
 *
 * Stamina Formula:
 *   Stamina = 0.8 × (220 − age) + 0.2 × (weight / time_min) − 3
 *
 * VO₂ max approximation (Cooper/Rockport-inspired simplified):
 *   VO2max ≈ 132.853 − (0.769 × weight_lb) − (0.3877 × age)
 *            + (6.315 if male) − (3.2649 × time_min) − (0.1565 × HR)
 *   (HR not available in CLI — we use a reasonable estimate from stamina)
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../include/athletic_assistant.h"

/* ── Age-group fitness norms table (VO2max ml/kg/min) ────────────── */
static const struct { int age_lo; int age_hi; float poor; float fair; float good; float excellent; } norms[] = {
    { 18, 24,  38.0f, 43.0f, 51.0f, 56.0f },
    { 25, 34,  37.0f, 41.0f, 48.0f, 53.0f },
    { 35, 44,  35.0f, 39.0f, 45.0f, 50.0f },
    { 45, 54,  32.0f, 36.0f, 42.0f, 47.0f },
    { 55, 64,  28.0f, 33.0f, 37.0f, 42.0f },
    { 65, 99,  25.0f, 28.0f, 33.0f, 37.0f },
};
static const int NORMS_COUNT = (int)(sizeof(norms)/sizeof(norms[0]));

static void print_vo2_norms(int age, float vo2)
{
    int row = -1;
    for (int i = 0; i < NORMS_COUNT; i++) {
        if (age >= norms[i].age_lo && age <= norms[i].age_hi) { row = i; break; }
    }
    if (row < 0) return;

    printf("\n  " BOLD "VO₂ Max Age-Group Comparison (ages %d–%d):" RESET "\n",
           norms[row].age_lo, norms[row].age_hi);
    printf("  ┌────────────────┬───────────────────┬────────┐\n");
    printf("  │ Rating         │ VO₂ max (ml/kg/min)│ Yours  │\n");
    printf("  ├────────────────┼───────────────────┼────────┤\n");

    struct { const char *label; float threshold; const char *col; } ratings[] = {
        { "Poor",      norms[row].poor,      RED    },
        { "Fair",      norms[row].fair,      YELLOW },
        { "Good",      norms[row].good,      CYAN   },
        { "Excellent", norms[row].excellent, GREEN  },
    };
    for (int i = 0; i < 4; i++) {
        char marker[8] = "   ";
        if (vo2 >= ratings[i].threshold &&
            (i == 3 || vo2 < ratings[i+1 < 4 ? i+1 : 3].threshold)) {
            strcpy(marker, "◀ YOU");
        }
        printf("  │ %s%-14s%s │ ≥ %16.1f  │ %-6s │\n",
               ratings[i].col, ratings[i].label, RESET,
               ratings[i].threshold, marker);
    }
    printf("  └────────────────┴───────────────────┴────────┘\n");
}

static const char *stamina_label(float s)
{
    if (s < 100) return RED    "Needs Improvement" RESET;
    if (s < 150) return YELLOW "Average"           RESET;
    if (s < 200) return CYAN   "Good"              RESET;
    return               GREEN  "Excellent"         RESET;
}

void display_stamina(UserProfile *user)
{
    float time_min;

    SECTION("STAMINA TEST");
    printf("  " DIM "Estimates cardiovascular fitness from a 1 km timed run.\n" RESET "\n");
    printf("  Enter time to run 1 km (minutes): ");
    scanf("%f", &time_min);

    if (time_min <= 0) { printf(RED "\n  [!] Invalid time.\n" RESET); return; }

    float stamina = 0.8f * (220 - user->age)
                  + 0.2f * (user->weight / time_min)
                  - 3.0f;

    /* Simplified VO₂ max estimate (no HR sensor — inferred from time) */
    float vo2max = 100.5f - (0.7f * time_min) - (0.08f * (float)user->age);
    if (vo2max < 10.0f) vo2max = 10.0f;

    user->stamina_score = stamina;

    HR();
    printf("\n  " BOLD "Results for %s:" RESET "\n\n", user->name);
    printf("  %-22s : %.2f min\n",   "1 km Run Time",  time_min);
    printf("  %-22s : " CYAN BOLD "%.2f" RESET "\n",   "Stamina Score",  stamina);
    printf("  %-22s : " CYAN BOLD "%.1f ml/kg/min" RESET "\n", "VO₂ max (est.)", vo2max);
    printf("  %-22s : %s\n\n",       "Rating",  stamina_label(stamina));

    /* Visual stamina bar (scale 0–300) */
    float pct = (stamina / 300.0f) * 100.0f;
    if (pct > 100.0f) pct = 100.0f;
    if (pct < 0.0f)   pct = 0.0f;
    printf("  Stamina ");
    PROGRESS_BAR(pct, 30);

    print_vo2_norms(user->age, vo2max);

    HR();
    printf("\n  " BOLD "Improvement Advice:" RESET "\n");
    if (stamina < 100) {
        printf("   • Start with brisk 20-min walks 5 × / week.\n"
               "   • Progress to walk/run intervals over 4 weeks.\n"
               "   • Target a 3-month programme before re-testing.\n");
    } else if (stamina < 150) {
        printf("   • Add 30-min continuous runs 3 × / week.\n"
               "   • One interval session per week (e.g. 6 × 400 m).\n"
               "   • Re-test in 6 weeks to track improvement.\n");
    } else if (stamina < 200) {
        printf("   • Introduce tempo runs at 80%% max HR.\n"
               "   • Add one long run (60+ min) per week.\n"
               "   • Consider a structured 10-week running plan.\n");
    } else {
        printf("   • Maintain with 5 × / week mixed training.\n"
               "   • Periodise: build → peak → recovery blocks.\n"
               "   • Target a race or event to stay motivated!\n");
    }

    printf("\n  " DIM "XR Layer : stamina score queued for XR HUD overlay.\n" RESET);
}
