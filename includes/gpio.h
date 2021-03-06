#include "mutex.h"
/**Modified from valvers.com tutorials
*
* Location offsets for the Broadcom BCM2836
* ARM peripheral.
*/


#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

#define GPIO_BASE       0x3F200000UL
#define PIN_SET_SIZE    53


/*Function select Registers*/
#define GPIO_GPFSEL0    0
#define GPIO_GPFSEL1    1
#define GPIO_GPFSEL2    2
#define GPIO_GPFSEL3    3
#define GPIO_GPFSEL4    4
#define GPIO_GPFSEL5    5


#define GPIO_GPSET0     7
#define GPIO_GPSET1     8

#define GPIO_GPCLR0     10
#define GPIO_GPCLR1     11

#define GPIO_GPLEV0     13
#define GPIO_GPLEV1     14

#define GPIO_GPEDS0     16
#define GPIO_GPEDS1     17

#define GPIO_GPREN0     19
#define GPIO_GPREN1     20

#define GPIO_GPFEN0     22
#define GPIO_GPFEN1     23

#define GPIO_GPHEN0     25
#define GPIO_GPHEN1     26

#define GPIO_GPLEN0     28
#define GPIO_GPLEN1     29

#define GPIO_GPAREN0    31
#define GPIO_GPAREN1    32

#define GPIO_GPAFEN0    34
#define GPIO_GPAFEN1    35

#define GPIO_GPPUD      37
#define GPIO_GPPUDCLK0  38
#define GPIO_GPPUDCLK1  39

/**Defines for the function GPIO function select mask
*000 = GPIO Pin is an input
 001 = GPIO Pin is an output
 100 = GPIO Pin alternative funct 0
 101 = GPIO pin alternative funct 1
 110 = GPIO pin alternative funct 2
 111 = GPIO pin alterative  funct 3
 011 = GPIO pin alternative funct 4
 010 = GPIO pin alternative funct 5
 */

#define INPUT 0 /*Set GPIO Pin to input --Always on INIT*/
#define OUTPUT 1 /*Set GPIO pin to output*/
#define ALTFIVE 2 /*Set GPIO pint to Alternative function five*/
#define ALTFOUR 3  /*. . .*/
#define ALTZERO 4
#define ALTONE 5
#define ALTTWO 6
#define ALTHREE 7





/*Defines for the Mini UART Peripheral, used in conjunction with GPIO pins*/





/**Structure will hold the GPIO Pin data
  such that each pin object can be initialized
  in a 52 element array. Each pin will be able to be locked
  and set up for each type of usage as specified in the
  Broadcom BCM2836 Arm Peripherals*/

 struct gpio_pin{
    unsigned int p_nmb; /*The GPIO Pin number*/
    volatile unsigned int *fnc_slt; /*Its associated function select*/
    volatile unsigned int *funct_mask;   /*Function mask - initializes to gpio_in*/
    volatile unsigned int *gpio_out_reg;  /*Register location for ouputs*/
    volatile unsigned int *gpio_clr_reg;  /*Register location to clear the outputs*/
    volatile unsigned int *gpio_lvl_reg; /*Register_to_detect the pin lvl;*/
    volatile unsigned int *gpio_up_dn_clk; /* Register for gpio clock signal */
    volatile unsigned int *gpio_pupdown; /*Register to control the GPIO pull up down*/
    volatile unsigned int *gpio_low_dtct;  /*Low Level Detect Register - sets evnt detect*/
    volatile unsigned int *evnt_dtct;        /*Event Register, used for irq */
    struct mutex hw_lock;           /*mutex lock*/
};


/*Holds the set of GPIO pins for use by the system*/
struct gpio_pin pin_set[PIN_SET_SIZE];

/*Initialize the set of gpio_pins for system use*/
int init_gpio(struct gpio_pin *pin_arr, unsigned int size);

#endif // GPIO_H_INCLUDED
