/*
 * data_logger.h
 * ─────────────────────────────────────────────────────────────────
 * Session persistence layer — logs user fitness sessions to CSV for
 * future XR data pipeline consumption (analytics, ML, trend tracking).
 *
 * Log file: logs/fitness_sessions.log
 * Format  : CSV (timestamp, name, bmi, bmr, stamina, calories, mode)
 */

#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#define SESSION_LOG_PATH  "logs/fitness_sessions.log"
#define XR_TELEMETRY_PATH "logs/xr_telemetry.log"
#define MAX_HISTORY_ROWS  20   /* rows shown in the history viewer */

/* ── Session record written to log ───────────────────────────────── */
typedef struct {
    char  timestamp[32];       /* ISO-8601 datetime string           */
    char  user_name[50];
    float bmi;
    float bmr;
    float stamina_score;       /* 0 if test not taken this session   */
    float recommended_calories;
    char  xr_mode[32];         /* XR display mode label              */
} SessionRecord;

/* ── API ─────────────────────────────────────────────────────────── */

/** Ensure log directory and file exist; write CSV header if new. */
void logger_init(void);

/** Append a session record to the CSV log. */
void logger_record_session(const SessionRecord *rec);

/** Pretty-print the last MAX_HISTORY_ROWS sessions to stdout. */
void logger_print_history(void);

/** Fill timestamp field with current local time (ISO-8601). */
void logger_timestamp(char *buf, int buf_size);

#endif /* DATA_LOGGER_H */
