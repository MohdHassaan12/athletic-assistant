/*
 * exercise_plan.c — Fitness Automation System XR
 * ─────────────────────────────────────────────────────────────────
 * Exercise Recommendation Engine.
 *
 * Provides:
 *   • BMI-tailored exercise TYPE with specific activities
 *   • Fitness-level INTENSITY with target heart-rate zones
 *   • Full 7-day weekly schedule with sets / reps / duration
 *   • Warm-up and cool-down routines
 *
 * XR Integration note:
 *   In XR mode, each workout slot maps to a virtual scene:
 *   e.g. "Virtual Gym" (strength), "Trail Run" (cardio),
 *        "Zen Studio" (flexibility / cool-down).
 */

#include <stdio.h>
#include "../include/athletic_assistant.h"

/* ── Exercise type by BMI ─────────────────────────────────────────── */
static void print_exercise_type(float bmi)
{
    printf("  " BOLD "Recommended Exercise Type:" RESET "\n\n");

    if (bmi < BMI_UNDERWEIGHT) {
        printf("  " CYAN BOLD "Strength & Hypertrophy Training" RESET "\n");
        printf("   • Squats, Deadlifts, Bench Press (compound focus)\n"
               "   • Progressive overload: +2.5 kg per session on big lifts\n"
               "   • LIMIT cardio to 2 × /week (15 min, low intensity)\n"
               "   • Caloric surplus essential — train to build, not burn\n\n");
        printf("  " DIM "XR Scene: " RESET CYAN "Virtual Gym — Strength Hall" RESET "\n");

    } else if (bmi <= BMI_HEALTHY_MAX) {
        printf("  " GREEN BOLD "Balanced Cardio + Strength Training" RESET "\n");
        printf("   • Cardio: Running, cycling, swimming 3 × /week\n"
               "   • Strength: Full-body or PPL split 3 × /week\n"
               "   • Core: Planks, cable rotations, hanging leg raises\n"
               "   • Flexibility: Yoga or dynamic stretching 1 × /week\n\n");
        printf("  " DIM "XR Scene: " RESET GREEN "Virtual Gym + Outdoor Trail" RESET "\n");

    } else {
        printf("  " YELLOW BOLD "Cardiovascular & Fat-Loss Training" RESET "\n");
        printf("   • Low-impact cardio: Walking → brisk walk → jogging\n"
               "   • Cycling, elliptical, or swimming (joint-friendly)\n"
               "   • Resistance training 2 × /week to preserve muscle\n"
               "   • Target 150 – 300 min moderate cardio / week (WHO)\n\n");
        printf("  " DIM "XR Scene: " RESET YELLOW "Trail Run + Virtual Pool" RESET "\n");
    }
}

/* ── Intensity by fitness level ───────────────────────────────────── */
static void print_intensity(int age, int level)
{
    int mhr = 220 - age;
    printf("  " BOLD "Intensity Zone (Fitness Level):" RESET "\n\n");

    switch (level) {
        case 1:
            printf("  " GREEN BOLD "★☆☆  Beginner" RESET "\n");
            printf("   Session length  : 20 – 30 min\n"
                   "   Frequency       : 3 × / week\n"
                   "   Heart rate zone : 50 – 60%% of MHR  (%d – %d bpm)\n"
                   "   Key principle   : Consistency over intensity\n"
                   "   Rest between sets: 90 – 120 seconds\n",
                   (int)(0.50f * mhr), (int)(0.60f * mhr));
            break;
        case 2:
            printf("  " YELLOW BOLD "★★☆  Intermediate" RESET "\n");
            printf("   Session length  : 40 – 55 min\n"
                   "   Frequency       : 4 × / week\n"
                   "   Heart rate zone : 60 – 75%% of MHR  (%d – %d bpm)\n"
                   "   Key principle   : Progressive overload + intervals\n"
                   "   Rest between sets: 60 – 90 seconds\n",
                   (int)(0.60f * mhr), (int)(0.75f * mhr));
            break;
        case 3:
            printf("  " RED BOLD "★★★  Advanced" RESET "\n");
            printf("   Session length  : 60 – 90 min\n"
                   "   Frequency       : 5 × / week\n"
                   "   Heart rate zone : 75 – 90%% of MHR  (%d – %d bpm)\n"
                   "   Key principle   : HIIT, periodisation, sport-specific\n"
                   "   Rest between sets: 30 – 60 seconds (HIIT: minimal)\n",
                   (int)(0.75f * mhr), (int)(0.90f * mhr));
            break;
        default:
            printf("  " RED "[!] Invalid level — choose 1, 2, or 3.\n" RESET);
    }
}

