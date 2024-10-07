#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
// #include <vector>
#include <utility>

#include "../array_exception.h"
#include "../s21_containers.h"
#include "../s21_containersplus.h"
#include "../lib_src/s21_base_tree.h"


/* ========================================================================= */
/*                                   List                                    */
/* ========================================================================= */

TEST(Creating_a_list, empty_list) {
  s21::List<int> list;

  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(Creating_a_list, inserting_elements) {
  s21::List<int> list;
  list.insert(0, 1);
  EXPECT_EQ(list.get(0), 1);
  list.insert(1, 2);
  EXPECT_EQ(list.get(1), 2);
  list.insert(2, 3);
  EXPECT_EQ(list.get(2), 3);

  EXPECT_EQ(list.size(), 3);
  EXPECT_FALSE(list.empty());

  // list.print();

  list.insert(3, 4);
  list.insert(4, 5);
  list.insert(5, 6);

  // list.print();
  EXPECT_EQ(list.size(), 6);

  list.insert(1, 7);
  EXPECT_EQ(list.get(1), 7);
  list.insert(3, 8);
  EXPECT_EQ(list.get(3), 8);
  list.insert(0, 9);
  EXPECT_EQ(list.get(0), 9);

  // list.print();
  EXPECT_EQ(list.size(), 9);
}

TEST(Creating_a_list, inserting_elements_errors) {
  s21::List<int> list;

  EXPECT_FALSE(list.insert(1, 1));

  list.insert(0, 1);
  EXPECT_EQ(list.get(0), 1);
  list.insert(1, 2);
  EXPECT_EQ(list.get(1), 2);
  list.insert(2, 3);
  EXPECT_EQ(list.get(2), 3);

  EXPECT_FALSE(list.insert(4, 4));

  EXPECT_FALSE(list.insert(-1, 5));
}

TEST(viewing_a_list, get_errors) {
  s21::List<int> list;

  list.insert(0, 1);
  EXPECT_EQ(list.get(0), 1);
  list.insert(1, 2);
  EXPECT_EQ(list.get(1), 2);
  list.insert(2, 3);
  EXPECT_EQ(list.get(2), 3);

  EXPECT_THROW(list.get(3), s21::ArrayException);
  EXPECT_THROW(list.get(-1), s21::ArrayException);
}

TEST(viewing_a_list, indexOf) {
  s21::List<int> list;

  list.insert(0, 1);
  EXPECT_EQ(list.indexOf(1), 0);
  list.insert(1, 2);
  EXPECT_EQ(list.indexOf(2), 1);
  list.insert(2, 3);
  EXPECT_EQ(list.indexOf(3), 2);
}

TEST(viewing_a_list, indexOf_errors) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_EQ(list.indexOf(4), -1);
  EXPECT_EQ(list.indexOf(-1), -1);
}

TEST(viewing_a_list, contains) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_TRUE(list.contains(1));
  EXPECT_TRUE(list.contains(2));
  EXPECT_TRUE(list.contains(3));

  EXPECT_FALSE(list.contains(4));
  EXPECT_FALSE(list.contains(-1));
}

TEST(modifying_a_list, set) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_TRUE(list.set(0, 4));
  EXPECT_EQ(list.get(0), 4);

  EXPECT_TRUE(list.set(1, 5));
  EXPECT_EQ(list.get(1), 5);

  EXPECT_TRUE(list.set(2, 6));
  EXPECT_EQ(list.get(2), 6);
}

TEST(modifying_a_list, set_errors) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_FALSE(list.set(3, 4));
  EXPECT_FALSE(list.set(-1, 5));
}

// push

TEST(modifying_a_list, pushBack) {
  s21::List<int> list;

  list.pushBack(1);
  list.pushBack(2);
  list.pushBack(3);

  EXPECT_EQ(list.size(), 3);

  EXPECT_EQ(list.get(0), 1);
  EXPECT_EQ(list.get(1), 2);
  EXPECT_EQ(list.get(2), 3);
}

TEST(modifying_a_list, pushFront) {
  s21::List<int> list;

  list.pushFront(1);
  list.pushFront(2);
  list.pushFront(3);

  EXPECT_EQ(list.size(), 3);

  EXPECT_EQ(list.get(0), 3);
  EXPECT_EQ(list.get(1), 2);
  EXPECT_EQ(list.get(2), 1);
}

TEST(modifying_a_list, remove_by_value) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_TRUE(list.remove(1));
  EXPECT_FALSE(list.contains(1));
  EXPECT_EQ(list.size(), 2);

  EXPECT_TRUE(list.remove(3));
  EXPECT_FALSE(list.contains(3));
  EXPECT_EQ(list.size(), 1);

  EXPECT_TRUE(list.remove(2));
  EXPECT_FALSE(list.contains(2));
  EXPECT_EQ(list.size(), 0);
}

TEST(modifying_a_list, remove_by_value_errors) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_FALSE(list.remove(4));
  EXPECT_FALSE(list.remove(-1));
}

TEST(modifying_a_list, remove_by_index) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_TRUE(list.removeAt(1));

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), 1);
  EXPECT_EQ(list.get(1), 3);

  EXPECT_TRUE(list.removeAt(0));

  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), 3);
}

TEST(modifying_a_list, remove_by_index_errors) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_FALSE(list.removeAt(3));
  EXPECT_FALSE(list.removeAt(-1));
}

TEST(clearing_a_list, clear) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_EQ(list.size(), 3);

  list.clear();

  EXPECT_EQ(list.size(), 0);

  EXPECT_TRUE(list.empty());

  EXPECT_THROW(list.get(0), s21::ArrayException);
}

TEST(copying_a_list, using_copy_constructor) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int> list2(list);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list2.size(), 3);

  EXPECT_EQ(list.get(0), 1);
  EXPECT_EQ(list.get(1), 2);
  EXPECT_EQ(list.get(2), 3);

  EXPECT_EQ(list2.get(0), 1);
  EXPECT_EQ(list2.get(1), 2);
  EXPECT_EQ(list2.get(2), 3);
}

TEST(copying_a_list, using_move_constructor) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int> list2(std::move(list));

  EXPECT_EQ(list2.size(), 3);

  EXPECT_EQ(list2.get(0), 1);
  EXPECT_EQ(list2.get(1), 2);
  EXPECT_EQ(list2.get(2), 3);

  EXPECT_EQ(list.size(), 0);

  EXPECT_THROW(list.get(0), s21::ArrayException);
  EXPECT_THROW(list.get(1), s21::ArrayException);
  EXPECT_THROW(list.get(2), s21::ArrayException);
}

TEST(traversing_a_list, using_forward_iterator) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int>::Iterator it = list.begin();

  int i = 1;
  while (it != list.end()) {
    EXPECT_EQ(*it, i++);
    ++it;
  }

  EXPECT_TRUE(it == list.end());
  EXPECT_THROW(*it, s21::ArrayException);

  s21::List<int>::Iterator it2 = list.end();
  --it2;

  i = 3;
  while (it2 != list.begin()) {
    EXPECT_EQ(*it2, i--);
    --it2;
  }

  EXPECT_TRUE(it2 == list.begin());
}

TEST(traversing_a_list, using_reverse_iterator) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int>::ReverseIterator rit = list.rbegin();

  int i = 3;
  while (rit != list.rend()) {
    EXPECT_EQ(*rit, i--);
    ++rit;
  }

  EXPECT_TRUE(rit == list.rend());
  EXPECT_THROW(*rit, s21::ArrayException);

  s21::List<int>::ReverseIterator rit2 = list.rend();
  --rit2;

  i = 1;
  while (rit2 != list.rbegin()) {
    EXPECT_EQ(*rit2, i++);
    --rit2;
  }

  EXPECT_TRUE(rit2 == list.rbegin());
}

// no assignment operators implemented
// don't really know what I should add to be able to
// copy one reference to an another

TEST(testing_iterators, using_copy_assignment) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int>::Iterator it = list.begin();

  while (it != list.end()) {
    ++it;
  }

  it = list.begin();

  EXPECT_TRUE(it == list.begin());
  EXPECT_EQ(*it, 1);
}

TEST(testing_iterators, using_copy_assignment_reverse) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int>::ReverseIterator rit = list.rbegin();

  while (rit != list.rend()) {
    ++rit;
  }

  rit = list.rbegin();

  EXPECT_TRUE(rit == list.rbegin());
  EXPECT_EQ(*rit, 3);
}

TEST(multiple_insertions, insert_many) {
  s21::List<int> list;
  s21::List<int>::Iterator it = list.begin();

  list.insert_many(it, 1, 2, 3);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.get(0), 1);
  EXPECT_EQ(list.get(1), 2);
  EXPECT_EQ(list.get(2), 3);
}

TEST(multiple_insertions, insert_many_2) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int>::Iterator it = list.begin();

  ++it;
  ++it;

  list.insert_many(it, 4, 5);

  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(list.get(0), 1);
  EXPECT_EQ(list.get(1), 2);
  EXPECT_EQ(list.get(2), 4);
  EXPECT_EQ(list.get(3), 5);
  EXPECT_EQ(list.get(4), 3);
}

TEST(multiple_insertions, insert_many_front) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  list.insert_many_front(4, 5);

  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(list.get(0), 5);
  EXPECT_EQ(list.get(1), 4);
  EXPECT_EQ(list.get(2), 1);
  EXPECT_EQ(list.get(3), 2);
  EXPECT_EQ(list.get(4), 3);
}

TEST(multiple_insertions, insert_many_back) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  list.insert_many_back(4, 5);

  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(list.get(0), 1);
  EXPECT_EQ(list.get(1), 2);
  EXPECT_EQ(list.get(2), 3);
  EXPECT_EQ(list.get(3), 4);
  EXPECT_EQ(list.get(4), 5);
}

TEST(creating_a_list, getting_max_size) {
  s21::List<int> list;
  EXPECT_EQ(list.max_size(), pow(2, 64) - 1);
}

TEST(creating_a_list, using_parameterized_constructor) {
  s21::List<int> list(3);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.get(0), 0);
  EXPECT_EQ(list.get(1), 0);
  EXPECT_EQ(list.get(2), 0);
}

TEST(creating_a_list,
     using_parameterized_constructor_with_initialization_list) {
  s21::List<int> list({1, 2, 3, 4, 5});

  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(list.get(0), 1);
  EXPECT_EQ(list.get(1), 2);
  EXPECT_EQ(list.get(2), 3);
  EXPECT_EQ(list.get(3), 4);
  EXPECT_EQ(list.get(4), 5);
}

TEST(creating_a_list, using_move_assignment) {
  s21::List<int> list({1, 2, 3});

  s21::List<int> list2;

  list2 = std::move(list);

  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(list2.size(), 3);

  EXPECT_EQ(list2.get(0), 1);
  EXPECT_EQ(list2.get(1), 2);
  EXPECT_EQ(list2.get(2), 3);

  EXPECT_THROW(list.get(0), s21::ArrayException);
}

TEST(accessing_a_list, getting_first_element) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_EQ(list.front(), 1);
}

TEST(accessing_a_list, getting_last_element) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_EQ(list.back(), 3);
}

TEST(accessing_a_list, front_back_errors) {
  s21::List<int> list;

  EXPECT_THROW(list.front(), s21::ArrayException);
  EXPECT_THROW(list.back(), s21::ArrayException);
}

