#include "fsm_automatic.h"
#include "led.h"
#include "software_timer.h"

static uint8_t remain;

static void render_phase(void)
{
    switch (status) {
        case PHASE_A_GREEN:
            led_set_traffic(0, 0, 1, 1, 0, 0);
            break;
        case PHASE_A_AMBER:
            led_set_traffic(0, 1, 0, 1, 0, 0);
            break;
        case PHASE_B_GREEN:
            led_set_traffic(1, 0, 0, 0, 0, 1);
            break;
        default:
            led_set_traffic(1, 0, 0, 0, 1, 0);
            break;
    }
}

static uint8_t get_phase_duration(void)
{
    switch (status) {
        case PHASE_A_GREEN:
        case PHASE_B_GREEN:
            return duration_green;
        case PHASE_A_AMBER:
        case PHASE_B_AMBER:
            return duration_amber;
        default:
            return duration_green;
    }
}

static void update_countdown_display(void)
{
    uint8_t remain_a;
    uint8_t remain_b;

    switch (status) {
        case PHASE_A_GREEN:
            remain_a = remain;
            remain_b = (uint8_t)(remain + duration_amber);
            break;
        case PHASE_B_GREEN:
            remain_a = (uint8_t)(remain + duration_amber);
            remain_b = remain;
            break;
        case PHASE_A_AMBER:
        case PHASE_B_AMBER:
        default:
            remain_a = remain;
            remain_b = remain;
            break;
    }

    display_set_pair(remain_a, remain_b);
}

void fsm_automatic_init(void)
{
    status = PHASE_A_GREEN;
    remain = get_phase_duration();
    setTimer(1, 1000 / BUTTON_SCAN_MS);
    render_phase();
    update_countdown_display();
}

void fsm_automatic_run(void)
{
    if (isTimerExpired(1)) {
        if (remain > 0) {
            remain--;
        }

        if (remain == 0) {
            switch (status) {
                case PHASE_A_GREEN:
                    status = PHASE_A_AMBER;
                    break;
                case PHASE_A_AMBER:
                    status = PHASE_B_GREEN;
                    break;
                case PHASE_B_GREEN:
                    status = PHASE_B_AMBER;
                    break;
                default:
                    status = PHASE_A_GREEN;
                    break;
            }

            remain = get_phase_duration();
            render_phase();
        }

        update_countdown_display();
        setTimer(1, 1000 / BUTTON_SCAN_MS);
    }
}
