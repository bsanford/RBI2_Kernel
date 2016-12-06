#include<stdlib.h>
#include "gpio_iterator.h"



/**Function is_done
 *
 * @self a pointer to the itor structure currently being worked on
 *
 * This function will check the current itor structure self
 * and check to ensure the cur_index is less than the total
 * nodes of the itor. If it is less
 */
   bool is_done(struct gpio_itor *self){

        if(self->cur_index < self->nodes)
            return false;

         return true;

   }


/**Function has_next
  *
  *@self a pointer to the itor structure currently being worked on
  *
  * This function checks to ensure that the current itorator structure
  * self has a next node. In this case if the current index + 1 is less
  * than or equal to the total nodes than it returns true. Otherwise it
  * returns false
  *
  */
  bool has_next(struct gpio_itor *self){

  if(self->cur_index + 1 <= self->nodes)
        return true;

    return false;

  }


/**Function get_next
  * @self a pointer to the itor structure currently being worked on
  *
  *
  * This function checks if the item has next if this is true then the
  * function increments the offset pointed to at cur_node and increments
  * the current index finally returns the new cur node.
  *
  * If the itor does not have next IE it is at the last node then it returns
  * NULL
  */



struct gpio_pin *get_next(struct gpio_itor *self){


       if(self->has_next(self)){

        self->cur_index++;
        self->cur_node++;
        return self->cur_node;
       }

       return NULL;
}




/** Function get_node_at_index
 *
 * @self a pointer to the itor structure currently being worked on
 *
 * @index the index from 0 where the node would like to be reached
 *
 * Function will take the supplied index and add it to the pointer to
 * the first node. In this way the interator will be indexed to that node
 * will set the current node to that offset and return a pointer to that
 * node
 *
 * If the index being passed in is greater than the total nodes stored at nodes
 * function will return NULL
 */

struct gpio_pin *get_node_at_index (struct gpio_itor *self, int index){


    if(index <= self->nodes){
        self->cur_index = index;
        self->cur_node = self->first + index;
        return self->cur_node;
    }

    return NULL;
}



/** Function init_gpitor
 * @iterator a pointer to a gpio_itor structure
 *
 * @pin_set  a pointer to the first node of the pin_set being used
 *
 * @size the total length of the nodes
 *
 * This function initializes the itorerator by taking the structure pointed to with *iterator
 * and packs the strucute with the function pointers that are required for use.
 * also does the initialization values of the current index and the total node size.
 */


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
