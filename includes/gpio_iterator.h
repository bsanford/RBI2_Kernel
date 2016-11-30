#ifndef GPIO_ITERATOR_H_INCLUDED
#define GPIO_ITERATOR_H_INCLUDED
#include <stdbool.h>
#include "gpio.h"


/**This needs to be improved to be general purpose
  *
  *In this case just using for GPIO but should be mostly void
  *pointers with casts. To make it generalized.
  */
struct gpio_itor{
    int nodes;
    int cur_index;
    struct gpio_pin *cur_node;
    struct gpio_pin *first;
    struct gpio_pin *(* get_next)(struct gpio_itor *self);
    bool (* has_next)(struct gpio_itor *self);
    bool (* is_done) (struct gpio_itor *self);
};

#endif // GPIO_ITERATOR_H_INCLUDED