TEST(modifying_a_list, insert_at_pos) {
  s21::List<int> list;
  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int>::Iterator it = list.begin();

  ++it;

  EXPECT_EQ(*it, 2);

  list.insert(it, 9);

  EXPECT_EQ(list.get(1), 9);
  EXPECT_EQ(list.get(2), 2);
}

TEST(modifying_a_list, erase_at_pos) {
  s21::List<int> list;
  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int>::Iterator it = list.begin();

  ++it;

  EXPECT_TRUE(list.contains(2));
  EXPECT_TRUE(list.erase(it));
  EXPECT_FALSE(list.contains(2));

  EXPECT_EQ(*it, 3);
}

TEST(modifying_a_list, erase_at_pos_errors) {
  s21::List<int> list;
  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int>::Iterator it = list.end();

  EXPECT_FALSE(list.erase(it));
}

TEST(modifying_a_list, pop_back) {
  s21::List<int> list;
  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_EQ(list.size(), 3);
  EXPECT_TRUE(list.contains(3));

  list.popBack();

  EXPECT_EQ(list.size(), 2);
  EXPECT_FALSE(list.contains(3));
}

TEST(modifying_a_list, pop_front) {
  s21::List<int> list;
  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  EXPECT_EQ(list.size(), 3);
  EXPECT_TRUE(list.contains(1));

  list.popFront();

  EXPECT_EQ(list.size(), 2);
  EXPECT_FALSE(list.contains(1));
}

TEST(special_list_operations, swapping_two_lists) {
  s21::List<int> list;
  list.insert(0, 1);
  list.insert(1, 2);

  s21::List<int> list2;
  list2.insert(0, 3);
  list2.insert(1, 2);
  list2.insert(2, 1);

  list.swap(list2);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list2.size(), 2);

  EXPECT_EQ(list.get(0), 3);
  EXPECT_EQ(list.get(1), 2);
  EXPECT_EQ(list.get(2), 1);

  EXPECT_EQ(list2.get(0), 1);
  EXPECT_EQ(list2.get(1), 2);
}

TEST(special_list_operations, merging_two_lists) {
  s21::List<int> list;
  list.insert(0, 1);
  list.insert(1, 3);
  list.insert(2, 7);

  s21::List<int> list2;
  list2.insert(0, 0);
  list2.insert(1, 2);
  list2.insert(2, 6);
  list2.insert(3, 9);

  list.merge(list2);

  EXPECT_EQ(list.size(), 7);

  EXPECT_EQ(list.get(0), 0);
  EXPECT_EQ(list.get(1), 1);
  EXPECT_EQ(list.get(2), 2);
  EXPECT_EQ(list.get(3), 3);
  EXPECT_EQ(list.get(4), 6);
  EXPECT_EQ(list.get(5), 7);
  EXPECT_EQ(list.get(6), 9);
}

TEST(special_list_operations, merging_two_lists_2) {
  s21::List<int> list;

  s21::List<int> list2;
  list2.insert(0, 0);
  list2.insert(1, 2);
  list2.insert(2, 6);
  list2.insert(3, 9);

  list.merge(list2);

  EXPECT_EQ(list.size(), 4);

  EXPECT_EQ(list.get(0), 0);
  EXPECT_EQ(list.get(1), 2);
  EXPECT_EQ(list.get(2), 6);
  EXPECT_EQ(list.get(3), 9);
}

TEST(testing_iterators, const_iterator) {
  s21::List<int> list;
  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int>::ConstIterator cit = list.cbegin();

  EXPECT_EQ(*cit, 1);
  EXPECT_TRUE(cit == list.cbegin());

  ++cit;

  EXPECT_EQ(*cit, 2);
  EXPECT_TRUE(cit != list.cbegin());

  ++cit;

  EXPECT_EQ(*cit, 3);
  EXPECT_TRUE(cit != list.cbegin());

  ++cit;

  EXPECT_THROW(*cit, s21::ArrayException);
  EXPECT_TRUE(cit == list.cend());

  --cit;
  EXPECT_EQ(*cit, 3);
  EXPECT_TRUE(cit != list.cend());
}

TEST(testing_iterators, const_iterator_copy) {
  s21::List<int> list;
  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int>::ConstIterator cit = list.cbegin();

  EXPECT_EQ(*cit, 1);

  ++cit;

  EXPECT_EQ(*cit, 2);

  s21::List<int>::ConstIterator cit2 = list.cend();

  EXPECT_TRUE(cit2 == list.cend());

  cit2 = cit;

  EXPECT_EQ(*cit2, 2);
}

TEST(special_list_operations, splicing_two_lists) {
  s21::List<int> list;
  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);

  s21::List<int> list2;
  list2.insert(0, 4);
  list2.insert(1, 3);
  list2.insert(2, 2);
  list2.insert(3, 1);

  s21::List<int>::ConstIterator cit = list2.cbegin();

  ++cit;
  ++cit;

  list.splice(cit, list2);
}

TEST(special_list_operations, reversing_a_list) {
  s21::List<int> list;
  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);
  list.insert(3, 4);
  list.insert(4, 5);

  list.reverse();

  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(list.get(0), 5);
  EXPECT_EQ(list.get(1), 4);
  EXPECT_EQ(list.get(2), 3);
  EXPECT_EQ(list.get(3), 2);
  EXPECT_EQ(list.get(4), 1);

  list.reverse();

  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(list.get(0), 1);
  EXPECT_EQ(list.get(1), 2);
  EXPECT_EQ(list.get(2), 3);
  EXPECT_EQ(list.get(3), 4);
  EXPECT_EQ(list.get(4), 5);
}

TEST(special_list_operations, using_unique) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);
  list.insert(3, 3);
  list.insert(4, 5);
  list.insert(5, 1);
  list.insert(6, 1);
  list.insert(7, 1);
  list.insert(8, 4);
  list.insert(9, 5);

  EXPECT_EQ(list.size(), 10);

  list.unique();

  EXPECT_EQ(list.size(), 7);

  EXPECT_EQ(list.get(0), 1);
  EXPECT_EQ(list.get(1), 2);
  EXPECT_EQ(list.get(2), 3);
  EXPECT_EQ(list.get(3), 5);
  EXPECT_EQ(list.get(4), 1);
  EXPECT_EQ(list.get(5), 4);
  EXPECT_EQ(list.get(6), 5);
}

TEST(special_list_operations, reversing_a_list_2) {
  s21::List<int> list;

  list.reverse();
}

TEST(special_list_operations, sorting_a_list) {
  s21::List<int> list;

  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(2, 3);
  list.insert(3, 3);
  list.insert(4, 5);
  list.insert(5, 1);
  list.insert(6, 1);
  list.insert(7, 1);
  list.insert(8, 4);
  list.insert(9, 5);

  list.sort();

  EXPECT_EQ(list.size(), 10);

  EXPECT_EQ(list.get(0), 1);
  EXPECT_EQ(list.get(1), 1);
  EXPECT_EQ(list.get(2), 1);
  EXPECT_EQ(list.get(3), 1);
  EXPECT_EQ(list.get(4), 2);
  EXPECT_EQ(list.get(5), 3);
  EXPECT_EQ(list.get(6), 3);
  EXPECT_EQ(list.get(7), 4);
  EXPECT_EQ(list.get(8), 5);
  EXPECT_EQ(list.get(9), 5);
}

TEST(special_list_operations, sorting_a_list_2) {
  s21::List<int> list;

  list.sort();
}


/* ========================================================================= */
/*                                   Stack                                   */
/* ========================================================================= */

TEST(creating_a_stack, using_default_constructor) {
  s21::Stack<int> stack;

  EXPECT_EQ(stack.size(), 0);
  EXPECT_TRUE(stack.empty());
}

TEST(creating_a_stack, using_initializer_list) {
  s21::Stack<int> stack({1, 2, 3, 4, 5});

  EXPECT_EQ(stack.size(), 5);
  EXPECT_FALSE(stack.empty());
  EXPECT_EQ(stack.top(), 5);

  stack.pop();
  EXPECT_EQ(stack.size(), 4);
  EXPECT_EQ(stack.top(), 4);

  stack.pop();
  stack.pop();
  stack.pop();
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.top(), 1);

  stack.pop();
  EXPECT_EQ(stack.size(), 0);
  EXPECT_TRUE(stack.empty());
}

TEST(creating_a_stack, using_copy_constructor) {
  s21::Stack<int> stack({1, 2, 3, 4, 5});

  s21::Stack<int> stack2 = stack;

  EXPECT_EQ(stack.size(), 5);
  EXPECT_EQ(stack2.size(), 5);

  EXPECT_EQ(stack.top(), 5);
  EXPECT_EQ(stack2.top(), 5);
}

TEST(creating_a_stack, using_move_constructor) {
  s21::Stack<int> stack({1, 2, 3, 4, 5});

  s21::Stack<int> stack2 = std::move(stack);

  EXPECT_EQ(stack.size(), 0);
  EXPECT_EQ(stack2.size(), 5);

  EXPECT_THROW(stack.top(), s21::ArrayException);
  EXPECT_EQ(stack2.top(), 5);
}

TEST(creating_a_stack, using_move_assignment) {
  s21::Stack<int> stack({1, 2, 3, 4, 5});

  s21::Stack<int> stack2({3, 2, 1});

  stack2 = std::move(stack);

  EXPECT_EQ(stack.size(), 0);
  EXPECT_EQ(stack2.size(), 5);

  EXPECT_THROW(stack.top(), s21::ArrayException);
  EXPECT_EQ(stack2.top(), 5);
}

TEST(redacting_a_stack, using_push_pop) {
  s21::Stack<int> stack;

  EXPECT_EQ(stack.size(), 0);
  EXPECT_THROW(stack.top(), s21::ArrayException);

  stack.push(1);

  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.top(), 1);

  stack.push(2);

  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.top(), 2);

  stack.pop();

  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.top(), 1);

  stack.pop();

  EXPECT_EQ(stack.size(), 0);
  EXPECT_THROW(stack.top(), s21::ArrayException);
}

TEST(redacting_a_stack, swapping_two_stacks) {
  s21::Stack<int> stack({1, 2, 3, 4, 5});

  s21::Stack<int> stack2({3, 2, 1});

  stack.swap(stack2);

  EXPECT_EQ(stack.size(), 3);
  EXPECT_EQ(stack2.size(), 5);

  EXPECT_EQ(stack.top(), 1);
  EXPECT_EQ(stack2.top(), 5);
}

TEST(inserting_in_stack, insert_many_front) {
  s21::Stack<int> stack({1, 2, 3});

  stack.insert_many_front(-1, -2, -3);

  EXPECT_EQ(stack.size(), 6);

  EXPECT_EQ(stack.top(), -3);
  stack.pop();
  EXPECT_EQ(stack.top(), -2);
  stack.pop();
  EXPECT_EQ(stack.top(), -1);
  stack.pop();
  EXPECT_EQ(stack.top(), 3);
  stack.pop();
  EXPECT_EQ(stack.top(), 2);
  stack.pop();
  EXPECT_EQ(stack.top(), 1);
  stack.pop();
}


/* ========================================================================= */
/*                                  Queue                                    */
/* ========================================================================= */

