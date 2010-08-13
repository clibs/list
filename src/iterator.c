
//
// iterator.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#include "list.h"

/*
 * Allocate a nwe ListIterator. NULL on failure.
 * Accepts a direction, which may be LIST_HEAD or LIST_TAIL.
 */

ListIterator *
ListIterator_new(List *list, ListDirection direction) {
  ListIterator *self;
  if (!(self = LIST_MALLOC(sizeof(ListIterator))))
    return NULL;
  self->next = direction == LIST_HEAD
    ? list->head
    : list->tail;
  self->direction = direction;
  return self;
}

/*
 * Return the next ListNode or NULL when no more
 * nodes remain in the list.
 */

ListNode *
ListIterator_next(ListIterator *self) {
  ListNode *curr = self->next;
  if (curr) {
    self->next = self->direction == LIST_HEAD
      ? curr->next
      : curr->prev;
  }
  return curr;
}

/*
 * Free the list iterator.
 */

void
ListIterator_destroy(ListIterator *self) {
  LIST_FREE(self);
}