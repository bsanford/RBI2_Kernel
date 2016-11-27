#ifndef MUTEX_H_INCLUDED
#define MUTEX_H_INCLUDED
#include <stdbool.h>


struct mutex{

volatile char locked;
bool (* islocked)();
void (* set_mutex_lock)();
void (* rmv_mutex_lock)();
};



extern char init_lock(struct mutex *self);
#endif // MUTEX_H_INCLUDED