TEST(creating_a_queue, using_initializer_list) {
  s21::Queue<int> queue({1, 2, 3, 4, 5});

  EXPECT_EQ(queue.size(), 5);
  EXPECT_FALSE(queue.empty());
  EXPECT_EQ(queue.back(), 5);
  EXPECT_EQ(queue.front(), 1);

  queue.pop();
  EXPECT_EQ(queue.size(), 4);
  EXPECT_EQ(queue.front(), 2);

  queue.pop();
  queue.pop();
  queue.pop();
  EXPECT_EQ(queue.size(), 1);
  EXPECT_EQ(queue.front(), 5);

  queue.pop();
  EXPECT_EQ(queue.size(), 0);
  EXPECT_TRUE(queue.empty());
}

TEST(creating_a_queue, using_copy_constructor) {
  s21::Queue<int> queue({1, 2, 3, 4, 5});

  s21::Queue<int> queue2 = queue;

  EXPECT_EQ(queue.size(), 5);
  EXPECT_EQ(queue2.size(), 5);

  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue2.front(), 1);

  EXPECT_EQ(queue.back(), 5);
  EXPECT_EQ(queue2.back(), 5);
}

TEST(creating_a_queue, using_move_constructor) {
  s21::Queue<int> queue({1, 2, 3, 4, 5});

  s21::Queue<int> queue2 = std::move(queue);

  EXPECT_EQ(queue.size(), 0);
  EXPECT_EQ(queue2.size(), 5);

  EXPECT_THROW(queue.front(), s21::ArrayException);
  EXPECT_THROW(queue.back(), s21::ArrayException);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue2.back(), 5);
}

TEST(creating_a_queue, using_move_assignment) {
  s21::Queue<int> queue({1, 2, 3, 4, 5});

  s21::Queue<int> queue2({3, 2, 1});

  queue2 = std::move(queue);

  EXPECT_EQ(queue.size(), 0);
  EXPECT_EQ(queue2.size(), 5);

  EXPECT_THROW(queue.front(), s21::ArrayException);
  EXPECT_THROW(queue.back(), s21::ArrayException);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue2.back(), 5);
}

TEST(redacting_a_queue, using_push_pop) {
  s21::Queue<int> queue;

  EXPECT_EQ(queue.size(), 0);
  EXPECT_THROW(queue.front(), s21::ArrayException);
  EXPECT_THROW(queue.back(), s21::ArrayException);

  queue.push(1);

  EXPECT_EQ(queue.size(), 1);
  EXPECT_EQ(queue.back(), 1);

  queue.push(2);

  EXPECT_EQ(queue.size(), 2);
  EXPECT_EQ(queue.back(), 2);

  queue.pop();

  EXPECT_EQ(queue.size(), 1);
  EXPECT_EQ(queue.back(), 2);

  queue.pop();

  EXPECT_EQ(queue.size(), 0);
  EXPECT_THROW(queue.back(), s21::ArrayException);
}

TEST(redacting_a_queue, swapping_two_queues) {
  s21::Queue<int> queue({1, 2, 3, 4, 5});

  s21::Queue<int> queue2({3, 2, 1});

  queue.swap(queue2);

  EXPECT_EQ(queue.size(), 3);
  EXPECT_EQ(queue2.size(), 5);

  EXPECT_EQ(queue.back(), 1);
  EXPECT_EQ(queue2.back(), 5);

  EXPECT_EQ(queue.front(), 3);
  EXPECT_EQ(queue2.front(), 1);
}

TEST(inserting_in_a_queue, insert_many_back) {
  s21::Queue<int> queue({1, 2, 3});

  queue.insert_many_back(4, 5, 6);

  EXPECT_EQ(queue.size(), 6);

  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 6);

  queue.pop();
  EXPECT_EQ(queue.front(), 2);
  queue.pop();
  EXPECT_EQ(queue.front(), 3);
  queue.pop();
  EXPECT_EQ(queue.front(), 4);
  queue.pop();
  EXPECT_EQ(queue.front(), 5);
  queue.pop();
  EXPECT_EQ(queue.front(), 6);
}


/* ========================================================================= */
/*                                Base Tree                                  */
/* ========================================================================= */

// TEST(BaseTree, DefaultConstructor) {
//   s21::BaseTree<int, int> tree;
//   EXPECT_EQ(tree.size(), 0);
// }

// TEST(BaseTree, CopyConstructor) {
//   s21::BaseTree<int, int> tree;
//   tree.insert(2, 2);
//   tree.insert(3, 3);
//   tree.insert(1, 1);
//   EXPECT_EQ(tree.size(), 3);

//   s21::BaseTree<int, int> tree_cpy = tree;
//   EXPECT_EQ(tree_cpy.size(), 3);
//   tree.print();
//   tree_cpy.print();
//   EXPECT_TRUE(tree_cpy.contains(1));
//   EXPECT_TRUE(tree_cpy.contains(2));
//   EXPECT_TRUE(tree_cpy.contains(3));
// }

// TEST(BaseTree, MoveConstructor) {
//   s21::BaseTree<int, int> tree;
//   tree.insert(3, 3);
//   tree.insert(1, 1);
//   tree.insert(2, 2);
//   EXPECT_EQ(tree.size(), 3);

//   s21::BaseTree<int, int> tree_cpy = std::move(tree);
//   EXPECT_EQ(tree_cpy.size(), 3);
//   EXPECT_EQ(tree.size(), 0);
// }

// TEST(BaseTree, ListInitializerConstructor) {
//   s21::BaseTree<int, int> tree({ std::pair<int, int>(3, 3), 
//     std::pair<int, int>(1, 1), std::pair<int, int>(5, 5) });

//   EXPECT_EQ(tree.size(), 3);
//   s21::BaseTree<int, int>::Iterator it = tree.begin();

//   EXPECT_EQ(*it, 1);
//   ++it;
//   EXPECT_EQ(*it, 3);
//   ++it;
//   EXPECT_EQ(*it, 5);
// }

// TEST(BaseTree, Insert) {
//   s21::BaseTree<int, int> tree;
//   EXPECT_EQ(tree.size(), 0);
//   EXPECT_TRUE(tree.insert(1, 1).second);
//   EXPECT_EQ(tree.size(), 1);
//   EXPECT_TRUE(tree.insert(2, 2).second);
//   EXPECT_EQ(tree.size(), 2);
//   EXPECT_TRUE(tree.insert(3, 3).second);
//   EXPECT_EQ(tree.size(), 3);
//   EXPECT_TRUE(tree.insert(4, 4).second);
//   EXPECT_EQ(tree.size(), 4);
//   EXPECT_TRUE(tree.insert(5, 5).second);
//   EXPECT_EQ(tree.size(), 5);
//   EXPECT_TRUE(tree.insert(6, 6).second);
//   EXPECT_EQ(tree.size(), 6);
//   EXPECT_TRUE(tree.insert(7, 7).second);
//   EXPECT_EQ(tree.size(), 7);
//   EXPECT_TRUE(tree.insert(8, 8).second);
//   EXPECT_EQ(tree.size(), 8);
//   EXPECT_TRUE(tree.insert(9, 9).second);
//   EXPECT_EQ(tree.size(), 9);
//   EXPECT_TRUE(tree.insert(9, 9).second);
//   EXPECT_EQ(tree.size(), 10);
//   EXPECT_TRUE(tree.insert(1, 1).second);
//   EXPECT_EQ(tree.size(), 11);
// }

// TEST(BaseTree, Insert2) {
//   s21::BaseTree<int, int> tree;

//   EXPECT_EQ(tree.size(), 0);
//   EXPECT_EQ(*(tree.insert(3, 3).first), 3);
//   EXPECT_EQ(tree.size(), 1);
//   EXPECT_EQ(*(tree.insert(2, 2).first), 2);
//   EXPECT_EQ(tree.size(), 2);
//   EXPECT_EQ(*(tree.insert(1, 1).first), 1);
//   EXPECT_EQ(tree.size(), 3);
// }

// TEST(BaseTree, Remove) {
//   s21::BaseTree<int, int> tree;
//   EXPECT_EQ(tree.size(), 0);
//   EXPECT_FALSE(tree.remove(1));
//   EXPECT_EQ(tree.size(), 0);

//   EXPECT_EQ(tree.size(), 0);
//   EXPECT_TRUE(tree.insert(1, 1).second);
//   EXPECT_TRUE(tree.insert(2, 2).second);
//   EXPECT_TRUE(tree.insert(3, 3).second);

//   EXPECT_EQ(tree.size(), 3);
//   EXPECT_TRUE(tree.remove(2));
//   EXPECT_EQ(tree.size(), 2);
//   EXPECT_TRUE(tree.remove(3));
//   EXPECT_EQ(tree.size(), 1);
//   EXPECT_TRUE(tree.remove(1));
//   EXPECT_EQ(tree.size(), 0);

//   EXPECT_FALSE(tree.remove(1));
//   EXPECT_FALSE(tree.remove(2));
//   EXPECT_FALSE(tree.remove(3));

//   EXPECT_EQ(tree.size(), 0);

//   EXPECT_TRUE(tree.insert(1, 1).second);
//   EXPECT_EQ(tree.size(), 1);
// }

// TEST(BaseTree, Erase) {
//   s21::BaseTree<int, int> tree;

//   s21::BaseTree<int, int>::Iterator it = tree.begin();

//   EXPECT_EQ(tree.size(), 0);
//   EXPECT_FALSE(tree.erase(it));
//   EXPECT_EQ(tree.size(), 0);

//   EXPECT_TRUE(tree.insert(1, 1).second);
//   EXPECT_TRUE(tree.insert(2, 2).second);
//   EXPECT_TRUE(tree.insert(3, 3).second);
//   EXPECT_EQ(tree.size(), 3);

//   it = tree.begin();
//   EXPECT_EQ(*it, 1);
//   ++it;
//   EXPECT_EQ(*it, 2);
//   ++it;
//   EXPECT_EQ(*it, 3);

//   EXPECT_EQ(tree.size(), 3);
//   EXPECT_FALSE(it == tree.end());
//   EXPECT_TRUE(tree.erase(it));
//   EXPECT_EQ(tree.size(), 2);

//   EXPECT_FALSE(tree.contains(3));
// }

// TEST(BaseTree, clear) {
//   s21::BaseTree<int, int> tree;
//   EXPECT_EQ(tree.size(), 0);
//   EXPECT_TRUE(tree.insert(1, 1).second);
//   EXPECT_EQ(tree.size(), 1);
//   EXPECT_TRUE(tree.insert(2, 2).second);
//   EXPECT_EQ(tree.size(), 2);
//   EXPECT_TRUE(tree.insert(3, 3).second);
//   EXPECT_EQ(tree.size(), 3);

//   tree.clear();

//   EXPECT_EQ(tree.size(), 0);
//   EXPECT_FALSE(tree.remove(1));

//   EXPECT_TRUE(tree.insert(1, 1).second);
//   EXPECT_EQ(tree.size(), 1);
// }

// TEST(BaseTree, find) {
//   s21::BaseTree<int, int> tree;
//   tree.insert(5, 5);
//   tree.insert(8, 8);
//   tree.insert(3, 3);
//   tree.insert(6, 6);
//   tree.insert(7, 7);
//   tree.insert(9, 9);
//   tree.insert(4, 4);
//   tree.insert(2, 2);
//   tree.insert(1, 1);
//   EXPECT_EQ(tree.size(), 9);

//   EXPECT_EQ(tree.begin(), tree.find(1));

//   EXPECT_EQ(*(tree.find(5)), 5);

//   EXPECT_EQ(*(++(tree.find(5))), 6);

//   EXPECT_EQ(*(--(tree.find(5))), 4);

//   EXPECT_THROW(tree.find(10), s21::ArrayException);
// }

