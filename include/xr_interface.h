/*
 * xr_interface.h
 * ───────────────────────────────────────────────────────────────────────
 * XR Integration Abstraction Layer — Athletic Assistant XR
 *
 * This header defines the contract between the core fitness engine and the
 * XR display/interaction platform. All implementations here are stubs that
 * write to a telemetry log, ready to be replaced with a real XR SDK
 * (e.g. OpenXR, WebXR, Unity XR Toolkit, or custom hardware driver).
 *
 * To enable real XR, compile with -DXR_ENABLED and link your XR SDK.
 *
 * Extension Points (grep "XR_EXTENSION_POINT"):
 *   xr_init()          → initialise headset / AR overlay
 *   xr_send_metrics()  → push live fitness data to XR HUD
 *   xr_render_overlay()→ draw contextual 3-D annotations
 *   xr_haptic_pulse()  → trigger controller / glove haptic feedback
 *   xr_teardown()      → graceful XR session shutdown
 *
 * Project: Athletic Assistant — Fitness Automation System XR
 * Team   : Ayyan Eqbal, Intekhab Ahmad, Md Hassan, Adeeeb Asif
 */

#ifndef XR_INTERFACE_H
#define XR_INTERFACE_H

#include <stdint.h>

/* ── Display modes ──────────────────────────────────────────────── */
typedef enum {
    XR_MODE_CLI         = 0,   /* Terminal UI (default / stub mode)   */
    XR_MODE_AR_OVERLAY  = 1,   /* Augmented Reality heads-up display  */
    XR_MODE_VR_IMMERSIVE= 2,   /* Full VR immersive workout scene     */
    XR_MODE_HOLOGRAPHIC = 3,   /* Mixed-reality holographic projection */
} XRDisplayMode;

/* ── Body tracking stub (future: IMU / depth-camera feed) ────────── */
typedef struct {
    float head_pitch_deg;    /* Head tilt from horizon             */
    float head_yaw_deg;      /* Head rotation left/right           */
    float left_hand_x;       /* Controller / glove position X      */
    float left_hand_y;
    float right_hand_x;
    float right_hand_y;
    float heart_rate_bpm;    /* Wearable HR sensor feed            */
    float calories_burned;   /* Live caloric expenditure estimate  */
} XRBodyTracking;

/* ── XR Workout Scene descriptor ─────────────────────────────────── */
typedef struct {
    XRDisplayMode mode;
    XRBodyTracking tracking;
    char   scene_name[64];     /* e.g. "Virtual Gym", "Trail Run"  */
    uint8_t hud_enabled;       /* 1 = metrics overlay active       */
    uint8_t haptic_enabled;    /* 1 = haptic feedback active       */
    float   ambient_intensity; /* Scene lighting (0.0 – 1.0)       */
} XRSession;

/* ── Live fitness metrics packet sent to XR HUD ──────────────────── */
typedef struct {
    float bmi;
    float bmr;
    float stamina_score;
    float recommended_calories;
    char  bmi_category[32];
    char  exercise_type[64];
} XRFitnessMetrics;

/* ── API ─────────────────────────────────────────────────────────── */

/**
 * xr_init() — Initialise XR session.
 * Stub: logs init event to logs/xr_telemetry.log.
 * Real: set up OpenXR instance, create session, load scene assets.
 */
int  xr_init(XRSession *session, XRDisplayMode mode);

/**
 * xr_send_metrics() — Push real-time fitness metrics to the XR HUD.
 * Stub: writes metrics to telemetry log.
 * Real: serialise to XR render thread message queue.
 */
void xr_send_metrics(const XRSession *session, const XRFitnessMetrics *metrics);

/**
 * xr_render_overlay() — Draw contextual 3-D annotation.
 * Stub: logs overlay request.
 * Real: submit billboard/panel draw call to XR compositor.
 */
void xr_render_overlay(const XRSession *session, const char *label, const char *value);

/**
 * xr_haptic_pulse() — Trigger haptic feedback on wearable/controller.
 * Stub: logs haptic event.
 * Real: call XrHapticVibration on target hand.
 */
void xr_haptic_pulse(const XRSession *session, int hand, float intensity_pct, float duration_ms);

/**
 * xr_update_tracking() — Poll body tracking sensors.
 * Stub: returns zeroed tracking data.
 * Real: read IMU / depth camera / hand-tracking SDK.
 */
void xr_update_tracking(XRSession *session);

/**
 * xr_teardown() — Tear down the XR session gracefully.
 * Stub: logs teardown event.
 * Real: destroy XrSession, XrInstance; free GPU resources.
 */
void xr_teardown(XRSession *session);

/* ── Convenience macro for reporting XR availability ─────────────── */
#ifdef XR_ENABLED
  #define XR_STATUS_STR "ACTIVE (XR SDK linked)"
#else
  #define XR_STATUS_STR "STUB   (CLI mode — compile with -DXR_ENABLED to enable)"
#endif

#endif /* XR_INTERFACE_H */
