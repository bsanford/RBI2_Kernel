#include<stddef.h>
#include "gpio.h"

/*GPIO.c standard functionality for the gpio pin set*/





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

unsigned int index;

if(pin_arr == NULL)
    return -1;

/*TODO add in support for appropriate func select register*/
for(index = 0; index < size; index++){
    pin_arr[index].mtex = 0;
    pin_arr[index].p_nmb = index;
}
return 0;
}



int set_pin_func(struct gpio_pin *pin){

return 0;
}


int get_pin_val(struct gpio_pin *pin){
return 0;
}


int is_mtex(struct gpio_pin *pin){

 return pin->mtex;
}