// TEST(BaseTree, find2) {
//   s21::BaseTree<int, int> tree;
//   EXPECT_THROW(tree.find(1), s21::ArrayException);
// }

// TEST(BaseTree, contains) {
//   s21::BaseTree<int, int> tree;
//   tree.insert(5, 5);
//   tree.insert(8, 8);
//   tree.insert(3, 3);
//   tree.insert(6, 6);
//   tree.insert(7, 7);
//   tree.insert(9, 9);
//   tree.insert(4, 4);
//   tree.insert(2, 2);
//   tree.insert(1, 1);
//   EXPECT_EQ(tree.size(), 9);

//   EXPECT_TRUE(tree.contains(1));
//   EXPECT_TRUE(tree.contains(5));
//   EXPECT_TRUE(tree.contains(9));

//   EXPECT_FALSE(tree.contains(0));
//   EXPECT_FALSE(tree.contains(-1));
//   EXPECT_FALSE(tree.contains(10));
// }

// TEST(BaseTree, swap) {
//   s21::BaseTree<int, int> tree;
//   EXPECT_TRUE(tree.insert(1, 1).second);
//   EXPECT_TRUE(tree.insert(2, 2).second);
//   EXPECT_TRUE(tree.insert(3, 3).second);

//   s21::BaseTree<int, int> tree2;
//   EXPECT_TRUE(tree2.insert(5, 5).second);
//   EXPECT_TRUE(tree2.insert(7, 7).second);

//   tree.swap(tree2);

//   EXPECT_EQ(tree.size(), 2);
//   EXPECT_EQ(tree2.size(), 3);

//   s21::BaseTree<int, int>::Iterator it = tree.begin();
//   EXPECT_EQ(*it, 5);
//   ++it;
//   EXPECT_EQ(*it, 7);

//   s21::BaseTree<int, int>::Iterator it2 = tree2.begin();
//   EXPECT_EQ(*it2, 1);
//   ++it2;
//   EXPECT_EQ(*it2, 2);
//   ++it2;
//   EXPECT_EQ(*it2, 3);
// }

// TEST(BaseTree, merge) {
//   s21::BaseTree<int, int> tree;
//   EXPECT_TRUE(tree.insert(1, 1).second);
//   EXPECT_TRUE(tree.insert(2, 2).second);
//   EXPECT_TRUE(tree.insert(3, 3).second);

//   s21::BaseTree<int, int> tree2;
//   EXPECT_TRUE(tree2.insert(5, 5).second);
//   EXPECT_TRUE(tree2.insert(7, 7).second);

//   tree.merge(tree2);

//   EXPECT_EQ(tree.size(), 5);

//   s21::BaseTree<int, int>::Iterator it = tree.begin();

//   EXPECT_EQ(*it, 1);
//   ++it;
//   EXPECT_EQ(*it, 2);
//   ++it;
//   EXPECT_EQ(*it, 3);
//   ++it;
//   EXPECT_EQ(*it, 5);
//   ++it;
//   EXPECT_EQ(*it, 7);
// }

// TEST (BaseTree, iterator_test1) {
//     s21::BaseTree<int, int> tree;
//     tree.insert(5, 5);
//     tree.insert(8, 8);
//     tree.insert(3, 3);
//     tree.insert(6, 6);
//     tree.insert(7, 7);
//     tree.insert(9, 9);
//     tree.insert(4, 4);
//     tree.insert(2, 2);
//     tree.insert(1, 1);

//     s21::BaseTree<int, int>::Iterator it = tree.begin();
//     EXPECT_EQ(*it, 1);
// }

// TEST (BaseTree, iterator_test2) {
//     s21::BaseTree<int, int> tree;
//     s21::BaseTree<int, int>::Iterator it = tree.begin();
//     EXPECT_THROW(*it, s21::ArrayException);
// }

// TEST (BaseTree, iterator_test3) {
//     s21::BaseTree<int, int> tree;
//     tree.insert(5, 5);
//     tree.insert(8, 8);
//     tree.insert(3, 3);
//     tree.insert(6, 6);
//     tree.insert(7, 7);
//     tree.insert(9, 9);
//     tree.insert(4, 4);
//     tree.insert(2, 2);
//     tree.insert(1, 1);

//     s21::BaseTree<int, int>::Iterator it = tree.begin();

//     for (int i = 1; i < 10; i++) {
//         EXPECT_EQ(*it, i);
//         ++it;
//     }

//     EXPECT_THROW(++it, s21::ArrayException);
//     EXPECT_THROW(*it, s21::ArrayException);
//     EXPECT_THROW(--it, s21::ArrayException);

//     EXPECT_EQ(it, tree.end());
// }

// TEST (BaseTree, iterator_test4) {
//     s21::BaseTree<int, int> tree;
//     tree.insert(5, 5);
//     tree.insert(8, 8);
//     tree.insert(3, 3);
//     tree.insert(6, 6);
//     tree.insert(7, 7);
//     tree.insert(9, 9);
//     tree.insert(4, 4);
//     tree.insert(2, 2);
//     tree.insert(1, 1);

//     s21::BaseTree<int, int>::Iterator it = tree.begin();

//     while (it != tree.end()) {
//         EXPECT_GE(*it, 1);
//         EXPECT_LE(*it, 9);
//         ++it;
//     }

//     EXPECT_EQ(it, tree.end());
// }

// TEST (BaseTree, iterator_test5) {
//     s21::BaseTree<int, int> tree;
//     tree.insert(5, 5);
//     tree.insert(8, 8);
//     tree.insert(3, 3);
//     tree.insert(6, 6);
//     tree.insert(7, 7);
//     tree.insert(9, 9);
//     tree.insert(4, 4);
//     tree.insert(2, 2);
//     tree.insert(1, 1);

//     s21::BaseTree<int, int>::Iterator it = tree.begin();

//     for (int i = 1; i < 10; i++) {
//         EXPECT_EQ(*it, i);
//         if (i != 9) {
//             ++it;
//         }
//     }

//     EXPECT_EQ(*it, 9);

//     for (int i = 9; i > 0; --i) {
//         EXPECT_EQ(*it, i);

//         if (i != 1) {
//             --it;
//         }
//     }

//     EXPECT_EQ(*it, 1);
//     EXPECT_EQ(it, tree.begin());
// }

// TEST (BaseTree, const_iterator_test1) {
//     s21::BaseTree<int, int> tree;
//     tree.insert(5, 5);
//     tree.insert(8, 8);
//     tree.insert(3, 3);
//     tree.insert(6, 6);
//     tree.insert(7, 7);
//     tree.insert(9, 9);
//     tree.insert(4, 4);
//     tree.insert(2, 2);
//     tree.insert(1, 1);

//     s21::BaseTree<int, int>::ConstIterator it = tree.cbegin();
//     EXPECT_EQ(*it, 1);
// }

// TEST (BaseTree, const_iterator_test2) {
//     s21::BaseTree<int, int> tree;
//     s21::BaseTree<int, int>::ConstIterator it = tree.cbegin();
//     EXPECT_THROW(*it, s21::ArrayException);
// }

// TEST (BaseTree, const_iterator_test3) {
//     s21::BaseTree<int, int> tree;
//     tree.insert(5, 5);
//     tree.insert(8, 8);
//     tree.insert(3, 3);
//     tree.insert(6, 6);
//     tree.insert(7, 7);
//     tree.insert(9, 9);
//     tree.insert(4, 4);
//     tree.insert(2, 2);
//     tree.insert(1, 1);

//     s21::BaseTree<int, int>::ConstIterator it = tree.cbegin();

//     for (int i = 1; i < 10; i++) {
//         EXPECT_EQ(*it, i);
//         ++it;
//     }

//     EXPECT_THROW(++it, s21::ArrayException);
//     EXPECT_THROW(*it, s21::ArrayException);
//     EXPECT_THROW(--it, s21::ArrayException);

//     EXPECT_EQ(it, tree.cend());
// }

// TEST (BaseTree, const_iterator_test4) {
//     s21::BaseTree<int, int> tree;
//     tree.insert(5, 5);
//     tree.insert(8, 8);
//     tree.insert(3, 3);
//     tree.insert(6, 6);
//     tree.insert(7, 7);
//     tree.insert(9, 9);
//     tree.insert(4, 4);
//     tree.insert(2, 2);
//     tree.insert(1, 1);

//     s21::BaseTree<int, int>::ConstIterator it = tree.cbegin();

//     while (it != tree.cend()) {
//         EXPECT_GE(*it, 1);
//         EXPECT_LE(*it, 9);
//         ++it;
//     }

//     EXPECT_EQ(it, tree.cend());
// }

// TEST (BaseTree, const_iterator_test5) {
//     s21::BaseTree<int, int> tree;
//     tree.insert(5, 5);
//     tree.insert(8, 8);
//     tree.insert(3, 3);
//     tree.insert(6, 6);
//     tree.insert(7, 7);
//     tree.insert(9, 9);
//     tree.insert(4, 4);
//     tree.insert(2, 2);
//     tree.insert(1, 1);

//     s21::BaseTree<int, int>::ConstIterator it = tree.cbegin();

//     for (int i = 1; i < 10; i++) {
//         EXPECT_EQ(*it, i);
//         if (i != 9) {
//             ++it;
//         }
//     }

//     EXPECT_EQ(*it, 9);

//     for (int i = 9; i > 0; --i) {
//         EXPECT_EQ(*it, i);

//         if (i != 1) {
//             --it;
//         }
//     }

//     EXPECT_EQ(*it, 1);
//     EXPECT_EQ(it, tree.cbegin());
// }

// TEST(BaseTree, printing_tree_structure) {
//   // s21::BaseTree<int, int> tree;
//   // tree.insert(5, 5);
//   // tree.insert(8, 8);
//   // tree.insert(3, 3);
//   // tree.insert(6, 6);
//   // tree.insert(7, 7);
//   // tree.insert(9, 9);
//   // tree.insert(4, 4);
//   // tree.insert(2, 2);
//   // tree.insert(1, 1);

//   // tree.print();
// }


/* ========================================================================= */
/*                                   Set                                     */
/* ========================================================================= */

TEST(Set, Creating_a_set) {
  s21::Set<int> set;

  EXPECT_TRUE(set.insert(1).second);

  EXPECT_TRUE(set.contains(1));

  EXPECT_TRUE(set.find(1) == set.begin());

  EXPECT_TRUE(set.remove(1));

  EXPECT_FALSE(set.contains(1));
}

TEST(Set, Creating_a_set_using_initializer_list) {
  s21::Set<int> set({ 1, 2, 3, 3, 2, 1, 2, 3 });

  EXPECT_EQ(set.size(), 3);

  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
}

TEST(Set, Creating_a_set_using_copy_constructor) {
  s21::Set<int> set({ 3, 1, 2, 5, 4 });

  EXPECT_EQ(set.size(), 5);
  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
  EXPECT_TRUE(set.contains(4));
  EXPECT_TRUE(set.contains(5));

  s21::Set<int> set2{ set };

  EXPECT_EQ(set2.size(), 5);
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));
  EXPECT_TRUE(set2.contains(3));
  EXPECT_TRUE(set2.contains(4));
  EXPECT_TRUE(set2.contains(5));

  s21::Set<int>::Iterator it = set2.begin();
  EXPECT_EQ(*it, 1);
  int count = 1;
  while (it != set.end()) {
    EXPECT_EQ(count++, *it);
    ++it;
  }
}

