#include "button.h"

#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

static volatile GPIO_PinState button_buffer[NUM_OF_BUTTONS];
static volatile uint8_t flag_for_button_press_1s[NUM_OF_BUTTONS];
static GPIO_PinState candidate_sample[NUM_OF_BUTTONS];
static uint8_t candidate_sample_count[NUM_OF_BUTTONS];
static uint16_t counter_for_button_press_1s[NUM_OF_BUTTONS];

static GPIO_PinState read_button_pin(uint8_t index)
{
    switch (index) {
        case BTN_MODE:
            return HAL_GPIO_ReadPin(btn0_GPIO_Port, btn0_Pin);
        case BTN_UP:
            return HAL_GPIO_ReadPin(btn1_GPIO_Port, btn1_Pin);
        case BTN_SET:
            return HAL_GPIO_ReadPin(btn2_GPIO_Port, btn2_Pin);
        default:
            return BUTTON_IS_RELEASED;
    }
}

void button_init_state(void)
{
    for (uint8_t i = 0; i < NUM_OF_BUTTONS; i++) {
        button_buffer[i] = BUTTON_IS_RELEASED;
        candidate_sample[i] = BUTTON_IS_RELEASED;
        candidate_sample_count[i] = 0U;
        flag_for_button_press_1s[i] = 0U;
        counter_for_button_press_1s[i] = 0U;
    }
}

void button_reading(void)
{
    for (uint8_t i = 0; i < NUM_OF_BUTTONS; i++) {
        GPIO_PinState sample = read_button_pin(i);

        if (sample != candidate_sample[i]) {
            candidate_sample[i] = sample;
            candidate_sample_count[i] = 1U;
        } else if (candidate_sample_count[i] < DEBOUNCE_SAMPLES) {
            candidate_sample_count[i]++;
        }

        if (candidate_sample_count[i] >= DEBOUNCE_SAMPLES &&
            button_buffer[i] != candidate_sample[i]) {
            button_buffer[i] = candidate_sample[i];
            counter_for_button_press_1s[i] = 0U;
            flag_for_button_press_1s[i] = 0U;
        }

        if (button_buffer[i] == BUTTON_IS_PRESSED) {
            const uint16_t hold_ticks =
                (uint16_t)(1000U / BUTTON_SCAN_MS);

            if (counter_for_button_press_1s[i] < hold_ticks) {
                counter_for_button_press_1s[i]++;
            } else {
                flag_for_button_press_1s[i] = 1U;
            }
        } else {
            counter_for_button_press_1s[i] = 0U;
            flag_for_button_press_1s[i] = 0U;
        }
    }
}

uint8_t is_button_pressed(uint8_t index)
{
    if (index >= NUM_OF_BUTTONS) {
        return 0U;
    }

    return button_buffer[index] == BUTTON_IS_PRESSED;
}

uint8_t is_button_pressed_1s(uint8_t index)
{
    if (index >= NUM_OF_BUTTONS) {
        return 0U;
    }

    return flag_for_button_press_1s[index] == 1U;
}
