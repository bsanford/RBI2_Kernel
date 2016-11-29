#ifndef MUTEX_H_INCLUDED
#define MUTEX_H_INCLUDED
#include <stdbool.h>


struct mutex{

volatile char locked;
bool (* islocked)(struct mutex *self);
char (* set_mutex_lock)(struct mutex *self);
char (* rmv_mutex_lock)(struct mutex *self);
};



extern char init_lock(struct mutex *self);
#endif // MUTEX_H_INCLUDED