TEST(Set, Creating_a_set_using_move_constructor) {
  s21::Set<int> set({ 3, 1, 2, 5, 4 });

  s21::Set<int> set2{ std::move(set) };

  EXPECT_EQ(set2.size(), 5);
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));
  EXPECT_TRUE(set2.contains(3));
  EXPECT_TRUE(set2.contains(4));
  EXPECT_TRUE(set2.contains(5));

  s21::Set<int>::Iterator it = set2.begin();
  EXPECT_EQ(*it, 1);
  int count = 1;
  while (it != set.end()) {
    EXPECT_EQ(count++, *it);
    ++it;
  }
}

TEST(Set, Creating_a_set_using_move_asssignment) {
  s21::Set<int> set({ 3, 1, 2, 5, 4 });

  s21::Set<int> set2;

  set2 = std::move(set);

  EXPECT_EQ(set2.size(), 5);
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));
  EXPECT_TRUE(set2.contains(3));
  EXPECT_TRUE(set2.contains(4));
  EXPECT_TRUE(set2.contains(5));

  s21::Set<int>::Iterator it = set2.begin();
  EXPECT_EQ(*it, 1);
  int count = 1;
  while (it != set.end()) {
    EXPECT_EQ(count++, *it);
    ++it;
  }
}

TEST(Set, Using_iterators) {
  s21::Set<int> set({ 3, 1, 2, 5, 4 });
  s21::Set<int>::Iterator it = set.begin();

  EXPECT_TRUE(it == set.begin());
  EXPECT_FALSE(it == set.end());

  while (it != set.end()) {
    ++it;
  }

  EXPECT_TRUE(it == set.end());
  EXPECT_FALSE(it == set.begin());

  it = set.begin();

  EXPECT_TRUE(it == set.begin());
  EXPECT_FALSE(it == set.end());
}

TEST(Set, Using_const_iterators) {
  s21::Set<int> set({ 3, 1, 2, 5, 4 });
  s21::Set<int>::ConstIterator it = set.cbegin();

  EXPECT_TRUE(it == set.cbegin());
  EXPECT_FALSE(it == set.cend());

  while (it != set.cend()) {
    ++it;
  }

  EXPECT_TRUE(it == set.cend());
  EXPECT_FALSE(it == set.cbegin());

  it = set.cbegin();

  EXPECT_TRUE(it == set.cbegin());
  EXPECT_FALSE(it == set.cend());
}

TEST(Set, Inserting_in_a_set) {
  s21::Set<int> set;
  EXPECT_EQ(*(set.insert(3).first), 3);
  EXPECT_EQ(*(set.insert(1).first), 1);
  EXPECT_EQ(*(set.insert(2).first), 2);

  EXPECT_FALSE(set.insert(3).second);
  EXPECT_TRUE(set.insert(0).second);
}

TEST(Set, Deleteing_from_a_set) {
  s21::Set<int> set({ 3, 1, 2, 5, 4 });

  EXPECT_EQ(set.size(), 5);

  s21::Set<int>::Iterator it = set.begin();
  ++it;

  set.erase(it);

  EXPECT_FALSE(set.contains(2));

  it = set.begin();

  set.erase(it);

  EXPECT_FALSE(set.contains(1));

  it = set.begin();
  ++it;
  ++it;

  set.erase(it);

  EXPECT_FALSE(set.contains(5));

  EXPECT_EQ(set.size(), 2);
}

TEST(Set, Swapping_sets) {
  s21::Set<int> set({ 3, 1, 2 });

  s21::Set<int> set2({ 5, 4 });

  set.swap(set2);

  EXPECT_EQ(set.size(), 2);
  EXPECT_EQ(set2.size(), 3);

  s21::Set<int>::Iterator it = set.begin();
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);

  s21::Set<int>::Iterator it2 = set2.begin();
  EXPECT_EQ(*it2, 1);
  ++it2;
  EXPECT_EQ(*it2, 2);
  ++it2;
  EXPECT_EQ(*it2, 3);
}

TEST(Set, Merging_sets) {
  s21::Set<int> set({ 3, 1, 2 });

  s21::Set<int> set2({ 5, 4 });

  set.merge(set2);

  EXPECT_EQ(set.size(), 5);

  s21::Set<int>::Iterator it = set.begin();
  int count = 1;
  while (it != set.end()) {
    EXPECT_EQ(count++, *it);
    ++it;
  }
}

TEST(Set, Finding_elements_in_a_set) {
  s21::Set<int> set({ 3, 1, 2, 5, 4 });

  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
  EXPECT_TRUE(set.contains(4));
  EXPECT_TRUE(set.contains(5));

  EXPECT_EQ(*set.find(1), 1);
  EXPECT_EQ(*set.find(2), 2);
  EXPECT_EQ(*set.find(3), 3);
  EXPECT_EQ(*set.find(4), 4);
  EXPECT_EQ(*set.find(5), 5);

  EXPECT_THROW(set.find(0), s21::ArrayException);
  EXPECT_THROW(set.find(6), s21::ArrayException);

  s21::Set<int> set2;
  EXPECT_THROW(set.find(0), s21::ArrayException);
}


/* ========================================================================= */
/*                                Multiset                                   */
/* ========================================================================= */

TEST(Multiset, Creating_multiset) {
  s21::Multiset<int> mset;

  EXPECT_EQ(mset.size(), 0);
}

TEST(Multiset, Creating_multiset_using_initializer_list) {
  s21::Multiset<int> mset( { 1, 1, 2, 3, 3, 3, 4, 5 });

  EXPECT_EQ(mset.size(), 8);

  EXPECT_TRUE(mset.contains(1));
  EXPECT_TRUE(mset.contains(2));
  EXPECT_TRUE(mset.contains(3));
  EXPECT_TRUE(mset.contains(4));
  EXPECT_TRUE(mset.contains(5));
}

TEST(Multiset, Creating_multiset_using_copy_constructor) {
  s21::Multiset<int> mset( { 1, 1, 2, 3, 3, 3 });

  s21::Multiset<int> mset2{ mset };

  EXPECT_EQ(mset.size(), 6);
  EXPECT_EQ(mset2.size(), 6);
}

TEST(Multiset, Creating_multiset_using_move_constructor) {
  s21::Multiset<int> mset( { 1, 1, 2, 3, 3, 3 });

  s21::Multiset<int> mset2{ std::move(mset) };

  EXPECT_EQ(mset.size(), 0);
  EXPECT_EQ(mset2.size(), 6);
}

TEST(Multiset, Creating_multiset_using_move_assignment) {
  s21::Multiset<int> mset( { 1, 1, 2, 3, 3, 3 });

  s21::Multiset<int> mset2;

  mset2 = std::move(mset);

  EXPECT_EQ(mset.size(), 0);
  EXPECT_EQ(mset2.size(), 6);
}

TEST(Multiset, Testing_iterators) {
  s21::Multiset<int> mset( { 1, 1, 2, 3, 3, 3 });

  s21::Multiset<int>::Iterator it = mset.begin();

  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 3);

  EXPECT_TRUE(it != mset.end());

  // ++it;
  // EXPECT_TRUE(it == mset.end());

  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
  --it;
  EXPECT_EQ(*it, 1);

  EXPECT_TRUE(it == mset.begin());

  --it;
  EXPECT_TRUE(it == mset.end());
}

TEST(Multiset, Testing_multiset_capacity) {
  s21::Multiset<int> mset;

  EXPECT_TRUE(mset.empty());
  EXPECT_EQ(mset.size(), 0);
}

TEST(Multiset, inserting_in_a_multiset) {
  s21::Multiset<int> mset;

  EXPECT_TRUE(mset.insert(3).second);
  EXPECT_EQ(*(mset.insert(2).first), 2);;
  EXPECT_TRUE(mset.insert(4).second);

  EXPECT_EQ(mset.size(), 3);

  s21::Multiset<int>::Iterator it = mset.begin();

  ++it;

  mset.erase(it);

  EXPECT_FALSE(mset.contains(3));

  EXPECT_EQ(mset.size(), 2);
}

TEST(Multiset, swapping_multisets) {
  s21::Multiset<int> mset{ 3, 2, 1, 4, 5};

  s21::Multiset<int> mset2{ 2, 1, 3 };

  mset.swap(mset2);

  EXPECT_EQ(mset.size(), 3);
  EXPECT_EQ(mset2.size(), 5);

  EXPECT_TRUE(mset.contains(1));
  EXPECT_TRUE(mset.contains(2));
  EXPECT_TRUE(mset.contains(3));

  EXPECT_TRUE(mset2.contains(1));
  EXPECT_TRUE(mset2.contains(2));
  EXPECT_TRUE(mset2.contains(3));
  EXPECT_TRUE(mset2.contains(4));
  EXPECT_TRUE(mset2.contains(5));
}

TEST(Multiset, merging_multisets) {
  s21::Multiset<int> mset{ 3, 2, 1, 4, 5};

  s21::Multiset<int> mset2{ 2, 1, 3 };

  mset.merge(mset2);

  EXPECT_EQ(mset.size(), 8);

  EXPECT_TRUE(mset.contains(1));
  EXPECT_TRUE(mset.contains(2));
  EXPECT_TRUE(mset.contains(3));
  EXPECT_TRUE(mset.contains(4));
  EXPECT_TRUE(mset.contains(5));

  EXPECT_EQ(mset2.size(), 3);

  EXPECT_TRUE(mset2.contains(1));
  EXPECT_TRUE(mset2.contains(2));
  EXPECT_TRUE(mset2.contains(3));
}

TEST(Multiset, testing_count) {
  s21::Multiset<int> mset( { 1, 1, 2, 3, 3, 3 });

  EXPECT_EQ(mset.count(1), 2);
  EXPECT_EQ(mset.count(2), 1);
  EXPECT_EQ(mset.count(3), 3);
}

TEST(Multiset, testing_equal_range) {
  s21::Multiset<int> mset( { 1, 1, 2, 3, 3, 3 });

  auto range = mset.equal_range(3);

  EXPECT_EQ(*(range.first), 3);
  
  int count = 0;
  while (range.first != range.second) {
    ++range.first;
    ++count;
  }

  EXPECT_EQ(count, 3);
}

TEST(Multiset, testing_lower_upper_bound) {
  s21::Multiset<int> mset( { 5, 3, 7, 4, 2, 8, 9, 4, 7, 8 });

  EXPECT_EQ(*(mset.lower_bound(4)), 4);
  EXPECT_EQ(*(mset.lower_bound(8)), 8);
  EXPECT_EQ(*(mset.lower_bound(6)), 7);

  EXPECT_EQ(*(mset.upper_bound(8)), 9);
  EXPECT_EQ(*(mset.upper_bound(6)), 7);
  EXPECT_EQ(*(mset.upper_bound(5)), 7);
}


/* ========================================================================= */
/*                                   Map                                     */
/* ========================================================================= */

TEST(Map, creating_a_map) {
  s21::Map<int, int> map;

  EXPECT_EQ(map.size(), 0);

  EXPECT_THROW(map.at(0), s21::ArrayException);

  map[0] = 1;
  EXPECT_EQ(map.at(0), 1);
}

TEST(Map, creating_a_map_using_initializer_list) {
  s21::Map<int, int> map({ std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(2, 3) });

  EXPECT_EQ(map.size(), 3);

  EXPECT_EQ(map[0], 1);
  EXPECT_EQ(map[1], 2);
  EXPECT_EQ(map[2], 3);

  map[3] = 4;

  EXPECT_EQ(map.size(), 4);
  EXPECT_EQ(map[3], 4);
}

