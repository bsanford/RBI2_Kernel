#ifndef GPIO_API_H_INCLUDED
#define GPIO_API_H_INCLUDED
#include "gpio.h"

int set_gpio_out(struct gpio_pin *pin);

int set_gpio_input(struct gpio_pin *pin);

int send_gpio_signal(struct gpio_pin *pin);

int get_signal(struct gpio_pin *pin);

int is_gpio_lvl_hgh(struct gpio_pin *pin);

int is_gpio_lvl_low(struct gpio_pin *pin);

int set_mutex(struct gpio_pin *pin);

#endif // GPIO_API_H_INCLUDED
