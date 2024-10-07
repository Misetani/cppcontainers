#ifndef S21_CONTAINERS_H_
#define S21_CONTAINERS_H_

#include <utility>

// basic collections
// include list, map, queue, set, stack, vector

// sequential containers (inherit directly from SequentialContainer)
#include "lib_src/s21_vector.h"
#include "lib_src/s21_list.h"

// associative containers (inherit directly from AssociativeContainer)
#include "lib_src/s21_map.h"
#include "lib_src/s21_set.h"

// other containers (Queue and Stack inherit from Deque, Deque does not inherit Container)
#include "lib_src/s21_queue.h"
#include "lib_src/s21_stack.h"

#endif  // S21_CONTAINERS_H_