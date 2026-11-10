#include "global.h"

/* Current application mode */
AppMode app_mode = MODE_NORMAL;

/* Configured traffic-light durations, in seconds */
uint8_t temp_value = 5; // Khởi tạo mặc định
uint8_t duration_red = DEFAULT_RED_SECONDS;
uint8_t duration_amber = DEFAULT_AMBER_SECONDS;
uint8_t duration_green = DEFAULT_GREEN_SECONDS;

/* Four-digit seven-segment display buffer */
uint8_t display_digits[4] = {0, 0, 0, 0};

/* Current traffic-light FSM state */
int status = PHASE_A_GREEN;
