#ifndef LED_H
#define LED_H
#include "global.h"
#include "main.h"
void led_all_off(void);
void led_set_traffic(uint8_t ra, uint8_t ya, uint8_t ga, uint8_t rb, uint8_t yb, uint8_t gb);
void led_set_status(uint8_t on);
void set_on_4digits(void);
void unable_4digit(void);
void display_set_number(uint8_t index, uint8_t value);
void display_set_pair(uint8_t left_value, uint8_t right_value);
void display_number(int number);
void enable_digit(int digit);
void display_a_digit(int digit, int number);
void display_4digits(void);
void display_scan(void);
#endif
