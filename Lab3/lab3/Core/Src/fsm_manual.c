#include "fsm_manual.h"
#include "button.h"
#include "fsm_automatic.h"
#include "led.h"
#include "software_timer.h"

#define BLINK_TIMER 5
#define BLINK_HALF_PERIOD_TICKS (250U / BUTTON_SCAN_MS)

#define AUTO_REPEAT_MS 500U   /* giu nut UP > 1s: tu tang moi 500ms */

enum UpButtonState { UP_RELEASED, UP_PRESSED, UP_PRESSED_MORE_THAN_1_SECOND };

static uint8_t previous_mode_button;
static uint8_t previous_set_button;
static enum UpButtonState up_state = UP_RELEASED;
static uint32_t last_repeat_ms;
static AppMode blink_mode = MODE_NORMAL;
static uint8_t blink_on;

static void load_temp_value(void);

static void advance_setting_mode(void)
{
    switch (app_mode) {
        case MODE_NORMAL:
            app_mode = MODE_SET_RED;
            break;
        case MODE_SET_RED:
            app_mode = MODE_SET_AMBER;
            break;
        case MODE_SET_AMBER:
            app_mode = MODE_SET_GREEN;
            break;
        case MODE_SET_GREEN:
        default:
            app_mode = MODE_NORMAL;
            blink_mode = MODE_NORMAL;
            blink_on = 0U;
            fsm_automatic_init();
            break;
    }

    load_temp_value();
}


/* Gioi han cua gia tri tam, giu rang buoc DO = VANG + XANH va moi gia tri <= 99 */
static uint8_t get_min_value(void)
{
    if (app_mode == MODE_SET_RED) {
        return (uint8_t)(duration_amber + 1U);      /* xanh = do - vang >= 1 */
    }
    return (uint8_t)MIN_DURATION_SECONDS;
}

static uint8_t get_max_value(void)
{
    switch (app_mode) {
        case MODE_SET_AMBER:
            return (uint8_t)(MAX_DURATION_SECONDS - duration_green);
        case MODE_SET_GREEN:
            return (uint8_t)(MAX_DURATION_SECONDS - duration_amber);
        default:
            return (uint8_t)MAX_DURATION_SECONDS;
    }
}

/* Vao mode chinh: nap gia tri hien tai vao temp_value */
static void load_temp_value(void)
{
    switch (app_mode) {
        case MODE_SET_RED:
            temp_value = duration_red;
            break;
        case MODE_SET_AMBER:
            temp_value = duration_amber;
            break;
        case MODE_SET_GREEN:
            temp_value = duration_green;
            break;
        default:
            break;
    }
}

/* Nut UP: chi doi temp_value, KHONG dong vao duration_* */
static void increase_temp_value(void)
{
    if (app_mode == MODE_NORMAL) {
        return;
    }

    if (temp_value >= get_max_value()) {
        temp_value = get_min_value();               /* quay ve gia tri nho nhat */
    } else {
        temp_value++;
    }
}

/* Nut SET: luc nay moi ghi temp_value vao duration_* */
static void commit_temp_value(void)
{
    switch (app_mode) {
        case MODE_SET_RED:
            duration_red = temp_value;
            duration_green = (uint8_t)(duration_red - duration_amber);
            break;
        case MODE_SET_AMBER:
            duration_amber = temp_value;
            duration_red = (uint8_t)(duration_amber + duration_green);
            break;
        case MODE_SET_GREEN:
            duration_green = temp_value;
            duration_red = (uint8_t)(duration_green + duration_amber);
            break;
        default:
            break;
    }
}

static void update_setting_display(void)
{
    if (app_mode == MODE_NORMAL) {
        return;
    }

    display_set_pair(temp_value, temp_value);   /* mode da co LED rieng */
}

static void update_setting_leds(void)
{
    if (blink_mode != app_mode) {
        blink_mode = app_mode;
        blink_on = 1U;
        setTimer(BLINK_TIMER, (int)BLINK_HALF_PERIOD_TICKS);
    } else if (isTimerExpired(BLINK_TIMER)) {
        blink_on = !blink_on;
        setTimer(BLINK_TIMER, (int)BLINK_HALF_PERIOD_TICKS);
    }

    switch (app_mode) {
        case MODE_SET_RED:
            led_set_traffic(blink_on, 0U, 0U, blink_on, 0U, 0U);
            break;
        case MODE_SET_AMBER:
            led_set_traffic(0U, blink_on, 0U, 0U, blink_on, 0U);
            break;
        case MODE_SET_GREEN:
            led_set_traffic(0U, 0U, blink_on, 0U, 0U, blink_on);
            break;
        default:
            break;
    }
}

void fsm_for_input_processing(void)
{
    uint8_t mode_pressed = is_button_pressed(BTN_MODE);

    if (mode_pressed && !previous_mode_button) {
        advance_setting_mode();
    }
    previous_mode_button = mode_pressed;

    uint8_t set_pressed = is_button_pressed(BTN_SET);

    if (set_pressed && !previous_set_button) {
        commit_temp_value();
    }
    previous_set_button = set_pressed;

    switch (up_state) {
        case UP_RELEASED:
            if (is_button_pressed(BTN_UP)) {
                up_state = UP_PRESSED;
                increase_temp_value();
            }
            break;

        case UP_PRESSED:
            if (!is_button_pressed(BTN_UP)) {
                up_state = UP_RELEASED;
            } else if (is_button_pressed_1s(BTN_UP)) {
                up_state = UP_PRESSED_MORE_THAN_1_SECOND;
                last_repeat_ms = HAL_GetTick();
            }
            break;

        case UP_PRESSED_MORE_THAN_1_SECOND:
            if (!is_button_pressed(BTN_UP)) {
                up_state = UP_RELEASED;
            } else if ((uint32_t)(HAL_GetTick() - last_repeat_ms) >= AUTO_REPEAT_MS) {
                last_repeat_ms = HAL_GetTick();
                increase_temp_value();
            }
            break;
    }
}

void fsm_manual_init(void)
{
    app_mode = MODE_NORMAL;
    previous_mode_button = is_button_pressed(BTN_MODE);
    previous_set_button = is_button_pressed(BTN_SET);
    up_state = is_button_pressed(BTN_UP) ? UP_PRESSED : UP_RELEASED;
    blink_mode = MODE_NORMAL;
    blink_on = 0U;
    setTimer(BLINK_TIMER, (int)BLINK_HALF_PERIOD_TICKS);
}

void fsm_manual_run(void)
{
    if (app_mode == MODE_NORMAL) {
        return;
    }

    update_setting_leds();
    update_setting_display();
}