/* ── 7-day schedule ──────────────────────────────────────────────── */
static void print_weekly_schedule(float bmi, int level)
{
    /* Determine workout tags per BMI */
    const char *w1, *w2, *w3, *w4;
    if (bmi < BMI_UNDERWEIGHT) {
        w1 = "Upper Body Strength  (Chest/Back/Shoulders)";
        w2 = "Lower Body Strength  (Squats, Deadlifts, Lunges)";
        w3 = "Full Body Compound   (3 sets × 6-8 reps)";
        w4 = "Accessory + Core     (Biceps, Triceps, Abs)";
    } else if (bmi <= BMI_HEALTHY_MAX) {
        w1 = "Push Day             (Chest, Shoulders, Triceps)";
        w2 = "Cardio               (30-min run / cycle)";
        w3 = "Pull Day             (Back, Biceps, Rear Delts)";
        w4 = "Legs + Core          (Squats, RDL, Planks)";
    } else {
        w1 = "Cardio               (30-min brisk walk / cycle)";
        w2 = "Full Body Resistance (Bodyweight or low weight)";
        w3 = "Cardio + HIIT Intro  (20-min interval walk/jog)";
        w4 = "Resistance + Stretch (2 sets × 12–15 reps)";
    }

    const char *intensity = (level == 1) ? " (60%% intensity)" :
                            (level == 2) ? " (75%% intensity)" : " (90%% HIIT)";

    printf("\n  " BOLD "7-Day Weekly Schedule:" RESET "\n");
    printf("  ┌─────────────┬──────────────────────────────────────────────┐\n");
    printf("  │ Day         │ Session                                      │\n");
    printf("  ├─────────────┼──────────────────────────────────────────────┤\n");
    printf("  │ " GREEN "Monday" RESET "      │ %-44s │\n", w1);
    printf("  │ " DIM "Tuesday" RESET "     │ %-44s │\n", "Active Recovery  (15-min walk, stretching)");
    printf("  │ " GREEN "Wednesday" RESET "  │ %-44s │\n", w2);
    printf("  │ " GREEN "Thursday" RESET "   │ %-44s │\n", w3);
    printf("  │ " DIM "Friday" RESET "      │ %-44s │\n", "Rest or Yoga     (flexibility & mobility)");
    printf("  │ " GREEN "Saturday" RESET "   │ %-44s │\n", w4);
    printf("  │ " DIM "Sunday" RESET "      │ %-44s │\n", "Full Rest        (sleep, nutrition focus)");
    printf("  └─────────────┴──────────────────────────────────────────────┘\n");
    printf("  " DIM "All workout days at%s" RESET "\n", intensity);
}

/* ── Warm-up & Cool-down ─────────────────────────────────────────── */
static void print_warmup_cooldown(void)
{
    printf("\n  " BOLD "Warm-Up (5–8 min): " RESET "\n"
           "   1. Jumping jacks — 2 min\n"
           "   2. Arm circles (forward + back) — 30 sec each\n"
           "   3. Hip circles — 30 sec each direction\n"
           "   4. Leg swings (front/back, side) — 30 sec each\n"
           "   5. High knees — 1 min\n");

    printf("\n  " BOLD "Cool-Down (5–8 min): " RESET "\n"
           "   1. Standing quad stretch — 30 sec each leg\n"
           "   2. Seated hamstring stretch — 45 sec each\n"
           "   3. Chest opener + shoulder stretch — 30 sec each\n"
           "   4. Child's pose — 1 min\n"
           "   5. Diaphragmatic breathing — 2 min\n");
}

/* ── API wrappers ────────────────────────────────────────────────── */

void recommend_exercise(int age, float bmi, int fitness_level)
{
    print_exercise_type(bmi);
    HR();
    print_intensity(age, fitness_level);
}

void display_exercise_plan(const UserProfile *user)
{
    int fitness_level;

    SECTION("EXERCISE RECOMMENDATION");
    printf("  Select fitness level:\n"
           "  " GREEN "  1. Beginner"      RESET "\n"
           "  " YELLOW "  2. Intermediate" RESET "\n"
           "  " RED    "  3. Advanced"     RESET "\n\n"
           "  Your choice: ");
    scanf("%d", &fitness_level);
    printf("\n");

    recommend_exercise(user->age, user->bmi, fitness_level);

    HR();
    print_weekly_schedule(user->bmi, fitness_level);
    HR();
    print_warmup_cooldown();

    printf("\n  " BOLD "Recovery Pillars:" RESET "\n"
           "   • Sleep 7 – 9 hours — primary anabolic window\n"
           "   • Protein within 30–60 min post-workout\n"
           "   • Stay hydrated: 500 ml water pre-workout + replace losses\n"
           "   • Foam roll / massage gun on sore areas daily\n");

    printf("\n  " DIM "XR Layer : workout schedule ready for Virtual Gym scene mapping.\n" RESET);
}
