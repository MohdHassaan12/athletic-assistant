/*
 * data_logger.c
 * ─────────────────────────────────────────────────────────────────
 * Fitness session persistence — writes CSV records and provides
 * an in-app history viewer for the last N sessions.
 *
 * CSV columns:
 *   timestamp, user_name, bmi, bmr, stamina_score,
 *   recommended_calories, xr_mode
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "../include/data_logger.h"
#include "../include/athletic_assistant.h"

#define CSV_HEADER "timestamp,user_name,bmi,bmr,stamina_score,recommended_calories,xr_mode\n"

/* ─────────────────────────────────────────────────────────────────
   Internal helpers
   ───────────────────────────────────────────────────────────────── */

static int log_file_is_new(void)
{
    FILE *fp = fopen(SESSION_LOG_PATH, "r");
    if (!fp) return 1;   /* doesn't exist → new */
    fclose(fp);
    return 0;
}

/* ─────────────────────────────────────────────────────────────────
   Public API
   ───────────────────────────────────────────────────────────────── */

void logger_init(void)
{
    if (log_file_is_new()) {
        FILE *fp = fopen(SESSION_LOG_PATH, "w");
        if (fp) { fprintf(fp, CSV_HEADER); fclose(fp); }
    }
    /* XR telemetry log — append mode, no header needed */
    FILE *xr = fopen(XR_TELEMETRY_PATH, "a");
    if (xr) fclose(xr);
}

void logger_timestamp(char *buf, int buf_size)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buf, (size_t)buf_size, "%Y-%m-%dT%H:%M:%S", t);
}

void logger_record_session(const SessionRecord *rec)
{
    FILE *fp = fopen(SESSION_LOG_PATH, "a");
    if (!fp) return;

    fprintf(fp, "%s,%s,%.2f,%.2f,%.2f,%.2f,%s\n",
            rec->timestamp,
            rec->user_name,
            rec->bmi,
            rec->bmr,
            rec->stamina_score,
            rec->recommended_calories,
            rec->xr_mode);

    fclose(fp);
}

void logger_print_history(void)
{
    FILE *fp = fopen(SESSION_LOG_PATH, "r");
    if (!fp) {
        printf("  " YELLOW "No session history found yet.\n" RESET);
        return;
    }

    /* Collect all lines */
    char lines[MAX_HISTORY_ROWS + 2][256];
    int count = 0;
    while (fgets(lines[count], 256, fp) && count < MAX_HISTORY_ROWS + 1)
        count++;
    fclose(fp);

    if (count <= 1) {
        printf("  " YELLOW "No sessions recorded yet — start using the app!\n" RESET);
        return;
    }

    printf("\n  ┌───────────────────────────────────────────────────────────────────┐\n");
    printf("  │               " BOLD UNDERLINE "SESSION HISTORY (last %d)" RESET "                        │\n", MAX_HISTORY_ROWS);
    printf("  ├──────────────────┬────────────┬───────┬────────┬───────┬──────────┤\n");
    printf("  │ %-16s │ %-10s │ %5s │ %6s │ %5s │ %-8s │\n",
           "Timestamp", "Name", "BMI", "BMR", "Stam.", "XR Mode");
    printf("  ├──────────────────┼────────────┼───────┼────────┼───────┼──────────┤\n");

    /* Skip header (lines[0]), print the rest newest-first */
    int start = (count > MAX_HISTORY_ROWS) ? count - MAX_HISTORY_ROWS : 1;
    for (int i = start; i < count; i++) {
        char ts[32], name[50], xr_mode[32];
        float bmi, bmr, stam, cal;
        if (sscanf(lines[i], "%31[^,],%49[^,],%f,%f,%f,%f,%31[^\n]",
                   ts, name, &bmi, &bmr, &stam, &cal, xr_mode) == 7) {
            /* shorten timestamp to HH:MM:SS date */
            char short_ts[20];
            strncpy(short_ts, ts, 19); short_ts[19] = '\0';
            printf("  │ %-16s │ %-10s │ " CYAN "%5.2f" RESET " │ " CYAN "%6.0f" RESET " │ " CYAN "%5.1f" RESET " │ %-8s │\n",
                   short_ts, name, bmi, bmr, stam, xr_mode);
        }
    }
    printf("  └──────────────────┴────────────┴───────┴────────┴───────┴──────────┘\n");
}
