#include <stddef.h>
#include "gpio_api.h"

/*Function: send_gpio_sig
 * GIven a GPIO pin structure the function will
 * write a one to the GPIO out register
 */
int send_gpio_sig(struct gpio_pin *pin){

    if(pin == NULL)
        return (-1);

    *(pin->gpio_out_reg) = (1 << (pin->p_nmb));

    return (0);
}



/*Function: clear_gpio_sig
 *Given a GPIO pin structure the function will
 *write a one to its location in the the clear
 *register
 */
int clear_gpio_sig(struct gpio_pin *pin){
    if(pin == NULL)
        return (-1);

     *(pin->gpio_clr_reg) = (1 << (pin->p_nmb));
     return (0);

}


/*Function: set_gpio_fnct
 *Given a gpio_pin and its associated GPIO function
 *this will take the modulus of the pin number and which finds lower
 * order bits of its mapping in its function slelect location. Function
 * will then write the GPIO function assignment to the particular register:
 *
 */

int set_gpio_fnct(struct gpio_pin *pin, int pin_fnc)
{
   int fun_reg_bits;
   if(pin == NULL)
        return -1;

   fun_reg_bits = pin->p_nmb % 10;

   switch(fun_reg_bits){

   case 0:
    *(pin->fnc_slt) |= (pin_fnc << 0);
    break;

   case 1:
    *(pin->fnc_slt) |= (pin_fnc << 3);
    break;

   case 2:
    *(pin->fnc_slt) |= (pin_fnc << 6);
    break;

   case 3:
    *(pin->fnc_slt) |= (pin_fnc << 9);
    break;

   case 4:
    *(pin->fnc_slt) |= (pin_fnc << 12);
    break;

   case 5:
    *(pin->fnc_slt) |= (pin_fnc << 15);
    break;
   case 6:
    *(pin->fnc_slt) |= (pin_fnc << 18);
    break;

   case 7:
    *(pin->fnc_slt) |= (pin_fnc << 21);
    break;

   case 8:
    *(pin->fnc_slt) |= (pin_fnc << 24);
    break;

   case 9:
    *(pin->fnc_slt) |= (pin_fnc << 27);
    break;

   default:
    return (-1);
   }
    return(0);

}


