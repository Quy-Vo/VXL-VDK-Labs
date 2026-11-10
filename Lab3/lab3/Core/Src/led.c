#include "led.h"

#define NO_OF_DIGITS     6U
#define MODE_DIGIT_INDEX 4U   /* Vị trí bắt đầu của cụm hiển thị Mode */

static GPIO_TypeDef * const digit_ports[NO_OF_DIGITS] = {
    en0_GPIO_Port, en1_GPIO_Port, en2_GPIO_Port, en3_GPIO_Port, en4_GPIO_Port, en5_GPIO_Port
};
static const uint16_t digit_pins[NO_OF_DIGITS] = {
    en0_Pin, en1_Pin, en2_Pin, en3_Pin, en4_Pin, en5_Pin
};
static const uint16_t segment_pins[8] = {
    seg0_Pin, seg1_Pin, seg2_Pin, seg3_Pin,
    seg4_Pin, seg5_Pin, seg6_Pin, seg7_Pin
};
static const uint8_t digit_patterns[10] = {
    0x3FU, 0x06U, 0x5BU, 0x4FU, 0x66U,
    0x6DU, 0x7DU, 0x07U, 0x7FU, 0x6FU
};
static const uint16_t traffic_led_pins[6] = {
    r0_Pin, y0_Pin, g0_Pin, r1_Pin, y1_Pin, g1_Pin
};

static uint8_t digit_enabled[NO_OF_DIGITS] = {1U, 1U, 1U, 1U, 1U, 1U};
static uint8_t scan_index;
static uint32_t last_scan_ms;

static void disable_all_digits(void)
{
    for (uint8_t i = 0; i < NO_OF_DIGITS; i++) {
        HAL_GPIO_WritePin(digit_ports[i], digit_pins[i], DIGIT_DISABLE_LEVEL);
    }
}

static void turn_all_segments_off(void)
{
    for (uint8_t i = 0; i < 8U; i++) {
        HAL_GPIO_WritePin(GPIOA, segment_pins[i], SEGMENT_OFF_LEVEL);
    }
}

void set_on_4digits(void)
{
    for (uint8_t i = 0; i < NO_OF_DIGITS; i++) {
        digit_enabled[i] = 1U;
    }
}

void unable_4digit(void)
{
    for (uint8_t i = 0; i < NO_OF_DIGITS; i++) {
        digit_enabled[i] = 0U;
    }
    disable_all_digits();
}

void display_set_number(uint8_t index, uint8_t value)
{
    if (index >= 4U) return;
    display_digits[index] = value;
}

void display_set_pair(uint8_t left_value, uint8_t right_value)
{
    if (left_value > 99U) left_value = 99U;
    if (right_value > 99U) right_value = 99U;

    display_digits[0] = (uint8_t)(left_value / 10U);
    display_digits[1] = (uint8_t)(left_value % 10U);
    display_digits[2] = (uint8_t)(right_value / 10U);
    display_digits[3] = (uint8_t)(right_value % 10U);
}

void enable_digit(int digit)
{
    disable_all_digits();
    if (digit >= 0 && digit < (int)NO_OF_DIGITS) {
        HAL_GPIO_WritePin(digit_ports[digit], digit_pins[digit], DIGIT_ENABLE_LEVEL);
    }
}

void display_number(int number)
{
    if (number < 0 || number > 9) {
        turn_all_segments_off();
        return;
    }
    uint8_t pattern = digit_patterns[number];
    for (uint8_t i = 0; i < 8U; i++) {
        GPIO_PinState state = (pattern & (1U << i)) ? SEGMENT_ON_LEVEL : SEGMENT_OFF_LEVEL;
        HAL_GPIO_WritePin(GPIOA, segment_pins[i], state);
    }
}

void display_a_digit(int digit, int number)
{
    disable_all_digits();
    if (digit < 0 || digit >= (int)NO_OF_DIGITS || number < 0 || number > 9) {
        turn_all_segments_off();
        return;
    }
    display_number(number);
    HAL_GPIO_WritePin(digit_ports[digit], digit_pins[digit], DIGIT_ENABLE_LEVEL);
}

void display_4digits(void)
{
    uint8_t current_digit = scan_index;
    uint8_t value;

    if (current_digit == 4U) {
        /* LED thứ 5 (index 4): Hiển thị hàng chục của Mode (Luôn là số 0) */
        value = 0;
    } else if (current_digit == 5U) {
        /* LED thứ 6 (index 5): Hiển thị hàng đơn vị của Mode (1, 2, 3, 4) */
        value = (uint8_t)app_mode;
    } else {
        /* 4 LED đầu (index 0-3): Hiển thị thời gian đếm ngược */
        value = display_digits[current_digit];
    }

    if (digit_enabled[current_digit] && value <= 9U) {
        display_a_digit(current_digit, value);
    } else {
        disable_all_digits();
    }

    scan_index = (uint8_t)((scan_index + 1U) % NO_OF_DIGITS);
}

void display_scan(void)
{
    uint32_t now = HAL_GetTick();
    if ((uint32_t)(now - last_scan_ms) < 2U) return; /* Quét mỗi 2ms */
    last_scan_ms = now;
    display_4digits();
}

void led_all_off(void)
{
    led_set_traffic(0U, 0U, 0U, 0U, 0U, 0U);
}

void led_set_traffic(uint8_t ra, uint8_t ya, uint8_t ga, uint8_t rb, uint8_t yb, uint8_t gb)
{
    const uint8_t states[6] = {ra, ya, ga, rb, yb, gb};
    for (uint8_t i = 0; i < 6U; i++) {
        HAL_GPIO_WritePin(GPIOB, traffic_led_pins[i], states[i] ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

void led_set_status(uint8_t state)
{
    HAL_GPIO_WritePin(GPIOA, status_Pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
