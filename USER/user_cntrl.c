#include<stdio.h>
#include<stdbool.h>
#include "user_cntrl.h"
#include "gpio_api.h"
#include "sys_time.h"
#include "rpi-interrupts.h"
#include "rpi-armtimer.h"

#define PIN18_ON "GPIO_18_ON"
#define PIN18_OFF "GPIO_18_OFF"
#define PIN20_ON "GPIO_20_ON"
#define PIN20_OFF "GPIO_20_OFF"
#define PIN23_ON  "GPIO_23_ON"
#define PIN23_OFF "GPIO_23_OFF"
#define CHMAS     "MERRY_CMAS"

void sleep(uint32_t micros){

  volatile uint32_t curr = (get_sys_clock()->lo_32bits);

  while((get_sys_clock()->lo_32bits - curr) < micros);

}




static bool str_match(char *buffer, int buf_len, char *match_string, int mtch_len){

int index;
for(index = 0; index < mtch_len; index++){
  if((buffer[index] != match_string[index]) || index >= buf_len)
    return false;

}
  return true;

}


/** blink_led
 *
 *  @user - structure to the gpio_api_funcs
 *
 *  @pin -  the gpio pin to send a high sig and then a low sig
 *
 */

void blink_led(struct gpio_api_funcs *user,  struct gpio_pin *pin){

  user->set_gpio_pin_on(pin);

  sleep(500000);

  user->set_gpio_pin_off(pin);

}




/** Function blink_leds
 *
 *  @user - pointer to the gpio_api_funcs
 *
 *  @pin1 - pointer the gpio pin1
 *
 *  @pin2 - pointer to the gpio pin2
 *
 *  @pin3 - pointer to the gpio pin3
 *
 *  blink_leds will turn 3 pins on and off in consecutive order. Pin1 Pin2 Pin3.
 */
void blink_leds(struct gpio_api_funcs *user, struct gpio_pin *pin1, struct gpio_pin *pin2, struct gpio_pin *pin3){
blink_led(user, pin1);
blink_led(user, pin2);
blink_led(user, pin3);
}






/**Function: merry_xmas
  * @user - pointer to the gpio_api_funcs structure
  *
  * A function that sends a 3.3v signal to different gpio pins.
  * this function assumes that the pins are hooked up to the
  * an LED on the GPIO rail.
  */
void merry_xmas(struct gpio_api_funcs *user){

int count = 0;

struct gpio_pin *pin1 = user->itor.get_node_at_index(&(user->itor), 18);
struct gpio_pin *pin2 = user->itor.get_node_at_index(&(user->itor), 20);
struct gpio_pin *pin3 = user->itor.get_node_at_index(&(user->itor), 23);


while (count < 10){

blink_leds(user, pin1, pin2, pin3);
blink_leds(user, pin2, pin1, pin3);
blink_leds(user, pin1, pin3, pin2);
blink_leds(user, pin2, pin3, pin1);
blink_leds(user, pin3, pin1, pin2);
blink_leds(user, pin3, pin2, pin1);

count++;
}

}




/** gpio_sys calls that will execute
 *  different system calls for each
 *  command recieved by the uart
 *
 * Pre-conditions Uart must be initialized to send data or this will not work
 * correctly.
 *
 * This function is basically some a test code that allows the system to interact with
 * the GPIO facade.
 *
 * Naive parser just to test different GPIO pins accepting commands from a UART and lighting LEDs
 * on a bread board
 */
void gpio_sys(void){
    struct gpio_api_funcs *user = init_gpio_api_funcs();

    user->init_gpio();

    user->init_uart_pins(user->itor.get_node_at_index(&(user->itor), 14), user->itor.get_node_at_index(&(user->itor), 15)); // Need to init the uart before the pins

    user->mini_uart_init(115200, 8);

    int cpsr_reg;

 int len = 30;
 char buffer[len]; /*Character buffer for the buffered read */
       //Initialize the Uart for reading and writing;'
   printf("\r \n");
   printf("Welcome to the GPIO controller Interface \r \n");

      cpsr_reg = get_cpsr();

    printf("initial CPSR = %d  \r \n", cpsr_reg);

     rpi_arm_timer_t *mytime  = RPI_GetArmTimer();
     rpi_irq_controller_t *myirq = RPI_GetIrqController();


    myirq->Enable_Basic_IRQs = RPI_BASIC_ARM_TIMER_IRQ;
    mytime->Load = 0x4000;
    mytime->Control = (RPI_ARMTIMER_CTRL_23BIT | RPI_ARMTIMER_CTRL_ENABLE | RPI_ARMTIMER_CTRL_INT_ENABLE | RPI_ARMTIMER_CTRL_PRESCALE_256);
    _enable_interrupts();

     cpsr_reg = get_cpsr();
     printf("Secondary CPSR = %d \r \n", cpsr_reg);

 while(1){

     //printf("IRQ Flag = %lu \r \n", mytime->RAWIRQ);

        printf("Please Enter a Command-> \r \n");
        uart_buff_read(buffer, len, ';');
        printf("Command -> %s received \r \n", buffer);

        if(str_match(buffer, len, PIN18_ON, 10)){
           printf("Setting GPIO Pin 18 to on \r \n");
           user->set_gpio_pin_on(user->itor.get_node_at_index(&(user->itor), 18));  //Uses the iterator in the GPIO API to access the pin
           continue;
        }

          if(str_match(buffer, len, PIN20_ON, 10)){
           printf("Setting GPIO Pin 20 to on \r \n");
           user->set_gpio_pin_on(user->itor.get_node_at_index(&(user->itor), 20));
           continue;
        }


          if(str_match(buffer, len, PIN23_ON, 10)){
           printf("Setting GPIO Pin 23 to on \r \n");
           user->set_gpio_pin_on(user->itor.get_node_at_index(&(user->itor), 23));
           continue;
        }


        if (str_match(buffer, len, PIN18_OFF, 11 )){
            printf("Clearning 3.3v signal from pin 18 \r \n");
            user->set_gpio_pin_off(user->itor.get_node_at_index(&(user->itor), 18));
            continue;
        }


         if (str_match(buffer, len, PIN20_OFF, 11 )){
            printf("Clearning 3.3v signal from pin 20 \r \n");
            user->set_gpio_pin_off(user->itor.get_node_at_index(&(user->itor), 20));
            continue;
        }

        if (str_match(buffer, len, PIN23_OFF, 11 )){

            printf("Clearning 3.3v signal from pin 23 \r \n");
            user->set_gpio_pin_off(user->itor.get_node_at_index(&(user->itor), 23));
            continue;
        }

        if(str_match(buffer, len, CHMAS, 10)){
            printf("Happy Holidays! \r \n");
            merry_xmas(user);
            continue;

        }

         printf("Unkonwn command -> %s \r \n", buffer);


 }

}
