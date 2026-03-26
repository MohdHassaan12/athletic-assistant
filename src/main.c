/*
 * main.c — Athletic Assistant: Fitness Automation System XR
 * ─────────────────────────────────────────────────────────────────
 * Entry point: XR boot sequence, user profile collection,
 * session-wrapped main menu loop, and auto-save on exit.
 *
 * Build: make          (CLI mode — XR stubs)
 *        make xr       (XR stubs visible in telemetry log)
 *
 * Project: Athletic Assistant — Fitness Automation System XR
 * Team   : Ayyan Eqbal, Intekhab Ahmad, Md Hassan, Adeeeb Asif
 * Version: 2.0.0
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/athletic_assistant.h"

/* ─────────────────────────────────────────────────────────────────
   Platform-portable clear
   ───────────────────────────────────────────────────────────────── */
static void clear_screen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* ─────────────────────────────────────────────────────────────────
   Banner & UI helpers
   ───────────────────────────────────────────────────────────────── */
static void print_banner(void)
{
    printf("\n");
    printf("  ╔══════════════════════════════════════════════════════╗\n");
    printf("  ║  " BOLD CYAN "  ⚡  ATHLETIC ASSISTANT — %s  ⚡" RESET "    ║\n", APP_VERSION);
    printf("  ║          " BOLD WHITE "%s" RESET "          ║\n", APP_SUBTITLE);
    printf("  ╚══════════════════════════════════════════════════════╝\n");
}

static void print_xr_status(const XRSession *xr)
{
    printf("  " DIM "XR Mode: %-18s │ Scene: %-20s" RESET "\n",
           XR_STATUS_STR, xr ? xr->scene_name : "—");
}

static void print_menu(const UserProfile *user)
{
    printf("\n");
    printf("  ┌─────────────────────────────────────────────────────┐\n");
    printf("  │  " BOLD "Welcome, %-10s" RESET "   BMI " CYAN "%.2f" RESET
           " (%s)%*s│\n",
           user->name, user->bmi, bmi_category_str(user->bmi),
           (int)(18 - strlen(bmi_category_str(user->bmi))), "");
    printf("  ├─────────────────────────────────────────────────────┤\n");
    printf("  │  " CYAN "[b]" RESET " BMI & BMR Analyser                             │\n");
    printf("  │  " CYAN "[w]" RESET " Weight Management Plan                         │\n");
    printf("  │  " CYAN "[s]" RESET " Stamina & VO₂ Max Test                         │\n");
    printf("  │  " CYAN "[d]" RESET " Personalised Diet Plan                         │\n");
    printf("  │  " CYAN "[e]" RESET " Exercise & Weekly Schedule                     │\n");
    printf("  │  " CYAN "[h]" RESET " Session History                                │\n");
    printf("  │  " RED  "[q]" RESET " Save & Quit                                    │\n");
    printf("  └─────────────────────────────────────────────────────┘\n");
    printf("  Choice: ");
}

/* ─────────────────────────────────────────────────────────────────
   XR boot sequence
   ───────────────────────────────────────────────────────────────── */
static void xr_boot_sequence(XRSession *xr)
{
    printf("\n  " BOLD CYAN "Initialising Fitness Automation System XR..." RESET "\n\n");

    /* Simulated boot log */
    const char *steps[] = {
        "Loading fitness engine            ",
        "Calibrating BMI/BMR module        ",
        "Initialising diet database        ",
        "Compiling exercise programmes     ",
        "Linking XR abstraction layer      ",
        "Starting session logger           ",
    };
    int n = (int)(sizeof(steps) / sizeof(steps[0]));
    for (int i = 0; i < n; i++) {
        printf("  %s [", steps[i]);
        int fill = ((i + 1) * 20) / n;
        for (int j = 0; j < 20; j++)
            printf("%s", j < fill ? GREEN "█" RESET : DIM "░" RESET);
        printf("] " GREEN "OK" RESET "\n");
    }

    xr_init(xr, XR_MODE_CLI);
    printf("\n  " GREEN "✓ System ready." RESET "  XR: " DIM XR_STATUS_STR RESET "\n\n");
}

/* ─────────────────────────────────────────────────────────────────
   Profile collection
   ───────────────────────────────────────────────────────────────── */