TEST(Map, creating_a_map_using_copy_constructor) {
  s21::Map<int, int> map({ std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(2, 3) });

  s21::Map<int, int> map2{ map };

  EXPECT_EQ(map.size(), 3);

  EXPECT_EQ(map[0], 1);
  EXPECT_EQ(map[1], 2);
  EXPECT_EQ(map[2], 3);

  EXPECT_EQ(map2.size(), 3);

  EXPECT_EQ(map2[0], 1);
  EXPECT_EQ(map2[1], 2);
  EXPECT_EQ(map2[2], 3);
}

TEST(Map, creating_a_map_using_move_constructor) {
  s21::Map<int, int> map({ std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(2, 3) });

  s21::Map<int, int> map2{ std::move(map) };

  EXPECT_EQ(map.size(), 0);

  EXPECT_EQ(map2.size(), 3);

  EXPECT_EQ(map2[0], 1);
  EXPECT_EQ(map2[1], 2);
  EXPECT_EQ(map2[2], 3);
}

TEST(Map, creating_a_map_using_move_assignment) {
  s21::Map<int, int> map({ std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(2, 3) });

  s21::Map<int, int> map2;

  map2 = std::move(map);

  EXPECT_EQ(map.size(), 0);

  EXPECT_EQ(map2.size(), 3);

  EXPECT_EQ(map2[0], 1);
  EXPECT_EQ(map2[1], 2);
  EXPECT_EQ(map2[2], 3);
}

TEST(Map, testing_iterators) {
  s21::Map<int, int> map({ std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(2, 3) });

  s21::Map<int, int>::Iterator it = map.begin();

  EXPECT_TRUE(it != map.end());

  int count = 0;
  while (it != map.end()) {
    EXPECT_EQ(*it, ++count);
    ++it;
  }

  EXPECT_TRUE(it == map.end());
}

TEST(Map, inserting_pairs) {
  s21::Map<int, int> map;

  EXPECT_TRUE(map.insert(std::make_pair(0, 1)).second);
  EXPECT_TRUE(map.insert(std::make_pair(1, 2)).second);
  EXPECT_TRUE(map.insert(std::make_pair(2, 3)).second);
  EXPECT_FALSE(map.insert(std::make_pair(0, 1)).second);
  EXPECT_EQ(*(map.insert(std::make_pair(3, 4)).first), 4);
  EXPECT_EQ(*(map.insert(std::make_pair(4, 5)).first), 5);

  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 5);
}

TEST(Map, inserting_pairs_using_insert_many) {
  s21::Map<int, int> map;

  auto vector = map.insert_many(std::make_pair(1, 1), std::make_pair(1, 1), std::make_pair(2, 2));

  EXPECT_EQ(vector.size(), 3);

  EXPECT_EQ(map.size(), 2);

  EXPECT_EQ(map[1], 1);

  EXPECT_EQ(*(vector.front().first), 1);
  EXPECT_TRUE(vector.front().second);

  EXPECT_EQ(*((vector.at(1)).first), 1);
  EXPECT_FALSE(vector.at(1).second);

  EXPECT_EQ(*((vector.at(2)).first), 2);
  EXPECT_TRUE(vector.at(2).second);
}

TEST(Set, inserting_pairs_using_insert_many) {
  s21::Set<int> set;

  auto vector = set.insert_many(1, 1, 2);

  EXPECT_EQ(vector.size(), 3);

  EXPECT_EQ(set.size(), 2);

  EXPECT_EQ(*(vector.front().first), 1);
  EXPECT_TRUE(vector.front().second);

  EXPECT_EQ(*((vector.at(1)).first), 1);
  EXPECT_FALSE(vector.at(1).second);

  EXPECT_EQ(*((vector.at(2)).first), 2);
  EXPECT_TRUE(vector.at(2).second);
}

TEST(Multiset, inserting_pairs_using_insert_many) {
  s21::Multiset<int> multiset;

  auto vector = multiset.insert_many(1, 1, 2);

  EXPECT_EQ(vector.size(), 3);

  EXPECT_EQ(multiset.size(), 3);

  EXPECT_EQ(*(vector.front().first), 1);
  EXPECT_TRUE(vector.front().second);

  EXPECT_EQ(*((vector.at(1)).first), 1);
  EXPECT_TRUE(vector.at(1).second);

  EXPECT_EQ(*((vector.at(2)).first), 2);
  EXPECT_TRUE(vector.at(2).second);
}

TEST(Map, inserting_keys_and_values) {
  s21::Map<int, int> map;

  EXPECT_TRUE(map.insert(0, 1).second);
  EXPECT_TRUE(map.insert(1, 2).second);
  EXPECT_TRUE(map.insert(2, 3).second);
  EXPECT_FALSE(map.insert(0, 1).second);
  EXPECT_EQ(*(map.insert(3, 4).first), 4);
  EXPECT_EQ(*(map.insert(4, 5).first), 5);

  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 5);
}

TEST(Map, insert_or_assign) {
  s21::Map<int, int> map;

  EXPECT_TRUE(map.insert(0, 1).second);
  EXPECT_TRUE(map.insert(1, 2).second);
  EXPECT_TRUE(map.insert(2, 3).second);

  EXPECT_TRUE(map.insert_or_assign(0, 9).second);

  EXPECT_EQ(map[0], 9);

  EXPECT_EQ(*(map.insert(3, 4).first), 4);
  EXPECT_EQ(*(map.insert(4, 5).first), 5);

  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 5);
}

TEST(Map, erase) {
  s21::Map<int, int> map;

  EXPECT_TRUE(map.insert(0, 1).second);
  EXPECT_TRUE(map.insert(1, 2).second);
  EXPECT_TRUE(map.insert(2, 3).second);

  EXPECT_EQ(map.size(), 3);

  s21::Map<int, int>::Iterator it = map.begin();

  EXPECT_EQ(*it, 1);

  ++it;

  EXPECT_EQ(*it, 2);

  map.erase(it);

  EXPECT_EQ(map.size(), 2);
  EXPECT_FALSE(map.contains(1));

  it = map.begin();

  ++it;

  map.erase(it);

  EXPECT_EQ(map.size(), 1);
  EXPECT_FALSE(map.contains(2));
  EXPECT_TRUE(map.contains(0));
}

TEST(Map, swapping_two_maps) {
  s21::Map<int, int> map;

  EXPECT_TRUE(map.insert(1, 2).second);
  EXPECT_TRUE(map.insert(0, 1).second);
  EXPECT_TRUE(map.insert(2, 3).second);

  s21::Map<int, int> map2;
  EXPECT_TRUE(map2.insert(3, -2).second);
  EXPECT_TRUE(map2.insert(4, -1).second);
  EXPECT_TRUE(map2.insert(5, -3).second);
  EXPECT_TRUE(map2.insert(6, -1).second);
  EXPECT_TRUE(map2.insert(7, -3).second);

  map.swap(map2);

  EXPECT_EQ(map.size(), 5);
  EXPECT_EQ(map2.size(), 3);

  EXPECT_TRUE(map.contains(3));
  EXPECT_TRUE(map.contains(4));
  EXPECT_TRUE(map.contains(5));
  EXPECT_TRUE(map.contains(6));
  EXPECT_TRUE(map.contains(7));

  EXPECT_FALSE(map.contains(0));
  EXPECT_FALSE(map.contains(1));
  EXPECT_FALSE(map.contains(2));

  EXPECT_TRUE(map2.contains(0));
  EXPECT_TRUE(map2.contains(1));
  EXPECT_TRUE(map2.contains(2));

  EXPECT_FALSE(map2.contains(3));
  EXPECT_FALSE(map2.contains(4));
  EXPECT_FALSE(map2.contains(5));
  EXPECT_FALSE(map2.contains(6));
  EXPECT_FALSE(map2.contains(7));
}

TEST(Map, merging_two_maps) {
  s21::Map<int, int> map;

  EXPECT_TRUE(map.insert(1, 2).second);
  EXPECT_TRUE(map.insert(0, 1).second);
  EXPECT_TRUE(map.insert(2, 3).second);

  s21::Map<int, int> map2;
  EXPECT_TRUE(map2.insert(3, -2).second);
  EXPECT_TRUE(map2.insert(4, -1).second);
  EXPECT_TRUE(map2.insert(5, -3).second);
  EXPECT_TRUE(map2.insert(6, -1).second);
  EXPECT_TRUE(map2.insert(7, -3).second);

  map.merge(map2);

  EXPECT_EQ(map.size(), 8);

  EXPECT_TRUE(map.contains(3));
  EXPECT_TRUE(map.contains(4));
  EXPECT_TRUE(map.contains(5));
  EXPECT_TRUE(map.contains(6));
  EXPECT_TRUE(map.contains(7));

  EXPECT_TRUE(map.contains(0));
  EXPECT_TRUE(map.contains(1));
  EXPECT_TRUE(map.contains(2));

}


/* ========================================================================= */
/*                                 Vector                                    */
/* ========================================================================= */

TEST(Creating_vector, vector_of_pairs) {
  // s21::List<int> list;

  // s21::Vector<std::pair<s21::List<int>::Iterator, bool>> vector(10);

  // vector.push_back(std::make_pair(list.begin(), true));

  // EXPECT_EQ(vector.size(), 1);

  // std::pair<int, int>* p = new std::pair<int, int>();
  // printf("p->first = %d, p->second = %d\n", p->first, p->second);
}

TEST(Creating_vector, empty_vector) {
  s21::Vector<int> vector;
  EXPECT_EQ(vector.size(), 0);
  EXPECT_TRUE(vector.empty());
}

TEST(Creating_vector, constructor_with_param) {
  s21::Vector<int> vector(11);

  EXPECT_EQ(vector.size(), 11);
}

TEST(Creating_vector, constructor_with_initializer_list) {
  s21::Vector<int> s21_vector = {1, 3, 5, 8, 10, 25};
  std::vector<int> std_vector = {1, 3, 5, 8, 10, 25};

  EXPECT_EQ(s21_vector.size(), std_vector.size());

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(Creating_vector, constructor_copy) {
  s21::Vector<int> vector(5);

  vector[0] = 10;
  vector[1] = 12;
  vector[2] = 13;
  vector[3] = 14;
  vector[4] = 15;

  s21::Vector<int> vectorCopy(vector);

  EXPECT_EQ(vectorCopy.size(), vector.size());

  for (size_t i = 0; i < vectorCopy.size(); ++i) {
    EXPECT_EQ(vectorCopy[i], vector[i]);
  }
}

TEST(Creating_vector, constructor_move) {
  s21::Vector<int> vector(5);

  vector[0] = 20;
  vector[1] = 21;
  vector[2] = 22;
  vector[3] = 23;
  vector[4] = 24;

  s21::Vector<int> vectorCopy(std::move(vector));

  EXPECT_EQ(vectorCopy.size(), 5);
  EXPECT_EQ(vector.size(), 0);

  for (size_t i = 0; i < vectorCopy.size(); ++i) {
    EXPECT_EQ(vectorCopy[i], 20 + i);
  }
}

TEST(Destructor_vector, destructor) {
  s21::Vector<int> vector(2);

  vector[0] = 20;
  vector[1] = 21;

  vector.~Vector();

  EXPECT_EQ(vector.size(), 0);
}

TEST(Assignment_operator_moving_object, Assignment_operator_moving_object) {
  s21::Vector<int> vector(5);

  vector[0] = 20;
  vector[1] = 21;
  vector[2] = 22;
  vector[3] = 23;
  vector[4] = 24;

  s21::Vector<int> vectorCopy(5);
  vectorCopy = (std::move(vector));

  EXPECT_EQ(vectorCopy.size(), 5);
  EXPECT_EQ(vector.size(), 0);

  for (size_t i = 0; i < vectorCopy.size(); ++i) {
    EXPECT_EQ(vectorCopy[i], 20 + i);
  }
}

TEST(Functions_vector, implimentation_at) {
  s21::Vector<int> s21_vector = {10, 20, 30};
  std::vector<int> std_vector = {10, 20, 30};

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector.at(i), std_vector.at(i));
  }

  EXPECT_THROW(s21_vector.at(10), s21::ArrayException);

  s21::Vector<int> const const_s21_vector = s21_vector;
  std::vector<int> const const_std_vector = std_vector;

  for (size_t i = 0; i < const_s21_vector.size(); ++i) {
    EXPECT_EQ(const_s21_vector.at(i), const_std_vector.at(i));
  }

  EXPECT_THROW(const_s21_vector.at(10), s21::ArrayException);
}

