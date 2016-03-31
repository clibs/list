
//
// iterator.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#include "list.h"

/*
 * Allocate a new tlist_iterator. NULL on failure.
 * Accepts a direction, which may be LIST_HEAD or LIST_TAIL.
 */

tlist_iterator *
list_iterator_new(tlist *list, tlist_direction direction) {
  tlist_node *node = direction == LIST_HEAD
    ? list->head
    : list->tail;
  return list_iterator_new_from_node(node, direction);
}

/*
 * Allocate a new tlist_iterator with the given start
 * node. NULL on failure.
 */

tlist_iterator *
list_iterator_new_from_node(tlist_node *node, tlist_direction direction) {
  tlist_iterator *self;
  if (!(self = LIST_MALLOC(sizeof *self)))
    return NULL;
  self->next = node;
  self->direction = direction;
  return self;
}

/*
 * Return the next tlist_node or NULL when no more
 * nodes remain in the list.
 */

tlist_node *
list_iterator_next(tlist_iterator *self) {
  tlist_node *curr = self->next;
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
list_iterator_destroy(tlist_iterator *self) {
  LIST_FREE(self);
}
