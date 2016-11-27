#ifndef MUTEX_H_INCLUDED
#define MUTEX_H_INCLUDED
#include <stdbool.h>


struct mutex{

char locked;
bool (* islocked)();
void (* set_mutex_lock)();
void (* remove_mutex_lock)();
};


#endif // MUTEX_H_INCLUDED