TEST(Functions_vector, implimentation_operator_index) {
  s21::Vector<int> s21_vector = {10, 20, 30};
  std::vector<int> std_vector = {10, 20, 30};

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }

  s21::Vector<int> const const_s21_vector = s21_vector;
  std::vector<int> const const_std_vector = std_vector;

  for (size_t i = 0; i < const_s21_vector.size(); ++i) {
    EXPECT_EQ(const_s21_vector[i], const_std_vector[i]);
  }
}

TEST(Functions_vector, implimentation_front) {
  s21::Vector<int> s21_vector = {10, 20, 30};
  std::vector<int> std_vector = {10, 20, 30};

  s21::Vector<int> const const_s21_vector = s21_vector;
  std::vector<int> const const_std_vector = std_vector;

  EXPECT_EQ(const_s21_vector.front(), const_std_vector.front());

  s21::Vector<int> const const_s21_vector_empty;

  EXPECT_THROW(const_s21_vector_empty.front(), s21::ArrayException);
}

TEST(Functions_vector, implimentation_back) {
  s21::Vector<int> s21_vector = {12, 22, 32};
  std::vector<int> std_vector = {12, 22, 32};

  s21::Vector<int> const const_s21_vector = s21_vector;
  std::vector<int> const const_std_vector = std_vector;

  EXPECT_EQ(const_s21_vector.back(), const_std_vector.back());

  s21::Vector<int> const const_s21_vector_empty;

  EXPECT_THROW(const_s21_vector_empty.back(), s21::ArrayException);
}

TEST(Functions_vector, implimentation_data) {
  s21::Vector<int> s21_vector;
  std::vector<int> std_vector;

  s21_vector.push_back(154);
  std_vector.push_back(154);

  EXPECT_EQ(*s21_vector.data(), 154);
  EXPECT_EQ(*s21_vector.data(), *std_vector.data());
}

TEST(Functions_vector, implimentation_begin) {
  s21::Vector<int> s21_vector = {12, 22, 32};
  std::vector<int> std_vector = {12, 22, 32};

  s21::Vector<int>::iterator s21_it = s21_vector.begin();
  std::vector<int>::iterator std_it = std_vector.begin();

  while (std_it != std_vector.end()) {
    EXPECT_EQ(*std_it, *s21_it);

    ++s21_it;
    ++std_it;
  }
}

TEST(Functions_vector, implimentation_end) {
  s21::Vector<int> s21_vector;
  std::vector<int> std_vector;

  s21_vector.push_back(12);
  s21_vector.push_back(22);
  s21_vector.push_back(32);

  std_vector.push_back(12);
  std_vector.push_back(22);
  std_vector.push_back(32);

  s21::Vector<int>::iterator s21_it = s21_vector.end();

  std::vector<int>::iterator std_it = std_vector.end();

  --s21_it;
  --std_it;

  while (std_it != std_vector.begin()) {
    EXPECT_EQ(*std_it, *s21_it);

    --s21_it;
    --std_it;
  }
}

TEST(Functions_vector, implimentation_cbegin) {
  s21::Vector<int> s21_vector;
  std::vector<int> std_vector;

  s21_vector.push_back(12);
  s21_vector.push_back(22);
  s21_vector.push_back(32);

  std_vector.push_back(12);
  std_vector.push_back(22);
  std_vector.push_back(32);

  s21::Vector<int> const const_s21_vector(s21_vector);
  std::vector<int> const const_std_vector(std_vector);

  EXPECT_EQ(*(const_s21_vector.begin()), *(const_std_vector.begin()));
}

TEST(Functions_vector, implimentation_cend) {
  s21::Vector<int> s21_vector;
  std::vector<int> std_vector;

  s21_vector.push_back(12);
  s21_vector.push_back(22);
  s21_vector.push_back(32);

  std_vector.push_back(12);
  std_vector.push_back(22);
  std_vector.push_back(32);

  s21::Vector<int> const const_s21_vector(s21_vector);
  std::vector<int> const const_std_vector(std_vector);

  EXPECT_EQ(*(--const_s21_vector.end()), *(--const_std_vector.end()));
}

// TEST(Functions_vector, implimentation_rbegin) {
//   s21::Vector<int> s21_vector = {1, 3, 5, 8, 10, 25};;
//   std::vector<int> std_vector = {1, 3, 5, 8, 10, 25};;

//   s21::Vector<int>::reverse_iterator s21_rit = s21_vector.rbegin();

//   std::vector<int>::reverse_iterator std_rit = std_vector.rbegin();

//   while(std_rit != std_vector.rend())
//   {
//     std::cout << *std_rit << " " << *s21_rit << std::endl;
//     EXPECT_EQ(*std_rit, *s21_rit);

//     ++std_rit;
//     ++s21_rit;
//   }
// }

TEST(Functions_vector, implimentation_reserve) {
  s21::Vector<int> s21_vector = {1, 3, 5, 8, 10, 25};
  std::vector<int> std_vector = {1, 3, 5, 8, 10, 25};

  s21_vector.reserve(44);
  std_vector.reserve(44);

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.capacity(), 44);
}

TEST(Functions_vector, implimentation_capacity) {
  s21::Vector<int> s21_vector = {1, 3, 5, 8, 10, 25};
  std::vector<int> std_vector = {1, 3, 5, 8, 10, 25};

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
}

TEST(Functions_vector, implimentation_shrink_to_fit) {
  s21::Vector<int> s21_vector = {1, 3, 5, 8, 10, 25};
  std::vector<int> std_vector = {1, 3, 5, 8, 10, 25};

  s21_vector.reserve(80);
  std_vector.reserve(80);

  s21_vector.shrink_to_fit();
  std_vector.shrink_to_fit();

  EXPECT_EQ(s21_vector.size(), 6);
  EXPECT_EQ(s21_vector.capacity(), 6);

  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
}

