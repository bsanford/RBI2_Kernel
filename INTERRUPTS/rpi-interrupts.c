#include<stdio.h>
#include "rpi-armtimer.h"
#include "rpi-interrupts.h"
#include "user_cntrl.h"

/** @brief The BCM2835/6 Interupt controller peripheral at it's base address */
static rpi_irq_controller_t* rpiIRQController =
        (rpi_irq_controller_t*)RPI_INTERRUPT_CONTROLLER_BASE;



/*TODO Needs to go into its own source file with other ARM inline assember functions */
/** Function get_cpsr
 *
 * @brief returns the ARM specific CPSR (current program status register)
 *
 * @note used to detect current processor modes and flags, see arm v7 architecture manual
 *
 * @return value stored in the cpsr reg
 */
int get_cpsr(void){

     unsigned int cpsr_reg;
     __asm__ __volatile__("mrs %0, cpsr" : "=r" (cpsr_reg));
     return cpsr_reg;
}




/**Function get_spsr
 * @brief fetches the ARM spsr (banked cpsr register)
 *
 * @return 32 bit value of the ARM spsr register
 */
int get_spsr(void){

    unsigned int spsr_reg;
    __asm__ __volatile__("mrs %0, spsr" : "=r" (spsr_reg));

    return spsr_reg;
}







/**Function RPI_GetIrqController
    @brief Return the IRQ Controller register set

    @return the pointer to the rpi_irq_controller_t structure
*/
rpi_irq_controller_t* RPI_GetIrqController( void )
{
    return rpiIRQController;
}




void irq_handler(void){
    rpi_irq_controller_t *irqctl = RPI_GetIrqController();
    struct gpio_api_funcs *gpio;
    /**
     * @brief GPIO event has happened on bank1 in this case there is only one
     *        this is the low level detect on line 21. Which is the reset button
     *        for the system.
     */
    if(irqctl->IRQ_pending_2 & IRQ_GPIO_ENABLE_B0){
        printf("Reset detected, jumping to reset vector \r \n");
        gpio = init_gpio_api_funcs();
        gpio->clr_evnt(gpio->itor.get_node_at_index(&(gpio->itor),21));
        _soft_reset();
    }




    printf("Undefined IRQ exception \r \n");
}



/**
    @brief The Reset vector interrupt handler

    This can never be called, since an ARM core reset would also reset the
    GPU and therefore cause the GPU to start running code again until
    the ARM is handed control at the end of boot loading
*/
void __attribute__((interrupt("ABORT"))) reset_vector(void) {

    printf("In Abort vector \r \n");
    while(1);
}

/**
    @brief The undefined instruction interrupt handler

    If an undefined intstruction is encountered, the CPU will start
    executing this function. Just trap here as a debug solution.
*/
void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void) {
    printf("In Undef instruction vector \r \n");
    while(1);
}


/**
    @brief The supervisor call interrupt handler

    The CPU will start executing this function. Just trap here as a debug
    solution.
*/
void __attribute__((interrupt("SWI"))) software_interrupt_vector(void) {
    printf("In software interrupt vector");
    while(1);
}


/**
    @brief The prefetch abort interrupt handler

    The CPU will start executing this function. Just trap here as a debug
    solution.
*/
void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void)
{
    printf("In prefetch abort vector \r \n");
    while(1);

}


/**
    @brief The Data Abort interrupt handler

    The CPU will start executing this function. Just trap here as a debug
    solution.
*/
void __attribute__((interrupt("ABORT"))) data_abort_vector(void)
{

    printf("In data abort vector \r \n");

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
void __attribute__((interrupt("FIQ")))fast_interrupt_vector(void)
{
    printf("In FIQ vector \r \n");
    while (1);
}