static void collect_profile(UserProfile *user)
{
    char emp;

    clear_screen();
    print_banner();
    printf("\n\n  Ready to power your fitness journey.\n\n");
    printf("  Enter your name: ");
    fgets(user->name, sizeof(user->name), stdin);
    int len = (int)strlen(user->name);
    if (len > 0 && user->name[len - 1] == '\n') user->name[len - 1] = '\0';

    clear_screen();
    print_banner();
    printf("\n\n  " BOLD "Hey %s," RESET " let's build your profile.\n\n", user->name);

    printf("  Gender (1 = Male / 2 = Female) : "); scanf("%d", &user->gender);
    printf("  Age (years)                    : "); scanf("%d", &user->age);
    printf("  Height (centimetres)           : "); scanf("%f", &user->height_cm);
    printf("  Weight (kilograms)             : "); scanf("%f", &user->weight);

    user->height_m    = user->height_cm / 100.0f;
    user->bmi         = calculate_bmi(user->weight, user->height_m);
    user->bmr         = calculate_bmr(user->gender, user->weight, user->height_cm, user->age);
    user->stamina_score   = 0.0f;
    user->rec_calories    = user->bmr * 1.375f;

    clear_screen();
    print_banner();
    printf("\n  " GREEN BOLD "✓ Profile saved!" RESET " Thank you, " BOLD "%s" RESET ".\n", user->name);
    printf("  BMI: " CYAN "%.2f" RESET "  |  BMR: " CYAN "%.0f kcal/day" RESET
           "  |  Category: " CYAN "%s" RESET "\n\n",
           user->bmi, user->bmr, bmi_category_str(user->bmi));
    printf("  Press Enter to continue...");
    scanf(" %c", &emp);
    clear_screen();
}

/* ─────────────────────────────────────────────────────────────────
   Session auto-save
   ───────────────────────────────────────────────────────────────── */
static void save_session(const UserProfile *user)
{
    SessionRecord rec;
    logger_timestamp(rec.timestamp, sizeof(rec.timestamp));
    strncpy(rec.user_name, user->name, 49); rec.user_name[49] = '\0';
    rec.bmi                  = user->bmi;
    rec.bmr                  = user->bmr;
    rec.stamina_score        = user->stamina_score;
    rec.recommended_calories = user->rec_calories;
    strncpy(rec.xr_mode, "CLI", 31);
    logger_record_session(&rec);
}

/* ─────────────────────────────────────────────────────────────────
   Main
   ───────────────────────────────────────────────────────────────── */
int main(void)
{
    UserProfile user;
    char        choice;
    char        emp;
    int         running = 1;

    /* Initialise logging and show boot sequence */
    clear_screen();
    logger_init();
    print_banner();
    xr_boot_sequence(&user.xr);

    printf("  Press Enter to begin...");
    fflush(stdout);
    getchar();

    collect_profile(&user);

    while (running) {
        print_banner();
        print_xr_status(&user.xr);
        print_menu(&user);

        scanf(" %c", &choice);
        getchar();

        clear_screen();
        print_banner();

        switch (choice) {
            case 'b':
                display_bmi_bmr(&user, &user.xr);
                break;

            case 'w':
                display_weight_plan(&user);
                break;

            case 's':
                display_stamina(&user);
                break;

            case 'd':
                display_diet_plan(&user);
                break;

            case 'e':
                display_exercise_plan(&user);
                break;

            case 'h':
                printf("\n");
                logger_print_history();
                break;

            case 'q':
                save_session(&user);
                xr_teardown(&user.xr);
                printf("\n  " GREEN BOLD "✓ Session saved." RESET "\n\n");
                printf("  " BOLD "%s" RESET ", thank you for using " CYAN BOLD "Athletic Assistant XR" RESET "!\n",
                       user.name);
                printf("  Keep pushing — every session counts. 💪\n\n");
                running = 0;
                continue;

            default:
                printf(RED "\n  [!] Unknown option. Use b/w/s/d/e/h/q.\n" RESET);
                break;
        }

        printf("\n\n  Press Enter to return to menu...");
        scanf(" %c", &emp);
        clear_screen();
    }

    return 0;
}