TEST(Functions_vector, implimentation_clear) {
  s21::Vector<int> s21_vector = {1, 3, 5, 8, 10, 25};
  std::vector<int> std_vector = {1, 3, 5, 8, 10, 25};

  s21_vector.clear();
  std_vector.clear();

  EXPECT_EQ(s21_vector.size(), 0);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(Functions_vector, implimentation_insert) {
  s21::Vector<int> s21_vector;
  std::vector<int> std_vector;

  for (size_t i = 0; i < 10; ++i) {
    std_vector.push_back(i * 3);
    s21_vector.push_back(i * 3);
  }

  s21_vector.insert(++s21_vector.begin(), 33);
  std_vector.insert(++std_vector.begin(), 33);

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }

  s21_vector.insert(s21_vector.end(), 44);
  std_vector.insert(std_vector.end(), 44);

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(Functions_vector, implimentation_erase) {
  s21::Vector<int> s21_vector;
  std::vector<int> std_vector;

  for (size_t i = 0; i < 10; ++i) {
    std_vector.push_back(i);
    s21_vector.push_back(i);
  }

  s21_vector.erase(++s21_vector.begin());
  std_vector.erase(++std_vector.begin());

  for (size_t i = 0; i < std_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }

  s21_vector.erase(--s21_vector.end());
  std_vector.erase(--std_vector.end());

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(Functions_vector, implimentation_push_back) {
  s21::Vector<int> s21_vector = {1, 3, 5, 8, 10, 25};
  std::vector<int> std_vector = {1, 3, 5, 8, 10, 25};

  for (size_t i = 0; i < 10; ++i) {
    std_vector.push_back(i);
    s21_vector.push_back(i);
  }

  for (size_t i = 0; i < std_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }
}

TEST(Functions_vector, implimentation_pop_back) {
  s21::Vector<int> s21_vector = {1, 3, 5, 8, 10, 25};
  std::vector<int> std_vector = {1, 3, 5, 8, 10, 25};

  s21_vector.pop_back();
  std_vector.pop_back();

  for (size_t i = 0; i < std_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }

  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(Functions_vector, implimentation_swap) {
  s21::Vector<int> s21_vector = {1, 3, 5, 8, 10, 25};
  s21::Vector<int> s21_vector_swap = {22, 33, 77, 88};
  std::vector<int> std_vector = {1, 3, 5, 8, 10, 25};
  std::vector<int> std_vector_swap = {22, 33, 77, 88};

  s21_vector.swap(s21_vector_swap);
  std_vector.swap(std_vector_swap);

  for (size_t i = 0; i < std_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }

  for (size_t i = 0; i < std_vector_swap.size(); ++i) {
    EXPECT_EQ(s21_vector_swap[i], std_vector_swap[i]);
  }
}

TEST(Functions_vector, implimentation_swap_one_vector_is_empty) {
  s21::Vector<int> s21_vector = {1, 3, 5, 8, 10, 25};
  s21::Vector<int> s21_vector_swap;
  std::vector<int> std_vector = {1, 3, 5, 8, 10, 25};
  std::vector<int> std_vector_swap;

  s21_vector.swap(s21_vector_swap);
  std_vector.swap(std_vector_swap);

  for (size_t i = 0; i < std_vector.size(); ++i) {
    EXPECT_EQ(s21_vector[i], std_vector[i]);
  }

  for (size_t i = 0; i < std_vector_swap.size(); ++i) {
    EXPECT_EQ(s21_vector_swap[i], std_vector_swap[i]);
  }
}

TEST(Functions_vector, insert_many_back) {
  s21::Vector<int> s21_vector = {1, 4, 5};

  s21_vector.insert_many_back(55, 88, 99);

  EXPECT_EQ(s21_vector.size(), 6);

  EXPECT_EQ(s21_vector[0], 1);
  EXPECT_EQ(s21_vector[1], 4);
  EXPECT_EQ(s21_vector[2], 5);
  EXPECT_EQ(s21_vector[3], 55);
  EXPECT_EQ(s21_vector[4], 88);
  EXPECT_EQ(s21_vector[5], 99);
}

TEST(Functions_vector, insert_many_back_empty) {
  s21::Vector<int> s21_vector;

  s21_vector.insert_many_back(55, 88, 99);

  EXPECT_EQ(s21_vector.size(), 3);

  EXPECT_EQ(s21_vector[0], 55);
  EXPECT_EQ(s21_vector[1], 88);
  EXPECT_EQ(s21_vector[2], 99);
}

TEST(Functions_vector, insert_many) {
  s21::Vector<int> s21_vector = {1, 2, 3, 4, 5, 6};

  s21::Vector<int>::iterator iter = s21_vector.begin();
  iter++;
  iter++;

  s21_vector.insert_many(iter, 10, 11, 12);

  EXPECT_EQ(s21_vector.size(), 9);

  EXPECT_EQ(s21_vector[0], 1);
  EXPECT_EQ(s21_vector[1], 2);
  EXPECT_EQ(s21_vector[2], 10);
  EXPECT_EQ(s21_vector[3], 11);
  EXPECT_EQ(s21_vector[4], 12);
  EXPECT_EQ(s21_vector[5], 3);
  EXPECT_EQ(s21_vector[6], 4);
  EXPECT_EQ(s21_vector[7], 5);
  EXPECT_EQ(s21_vector[8], 6);
}

TEST(Functions_vector, insert_many_to_begin) {
  s21::Vector<int> s21_vector = {1, 2, 3, 4, 5, 6};

  s21::Vector<int>::iterator iter = s21_vector.begin();

  s21_vector.insert_many(iter, 20, 21, 22);

  EXPECT_EQ(s21_vector.size(), 9);

  EXPECT_EQ(s21_vector[0], 20);
  EXPECT_EQ(s21_vector[1], 21);
  EXPECT_EQ(s21_vector[2], 22);
  EXPECT_EQ(s21_vector[3], 1);
  EXPECT_EQ(s21_vector[4], 2);
  EXPECT_EQ(s21_vector[5], 3);
  EXPECT_EQ(s21_vector[6], 4);
  EXPECT_EQ(s21_vector[7], 5);
  EXPECT_EQ(s21_vector[8], 6);
}

TEST(Functions_vector, insert_many_to_end) {
  s21::Vector<int> s21_vector = {1, 2, 3, 4, 5, 6};

  s21::Vector<int>::iterator iter = s21_vector.end();

  s21_vector.insert_many(iter, 10, 11, 12);

  EXPECT_EQ(s21_vector.size(), 9);

  EXPECT_EQ(s21_vector[0], 1);
  EXPECT_EQ(s21_vector[1], 2);
  EXPECT_EQ(s21_vector[2], 3);
  EXPECT_EQ(s21_vector[3], 4);
  EXPECT_EQ(s21_vector[4], 5);
  EXPECT_EQ(s21_vector[5], 6);
  EXPECT_EQ(s21_vector[6], 10);
  EXPECT_EQ(s21_vector[7], 11);
  EXPECT_EQ(s21_vector[8], 12);
}

TEST(Functions_vector, insert_many_to_empty_vector) {
  s21::Vector<int> s21_vector;

  s21::Vector<int>::iterator iter = s21_vector.begin();

  s21_vector.insert_many(iter, 10, 11, 12);

  EXPECT_EQ(s21_vector.size(), 3);

  EXPECT_EQ(s21_vector[0], 10);
  EXPECT_EQ(s21_vector[1], 11);
  EXPECT_EQ(s21_vector[2], 12);
}


/* ========================================================================= */
/*                                 Array                                     */
/* ========================================================================= */

TEST(Array, creating_an_array) {
  s21::Array<int, 5> array;

  EXPECT_FALSE(array.empty());
  EXPECT_EQ(array.size(), 5);

  // EXPECT_EQ(array[0], 0);
  // EXPECT_EQ(array[1], 0);
  // EXPECT_EQ(array[2], 0);
  // EXPECT_EQ(array[3], 0);
  // EXPECT_EQ(array[4], 0);

  EXPECT_THROW(array.at(5), s21::ArrayException);
  EXPECT_THROW(array.at(-1), s21::ArrayException);
}

TEST(Array, creating_an_array_using_initializer_list) {
  s21::Array<int, 5> array{ 1, 2, 3, 4, 5 };

  EXPECT_FALSE(array.empty());
  EXPECT_EQ(array.size(), 5);

  EXPECT_EQ(array[0], 1);
  EXPECT_EQ(array[1], 2);
  EXPECT_EQ(array[2], 3);
  EXPECT_EQ(array[3], 4);
  EXPECT_EQ(array[4], 5);
}

TEST(Array, creating_an_array_using_copy_constructor) {
  s21::Array<int, 5> array{ 1, 2, 3, 4, 5 };

  s21::Array<int, 5> array2 = array;

  EXPECT_EQ(array.size(), 5);
  EXPECT_EQ(array2.size(), 5);

  EXPECT_EQ(array[0], 1);
  EXPECT_EQ(array[1], 2);
  EXPECT_EQ(array[2], 3);
  EXPECT_EQ(array[3], 4);
  EXPECT_EQ(array[4], 5);

  EXPECT_EQ(array2[0], 1);
  EXPECT_EQ(array2[1], 2);
  EXPECT_EQ(array2[2], 3);
  EXPECT_EQ(array2[3], 4);
  EXPECT_EQ(array2[4], 5);
}

TEST(Array, creating_an_array_using_move_constructor) {
  s21::Array<int, 5> array{ 1, 2, 3, 4, 5 };

  s21::Array<int, 5> array2 = std::move(array);

  EXPECT_EQ(array.size(), 5);
  EXPECT_EQ(array2.size(), 5);

  EXPECT_EQ(array[0], 0);
  EXPECT_EQ(array[1], 0);
  EXPECT_EQ(array[2], 0);
  EXPECT_EQ(array[3], 0);
  EXPECT_EQ(array[4], 0);

  EXPECT_EQ(array2[0], 1);
  EXPECT_EQ(array2[1], 2);
  EXPECT_EQ(array2[2], 3);
  EXPECT_EQ(array2[3], 4);
  EXPECT_EQ(array2[4], 5);
}

TEST(Array, creating_an_array_using_move_assignment) {
  s21::Array<int, 5> array{ 1, 2, 3, 4, 5 };

  s21::Array<int, 5> array2;

  EXPECT_EQ(array.size(), 5);
  EXPECT_EQ(array2.size(), 5);

  array2 = std::move(array);

  EXPECT_EQ(array.size(), 5);
  EXPECT_EQ(array2.size(), 5);

  EXPECT_EQ(array[0], 0);
  EXPECT_EQ(array[1], 0);
  EXPECT_EQ(array[2], 0);
  EXPECT_EQ(array[3], 0);
  EXPECT_EQ(array[4], 0);

  EXPECT_EQ(array2[0], 1);
  EXPECT_EQ(array2[1], 2);
  EXPECT_EQ(array2[2], 3);
  EXPECT_EQ(array2[3], 4);
  EXPECT_EQ(array2[4], 5);
}

TEST(Array, testing_access_methods) {
  s21::Array<int, 5> array{ 1, 2, 3, 4, 5 };

  EXPECT_EQ(array.size(), 5);

  EXPECT_EQ(array[0], 1);
  EXPECT_EQ(array[1], 2);
  EXPECT_EQ(array[2], 3);
  EXPECT_EQ(array[3], 4);
  EXPECT_EQ(array[4], 5);

  EXPECT_EQ(array.at(0), 1);
  EXPECT_EQ(array.at(1), 2);
  EXPECT_EQ(array.at(2), 3);
  EXPECT_EQ(array.at(3), 4);
  EXPECT_EQ(array.at(4), 5);

  EXPECT_THROW(array.at(-1), s21::ArrayException);
  EXPECT_THROW(array.at(5), s21::ArrayException);
}

TEST(Array, testing_const_access_methods) {
  const s21::Array<int, 5> array{ 1, 2, 3, 4, 5 };

  EXPECT_EQ(array.size(), 5);

  EXPECT_EQ(array[0], 1);
  EXPECT_EQ(array[1], 2);
  EXPECT_EQ(array[2], 3);
  EXPECT_EQ(array[3], 4);
  EXPECT_EQ(array[4], 5);

  EXPECT_EQ(array.at(0), 1);
  EXPECT_EQ(array.at(1), 2);
  EXPECT_EQ(array.at(2), 3);
  EXPECT_EQ(array.at(3), 4);
  EXPECT_EQ(array.at(4), 5);

  EXPECT_THROW(array.at(-1), s21::ArrayException);
  EXPECT_THROW(array.at(5), s21::ArrayException);
}

TEST(Array, testing_other_access_methods) {
  const s21::Array<int, 5> array{ 1, 2, 3, 4, 5 };

  EXPECT_EQ(array.size(), 5);

  EXPECT_EQ(array.front(), 1);
  EXPECT_EQ(array.back(), 5);
}

TEST(Array, getting_access_to_the_underlying_data) {
  s21::Array<int, 5> array{ 1, 2, 3, 4, 5 };

  EXPECT_EQ(array.size(), 5);

  int* data = array.data();

  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[1], 2);
  EXPECT_EQ(data[2], 3);
  EXPECT_EQ(data[3], 4);
  EXPECT_EQ(data[4], 5);

  data[2] = 9;
  EXPECT_EQ(data[2], 9);
}

TEST(Array, getting_access_to_the_underlying_data_const) {
  const s21::Array<int, 5> array{ 1, 2, 3, 4, 5 };

  EXPECT_EQ(array.size(), 5);

  const int* data = array.data();

  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[1], 2);
  EXPECT_EQ(data[2], 3);
  EXPECT_EQ(data[3], 4);
  EXPECT_EQ(data[4], 5);
}

TEST(Array, testing_iterators) {
  s21::Array<int, 5> array{ 1, 2, 3, 4, 5 };

  EXPECT_EQ(array.size(), 5);

  int* it = array.begin();
  int count = 0;
  while (it != array.end()) {
    EXPECT_EQ(*it, ++count);
    ++it;
  }
}

TEST(Array, testing_const_iterators) {
  const s21::Array<int, 5> array{ 1, 2, 3, 4, 5 };

  EXPECT_EQ(array.size(), 5);

  const int* it = array.cbegin();
  int count = 0;
  while (it != array.cend()) {
    EXPECT_EQ(*it, ++count);
    ++it;
  }
}

TEST(Array, swapping_two_array) {
  s21::Array<int, 5> array{ 1, 2, 3, 4, 5 };
  s21::Array<int, 5> array2{ 5, 4, 3, 2, 1 };

  EXPECT_EQ(array.size(), 5);
  EXPECT_EQ(array2.size(), 5);

  array.swap(array2);

  EXPECT_EQ(array.size(), 5);
  EXPECT_EQ(array2.size(), 5);

  EXPECT_EQ(array[0], 5);
  EXPECT_EQ(array[1], 4);
  EXPECT_EQ(array[2], 3);
  EXPECT_EQ(array[3], 2);
  EXPECT_EQ(array[4], 1);

  EXPECT_EQ(array2[0], 1);
  EXPECT_EQ(array2[1], 2);
  EXPECT_EQ(array2[2], 3);
  EXPECT_EQ(array2[3], 4);
  EXPECT_EQ(array2[4], 5);
}

TEST(Array, autofilling_array) {
  s21::Array<int, 5> array;

  EXPECT_EQ(array.size(), 5);

  array.fill(999);

  EXPECT_EQ(array.size(), 5);

  EXPECT_EQ(array[0], 999);
  EXPECT_EQ(array[1], 999);
  EXPECT_EQ(array[2], 999);
  EXPECT_EQ(array[3], 999);
  EXPECT_EQ(array[4], 999);
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}