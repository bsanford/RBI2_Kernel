#include<stdlib.h>
#include "gpio_iterator.h"




   bool is_done(struct gpio_itor *self){

        if(self->cur_index < self->nodes)
            return false;

         return true;

   }



  bool has_next(struct gpio_itor *self){

  if(self->cur_index + 1 <= self->nodes)
        return true;

    return false;

  }




struct gpio_pin *get_next(struct gpio_itor *self){


       if(self->has_next(self)){

        self->cur_index++;
        self->cur_node++;
        return self->cur_node;
       }

       return NULL;
}





struct gpio_pin *get_node_at_index (struct gpio_itor *self, int index){

    if(index <= self->nodes){
        self->cur_index = index;
        self->cur_node = self->first + index;
        return self->cur_node;
    }

    return NULL;
}





void init_gpitor(struct gpio_itor *iterator, struct gpio_pin *pin_set, int size){

    iterator->nodes = size;
    iterator->first = pin_set;
    iterator->cur_index = 0;
    iterator->cur_node = pin_set;
    iterator->get_next = &get_next;
    iterator->has_next = &has_next;
    iterator->is_done = &is_done;
    iterator->get_node_at_index = &get_node_at_index;
}
