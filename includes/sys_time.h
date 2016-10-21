#ifndef SYS_TIME_H_INCLUDED
#define SYS_TIME_H_INCLUDED

#endif // SYS_TIME_H_INCLUDED

struct sys_time_reg{
    volatile int *cntrl_status; /*System clock control status*/
    volatile int *lo_32bits;
    volatile int *hi_32bits;
    volatile int *time_cmpr_0;
    volatile int *time_cmpr_1;
    volatile int *time_cmpr_2;
    volatile int *time_cmpr_3;

};



/*Function: get_sys_time
 *
 *Returns the singleton address to the
 *system clock control registers.
 */

struct sys_time_reg *get_sys_time(void);



/*TODO - Set up control status functions to systime based interrupts */

