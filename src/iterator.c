
//
// iterator.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#include "list.h"

ListIterator *
ListIterator_new(List *list, ListDirection direction) {
  ListIterator *self;
  if (!(self = LIST_MALLOC(sizeof(ListIterator))))
    return NULL;
  self->next = direction == ListHead
    ? list->head
    : list->tail;
  self->direction = direction;
  return self;
}

ListNode *
ListIterator_next(ListIterator *self) {
  ListNode *curr = self->next;
  if (curr) {
    self->next = self->direction == ListHead
      ? curr->next
      : curr->prev;
  }
  return curr;
}