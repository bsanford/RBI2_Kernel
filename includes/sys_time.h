#ifndef SYS_TIME_H_INCLUDED
#define SYS_TIME_H_INCLUDED



#include<stdint.h>

struct sys_time_reg{
    volatile uint32_t  lo_32bits;
    volatile uint32_t  hi_32bits;
    volatile uint32_t  time_cmpr_0;
    volatile uint32_t  time_cmpr_1;
    volatile uint32_t  time_cmpr_2;
    volatile uint32_t  time_cmpr_3;

};



/*Function: get_sys_time
 *
 *Returns the singleton address to the
 *system clock control registers.
 */

struct sys_time_reg *get_sys_clock(void);

/*TODO - Set up control status functions to systime based interrupts */

#endif // SYS_TIME_H_INCLUDED
