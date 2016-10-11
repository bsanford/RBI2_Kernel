#include "gpio.h"




/*Function init_gpio
 *Braeden Sanford 10-11-2016
 *
 *Args: *pin_arr pointer to the start of the gpio_pin set
 *       size - size of the the array (52 elements)
 *
 *       Loops over the array set and does any initialization for static
 *       register location offsets.
 */


int init_gpio(struct gpio_pin *pin_arr, int size){

if(pin_arr == NULL)
    return -1;

return 0;
}



int set_pin_func(struct gpio_pin *pin){

return 0;
}


int get_pin_val(struct gpio_pin *pin){
return 0;
}_


int is_mtex(struct gpio_pin *pin){

 return pin->mtex;
}
