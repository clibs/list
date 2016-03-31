
//
// list.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#include "list.h"

/*
 * Allocate a new tlist. NULL on failure.
 */

tlist *
list_new() {
  tlist *self;
  if (!(self = LIST_MALLOC(sizeof *self)))
    return NULL;
  self->head = NULL;
  self->tail = NULL;
  self->free = NULL;
  self->match = NULL;
  self->len = 0;
  return self;
}

/*
 * Free the list.
 */

void
list_destroy(tlist *self) {
  unsigned int len = self->len;
  tlist_node *next;
  tlist_node *curr = self->head;

  while (len--) {
    next = curr->next;
    if (self->free) self->free(curr->val);
    LIST_FREE(curr);
    curr = next;
  }

  LIST_FREE(self);
}

/*
 * Append the given node to the list
 * and return the node, NULL on failure.
 */

tlist_node *
list_rpush(tlist *self, tlist_node *node) {
  if (!node) return NULL;

  if (self->len) {
    node->prev = self->tail;
    node->next = NULL;
    self->tail->next = node;
    self->tail = node;
  } else {
    self->head = self->tail = node;
    node->prev = node->next = NULL;
  }

  ++self->len;
  return node;
}

/*
 * Return / detach the last node in the list, or NULL.
 */

tlist_node *
list_rpop(tlist *self) {
  if (!self->len) return NULL;

  tlist_node *node = self->tail;

  if (--self->len) {
    (self->tail = node->prev)->next = NULL;
  } else {
    self->tail = self->head = NULL;
  }

  node->next = node->prev = NULL;
  return node;
}

/*
 * Return / detach the first node in the list, or NULL.
 */

tlist_node *
list_lpop(tlist *self) {
  if (!self->len) return NULL;

  tlist_node *node = self->head;

  if (--self->len) {
    (self->head = node->next)->prev = NULL;
  } else {
    self->head = self->tail = NULL;
  }

  node->next = node->prev = NULL;
  return node;
}

/*
 * Prepend the given node to the list
 * and return the node, NULL on failure.
 */

tlist_node *
list_lpush(tlist *self, tlist_node *node) {
  if (!node) return NULL;

  if (self->len) {
    node->next = self->head;
    node->prev = NULL;
    self->head->prev = node;
    self->head = node;
  } else {
    self->head = self->tail = node;
    node->prev = node->next = NULL;
  }

  ++self->len;
  return node;
}

/*
 * Return the node associated to val or NULL.
 */

tlist_node *
list_find(tlist *self, void *val) {
  tlist_iterator *it = list_iterator_new(self, LIST_HEAD);
  if(! it)
    return NULL;

  tlist_node *node;

  while ((node = list_iterator_next(it))) {
    if (self->match) {
      if (self->match(val, node->val)) {
        list_iterator_destroy(it);
        return node;
      }
    } else {
      if (val == node->val) {
        list_iterator_destroy(it);
        return node;
      }
    }
  }

  list_iterator_destroy(it);
  return NULL;
}

/*
 * Return the node at the given index or NULL.
 */

tlist_node *
list_at(tlist *self, int index) {
  tlist_direction direction = LIST_HEAD;

  if (index < 0) {
    direction = LIST_TAIL;
    index = ~index;
  }

  if ((unsigned)index < self->len) {
    tlist_iterator *it = list_iterator_new(self, direction);
    if (! it)
      return NULL;

    tlist_node *node = list_iterator_next(it);
    while (index--) node = list_iterator_next(it);
    list_iterator_destroy(it);
    return node;
  }

  return NULL;
}

/*
 * Remove the given node from the list, freeing it and it's value.
 */

void
list_remove(tlist *self, tlist_node *node) {
  node->prev
    ? (node->prev->next = node->next)
    : (self->head = node->next);

  node->next
    ? (node->next->prev = node->prev)
    : (self->tail = node->prev);

  if (self->free) self->free(node->val);

  LIST_FREE(node);
  --self->len;
}
