#ifndef GLOBAL_H
#define GLOBAL_H

#include "main.h"
#include <stdint.h>

/* GPIO logic levels */
#define SEGMENT_ON_LEVEL     GPIO_PIN_SET
#define SEGMENT_OFF_LEVEL    GPIO_PIN_RESET
#define DIGIT_ENABLE_LEVEL   GPIO_PIN_RESET  /* Active-low for common-cathode displays */
#define DIGIT_DISABLE_LEVEL  GPIO_PIN_SET

/* Timing and duration configuration */
#define BUTTON_SCAN_MS       10U
#define DEBOUNCE_SAMPLES     2U

#define DEFAULT_RED_SECONDS  5U
#define DEFAULT_AMBER_SECONDS 3U
#define DEFAULT_GREEN_SECONDS 2U

#define MIN_DURATION_SECONDS 1U
#define MAX_DURATION_SECONDS 99U

#define NO_OF_DIGITS     6U   /* Tổng cộng 5 LED */
#define MODE_DIGIT_INDEX 4U

/* Application modes selected by the mode button */
extern uint8_t temp_value;
typedef enum {
    MODE_NORMAL = 1,
    MODE_SET_RED,
    MODE_SET_AMBER,
    MODE_SET_GREEN
} AppMode;

/* Button identifiers */
typedef enum {
    BTN_MODE = 0,
    BTN_UP,
    BTN_SET,
    BTN_COUNT  /* Bằng 3 */
} ButtonId;

/* Traffic-light FSM states stored in status */
enum {
    PHASE_A_GREEN = 0,
    PHASE_A_AMBER,
    PHASE_B_GREEN,
    PHASE_B_AMBER
};

/* Current application mode */
extern AppMode app_mode;

/* Configured traffic-light durations, in seconds */
extern uint8_t duration_red, duration_amber, duration_green;

/* Four-digit seven-segment display buffer */
extern uint8_t display_digits[4];

/* Current traffic-light FSM state */
extern int status;

#endif /* GLOBAL_H */
