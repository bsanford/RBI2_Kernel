#include <stddef.h>
#include "gpio_api.h"






int set_gpio_out(struct gpio_pin *pin, int pin_fnc)
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
