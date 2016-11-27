#include "mutex.h"





void init_lock(void){



}




void set_mutex_lock(void){



}




void remove_mutex_lock(void){



}



bool is_locked(struct mutex *self){

  if(self->locked == 1)
        return true;

  return false;
}


