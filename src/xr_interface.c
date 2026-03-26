/*
 * xr_interface.c
 * ───────────────────────────────────────────────────────────────────────
 * XR Integration Abstraction — Stub Implementations
 *
 * All functions write trace records to logs/xr_telemetry.log.
 * Replace function bodies with real XR SDK calls
 * when an XR hardware target is available.
 *
 * XR_EXTENSION_POINT markers show exactly where SDK calls go.
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/xr_interface.h"
#include "../include/data_logger.h"

/* ── Internal telemetry writer ───────────────────────────────────── */
static void xr_log(const char *func, const char *msg)
{
    FILE *fp = fopen(XR_TELEMETRY_PATH, "a");
    if (!fp) return;

    char ts[32];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(ts, sizeof(ts), "%Y-%m-%dT%H:%M:%S", t);

    fprintf(fp, "[%s] XR::%s → %s\n", ts, func, msg);
    fclose(fp);
}

/* ── API Implementations ─────────────────────────────────────────── */

int xr_init(XRSession *session, XRDisplayMode mode)
{
    if (!session) return -1;

    session->mode            = mode;
    session->hud_enabled     = 1;
    session->haptic_enabled  = 0;  /* disabled until hardware linked */
    session->ambient_intensity = 0.85f;
    memset(&session->tracking, 0, sizeof(XRBodyTracking));

    switch (mode) {
        case XR_MODE_AR_OVERLAY:   strncpy(session->scene_name, "AR Overlay",       63); break;
        case XR_MODE_VR_IMMERSIVE: strncpy(session->scene_name, "Virtual Gym",     63); break;
        case XR_MODE_HOLOGRAPHIC:  strncpy(session->scene_name, "Holo Dojo",       63); break;
        default:                   strncpy(session->scene_name, "CLI Dashboard",   63); break;
    }
    session->scene_name[63] = '\0';

    /* XR_EXTENSION_POINT: xrCreateInstance(), xrCreateSession(), xrCreateSwapchain() */
    xr_log("init", session->scene_name);

    return 0;   /* 0 = success */
}

void xr_send_metrics(const XRSession *session, const XRFitnessMetrics *metrics)
{
    if (!session || !metrics) return;

    char msg[256];
    snprintf(msg, sizeof(msg),
             "BMI=%.2f BMR=%.2f Cal=%.0f Stamina=%.2f Category='%s'",
             metrics->bmi, metrics->bmr, metrics->recommended_calories,
             metrics->stamina_score, metrics->bmi_category);

    /* XR_EXTENSION_POINT: update HUD widget data buffers, signal XR render thread */
    xr_log("send_metrics", msg);
}

void xr_render_overlay(const XRSession *session, const char *label, const char *value)
{
    if (!session) return;

    char msg[256];
    snprintf(msg, sizeof(msg), "overlay label='%s' value='%s'", label, value);

    /* XR_EXTENSION_POINT: xrEndFrame() billboard panel with label/value text */
    xr_log("render_overlay", msg);
}

void xr_haptic_pulse(const XRSession *session, int hand, float intensity_pct, float duration_ms)
{
    if (!session) return;

    char msg[128];
    snprintf(msg, sizeof(msg), "hand=%d intensity=%.1f%% duration=%.0fms",
             hand, intensity_pct, duration_ms);

    /* XR_EXTENSION_POINT: XrHapticVibration → xrApplyHapticFeedback() */
    xr_log("haptic_pulse", msg);
}

void xr_update_tracking(XRSession *session)
{
    if (!session) return;

    /* XR_EXTENSION_POINT: poll xrLocateViews(), hand-tracking extension,
       heart-rate BLE characteristic, or IMU driver. */
    xr_log("update_tracking", "poll sensors (stub — returning zeros)");
    /* Tracking data remains zeroed in stub mode */
}

void xr_teardown(XRSession *session)
{
    if (!session) return;

    /* XR_EXTENSION_POINT: xrDestroySession(), xrDestroyInstance() */
    xr_log("teardown", session->scene_name);
    memset(session, 0, sizeof(XRSession));
}
