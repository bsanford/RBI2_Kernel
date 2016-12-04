
#include <stdint.h>
#include <stdbool.h>

#include "rpi-armtimer.h"
#include "rpi-interrupts.h"
#include "gpio_api.h"

/**TODO ----------
  *
  * The interrupt handler needs to be fixed.. I don't believe the address mapping in the assembler script
  *  maps correctly to the Cortex Arm v7. I still have to go back and read the architecture manual for that
  *  processor.
  *
  *
  *There are two main features that I would like to add to the interrupt handler.
  *    1.) Want to tie the reset vector to a GPIO line which contains a hardware switch
  *         In this way, can reset the code with out having to constantly power down the
  *         RBI2 hardware.
  *
  *    2.) Would like to define an error led on the bread board so when an error has occured the
  *        the system will pull the iterrupt handler line and blink the LED error.
  */


/** @brief The BCM2835/6 Interupt controller peripheral at it's base address */
static rpi_irq_controller_t* rpiIRQController =
        (rpi_irq_controller_t*)RPI_INTERRUPT_CONTROLLER_BASE;



volatile int calculate_frame_count = 0;

/**
    @brief Return the IRQ Controller register set
*/
rpi_irq_controller_t* RPI_GetIrqController( void )
{
    return rpiIRQController;
}


/**
    @brief The Reset vector interrupt handler

    This can never be called, since an ARM core reset would also reset the
    GPU and therefore cause the GPU to start running code again until
    the ARM is handed control at the end of boot loading
*/
void __attribute__((interrupt("ABORT"))) reset_vector(void)
{
    while( 1 )
    {
        send_gpio_sig(&pin_set[18]);
    }
}

/**
    @brief The undefined instruction interrupt handler

    If an undefined intstruction is encountered, the CPU will start
    executing this function. Just trap here as a debug solution.
*/
void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void)
{
    while( 1 )
    {
        /* Do Nothing! */
       send_gpio_sig(&pin_set[18]);
    }
}


/**
    @brief The supervisor call interrupt handler

    The CPU will start executing this function. Just trap here as a debug
    solution.
*/
void __attribute__((interrupt("SWI"))) software_interrupt_vector(void)
{
    while( 1 )
    {
        /* Do Nothing! */
        send_gpio_sig(&pin_set[18]);
    }
}


/**
    @brief The prefetch abort interrupt handler

    The CPU will start executing this function. Just trap here as a debug
    solution.
*/
void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void)
{
    while( 1 )
    {
        send_gpio_sig(&pin_set[18]);
    }
}


/**
    @brief The Data Abort interrupt handler

    The CPU will start executing this function. Just trap here as a debug
    solution.
*/
void __attribute__((interrupt("ABORT"))) data_abort_vector(void)
{
    while( 1 )
    {
        send_gpio_sig(&pin_set[18]);
    }
}


/**
    @brief The IRQ Interrupt handler

    This handler is run every time an interrupt source is triggered. It's
    up to the handler to determine the source of the interrupt and most
    importantly clear the interrupt flag so that the interrupt won't
    immediately put us back into the start of the handler again.
*/
void __attribute__((interrupt("IRQ"))) interrupt_vector(void)
{
    static int lit = 0;
       /* Clear the ARM Timer interrupt - it's the only interrupt we have
       enabled, so we want don't have to work out which interrupt source
       caused us to interrupt */
    RPI_GetArmTimer()->IRQClear = 1;


    /* Flip the LED */
    if( lit )
    {
        clear_gpio_sig(&pin_set[18]);
        lit = 0;
    }
    else
    {
        send_gpio_sig(&pin_set[18]);
        lit = 1;
    }
}


/**
    @brief The FIQ Interrupt Handler

    The FIQ handler can only be allocated to one interrupt source. The FIQ has
    a full CPU shadow register set. Upon entry to this function the CPU
    switches to the shadow register set so that there is no need to save
    registers before using them in the interrupt.

    In C you can't see the difference between the IRQ and the FIQ interrupt
    handlers except for the FIQ knowing it's source of interrupt as there can
    only be one source, but the prologue and epilogue code is quite different.
    It's much faster on the FIQ interrupt handler.

    The prologue is the code that the compiler inserts at the start of the
    function, if you like, think of the opening curly brace of the function as
    being the prologue code. For the FIQ interrupt handler this is nearly
    empty because the CPU has switched to a fresh set of registers, there's
    nothing we need to save.

    The epilogue is the code that the compiler inserts at the end of the
    function, if you like, think of the closing curly brace of the function as
    being the epilogue code. For the FIQ interrupt handler this is nearly
    empty because the CPU has switched to a fresh set of registers and so has
    not altered the main set of registers.
*/
void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void)
{

}
